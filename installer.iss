[Setup]
AppName=Chroma Editor
AppVerName=Chroma Editor 1.14
AppPublisher=Razer, Inc.
AppPublisherURL=https://razerzone.com
AppSupportURL=https://razerzone.com
AppUpdatesURL=https://razerzone.com
DefaultDirName={pf32}\Razer\ChromaEditor
DefaultGroupName=Razer\ChromaEditor
OutputBaseFilename=ChromaEditorSetup
SetupIconFile=release_icon.ico
UninstallDisplayIcon=release_icon.ico
Compression=lzma
SolidCompression=yes
InfoBeforeFile=eula.txt
PrivilegesRequired=admin
ChangesAssociations = yes

#define MyAppName "ChromaEditor"
#define MyAppExeName "CConsoleEditor.exe"

[Registry]
Root: HKCR; Subkey: ".chroma"; ValueData: "{#MyAppName}"; Flags: uninsdeletevalue; ValueType: string; ValueName: ""
Root: HKCR; Subkey: "{#MyAppName}\DefaultIcon"; ValueData: "{app}\{#MyAppExeName},0"; ValueType: string; ValueName: ""
Root: HKCR; Subkey: "{#MyAppName}\shell\open\command";  ValueData: """{app}\{#MyAppExeName}"" ""%1"""; ValueType: string; ValueName: ""

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Files]
Source: "ChromaAppInfo.xml"; DestDir: "{pf32}\Razer\ChromaEditor"; CopyMode: alwaysoverwrite
Source: "Win32\Release\CChromaEditorLibrary.dll"; DestDir: "{pf32}\Razer\ChromaEditor"; CopyMode: alwaysoverwrite
Source: "Win32\Release\CConsoleEditor.exe"; DestDir: "{pf32}\Razer\ChromaEditor"; CopyMode: alwaysoverwrite

[Icons]
Name: "{group}\Chroma Editor"; Filename: "{pf32}\Razer\ChromaEditor\CConsoleEditor.exe"; WorkingDir: "{app}";
Name: "{commondesktop}\Chroma Editor"; Filename: "{pf32}\Razer\ChromaEditor\CConsoleEditor.exe"; WorkingDir: "{app}";
Name: "{group}\Uninstall Chroma Editor"; Filename: "{uninstallexe}"

[Run]
Filename: "{pf32}\Razer\ChromaEditor\CConsoleEditor.exe"; Description: "Launch Chroma Editor"; Flags: postinstall skipifsilent runascurrentuser nowait; Parameters: "{userdesktop}\temp.chroma"; WorkingDir: "{app}"
