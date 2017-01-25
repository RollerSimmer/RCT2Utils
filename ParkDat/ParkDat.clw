; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CParkDatDlg
LastTemplate=CStatic
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ParkDat.h"
ODLFile=ParkDat.odl

ClassCount=9
Class1=CParkDatApp
Class2=CParkDatDlg
Class3=CAboutDlg
Class4=CParkDatDlgAutoProxy

ResourceCount=5
Resource1=IDR_ACCELERATOR
Resource2=IDR_MAINFRAME
Resource3=IDD_PARKDAT_DIALOG
Resource4=IDD_ABOUTBOX
Class5=ReportCtrl
Class6=ReportCtrl2
Class7=ReportControl
Class8=ImgFrameClass
Class9=ParkDat_Class_ImgPreview
Resource5=IDR_MENU1

[CLS:CParkDatApp]
Type=0
HeaderFile=ParkDat.h
ImplementationFile=ParkDat.cpp
Filter=N

[CLS:CParkDatDlg]
Type=0
HeaderFile=ParkDatDlg.h
ImplementationFile=ParkDatDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC__EDIT__SEARCH

[CLS:CAboutDlg]
Type=0
HeaderFile=ParkDatDlg.h
ImplementationFile=ParkDatDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CParkDatDlgAutoProxy]
Type=0
HeaderFile=DlgProxy.h
ImplementationFile=DlgProxy.cpp
BaseClass=CCmdTarget
Filter=N

[DLG:IDD_PARKDAT_DIALOG]
Type=1
Class=CParkDatDlg
ControlCount=22
Control1=IDC_STATIC,static,1342308866
Control2=IDC__EDIT__SV6_NAME,edit,1342242944
Control3=IDC__BUTTON__SV6_NAME,button,1342242816
Control4=IDC__BUTTON__OPEN_SV6,button,1342242816
Control5=IDC__BUTTON__SAVE_SV6,button,1342242816
Control6=IDC_STATIC,static,1342308866
Control7=IDC__EDIT__SEARCH,edit,1342242944
Control8=IDC__BUTTON__SEARCH,button,1342242817
Control9=IDC__TEXT__SEARCH_RESULT,static,1342308864
Control10=IDC__LIST__DATS,SysListView32,1350631437
Control11=IDC_PROGRESS,msctls_progress32,1342177281
Control12=IDC_STATIC,button,1342177287
Control13=IDC_EDIT_OUTPUT,edit,1353781444
Control14=IDC_STATIC,button,1342177287
Control15=IDC__BUTTON__ADD_DAT,button,1342242816
Control16=IDC__BUTTON__REPLACE_SELECTED_DAT,button,1342242816
Control17=IDC__BUTTON__DELETE_SELECTED_DAT,button,1342242816
Control18=IDC__BUTTON__UPDATE_DAT_HEADERS,button,1342242816
Control19=IDC__BUTTON__DELETE_UNUSED,button,1342242816
Control20=IDC_STATIC,static,1342308352
Control21=IDC__IMG_FRAME,static,1342177287
Control22=IDC__BUTTON__UPDATE_IMG_PREVIEW,button,1208028928

[ACL:IDR_ACCELERATOR]
Type=1
Class=CParkDatDlg
Command1=IDC__BUTTON__DELETE_UNUSED
Command2=IDC__BUTTON__SEARCH
Command3=IDC__BUTTON__ADD_DAT
Command4=IDC__BUTTON__REPLACE_SELECTED_DAT
Command5=IDC__BUTTON__DELETE_SELECTED_DAT
Command6=IDC__BUTTON__UPDATE_DAT_HEADERS
Command7=IDC__BUTTON__OPEN_SV6
Command8=IDC__BUTTON__SAVE_SV6
Command9=IDC__BUTTON__UPDATE_IMG_PREVIEW
CommandCount=9

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=IDC__BUTTON__OPEN_SV6
Command2=IDC__BUTTON__SAVE_SV6
Command3=IDC__BUTTON__ADD_DAT
Command4=ID_ACTION_REPLACE
Command5=ID_ACTION_DELETE
Command6=ID_ACTION_UPDATE
Command7=IDC__BUTTON__DELETE_UNUSED
CommandCount=7

[CLS:ReportCtrl]
Type=0
HeaderFile=ReportCtrl.h
ImplementationFile=ReportCtrl.cpp
BaseClass=CListCtrl
Filter=W
LastObject=ID_ACTION_DELETE
VirtualFilter=FWC

[CLS:ReportCtrl2]
Type=0
HeaderFile=..\..\..\..\programming\libs\reportctrl\reportctrl.h
ImplementationFile=..\..\..\..\programming\libs\reportctrl\reportctrl.cpp
BaseClass=CListCtrl
Filter=W

[CLS:ReportControl]
Type=0
HeaderFile=ReportControl.h
ImplementationFile=ReportControl.cpp
BaseClass=CListCtrl
Filter=W
LastObject=ReportControl
VirtualFilter=FWC

[CLS:ImgFrameClass]
Type=0
HeaderFile=ImgFrameClass.h
ImplementationFile=ImgFrameClass.cpp
BaseClass=CStatic
Filter=W

[CLS:ParkDat_Class_ImgPreview]
Type=0
HeaderFile=ParkDat_Class_ImgPreview.h
ImplementationFile=ParkDat_Class_ImgPreview.cpp
BaseClass=CStatic
Filter=W
LastObject=ParkDat_Class_ImgPreview
VirtualFilter=WC

