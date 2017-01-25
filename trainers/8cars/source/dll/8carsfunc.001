# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=8carsfunc - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to 8carsfunc - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "8carsfunc - Win32 Release" && "$(CFG)" !=\
 "8carsfunc - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "8carsfunc.mak" CFG="8carsfunc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "8carsfunc - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "8carsfunc - Win32 Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "8carsfunc - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "8carsfunc - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "link"
# PROP Intermediate_Dir "compile"
# PROP Target_Dir ""
OUTDIR=.\link
INTDIR=.\compile

ALL : "$(OUTDIR)\8carsfunc.dll"

CLEAN : 
	-@erase "..\..\..\..\rct2\util\utils\trainers\8cars\v131\8carsfunc.dll"
	-@erase ".\compile\spritefuncs.obj"
	-@erase ".\compile\peepColor.obj"
	-@erase ".\compile\clearance.obj"
	-@erase ".\compile\moneyfuncs.obj"
	-@erase ".\compile\terrfuncs.obj"
	-@erase ".\compile\textInput.obj"
	-@erase ".\compile\staffdlg.obj"
	-@erase ".\compile\weather.obj"
	-@erase ".\compile\guestfuncs.obj"
	-@erase ".\compile\ridedlg.obj"
	-@erase ".\compile\parkstatus.obj"
	-@erase ".\compile\mapobjmandlg.obj"
	-@erase ".\compile\mapfuncs.obj"
	-@erase ".\compile\rct2.obj"
	-@erase ".\compile\messages.obj"
	-@erase ".\compile\ridefuncs.obj"
	-@erase ".\compile\8carsfunc.obj"
	-@erase ".\link\8carsfunc.lib"
	-@erase ".\link\8carsfunc.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp1 /MT /w /W0 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /Zp1 /MT /w /W0 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)/8carsfunc.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\compile/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/8carsfunc.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib version.lib /nologo /subsystem:windows /dll /pdb:none /machine:I386 /out:"E:\rct2\util\utils\trainers\8cars\v131\8carsfunc.dll"
# SUBTRACT LINK32 /debug
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib version.lib /nologo /subsystem:windows /dll /pdb:none\
 /machine:I386 /def:".\8carsfunc.def"\
 /out:"E:\rct2\util\utils\trainers\8cars\v131\8carsfunc.dll"\
 /implib:"$(OUTDIR)/8carsfunc.lib" 
DEF_FILE= \
	".\8carsfunc.def"
LINK32_OBJS= \
	"$(INTDIR)/spritefuncs.obj" \
	"$(INTDIR)/peepColor.obj" \
	"$(INTDIR)/clearance.obj" \
	"$(INTDIR)/moneyfuncs.obj" \
	"$(INTDIR)/terrfuncs.obj" \
	"$(INTDIR)/textInput.obj" \
	"$(INTDIR)/staffdlg.obj" \
	"$(INTDIR)/weather.obj" \
	"$(INTDIR)/guestfuncs.obj" \
	"$(INTDIR)/ridedlg.obj" \
	"$(INTDIR)/parkstatus.obj" \
	"$(INTDIR)/mapobjmandlg.obj" \
	"$(INTDIR)/mapfuncs.obj" \
	"$(INTDIR)/rct2.obj" \
	"$(INTDIR)/messages.obj" \
	"$(INTDIR)/ridefuncs.obj" \
	"$(INTDIR)/8carsfunc.obj" \
	"..\..\..\..\vclibs\libs\mem2.lib" \
	"..\..\..\..\vclibs\libs\COLORFUNCS.lib" \
	"..\..\..\..\vclibs\libs\conio2.lib" \
	"..\..\..\..\vclibs\libs\Process.lib" \
	"..\..\..\..\vclibs\libs\io2.lib" \
	"..\..\..\..\vclibs\libs\stddlg.lib" \
	"..\..\..\..\vclibs\libs\stdlib2.lib"

"$(OUTDIR)\8carsfunc.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "8carsfunc - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "link"
# PROP Intermediate_Dir "compile"
# PROP Target_Dir ""
OUTDIR=.\link
INTDIR=.\compile

ALL : "$(OUTDIR)\8carsfunc.dll"

