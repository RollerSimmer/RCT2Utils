# Microsoft Developer Studio Project File - Name="8carsfunc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=8carsfunc - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "8carsfunc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "8carsfunc.mak" CFG="8carsfunc - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "8carsfunc - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "8carsfunc - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "8carsfunc - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\link"
# PROP Intermediate_Dir ".\compile"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp1 /MT /w /W0 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib version.lib /nologo /subsystem:windows /dll /pdb:none /machine:I386 /out:"E:\winnt\system32\8carsfunc.dll"
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "8carsfunc - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\8cars_Output"
# PROP Intermediate_Dir ".\8cars_Intermediate"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp1 /MTd /w /W0 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib version.lib /nologo /subsystem:windows /dll /pdb:none /debug /machine:I386 /force /out:"E:\winnt\system32\8carsfunc.dll"
# SUBTRACT LINK32 /nodefaultlib

!ENDIF 

# Begin Target

# Name "8carsfunc - Win32 Release"
# Name "8carsfunc - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\8carsfunc.c
# End Source File
# Begin Source File

SOURCE=.\8carsfunc.def
# End Source File
# Begin Source File

SOURCE=..\clearance\clearance.c
# End Source File
# Begin Source File

SOURCE=..\guests\guestfuncs.c
# End Source File
# Begin Source File

SOURCE=..\mapfuncs\mapfuncs.c
# End Source File
# Begin Source File

SOURCE=..\dlg\mapobjmandlg\mapobjmandlg.c
# End Source File
# Begin Source File

SOURCE=..\messages\messages.c
# End Source File
# Begin Source File

SOURCE=..\moneyfuncs\moneyfuncs.c
# End Source File
# Begin Source File

SOURCE=..\parkstatus\parkstatus.c
# End Source File
# Begin Source File

SOURCE="..\dlg\peep color\peepColor.c"
# End Source File
# Begin Source File

SOURCE=..\rct2.c
# End Source File
# Begin Source File

SOURCE=..\dlg\ridedlg\ridedlg.c
# End Source File
# Begin Source File

SOURCE=..\ridefuncs\ridefuncs.c
# End Source File
# Begin Source File

SOURCE=..\spritefuncs\spritefuncs.c
# End Source File
# Begin Source File

SOURCE=..\dlg\staffdlg\staffdlg.c
# End Source File
# Begin Source File

SOURCE=..\terrfuncs\terrfuncs.c
# End Source File
# Begin Source File

SOURCE="..\dlg\text input\textInput.c"
# End Source File
# Begin Source File

SOURCE=..\weather\weather.c
# End Source File
# Begin Source File

SOURCE=C:\Files\vc1\vclibs\libs\stdlib2.lib
# End Source File
# Begin Source File

SOURCE=C:\Files\vc1\vclibs\libs\conio2.lib
# End Source File
# Begin Source File

SOURCE=C:\Files\vc1\vclibs\libs\io2.lib
# End Source File
# Begin Source File

SOURCE=C:\Files\vc1\vclibs\libs\stddlg.lib
# End Source File
# Begin Source File

SOURCE=C:\Files\vc1\vclibs\libs\COLORFUNCS.lib
# End Source File
# Begin Source File

SOURCE=C:\Files\vc1\vclibs\libs\PROCESS.LIB
# End Source File
# Begin Source File

SOURCE=C:\Files\vc1\vclibs\libs\mem2C.lib
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Group "messages"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\messages\messages.H
# End Source File
# End Group
# Begin Source File

SOURCE=..\8cars.h
# End Source File
# Begin Source File

SOURCE=..\8cars_windowName.h
# End Source File
# Begin Source File

SOURCE=.\8carsfunc.h
# End Source File
# Begin Source File

SOURCE="C:\Apps\MSVC++6\VC98\Include\BASETSD.H"
# End Source File
# Begin Source File

SOURCE=..\clearance\clearance.h
# End Source File
# Begin Source File

SOURCE=C:\Files\vc2\vcLib\include\codeShortcuts.h
# End Source File
# Begin Source File

SOURCE=..\guests\guestfuncs.h
# End Source File
# Begin Source File

SOURCE=..\mapfuncs\mapfuncs.h
# End Source File
# Begin Source File

SOURCE=..\dlg\mapobjmandlg\mapobjmandlg.h
# End Source File
# Begin Source File

SOURCE=..\moneyfuncs\moneyfuncs.h
# End Source File
# Begin Source File

SOURCE=C:\Files\vc1\vclibs\include\objdat.h
# End Source File
# Begin Source File

SOURCE=..\parkstatus\parkstatus.h
# End Source File
# Begin Source File

SOURCE="..\dlg\peep color\peepColor.h"
# End Source File
# Begin Source File

SOURCE=..\rct2.h
# End Source File
# Begin Source File

SOURCE=..\resource.h
# End Source File
# Begin Source File

SOURCE=..\dlg\ridedlg\ridedlg.h
# End Source File
# Begin Source File

SOURCE=..\ridefuncs\ridefuncs.h
# End Source File
# Begin Source File

SOURCE=..\spritefuncs\spritefuncs.h
# End Source File
# Begin Source File

SOURCE=..\dlg\staffdlg\staffdlg.h
# End Source File
# Begin Source File

SOURCE=C:\Files\vc1\vclibs\include\stddlg.H
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

SOURCE=..\terrfuncs\terrfuncs.h
# End Source File
# Begin Source File

SOURCE="..\dlg\text input\textInput.h"
# End Source File
# Begin Source File

SOURCE=..\weather\weather.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\4CARS.ico
# End Source File
# Begin Source File

SOURCE=..\icon1.ico
# End Source File
# End Group
# Begin Group "8cars"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\8cars.rc
# PROP Exclude_From_Build 1
# End Source File
# End Group
# End Target
# End Project
