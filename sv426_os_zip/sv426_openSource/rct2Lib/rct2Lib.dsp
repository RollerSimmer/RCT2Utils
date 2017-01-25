# Microsoft Developer Studio Project File - Name="rct2Lib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=rct2Lib - Win32 Debug_System32
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "rct2Lib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "rct2Lib.mak" CFG="rct2Lib - Win32 Debug_System32"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "rct2Lib - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "rct2Lib - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "rct2Lib - Win32 Debug_ParkDat" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "rct2Lib - Win32 Release_ParkDat" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "rct2Lib - Win32 Debug_Park_Editor" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "rct2Lib - Win32 Debug_System32" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "rct2Lib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "out"
# PROP Intermediate_Dir "out"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RCT2LIB_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /Zp1 /MD /w /W0 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RCT2LIB_EXPORTS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /force

!ELSEIF  "$(CFG)" == "rct2Lib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "out"
# PROP Intermediate_Dir "out"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RCT2LIB_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /Zp1 /MTd /w /W0 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RCT2LIB_EXPORTS" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /force /out:"E:\games\rct2 files\utils\BlankParkMaker\Debug\rct2Lib.dll" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "rct2Lib - Win32 Debug_ParkDat"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "rct2Lib___Win32_Debug_ParkDat"
# PROP BASE Intermediate_Dir "rct2Lib___Win32_Debug_ParkDat"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "rct2Lib_Parkdat"
# PROP Intermediate_Dir "rct2Lib_Parkdat"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp1 /MTd /w /W0 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RCT2LIB_EXPORTS" /FD /GZ /c
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /nologo /Zp1 /MTd /w /W0 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RCT2LIB_EXPORTS" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /force /out:"E:\games\rct2 files\utils\RCT2Landmark_LScen\Debug\rct2Lib.dll" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /force /out:"E:\games\rct2 files\utils\ParkDat\out\rct2Lib.dll" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "rct2Lib - Win32 Release_ParkDat"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "rct2Lib___Win32_Release_ParkDat"
# PROP BASE Intermediate_Dir "rct2Lib___Win32_Release_ParkDat"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "rct2Lib_Parkdat"
# PROP Intermediate_Dir "rct2Lib_Parkdat"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp1 /MT /w /W0 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RCT2LIB_EXPORTS" /FD /c
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /nologo /Zp1 /MDd /w /W0 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RCT2LIB_EXPORTS" /FR /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /force /out:"E:\games\rct2 files\utils\RCT2Landmark_LScen\Release/rct2Lib.dll"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /debug /machine:I386 /force /out:"E:\games\rct2 files\utils\ParkDat\out\rct2Lib.dll"

!ELSEIF  "$(CFG)" == "rct2Lib - Win32 Debug_Park_Editor"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "rct2Lib___Win32_Debug_Park_Editor"
# PROP BASE Intermediate_Dir "rct2Lib___Win32_Debug_Park_Editor"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "rct2Lib___Win32_Debug_Park_Editor"
# PROP Intermediate_Dir "rct2Lib___Win32_Debug_Park_Editor"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp1 /MTd /w /W0 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RCT2LIB_EXPORTS" /FD /GZ /c
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /nologo /Zp1 /MTd /w /W0 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RCT2LIB_EXPORTS" /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /force /out:"E:\games\rct2 files\utils\ParkDat\out\rct2Lib.dll" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /force /out:"E:\games\rct2 files\utils\Park Editor\debug\rct2Lib.dll" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "rct2Lib - Win32 Debug_System32"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "rct2Lib___Win32_Debug_System32"
# PROP BASE Intermediate_Dir "rct2Lib___Win32_Debug_System32"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "rct2Lib___Win32_Debug_System32"
# PROP Intermediate_Dir "rct2Lib___Win32_Debug_System32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp1 /MTd /w /W0 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RCT2LIB_EXPORTS" /FD /GZ /c
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /nologo /Zp1 /MTd /w /W0 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RCT2LIB_EXPORTS" /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /force /out:"E:\games\rct2 files\utils\BlankParkMaker\Debug\rct2Lib.dll" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /force /out:"E:\winnt\system32\rct2Lib.dll" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "rct2Lib - Win32 Release"
# Name "rct2Lib - Win32 Debug"
# Name "rct2Lib - Win32 Debug_ParkDat"
# Name "rct2Lib - Win32 Release_ParkDat"
# Name "rct2Lib - Win32 Debug_Park_Editor"
# Name "rct2Lib - Win32 Debug_System32"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "rct2"

