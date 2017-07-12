// ColorButton.cpp : implementation file
//
// Written by Marius Bancila (mbancila@yahoo.com)
// Copyright (c) 2004.
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. If 
// the source code in  this file is used in any commercial application 
// then acknowledgement must be made to the author of this file 
// (in whatever form you wish).
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
// THE AUTHOR BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
// IN THE SOFTWARE.
// 
// Please use and enjoy. Please let me know of any bugs/mods/improvements 
// that you have found/implemented and I will fix/incorporate them into this
// file. 

#include "stdafx.h"
#include "ColorButton.h"

#include <afxtempl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace clr
{
	const COLORREF CLR_BTN_WHITE  = RGB(255, 255, 255);
	const COLORREF CLR_BTN_BLACK  = RGB(0, 0, 0);
	const COLORREF CLR_BTN_DGREY  = RGB(128, 128, 128);
	const COLORREF CLR_BTN_GREY   = RGB(192, 192, 192);
	const COLORREF CLR_BTN_LLGREY = RGB(223, 223, 223);
}

/////////////////////////////////////////////////////////////////////////////
// CColorButton
CColorButton::CColorButton()
{
	SetColorToWindowsDefault();
}

CColorButton::CColorButton(COLORREF text, COLORREF bkgnd)
{
	m_TextColor				= text;
	m_BkgndColor			= bkgnd; 
	m_DisabledBkgndColor	= GetSysColor(COLOR_BTNFACE);
	m_Light					= GetSysColor(COLOR_3DLIGHT);
	m_Highlight				= GetSysColor(COLOR_BTNHIGHLIGHT);
	m_Shadow				= GetSysColor(COLOR_BTNSHADOW);
	m_DarkShadow			= GetSysColor(COLOR_3DDKSHADOW);	
}

CColorButton::CColorButton(COLORREF text, COLORREF bkgnd, COLORREF disabled)
{
	m_TextColor				= text;
	m_BkgndColor			= bkgnd; 
	m_DisabledBkgndColor	= disabled;
	m_Light					= GetSysColor(COLOR_3DLIGHT);
	m_Highlight				= GetSysColor(COLOR_BTNHIGHLIGHT);
	m_Shadow				= GetSysColor(COLOR_BTNSHADOW);
	m_DarkShadow			= GetSysColor(COLOR_3DDKSHADOW);	
}

CColorButton::CColorButton(COLORREF text, COLORREF bkgnd, COLORREF disabled, COLORREF light, COLORREF highlight, COLORREF shadow, COLORREF darkShadow)
{
	m_TextColor				= text;
	m_BkgndColor			= bkgnd; 
	m_DisabledBkgndColor	= disabled;
	m_Light					= light;
	m_Highlight				= highlight;
	m_Shadow				= shadow;
	m_DarkShadow			= darkShadow;
}

CColorButton::~CColorButton()
{
}


BEGIN_MESSAGE_MAP(CColorButton, CButton)
	//{{AFX_MSG_MAP(CColorButton)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorButton message handlers

void CColorButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC		*pDC;
	CRect	rcFocus, rcButton, rcText, rcOffsetText;
	UINT	state;
	
	pDC    = CDC::FromHandle(lpDrawItemStruct->hDC);
	state = lpDrawItemStruct->itemState;
	
	rcFocus.CopyRect(&lpDrawItemStruct->rcItem); 
	rcButton.CopyRect(&lpDrawItemStruct->rcItem); 
	
	rcText = rcButton;
	rcText.OffsetRect(-1, -1);

	rcOffsetText = rcText;
	rcOffsetText.OffsetRect(1, 1);
	
	// Set the focus rectangle to just past the border decoration
	rcFocus.left   += 4;
    rcFocus.right  -= 4;
    rcFocus.top    += 4;
    rcFocus.bottom -= 4;
	
	// Retrieve the button's caption
	CString strCaption;
	GetWindowText(strCaption);
	
	if (state & ODS_DISABLED)
    {
		DrawFilledRect(pDC, rcButton, m_DisabledBkgndColor);
	}
	else
	{
		DrawFilledRect(pDC, rcButton, m_BkgndColor);
	}
	
	if (state & ODS_SELECTED)
	{ 
		DrawFrame(pDC, rcButton, BUTTON_IN);
	}
	else
	{
		if ((state & ODS_DEFAULT) || (state & ODS_FOCUS))
		{
			DrawFrame(pDC, rcButton, BUTTON_OUT | BUTTON_BLACK_BORDER);			
		}
		else
		{
			DrawFrame(pDC, rcButton, BUTTON_OUT);
		}
	}
	
	if (state & ODS_DISABLED)
	{
		DrawButtonText(pDC, rcOffsetText, strCaption, clr::CLR_BTN_WHITE);
		DrawButtonText(pDC, rcText,	strCaption, clr::CLR_BTN_DGREY);
    }
	else
	{
		if (state & ODS_SELECTED)
		{
			DrawButtonText(pDC, rcOffsetText, strCaption, m_TextColor);
		}
		else
		{
			DrawButtonText(pDC, rcText, strCaption, m_TextColor);
		}
	}
	
	if (state & ODS_FOCUS)
	{
		DrawFocusRect(lpDrawItemStruct->hDC, (LPRECT)&rcFocus);
	}	
}

