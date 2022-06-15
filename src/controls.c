/*-------------------------------------------
  Copyright Simple Solutions, 2022
  Revised: 2022/05/30 14:09
-------------------------------------------*/

//standard includes
#include <windows.h>
#include <commctrl.h> 

//custom includes
#include "..\include\controls.h"
#include "..\include\resource.h"

int CreateControls(HWND sHdlWinMain)
{
	//declaring controls
	HWND sToolBar;

	HWND sGrpBoxParams;
	HWND sGrpBoxCMDLine;
	HWND sGrpBoxFile;

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
	HWND sEditFile;

	HWND sBtnBrowse;
	HWND sBtnCMDRun;

	//declare font to use
	HFONT sFontHandle;

	LRESULT iResult;

	//declare variables/structures for toolbar
	TBBUTTON sButtonsToAdd[TB_BTN_COUNT]; //Container for toolbar buttons
	HIMAGELIST sImageList;
	HBITMAP sBitmap;
	int iBitmapIndex;

	//declare variables for combo boxes 
	TCHAR cComboOptions[7][15];
	TCHAR cTempBuff[16];
	int  iLoopIndex = 0; //loop index for combo boxes

	//define X and Y Coordinates for labels and controls
	int iPosLabelY = 90;
	int iIncLabelY = 30;
	int iPosCtrlY = 85;
	int iIncCtrlY = 30;
	int iPosCol1 = 10;
	int iPosCol2 = iPosCol1 + 110;
	int iPosCol3 = iPosCol2 + 160;
	int iPosCol4 = iPosCol3 + 110;

	//declare this module/executable instance handle
	HMODULE vModInstHandle;

	//attempt to create this module instance handle
	vModInstHandle = GetModuleHandle(NULL);
	
	//verify if module instance handle was created correctly
	if(vModInstHandle == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create module instance handle.", "Error", MB_OK | MB_ICONERROR);
		return __LINE__;
	}

	//attempt to create font to use
	sFontHandle = CreateFont(16, 0, 0, 0, FW_LIGHT, FALSE, 0, 0, 0, 0, 0, 0, 0, "Arial");

	//verify that font to use was created correctly
	if(sFontHandle == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create font.", "Error", MB_OK | MB_ICONINFORMATION);
	}

	//attempt to create toolbar 
	sToolBar = CreateWindowEx(0, "ToolbarWindow32", NULL,
	CCS_ADJUSTABLE | WS_BORDER | WS_CHILD | WS_VISIBLE | TBSTYLE_FLAT,
	0, 0, 0, 0, sHdlWinMain, (HMENU) IDC_MAIN_TOOLBAR, vModInstHandle, NULL);

	//verify if toolbar was created correctly
	if(sToolBar == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create toolbar.", "Error", MB_OK | MB_ICONERROR);
		return __LINE__;
	}

	//attempt to create bitmap
	sBitmap = (HBITMAP) LoadImage(vModInstHandle, MAKEINTRESOURCE(IDB_TBBITMAP_LARGE_COLOR), IMAGE_BITMAP,
	TB_BTN_BITMAP_W, TB_BTN_BITMAP_H, LR_CREATEDIBSECTION /*<- this is important*/);

	//verify if bitmap was created correctly
	if(sBitmap == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create bitmap.", "Error", MB_OK | MB_ICONERROR);
		return __LINE__;
	}

	//attempt to create image list
	sImageList = ImageList_Create(TB_BTN_BITMAP_H, TB_BTN_BITMAP_H, ILC_COLOR32,
	(TB_BTN_BITMAP_W / TB_BTN_BITMAP_H), (TB_BTN_BITMAP_W / TB_BTN_BITMAP_H));

	//verify if image list was created correctly
	if(sImageList == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create image list.", "Error", MB_OK | MB_ICONERROR);
		return __LINE__;
	}
	
	//attempt to add bitmap to image list
	iBitmapIndex = ImageList_Add(sImageList, sBitmap, NULL);

	//verify if bitmap was added to image list correctly
	if(iBitmapIndex == -1)
	{
		MessageBox(sHdlWinMain, "Could not add bitmap to image list.", "Error", MB_OK | MB_ICONERROR);
		return __LINE__;
	}
	
	//define functionality for buttons
	ZeroMemory(sButtonsToAdd, sizeof(sButtonsToAdd));

    sButtonsToAdd[0].iBitmap = MAKELONG(0, 0);
    sButtonsToAdd[0].fsState = TBSTATE_ENABLED;
    sButtonsToAdd[0].fsStyle = TBSTYLE_BUTTON;
    sButtonsToAdd[0].idCommand = IDC_MAIN_TOOLBAR_FILE_NEW;
	sButtonsToAdd[0].iString = (INT_PTR) "New file";

    sButtonsToAdd[1].iBitmap = MAKELONG(1, 0);
    sButtonsToAdd[1].fsState = TBSTATE_ENABLED;
    sButtonsToAdd[1].fsStyle = TBSTYLE_BUTTON;
    sButtonsToAdd[1].idCommand = IDC_MAIN_TOOLBAR_FILE_OPEN;
	sButtonsToAdd[1].iString = (INT_PTR) "Open file";

	sButtonsToAdd[2].iBitmap = 0;
    sButtonsToAdd[2].fsState = TBSTATE_ENABLED;
    sButtonsToAdd[2].fsStyle = TBSTYLE_SEP;
    sButtonsToAdd[2].idCommand =0;

    sButtonsToAdd[3].iBitmap = MAKELONG(2, 0);
    sButtonsToAdd[3].fsState = TBSTATE_ENABLED;
    sButtonsToAdd[3].fsStyle = TBSTYLE_BUTTON;
    sButtonsToAdd[3].idCommand = IDC_MAIN_TOOLBAR_FILE_SAVETXT;
	sButtonsToAdd[3].iString = (INT_PTR) "Save as text";

    sButtonsToAdd[4].iBitmap = MAKELONG(3, 0);
    sButtonsToAdd[4].fsState = TBSTATE_ENABLED;
    sButtonsToAdd[4].fsStyle = TBSTYLE_BUTTON;
    sButtonsToAdd[4].idCommand = IDC_MAIN_TOOLBAR_FILE_SAVEBAT;
	sButtonsToAdd[4].iString = (INT_PTR) "Save as batch";

	sButtonsToAdd[5].iBitmap = 0;
    sButtonsToAdd[5].fsState = TBSTATE_ENABLED;
    sButtonsToAdd[5].fsStyle = TBSTYLE_SEP;
    sButtonsToAdd[5].idCommand =0;

	sButtonsToAdd[6].iBitmap = MAKELONG(4, 0);
    sButtonsToAdd[6].fsState = TBSTATE_ENABLED;
    sButtonsToAdd[6].fsStyle = TBSTYLE_BUTTON;
    sButtonsToAdd[6].idCommand = IDC_MAIN_TOOLBAR_SVC_OPEN;
	sButtonsToAdd[6].iString = (INT_PTR) "Open Services";

	sButtonsToAdd[7].iBitmap = MAKELONG(5, 0);
    sButtonsToAdd[7].fsState = TBSTATE_ENABLED;
    sButtonsToAdd[7].fsStyle = TBSTYLE_BUTTON;
    sButtonsToAdd[7].idCommand = IDC_MAIN_TOOLBAR_ABOUT;
	sButtonsToAdd[7].iString = (INT_PTR) "About";

	//send messages to toolbar (apply definitions)
	SendMessage(sToolBar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0); //Send the TB_BUTTONSTRUCTSIZE message (for backward compatibility)
	//SendMessage(sToolBar, CCM_SETVERSION, (WPARAM) 5, 0); //enable multiple image lists (versions <5)
	SendMessage(sToolBar, TB_SETIMAGELIST, 0, (LPARAM) sImageList); //add bitmap to toolbar
	SendMessage(sToolBar, TB_ADDBUTTONS, TB_BTN_COUNT, (LPARAM) &sButtonsToAdd); //add buttons to toolbar
	SendMessage(sToolBar, TB_AUTOSIZE, 0, 0); //resize buttons on toolbar

	//attempt to create group box (Typical going forward)
	sGrpBoxParams = CreateWindowEx(0, "BUTTON", "Parameters", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
	5, 60, 850, 275, sHdlWinMain, (HMENU) IDC_GRPBOX_PARAMS, vModInstHandle, NULL);

	//verify group box was created correctly (Typical going forward)
	if(sGrpBoxParams == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create group box.", "Error", MB_OK | MB_ICONERROR);
	}

	//attempt to set the default font for label 
	SendMessage(sGrpBoxParams, WM_SETFONT, sFontHandle, TRUE);

	//begin creating labels

	//attempt to create label (Typical going forward)
	sLabelCommand = CreateWindowEx(0, "STATIC", "Command", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	iPosCol1, iPosLabelY, 105, 20, sHdlWinMain, (HMENU) IDC_LABEL_COMMAND, vModInstHandle, NULL);
	
	//verify label was created correctly (Typical going forward)
	if(sLabelCommand == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);
	}

	//attempt to set the default font for label  (Typical going forward)
	SendMessage(sLabelCommand, WM_SETFONT, sFontHandle, TRUE);
	
	//increment X and Y coordinates for next control (Typical going forward)
	iPosLabelY = iPosLabelY + iIncLabelY;
	
	sLabelSvrName = CreateWindowEx(0, "STATIC", "Server name:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	iPosCol1, iPosLabelY, 105, 20, sHdlWinMain, (HMENU) IDC_LABEL_SVRNAME, vModInstHandle, NULL);

	if(sLabelSvrName == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);
	}

	SendMessage(sLabelSvrName, WM_SETFONT, sFontHandle, TRUE);
		
	iPosLabelY = iPosLabelY + iIncLabelY;
	
	sLabelSvcName = CreateWindowEx(0, "STATIC", "Service name:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	iPosCol1, iPosLabelY, 105, 20, sHdlWinMain, (HMENU) IDC_LABEL_SVCNAME, vModInstHandle, NULL);

	if(sLabelSvcName == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);
	}
 
	SendMessage(sLabelSvcName, WM_SETFONT, sFontHandle, TRUE);
		
	iPosLabelY = iPosLabelY + iIncLabelY;
	
	sLabelType = CreateWindowEx(0, "STATIC", "Type:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	iPosCol1, iPosLabelY, 105, 20, sHdlWinMain, (HMENU) IDC_LABEL_TYPE, vModInstHandle, NULL);

	if(sLabelType == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}
 
	SendMessage(sLabelType, WM_SETFONT, sFontHandle, TRUE);
		
	iPosLabelY = iPosLabelY + iIncLabelY;
	
	sLabelInteract = CreateWindowEx(0, "STATIC", "Interact type:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	iPosCol1, iPosLabelY, 105, 20, sHdlWinMain, (HMENU) IDC_LABEL_INTERACT, vModInstHandle, NULL);

	if(sLabelInteract == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}
 
	SendMessage(sLabelInteract, WM_SETFONT, sFontHandle, TRUE);
		
	iPosLabelY = iPosLabelY + iIncLabelY;
	
	sLabelStart = CreateWindowEx(0, "STATIC", "Start Type:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	iPosCol1, iPosLabelY, 105, 20, sHdlWinMain, (HMENU) IDC_LABEL_START, vModInstHandle, NULL);

	if(sLabelStart == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}
 
	SendMessage(sLabelStart, WM_SETFONT, sFontHandle, TRUE);
	
	iPosLabelY = iPosLabelY + iIncLabelY;
	
	sLabelError = CreateWindowEx(0, "STATIC", "Error:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	iPosCol1, iPosLabelY, 105, 20, sHdlWinMain, (HMENU) IDC_LABEL_ERROR, vModInstHandle, NULL);

	if(sLabelError == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create Label Error.", "Error", MB_OK | MB_ICONERROR);

	}

	SendMessage(sLabelError, WM_SETFONT, sFontHandle, TRUE);
		
	iPosLabelY = iPosLabelY + iIncLabelY;
	
	sLabelPathBin = CreateWindowEx(0, "STATIC", "Binary Path:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	iPosCol1, iPosLabelY, 105, 20, sHdlWinMain, (HMENU) IDC_LABEL_PATHBIN, vModInstHandle, NULL);

	if(sLabelPathBin == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}

	SendMessage(sLabelPathBin, WM_SETFONT, sFontHandle, TRUE);
		
	iPosLabelY = 90;
	
	sLabelGroup = CreateWindowEx(0, "STATIC", "Group:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	iPosCol3, iPosLabelY, 105, 20, sHdlWinMain, (HMENU) IDC_LABEL_GROUP, vModInstHandle, NULL);

	if(sLabelGroup == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}

	SendMessage(sLabelGroup, WM_SETFONT, sFontHandle, TRUE);
		
	iPosLabelY = iPosLabelY + iIncLabelY;
	
	sLabelTag = CreateWindowEx(0, "STATIC", "Tag:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	iPosCol3, iPosLabelY, 105, 20, sHdlWinMain, (HMENU) IDC_LABEL_TAG, vModInstHandle, NULL);

	if(sLabelTag == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}

	SendMessage(sLabelTag, WM_SETFONT, sFontHandle, TRUE);
	
	iPosLabelY = iPosLabelY + iIncLabelY;
	
	sLabelDepend = CreateWindowEx(0, "STATIC", "Dependencies:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	iPosCol3, iPosLabelY, 105, 20, sHdlWinMain, (HMENU) IDC_LABEL_DEPEND, vModInstHandle, NULL);

	if(sLabelDepend == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}

	SendMessage(sLabelDepend, WM_SETFONT, sFontHandle, TRUE);
	
	iPosLabelY = iPosLabelY + iIncLabelY;
	
	sLabelAccName = CreateWindowEx(0, "STATIC", "Account name:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	iPosCol3, iPosLabelY, 105, 20, sHdlWinMain, (HMENU) IDC_LABEL_ACCNAME, vModInstHandle, NULL);

	if(sLabelAccName == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}

	SendMessage(sLabelAccName, WM_SETFONT, sFontHandle, TRUE);
		
	iPosLabelY = iPosLabelY + iIncLabelY;
	
	sLabelObjName = CreateWindowEx(0, "STATIC", "Object name:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	iPosCol3, iPosLabelY, 105, 20, sHdlWinMain, (HMENU) IDC_LABEL_OBJNAME, vModInstHandle, NULL);

	if(sLabelObjName == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}

	SendMessage(sLabelObjName, WM_SETFONT, sFontHandle, TRUE);
		
	iPosLabelY = iPosLabelY + iIncLabelY;
	
	sLabelDispName = CreateWindowEx(0, "STATIC", "Display name:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	iPosCol3, iPosLabelY, 105, 20, sHdlWinMain, (HMENU) IDC_LABEL_DISPNAME, vModInstHandle, NULL);

	if(sLabelDispName == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}

	SendMessage(sLabelDispName, WM_SETFONT, sFontHandle, TRUE);
		
	iPosLabelY = iPosLabelY + iIncLabelY;
	
	sLabelPW = CreateWindowEx(0, "STATIC", "Password:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	iPosCol3, iPosLabelY, 105, 20, sHdlWinMain, (HMENU) IDC_LABEL_PW, vModInstHandle, NULL);
	if(sLabelPW == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}

	SendMessage(sLabelPW, WM_SETFONT, sFontHandle, TRUE);
	
	//attempt to create combo box (Typical going forward)
	sComboCommand = CreateWindowEx(0, "ComboBox", NULL,
	CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	iPosCol2, iPosCtrlY, 150, 25, sHdlWinMain, (HMENU) IDC_COMBO_COMMAND, vModInstHandle, NULL);

	//verify combo box was created correctly (Typical going forward)
	if(sComboCommand == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create combo box.", "Error", MB_OK | MB_ICONERROR);
	}

	SendMessage(sComboCommand, WM_SETFONT, sFontHandle, TRUE);

	//define combo box list options text
	memset(&cComboOptions, 0, sizeof(cComboOptions));
	strcpy(cComboOptions[0], "create"); //blank/none
	strcpy(cComboOptions[1], "config");
	strcpy(cComboOptions[2], "delete");
	strcpy(cComboOptions[3], "query");
	memset(&cTempBuff, 0, sizeof (cTempBuff)); 

	//send message to add each list option text (Typical going forward)   
	for(iLoopIndex = 0; iLoopIndex <= 3; iLoopIndex++)
	{
		strcpy(&cTempBuff[0], (TCHAR*)cComboOptions[iLoopIndex]);

		SendMessage(sComboCommand,(UINT) CB_ADDSTRING,(WPARAM) 0, (LPARAM) cTempBuff); 
	}

	//send message to select default option (Typical going forward)
	SendMessage(sComboCommand, CB_SETCURSEL, (WPARAM) 0, (LPARAM)0);
	
	iPosCtrlY = iPosCtrlY + iIncCtrlY;
		
	//attempt to create edit box (Typical going forward)
	sEditSvrName = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, ES_LEFT | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	iPosCol2, iPosCtrlY, 150, 25, sHdlWinMain, (HMENU) IDC_EDIT_SVRNAME, vModInstHandle, NULL);

	//verify edit box was created correctly (Typical going forward)
	if(sEditSvrName == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}

	SendMessage(sEditSvrName, WM_SETFONT, sFontHandle, TRUE);
	
	iPosCtrlY = iPosCtrlY + iIncCtrlY;
	
	sEditSvcName = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL ,
	iPosCol2, iPosCtrlY, 150, 25, sHdlWinMain, (HMENU) IDC_EDIT_SVCNAME, vModInstHandle, NULL);

	if(sEditSvcName == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}

	SendMessage(sEditSvcName, WM_SETFONT, sFontHandle, TRUE);
	
	iPosCtrlY = iPosCtrlY + iIncCtrlY;
	
	sComboType = CreateWindowEx(0, "ComboBox", NULL,
	CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	iPosCol2, iPosCtrlY, 150, 25, sHdlWinMain, (HMENU) IDC_COMBO_TYPE, vModInstHandle, NULL);

	if(sComboType == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create combo box.", "Error", MB_OK | MB_ICONERROR);
	}

	SendMessage(sComboType, WM_SETFONT, sFontHandle, TRUE);

	memset(&cComboOptions, 0, sizeof(cComboOptions));
	strcpy(cComboOptions[0], "");
	strcpy(cComboOptions[1], "own");
	strcpy(cComboOptions[2], "share");
	strcpy(cComboOptions[3], "kernal");
	strcpy(cComboOptions[4], "filesys");
	strcpy(cComboOptions[5], "rec");
	strcpy(cComboOptions[6], "interact type");
	memset(&cTempBuff, 0, sizeof (cTempBuff));

	for(iLoopIndex = 0; iLoopIndex <= 6; iLoopIndex++)
	{
		strcpy(&cTempBuff[0], (TCHAR*) cComboOptions[iLoopIndex]);

		SendMessage(sComboType,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) cTempBuff); 
	}

	SendMessage(sComboType, CB_SETCURSEL, (WPARAM) 0, (LPARAM)0);
		
	iPosCtrlY = iPosCtrlY + iIncCtrlY;
	
	sComboInteract = CreateWindowEx(0, "ComboBox", NULL,
	CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	iPosCol2, iPosCtrlY, 150, 25, sHdlWinMain, (HMENU) IDC_COMBO_INTERACT, vModInstHandle, NULL);

	if(sComboInteract == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create combo box.", "Error", MB_OK | MB_ICONERROR);
	}

	SendMessage(sComboInteract, WM_SETFONT, sFontHandle, TRUE);

	memset(&cComboOptions, 0, sizeof(cComboOptions));
	strcpy(cComboOptions[0], "");
	strcpy(cComboOptions[1], "own");
	strcpy(cComboOptions[2], "share");
	memset(&cTempBuff, 0, sizeof (cTempBuff));

	for(iLoopIndex = 0; iLoopIndex <= 2; iLoopIndex++)
	{
		strcpy(&cTempBuff[0], (TCHAR*) cComboOptions[iLoopIndex]);
		SendMessage(sComboInteract,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) cTempBuff); 
	}	
 
	SendMessage(sComboInteract, CB_SETCURSEL, (WPARAM) 0, (LPARAM)0);
		
	iPosCtrlY = iPosCtrlY + iIncCtrlY;
	
	sComboStart = CreateWindowEx(0, "ComboBox", NULL,
	CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	iPosCol2, iPosCtrlY, 150, 25, sHdlWinMain, (HMENU) IDC_COMBO_START, vModInstHandle, NULL);

	if(sComboStart == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create combo box.", "Error", MB_OK | MB_ICONERROR);
	}

	SendMessage(sComboStart, WM_SETFONT, sFontHandle, TRUE);

	memset(&cComboOptions, 0, sizeof(cComboOptions));
	strcpy(cComboOptions[0], "");
	strcpy(cComboOptions[1], "boot");
	strcpy(cComboOptions[2], "system");
	strcpy(cComboOptions[3], "auto");
	strcpy(cComboOptions[4], "demand");
	strcpy(cComboOptions[5], "disabled");
	strcpy(cComboOptions[6], "delayed-auto");
	memset(&cTempBuff, 0, sizeof (cTempBuff));

	for(iLoopIndex = 0; iLoopIndex <= 5; iLoopIndex++)
	{
		strcpy(&cTempBuff[0], (TCHAR*) cComboOptions[iLoopIndex]);
		SendMessage(sComboStart,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) cTempBuff); 
	} 

	SendMessage(sComboStart, CB_SETCURSEL, (WPARAM) 0, (LPARAM)0);
		
	iPosCtrlY = iPosCtrlY + iIncCtrlY;
	
	sComboError = CreateWindowEx(0, "ComboBox", NULL,
	CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	iPosCol2, iPosCtrlY, 150, 25, sHdlWinMain, (HMENU) IDC_COMBO_ERROR, vModInstHandle, NULL);

	if(sComboError == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create combo box.", "Error", MB_OK | MB_ICONERROR);
	}

	SendMessage(sComboError, WM_SETFONT, sFontHandle, TRUE);

	memset(&cComboOptions, 0, sizeof(cComboOptions));
	strcpy(cComboOptions[0], "");
	strcpy(cComboOptions[1], "normal");
	strcpy(cComboOptions[2], "severe");
	strcpy(cComboOptions[3], "critical");
	strcpy(cComboOptions[4], "ignore");
	memset(&cTempBuff, 0, sizeof (cTempBuff));

	for(iLoopIndex = 0; iLoopIndex <= 4; iLoopIndex++)
	{
		strcpy(&cTempBuff[0], (TCHAR*) cComboOptions[iLoopIndex]);

		SendMessage(sComboError,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) cTempBuff); 
	}	
 
	SendMessage(sComboError, CB_SETCURSEL, (WPARAM) 0, (LPARAM)0);
	
	iPosCtrlY = iPosCtrlY + iIncCtrlY;
	
	sEditPathBin = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL ,
	iPosCol2, iPosCtrlY, 420, 25, sHdlWinMain, (HMENU) IDC_EDIT_PATHBIN, vModInstHandle, NULL);

	if(sEditPathBin == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}

	SendMessage(sEditPathBin, WM_SETFONT, sFontHandle, TRUE);

	iPosCtrlY = 85;

	sEditGroup = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL ,
	iPosCol4, iPosCtrlY, 150, 25, sHdlWinMain, (HMENU) IDC_EDIT_GROUP, vModInstHandle, NULL);

	if(sEditGroup == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}

	SendMessage(sEditGroup, WM_SETFONT, sFontHandle, TRUE);
	
	iPosCtrlY = iPosCtrlY + iIncCtrlY;
	
	sComboTag = CreateWindowEx(0, "ComboBox", NULL,
	CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	iPosCol4, iPosCtrlY, 150, 25, sHdlWinMain, (HMENU) IDC_COMBO_TAG, vModInstHandle, NULL);

	if(sComboError == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create combo box.", "Error", MB_OK | MB_ICONERROR);
	}

	SendMessage(sComboError, WM_SETFONT, sFontHandle, TRUE);

	memset(&cComboOptions, 0, sizeof(cComboOptions));
	strcpy(cComboOptions[0], "");
	strcpy(cComboOptions[1], "yes");
	strcpy(cComboOptions[2], "no");
	memset(&cTempBuff, 0, sizeof (cTempBuff));   

	for(iLoopIndex = 0; iLoopIndex <= 2; iLoopIndex++)
	{
		strcpy(&cTempBuff[0], (TCHAR*) cComboOptions[iLoopIndex]);

		SendMessage(sComboTag,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) cTempBuff); 
	}	

	SendMessage(sComboTag, CB_SETCURSEL, (WPARAM) 0, (LPARAM)0);
	
	iPosCtrlY = iPosCtrlY + iIncCtrlY;
	
	sEditDepend = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL ,
	iPosCol4, iPosCtrlY, 150, 25, sHdlWinMain, (HMENU) IDC_EDIT_DEPEND, vModInstHandle, NULL);

	if(sEditDepend == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}

	SendMessage(sEditDepend, WM_SETFONT, sFontHandle, TRUE);
	
	iPosCtrlY = iPosCtrlY + iIncCtrlY;
	
	sEditAccName = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL ,
	iPosCol4, iPosCtrlY, 150, 25, sHdlWinMain, (HMENU) IDC_EDIT_ACCNAME, vModInstHandle, NULL);

	if(sEditAccName == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}

	SendMessage(sEditAccName, WM_SETFONT, sFontHandle, TRUE);
	
	iPosCtrlY = iPosCtrlY + iIncCtrlY;
	
	sEditObjName = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL ,
	iPosCol4, iPosCtrlY, 150, 25, sHdlWinMain, (HMENU) IDC_EDIT_OBJNAME, vModInstHandle, NULL);

	if(sEditObjName == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}

	SendMessage(sEditObjName, WM_SETFONT, sFontHandle, TRUE);

	iPosCtrlY = iPosCtrlY + iIncCtrlY;

	sEditDispName = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL ,
	iPosCol4, iPosCtrlY, 150, 25, sHdlWinMain, (HMENU) IDC_EDIT_DISPNAME, vModInstHandle, NULL);

	if(sEditDispName == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}

	SendMessage(sEditDispName, WM_SETFONT, sFontHandle, TRUE);
	
	iPosCtrlY = iPosCtrlY + iIncCtrlY;
	
	sEditPW = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL ,
	iPosCol4, iPosCtrlY, 150, 25, sHdlWinMain, (HMENU) IDC_EDIT_PW, vModInstHandle, NULL);

	if(sEditPW == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}

	SendMessage(sEditPW, WM_SETFONT, sFontHandle, TRUE);

	sBtnBrowse = CreateWindowEx(0, "BUTTON", "Browse", WS_CHILD | WS_VISIBLE, //BS_DEFPUSHBUTTON "Enter button"
	548, 295, 60, 25, sHdlWinMain, (HMENU) IDC_BTN_BROWSE, vModInstHandle, NULL);

	if(sBtnBrowse == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create button.", "Error", MB_OK | MB_ICONERROR);
	}

	SendMessage(sBtnBrowse, WM_SETFONT, sFontHandle, TRUE);

	sEditDesc = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "The description of each parameter will appear here.", WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
	548, 85, 300, 205, sHdlWinMain, (HMENU) IDC_EDIT_PW, vModInstHandle, NULL);

	if(sEditDesc == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}

	SendMessage(sEditDesc, WM_SETFONT, sFontHandle, TRUE);

	sGrpBoxCMDLine = CreateWindowEx(0, "BUTTON", "Build", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
	5, 340, 850, 70, sHdlWinMain, (HMENU) IDC_GRPBOX_CMDLINE, vModInstHandle, NULL);

	if(sGrpBoxCMDLine == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create group box.", "Error", MB_OK | MB_ICONERROR);

	}

	SendMessage(sGrpBoxCMDLine, WM_SETFONT, sFontHandle, TRUE);

	sLabelCMDLine = CreateWindowEx(0, "STATIC", "Command line:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	10, 370, 105, 20, sHdlWinMain, (HMENU) IDC_LABEL_CMDLINE, vModInstHandle, NULL);

	if(sLabelCMDLine == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}

	SendMessage(sLabelCMDLine, WM_SETFONT, sFontHandle, TRUE);

	sEditCMDLine = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
	120, 365, 665, 25, sHdlWinMain, (HMENU) IDC_EDIT_CMDLINE, vModInstHandle, NULL);

	if(sEditCMDLine == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}

	SendMessage(sEditCMDLine, WM_SETFONT, sFontHandle, TRUE);

	sBtnCMDRun = CreateWindowEx(0, "BUTTON", "Run", WS_CHILD | WS_VISIBLE,
	790, 365, 60, 25, sHdlWinMain, (HMENU) IDC_BTN_CMDRUN, vModInstHandle, NULL);

	if(sBtnCMDRun == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create button.", "Error", MB_OK | MB_ICONERROR);
	}

	SendMessage(sBtnCMDRun, WM_SETFONT, sFontHandle, TRUE);

	sGrpBoxFile = CreateWindowEx(0, "BUTTON", "File contents", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
	5, 415, 850, 250, sHdlWinMain, (HMENU) IDC_GRPBOX_PARAMS, vModInstHandle, NULL);

	if(sGrpBoxFile == NULL)
	{
		MessageBox(sHdlWinMain, "Could not group box.", "Error", MB_OK | MB_ICONERROR);
	}

	SendMessage(sGrpBoxFile, WM_SETFONT, sFontHandle, TRUE);

	sEditFile = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL | ES_MULTILINE,
	10, 440, 840, 220, sHdlWinMain, (HMENU) IDC_EDIT_FILE, vModInstHandle, NULL);

	if(sEditFile == NULL)
	{
		MessageBox(sHdlWinMain, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}

	SendMessage(sEditFile, WM_SETFONT, sFontHandle, TRUE);

	return 0;
}