# Microsoft Developer Studio Project File - Name="sv4_to_sv6" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=sv4_to_sv6 - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "sv6_obj_fixer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sv6_obj_fixer.mak" CFG="sv4_to_sv6 - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sv4_to_sv6 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "sv4_to_sv6 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "sv4_to_sv6 - Win32 Debug"

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
# ADD CPP /nologo /Zp1 /MDd /w /W0 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /FD /GZ /c
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
# SUBTRACT LINK32 /pdb:none /incremental:no

!ELSEIF  "$(CFG)" == "sv4_to_sv6 - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "sv4_to_sv6___Win32_Release"
# PROP BASE Intermediate_Dir "sv4_to_sv6___Win32_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\Games\RCT2Fi~1\Utils\sv6_obj_fixer\Win32_Release"
# PROP Intermediate_Dir "C:\Games\RCT2Fi~1\Utils\sv6_obj_fixer\Win32_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp1 /MDd /w /W0 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /FD /GZ /c
# ADD CPP /nologo /Zp1 /MD /w /W0 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /force /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none /incremental:no
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /force /out:"C:\Games\RCT2Fi~1\Utils\sv6_obj_fixer_v1\1_1\sv6_obj_fixer.exe" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none /incremental:no

!ENDIF 

# Begin Target

# Name "sv4_to_sv6 - Win32 Debug"
# Name "sv4_to_sv6 - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "fix"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\sv6_obj_fixer\funcs\rct2Funcs.cpp
# End Source File
# Begin Source File

SOURCE=..\sv6_obj_fixer\RCT2\SV6\SV6_DECODE.Cpp
# End Source File
# Begin Source File

SOURCE=..\sv6_obj_fixer\RCT2\SV6\SV6_ENCODE.cpp
# End Source File
# Begin Source File

SOURCE=..\sv6_obj_fixer\RCT2\SV6\SV6_FIXOBJECTS.CPP
# End Source File
# Begin Source File

SOURCE=..\sv6_obj_fixer\RCT2\SV6\SV6_OBJDAT_fix.Cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\sv6_obj_fixer\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=..\sv6_obj_fixer\sv6_obj_fixer.cpp
# End Source File
# Begin Source File

SOURCE=..\sv6_obj_fixer\sv6_obj_fixer.rc
# End Source File
# Begin Source File

SOURCE=..\sv6_obj_fixer\sv6_obj_fixerDLG.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\sv6_obj_fixer\RCT2\SV6\SV6_OBJDAT.H
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\sv4_to_sv6.ico
# End Source File
# Begin Source File

SOURCE=..\sv6_obj_fixer\res\sv4_to_sv6.ico
# End Source File
# Begin Source File

SOURCE=.\res\sv4_to_sv6.rc2
# End Source File
# Begin Source File

SOURCE=..\sv6_obj_fixer\res\sv6_obj_fixer.ico
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\..\Files\vc2\vcLib\lib\prompt.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Files\vc2\vcLib\lib\FileIO2.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Files\vc1\vclibs\libs\stdlib2.lib
# End Source File
# End Target
# End Project
