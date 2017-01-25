# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

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
!MESSAGE "8cars - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "8cars - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Output_Dir "8cars___"
# PROP Intermediate_Dir "8cars___"
# PROP Target_Dir ""
OUTDIR=.\8cars___
INTDIR=.\8cars___

ALL : "$(OUTDIR)\8carsfunc.dll"

CLEAN : 
	-@erase "..\..\rct2\util\utils\trainers\8cars\v131\8carsfunc.dll"
	-@erase ".\8cars___\8carsfunc.obj"
	-@erase ".\8cars___\8carsfunc.lib"
	-@erase ".\8cars___\8carsfunc.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /w /W0 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /c
# SUBTRACT CPP /YX
CPP_PROJ=/nologo /MT /w /W0 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\8cars___/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/8cars.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /out:"E:\rct2\util\utils\trainers\8cars\v131\8carsfunc.dll"
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/8carsfunc.pdb" /machine:I386\
 /out:"E:\rct2\util\utils\trainers\8cars\v131\8carsfunc.dll"\
 /implib:"$(OUTDIR)/8carsfunc.lib" 
LINK32_OBJS= \
	".\8cars___\8carsfunc.obj"

"$(OUTDIR)\8carsfunc.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "8cars - Win32 Debug"

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
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\8carsfunc.dll"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase "..\..\rct2\util\utils\trainers\8cars\v131\8carsfunc.dll"
	-@erase ".\Debug\8carsfunc.obj"
	-@erase "..\..\rct2\util\utils\trainers\8cars\v131\8carsfunc.ilk"
	-@erase ".\Debug\8carsfunc.lib"
	-@erase ".\Debug\8carsfunc.exp"
	-@erase ".\Debug\8carsfunc.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /w /W0 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /c
# SUBTRACT CPP /YX
CPP_PROJ=/nologo /MTd /w /W0 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/8cars.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"E:\rct2\util\utils\trainers\8cars\v131\8carsfunc.dll"
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/8carsfunc.pdb" /debug /machine:I386\
 /out:"E:\rct2\util\utils\trainers\8cars\v131\8carsfunc.dll"\
 /implib:"$(OUTDIR)/8carsfunc.lib" 
LINK32_OBJS= \
	".\Debug\8carsfunc.obj"

"$(OUTDIR)\8carsfunc.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

SOURCE=.\8carsfunc.c
DEP_CPP_8CARS=\
	".\8carsfunc.h"\
	

!IF  "$(CFG)" == "8cars - Win32 Release"


"$(INTDIR)\8carsfunc.obj" : $(SOURCE) $(DEP_CPP_8CARS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "8cars - Win32 Debug"


"$(INTDIR)\8carsfunc.obj" : $(SOURCE) $(DEP_CPP_8CARS) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