CLEAN : 
	-@erase ".\compile\vc40.pdb"
	-@erase ".\compile\vc40.idb"
	-@erase "..\..\..\..\rct2\util\utils\trainers\8cars\v131\8carsfunc.dll"
	-@erase ".\compile\spritefuncs.obj"
	-@erase ".\compile\peepColor.obj"
	-@erase ".\compile\clearance.obj"
	-@erase ".\compile\moneyfuncs.obj"
	-@erase ".\compile\terrfuncs.obj"
	-@erase ".\compile\textInput.obj"
	-@erase ".\compile\staffdlg.obj"
	-@erase ".\compile\weather.obj"
	-@erase ".\compile\guestfuncs.obj"
	-@erase ".\compile\ridedlg.obj"
	-@erase ".\compile\parkstatus.obj"
	-@erase ".\compile\mapobjmandlg.obj"
	-@erase ".\compile\mapfuncs.obj"
	-@erase ".\compile\rct2.obj"
	-@erase ".\compile\messages.obj"
	-@erase ".\compile\ridefuncs.obj"
	-@erase ".\compile\8carsfunc.obj"
	-@erase ".\link\8carsfunc.lib"
	-@erase ".\link\8carsfunc.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp1 /MTd /w /W0 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /Zp1 /MTd /w /W0 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)/8carsfunc.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\compile/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/8carsfunc.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib version.lib /nologo /subsystem:windows /dll /pdb:none /debug /machine:I386 /out:"E:\rct2\util\utils\trainers\8cars\v131\8carsfunc.dll"
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib version.lib /nologo /subsystem:windows /dll /pdb:none /debug\
 /machine:I386 /def:".\8carsfunc.def"\
 /out:"E:\rct2\util\utils\trainers\8cars\v131\8carsfunc.dll"\
 /implib:"$(OUTDIR)/8carsfunc.lib" 
DEF_FILE= \
	".\8carsfunc.def"
LINK32_OBJS= \
	"$(INTDIR)/spritefuncs.obj" \
	"$(INTDIR)/peepColor.obj" \
	"$(INTDIR)/clearance.obj" \
	"$(INTDIR)/moneyfuncs.obj" \
	"$(INTDIR)/terrfuncs.obj" \
	"$(INTDIR)/textInput.obj" \
	"$(INTDIR)/staffdlg.obj" \
	"$(INTDIR)/weather.obj" \
	"$(INTDIR)/guestfuncs.obj" \
	"$(INTDIR)/ridedlg.obj" \
	"$(INTDIR)/parkstatus.obj" \
	"$(INTDIR)/mapobjmandlg.obj" \
	"$(INTDIR)/mapfuncs.obj" \
	"$(INTDIR)/rct2.obj" \
	"$(INTDIR)/messages.obj" \
	"$(INTDIR)/ridefuncs.obj" \
	"$(INTDIR)/8carsfunc.obj" \
	"..\..\..\..\vclibs\libs\mem2.lib" \
	"..\..\..\..\vclibs\libs\COLORFUNCS.lib" \
	"..\..\..\..\vclibs\libs\conio2.lib" \
	"..\..\..\..\vclibs\libs\Process.lib" \
	"..\..\..\..\vclibs\libs\io2.lib" \
	"..\..\..\..\vclibs\libs\stddlg.lib" \
	"..\..\..\..\vclibs\libs\stdlib2.lib"

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

# Name "8carsfunc - Win32 Release"
# Name "8carsfunc - Win32 Debug"

!IF  "$(CFG)" == "8carsfunc - Win32 Release"

!ELSEIF  "$(CFG)" == "8carsfunc - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\8carsfunc.c
DEP_CPP_8CARS=\
	{$(INCLUDE)}"\8carsfunc.h"\
	".\..\rct2.h"\
	".\..\weather\weather.h"\
	{$(INCLUDE)}"\dlg\ridedlg\ridedlg.h"\
	{$(INCLUDE)}"\dlg\staffdlg\staffdlg.h"\
	{$(INCLUDE)}"\dlg\mapobjmandlg\mapobjmandlg.h"\
	{$(INCLUDE)}"\guests\guestfuncs.h"\
	{$(INCLUDE)}"\dlg\peep color\peepColor.h"\
	{$(INCLUDE)}"\stdtypes.h"\
	

