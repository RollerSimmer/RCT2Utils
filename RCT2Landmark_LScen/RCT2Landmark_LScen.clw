; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRCT2Landmark_LScenDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "RCT2Landmark_LScen.h"
ODLFile=RCT2Landmark_LScen.odl

ClassCount=3
Class1=CRCT2Landmark_LScenApp
Class2=CRCT2Landmark_LScenDlg

ResourceCount=4
Resource2=IDR_MAINFRAME
Resource3=IDD_RCT2LANDMARK_LSCEN_DIALOG
Class3=CRCT2Landmark_LScenDlgAutoProxy
Resource4=IDD_SV6_OBJ_FIXER_DIALOG

[CLS:CRCT2Landmark_LScenApp]
Type=0
HeaderFile=RCT2Landmark_LScen.h
ImplementationFile=RCT2Landmark_LScen.cpp
Filter=N

[CLS:CRCT2Landmark_LScenDlg]
Type=0
HeaderFile=RCT2Landmark_LScenDlg.h
ImplementationFile=RCT2Landmark_LScenDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDIT_OUTPUT


[CLS:CRCT2Landmark_LScenDlgAutoProxy]
Type=0
HeaderFile=DlgProxy.h
ImplementationFile=DlgProxy.cpp
BaseClass=CCmdTarget
Filter=N

[DLG:IDD_RCT2LANDMARK_LSCEN_DIALOG]
Type=1
Class=CRCT2Landmark_LScenDlg
ControlCount=21
Control1=IDC_STATIC,static,1342308866
Control2=IDC__EDIT__LSCEN_DAT_NAME,edit,1342242944
Control3=IDC__BUTTON__LSCEN_DAT_NAME,button,1342242817
Control4=IDC_STATIC,static,1342308866
Control5=IDC__EDIT__RCT2LMM_PROJECT_NAME,edit,1342242944
Control6=IDC__BUTTON__RCT2LMM_PROJECT_NAME,button,1342242817
Control7=IDC_STATIC,button,1342177287
Control8=IDC_EDIT_OUTPUT,edit,1353781444
Control9=IDC__BUTTON__EXTRACT_TO_PROJECT,button,1342254848
Control10=IDC__BUTTON__EXTRACT_FULL_VIEWS,button,1342254848
Control11=IDC__BUTTON__EXTRACT_TILE_IMAGES,button,1342254848
Control12=IDC_STATIC,static,1342177294
Control13=IDC__CHECK__USE_IMG_NUM,button,1342275587
Control14=IDC_STATIC,static,1342177294
Control15=IDC_STATIC,static,1342308352
Control16=IDC_START_IMG_I,edit,1350631552
Control17=IDC_STATIC,static,1342177294
Control18=IDC__CHECK__USE_COL_ROW_ROT,button,1342275587
Control19=IDC__BUTTON__TEST_SAVE_DAT,button,1208037120
Control20=IDC__BUTTON__BUILD_DAT,button,1342254848
Control21=IDC_RCT2LMM_PROGRESS,msctls_progress32,1350565888

[DLG:IDD_SV6_OBJ_FIXER_DIALOG]
Type=1
Class=?
ControlCount=5
Control1=IDC_STATIC,static,1342308866
Control2=IDC_EDIT_SV6NAME,edit,1342242944
Control3=IDC_BUTTON_SV6NAME,button,1342242817
Control4=IDC_BUTTON_WRITESV6FILE,button,1342254848
Control5=IDC_MESSAGE,static,1342378496

