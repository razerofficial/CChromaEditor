#include "stdafx.h"
#include "ChromaLogger.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <filesystem>
#include "VerifyLibrarySignature.h"
#include <psapi.h>
#include <wintrust.h>
#include <Softpub.h>
#include <shlwapi.h>

#pragma comment (lib, "wintrust")
#pragma comment (lib, "Psapi")
#pragma comment(lib, "crypt32")
#pragma comment(lib, "ShLwApi")

using namespace std;

namespace ChromaSDK
{

	// Source: https://docs.microsoft.com/en-us/windows/desktop/seccrypto/example-c-program--verifying-the-signature-of-a-pe-file
	BOOL VerifyLibrarySignature::VerifyModule(const std::wstring& filename)
	{
		return IsFileSigned(filename.c_str());
	}

	BOOL VerifyLibrarySignature::IsFileSignedByRazer(const wchar_t* szFileName)
	{
		BOOL bResult = FALSE;

		// File is signed, lets check the whos the certificate is issue to.
		HCERTSTORE hStore = NULL;
		HCRYPTMSG hMsg = NULL;
		DWORD dwEncoding = 0;
		DWORD dwContentType = 0;
		DWORD dwFormatType = 0;
		LPTSTR szName = NULL;
		PCMSG_SIGNER_INFO pSignerInfo = NULL;
		PCCERT_CONTEXT pCertContext = NULL;

		if (TRUE == CryptQueryObject(CERT_QUERY_OBJECT_FILE,
			szFileName,
			CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED_EMBED,
			CERT_QUERY_FORMAT_FLAG_BINARY,
			0,
			&dwEncoding,
			&dwContentType,
			&dwFormatType,
			&hStore,
			&hMsg,
			NULL))
		{
			DWORD dwSignerInfo = 0;

			if (TRUE == CryptMsgGetParam(hMsg,
				CMSG_SIGNER_INFO_PARAM,
				0,
				NULL,
				&dwSignerInfo))
			{
				// Allocate memory for signer information.
				pSignerInfo = (PCMSG_SIGNER_INFO)LocalAlloc(LPTR, dwSignerInfo);

				if (TRUE == CryptMsgGetParam(hMsg,
					CMSG_SIGNER_INFO_PARAM,
					0,
					(PVOID)pSignerInfo,
					&dwSignerInfo))
				{
					CERT_INFO CertInfo = {};
					CertInfo.Issuer = pSignerInfo->Issuer;
					CertInfo.SerialNumber = pSignerInfo->SerialNumber;

					pCertContext = CertFindCertificateInStore(hStore,
						(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING),
						0,
						CERT_FIND_SUBJECT_CERT,
						(PVOID)&CertInfo,
						NULL);

					if (pCertContext != NULL)
					{
						DWORD dwData = 0;

						// Get Subject name size.
						dwData = CertGetNameString(pCertContext,
							CERT_NAME_SIMPLE_DISPLAY_TYPE,
							0,
							NULL,
							NULL,
							0);

						if (dwData > 1)
						{
							// Allocate memory for subject name.
							szName = (LPTSTR)LocalAlloc(LPTR, dwData * sizeof(TCHAR));

							// Get subject name.
							if (CertGetNameString(pCertContext,
								CERT_NAME_SIMPLE_DISPLAY_TYPE,
								0,
								NULL,
								szName,
								dwData) > 1)
							{
								// Compare the issuer
								if (_tcsicmp(szName, L"Razer USA Ltd.") == 0)
								{
									bResult = TRUE;
								}
							}
						}
					}
				}
			}
		}

		LocalFree(szName);
		LocalFree(pSignerInfo);
		CertFreeCertificateContext(pCertContext);
		CertCloseStore(hStore, 0);
		CryptMsgClose(hMsg);

		return bResult;
	}

