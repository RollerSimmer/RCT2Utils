; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDatListerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DatLister.h"

ClassCount=3
Class1=CDatListerApp
Class2=CDatListerDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_DATLISTER_DIALOG

[CLS:CDatListerApp]
Type=0
HeaderFile=DatLister.h
ImplementationFile=DatLister.cpp
Filter=N

[CLS:CDatListerDlg]
Type=0
HeaderFile=DatListerDlg.h
ImplementationFile=DatListerDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CDatListerDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=DatListerDlg.h
ImplementationFile=DatListerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DATLISTER_DIALOG]
Type=1
Class=CDatListerDlg
ControlCount=6
Control1=IDC_STATIC,static,1342308354
Control2=IDC__EDIT__DIRECTORY_SELECT,edit,1350631552
Control3=IDC__BUTTON__DIRECTORY_SELECT,button,1342242816
Control4=IDC__DAT_LIST,SysListView32,1350633485
Control5=IDC_BUTTON_LIST,button,1342242817
Control6=IDC_PROGRESS,msctls_progress32,1350565888

