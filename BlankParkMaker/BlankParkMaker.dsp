# Microsoft Developer Studio Project File - Name="BlankParkMaker" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=BlankParkMaker - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BlankParkMaker.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BlankParkMaker.mak" CFG="BlankParkMaker - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BlankParkMaker - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "BlankParkMaker - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BlankParkMaker - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /Zp1 /w /W0 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "BlankParkMaker - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /Zp1 /w /W0 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "BlankParkMaker - Win32 Release"
# Name "BlankParkMaker - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BlankParkMaker.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\..\rct2Lib\rct2Lib___Win32_Debug_System32\rct2Lib.lib
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "rct2lib"

# PROP Default_Filter ""
# Begin Group "sv6"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\rct2Lib\RCT2\SV6\SV6.H
# End Source File
# Begin Source File

SOURCE=..\..\rct2Lib\RCT2\SV6\SV6_DECODE.h
# End Source File
# Begin Source File

SOURCE=..\..\rct2Lib\RCT2\SV6\SV6_DECODE_DecodeSv6Chunk.inl
# End Source File
# Begin Source File

SOURCE=..\..\rct2Lib\RCT2\SV6\SV6_ENCODE.H
# End Source File
# Begin Source File

SOURCE=..\..\rct2Lib\RCT2\SV6\SV6_ENCODE_DECODE.H
# End Source File
# Begin Source File

SOURCE=..\..\rct2Lib\RCT2\SV6\SV6_ENCODE_EncodeSv6Chunk.inl
# End Source File
# Begin Source File

SOURCE=..\..\rct2Lib\RCT2\SV6\SV6_ENCODE_GetStringEncodeOffset.inl
# End Source File
# Begin Source File

SOURCE=..\..\rct2Lib\RCT2\SV6\SV6_ENCODE_RleEncodeFlush.inl
# End Source File
# Begin Source File

SOURCE=..\..\rct2Lib\RCT2\SV6\SV6_EXTRACTOBJS.h
# End Source File
# Begin Source File

SOURCE=..\..\rct2Lib\RCT2\SV6\SV6_FIXOBJECTS.H
# End Source File
# Begin Source File

SOURCE=..\..\rct2Lib\RCT2\SV6\SV6_MAP.H
# End Source File
# Begin Source File

SOURCE=..\..\rct2Lib\RCT2\SV6\SV6_MESSAGES.H
# End Source File
# Begin Source File

SOURCE=..\..\rct2Lib\RCT2\SV6\SV6_OBJDAT.H
# End Source File
# Begin Source File

SOURCE=..\..\rct2Lib\RCT2\SV6\SV6_OBJDAT_fix.H
# End Source File
# Begin Source File

SOURCE=..\..\rct2Lib\RCT2\SV6\sv6_rideFeatureTable.h
# End Source File
# Begin Source File

SOURCE=..\..\rct2Lib\RCT2\SV6\SV6_RIDES.H
# End Source File
# Begin Source File

SOURCE=..\..\rct2Lib\RCT2\SV6\SV6_SPRITES.H
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\..\Programming\include\rct2Lib.h
# End Source File
# End Group
# Begin Source File

SOURCE="C:\Apps\MSVC++6\VC98\Include\BASETSD.H"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
