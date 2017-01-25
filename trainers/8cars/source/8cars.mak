# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=8cars - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to 8cars - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "8cars - Win32 Release" && "$(CFG)" != "8cars - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "8cars.mak" CFG="8cars - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "8cars - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "8cars - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "8cars - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "8cars - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "8cars___"
# PROP BASE Intermediate_Dir "8cars___"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "8cars_Output"
# PROP Intermediate_Dir "8cars_Intermediate"
# PROP Target_Dir ""
OUTDIR=.\8cars_Output
INTDIR=.\8cars_Intermediate

ALL : "$(OUTDIR)\8cars131.exe"

CLEAN : 
	-@erase "..\..\..\rct2\util\utils\trainers\8cars\v131\8cars131.exe"
	-@erase ".\8cars_Intermediate\8cars.obj"
	-@erase ".\8cars_Intermediate\8cars.res"
	-@erase "..\..\..\rct2\util\utils\trainers\8cars\v131\8cars131.ilk"
	-@erase ".\8cars_Output\8cars131.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp1 /w /W0 /Gi /GX /Gf /Gy /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /Zp1 /ML /w /W0 /Gi /GX /Gf /Gy /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)/8cars.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\8cars_Intermediate/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/8cars.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/8cars.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 COMCTL32.LIB kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib VERSION.LIB /nologo /subsystem:windows /incremental:yes /debug /machine:I386 /out:"E:\rct2\util\utils\trainers\8cars\v131\8cars131.exe"
LINK32_FLAGS=COMCTL32.LIB kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib VERSION.LIB /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/8cars131.pdb" /debug /machine:I386\
 /out:"E:\rct2\util\utils\trainers\8cars\v131\8cars131.exe" 
LINK32_OBJS= \
	"$(INTDIR)/8cars.obj" \
	"$(INTDIR)/8cars.res" \
	".\dll\link\8carsfunc.lib"

"$(OUTDIR)\8cars131.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "8cars - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "8cars__0"
# PROP BASE Intermediate_Dir "8cars__0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "8cars_Output"
# PROP Intermediate_Dir "8cars_Intermediate"
# PROP Target_Dir ""
OUTDIR=.\8cars_Output
INTDIR=.\8cars_Intermediate

ALL : "$(OUTDIR)\8cars131.exe"

CLEAN : 
	-@erase ".\8cars_Intermediate\vc40.pdb"
	-@erase ".\8cars_Intermediate\vc40.idb"
	-@erase "..\..\..\rct2\util\utils\trainers\8cars\v131\8cars131.exe"
	-@erase ".\8cars_Intermediate\8cars.obj"
	-@erase ".\8cars_Intermediate\8cars.res"
	-@erase "..\..\..\rct2\util\utils\trainers\8cars\v131\8cars131.ilk"
	-@erase ".\8cars_Output\8cars131.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp1 /w /W0 /Gm /Gi /GX /Zi /Od /Gf /Gy /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /Zp1 /MLd /w /W0 /Gm /Gi /GX /Zi /Od /Gf /Gy /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)/8cars.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\8cars_Intermediate/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/8cars.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/8cars.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 stddlg.lib stdlib2.lib COMCTL32.LIB kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib VERSION.LIB /nologo /subsystem:windows /debug /machine:I386 /out:"E:\rct2\util\utils\trainers\8cars\v131\8cars131.exe"
# SUBTRACT LINK32 /incremental:no /nodefaultlib
LINK32_FLAGS=stddlg.lib stdlib2.lib COMCTL32.LIB kernel32.lib user32.lib\
 gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib\
 oleaut32.lib uuid.lib odbc32.lib odbccp32.lib VERSION.LIB /nologo\
 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)/8cars131.pdb" /debug\
 /machine:I386 /out:"E:\rct2\util\utils\trainers\8cars\v131\8cars131.exe" 
LINK32_OBJS= \
	"$(INTDIR)/8cars.obj" \
	"$(INTDIR)/8cars.res" \
	".\dll\link\8carsfunc.lib"

"$(OUTDIR)\8cars131.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "8cars - Win32 Release"
# Name "8cars - Win32 Debug"

!IF  "$(CFG)" == "8cars - Win32 Release"

!ELSEIF  "$(CFG)" == "8cars - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\8cars.c
DEP_CPP_8CARS=\
	{$(INCLUDE)}"\8carsfunc.h"\
	".\terrfuncs\..\process\process.h"\
	".\weather\..\rct2.h"\
	".\terrfuncs\terrfuncs.h"\
	".\terrfuncs\..\mapfuncs\mapfuncs.h"\
	".\terrfuncs\..\8cars.h"\
	".\weather\weather.h"\
	".\moneyfuncs\moneyfuncs.h"\
	".\messages\messages.H"\
	".\dlg\ridedlg\..\..\parkstatus\parkstatus.h"\
	".\dlg\ridedlg\ridedlg.h"\
	".\dlg\mapobjmandlg\mapobjmandlg.h"\
	".\guests\guestfuncs.h"\
	{$(INCLUDE)}"\stdtypes.h"\
	

"$(INTDIR)\8cars.obj" : $(SOURCE) $(DEP_CPP_8CARS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\8cars.rc
DEP_RSC_8CARS_=\
	".\4CARS.ico"\
	".\icon1.ico"\
	".\dlg\peep color\colorpalette.bmp"\
	

"$(INTDIR)\8cars.res" : $(SOURCE) $(DEP_RSC_8CARS_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dll\link\8carsfunc.lib

!IF  "$(CFG)" == "8cars - Win32 Release"

!ELSEIF  "$(CFG)" == "8cars - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\rct2\util\utils\trainers\8cars\v131\8carsfunc.dll

!IF  "$(CFG)" == "8cars - Win32 Release"

!ELSEIF  "$(CFG)" == "8cars - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