void CColorButton::DrawFrame(CDC *pDC, CRect rc, int state)
{
	COLORREF color;
	
	if (state & BUTTON_BLACK_BORDER)
	{
		color = clr::CLR_BTN_BLACK;
		
		DrawLine(pDC, rc.left, rc.top, rc.right, rc.top,    color); // Across top
		DrawLine(pDC, rc.left, rc.top, rc.left,  rc.bottom, color); // Down left
		
		DrawLine(pDC, rc.left,      rc.bottom - 1, rc.right,     rc.bottom - 1, color); // Across bottom
		DrawLine(pDC, rc.right - 1, rc.top,        rc.right - 1, rc.bottom,     color); // Down right
		
		rc.InflateRect(-1, -1);
	}
	
	if (state & BUTTON_OUT)
	{
		color = m_Highlight;
		
		DrawLine(pDC, rc.left, rc.top, rc.right, rc.top,    color); // Across top
		DrawLine(pDC, rc.left, rc.top, rc.left,  rc.bottom, color); // Down left
		
		color = m_DarkShadow;
		
		DrawLine(pDC, rc.left,      rc.bottom - 1, rc.right,     rc.bottom - 1, color); // Across bottom
		DrawLine(pDC, rc.right - 1, rc.top,        rc.right - 1, rc.bottom,     color); // Down right
		
		rc.InflateRect(-1, -1);
		
		color = m_Light;
		
		DrawLine(pDC, rc.left, rc.top, rc.right, rc.top,    color); // Across top
		DrawLine(pDC, rc.left, rc.top, rc.left,  rc.bottom, color); // Down left
		
		color = m_Shadow;
		
		DrawLine(pDC, rc.left,      rc.bottom - 1, rc.right,     rc.bottom - 1, color); // Across bottom
		DrawLine(pDC, rc.right - 1, rc.top,        rc.right - 1, rc.bottom,     color); // Down right
	}
	
	if (state & BUTTON_IN)
	{
		color = m_DarkShadow;
		
		DrawLine(pDC, rc.left, rc.top, rc.right, rc.top,    color); // Across top
		DrawLine(pDC, rc.left, rc.top, rc.left,  rc.bottom, color); // Down left
		DrawLine(pDC, rc.left,      rc.bottom - 1, rc.right,     rc.bottom - 1, color); // Across bottom
		DrawLine(pDC, rc.right - 1, rc.top,        rc.right - 1, rc.bottom,     color); // Down right
		
		rc.InflateRect(-1, -1);
		
		color = m_Shadow;
		
		DrawLine(pDC, rc.left, rc.top, rc.right, rc.top,    color); // Across top
		DrawLine(pDC, rc.left, rc.top, rc.left,  rc.bottom, color); // Down left
		DrawLine(pDC, rc.left,      rc.bottom - 1, rc.right,     rc.bottom - 1, color); // Across bottom
		DrawLine(pDC, rc.right - 1, rc.top,        rc.right - 1, rc.bottom,     color); // Down right
	}
}

void CColorButton::DrawFilledRect(CDC *pDC, CRect rc, COLORREF color)
{
	CBrush brSolid;
	
	brSolid.CreateSolidBrush(color);
	pDC->FillRect(rc, &brSolid);
}

void CColorButton::DrawLine(CDC *pDC, long sx, long sy, long ex, long ey, COLORREF color)
{
	CPen newPen;
	CPen *oldPen;
	
	newPen.CreatePen(PS_SOLID, 1, color);
	oldPen = pDC->SelectObject(&newPen);

	pDC->MoveTo(sx, sy);
	pDC->LineTo(ex, ey);
	pDC->SelectObject(oldPen);

    newPen.DeleteObject();	
}

