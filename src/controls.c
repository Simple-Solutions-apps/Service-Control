/*-------------------------------------------
  Copyright Simple Solutions, 2022
  Revised: 2022/05/30 14:09
-------------------------------------------*/

//standard includes
#include <windows.h>
#include <commctrl.h> 

//custom includes
#include "..\include\controls.h"

//Declarations
HFONT cDefaultFont;

HWND sGrpBoxParams;
HWND sGrpBoxCMDLine;

HWND sLabelCommand;
HWND sLabelSvrName;
HWND sLabelSvcName;
HWND sLabelType;
HWND sLabelInteract;
HWND sLabelStart;
HWND sLabelError;
HWND sLabelPathBin;
HWND sLabelGroup;
HWND sLabelTag;
HWND sLabelDepend;
HWND sLabelAccName;
HWND sLabelObjName;
HWND sLabelDispName;
HWND sLabelPW;
HWND sLabelDesc;
HWND sLabelCMDLine;

HWND sComboCommand;
HWND sComboType;
HWND sComboInteract;
HWND sComboStart;
HWND sComboError;
HWND sComboTag;

HWND sEditDepend;
HWND sEditAccName;
HWND sEditObjName;
HWND sEditDispName;
HWND sEditPW;
HWND sEditDesc;
HWND sEditSvrName;
HWND sEditSvcName;
HWND sEditPathBin;
HWND sEditGroup;
HWND sEditCMDLine;

HWND sBtnBrowse;
HWND sBtnCMDRun;

HWND sToolBar;
HWND sStatusBar;

//image list handle for toolbar
HIMAGELIST sImageList;

