# Microsoft Developer Studio Project File - Name="sv6ObjExtract" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=sv6ObjExtract - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "sv6ObjExtract.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sv6ObjExtract.mak" CFG="sv6ObjExtract - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sv6ObjExtract - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "sv6ObjExtract - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "sv6ObjExtract - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /Zp1 /MD /w /W0 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FD /c
# SUBTRACT CPP /X /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /force
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "sv6ObjExtract - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /Zp1 /MDd /w /W0 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /force /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "sv6ObjExtract - Win32 Release"
# Name "sv6ObjExtract - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "sv6"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\RCT2\SV6\SV6_DECODE.Cpp
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\SV6_EXTRACTOBJS.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\sv6ObjExtract.cpp
# End Source File
# Begin Source File

SOURCE=.\sv6ObjExtract.rc
# End Source File
# Begin Source File

SOURCE=.\sv6ObjExtractDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "sv6 No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\RCT2\SV6\SV6.H
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\SV6_DECODE.h
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\SV6_DECODE_DecodeSv6Chunk.inl
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\SV6_ENCODE_DECODE.H
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\SV6_EXTRACTOBJS.h
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\SV6_MAP.H
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\SV6_MESSAGES.H
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\SV6_OBJDAT.H
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\SV6_RIDES.H
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\SV6_SPRITES.H
# End Source File
# End Group
# Begin Source File

SOURCE="..\..\..\..\Apps\MSVC++6\VC98\Include\BASETSD.H"
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Files\vc2\vcLib\include\FileIO2.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Files\vc1\vclibs\include\stdlib2.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Files\vc2\vcLib\include\STDTYPES.H
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Files\vc1\vclibs\include\stdtypes0.h
# End Source File
# Begin Source File

SOURCE=.\sv6ObjExtract.h
# End Source File
# Begin Source File

SOURCE=.\sv6ObjExtractDlg.h
# End Source File
# Begin Source File

SOURCE=.\shared\svx\svx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\sv6ObjExtract.ico
# End Source File
# Begin Source File

SOURCE=.\res\sv6ObjExtract.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Files\vc2\vcLib\lib\prompt.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Files\vc2\vcLib\lib\FileIO2.lib
# End Source File
# End Target
# End Project
