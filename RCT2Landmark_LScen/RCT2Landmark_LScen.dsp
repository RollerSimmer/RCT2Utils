# Microsoft Developer Studio Project File - Name="RCT2Landmark_LScen" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=RCT2Landmark_LScen - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RCT2Landmark_LScen.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RCT2Landmark_LScen.mak" CFG="RCT2Landmark_LScen - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RCT2Landmark_LScen - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "RCT2Landmark_LScen - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RCT2Landmark_LScen - Win32 Release"

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
# ADD CPP /nologo /Zp1 /MD /w /W0 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /FD /c
# SUBTRACT CPP /YX /Yc /Yu
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

!ELSEIF  "$(CFG)" == "RCT2Landmark_LScen - Win32 Debug"

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

# Name "RCT2Landmark_LScen - Win32 Release"
# Name "RCT2Landmark_LScen - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "lib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=C:\Files\vc2\vcLib\lib\prompt.lib
# End Source File
# Begin Source File

SOURCE=C:\Files\vc2\vcLib\lib\FileIO2.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Programming\libs\libs\mem3.lib
# End Source File
# Begin Source File

SOURCE=C:\Files\vc2\vcLib\lib\BMPLib.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Programming\libs\libs\img256_lib.lib
# End Source File
# Begin Source File

SOURCE=C:\Files\vc1\vclibs\libs\stdlib2.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Programming\libs\libs\superString.lib
# End Source File
# End Group
# Begin Group "dll"

# PROP Default_Filter ""
# Begin Group "import"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\rct2Lib\rct2Lib___Win32_Debug_System32\rct2Lib.lib
# End Source File
# End Group
# End Group
# Begin Group "parse"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\parse\Parse_Input.cpp
# End Source File
# Begin Source File

SOURCE=.\parse\Parse_Output.cpp
# End Source File
# End Group
# Begin Group "bitmap"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\bitmap\bitmap_compile.cpp
# End Source File
# Begin Source File

SOURCE=.\bitmap\bitmap_extract.cpp
# End Source File
# End Group
# Begin Group "mfc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DlgProxy.cpp
# End Source File
# Begin Source File

SOURCE=.\RCT2Landmark_LScen.cpp
# End Source File
# Begin Source File

SOURCE=.\RCT2Landmark_LScen.odl
# End Source File
# Begin Source File

SOURCE=.\RCT2Landmark_LScen.rc
# End Source File
# Begin Source File

SOURCE=.\RCT2Landmark_LScenDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\..\Programming\libs\superString\superString.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "std_h"

# PROP Default_Filter ""
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

SOURCE=..\..\..\..\Programming\include\mem3.h
# End Source File
# Begin Source File

SOURCE=C:\Files\vc1\vclibs\include\stdlib2.h
# End Source File
# Begin Source File

SOURCE=C:\Files\vc2\vcLib\include\stdMacros.h
# End Source File
# Begin Source File

SOURCE=C:\Files\vc2\vcLib\include\STDTYPES.H
# End Source File
# Begin Source File

SOURCE=C:\Files\vc1\vclibs\include\stdtypes0.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Programming\include\superString.h
# End Source File
# End Group
# Begin Group "rct2lib_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\rct2Lib\RCT2\iso\iso.h
# End Source File
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

SOURCE=..\..\rct2Lib\RCT2\SV6\SV6.H
# End Source File
# Begin Source File

SOURCE=..\..\rct2Lib\shared\svx\svx.h
# End Source File
# End Group
# Begin Group "parse_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\parse\Parse.h
# End Source File
# Begin Source File

SOURCE=.\parse\Parse_Input.h
# End Source File
# Begin Source File

SOURCE=.\parse\Parse_Output.h
# End Source File
# Begin Source File

SOURCE=.\parse\Parse_Output_image.inl
# End Source File
# Begin Source File

SOURCE=.\parse\Parse_Output_image_remap.inl
# End Source File
# Begin Source File

SOURCE=.\parse\Parse_Output_infoHeader.inl
# End Source File
# Begin Source File

SOURCE=.\parse\Parse_Output_names.inl
# End Source File
# Begin Source File

SOURCE=.\parse\Parse_Output_pos.inl
# End Source File
# End Group
# Begin Group "bitmap_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\bitmap\bitmap_compile.h
# End Source File
# Begin Source File

SOURCE=.\bitmap\bitmap_extract.h
# End Source File
# End Group
# Begin Group "mfc_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE="C:\Apps\MSVC++6\VC98\Include\BASETSD.H"
# End Source File
# Begin Source File

SOURCE=.\DlgProxy.h
# End Source File
# Begin Source File

SOURCE=.\RCT2Landmark_LScen.h
# End Source File
# Begin Source File

SOURCE=.\RCT2Landmark_LScenDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\palette_rct2.bin
# End Source File
# Begin Source File

SOURCE=.\res\RCT2Landmark_LScen.ico
# End Source File
# Begin Source File

SOURCE=.\res\RCT2Landmark_LScen.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\RCT2Landmark_LScen.reg
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