"$(INTDIR)\8carsfunc.obj" : $(SOURCE) $(DEP_CPP_8CARS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=\8cars\c\src\clearance\clearance.c
DEP_CPP_CLEAR=\
	".\..\clearance\clearance.h"\
	".\..\rct2.h"\
	".\..\8cars.h"\
	{$(INCLUDE)}"\objdat.h"\
	{$(INCLUDE)}"\stdtypes.h"\
	

"$(INTDIR)\clearance.obj" : $(SOURCE) $(DEP_CPP_CLEAR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\8cars\c\src\dlg\mapobjmandlg\mapobjmandlg.c
DEP_CPP_MAPOB=\
	{$(INCLUDE)}"\dlg\mapobjmandlg\mapobjmandlg.h"\
	{$(INCLUDE)}"\stddlg.H"\
	".\..\rct2.h"\
	".\..\8cars.h"\
	{$(INCLUDE)}"\stdlib2.h"\
	".\..\parkstatus\parkstatus.h"\
	".\..\mapfuncs\mapfuncs.h"\
	{$(INCLUDE)}"\stdtypes.h"\
	

"$(INTDIR)\mapobjmandlg.obj" : $(SOURCE) $(DEP_CPP_MAPOB) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\8cars\c\src\dlg\ridedlg\ridedlg.c
DEP_CPP_RIDED=\
	{$(INCLUDE)}"\dlg\ridedlg\ridedlg.h"\
	{$(INCLUDE)}"\stddlg.H"\
	".\..\rct2.h"\
	".\..\8cars.h"\
	{$(INCLUDE)}"\stdlib2.h"\
	".\..\parkstatus\parkstatus.h"\
	".\..\ridefuncs\ridefuncs.h"\
	{$(INCLUDE)}"\objdat.h"\
	{$(INCLUDE)}"\stdtypes.h"\
	

"$(INTDIR)\ridedlg.obj" : $(SOURCE) $(DEP_CPP_RIDED) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE="\8cars\c\src\dlg\text input\textInput.c"
DEP_CPP_TEXTI=\
	{$(INCLUDE)}"\stddlg.H"\
	".\..\dlg\text input\TEXTINPUT.H"\
	

"$(INTDIR)\textInput.obj" : $(SOURCE) $(DEP_CPP_TEXTI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\8cars\c\src\guests\guestfuncs.c
DEP_CPP_GUEST=\
	{$(INCLUDE)}"\guests\guestfuncs.h"\
	".\..\8cars.h"\
	".\..\rct2.h"\
	{$(INCLUDE)}"\stdtypes.h"\
	

"$(INTDIR)\guestfuncs.obj" : $(SOURCE) $(DEP_CPP_GUEST) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\8cars\c\src\mapfuncs\mapfuncs.c
DEP_CPP_MAPFU=\
	".\..\process\process.h"\
	".\..\rct2.h"\
	".\..\mapfuncs\mapfuncs.h"\
	".\..\8cars.h"\
	{$(INCLUDE)}"\stdlib2.h"\
	".\..\clearance\clearance.h"\
	{$(INCLUDE)}"\stdtypes.h"\
	

"$(INTDIR)\mapfuncs.obj" : $(SOURCE) $(DEP_CPP_MAPFU) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\8cars\c\src\messages\messages.c
DEP_CPP_MESSA=\
	".\..\messages\messages.h"\
	".\..\rct2.h"\
	".\..\process\process.h"\
	".\..\8cars.h"\
	{$(INCLUDE)}"\stdtypes.h"\
	

"$(INTDIR)\messages.obj" : $(SOURCE) $(DEP_CPP_MESSA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\8cars\c\src\moneyfuncs\moneyfuncs.c
DEP_CPP_MONEY=\
	".\..\moneyfuncs\moneyfuncs.h"\
	".\..\rct2.h"\
	".\..\8cars.h"\
	{$(INCLUDE)}"\stdtypes.h"\
	

"$(INTDIR)\moneyfuncs.obj" : $(SOURCE) $(DEP_CPP_MONEY) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\8cars\c\src\parkstatus\parkstatus.c
DEP_CPP_PARKS=\
	".\..\rct2.h"\
	".\..\parkstatus\parkstatus.h"\
	".\..\process\process.h"\
	".\..\8cars.h"\
	{$(INCLUDE)}"\stdtypes.h"\
	".\..\ridefuncs\ridefuncs.h"\
	".\..\mapfuncs\mapfuncs.h"\
	

"$(INTDIR)\parkstatus.obj" : $(SOURCE) $(DEP_CPP_PARKS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\8cars\c\src\ridefuncs\ridefuncs.c

!IF  "$(CFG)" == "8carsfunc - Win32 Release"

DEP_CPP_RIDEF=\
	".\..\ridefuncs\ridefuncs.h"\
	".\..\8cars.h"\
	{$(INCLUDE)}"\objdat.h"\
	".\..\rct2.h"\
	{$(INCLUDE)}"\stdtypes.h"\
	
NODEP_CPP_RIDEF=\
	".\..\ridefuncs\CASE_TSFCHANGECARSPERTRAIN"\
	

"$(INTDIR)\ridefuncs.obj" : $(SOURCE) $(DEP_CPP_RIDEF) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "8carsfunc - Win32 Debug"

DEP_CPP_RIDEF=\
	".\..\ridefuncs\ridefuncs.h"\
	".\..\8cars.h"\
	{$(INCLUDE)}"\objdat.h"\
	".\..\rct2.h"\
	{$(INCLUDE)}"\stdtypes.h"\
	

"$(INTDIR)\ridefuncs.obj" : $(SOURCE) $(DEP_CPP_RIDEF) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\8cars\c\src\spritefuncs\spritefuncs.c
DEP_CPP_SPRIT=\
	".\..\spritefuncs\spritefuncs.h"\
	".\..\rct2.h"\
	".\..\8cars.h"\
	".\..\ridefuncs\ridefuncs.h"\
	".\..\parkstatus\parkstatus.h"\
	{$(INCLUDE)}"\stdtypes.h"\
	

"$(INTDIR)\spritefuncs.obj" : $(SOURCE) $(DEP_CPP_SPRIT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\8cars\c\src\terrfuncs\terrfuncs.c
DEP_CPP_TERRF=\
	".\..\process\process.h"\
	".\..\rct2.h"\
	".\..\terrfuncs\terrfuncs.h"\
	".\..\mapfuncs\mapfuncs.h"\
	".\..\8cars.h"\
	{$(INCLUDE)}"\stdlib2.h"\
	{$(INCLUDE)}"\sys\Stat.h"\
	{$(INCLUDE)}"\stdtypes.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	

"$(INTDIR)\terrfuncs.obj" : $(SOURCE) $(DEP_CPP_TERRF) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\8cars\c\src\weather\weather.c
DEP_CPP_WEATH=\
	".\..\weather\weather.h"\
	".\..\8cars.h"\
	".\..\rct2.h"\
	{$(INCLUDE)}"\stdtypes.h"\
	

"$(INTDIR)\weather.obj" : $(SOURCE) $(DEP_CPP_WEATH) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\8cars\c\src\rct2.c
DEP_CPP_RCT2_=\
	".\..\rct2.h"\
	".\..\process\process.h"\
	".\..\8cars.h"\
	{$(INCLUDE)}"\stdtypes.h"\
	

"$(INTDIR)\rct2.obj" : $(SOURCE) $(DEP_CPP_RCT2_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\vclibs\libs\stdlib2.lib

!IF  "$(CFG)" == "8carsfunc - Win32 Release"

!ELSEIF  "$(CFG)" == "8carsfunc - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\vclibs\libs\conio2.lib

!IF  "$(CFG)" == "8carsfunc - Win32 Release"

!ELSEIF  "$(CFG)" == "8carsfunc - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\vclibs\libs\io2.lib

!IF  "$(CFG)" == "8carsfunc - Win32 Release"

!ELSEIF  "$(CFG)" == "8carsfunc - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\vclibs\libs\mem2.lib

!IF  "$(CFG)" == "8carsfunc - Win32 Release"

!ELSEIF  "$(CFG)" == "8carsfunc - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\vclibs\libs\Process.lib

!IF  "$(CFG)" == "8carsfunc - Win32 Release"

!ELSEIF  "$(CFG)" == "8carsfunc - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\vclibs\libs\stddlg.lib

!IF  "$(CFG)" == "8carsfunc - Win32 Release"

!ELSEIF  "$(CFG)" == "8carsfunc - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\vclibs\libs\COLORFUNCS.lib

!IF  "$(CFG)" == "8carsfunc - Win32 Release"

!ELSEIF  "$(CFG)" == "8carsfunc - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\8carsfunc.def

!IF  "$(CFG)" == "8carsfunc - Win32 Release"

!ELSEIF  "$(CFG)" == "8carsfunc - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE="\8cars\c\src\dlg\peep color\peepColor.c"
DEP_CPP_PEEPC=\
	{$(INCLUDE)}"\stddlg.H"\
	{$(INCLUDE)}"\stdlib2.h"\
	{$(INCLUDE)}"\dlg\peep color\peepColor.h"\
	".\..\spritefuncs\spritefuncs.h"\
	".\..\rct2.h"\
	{$(INCLUDE)}"\stdtypes.h"\
	

"$(INTDIR)\peepColor.obj" : $(SOURCE) $(DEP_CPP_PEEPC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\8cars\c\src\dlg\staffdlg\staffdlg.c
DEP_CPP_STAFF=\
	{$(INCLUDE)}"\dlg\staffdlg\staffdlg.h"\
	{$(INCLUDE)}"\stddlg.H"\
	".\..\rct2.h"\
	".\..\8cars.h"\
	{$(INCLUDE)}"\stdlib2.h"\
	".\..\parkstatus\parkstatus.h"\
	{$(INCLUDE)}"\objdat.h"\
	{$(INCLUDE)}"\stdtypes.h"\
	

"$(INTDIR)\staffdlg.obj" : $(SOURCE) $(DEP_CPP_STAFF) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