	BOOL VerifyLibrarySignature::IsFileSigned(const wchar_t* szFileName)
	{
		BOOL bResult = FALSE;
		DWORD dwLastError = 0;

		WINTRUST_FILE_INFO FileData = {};

		FileData.cbStruct = sizeof(WINTRUST_FILE_INFO);
		FileData.pcwszFilePath = szFileName;
		FileData.hFile = NULL;
		FileData.pgKnownSubject = NULL;

		/*
		WVTPolicyGUID specifies the policy to apply on the file
		WINTRUST_ACTION_GENERIC_VERIFY_V2 policy checks:

		1) The certificate used to sign the file chains up to a root
		certificate located in the trusted root certificate store. This
		implies that the identity of the publisher has been verified by
		a certification authority.

		2) In cases where user interface is displayed (which this example
		does not do), WinVerifyTrust will check for whether the
		end entity certificate is stored in the trusted publisher store,
		implying that the user trusts content from this publisher.

		3) The end entity certificate has sufficient permission to sign
		code, as indicated by the presence of a code signing EKU or no
		EKU.
		*/

		GUID WVTPolicyGUID = WINTRUST_ACTION_GENERIC_VERIFY_V2;

		WINTRUST_DATA WinTrustData = {};

		WinTrustData.cbStruct = sizeof(WinTrustData);
		WinTrustData.pPolicyCallbackData = NULL;
		WinTrustData.pSIPClientData = NULL;
		WinTrustData.dwUIChoice = WTD_UI_NONE;
		WinTrustData.fdwRevocationChecks = WTD_REVOKE_NONE;
		WinTrustData.dwUnionChoice = WTD_CHOICE_FILE;
		WinTrustData.dwStateAction = WTD_STATEACTION_VERIFY;
		WinTrustData.hWVTStateData = NULL;
		WinTrustData.pwszURLReference = NULL;
		WinTrustData.dwUIContext = 0;
		WinTrustData.pFile = &FileData;

		// WinVerifyTrust verifies signatures as specified by the GUID 
		// and Wintrust_Data.
		LONG lStatus = WinVerifyTrust(
			NULL,
			&WVTPolicyGUID,
			&WinTrustData);

		switch (lStatus)
		{
		case ERROR_SUCCESS:
			/*
			Signed file:
				- Hash that represents the subject is trusted.

				- Trusted publisher without any verification errors.

				- UI was disabled in dwUIChoice. No publisher or
					time stamp chain errors.

				- UI was enabled in dwUIChoice and the user clicked
					"Yes" when asked to install and run the signed
					subject.
			*/
			bResult = IsFileSignedByRazer(szFileName);
			break;
		case TRUST_E_NOSIGNATURE:
			// The file was not signed or had a signature 
			// that was not valid.

			// Get the reason for no signature.
			dwLastError = GetLastError();
			if (TRUST_E_NOSIGNATURE == dwLastError ||
				TRUST_E_SUBJECT_FORM_UNKNOWN == dwLastError ||
				TRUST_E_PROVIDER_UNKNOWN == dwLastError)
			{
				// The file was not signed.
			}
			else
			{
				// The signature was not valid or there was an error 
				// opening the file.
			}

			bResult = FALSE;
			break;
		case TRUST_E_EXPLICIT_DISTRUST:
			// The hash that represents the subject or the publisher 
			// is not allowed by the admin or user.
			bResult = FALSE;
			break;
		case TRUST_E_SUBJECT_NOT_TRUSTED:
			// The user clicked "No" when asked to install and run.
			bResult = FALSE;
			break;
		case CRYPT_E_SECURITY_SETTINGS:
			/*
			The hash that represents the subject or the publisher
			was not explicitly trusted by the admin and the
			admin policy has disabled user trust. No signature,
			publisher or time stamp errors.
			*/
			bResult = FALSE;
			break;
		default:
			// The UI was disabled in dwUIChoice or the admin policy 
			// has disabled user trust. lStatus contains the 
			// publisher or time stamp chain error.
			dwLastError = GetLastError();
			bResult = FALSE;
			break;
		}

		// Any hWVTStateData must be released by a call with close.
		WinTrustData.dwStateAction = WTD_STATEACTION_CLOSE;

		lStatus = WinVerifyTrust(
			NULL,
			&WVTPolicyGUID,
			&WinTrustData);

		return bResult;
	}

	BOOL VerifyLibrarySignature::IsFileVersionSameOrNewer(const std::wstring& filename, const int minMajor, const int minMinor, const int minRevision, const int minBuild)
	{
		std::filesystem::path p = filename.c_str();
		std::error_code pathError;
		if (!std::filesystem::exists(p, pathError))
		{
			ChromaLogger::fwprintf(stderr, L"Library not found! %s\r\n", filename.c_str());
			return false;
		}

		bool result = false;

		DWORD  verHandle = 0;
		UINT   size = 0;
		LPBYTE lpBuffer = NULL;
		DWORD  verSize = GetFileVersionInfoSize(filename.c_str(), &verHandle);

		if (verSize)
		{
			LPSTR verData = (LPSTR)malloc(verSize);

			if (GetFileVersionInfo(filename.c_str(), verHandle, verSize, verData))
			{
				if (VerQueryValue(verData, L"\\", (VOID FAR * FAR*) & lpBuffer, &size))
				{
					if (size)
					{
						VS_FIXEDFILEINFO* verInfo = (VS_FIXEDFILEINFO*)lpBuffer;
						if (verInfo->dwSignature == 0xfeef04bd)
						{
							const int major = (verInfo->dwFileVersionMS >> 16) & 0xffff;
							const int minor = (verInfo->dwFileVersionMS >> 0) & 0xffff;
							const int revision = (verInfo->dwFileVersionLS >> 16) & 0xffff;
							const int build = (verInfo->dwFileVersionLS >> 0) & 0xffff;

							ChromaLogger::wprintf(L"File Version: %d.%d.%d.%d %s\r\n", major, minor, revision, build, filename.c_str());

							// Anything less than the min version returns false

							if (major < minMajor) // Less than X
							{
								result = false;
							}
							else if (major == minMajor && minor < minMinor) // Less than major.X
							{
								result = false;
							}
							else if (major == minMajor && minor == minMinor && revision < minRevision) // Less than major.minor.X
							{
								result = false;
							}
							else if (major == minMajor && minor == minMinor && revision == minRevision && build < minBuild) // Less than major.minor.revision.X
							{
								result = false;
							}
							else
							{
								result = true; // production version or better
							}
						}
					}
				}
			}
			free(verData);
		}

		return result;
	}

}
