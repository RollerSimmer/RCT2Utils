# Microsoft Developer Studio Project File - Name="SC426_TEST" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SC426_TEST - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Sv426_TEST.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Sv426_TEST.mak" CFG="SC426_TEST - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SC426_TEST - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SC426_TEST - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SC426_TEST - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /Zp1 /w /W0 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib fileio2.lib prompt.lib /nologo /subsystem:windows /machine:I386 /force

!ELSEIF  "$(CFG)" == "SC426_TEST - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /Zp1 /w /W0 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /force /pdbtype:sept /W0
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "SC426_TEST - Win32 Release"
# Name "SC426_TEST - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "lib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\lib\prompt.lib
# End Source File
# Begin Source File

SOURCE=..\lib\FileIO2.lib
# End Source File
# Begin Source File

SOURCE=..\lib\stdlib2.lib
# End Source File
# Begin Source File

SOURCE=..\rct1lib\Debug\rct1lib.lib
# End Source File
# Begin Source File

SOURCE=..\rct2Lib\rct2Lib___Win32_Debug_System32\rct2Lib.lib
# End Source File
# End Group
# Begin Group "426"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\426\426_OBJDAT.Cpp
# End Source File
# Begin Source File

SOURCE=.\426\426_ride_trackVehiConvert.cpp
# End Source File
# Begin Source File

SOURCE=.\426\colorConvert.cpp
# End Source File
# Begin Source File

SOURCE=.\426\ConvertParkData.cpp
# End Source File
# Begin Source File

SOURCE=.\426\mapConvert.cpp
# End Source File
# Begin Source File

SOURCE=.\426\rideConvert.cpp
# End Source File
# Begin Source File

SOURCE=.\426\trackElementConvert.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Sv426_TEST.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "426_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\426\426_compileflags.h
# End Source File
# Begin Source File

SOURCE=.\426\426_map_surface.h
# End Source File
# Begin Source File

SOURCE=.\426\426_OBJDAT.H
# End Source File
# Begin Source File

SOURCE=.\426\426_ride_trackVehiConvert.h
# End Source File
# Begin Source File

SOURCE=.\426\colorConvert.h
# End Source File
# Begin Source File

SOURCE=.\426\ConvertParkData.h
# End Source File
# Begin Source File

SOURCE=.\426\mapConvert.H
# End Source File
# Begin Source File

SOURCE=.\426\rideConvert.h
# End Source File
# Begin Source File

SOURCE=.\426\trackElementConvert.h
# End Source File
# End Group
# Begin Group "rctxlib_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\rct2Lib\RCT2\iso\iso.h
# End Source File
# Begin Source File

SOURCE=..\include\objdat.h
# End Source File
# Begin Source File

SOURCE=..\rct2Lib\RCT2\objdat\objdat.h
# End Source File
# Begin Source File

SOURCE=..\include\rct1Lib.h
# End Source File
# Begin Source File

SOURCE=..\rct1lib\rct1lib.h
# End Source File
# Begin Source File

SOURCE=..\rct2Lib\RCT2\rct2.h
# End Source File
# Begin Source File

SOURCE=..\rct2Lib\RCT2\rct2_chunk.h
# End Source File
# Begin Source File

SOURCE=..\rct2Lib\funcs\rct2Funcs.h
# End Source File
# Begin Source File

SOURCE=..\include\rct2Lib.h
# End Source File
# Begin Source File

SOURCE=..\rct2Lib\rct2lib.h
# End Source File
# Begin Source File

SOURCE=..\include\rct_svx.h
# End Source File
# Begin Source File

SOURCE=..\rct1lib\RCT1\SV4\SV4.H
# End Source File
# Begin Source File

SOURCE=..\rct1lib\RCT1\SV4\SV4_MAP.H
# End Source File
# Begin Source File

SOURCE=..\rct1lib\RCT1\SV4\SV4_MESSAGES.H
# End Source File
# Begin Source File

SOURCE="..\rct1lib\RCT1\SV4\SV4_RIDES.H"
# End Source File
# Begin Source File

SOURCE="..\rct1lib\RCT1\SV4\SV4_SPRITES.H"
# End Source File
# Begin Source File

SOURCE="..\rct1lib\RCT1\SV4\SV4_SV4_PARKDATA.inl"
# End Source File
# Begin Source File

SOURCE=..\rct2Lib\RCT2\SV6\SV6.H
# End Source File
# Begin Source File

SOURCE=..\rct2Lib\RCT2\SV6\SV6_DECODE.h
# End Source File
# Begin Source File

SOURCE=..\rct2Lib\RCT2\SV6\SV6_ENCODE.H
# End Source File
# Begin Source File

SOURCE=..\rct2Lib\RCT2\SV6\SV6_ENCODE_DECODE.H
# End Source File
# Begin Source File

SOURCE=..\rct2Lib\RCT2\SV6\SV6_MAP.H
# End Source File
# Begin Source File

SOURCE=..\rct2Lib\RCT2\SV6\SV6_MESSAGES.H
# End Source File
# Begin Source File

SOURCE=..\rct2Lib\RCT2\SV6\SV6_OBJDAT.H
# End Source File
# Begin Source File

SOURCE=..\rct2Lib\RCT2\SV6\SV6_RIDES.H
# End Source File
# Begin Source File

SOURCE=..\rct2Lib\RCT2\SV6\SV6_SPRITES.H
# End Source File
# Begin Source File

SOURCE="..\rct1lib\shared\svx\svx.h"
# End Source File
# Begin Source File

SOURCE=..\rct2Lib\shared\svx\svx.h
# End Source File
# End Group
# Begin Group "stdlib_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\codeShortcuts.h
# End Source File
# Begin Source File

SOURCE=..\include\FileIO2.h
# End Source File
# Begin Source File

SOURCE=..\include\img256_lib.h
# End Source File
# Begin Source File

SOURCE=..\include\stdMacros.h
# End Source File
# Begin Source File

SOURCE=..\include\STDTYPES.H
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
