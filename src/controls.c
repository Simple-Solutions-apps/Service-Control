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

int CreateControls(HWND sHwndMain)
{
	//declaring controls
	HWND sHwndCtlToolBar;
	HWND sHwndCtlTipInteract;

	HWND sHwndCtlGrpParams;
	HWND sHwndCtlGrpCMDLine;
	HWND sHwndCtlGrpFile;

	HWND sHwndCtlLblCmd;
	HWND sHwndCtlLblSvr;
	HWND sHwndCtlLblSvc;
	HWND sHwndCtlLblType;
	HWND sHwndCtlLblInteract;
	HWND sHwndCtlLblStart;
	HWND sHwndCtlLblErr;
	HWND sHwndCtlLblBin;
	HWND sHwndCtlLblGrp;
	HWND sHwndCtlLblTag;
	HWND sHwndCtlLblDpd;
	HWND sHwndCtlLblAcc;
	HWND sHwndCtlLblObj;
	HWND sHwndCtlLblDisp;
	HWND sHwndCtlLblPw;
	HWND sHwndCtlLblCMDLine;
	HWND sHwndCtlLblQyType;
	HWND sHwndCtlLblState;
	HWND sHwndCtlLblBuf;
	HWND sHwndCtlLblResm;	

	HWND sHwndCtlCmbCmd;
	HWND sHwndCtlCmbType;
	HWND sHwndCtlCmbInteract;
	HWND sHwndCtlCmbStart;
	HWND sHwndCtlCmbErr;
	HWND sHwndCtlCmbTag;
	HWND sHwndCtlCmbQyType;
	HWND sHwndCtlCmbState;

	HWND sHwndCtlEdtDpd;
	HWND sHwndCtlEdtAcc;
	HWND sHwndCtlEdtObj;
	HWND sHwndCtlEdtDisp;
	HWND sHwndCtlEdtPw;
	HWND sHwndCtlEdtDes;
	HWND sHwndCtlEdtReq;
	HWND sHwndCtlEdtSvr;
	HWND sHwndCtlEdtSvc;
	HWND sHwndCtlEdtBin;
	HWND sHwndCtlEdtGrp;
	HWND sHwndCtlEdtCMDLine;
	HWND sHwndCtlEdtFile;
	HWND sHwndCtlEdtBuf;
	HWND sHwndCtlEdtResm;

	HWND sHwndCtlBtnBrowse;
	HWND sHwndCtlBtnRun;

	//declare global font to use
	HFONT sHfontGbl;

	//declare variables and structures for toolbar
	TBBUTTON sButtonsToAdd[TB_BTN_COUNT]; //Container for toolbar buttons
	HIMAGELIST sHImageListToolBar; //custom image list for toolbar
	HBITMAP sHbitmapToolBar;
	int iBitmapIndex;

	//declare variables for combo boxes 
	TCHAR cComboOptions[7][15];
	TCHAR cTempBuff[16];
	int  iLoopIndex = 0;

	//declare this module/executable instance handle
	HMODULE vHmodInst;

	//define tool info for Tool tips
	TOOLINFO sTi = {0};

	//define tool tip text
	char cToolTipText[52] = "Required parameter when interact type is selected\r ";

	//attempt to create global font to use
	sHfontGbl = CreateFont(16, 0, 0, 0, FW_LIGHT, FALSE, 0, 0, 0, 0, 0, 0, 0, "Arial");

	//attempt to create this module instance handle
	vHmodInst = GetModuleHandle(NULL);
	//verify that font to use was created correctly
	if(sHfontGbl == NULL)
	{
		MessageBox(sHwndMain, "Could not create font.", "Error", MB_OK | MB_ICONINFORMATION);
	}

	//begin creating toolbar

	//attempt to create toolbar 
	sHwndCtlToolBar = CreateWindowEx(0, "ToolbarWindow32", NULL,
	CCS_ADJUSTABLE | WS_BORDER | WS_CHILD | WS_VISIBLE | TBSTYLE_FLAT,
	0, 0, 0, 0, sHwndMain, (HMENU) IDC_MAIN_TOOLBAR, vHmodInst, NULL);

	//verify if toolbar was created correctly
	if(sHwndCtlToolBar == NULL)
	{
		MessageBox(sHwndMain, "Could not create toolbar.", "Error", MB_OK | MB_ICONERROR);
		return __LINE__;
	}

	//attempt to create bitmap
	sHbitmapToolBar = (HBITMAP) LoadImage(vHmodInst, MAKEINTRESOURCE(IDB_TBBITMAP_LARGE_COLOR), IMAGE_BITMAP,
	TB_BTN_BITMAP_W, TB_BTN_BITMAP_H, LR_CREATEDIBSECTION /*<- this is important*/);

	//verify if bitmap was created correctly
	if(sHbitmapToolBar == NULL)
	{
		MessageBox(sHwndMain, "Could not create bitmap.", "Error", MB_OK | MB_ICONERROR);
		return __LINE__;
	}

	//attempt to create image list
	sHImageListToolBar = ImageList_Create(TB_BTN_BITMAP_H, TB_BTN_BITMAP_H, ILC_COLOR32,
	(TB_BTN_BITMAP_W / TB_BTN_BITMAP_H), (TB_BTN_BITMAP_W / TB_BTN_BITMAP_H));

	//verify if image list was created correctly
	if(sHImageListToolBar == NULL)
	{
		MessageBox(sHwndMain, "Could not create image list.", "Error", MB_OK | MB_ICONERROR);
		return __LINE__;
	}
	
	//attempt to add bitmap to image list
	iBitmapIndex = ImageList_Add(sHImageListToolBar, sHbitmapToolBar, NULL);

	//verify if bitmap was added to image list correctly
	if(iBitmapIndex == -1)
	{
		MessageBox(sHwndMain, "Could not add bitmap to image list.", "Error", MB_OK | MB_ICONERROR);
		return __LINE__;
	}

	//define functionality for buttons
	ZeroMemory(sButtonsToAdd, sizeof(sButtonsToAdd));

    sButtonsToAdd[0].iBitmap = MAKELONG(0, 0);
    sButtonsToAdd[0].fsState = TBSTATE_ENABLED;
    sButtonsToAdd[0].fsStyle = TBSTYLE_BUTTON;
    sButtonsToAdd[0].idCommand = IDC_BTN_TBNEW;
	sButtonsToAdd[0].iString = (INT_PTR) "New file";

    sButtonsToAdd[1].iBitmap = MAKELONG(1, 0);
    sButtonsToAdd[1].fsState = TBSTATE_ENABLED;
    sButtonsToAdd[1].fsStyle = TBSTYLE_BUTTON;
    sButtonsToAdd[1].idCommand = IDC_BTN_TBOPEN;
	sButtonsToAdd[1].iString = (INT_PTR) "Open file";

	sButtonsToAdd[2].iBitmap = 0;
    sButtonsToAdd[2].fsState = TBSTATE_ENABLED;
    sButtonsToAdd[2].fsStyle = TBSTYLE_SEP;
    sButtonsToAdd[2].idCommand =0;

    sButtonsToAdd[3].iBitmap = MAKELONG(2, 0);
    sButtonsToAdd[3].fsState = TBSTATE_ENABLED;
    sButtonsToAdd[3].fsStyle = TBSTYLE_BUTTON;
    sButtonsToAdd[3].idCommand = IDC_BTN_TBTEXT;
	sButtonsToAdd[3].iString = (INT_PTR) "Save as text";

    sButtonsToAdd[4].iBitmap = MAKELONG(3, 0);
    sButtonsToAdd[4].fsState = TBSTATE_ENABLED;
    sButtonsToAdd[4].fsStyle = TBSTYLE_BUTTON;
    sButtonsToAdd[4].idCommand = IDC_BTN_TBBAT;
	sButtonsToAdd[4].iString = (INT_PTR) "Save as batch";

	sButtonsToAdd[5].iBitmap = 0;
    sButtonsToAdd[5].fsState = TBSTATE_ENABLED;
    sButtonsToAdd[5].fsStyle = TBSTYLE_SEP;
    sButtonsToAdd[5].idCommand =0;

	sButtonsToAdd[6].iBitmap = MAKELONG(4, 0);
    sButtonsToAdd[6].fsState = TBSTATE_ENABLED;
    sButtonsToAdd[6].fsStyle = TBSTYLE_BUTTON;
    sButtonsToAdd[6].idCommand = IDC_BTN_TBSVC;
	sButtonsToAdd[6].iString = (INT_PTR) "Open Services";

	sButtonsToAdd[7].iBitmap = MAKELONG(5, 0);
    sButtonsToAdd[7].fsState = TBSTATE_ENABLED;
    sButtonsToAdd[7].fsStyle = TBSTYLE_BUTTON;
    sButtonsToAdd[7].idCommand = IDC_BTN_TBABOUT;
	sButtonsToAdd[7].iString = (INT_PTR) "About";

	//send messages to toolbar (apply definitions)
	SendMessage(sHwndCtlToolBar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0); //Send the TB_BUTTONSTRUCTSIZE message (for backward compatibility)
	SendMessage(sHwndCtlToolBar, TB_SETIMAGELIST, 0, (LPARAM) sHImageListToolBar); //add bitmap to toolbar
	SendMessage(sHwndCtlToolBar, TB_ADDBUTTONS, TB_BTN_COUNT, (LPARAM) &sButtonsToAdd); //add buttons to toolbar
	SendMessage(sHwndCtlToolBar, TB_AUTOSIZE, 0, 0); //resize buttons on toolbar

	//begin creating group boxes

	//attempt to create group box (Typical going forward)
	sHwndCtlGrpParams = CreateWindowEx(0, "BUTTON", "Parameters", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
	5, 60, 850, 325, sHwndMain, (HMENU) IDC_GRPBOX_PARAMS, vHmodInst, NULL);
	//verify group box was created correctly (Typical going forward)
	if(sHwndCtlGrpParams == NULL)
	{
		MessageBox(sHwndMain, "Could not create group box.", "Error", MB_OK | MB_ICONERROR);
	}
	//attempt to set the default font group box (Typical going forward)
	SendMessage(sHwndCtlGrpParams, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);

	sHwndCtlGrpCMDLine = CreateWindowEx(0, "BUTTON", "Build", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
	5, 390, 850, 70, sHwndMain, (HMENU) IDC_GRPBOX_CMDLINE, vHmodInst, NULL);
	if(sHwndCtlGrpCMDLine == NULL)
	{
		MessageBox(sHwndMain, "Could not create group box.", "Error", MB_OK | MB_ICONERROR);

	}
	SendMessage(sHwndCtlGrpCMDLine, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);

	sHwndCtlGrpFile = CreateWindowEx(0, "BUTTON", "File contents", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
	5, 465, 850, 200, sHwndMain, (HMENU) IDC_GRPBOX_PARAMS, vHmodInst, NULL);
	if(sHwndCtlGrpFile == NULL)
	{
		MessageBox(sHwndMain, "Could not group box.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(sHwndCtlGrpFile, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);

	//begin creating labels

	//attempt to create label (Typical going forward)
	sHwndCtlLblCmd = CreateWindowEx(0, "STATIC", "Command", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	10, 90, 105, 20, sHwndMain, (HMENU) IDC_LABEL_COMMAND, vHmodInst, NULL);	
	//verify label was created correctly (Typical going forward)
	if(sHwndCtlLblCmd == NULL)
	{
		MessageBox(sHwndMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);
	}
	//attempt to set the default font for label  (Typical going forward)
	SendMessage(sHwndCtlLblCmd, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	
	sHwndCtlLblSvr = CreateWindowEx(0, "STATIC", "Server name:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	10, 120, 105, 20, sHwndMain, (HMENU) IDC_LABEL_SVRNAME, vHmodInst, NULL);
	if(sHwndCtlLblSvr == NULL)
	{
		MessageBox(sHwndMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(sHwndCtlLblSvr, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);

	sHwndCtlLblSvc = CreateWindowEx(0, "STATIC", "Service name:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	10, 150, 105, 20, sHwndMain, (HMENU) IDC_LABEL_SVCNAME, vHmodInst, NULL);
	if(sHwndCtlLblSvc == NULL)
	{
		MessageBox(sHwndMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);
	} 
	SendMessage(sHwndCtlLblSvc, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	
	sHwndCtlLblType = CreateWindowEx(0, "STATIC", "Type:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	10, 180, 105, 20, sHwndMain, (HMENU) IDC_LABEL_TYPE, vHmodInst, NULL);
	if(sHwndCtlLblType == NULL)
	{
		MessageBox(sHwndMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	} 
	SendMessage(sHwndCtlLblType, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	
	sHwndCtlLblInteract = CreateWindowEx(0, "STATIC", "Interact type:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	10, 210, 105, 20, sHwndMain, (HMENU) IDC_LABEL_INTERACT, vHmodInst, NULL);
	if(sHwndCtlLblInteract == NULL)
	{
		MessageBox(sHwndMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	} 
	SendMessage(sHwndCtlLblInteract, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	
	sHwndCtlLblStart = CreateWindowEx(0, "STATIC", "Start Type:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	10, 240, 105, 20, sHwndMain, (HMENU) IDC_LABEL_START, vHmodInst, NULL);
	if(sHwndCtlLblStart == NULL)
	{
		MessageBox(sHwndMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	} 
	SendMessage(sHwndCtlLblStart, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	
	sHwndCtlLblErr = CreateWindowEx(0, "STATIC", "Error:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	10, 270, 105, 20, sHwndMain, (HMENU) IDC_LABEL_ERROR, vHmodInst, NULL);
	if(sHwndCtlLblErr == NULL)
	{
		MessageBox(sHwndMain, "Could not create Label Error.", "Error", MB_OK | MB_ICONERROR);

	}
	SendMessage(sHwndCtlLblErr, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	
	sHwndCtlLblBin = CreateWindowEx(0, "STATIC", "Binary Path:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	10, 300, 105, 20, sHwndMain, (HMENU) IDC_LABEL_PATHBIN, vHmodInst, NULL);
	if(sHwndCtlLblBin == NULL)
	{
		MessageBox(sHwndMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}
	SendMessage(sHwndCtlLblBin, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	
	sHwndCtlLblGrp = CreateWindowEx(0, "STATIC", "Group:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	280, 90, 105, 20, sHwndMain, (HMENU) IDC_LABEL_GROUP, vHmodInst, NULL);
	if(sHwndCtlLblGrp == NULL)
	{
		MessageBox(sHwndMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}
	SendMessage(sHwndCtlLblGrp, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	
	sHwndCtlLblTag = CreateWindowEx(0, "STATIC", "Tag:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	280, 120, 105, 20, sHwndMain, (HMENU) IDC_LABEL_TAG, vHmodInst, NULL);
	if(sHwndCtlLblTag == NULL)
	{
		MessageBox(sHwndMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}
	SendMessage(sHwndCtlLblTag, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	
	sHwndCtlLblDpd = CreateWindowEx(0, "STATIC", "Dependencies:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	280, 150, 105, 20, sHwndMain, (HMENU) IDC_LABEL_DEPEND, vHmodInst, NULL);
	if(sHwndCtlLblDpd == NULL)
	{
		MessageBox(sHwndMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}
	SendMessage(sHwndCtlLblDpd, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	
	sHwndCtlLblAcc = CreateWindowEx(0, "STATIC", "Account name:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	280, 180, 105, 20, sHwndMain, (HMENU) IDC_LABEL_ACCNAME, vHmodInst, NULL);
	if(sHwndCtlLblAcc == NULL)
	{
		MessageBox(sHwndMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}
	SendMessage(sHwndCtlLblAcc, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	
	sHwndCtlLblObj = CreateWindowEx(0, "STATIC", "Object name:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	280, 210, 105, 20, sHwndMain, (HMENU) IDC_LABEL_OBJNAME, vHmodInst, NULL);
	if(sHwndCtlLblObj == NULL)
	{
		MessageBox(sHwndMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}
	SendMessage(sHwndCtlLblObj, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	
	sHwndCtlLblDisp = CreateWindowEx(0, "STATIC", "Display name:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	280, 240, 105, 20, sHwndMain, (HMENU) IDC_LABEL_DISPNAME, vHmodInst, NULL);
	if(sHwndCtlLblDisp == NULL)
	{
		MessageBox(sHwndMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}
	SendMessage(sHwndCtlLblDisp, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	
	sHwndCtlLblPw = CreateWindowEx(0, "STATIC", "Password:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	280, 270, 105, 20, sHwndMain, (HMENU) IDC_LABEL_PW, vHmodInst, NULL);
	if(sHwndCtlLblPw == NULL)
	{
		MessageBox(sHwndMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}
	SendMessage(sHwndCtlLblPw, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	
	sHwndCtlLblQyType = CreateWindowEx(0, "STATIC", "Query Type:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	10, 330, 105, 20, sHwndMain, (HMENU) IDC_LABEL_QYTYPE, vHmodInst, NULL);
	if(sHwndCtlLblQyType == NULL)
	{
		MessageBox(sHwndMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}
	SendMessage(sHwndCtlLblQyType, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);

	sHwndCtlLblState = CreateWindowEx(0, "STATIC", "State:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	10, 360, 105, 20, sHwndMain, (HMENU) IDC_LABEL_STATE, vHmodInst, NULL);
	if(sHwndCtlLblState == NULL)
	{
		MessageBox(sHwndMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}
	SendMessage(sHwndCtlLblState, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);

	sHwndCtlLblBuf = CreateWindowEx(0, "STATIC", "Buffer Size:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	280, 330, 105, 20, sHwndMain, (HMENU) IDC_LABEL_BUFF, vHmodInst, NULL);
	if(sHwndCtlLblBuf == NULL)
	{
		MessageBox(sHwndMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}
	SendMessage(sHwndCtlLblBuf, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);

	sHwndCtlLblResm = CreateWindowEx(0, "STATIC", "Resume Index:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	280, 360, 105, 20, sHwndMain, (HMENU) IDC_LABEL_RESUME, vHmodInst, NULL);
	if(sHwndCtlLblResm == NULL)
	{
		MessageBox(sHwndMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}
	SendMessage(sHwndCtlLblResm, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);

	sHwndCtlLblCMDLine = CreateWindowEx(0, "STATIC", "Command line:", WS_CHILD | WS_VISIBLE | SS_RIGHT,
	10, 420, 105, 20, sHwndMain, (HMENU) IDC_LABEL_CMDLINE, vHmodInst, NULL);
	if(sHwndCtlLblCMDLine == NULL)
	{
		MessageBox(sHwndMain, "Could not create Label.", "Error", MB_OK | MB_ICONERROR);

	}
	SendMessage(sHwndCtlLblCMDLine, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);

	//begin creating comboboxes

	//attempt to create combo box (Typical going forward)
	sHwndCtlCmbCmd = CreateWindowEx(0, "ComboBox", NULL,
	CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	120, 85, 150, 25, sHwndMain, (HMENU) IDC_COMBO_COMMAND, vHmodInst, NULL);
	//verify combo box was created correctly (Typical going forward)
	if(sHwndCtlCmbCmd == NULL)
	{
		MessageBox(sHwndMain, "Could not create combo box.", "Error", MB_OK | MB_ICONERROR);
	}
	//attempt to set the default font for combo box  (Typical going forward)
	SendMessage(sHwndCtlCmbCmd, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	//define combo box list options text
	memset(&cComboOptions, 0, sizeof(cComboOptions));
	strcpy(cComboOptions[0], "create");
	strcpy(cComboOptions[1], "config");
	strcpy(cComboOptions[2], "delete");
	strcpy(cComboOptions[3], "query");
	memset(&cTempBuff, 0, sizeof (cTempBuff)); 
	//send message to add each list option text (Typical going forward)   
	for(iLoopIndex = 0; iLoopIndex <= 3; iLoopIndex++)
	{
		strcpy(&cTempBuff[0], (TCHAR*)cComboOptions[iLoopIndex]);

		SendMessage(sHwndCtlCmbCmd,(UINT) CB_ADDSTRING,(WPARAM) 0, (LPARAM) cTempBuff); 
	}
	//send message to select default option (Typical going forward)
	SendMessage(sHwndCtlCmbCmd, CB_SETCURSEL, (WPARAM) 0, (LPARAM)0);

	sHwndCtlCmbType = CreateWindowEx(0, "ComboBox", NULL,
	CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	120, 175, 150, 25, sHwndMain, (HMENU) IDC_COMBO_TYPE, vHmodInst, NULL);
	if(sHwndCtlCmbType == NULL)
	{
		MessageBox(sHwndMain, "Could not create combo box.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(sHwndCtlCmbType, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	memset(&cComboOptions, 0, sizeof(cComboOptions));
	strcpy(cComboOptions[0], "");
	strcpy(cComboOptions[1], "own");
	strcpy(cComboOptions[2], "share");
	strcpy(cComboOptions[3], "kernal");
	strcpy(cComboOptions[4], "filesys");
	strcpy(cComboOptions[5], "rec");
	strcpy(cComboOptions[6], "interact");
	memset(&cTempBuff, 0, sizeof (cTempBuff));
	for(iLoopIndex = 0; iLoopIndex <= 6; iLoopIndex++)
	{
		strcpy(&cTempBuff[0], (TCHAR*) cComboOptions[iLoopIndex]);

		SendMessage(sHwndCtlCmbType,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) cTempBuff); 
	}
	SendMessage(sHwndCtlCmbType, CB_SETCURSEL, (WPARAM) 0, (LPARAM)0);
	
	sHwndCtlCmbInteract = CreateWindowEx(0, "ComboBox", NULL,
	CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	120, 205, 150, 25, sHwndMain, (HMENU) IDC_COMBO_INTERACT, vHmodInst, NULL);
	if(sHwndCtlCmbInteract == NULL)
	{
		MessageBox(sHwndMain, "Could not create combo box.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(sHwndCtlCmbInteract, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	memset(&cComboOptions, 0, sizeof(cComboOptions));
	strcpy(cComboOptions[0], "own");
	strcpy(cComboOptions[1], "share");
	memset(&cTempBuff, 0, sizeof (cTempBuff));
	for(iLoopIndex = 0; iLoopIndex <= 1; iLoopIndex++)
	{
		strcpy(&cTempBuff[0], (TCHAR*) cComboOptions[iLoopIndex]);
		SendMessage(sHwndCtlCmbInteract,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) cTempBuff); 
	} 
	SendMessage(sHwndCtlCmbInteract, CB_SETCURSEL, (WPARAM) -1, (LPARAM)0);

	sHwndCtlCmbStart = CreateWindowEx(0, "ComboBox", NULL,
	CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	120, 235, 150, 25, sHwndMain, (HMENU) IDC_COMBO_START, vHmodInst, NULL);
	if(sHwndCtlCmbStart == NULL)
	{
		MessageBox(sHwndMain, "Could not create combo box.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(sHwndCtlCmbStart, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	memset(&cComboOptions, 0, sizeof(cComboOptions));
	strcpy(cComboOptions[0], "");
	strcpy(cComboOptions[1], "boot");
	strcpy(cComboOptions[2], "system");
	strcpy(cComboOptions[3], "auto");
	strcpy(cComboOptions[4], "demand");
	strcpy(cComboOptions[5], "disabled");
	strcpy(cComboOptions[6], "delayed-auto");
	memset(&cTempBuff, 0, sizeof (cTempBuff));
	for(iLoopIndex = 0; iLoopIndex <= 6; iLoopIndex++)
	{
		strcpy(&cTempBuff[0], (TCHAR*) cComboOptions[iLoopIndex]);
		SendMessage(sHwndCtlCmbStart,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) cTempBuff); 
	}
	SendMessage(sHwndCtlCmbStart, CB_SETCURSEL, (WPARAM) 0, (LPARAM)0);
	
	sHwndCtlCmbErr = CreateWindowEx(0, "ComboBox", NULL,
	CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	120, 265, 150, 25, sHwndMain, (HMENU) IDC_COMBO_ERROR, vHmodInst, NULL);
	if(sHwndCtlCmbErr == NULL)
	{
		MessageBox(sHwndMain, "Could not create combo box.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(sHwndCtlCmbErr, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
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

		SendMessage(sHwndCtlCmbErr,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) cTempBuff); 
	} 
	SendMessage(sHwndCtlCmbErr, CB_SETCURSEL, (WPARAM) 0, (LPARAM)0);

	sHwndCtlCmbTag = CreateWindowEx(0, "ComboBox", NULL,
	CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	390, 115, 150, 25, sHwndMain, (HMENU) IDC_COMBO_TAG, vHmodInst, NULL);
	if(sHwndCtlCmbTag == NULL)
	{
		MessageBox(sHwndMain, "Could not create combo box.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(sHwndCtlCmbTag, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	memset(&cComboOptions, 0, sizeof(cComboOptions));
	strcpy(cComboOptions[0], "");
	strcpy(cComboOptions[1], "yes");
	strcpy(cComboOptions[2], "no");
	memset(&cTempBuff, 0, sizeof (cTempBuff));
	for(iLoopIndex = 0; iLoopIndex <= 2; iLoopIndex++)
	{
		strcpy(&cTempBuff[0], (TCHAR*) cComboOptions[iLoopIndex]);

		SendMessage(sHwndCtlCmbTag,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) cTempBuff); 
	}
	SendMessage(sHwndCtlCmbTag, CB_SETCURSEL, (WPARAM) 0, (LPARAM)0);

	sHwndCtlCmbQyType = CreateWindowEx(0, "ComboBox", NULL,
	CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	120, 325, 150, 25, sHwndMain, (HMENU) IDC_COMBO_QYTYPE, vHmodInst, NULL);
	if(sHwndCtlCmbQyType == NULL)
	{
		MessageBox(sHwndMain, "Could not create combo box.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(sHwndCtlCmbQyType, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	memset(&cComboOptions, 0, sizeof(cComboOptions));
	strcpy(cComboOptions[0], "service");
	strcpy(cComboOptions[1], "driver");
	strcpy(cComboOptions[2], "all");
	memset(&cTempBuff, 0, sizeof (cTempBuff));
	for(iLoopIndex = 0; iLoopIndex <= 2; iLoopIndex++)
	{
		strcpy(&cTempBuff[0], (TCHAR*) cComboOptions[iLoopIndex]);

		SendMessage(sHwndCtlCmbQyType,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) cTempBuff); 
	}
	SendMessage(sHwndCtlCmbQyType, CB_SETCURSEL, (WPARAM) -1, (LPARAM)0);

	sHwndCtlCmbState = CreateWindowEx(0, "ComboBox", NULL,
	CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	120, 355, 150, 25, sHwndMain, (HMENU) IDC_COMBO_STATE, vHmodInst, NULL);
	if(sHwndCtlCmbState == NULL)
	{
		MessageBox(sHwndMain, "Could not create combo box.", "Error", MB_OK | MB_ICONERROR);
	}

	SendMessage(sHwndCtlCmbState, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	memset(&cComboOptions, 0, sizeof(cComboOptions));
	strcpy(cComboOptions[0], "active");
	strcpy(cComboOptions[1], "inactive");
	strcpy(cComboOptions[2], "all");
	memset(&cTempBuff, 0, sizeof (cTempBuff));
	for(iLoopIndex = 0; iLoopIndex <= 2; iLoopIndex++)
	{
		strcpy(&cTempBuff[0], (TCHAR*) cComboOptions[iLoopIndex]);

		SendMessage(sHwndCtlCmbState,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) cTempBuff); 
	}
	SendMessage(sHwndCtlCmbState, CB_SETCURSEL, (WPARAM) -1, (LPARAM)0);

	//begin creating edit boxes
		
	//attempt to create edit box (Typical going forward)
	sHwndCtlEdtSvr = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, ES_LEFT | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	120, 115, 150, 25, sHwndMain, (HMENU) IDC_EDIT_SVRNAME, vHmodInst, NULL);
	//verify edit box was created correctly (Typical going forward)
	if(sHwndCtlEdtSvr == NULL)
	{
		MessageBox(sHwndMain, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(sHwndCtlEdtSvr, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	SendMessage(sHwndCtlEdtSvr, EM_SETLIMITTEXT, (WPARAM) 16, TRUE);
	
	sHwndCtlEdtSvc = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL ,
	120, 145, 150, 25, sHwndMain, (HMENU) IDC_EDIT_SVCNAME, vHmodInst, NULL);
	if(sHwndCtlEdtSvc == NULL)
	{
		MessageBox(sHwndMain, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(sHwndCtlEdtSvc, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	SendMessage(sHwndCtlEdtSvc, EM_SETLIMITTEXT, (WPARAM) 256, TRUE);
	
	sHwndCtlEdtBin = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL ,
	120, 295, 420, 25, sHwndMain, (HMENU) IDC_EDIT_PATHBIN, vHmodInst, NULL);
	if(sHwndCtlEdtBin == NULL)
	{
		MessageBox(sHwndMain, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(sHwndCtlEdtBin, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	SendMessage(sHwndCtlEdtBin, EM_SETLIMITTEXT, (WPARAM) PATH_MAX, TRUE);

	sHwndCtlEdtGrp = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL ,
	390, 85, 150, 25, sHwndMain, (HMENU) IDC_EDIT_GROUP, vHmodInst, NULL);
	if(sHwndCtlEdtGrp == NULL)
	{
		MessageBox(sHwndMain, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(sHwndCtlEdtGrp, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	SendMessage(sHwndCtlEdtGrp, EM_SETLIMITTEXT, (WPARAM) 17, TRUE);
	
	sHwndCtlEdtDpd = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL ,
	390, 145, 150, 25, sHwndMain, (HMENU) IDC_EDIT_DEPEND, vHmodInst, NULL);
	if(sHwndCtlEdtDpd == NULL)
	{
		MessageBox(sHwndMain, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(sHwndCtlEdtDpd, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	SendMessage(sHwndCtlEdtDpd, EM_SETLIMITTEXT, (WPARAM) 179, TRUE);
	
	sHwndCtlEdtAcc = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL ,
	390, 175, 150, 25, sHwndMain, (HMENU) IDC_EDIT_ACCNAME, vHmodInst, NULL);
	if(sHwndCtlEdtAcc == NULL)
	{
		MessageBox(sHwndMain, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(sHwndCtlEdtAcc, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	SendMessage(sHwndCtlEdtAcc, EM_SETLIMITTEXT, (WPARAM) 256, TRUE);
	
	sHwndCtlEdtObj = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL ,
	390, 205, 150, 25, sHwndMain, (HMENU) IDC_EDIT_OBJNAME, vHmodInst, NULL);
	if(sHwndCtlEdtObj == NULL)
	{
		MessageBox(sHwndMain, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(sHwndCtlEdtObj, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	SendMessage(sHwndCtlEdtObj, EM_SETLIMITTEXT, (WPARAM) 256, TRUE);

	sHwndCtlEdtDisp = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL ,
	390, 235, 150, 25, sHwndMain, (HMENU) IDC_EDIT_DISPNAME, vHmodInst, NULL);
	if(sHwndCtlEdtDisp == NULL)
	{
		MessageBox(sHwndMain, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(sHwndCtlEdtDisp, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	SendMessage(sHwndCtlEdtDisp, EM_SETLIMITTEXT, (WPARAM) 256, TRUE);
	
	sHwndCtlEdtPw = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL ,
	390, 265, 150, 25, sHwndMain, (HMENU) IDC_EDIT_PW, vHmodInst, NULL);
	if(sHwndCtlEdtPw == NULL)
	{
		MessageBox(sHwndMain, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(sHwndCtlEdtPw, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	SendMessage(sHwndCtlEdtPw, EM_SETLIMITTEXT, (WPARAM) 16, TRUE);

	sHwndCtlEdtBuf = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_NUMBER,
	390, 325, 150, 25, sHwndMain, (HMENU) IDC_EDIT_BUFF, vHmodInst, NULL);
	if(sHwndCtlEdtBuf == NULL)
	{
		MessageBox(sHwndMain, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(sHwndCtlEdtBuf, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	SendMessage(sHwndCtlEdtBuf, EM_SETLIMITTEXT, (WPARAM) 4, TRUE);

	sHwndCtlEdtResm = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_NUMBER,
	390, 355, 150, 25, sHwndMain, (HMENU) IDC_EDIT_RESUME, vHmodInst, NULL);
	if(sHwndCtlEdtResm == NULL)
	{
		MessageBox(sHwndMain, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(sHwndCtlEdtResm, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	SendMessage(sHwndCtlEdtResm, EM_SETLIMITTEXT, (WPARAM) 2, TRUE);

	sHwndCtlEdtDes = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
	548, 85, 300, 105, sHwndMain, (HMENU) IDC_EDIT_DESC, vHmodInst, NULL);
	if(sHwndCtlEdtDes == NULL)
	{
		MessageBox(sHwndMain, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(sHwndCtlEdtDes, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);

	sHwndCtlEdtReq = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
	548, 195, 300, 95, sHwndMain, (HMENU) IDC_EDIT_REQ, vHmodInst, NULL);
	if(sHwndCtlEdtReq == NULL)
	{
		MessageBox(sHwndMain, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(sHwndCtlEdtReq, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);

	sHwndCtlEdtCMDLine = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
	120, 415, 665, 25, sHwndMain, (HMENU) IDC_EDIT_CMDLINE, vHmodInst, NULL);
	if(sHwndCtlEdtCMDLine == NULL)
	{
		MessageBox(sHwndMain, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(sHwndCtlEdtCMDLine, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);
	SendMessage(sHwndCtlEdtCMDLine, EM_SETLIMITTEXT, (WPARAM) 1499, TRUE);

	sHwndCtlEdtFile = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL | ES_MULTILINE,
	10, 490, 840, 170, sHwndMain, (HMENU) IDC_EDIT_FILE, vHmodInst, NULL);
	if(sHwndCtlEdtFile == NULL)
	{
		MessageBox(sHwndMain, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(sHwndCtlEdtFile, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);

	//begin creating buttons
	
	sHwndCtlBtnBrowse = CreateWindowEx(0, "BUTTON", "Browse", WS_CHILD | WS_VISIBLE, //BS_DEFPUSHBUTTON "Enter button"
	548, 295, 60, 25, sHwndMain, (HMENU) IDC_BTN_BROWSE, vHmodInst, NULL);
	if(sHwndCtlBtnBrowse == NULL)
	{
		MessageBox(sHwndMain, "Could not create button.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(sHwndCtlBtnBrowse, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);

	sHwndCtlBtnRun = CreateWindowEx(0, "BUTTON", "Run", WS_CHILD | WS_VISIBLE,
	790, 415, 60, 25, sHwndMain, (HMENU) IDC_BTN_RUN, vHmodInst, NULL);
	if(sHwndCtlBtnRun == NULL)
	{
		MessageBox(sHwndMain, "Could not create button.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(sHwndCtlBtnRun, WM_SETFONT, (WPARAM) sHfontGbl, TRUE);	

	//begin creating tooltip

	//attempt to create tooltip
	sHwndCtlTipInteract = CreateWindowEx(0, TOOLTIPS_CLASS, NULL,
	WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP | TTS_BALLOON,
	CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, sHwndMain, NULL, vHmodInst, NULL);
	//verify if tooltip was created correctly
	if(sHwndCtlTipInteract == NULL)
	{
		MessageBox(sHwndMain, "Could not create Tool tip.", "Error", MB_OK | MB_ICONERROR);
		return __LINE__;
	}	
	//define tool information structure
	sTi.cbSize = (UINT) sizeof (sTi);
	sTi.uFlags = (UINT) TTF_IDISHWND | TTF_SUBCLASS;
	sTi.hwnd = (HWND) sHwndMain;
	sTi.uId = (UINT_PTR) sHwndCtlCmbInteract;
	sTi.lpszText = (LPTSTR) cToolTipText;
	//send tool tip messages (apply definitions)
	SendMessage(sHwndCtlTipInteract, TTM_ADDTOOL, 0, (LPARAM) &sTi);
	SendMessage(sHwndCtlTipInteract,  TTM_SETMAXTIPWIDTH, 0, (LPARAM) 140);

	//attempt to preset controls
	SendMessage(sHwndMain, WM_COMMAND, (WPARAM) MAKELONG(IDC_COMBO_COMMAND, CBN_SELCHANGE), (LPARAM) sHwndCtlCmbCmd);

	return 0;
}