void CreateControls(HWND hwnd)
{
	cDefaultFont = GetStockObject(SYSTEM_FONT); //ANSI_FIXED_FONT ANSI_VAR_FONT DEVICE_DEFAULT_FONT DEFAULT_GUI_FONT OEM_FIXED_FONT SYSTEM_FIXED_FONT

	HANDLE vModHandle = GetModuleHandle(NULL);

	sGrpBoxParams = CreateWindowEx(0, "BUTTON", "Parameters", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
	5, 40, 850, 275, hwnd, (HMENU) IDC_GRPBOX_PARAMS, vModHandle, NULL);
	
	int iPosLabelY = 70;
	int iIncLabelY = 30;
	int iPosCtrlY = 65;
	int iIncCtrlY = 30;
	int iPosCol1 = 10;
	int iPosCol2 = iPosCol1 + 110;
	int iPosCol3 = iPosCol2 + 160;
	int iPosCol4 = iPosCol3 + 110;

	//begin creating labels
	{
	sLabelCommand = CreateWindowEx(0, "STATIC", "Command", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	iPosCol1, iPosLabelY, 105, 20, hwnd, (HMENU) IDC_LABEL_COMMAND, vModHandle, NULL);
	if(sLabelCommand == NULL)
	{
		MessageBox(hwnd, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);
	}
	//Adding text to label
	SendMessage(sLabelCommand, WM_SETFONT, (WPARAM)cDefaultFont, MAKELPARAM(0, 0));
	//SendMessage(sLabelCommand, WM_SETTEXT, (WPARAM)cDefaultFont, (LPARAM) "Command:");

	iPosLabelY = iPosLabelY + iIncLabelY;
	
	sLabelSvrName = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_RIGHT,
	iPosCol1, iPosLabelY, 105, 20, hwnd, (HMENU) IDC_LABEL_SVRNAME, vModHandle, NULL);
	if(sLabelSvrName == NULL)
	{
		MessageBox(hwnd, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}	
	SendMessage(sLabelSvrName, WM_SETFONT, (WPARAM)cDefaultFont, MAKELPARAM(0, 0));
	SendMessage(sLabelSvrName, WM_SETTEXT, (WPARAM)cDefaultFont, (LPARAM) "Server name:");
		
	iPosLabelY = iPosLabelY + iIncLabelY;
	
	sLabelSvcName = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_RIGHT,
	iPosCol1, iPosLabelY, 105, 20, hwnd, (HMENU) IDC_LABEL_SVCNAME, vModHandle, NULL);
	if(sLabelSvcName == NULL)
	{
		MessageBox(hwnd, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}	
	SendMessage(sLabelSvcName, WM_SETFONT, (WPARAM)cDefaultFont, MAKELPARAM(0, 0));
	SendMessage(sLabelSvcName, WM_SETTEXT, (WPARAM)cDefaultFont, (LPARAM) "Service name:");
		
	iPosLabelY = iPosLabelY + iIncLabelY;
	
	sLabelType = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_RIGHT,
	iPosCol1, iPosLabelY, 105, 20, hwnd, (HMENU) IDC_LABEL_TYPE, vModHandle, NULL);
	if(sLabelType == NULL)
	{
		MessageBox(hwnd, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}	
	SendMessage(sLabelType, WM_SETFONT, (WPARAM)cDefaultFont, MAKELPARAM(0, 0));
	SendMessage(sLabelType, WM_SETTEXT, (WPARAM)cDefaultFont, (LPARAM) "Type:");
		
	iPosLabelY = iPosLabelY + iIncLabelY;
	
	sLabelInteract = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_RIGHT,
	iPosCol1, iPosLabelY, 105, 20, hwnd, (HMENU) IDC_LABEL_INTERACT, vModHandle, NULL);
	if(sLabelInteract == NULL)
	{
		MessageBox(hwnd, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}	
	SendMessage(sLabelInteract, WM_SETFONT, (WPARAM)cDefaultFont, MAKELPARAM(0, 0));
	SendMessage(sLabelInteract, WM_SETTEXT, (WPARAM)cDefaultFont, (LPARAM) "Interact type:");
		
	iPosLabelY = iPosLabelY + iIncLabelY;
	
	sLabelStart = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_RIGHT,
	iPosCol1, iPosLabelY, 105, 20, hwnd, (HMENU) IDC_LABEL_START, vModHandle, NULL);
	if(sLabelStart == NULL)
	{
		MessageBox(hwnd, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}	
	SendMessage(sLabelStart, WM_SETFONT, (WPARAM)cDefaultFont, MAKELPARAM(0, 0));
	SendMessage(sLabelStart, WM_SETTEXT, (WPARAM)cDefaultFont, (LPARAM) "Start Type:");
	
	iPosLabelY = iPosLabelY + iIncLabelY;
	
	sLabelError = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_RIGHT,
	iPosCol1, iPosLabelY, 105, 20, hwnd, (HMENU) IDC_LABEL_ERROR, vModHandle, NULL);
	if(sLabelError == NULL)
	{
		MessageBox(hwnd, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}	
	SendMessage(sLabelError, WM_SETFONT, (WPARAM)cDefaultFont, MAKELPARAM(0, 0));
	SendMessage(sLabelError, WM_SETTEXT, (WPARAM)cDefaultFont, (LPARAM) "Error:");
		
	iPosLabelY = iPosLabelY + iIncLabelY;
	
	sLabelPathBin = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_RIGHT,
	iPosCol1, iPosLabelY, 105, 20, hwnd, (HMENU) IDC_LABEL_PATHBIN, vModHandle, NULL);
	if(sLabelPathBin == NULL)
	{
		MessageBox(hwnd, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}	
	SendMessage(sLabelPathBin, WM_SETFONT, (WPARAM)cDefaultFont, MAKELPARAM(0, 0));
	SendMessage(sLabelPathBin, WM_SETTEXT, (WPARAM)cDefaultFont, (LPARAM) "Binary Path:");
		
	iPosLabelY = 70;
	
	sLabelGroup = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_RIGHT,
	iPosCol3, iPosLabelY, 105, 20, hwnd, (HMENU) IDC_LABEL_GROUP, vModHandle, NULL);
	if(sLabelGroup == NULL)
	{
		MessageBox(hwnd, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}	
	SendMessage(sLabelGroup, WM_SETFONT, (WPARAM)cDefaultFont, MAKELPARAM(0, 0));
	SendMessage(sLabelGroup, WM_SETTEXT, (WPARAM)cDefaultFont, (LPARAM) "Group:");
		
	iPosLabelY = iPosLabelY + iIncLabelY;
	
	sLabelTag = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_RIGHT,
	iPosCol3, iPosLabelY, 105, 20, hwnd, (HMENU) IDC_LABEL_TAG, vModHandle, NULL);
	if(sLabelTag == NULL)
	{
		MessageBox(hwnd, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}	
	SendMessage(sLabelTag, WM_SETFONT, (WPARAM)cDefaultFont, MAKELPARAM(0, 0));
	SendMessage(sLabelTag, WM_SETTEXT, (WPARAM)cDefaultFont, (LPARAM) "Tag:");
	
	iPosLabelY = iPosLabelY + iIncLabelY;
	
	sLabelDepend = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_RIGHT,
	iPosCol3, iPosLabelY, 105, 20, hwnd, (HMENU) IDC_LABEL_DEPEND, vModHandle, NULL);
	if(sLabelDepend == NULL)
	{
		MessageBox(hwnd, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}	
	SendMessage(sLabelDepend, WM_SETFONT, (WPARAM)cDefaultFont, MAKELPARAM(0, 0));
	SendMessage(sLabelDepend, WM_SETTEXT, (WPARAM)cDefaultFont, (LPARAM) "Dependencies:");
	
	iPosLabelY = iPosLabelY + iIncLabelY;
	
	sLabelAccName = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_RIGHT,
	iPosCol3, iPosLabelY, 105, 20, hwnd, (HMENU) IDC_LABEL_ACCNAME, vModHandle, NULL);
	if(sLabelAccName == NULL)
	{
		MessageBox(hwnd, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}	
	SendMessage(sLabelAccName, WM_SETFONT, (WPARAM)cDefaultFont, MAKELPARAM(0, 0));
	SendMessage(sLabelAccName, WM_SETTEXT, (WPARAM)cDefaultFont, (LPARAM) "Account name:");
		
	iPosLabelY = iPosLabelY + iIncLabelY;
	
	sLabelObjName = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_RIGHT,
	iPosCol3, iPosLabelY, 105, 20, hwnd, (HMENU) IDC_LABEL_OBJNAME, vModHandle, NULL);
	if(sLabelObjName == NULL)
	{
		MessageBox(hwnd, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}	
	SendMessage(sLabelObjName, WM_SETFONT, (WPARAM)cDefaultFont, MAKELPARAM(0, 0));
	SendMessage(sLabelObjName, WM_SETTEXT, (WPARAM)cDefaultFont, (LPARAM) "Object name:");
		
	iPosLabelY = iPosLabelY + iIncLabelY;
	
	sLabelDispName = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_RIGHT,
	iPosCol3, iPosLabelY, 105, 20, hwnd, (HMENU) IDC_LABEL_DISPNAME, vModHandle, NULL);
	if(sLabelDispName == NULL)
	{
		MessageBox(hwnd, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}	
	SendMessage(sLabelDispName, WM_SETFONT, (WPARAM)cDefaultFont, MAKELPARAM(0, 0));
	SendMessage(sLabelDispName, WM_SETTEXT, (WPARAM)cDefaultFont, (LPARAM) "Display name:");
		
	iPosLabelY = iPosLabelY + iIncLabelY;
	
	sLabelPW = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_RIGHT,
	iPosCol3, iPosLabelY, 105, 20, hwnd, (HMENU) IDC_LABEL_PW, vModHandle, NULL);
	if(sLabelPW == NULL)
	{
		MessageBox(hwnd, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}	
	SendMessage(sLabelPW, WM_SETFONT, (WPARAM)cDefaultFont, MAKELPARAM(0, 0));
	SendMessage(sLabelPW, WM_SETTEXT, (WPARAM)cDefaultFont, (LPARAM) "Password:");
	}
	//end creating labels

	//creating controls

	//declarations for combo boxes 
	TCHAR cComboOptions[6][15];
	TCHAR A[16];
	int  k = 0; //loop index for combo boxes
	
	//create combo box
	sComboCommand = CreateWindow(WC_COMBOBOX, "",
	CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	iPosCol2, iPosCtrlY, 150, 25, hwnd, (HMENU) IDC_COMBO_COMMAND, vModHandle, NULL);
	if(sComboCommand == NULL)
	{
		MessageBox(hwnd, "Could not create combo box.", "Error", MB_OK | MB_ICONERROR);
	}
	memset(&cComboOptions, 0, sizeof(cComboOptions));
	strcpy(cComboOptions[0], "config");
	strcpy(cComboOptions[1], "create");
	strcpy(cComboOptions[2], "delete");
	strcpy(cComboOptions[3], "query");
	memset(&A, 0, sizeof (A));      
	for(k = 0; k <= 3; k++)
	{
		strcpy(&A[0], (TCHAR*)cComboOptions[k]);
		// Add string to combo box.
		SendMessage(sComboCommand,(UINT) CB_ADDSTRING,(WPARAM) 0, (LPARAM) A); 
	}	
	// Send the CB_SETCURSEL message to display an initial item in the selection field  
	SendMessage(sComboCommand, CB_SETCURSEL, (WPARAM)-1, (LPARAM)0);
	
	iPosCtrlY = iPosCtrlY + iIncCtrlY;
		
	//creating Edit edit box
	sEditSvrName = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
	iPosCol2, iPosCtrlY, 150, 25, hwnd, (HMENU) IDC_EDIT_SVRNAME, vModHandle, NULL);
	if(sEditSvrName == NULL)
	{
		MessageBox(hwnd, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}
	//Adding text to edit box
	SendMessage(sEditSvrName, WM_SETFONT, (WPARAM) cDefaultFont, MAKELPARAM(0, 0));
	SendMessage(sEditSvrName, WM_SETTEXT, (WPARAM) cDefaultFont, (LPARAM) "");
	
	iPosCtrlY = iPosCtrlY + iIncCtrlY;
	
	sEditSvcName = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
	iPosCol2, iPosCtrlY, 150, 25, hwnd, (HMENU) IDC_EDIT_SVCNAME, vModHandle, NULL);
	if(sEditSvcName == NULL)
	{
		MessageBox(hwnd, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(sEditSvcName, WM_SETFONT, (WPARAM) cDefaultFont, MAKELPARAM(0, 0));
	SendMessage(sEditSvcName, WM_SETTEXT, (WPARAM) cDefaultFont, (LPARAM) "");
	
	iPosCtrlY = iPosCtrlY + iIncCtrlY;
	
	sComboType = CreateWindow(WC_COMBOBOX, "",
	CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	iPosCol2, iPosCtrlY, 150, 25, hwnd, (HMENU) IDC_COMBO_TYPE, vModHandle, NULL);
	if(sComboType == NULL)
	{
		MessageBox(hwnd, "Could not create combo box.", "Error", MB_OK | MB_ICONERROR);
	}
	memset(&cComboOptions, 0, sizeof(cComboOptions));
	strcpy(cComboOptions[0], "own");
	strcpy(cComboOptions[1], "share");
	strcpy(cComboOptions[2], "kernal");
	strcpy(cComboOptions[3], "filesys");
	strcpy(cComboOptions[4], "rec");
	strcpy(cComboOptions[5], "interact type");
	memset(&A, 0, sizeof (A));       
	for(k = 0; k <= 5; k += 1)
	{
		strcpy(&A[0], (TCHAR*)cComboOptions[k]);
		// Add string to combo box.
		SendMessage(sComboType,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A); 
	}	 
	SendMessage(sComboType, CB_SETCURSEL, (WPARAM)-1, (LPARAM)0);
		
	iPosCtrlY = iPosCtrlY + iIncCtrlY;
	
	sComboInteract = CreateWindow(WC_COMBOBOX, "",
	CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	iPosCol2, iPosCtrlY, 150, 25, hwnd, (HMENU) IDC_COMBO_INTERACT, vModHandle, NULL);
	if(sComboInteract == NULL)
	{
		MessageBox(hwnd, "Could not create combo box.", "Error", MB_OK | MB_ICONERROR);
	}
	memset(&cComboOptions, 0, sizeof(cComboOptions));
	strcpy(cComboOptions[0], "own");
	strcpy(cComboOptions[1], "share");
	memset(&A, 0, sizeof (A));       
	for(k = 0; k <= 1; k += 1)
	{
		strcpy(&A[0], (TCHAR*)cComboOptions[k]);
		// Add string to combo box.
		SendMessage(sComboInteract,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A); 
	}	
	// Send the CB_SETCURSEL message to display an initial item in the selection field  
	SendMessage(sComboInteract, CB_SETCURSEL, (WPARAM)-1, (LPARAM)0);
		
	iPosCtrlY = iPosCtrlY + iIncCtrlY;
	
	sComboStart = CreateWindow(WC_COMBOBOX, "",
	CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	iPosCol2, iPosCtrlY, 150, 25, hwnd, (HMENU) IDC_COMBO_START, vModHandle, NULL);
	if(sComboStart == NULL)
	{
		MessageBox(hwnd, "Could not create combo box.", "Error", MB_OK | MB_ICONERROR);
	}
	memset(&cComboOptions, 0, sizeof(cComboOptions));
	strcpy(cComboOptions[0], "boot");
	strcpy(cComboOptions[1], "system");
	strcpy(cComboOptions[2], "auto");
	strcpy(cComboOptions[3], "demand");
	strcpy(cComboOptions[4], "disabled");
	strcpy(cComboOptions[5], "delayed-auto");
	memset(&A, 0, sizeof (A));       
	for(k = 0; k <= 5; k += 1)
	{
		strcpy(&A[0], (TCHAR*)cComboOptions[k]);
		// Add string to combo box.
		SendMessage(sComboStart,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A); 
	}  
	SendMessage(sComboStart, CB_SETCURSEL, (WPARAM)-1, (LPARAM)0);
		
	iPosCtrlY = iPosCtrlY + iIncCtrlY;
	
	sComboError = CreateWindow(WC_COMBOBOX, "",
	CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	iPosCol2, iPosCtrlY, 150, 25, hwnd, (HMENU) IDC_COMBO_ERROR, vModHandle, NULL);
	if(sComboError == NULL)
	{
		MessageBox(hwnd, "Could not create combo box.", "Error", MB_OK | MB_ICONERROR);
	}
	memset(&cComboOptions, 0, sizeof(cComboOptions));
	strcpy(cComboOptions[0], "normal");
	strcpy(cComboOptions[1], "severe");
	strcpy(cComboOptions[2], "critical");
	strcpy(cComboOptions[3], "ignore");
	memset(&A, 0, sizeof (A));       
	for(k = 0; k <= 3; k += 1)
	{
		strcpy(&A[0], (TCHAR*)cComboOptions[k]);
		// Add string to combo box.
		SendMessage(sComboError,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A); 
	}	
	// Send the CB_SETCURSEL message to display an initial item in the selection field  
	SendMessage(sComboError, CB_SETCURSEL, (WPARAM)-1, (LPARAM)0);
	
	iPosCtrlY = iPosCtrlY + iIncCtrlY;
	
	sEditPathBin = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
	iPosCol2, iPosCtrlY, 420, 25, hwnd, (HMENU) IDC_EDIT_PATHBIN, vModHandle, NULL);
	if(sEditPathBin == NULL)
	{
		MessageBox(hwnd, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}
	//Adding text to edit box
	SendMessage(sEditPathBin, WM_SETFONT, (WPARAM) cDefaultFont, MAKELPARAM(0, 0));
	SendMessage(sEditPathBin, WM_SETTEXT, (WPARAM) cDefaultFont, (LPARAM) "");

	iPosCtrlY = 65;

	sEditGroup = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
	iPosCol4, iPosCtrlY, 150, 25, hwnd, (HMENU) IDC_EDIT_GROUP, vModHandle, NULL);
	if(sEditGroup == NULL)
	{
		MessageBox(hwnd, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(sEditGroup, WM_SETFONT, (WPARAM) cDefaultFont, MAKELPARAM(0, 0));
	SendMessage(sEditGroup, WM_SETTEXT, (WPARAM) cDefaultFont, (LPARAM) "");
	
	iPosCtrlY = iPosCtrlY + iIncCtrlY;
	
	sComboTag = CreateWindow(WC_COMBOBOX, "",
	CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	iPosCol4, iPosCtrlY, 150, 25, hwnd, (HMENU) IDC_COMBO_TAG, vModHandle, NULL);
	if(sComboError == NULL)
	{
		MessageBox(hwnd, "Could not create combo box.", "Error", MB_OK | MB_ICONERROR);
	}
	memset(&cComboOptions, 0, sizeof(cComboOptions));
	strcpy(cComboOptions[0], "yes");
	strcpy(cComboOptions[1], "no");
	memset(&A, 0, sizeof (A));       
	for(k = 0; k <= 1; k += 1)
	{
		strcpy(&A[0], (TCHAR*)cComboOptions[k]);
		// Add string to combo box.
		SendMessage(sComboTag,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A); 
	}	  
	SendMessage(sComboTag, CB_SETCURSEL, (WPARAM)-1, (LPARAM)0);
	
	iPosCtrlY = iPosCtrlY + iIncCtrlY;
	
	sEditDepend = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
	iPosCol4, iPosCtrlY, 150, 25, hwnd, (HMENU) IDC_EDIT_DEPEND, vModHandle, NULL);
	if(sEditPathBin == NULL)
	{
		MessageBox(hwnd, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(sEditDepend, WM_SETFONT, (WPARAM) cDefaultFont, MAKELPARAM(0, 0));
	SendMessage(sEditDepend, WM_SETTEXT, (WPARAM) cDefaultFont, (LPARAM) "");
	
	iPosCtrlY = iPosCtrlY + iIncCtrlY;
	
	sEditAccName = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
	iPosCol4, iPosCtrlY, 150, 25, hwnd, (HMENU) IDC_EDIT_ACCNAME, vModHandle, NULL);
	if(sEditAccName == NULL)
	{
		MessageBox(hwnd, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(sEditAccName, WM_SETFONT, (WPARAM) cDefaultFont, MAKELPARAM(0, 0));
	SendMessage(sEditAccName, WM_SETTEXT, (WPARAM) cDefaultFont, (LPARAM) "");
	
	iPosCtrlY = iPosCtrlY + iIncCtrlY;
	
	sEditObjName = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
	iPosCol4, iPosCtrlY, 150, 25, hwnd, (HMENU) IDC_EDIT_OBJNAME, vModHandle, NULL);
	if(sEditObjName == NULL)
	{
		MessageBox(hwnd, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}
	//Adding text to edit box
	SendMessage(sEditObjName, WM_SETFONT, (WPARAM) cDefaultFont, MAKELPARAM(0, 0));
	SendMessage(sEditObjName, WM_SETTEXT, (WPARAM) cDefaultFont, (LPARAM) "");

	iPosCtrlY = iPosCtrlY + iIncCtrlY;

	sEditDispName = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
	iPosCol4, iPosCtrlY, 150, 25, hwnd, (HMENU) IDC_EDIT_DISPNAME, vModHandle, NULL);
	if(sEditDispName == NULL)
	{
		MessageBox(hwnd, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}
	//Adding text to edit box
	SendMessage(sEditDispName, WM_SETFONT, (WPARAM) cDefaultFont, MAKELPARAM(0, 0));
	SendMessage(sEditDispName, WM_SETTEXT, (WPARAM) cDefaultFont, (LPARAM) "");
	
	iPosCtrlY = iPosCtrlY + iIncCtrlY;
	
	sEditPW = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
	iPosCol4, iPosCtrlY, 150, 25, hwnd, (HMENU) IDC_EDIT_PW, vModHandle, NULL);
	if(sEditPW == NULL)
	{
		MessageBox(hwnd, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}
	//Adding text to edit box
	SendMessage(sEditPW, WM_SETFONT, (WPARAM) cDefaultFont, MAKELPARAM(0, 0));
	SendMessage(sEditPW, WM_SETTEXT, (WPARAM) cDefaultFont, (LPARAM) "");

	sBtnBrowse = CreateWindowEx(0, "BUTTON", "Browse", WS_CHILD | WS_VISIBLE, //BS_DEFPUSHBUTTON "Enter button"
	548, 275, 60, 25, hwnd, (HMENU) IDC_BTN_BROWSE, vModHandle, NULL);

	sEditDesc = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
	548, 65, 300, 205, hwnd, (HMENU) IDC_EDIT_PW, vModHandle, NULL);
	if(sEditDesc == NULL)
	{
		MessageBox(hwnd, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}
	//Adding text to edit box
	SendMessage(sEditDesc, WM_SETFONT, (WPARAM) cDefaultFont, MAKELPARAM(0, 0));
	SendMessage(sEditDesc, WM_SETTEXT, (WPARAM) cDefaultFont, (LPARAM) "The description to each parameter will appear here.");

	sGrpBoxCMDLine = CreateWindowEx(0, "BUTTON", "Build", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
	5, 320, 850, 70, hwnd, (HMENU) IDC_GRPBOX_CMDLINE, vModHandle, NULL);

	sLabelCMDLine = CreateWindowEx(0, "STATIC", "Command line:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	10, 350, 105, 20, hwnd, (HMENU) IDC_LABEL_CMDLINE, vModHandle, NULL);
	if(sLabelCMDLine == NULL)
	{
		MessageBox(hwnd, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}
	SendMessage(sLabelCMDLine, WM_SETFONT, (WPARAM) cDefaultFont, MAKELPARAM(0, 0));

	sEditCMDLine = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
	120, 345, 665, 25, hwnd, (HMENU) IDC_EDIT_CMDLINE, vModHandle, NULL);
	if(sEditCMDLine == NULL)
	{
		MessageBox(hwnd, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}
	//Adding text to edit box
	SendMessage(sEditCMDLine, WM_SETFONT, (WPARAM) cDefaultFont, MAKELPARAM(0, 0));
	SendMessage(sEditCMDLine, WM_SETTEXT, (WPARAM) cDefaultFont, (LPARAM) "");

	sBtnCMDRun = CreateWindowEx(0, "BUTTON", "Run", WS_CHILD | WS_VISIBLE,
	790, 345, 60, 25, hwnd, (HMENU) IDC_BTN_CMDRUN, vModHandle, NULL);

	sToolBar = CreateWindowEx(0, "ToolbarWindow32", NULL, CCS_ADJUSTABLE | WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hwnd, (HMENU) IDC_MAIN_TOOLBAR, vModHandle, NULL);
	if(sToolBar == NULL)
	{
		MessageBox(hwnd, "Could not create Tool bar.", "Error", MB_OK | MB_ICONERROR);
	}

	// Send the TB_BUTTONSTRUCTSIZE message, which is required for backward compatibility.
	SendMessage(sToolBar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);

	const int iButtonsCount = 3;

	//first you add a list of images to use
	//add a list of buttons
	TBBUTTON tbButtonsToAdd[iButtonsCount]; //Container for three buttons
	TBADDBITMAP tbaBitMap;

	//add the standard bitmaps to the toolbar
	tbaBitMap.hInst = HINST_COMMCTRL;
	tbaBitMap.nID = IDB_STD_SMALL_COLOR;
	
	SendMessage(sToolBar, TB_ADDBITMAP, 0, (LPARAM) &tbaBitMap);
	//add functionality for buttons
	ZeroMemory(tbButtonsToAdd, sizeof(tbButtonsToAdd));
    tbButtonsToAdd[0].iBitmap = STD_FILENEW;
    tbButtonsToAdd[0].fsState = TBSTATE_ENABLED;
    tbButtonsToAdd[0].fsStyle = TBSTYLE_BUTTON;
    tbButtonsToAdd[0].idCommand = IDC_MAIN_TOOLBAR_FILE_NEW;

    tbButtonsToAdd[1].iBitmap = STD_FILEOPEN;
    tbButtonsToAdd[1].fsState = TBSTATE_ENABLED;
    tbButtonsToAdd[1].fsStyle = TBSTYLE_BUTTON;
    tbButtonsToAdd[1].idCommand = IDC_MAIN_TOOLBAR_FILE_OPEN;

    tbButtonsToAdd[2].iBitmap = STD_FILESAVE;
    tbButtonsToAdd[2].fsState = TBSTATE_ENABLED;
    tbButtonsToAdd[2].fsStyle = TBSTYLE_BUTTON;
    tbButtonsToAdd[2].idCommand = IDC_MAIN_TOOLBAR_FILE_SAVEAS;

	// Add buttons.
	SendMessage(sToolBar, TB_ADDBUTTONS, sizeof(tbButtonsToAdd)/sizeof(TBBUTTON), (LPARAM) &tbButtonsToAdd);
	//resize buttons
	SendMessage(sToolBar, TB_AUTOSIZE, 0, 0);
	//show buttons
	ShowWindow(sToolBar, TRUE);
}