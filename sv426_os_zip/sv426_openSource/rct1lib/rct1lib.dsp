# Microsoft Developer Studio Project File - Name="rct1lib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=rct1lib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "rct1lib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "rct1lib.mak" CFG="rct1lib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "rct1lib - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "rct1lib - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "rct1lib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RCT1LIB_EXPORTS" /YX /FD /c
# ADD CPP /nologo /Zp1 /MT /w /W0 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RCT1LIB_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /force /out:"e:\winnt\system32\rct1lib.dll"

!ELSEIF  "$(CFG)" == "rct1lib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RCT1LIB_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /Zp1 /MTd /w /W0 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RCT1LIB_EXPORTS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /force /out:"e:\winnt\system32\rct1lib.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "rct1lib - Win32 Release"
# Name "rct1lib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "rct1"

# PROP Default_Filter ""
# Begin Group "sv4"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\RCT1\SV4\sv4_OpenSave.cpp
# End Source File
# End Group
# End Group
# Begin Group "lib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\lib\FileIO2.lib
# End Source File
# Begin Source File

SOURCE=..\lib\prompt.lib
# End Source File
# End Group
# Begin Group "rctx"

# PROP Default_Filter ""
# Begin Group "svx"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\shared\svx\SVX_DECODE.Cpp
# End Source File
# End Group
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "rct1_h"

# PROP Default_Filter ""
# Begin Group "sv4_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\RCT1\SV4\SV4.H
# End Source File
# Begin Source File

SOURCE=.\RCT1\SV4\SV4_MAP.H
# End Source File
# Begin Source File

SOURCE=.\RCT1\SV4\SV4_MESSAGES.H
# End Source File
# Begin Source File

SOURCE=.\RCT1\SV4\SV4_RIDES.H
# End Source File
# Begin Source File

SOURCE=.\RCT1\SV4\SV4_SPRITES.H
# End Source File
# Begin Source File

SOURCE=.\RCT1\SV4\SV4_SV4_PARKDATA.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\RCT1\rct.h
# End Source File
# End Group
# Begin Group "rctx_h"

# PROP Default_Filter ""
# Begin Group "svx_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\rct_svx.h
# End Source File
# Begin Source File

SOURCE=.\shared\svx\svx.h
# End Source File
# Begin Source File

SOURCE=.\shared\svx\SVX_ENCODE_DECODE.H
# End Source File
# End Group
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