void CColorButton::DrawButtonText(CDC *pDC, CRect rc, CString strCaption, COLORREF textcolor)
{
	DWORD uStyle = GetWindowLong(this->m_hWnd,GWL_STYLE);

	CArray<CString, CString> arLines;

	if((uStyle & BS_MULTILINE) == BS_MULTILINE)
	{
		int nIndex = 0;
		while(nIndex != -1)
		{
			nIndex = strCaption.Find('\n');
			if(nIndex>-1)
			{
				CString line = strCaption.Left(nIndex);
				arLines.Add(line);
				strCaption.Delete(0,nIndex+1);
			}
			else
				arLines.Add(strCaption);
		}
	}
	else
	{
		arLines.Add(strCaption);
	}

	CSize sizeText = pDC->GetOutputTextExtent( strCaption );
	
    COLORREF oldColour;
	
	oldColour = pDC->SetTextColor(textcolor);
	pDC->SetBkMode(TRANSPARENT);
	
	int nStartPos = (rc.Height() - arLines.GetSize()*sizeText.cy)/2-1;
	if((uStyle & BS_TOP) == BS_TOP)
		nStartPos = rc.top+2;
	if((uStyle & BS_BOTTOM) == BS_BOTTOM)
		nStartPos = rc.bottom- arLines.GetSize()*sizeText.cy-2;
	if((uStyle & BS_VCENTER) == BS_VCENTER)
		nStartPos = (rc.Height() - arLines.GetSize()*sizeText.cy)/2-1;
	
	UINT uDrawStyles = 0;
	if((uStyle & BS_CENTER) == BS_CENTER)
		uDrawStyles |= DT_CENTER;
	else
	{
		if((uStyle & BS_LEFT) == BS_LEFT)
			uDrawStyles |= DT_LEFT;
		else
		if((uStyle & BS_RIGHT) == BS_RIGHT)
			uDrawStyles |= DT_RIGHT;
		else
		if(uDrawStyles == 0)
			uDrawStyles = DT_CENTER|DT_VCENTER | DT_SINGLELINE;
	}
	
	for(int i=0; i<arLines.GetSize(); i++)
	{
		CRect textrc = rc;
		textrc.DeflateRect(3,0,3,0);
		textrc.top = nStartPos + sizeText.cy*i;
		textrc.bottom = nStartPos + sizeText.cy*(i+1);
		CString line = arLines.GetAt(i);
		pDC->DrawText(line, line.GetLength(), textrc, uDrawStyles);
	}

	pDC->SetTextColor(oldColour);
}

void CColorButton::SetColor(COLORREF text, COLORREF bkgnd)
{
	m_TextColor				= text;
	m_BkgndColor			= bkgnd; 

	if(m_hWnd != NULL)
		Invalidate();
}

void CColorButton::SetColor(COLORREF text, COLORREF bkgnd, COLORREF disabled)
{
	m_TextColor				= text;
	m_BkgndColor			= bkgnd; 
	m_DisabledBkgndColor	= disabled;

	if(m_hWnd != NULL)
		Invalidate();
}

void CColorButton::SetColor(COLORREF text, COLORREF bkgnd, COLORREF disabled, COLORREF light, COLORREF highlight, COLORREF shadow, COLORREF darkShadow)
{
	m_TextColor				= text;
	m_BkgndColor			= bkgnd; 
	m_DisabledBkgndColor	= disabled;
	m_Light					= light;
	m_Highlight				= highlight;
	m_Shadow				= shadow;
	m_DarkShadow			= darkShadow;

	if(m_hWnd != NULL)
		Invalidate();
}

void CColorButton::SetColorToWindowsDefault()
{
	m_TextColor				= GetSysColor(COLOR_BTNTEXT);
	m_BkgndColor			= GetSysColor(COLOR_BTNFACE); 
	m_DisabledBkgndColor	= GetSysColor(COLOR_BTNFACE);
	m_Light					= GetSysColor(COLOR_3DLIGHT);
	m_Highlight				= GetSysColor(COLOR_BTNHIGHLIGHT);
	m_Shadow				= GetSysColor(COLOR_BTNSHADOW);
	m_DarkShadow			= GetSysColor(COLOR_3DDKSHADOW);	
}

int CColorButton::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	lpCreateStruct->dwExStyle |= BS_OWNERDRAW;

	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}
