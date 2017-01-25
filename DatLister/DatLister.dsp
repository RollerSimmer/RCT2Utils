# Microsoft Developer Studio Project File - Name="DatLister" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DatLister - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DatLister.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DatLister.mak" CFG="DatLister - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DatLister - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DatLister - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DatLister - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "DatLister - Win32 Debug"

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

# Name "DatLister - Win32 Release"
# Name "DatLister - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "lib"

# PROP Default_Filter ""
# Begin Group "dllImport"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\rct2Lib\Debug\rct2Lib.lib
# End Source File
# End Group
# Begin Source File

SOURCE=C:\Files\vc2\vcLib\lib\FileIO2.lib
# End Source File
# Begin Source File

SOURCE=C:\Files\vc2\vcLib\lib\prompt.lib
# End Source File
# Begin Source File

SOURCE=C:\Files\vc2\vcLib\lib\BMPLib.lib
# End Source File
# End Group
# Begin Source File

SOURCE=.\DatLister.cpp
# End Source File
# Begin Source File

SOURCE=.\DatLister.rc
# End Source File
# Begin Source File

SOURCE=.\DatListerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MakeDatList.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "std_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE="C:\Apps\MSVC++6\VC98\Include\BASETSD.H"
# End Source File
# Begin Source File

SOURCE=C:\Files\vc2\vcLib\include\BMPLib.h
# End Source File
# Begin Source File

SOURCE=C:\Files\vc2\vcLib\include\BMPLib__Functions.h
# End Source File
# Begin Source File

SOURCE=C:\Files\vc2\vcLib\include\codeShortcuts.h
# End Source File
# Begin Source File

SOURCE=C:\Files\vc2\vcLib\include\FileIO2.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Programming\include\img256_lib.h
# End Source File
# Begin Source File

SOURCE=C:\Files\vc2\vcLib\include\stdMacros.h
# End Source File
# End Group
# Begin Group "rct2_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\rct2Lib\RCT2\objdat\objdat.h
# End Source File
# Begin Source File

SOURCE=..\..\rct2Lib\RCT2\rct2.h
# End Source File
# Begin Source File

SOURCE=..\..\rct2Lib\RCT2\rct2_chunk.h
# End Source File
# Begin Source File

SOURCE=..\..\rct2Lib\funcs\rct2Funcs.h
# End Source File
# Begin Source File

SOURCE=..\..\rct2Lib\rct2lib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Programming\include\rct2Lib.h
# End Source File
# Begin Source File

SOURCE=C:\Files\vc2\vcLib\include\STDTYPES.H
# End Source File
# Begin Source File

SOURCE=..\..\rct2Lib\RCT2\SV6\SV6.H
# End Source File
# Begin Source File

SOURCE=..\..\rct2Lib\shared\svx\svx.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\DatLister.h
# End Source File
# Begin Source File

SOURCE=.\DatListerDlg.h
# End Source File
# Begin Source File

SOURCE=.\MakeDatList.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\DatLister.ico
# End Source File
# Begin Source File

SOURCE=.\res\DatLister.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