# PROP Default_Filter ""
# Begin Group "sv6"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\RCT2\SV6\SV6.cpp
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\SV6_DECODE.Cpp
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\SV6_ENCODE.cpp
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\SV6_EXTRACTOBJS.cpp
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\SV6_FIXOBJECTS.CPP
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\sv6_genNew.cpp
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\sv6_map.cpp
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\SV6_OBJDAT.Cpp
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\SV6_OBJDAT_fix.Cpp
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\sv6_rideFeatureTable.cpp
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\SV6_SPRITES.cpp
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\sv6_terrFuncs.cpp
# End Source File
# End Group
# Begin Group "objdat"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\RCT2\objdat\objdat_all.cpp
# End Source File
# Begin Source File

SOURCE=.\RCT2\objdat\objDat_CopyImage.cpp
# End Source File
# Begin Source File

SOURCE=.\RCT2\objdat\objDat_Image.cpp
# End Source File
# Begin Source File

SOURCE=.\RCT2\objdat\objdat_LargeScenery.cpp
# End Source File
# End Group
# Begin Group "funcs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\funcs\rct2Funcs.cpp
# End Source File
# Begin Source File

SOURCE=.\funcs\rctFuncs.cpp
# End Source File
# End Group
# End Group
# Begin Group "lib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\lib\prompt.lib
# End Source File
# Begin Source File

SOURCE=..\lib\BMPLib.lib
# End Source File
# Begin Source File

SOURCE=..\lib\FileIO2.lib
# End Source File
# Begin Source File

SOURCE=..\lib\basicOps.lib
# End Source File
# Begin Source File

SOURCE=..\lib\img256_lib.lib
# End Source File
# Begin Source File

SOURCE=..\lib\stdlib2.lib
# End Source File
# Begin Source File

SOURCE=..\lib\mem3.lib
# End Source File
# End Group
# Begin Group "resource"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\rct2lib.rc
# End Source File
# Begin Source File

SOURCE=.\readResource.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\rct2Lib.cpp
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "objdat_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\RCT2\objdat\objdat.h
# End Source File
# Begin Source File

SOURCE=.\RCT2\objdat\objdat_all.h
# End Source File
# End Group
# Begin Group "sv6_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\rct2Lib.h
# End Source File
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

SOURCE=.\RCT2\SV6\SV6_ENCODE.H
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\SV6_ENCODE_DECODE.H
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\SV6_ENCODE_EncodeSv6Chunk.inl
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\SV6_ENCODE_GetStringEncodeOffset.inl
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\SV6_ENCODE_RleEncodeFlush.inl
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

SOURCE=.\RCT2\SV6\SV6_OBJDAT_fix.H
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\SV6_RIDES.H
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\SV6_SPRITES.H
# End Source File
# End Group
# Begin Group "func_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\funcs\rct2Funcs.h
# End Source File
# Begin Source File

SOURCE=.\funcs\rctFuncs.h
# End Source File
# End Group
# Begin Group "lib_h"

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

SOURCE=..\include\mem3.h
# End Source File
# Begin Source File

SOURCE=.\readResource.h
# End Source File
# Begin Source File

SOURCE=..\include\stdlib2.h
# End Source File
# Begin Source File

SOURCE=..\include\stdMacros.h
# End Source File
# Begin Source File

SOURCE=..\include\STDTYPES.H
# End Source File
# Begin Source File

SOURCE=..\include\stdtypes0.h
# End Source File
# End Group
# Begin Group "svx_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\rct_svx.h
# End Source File
# Begin Source File

SOURCE=.\shared\svx\svx.h
# End Source File
# End Group
# Begin Group "rct2_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\RCT2\rct2.h
# End Source File
# Begin Source File

SOURCE=.\RCT2\rct2_chunk.h
# End Source File
# End Group
# Begin Group "rct2lib_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE="C:\Apps\MSVC++6\VC98\Include\BASETSD.H"
# End Source File
# Begin Source File

SOURCE=.\rct2lib.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "iso_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\RCT2\iso\iso.h
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\RCT2\SV6\genTemplates\blankMap.bin
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\genTemplates\header.bin
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\genTemplates\mapData.bin
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\genTemplates\objDatTable.bin
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\genTemplates\parkData.bin
# End Source File
# Begin Source File

SOURCE=.\RCT2\SV6\rideFeature\rct2_trackFeatures.bin
# End Source File
# Begin Source File

SOURCE=.\rct2_trackFeatures.bin
# End Source File
# Begin Source File

SOURCE=.\ride_fea.bin
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
