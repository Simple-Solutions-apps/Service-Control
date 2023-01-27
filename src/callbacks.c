/*-------------------------------------------
  Copyright Simple Solutions, 2022
  Revised: 2022/05/30 09:36
-------------------------------------------*/

//standard includes
#include <windows.h>
#include <commctrl.h>
#include <libgen.h>
#include <Shlobj.h>
#include <stdio.h>

//custom includes
#include "..\include\resource.h"
#include "..\include\controls.h"
#include "..\include\callbacks.h"

//declarations
HMODULE vHmodInst;
EDITBALLOONTIP sTipAcc;
OPENFILENAME sOpenFileName;
LPCWSTR cPathFileSaveText;
LPCWSTR cTempBuff;
LPCWSTR cPathFolderMyDocs;
HANDLE hFileToOpen;
HANDLE hFileToSave;
HRESULT hResult;
BOOL bResult;
int iComboIndex;
int iTextLen;
int iFileModified;
char *cWinTitle;
LPCWSTR cCMDLine;
LPCWSTR cCommand;
LPCWSTR cSvr;
LPCWSTR cSvc;
LPCWSTR cType;
LPCWSTR cInteract;
LPCWSTR cStart;
LPCWSTR cErr;
LPCWSTR cBin;
LPCWSTR cGrp;
LPCWSTR cTag;
LPCWSTR cDpd;
LPCWSTR cAcc;
LPCWSTR cObj;
LPCWSTR cDisp;
LPCWSTR cPw;
LPCWSTR cQyType;
LPCWSTR cState;
LPCWSTR cBuf;
LPCWSTR cResm;
LPCWSTR cRslt;
char *cPathFileSaveBat;
char *cPathFolderUserProfile;
char *cFileName;
char *cContentsResult;
HWND sHwndTbText;
HWND sHwndCtlEdtDes;
HWND sHwndCtlEdtReq;
HWND sHwndCtlEdtSvr;
HWND sHwndCtlEdtSvc;
HWND sHwndCtlEdtGrp;
HWND sHwndCtlEdtBin;
HWND sHwndCtlEdtDpd;
HWND sHwndCtlEdtAcc;
HWND sHwndCtlEdtObj;
HWND sHwndCtlEdtDisp;
HWND sHwndCtlEdtPw;
HWND sHwndCtlEdtBuf;
HWND sHwndCtlEdtResm;
HWND sHwndCtlEdtCMDLine;
HWND sHwndCtlEdtRslt;
HWND sHwndCtlCmbCmd;
HWND sHwndCtlCmbType;
HWND sHwndCtlCmbInteract;
HWND sHwndCtlCmbStart;
HWND sHwndCtlCmbErr;	
HWND sHwndCtlCmbTag;	
HWND sHwndCtlCmbQyType;
HWND sHwndCtlCmbState;
HWND sHwndCtlBtnBrowse;
HWND sHwndCtlBtnRun;
	
//main window callback procedure
LRESULT CALLBACK WndProc(HWND sHwndMain, UINT sMsg, WPARAM wParam, LPARAM lParam)
{	
	switch(sMsg)
	{
		//begin window messages

		case WM_CREATE:

			//define module/executable handle
			vHmodInst = GetModuleHandle(NULL);	

			//verify if module instance handle was created correctly
			if(vHmodInst == NULL)
			{
				MessageBox(sHwndMain, TEXT("Could not create module instance handle."), TEXT("Error"), MB_OK | MB_ICONERROR);
				return FALSE;
			}
			
			//initializations	
			cTempBuff = malloc(400 * sizeof (LPCWSTR));
			cCMDLine = calloc(1500, sizeof (LPCWSTR)); //The maximum command line length for the CreateProcess function is 32767 characters.
			cCommand = calloc(10, sizeof (LPCWSTR));
			cSvr = calloc(17, sizeof (LPCWSTR));
			cSvc = calloc(257, sizeof (LPCWSTR));
			cType = calloc(30, sizeof (LPCWSTR));
			cInteract = calloc(20, sizeof (LPCWSTR));
			cStart = calloc(22, sizeof (LPCWSTR));
			cErr = calloc(20, sizeof (LPCWSTR));
			cBin = calloc(MAX_PATH, sizeof (LPCWSTR));
			cGrp = calloc(80, sizeof (LPCWSTR));
			cTag = calloc(15, sizeof (LPCWSTR));
			cDpd = calloc(190, sizeof (LPCWSTR));
			cAcc = calloc(257, sizeof (LPCWSTR));
			cObj = calloc(267, sizeof (LPCWSTR));
			cDisp = calloc(287, sizeof (LPCWSTR));
			cPw = calloc(27, sizeof (LPCWSTR));
			cQyType = calloc(20, sizeof (LPCWSTR));
			cState = calloc(20, sizeof (LPCWSTR));
			cBuf = calloc(25, sizeof (LPCWSTR));
			cResm = calloc(8, sizeof (LPCWSTR));
			cRslt = calloc(1, sizeof (LPCWSTR));
			cPathFileSaveText = calloc(MAX_PATH, sizeof (LPCWSTR));
			cPathFileSaveBat = calloc(MAX_PATH, sizeof (LPCWSTR));
			cPathFolderMyDocs = calloc(MAX_PATH, sizeof (LPCWSTR));
			cFileName = calloc(50, sizeof (LPCWSTR));
			cContentsResult = calloc(128, sizeof (LPCWSTR));

			//definitions
			sHwndTbText = GetDlgItem(sHwndMain, IDC_BTN_TBTEXT);
			sHwndCtlEdtDes = GetDlgItem(sHwndMain, IDC_EDIT_DESC);
			sHwndCtlEdtReq = GetDlgItem(sHwndMain, IDC_EDIT_REQ);
			sHwndCtlEdtSvr = GetDlgItem(sHwndMain, IDC_EDIT_SVRNAME);
			sHwndCtlEdtSvc = GetDlgItem(sHwndMain, IDC_EDIT_SVCNAME);
			sHwndCtlEdtGrp = GetDlgItem(sHwndMain, IDC_EDIT_GROUP);
			sHwndCtlEdtBin = GetDlgItem(sHwndMain, IDC_EDIT_PATHBIN);
			sHwndCtlEdtDpd = GetDlgItem(sHwndMain, IDC_EDIT_DEPEND);
			sHwndCtlEdtAcc = GetDlgItem(sHwndMain, IDC_EDIT_ACCNAME);
			sHwndCtlEdtObj = GetDlgItem(sHwndMain, IDC_EDIT_OBJNAME);
			sHwndCtlEdtDisp = GetDlgItem(sHwndMain, IDC_EDIT_DISPNAME);
			sHwndCtlEdtPw = GetDlgItem(sHwndMain, IDC_EDIT_PW);
			sHwndCtlEdtBuf = GetDlgItem(sHwndMain, IDC_EDIT_BUFF);
			sHwndCtlEdtResm = GetDlgItem(sHwndMain, IDC_EDIT_RESUME);
			sHwndCtlEdtCMDLine = GetDlgItem(sHwndMain, IDC_EDIT_CMDLINE);
			sHwndCtlEdtRslt = GetDlgItem(sHwndMain, IDC_EDIT_RSLT);
			sHwndCtlCmbCmd = GetDlgItem(sHwndMain, IDC_COMBO_COMMAND);
			sHwndCtlCmbType = GetDlgItem(sHwndMain, IDC_COMBO_TYPE);
			sHwndCtlCmbInteract = GetDlgItem(sHwndMain, IDC_COMBO_INTERACT);
			sHwndCtlCmbStart = GetDlgItem(sHwndMain, IDC_COMBO_START);
			sHwndCtlCmbErr = GetDlgItem(sHwndMain, IDC_COMBO_ERROR);	
			sHwndCtlCmbTag = GetDlgItem(sHwndMain, IDC_COMBO_TAG);	
			sHwndCtlCmbQyType = GetDlgItem(sHwndMain, IDC_COMBO_QYTYPE);
			sHwndCtlCmbState = GetDlgItem(sHwndMain, IDC_COMBO_STATE);
			sHwndCtlBtnBrowse = GetDlgItem(sHwndMain, IDC_BTN_BROWSE);
			sHwndCtlBtnRun = GetDlgItem(sHwndMain, IDC_BTN_RUN);

			//define path defaults
			hResult = SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, SHGFP_TYPE_CURRENT,(LPWSTR) cPathFolderMyDocs);
			if(hResult != S_OK)
			{
				MessageBox(sHwndMain, TEXT("Could not find user profile folder"), TEXT("Error"), MB_OK | MB_ICONERROR);
				return FALSE;
			}						
			wcscpy_s((wchar_t *) cPathFileSaveText, MAX_PATH, (wchar_t *) cPathFolderMyDocs);
			wcsncat((wchar_t *) cPathFileSaveText, TEXT("\\results.txt"), 15);
			wcscpy_s((wchar_t *) cPathFileSaveBat, MAX_PATH, cPathFolderMyDocs);
			wcsncat((wchar_t *) cPathFileSaveBat, TEXT("\\results.bat"), 15);
			//define edit box tooltip structure.
			sTipAcc.cbStruct = sizeof (EDITBALLOONTIP);
			sTipAcc.pszTitle =  TEXT("Account or object name");
			sTipAcc.pszText = TEXT("Either account name or object\nname is allowed but not both");
			sTipAcc.ttiIcon = TTI_INFO;
			//atempt to create controls
			if(CreateControls(sHwndMain) != 0) //function to create all controls. Review controls.h and controls.c
			{
				MessageBox(sHwndMain, TEXT("Could not create controls"), TEXT("Error"), MB_OK | MB_ICONERROR);
				return FALSE;
			}
			//attempt to preset controls			
			//SendMessage(sHwndMain, WM_COMMAND, (WPARAM) WIPE_CONTROLS, 0);
			//SendMessage(sHwndCtlCmbCmd, CB_SETCURSEL, (WPARAM) 0, (LPARAM) 0);
			//SendMessage(sHwndCtlCmbCmd, CBN_SELCHANGE, (WPARAM) 0, (LPARAM) 0);
			break;

		case WM_CLOSE:
			DestroyWindow(sHwndMain);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_CTLCOLORSTATIC:
			SetBkColor((HDC) wParam, RGB(255, 255, 255));
			SetTextColor((HDC) wParam, RGB(0, 0, 0));
			return (LRESULT) GetStockObject(DC_BRUSH);
			break;

		case WM_CTLCOLOREDIT:
			SetBkColor((HDC) wParam, RGB(255, 255, 255));
			SetTextColor((HDC) wParam, RGB(0, 0, 0));
			return (LRESULT) GetStockObject(DC_BRUSH);
			break;

		case WM_CTLCOLORLISTBOX:
			SetBkColor((HDC) wParam, RGB(255, 255, 255));
			SetTextColor((HDC) wParam, RGB(0, 0, 0));
			return (LRESULT) GetStockObject(DC_BRUSH);
			break;

		case WM_COMMAND:
			switch(LOWORD (wParam))
			{	
				//begin toolbar messages

				case IDC_BTN_TBCLEAR:
					SendMessage(sHwndMain, WM_COMMAND, (WPARAM) WIPE_CONTROLS, 0);				
					iTextLen = SendMessage(sHwndCtlEdtRslt, WM_GETTEXTLENGTH, 0, 0);
					if(iTextLen != 0 && MessageBox(sHwndMain, TEXT("Save command results to text file?"), TEXT("Save text file"), MB_YESNO|MB_ICONQUESTION) == IDYES)
					{						
						SendMessage(sHwndMain, WM_COMMAND, (WPARAM) IDC_BTN_TBTEXT, (LPARAM) sHwndTbText);
					}
					//SendMessage(sHwndCtlCmbCmd, CB_SETCURSEL, (WPARAM) 0, (LPARAM) 0);
					//SendMessage(sHwndMain, WM_COMMAND, (WPARAM) MAKELONG(IDC_COMBO_COMMAND, CBN_SELCHANGE), (LPARAM) sHwndCtlCmbCmd);					
					//MessageBox(sHwndMain, TEXT("Controls cleared"), TEXT("Error"), MB_OK | MB_ICONERROR);
					break;

				case IDC_BTN_TBTEXT:
					iTextLen = SendMessage(sHwndCtlEdtRslt, WM_GETTEXTLENGTH, 0, 0);					
					if(iTextLen == 0)
					{	
						MessageBox(sHwndMain, TEXT("There are no results to save."), TEXT("Save results as text"), MB_OK | MB_ICONINFORMATION);					
						break;
					}
					ZeroMemory(&sOpenFileName, sizeof (sOpenFileName));					
					sOpenFileName.lStructSize = sizeof (sOpenFileName);
					sOpenFileName.hwndOwner = sHwndMain;
					sOpenFileName.lpstrFilter = TEXT("Text Files (*.txt)\0*.txt\0\0");
					sOpenFileName.nFilterIndex = 1;
					sOpenFileName.lpstrFile = (LPWSTR) cPathFileSaveText;
					sOpenFileName.nMaxFile = MAX_PATH;
					sOpenFileName.lpstrInitialDir = (LPWSTR) cPathFolderMyDocs;
					sOpenFileName.lpstrTitle = TEXT("Save command results as text file");					
					sOpenFileName.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT; //For saving a file
					sOpenFileName.lpstrDefExt = TEXT("txt");
									
					if(GetSaveFileName(&sOpenFileName) == TRUE) //for saving a file
					{
						/*
						//wcscpy_s((wchar_t *) cFileName, basename(cPathFileSaveText));
						HANDLE hFileToSave;
						hFileToSave = CreateFile(cPathFileSaveText, GENERIC_WRITE, 0, NULL,CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
						if(hFileToSave == INVALID_HANDLE_VALUE)
						{
							MessageBox(sHwndMain, TEXT("Unable to open file for writing."), TEXT("Save results as text"), MB_OK | MB_ICONASTERISK);
							CloseHandle(hFileToSave);
							break;
						}
						cContentsResult = realloc(cContentsResult, (iTextLen + 1) * sizeof(char));
						SendMessage(sHwndCtlEdtRslt, WM_GETTEXT, (WPARAM) (iTextLen + 1), (LPARAM) cContentsResult);
						bResult = WriteFile(hFileToSave, cContentsResult, sizeof(cContentsResult), NULL, NULL);
						if(bResult == FALSE)
						{
							MessageBox(sHwndMain, TEXT("Unable to write to file."), TEXT("Save results as text"), MB_OK | MB_ICONASTERISK);
							CloseHandle(hFileToSave);
							break;
						}
						SendMessage(sHwndMain,  WM_SETTEXT, 0, (LPARAM) strcat(cFileName, " - Service Control"));				
						CloseHandle(hFileToSave);
						*/
					}
					break;

				case IDC_BTN_TBBAT:
					break;

				case IDC_BTN_TBSVC:
					break;

				case IDC_BTN_TBABOUT:
					DialogBox(vHmodInst, MAKEINTRESOURCE(IDD_ABOUT), sHwndMain, (DLGPROC) AboutDlgProc);
					break;

				//begin combo messages

				case IDC_COMBO_COMMAND:
					switch(HIWORD (wParam))
					{
						case CBN_SELCHANGE:							
							iComboIndex = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
							switch(iComboIndex)
							{
								case 0:							
									LoadString(vHmodInst, IDS_COMMAND_CREATE, (LPWSTR) cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									SendMessage(sHwndCtlEdtReq,  WM_SETTEXT, 0, (LPARAM) TEXT("Required parameters:\r\n Service name, Binary Path."));
									SendMessage(sHwndCtlEdtSvr, WM_SETTEXT, (WPARAM) 0, (LPARAM) "");
									SendMessage(sHwndCtlEdtSvc, WM_SETTEXT, (WPARAM) 0, (LPARAM) "");
									SendMessage(sHwndCtlCmbType, CB_SETCURSEL, (WPARAM) 0, (LPARAM) 0);					
									SendMessage(sHwndCtlCmbInteract, CB_SETCURSEL, (WPARAM) 0, (LPARAM) 0);
									SendMessage(sHwndCtlCmbStart, CB_SETCURSEL, (WPARAM) 0, (LPARAM) 0);
									SendMessage(sHwndCtlCmbErr, CB_SETCURSEL, (WPARAM) 0, (LPARAM) 0);
									SendMessage(sHwndCtlEdtBin, WM_SETTEXT, (WPARAM) 0, (LPARAM) "");
									SendMessage(sHwndCtlEdtGrp, WM_SETTEXT, (WPARAM) 0, (LPARAM) "");
									SendMessage(sHwndCtlCmbTag, CB_SETCURSEL, (WPARAM) 0, (LPARAM) 0);
									SendMessage(sHwndCtlEdtDpd, WM_SETTEXT, (WPARAM) 0, (LPARAM) "");
									SendMessage(sHwndCtlEdtAcc, WM_SETTEXT, (WPARAM) 0, (LPARAM) "");
									SendMessage(sHwndCtlEdtObj, WM_SETTEXT, (WPARAM) 0, (LPARAM) "");
									SendMessage(sHwndCtlEdtDisp, WM_SETTEXT, (WPARAM) 0, (LPARAM) "");
									SendMessage(sHwndCtlEdtPw, WM_SETTEXT, (WPARAM) 0, (LPARAM) "");
									EnableWindow(sHwndCtlEdtSvr, TRUE);
									EnableWindow(sHwndCtlEdtSvc, TRUE);
									EnableWindow(sHwndCtlCmbType, TRUE);
									EnableWindow(sHwndCtlCmbInteract, TRUE);
									EnableWindow(sHwndCtlCmbStart, TRUE);
									EnableWindow(sHwndCtlCmbErr, TRUE);
									EnableWindow(sHwndCtlEdtBin, TRUE);
									EnableWindow(sHwndCtlEdtGrp, TRUE);
									EnableWindow(sHwndCtlCmbTag, TRUE);
									EnableWindow(sHwndCtlEdtDpd, TRUE);
									EnableWindow(sHwndCtlEdtAcc, TRUE);
									EnableWindow(sHwndCtlEdtObj, TRUE);
									EnableWindow(sHwndCtlEdtDisp, TRUE);
									EnableWindow(sHwndCtlEdtPw, TRUE);
									EnableWindow(sHwndCtlBtnBrowse, TRUE);														
									wcscpy_s((wchar_t *) cCommand, 10, TEXT(" create"));
									break;

								case 1:
									LoadString(vHmodInst, IDS_COMMAND_CONF, (LPWSTR) cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									SendMessage(sHwndCtlEdtReq,  WM_SETTEXT, 0, (LPARAM) TEXT("Required parameters:\r\n Service name, one other parameter to modify."));
									wcscpy_s((wchar_t *) cCommand, 10, TEXT(" config"));
									SendMessage(sHwndCtlCmbType, CB_ADDSTRING,7,(LPARAM) TEXT("adapt"));
									break;

								case 2:
									/*
									LoadString(vHmodInst, IDS_COMMAND_DELETE, (LPWSTR) cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									SendMessage(sHwndCtlEdtReq,  WM_SETTEXT, 0, (LPARAM) TEXT("Required parameters:\r\n Service name."));
									wcscpy_s((wchar_t *) cCommand, 10, TEXT(" delete"));									
									SendMessage(sHwndCtlCmbType,  CB_SETCURSEL, 0, 0);
									SendMessage(sHwndCtlCmbInteract,  CB_SETCURSEL, -1, 0);
									SendMessage(sHwndCtlCmbStart,  CB_SETCURSEL, 0, 0);
									SendMessage(sHwndCtlCmbErr,  CB_SETCURSEL, 0, 0);
									SendMessage(sHwndCtlCmbTag,  CB_SETCURSEL, 0, 0);
									SendMessage(sHwndCtlEdtBin,  WM_SETTEXT, 0, (LPARAM) TEXT(""));
									SendMessage(sHwndCtlEdtGrp,  WM_SETTEXT, 0, (LPARAM) TEXT(""));
									SendMessage(sHwndCtlEdtDpd,  WM_SETTEXT, 0, (LPARAM) TEXT(""));
									SendMessage(sHwndCtlEdtAcc,  WM_SETTEXT, 0, (LPARAM) TEXT(""));
									SendMessage(sHwndCtlEdtObj,  WM_SETTEXT, 0, (LPARAM) TEXT(""));
									SendMessage(sHwndCtlEdtDisp,  WM_SETTEXT, 0, (LPARAM) TEXT(""));
									SendMessage(sHwndCtlEdtPw,  WM_SETTEXT, 0, (LPARAM) TEXT(""));																											
									EnableWindow(sHwndCtlCmbType, FALSE);
									EnableWindow(sHwndCtlCmbInteract, FALSE);
									EnableWindow(sHwndCtlCmbStart, FALSE);
									EnableWindow(sHwndCtlCmbErr, FALSE);
									EnableWindow(sHwndCtlEdtBin, FALSE);
									EnableWindow(sHwndCtlBtnBrowse, FALSE);
									EnableWindow(sHwndCtlEdtGrp, FALSE);
									EnableWindow(sHwndCtlCmbTag, FALSE);
									EnableWindow(sHwndCtlEdtDpd, FALSE);
									EnableWindow(sHwndCtlEdtAcc, FALSE);
									EnableWindow(sHwndCtlEdtObj, FALSE);
									EnableWindow(sHwndCtlEdtDisp, FALSE);
									EnableWindow(sHwndCtlEdtPw, FALSE);
									wcscpy_s((wchar_t *) cType, 30, TEXT(""));
									wcscpy_s((wchar_t *) cInteract, 20, TEXT(""));
									wcscpy_s((wchar_t *) cStart, 22, TEXT(""));
									wcscpy_s((wchar_t *) cErr, 20, TEXT(""));
									wcscpy_s((wchar_t *) cTag, 15, TEXT(""));
									wcscpy_s((wchar_t *) cBin,  MAX_PATH, TEXT(""));
									wcscpy_s((wchar_t *) cGrp, 80, TEXT(""));
									wcscpy_s((wchar_t *) cDpd, 190, TEXT(""));
									wcscpy_s((wchar_t *) cAcc, 257, TEXT(""));
									wcscpy_s((wchar_t *) cDisp, 287, TEXT(""));
									wcscpy_s((wchar_t *) cPw, 27, TEXT(""));
									*/
									break;

								case 3:
									LoadString(vHmodInst, IDS_COMMAND_QUERY, (LPWSTR) cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									SendMessage(sHwndCtlEdtReq,  WM_SETTEXT, 0, (LPARAM) TEXT("Required parameters:\r\n Service name."));
									wcscpy_s((wchar_t *) cCommand, 10, TEXT(" query"));
									SendMessage(sHwndCtlCmbType, CB_ADDSTRING,0,(LPARAM) "adapt");									
									SendMessage(sHwndCtlCmbStart,  CB_SETCURSEL, 0, 0);
									SendMessage(sHwndCtlCmbErr,  CB_SETCURSEL, 0, 0);
									SendMessage(sHwndCtlCmbTag,  CB_SETCURSEL, 0, 0);
									SendMessage(sHwndCtlEdtBin,  WM_SETTEXT, 0, (LPARAM) TEXT(""));									
									SendMessage(sHwndCtlEdtDpd,  WM_SETTEXT, 0, (LPARAM) TEXT(""));
									SendMessage(sHwndCtlEdtAcc,  WM_SETTEXT, 0, (LPARAM) TEXT(""));
									SendMessage(sHwndCtlEdtObj,  WM_SETTEXT, 0, (LPARAM) TEXT(""));
									SendMessage(sHwndCtlEdtDisp,  WM_SETTEXT, 0, (LPARAM) TEXT(""));
									SendMessage(sHwndCtlEdtPw,  WM_SETTEXT, 0, (LPARAM) TEXT(""));									
									EnableWindow(sHwndCtlCmbStart, FALSE);
									EnableWindow(sHwndCtlCmbErr, FALSE);
									EnableWindow(sHwndCtlEdtBin, FALSE);
									EnableWindow(sHwndCtlBtnBrowse, FALSE);
									EnableWindow(sHwndCtlCmbTag, FALSE);
									EnableWindow(sHwndCtlEdtDpd, FALSE);
									EnableWindow(sHwndCtlEdtAcc, FALSE);
									EnableWindow(sHwndCtlEdtObj, FALSE);
									EnableWindow(sHwndCtlEdtDisp, FALSE);
									EnableWindow(sHwndCtlEdtPw, FALSE);
									EnableWindow(sHwndCtlCmbQyType, TRUE);									
									EnableWindow(sHwndCtlCmbState, TRUE);									
									EnableWindow(sHwndCtlEdtBuf, TRUE);
									EnableWindow(sHwndCtlEdtResm, TRUE);
									SendMessage(sHwndCtlCmbQyType, CB_SETCURSEL, 0, 0);
									SendMessage(sHwndCtlCmbState, CB_SETCURSEL, 0, 0);
									wcscpy_s((wchar_t *) cStart, 22, TEXT(""));
									wcscpy_s((wchar_t *) cErr, 20, TEXT(""));
									wcscpy_s((wchar_t *) cTag, 15, TEXT(""));
									wcscpy_s((wchar_t *) cBin,  MAX_PATH, TEXT(""));
									wcscpy_s((wchar_t *) cDpd, 190, TEXT(""));
									wcscpy_s((wchar_t *) cAcc, 257, TEXT(""));
									wcscpy_s((wchar_t *) cDisp, 287, TEXT(""));
									wcscpy_s((wchar_t *) cPw, 27, TEXT(""));
									wcscpy_s((wchar_t *) cQyType, 20,  TEXT(" type= service"));
									wcscpy_s((wchar_t *) cState, 20, TEXT(" state= active"));
									break;
							}
							SetTextCMDLine(sHwndCtlEdtCMDLine);
							EnableBtnRun(sHwndCtlBtnRun, sHwndCtlCmbCmd);
							break;
					}
					break;

				case IDC_COMBO_TYPE:
					switch(HIWORD (wParam))
					{
						case CBN_SELCHANGE:
							iComboIndex = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
							switch(iComboIndex)
							{
								case 0:
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) TEXT("Exclude this paramater (Type)"));
									SendMessage(sHwndCtlCmbInteract, CB_SETCURSEL, (WPARAM) -1, 0);
									wcscpy_s((wchar_t *) cType, 30, TEXT(""));
									wcscpy_s((wchar_t *) cInteract, 20, TEXT(""));
									EnableWindow(sHwndCtlCmbInteract, FALSE);									
									break;

								case 1:
									LoadString(vHmodInst, IDS_TYPE_OWN, (LPWSTR) cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									SendMessage(sHwndCtlCmbInteract, CB_SETCURSEL, (WPARAM) -1, 0);
									wcscpy_s((wchar_t *) cType, 30, TEXT(" type= own"));
									wcscpy_s((wchar_t *) cInteract, 20, TEXT(""));
									EnableWindow(sHwndCtlCmbInteract, FALSE);									
									break;

								case 2:
									LoadString(vHmodInst, IDS_TYPE_SHARE, (LPWSTR) cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									SendMessage(sHwndCtlCmbInteract, CB_SETCURSEL, (WPARAM) -1, 0);
									wcscpy_s((wchar_t *) cType, 30, TEXT(" type= share"));
									wcscpy_s((wchar_t *) cInteract, 20, TEXT(""));
									EnableWindow(sHwndCtlCmbInteract, FALSE);									
									break;

								case 3:
									LoadString(vHmodInst, IDS_TYPE_KERNEL, (LPWSTR) cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									SendMessage(sHwndCtlCmbInteract, CB_SETCURSEL, (WPARAM) -1, 0);
									wcscpy_s((wchar_t *) cType, 30, TEXT(" type= kernal"));
									wcscpy_s((wchar_t *) cInteract, 20, TEXT(""));
									EnableWindow(sHwndCtlCmbInteract, FALSE);									
									break;

								case 4:
									LoadString(vHmodInst, IDS_TYPE_FILSYS, (LPWSTR) cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									SendMessage(sHwndCtlCmbInteract, CB_SETCURSEL, (WPARAM) -1, 0);
									wcscpy_s((wchar_t *) cType, 30, TEXT(" type= filesys"));
									wcscpy_s((wchar_t *) cInteract, 20, TEXT(""));
									EnableWindow(sHwndCtlCmbInteract, FALSE);									
									break;

								case 5:
									LoadString(vHmodInst, IDS_TYPE_REC, (LPWSTR) cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									SendMessage(sHwndCtlCmbInteract, CB_SETCURSEL, (WPARAM) -1, 0);
									wcscpy_s((wchar_t *) cType, 30, TEXT(" type= rec"));
									wcscpy_s((wchar_t *) cInteract, 20, TEXT(""));
									EnableWindow(sHwndCtlCmbInteract, FALSE);									
									break;

								case 6:
									LoadString(vHmodInst, IDS_TYPE_INTERACT, (LPWSTR) cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									wcscpy_s((wchar_t *) cType, 30, TEXT(" type= interact"));
									wcscpy_s((wchar_t *) cInteract, 20, TEXT(" type= own"));
									EnableWindow(sHwndCtlCmbInteract, TRUE);
									SendMessage(sHwndCtlCmbInteract, CB_SETCURSEL, 0, 0);									
									break;

								case 7:
									LoadString(vHmodInst, IDS_TYPE_ADAPT, (LPWSTR) cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									wcscpy_s((wchar_t *) cType, 30, TEXT(" type= adapt"));
									wcscpy_s((wchar_t *) cInteract, 20, TEXT(""));
									EnableWindow(sHwndCtlCmbInteract, FALSE);
									SendMessage(sHwndCtlCmbInteract, CB_SETCURSEL, (WPARAM) -1, 0);									
									break;
							}
							SetTextCMDLine(sHwndCtlEdtCMDLine);
							EnableBtnRun(sHwndCtlBtnRun, sHwndCtlCmbCmd);							
							break;
					}
					break;

				case IDC_COMBO_INTERACT:
					switch(HIWORD (wParam))
					{
						case CBN_SELCHANGE:
							iComboIndex = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
							switch(iComboIndex)
							{
								case 0:
									LoadString(vHmodInst, IDS_INTERACT_OWN, (LPWSTR) cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									wcscpy_s((wchar_t *) cInteract, 20, TEXT(" type= own"));										
									break;

								case 1:
									LoadString(vHmodInst, IDS_INTERACT_SHARE, (LPWSTR) cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									wcscpy_s((wchar_t *) cInteract, 20, TEXT(" type= share"));									
									break;
							}
							SetTextCMDLine(sHwndCtlEdtCMDLine);
							EnableBtnRun(sHwndCtlBtnRun, sHwndCtlCmbCmd);							
							break;
					}
					break;

				case IDC_COMBO_START:
					switch(HIWORD (wParam))
					{
						case CBN_SELCHANGE:
							iComboIndex = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
							switch(iComboIndex)
							{
								case 0:
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) TEXT("Exclude this paramater (Start)"));
									wcscpy_s((wchar_t *) cStart, 22, TEXT(""));
									break;

								case 1:
									LoadString(vHmodInst, IDS_START_BOOT, (LPWSTR) cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									wcscpy_s((wchar_t *) cStart, 22, TEXT(" start= boot"));
									break;

								case 2:
									LoadString(vHmodInst, IDS_START_SYSTEM, (LPWSTR) cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									wcscpy_s((wchar_t *) cStart, 22, TEXT(" start= system"));
									break;

								case 3:
									LoadString(vHmodInst, IDS_START_AUTO, (LPWSTR) cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									wcscpy_s((wchar_t *) cStart, 22, TEXT(" start= auto"));
									break;

								case 4:
									LoadString(vHmodInst, IDS_START_DEMAND, (LPWSTR) cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									wcscpy_s((wchar_t *) cStart, 22, TEXT(" start= demand"));
									break;

								case 5:
									LoadString(vHmodInst, IDS_START_DISABLED, (LPWSTR) cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									wcscpy_s((wchar_t *) cStart, 22, TEXT(" start= disabled"));
									break;

								case 6:
									LoadString(vHmodInst, IDS_START_DELAYED, (LPWSTR) cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									wcscpy_s((wchar_t *) cStart, 22, TEXT(" start= delayed-auto"));
									break;

							}
							SetTextCMDLine(sHwndCtlEdtCMDLine);
							EnableBtnRun(sHwndCtlBtnRun, sHwndCtlCmbCmd);							
							break;
					}
					break;

				case IDC_COMBO_ERROR:
					switch(HIWORD (wParam))
					{
						case CBN_SELCHANGE:
							iComboIndex = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
							switch(iComboIndex)
							{
								case 0:
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) TEXT("Exclude this paramater (Error)"));
									wcscpy_s((wchar_t *) cErr, 20, TEXT(""));
									break;

								case 1:
									LoadString(vHmodInst, IDS_ERROR_NORMAL, (LPWSTR) cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									wcscpy_s((wchar_t *) cErr, 20, TEXT(" error= normal"));
									break;

								case 2:
									LoadString(vHmodInst, IDS_ERROR_SEVERE, (LPWSTR) cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									wcscpy_s((wchar_t *) cErr, 20, TEXT(" error= severe"));
									break;

								case 3:
									LoadString(vHmodInst, IDS_ERROR_CRITICAL, (LPWSTR) cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									wcscpy_s((wchar_t *) cErr, 20, TEXT(" error= critical"));
									break;

								case 4:
									LoadString(vHmodInst, IDS_ERROR_IGNORE, (LPWSTR) cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									wcscpy_s((wchar_t *) cErr, 20, TEXT(" error= ignore"));
									break;

							}
							SetTextCMDLine(sHwndCtlEdtCMDLine);
							EnableBtnRun(sHwndCtlBtnRun, sHwndCtlCmbCmd);							
							break;
					}
					break;

				case IDC_COMBO_TAG:
					switch(HIWORD (wParam))
					{
						case CBN_SELCHANGE:
							iComboIndex = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
							switch(iComboIndex)
							{
								case 0:
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) TEXT("Exclude this paramater (Tag)"));
									wcscpy_s((wchar_t *) cTag, 2, TEXT(""));
									break;

								case 1:
									LoadString(vHmodInst, IDS_TAG_YES, (LPWSTR) cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									wcscpy_s((wchar_t *) cTag, 10, TEXT(" tag= yes"));
									break;

								case 2:
									LoadString(vHmodInst, IDS_TAG_NO, (LPWSTR) cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									wcscpy_s((wchar_t *) cTag, 9, TEXT(" tag= no"));
									break;

							}
							SetTextCMDLine(sHwndCtlEdtCMDLine);
							EnableBtnRun(sHwndCtlBtnRun, sHwndCtlCmbCmd);							
							break;
					}
					break;

				case IDC_COMBO_QYTYPE:
						switch(HIWORD (wParam))
						{
							case CBN_SELCHANGE:
								iComboIndex = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
								switch(iComboIndex)
								{
									case 0:
										LoadString(vHmodInst, IDS_QYTYPE_SERVICE, (LPWSTR) cTempBuff, 399);
										SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										wcscpy_s((wchar_t *) cQyType, 20,  TEXT(" type= service"));
										break;

									case 1:
										LoadString(vHmodInst, IDS_QYTYPE_DRIVER, (LPWSTR) cTempBuff, 399);
										SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										wcscpy_s((wchar_t *) cQyType, 20,  TEXT(" type= driver"));
										break;

									case 2:
										LoadString(vHmodInst, IDS_QYTYPE_ALL, (LPWSTR) cTempBuff, 399);
										SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										wcscpy_s((wchar_t *) cQyType, 20,  TEXT(" type= all"));
										break;
								}
								SetTextCMDLine(sHwndCtlEdtCMDLine);
								EnableBtnRun(sHwndCtlBtnRun, sHwndCtlCmbCmd);							
								break;
						}
						break;

				case IDC_COMBO_STATE:
						switch(HIWORD (wParam))
						{
							case CBN_SELCHANGE:
								iComboIndex = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
								switch(iComboIndex)
								{
									case 0:
										LoadString(vHmodInst, IDS_STATE_ACTIVE, (LPWSTR) cTempBuff, 399);
										SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										wcscpy_s((wchar_t *) cState, 20, TEXT(" state= active"));
										break;

									case 1:
										LoadString(vHmodInst, IDS_STATE_INACTIVE, (LPWSTR) cTempBuff, 399);
										SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										wcscpy_s((wchar_t *) cState, 20, TEXT(" state= inactive"));
										break;

									case 2:
										LoadString(vHmodInst, IDS_STATE_ALL, (LPWSTR) cTempBuff, 399);
										SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										wcscpy_s((wchar_t *) cState, 20, TEXT(" state= all"));
										break;

								}
								SetTextCMDLine(sHwndCtlEdtCMDLine);
								EnableBtnRun(sHwndCtlBtnRun, sHwndCtlCmbCmd);							
								break;
						}
						break;
				
				//begin edit messages

				case IDC_EDIT_SVRNAME:
					switch(HIWORD (wParam))
					{
						case EN_SETFOCUS:
							LoadString(vHmodInst, IDS_SVRNAME, (LPWSTR) cTempBuff, 399);
							SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
							break;

						case EN_CHANGE:
							SendMessage(sHwndCtlEdtSvr, WM_GETTEXT, (WPARAM) 400,(LPARAM) cTempBuff);
							if(strcmp((char *) cTempBuff, "") != 0)
							{								
								wcscpy_s((wchar_t *) cSvr, 17, TEXT(" "));
								wcsncat((wchar_t *) cSvr, (wchar_t *) cTempBuff, 15);								
							}
							else
							{
								wcscpy_s((wchar_t *) cSvr, 17, TEXT(""));
							}
							SetTextCMDLine(sHwndCtlEdtCMDLine);
							EnableBtnRun(sHwndCtlBtnRun, sHwndCtlCmbCmd);								
							break;
					}
					break;

				case IDC_EDIT_SVCNAME:
					switch(HIWORD (wParam))
					{
						case EN_SETFOCUS:
							LoadString(vHmodInst, IDS_SVCNAME, (LPWSTR) cTempBuff, 399);
							SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);							
							break;

						case EN_CHANGE:
							SendMessage(sHwndCtlEdtSvc, WM_GETTEXT, (WPARAM) 400,(LPARAM) cTempBuff);
							if(strcmp((char *) cTempBuff, "") != 0)
							{
								wcscpy_s((wchar_t *) cSvc, 257, TEXT(" "));
								wcsncat((wchar_t *) cSvc, (wchar_t *) cTempBuff, 15);								
							}
							else
							{
								wcscpy_s((wchar_t *) cSvc, 257, TEXT(""));
							}
							SetTextCMDLine(sHwndCtlEdtCMDLine);
							EnableBtnRun(sHwndCtlBtnRun, sHwndCtlCmbCmd);								
							break;
					}
					break;				

				case IDC_EDIT_PATHBIN:
					switch(HIWORD (wParam))
					{
						case EN_SETFOCUS:
							LoadString(vHmodInst, IDS_PATHBIN, (LPWSTR) cTempBuff, 399);
							SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);								
							break;

						case  EN_CHANGE:
						SendMessage(sHwndCtlEdtBin , WM_GETTEXT, (WPARAM) 400,(LPARAM) cTempBuff);
						if(strcmp((char *) cTempBuff, "") != 0)
						{
							wcscpy_s((wchar_t *) cBin,  MAX_PATH, TEXT(" binpath= \""));
							wcsncat((wchar_t *) cBin, (wchar_t *) cTempBuff, MAX_PATH);
							wcsncat((wchar_t *) cBin, TEXT("\""), 2);								
						}
						else
						{
							wcscpy_s((wchar_t *) cBin,  MAX_PATH, TEXT(""));
						}
						SetTextCMDLine(sHwndCtlEdtCMDLine);
						EnableBtnRun(sHwndCtlBtnRun, sHwndCtlCmbCmd);								
						break;							
					}
					break;

				case IDC_EDIT_GROUP:
					switch(HIWORD (wParam))
					{
						case EN_SETFOCUS:
							LoadString(vHmodInst, IDS_GROUP, (LPWSTR) cTempBuff, 399);
							SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);								
							break;
						
						case  EN_CHANGE:
						SendMessage(sHwndCtlEdtGrp, WM_GETTEXT, (WPARAM) 400,(LPARAM) cTempBuff);
						if(strcmp((char *) cTempBuff, "") != 0)
						{
							wcscpy_s((wchar_t *) cGrp, 80, TEXT(" group= "));
							wcsncat((wchar_t *) cGrp, (wchar_t *) cTempBuff, 15);									
						}
						else
						{
							wcscpy_s((wchar_t *) cGrp, 80, TEXT(""));
						}
						SetTextCMDLine(sHwndCtlEdtCMDLine);
						EnableBtnRun(sHwndCtlBtnRun, sHwndCtlCmbCmd);								
						break;
					}
					break;

				case IDC_EDIT_DEPEND:
					switch(HIWORD (wParam))
					{
						case EN_SETFOCUS:
							LoadString(vHmodInst, IDS_DEPEND, (LPWSTR) cTempBuff, 399);
							SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);								
							break;

						case  EN_CHANGE:
							SendMessage(sHwndCtlEdtDpd, WM_GETTEXT, (WPARAM) 400,(LPARAM) cTempBuff);
							if(strcmp((char *) cTempBuff, "") != 0)
							{
								wcscpy_s((wchar_t *) cDpd, 190, TEXT(" depend= "));
								wcsncat((wchar_t *) cDpd, (wchar_t *) cTempBuff, 15);									
							}
							else
							{
								wcscpy_s((wchar_t *) cDpd, 190, TEXT(""));
							}
							SetTextCMDLine(sHwndCtlEdtCMDLine);
							EnableBtnRun(sHwndCtlBtnRun, sHwndCtlCmbCmd);
							break;
					}
					break;

				case IDC_EDIT_ACCNAME:
					switch(HIWORD (wParam))
					{
						case EN_SETFOCUS:
							LoadString(vHmodInst, IDS_ACCNAME, (LPWSTR) cTempBuff, 399);
							SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
							SendMessage(sHwndCtlEdtAcc,  EM_SHOWBALLOONTIP, 0, (LPARAM) &sTipAcc);								
							break;

						case EN_CHANGE:
							if(SendMessage(sHwndCtlEdtAcc,  WM_GETTEXTLENGTH, 0, 0) > 0)
							{
								SendMessage(sHwndCtlEdtObj,  WM_SETTEXT, 0, (LPARAM) "");
								EnableWindow(sHwndCtlEdtObj, FALSE);
								EnableWindow(sHwndCtlEdtPw, TRUE);
							}
							else
							{
								EnableWindow(sHwndCtlEdtObj, TRUE);
								EnableWindow(sHwndCtlEdtPw, FALSE);
							}
							SendMessage(sHwndCtlEdtAcc, WM_GETTEXT, (WPARAM) 400,(LPARAM) cTempBuff);
							if(strcmp((char *) cTempBuff, "") != 0)
							{
								wcscpy_s((wchar_t *) cAcc, 257, TEXT(" obj= "));
								wcsncat((wchar_t *) cAcc,(wchar_t *) cTempBuff, 15);									
							}
							else
							{
								wcscpy_s((wchar_t *) cAcc, 257, TEXT(""));
							}
							SetTextCMDLine(sHwndCtlEdtCMDLine);
							EnableBtnRun(sHwndCtlBtnRun, sHwndCtlCmbCmd);								
							break;

						case EN_KILLFOCUS:
							if(SendMessage(sHwndCtlEdtAcc,  WM_GETTEXTLENGTH, 0, 0) <= 0)
							{
								SendMessage(sHwndCtlEdtPw,  WM_SETTEXT, 0, (LPARAM) TEXT(""));
								EnableWindow(sHwndCtlEdtPw, FALSE);
								wcscpy_s((wchar_t *) cPw, 27, TEXT(""));
							}
							SetTextCMDLine(sHwndCtlEdtCMDLine);
							EnableBtnRun(sHwndCtlBtnRun, sHwndCtlCmbCmd);
							break;

					}
					break;

				case IDC_EDIT_OBJNAME:
					switch(HIWORD (wParam))
					{
						case EN_SETFOCUS:
							LoadString(vHmodInst, IDS_OBJNAME, (LPWSTR) cTempBuff, 399);
							SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
							SendMessage(sHwndCtlEdtObj,  EM_SHOWBALLOONTIP, 0, (LPARAM) &sTipAcc);								
							break;

						case EN_CHANGE:
							if(SendMessage(sHwndCtlEdtObj,  WM_GETTEXTLENGTH, 0, 0) > 0)
							{
								SendMessage(sHwndCtlEdtAcc,  WM_SETTEXT, 0, (LPARAM) TEXT(""));
								EnableWindow(sHwndCtlEdtAcc, FALSE);
								EnableWindow(sHwndCtlEdtPw, TRUE);
							}
							else
							{
								EnableWindow(sHwndCtlEdtAcc, TRUE);
								EnableWindow(sHwndCtlEdtPw, FALSE);
							}
							SendMessage(sHwndCtlEdtObj, WM_GETTEXT, (WPARAM) 400,(LPARAM) cTempBuff);
							if(strcmp((char *) cTempBuff, "") != 0)
							{
								wcscpy_s((wchar_t *) cAcc, 257, TEXT(" obj= "));
								wcsncat((wchar_t *) cAcc, (wchar_t *) cTempBuff, 15);									
							}
							else
							{
								wcscpy_s((wchar_t *) cAcc, 257, TEXT(""));
							}								
							SetTextCMDLine(sHwndCtlEdtCMDLine);
							EnableBtnRun(sHwndCtlBtnRun, sHwndCtlCmbCmd);
							break;

						case EN_KILLFOCUS:
							if(SendMessage(sHwndCtlEdtObj,  WM_GETTEXTLENGTH, 0, 0) <= 0)
							{
								SendMessage(sHwndCtlEdtPw,  WM_SETTEXT, 0, (LPARAM) TEXT(""));
								EnableWindow(sHwndCtlEdtPw, FALSE);
								wcscpy_s((wchar_t *) cPw, 27, TEXT(""));
							}
							SetTextCMDLine(sHwndCtlEdtCMDLine);
							EnableBtnRun(sHwndCtlBtnRun, sHwndCtlCmbCmd);
							break;
					}
					break;

				case IDC_EDIT_DISPNAME:
					switch(HIWORD (wParam))
					{
						case EN_SETFOCUS:
							LoadString(vHmodInst, IDS_DISPNAME, (LPWSTR) cTempBuff, 399);
							SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);								
							break;

						case EN_CHANGE:
							SendMessage(sHwndCtlEdtDisp, WM_GETTEXT, (WPARAM) 400,(LPARAM) cTempBuff);
							if(strcmp((char *) cTempBuff, "") != 0)
							{
								wcscpy_s((wchar_t *) cDisp, 287, TEXT(" displayname= "));
								wcsncat((wchar_t *) cDisp, (wchar_t *) cTempBuff, 15);									
							}
							else
							{
								wcscpy_s((wchar_t *) cDisp, 287, TEXT(""));
							}
							SetTextCMDLine(sHwndCtlEdtCMDLine);
							EnableBtnRun(sHwndCtlBtnRun, sHwndCtlCmbCmd);
							break;
					}
					break;

				case IDC_EDIT_PW:
					switch(HIWORD (wParam))
					{
						case EN_SETFOCUS:
							LoadString(vHmodInst, IDS_PW, (LPWSTR) cTempBuff, 399);
							SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);								
							break;

						case EN_CHANGE:
							SendMessage(sHwndCtlEdtPw, WM_GETTEXT, (WPARAM) 400,(LPARAM) cTempBuff);
							if(strcmp((char *) cTempBuff, "") != 0)
							{
								wcscpy_s((wchar_t *) cPw, 27, TEXT(" password= "));
								wcsncat((wchar_t *) cPw, (wchar_t *) cTempBuff, 15);									
							}
							else
							{
								wcscpy_s((wchar_t *) cPw, 27, TEXT(""));
							}
							SetTextCMDLine(sHwndCtlEdtCMDLine);
							EnableBtnRun(sHwndCtlBtnRun, sHwndCtlCmbCmd);
							break;
					}
					break;

				case IDC_EDIT_CMDLINE:
					switch(HIWORD (wParam))
					{
						case EN_SETFOCUS:
							LoadString(vHmodInst, IDS_CMDLINE, (LPWSTR) cTempBuff, 399);
							SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);								
							break;

						case EN_CHANGE:
							SendMessage(sHwndCtlEdtCMDLine, WM_GETTEXT, (WPARAM) 400,(LPARAM) cTempBuff);
							if(strcmp((char *) cTempBuff, "") != 0)
							{
								wcscpy_s((wchar_t *) cCMDLine, 1500, cTempBuff);									
							}
							break;
					}
					break;

				case IDC_EDIT_BUFF:
						switch(HIWORD (wParam))
						{
							case EN_SETFOCUS:
								LoadString(vHmodInst, IDS_BUFF, (LPWSTR) cTempBuff, 399);
								SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);								
								break;

							case EN_CHANGE:
								SendMessage(sHwndCtlEdtBuf, WM_GETTEXT, (WPARAM) 400,(LPARAM) cTempBuff);
								if(strcmp((char *) cTempBuff, "") != 0)
								{
									wcscpy_s((wchar_t *) cBuf, 25, TEXT(" bufsize= "));
									wcsncat((wchar_t *) cBuf, (wchar_t *) cTempBuff, 15);									
								}
								else
								{
									wcscpy_s((wchar_t *) cBuf, 25, TEXT(""));
								}
								SetTextCMDLine(sHwndCtlEdtCMDLine);
								EnableBtnRun(sHwndCtlBtnRun, sHwndCtlCmbCmd);
								break;
						}
						break;

				case IDC_EDIT_RESUME:
						switch(HIWORD (wParam))
						{
							case EN_SETFOCUS:
								LoadString(vHmodInst, IDS_RESUME, (LPWSTR) cTempBuff, 399);
								SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);								
								break;

							case EN_CHANGE:
								SendMessage(sHwndCtlEdtResm, WM_GETTEXT, (WPARAM) 400,(LPARAM) cTempBuff);
								if(strcmp((char *) cTempBuff, "") != 0)
								{
									wcscpy_s((wchar_t *) cResm, 8, TEXT(" ri= "));
									wcsncat((wchar_t *) cResm, (wchar_t *) cTempBuff, 15);								
								}
								else
								{
									wcscpy_s((wchar_t *) cResm, 8, TEXT(""));
								}
								SetTextCMDLine(sHwndCtlEdtCMDLine);
								EnableBtnRun(sHwndCtlBtnRun, sHwndCtlCmbCmd);
								break;							
						}
						break;

				case IDC_EDIT_RSLT:
					switch(HIWORD (wParam))
					{
						case EN_SETFOCUS:							
							//SendMessage(sHwndCtlEdtRslt,  WM_SETTEXT, 0, (LPARAM) "File contents.");								
							break;

						case EN_CHANGE:
							SendMessage(sHwndCtlEdtRslt, WM_GETTEXT, (WPARAM) 400,(LPARAM) cTempBuff);
							if(strcmp((char *) cTempBuff, "") != 0)
							{
								iFileModified = 0;
								//SendMessage(sHwndCtlEdtRslt, WM_SETTEXT, 0,(LPARAM) cTempBuff);									
							}
							else
							{
								iFileModified = 1;
							}
							break;
					}
					break;

				//begin button messages 

				case IDC_BTN_BROWSE:
					ZeroMemory(&sOpenFileName, sizeof (sOpenFileName));
					wcscpy_s((wchar_t *) cBin, 8, TEXT(""));
					sOpenFileName.lStructSize = sizeof (sOpenFileName);
					sOpenFileName.hwndOwner = sHwndMain;					
					sOpenFileName.lpstrFilter = TEXT("Executable Files (*.exe)\0*.exe\0");					
					sOpenFileName.nFilterIndex = 1;
					sOpenFileName.lpstrFile = (LPWSTR) cBin;
					sOpenFileName.nMaxFile = MAX_PATH;
					sOpenFileName.lpstrFileTitle = NULL;
					sOpenFileName.nMaxFileTitle = 0;
					sOpenFileName.lpstrTitle = TEXT("Select executable file");
					sOpenFileName.lpstrInitialDir = TEXT("C:\\Windows\\System32");
					sOpenFileName.nFileExtension = 0;
					sOpenFileName.lpstrDefExt = TEXT("exe");				
					//For opening a file
					sOpenFileName.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;					
					//For saving a file
					//sOpenFileName.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;					
					if(GetOpenFileName(&sOpenFileName) == TRUE) //for opening a file
					//if(GetSaveFileName(&sOpenFileName) > 0) //for saving a file
					{
						SendMessage(sHwndCtlEdtBin,  WM_SETTEXT, 0, (LPARAM) cBin);
					}
					break;

				case IDC_BTN_RUN:
					
					break;
			}
		default:
			return DefWindowProc(sHwndMain, sMsg, wParam, lParam);
	}
	return DefWindowProc(sHwndMain, sMsg, wParam, lParam);
}
//custom functions
LRESULT SetTextCMDLine(HWND sHwndCtlEdtCMDLine)
{
	swprintf_s((wchar_t *) cCMDLine, 1500, TEXT("sc.exe%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"),
	cSvr, cCommand, cSvc, cType, cQyType, cState, cInteract, cStart,
	cErr, cBin, cGrp, cTag, cDpd, cAcc, cPw, cDisp, cBuf, cResm);
	return SendMessage(sHwndCtlEdtCMDLine,  WM_SETTEXT, 0, (LPARAM) cCMDLine);
}

VOID EnableBtnRun(HWND sHwndCtlBtnRun, HWND sHwndCtlCmbCmd)
{
	iComboIndex = SendMessage(sHwndCtlCmbCmd, CB_GETCURSEL, 0, 0);
	switch(iComboIndex)
	{
		case 0:
			if(strcmp((char *) cSvc, "") != 0 && strcmp((char *) cBin, "") != 0)
			{
				EnableWindow(sHwndCtlBtnRun, TRUE);
			}
			else
			{
				EnableWindow(sHwndCtlBtnRun, FALSE);
			}				
			break;

		case 1:
			if(strcmp((char *) cSvc, "") != 0 &&
			(strcmp((char *) cBin, "") != 0 ||
			strcmp((char *) cType, "") != 0 ||
			strcmp((char *) cStart, "") != 0 ||
			strcmp((char *) cErr, "") != 0 ||
			strcmp((char *) cGrp, "") != 0 ||
			strcmp((char *) cTag, "") != 0 ||
			strcmp((char *) cDpd, "") != 0 ||
			strcmp((char *) cAcc, "") != 0 ||
			strcmp((char *) cDisp, "") != 0))
			{
				EnableWindow(sHwndCtlBtnRun, TRUE);
			}
			else
			{
				EnableWindow(sHwndCtlBtnRun, FALSE);
			}
			break;

		case 2:
			if(strcmp((char *) cSvc, "") != 0 )
			{
				EnableWindow(sHwndCtlBtnRun, TRUE);
			}
			else
			{
				EnableWindow(sHwndCtlBtnRun, FALSE);
			}
			break;

		case 3:
			if(strcmp((char *) cSvc, "") != 0)
			{
				EnableWindow(sHwndCtlBtnRun, TRUE);
			}
			else
			{
				EnableWindow(sHwndCtlBtnRun, FALSE);
			}
			break;			
	};
}

BOOL CALLBACK AboutDlgProc(HWND sHwndMain, UINT sMsg, WPARAM wParam, LPARAM lParam)
{
	switch(sMsg)
	{
		case WM_INITDIALOG:
			
			break;

		case WM_CTLCOLORDLG:
			SetBkColor((HDC) wParam, RGB(255, 255, 255));
			SetTextColor((HDC) wParam, RGB(0, 0, 0));
			return (LRESULT) GetStockObject(DC_BRUSH);
			break;

		case WM_CTLCOLORSTATIC:
			SetBkColor((HDC) wParam, RGB(255, 255, 255));
			SetTextColor((HDC) wParam, RGB(0, 0, 0));
			return (LRESULT) GetStockObject(DC_BRUSH);
			break;

		case WM_CTLCOLOREDIT:
			SetBkColor((HDC) wParam, RGB(255, 255, 255));
			SetTextColor((HDC) wParam, RGB(0, 0, 0));
			return (LRESULT) GetStockObject(DC_BRUSH);
			break;
		
		case WM_CLOSE:
			EndDialog(sHwndMain, sMsg);
			break;

		case WM_DESTROY:
			EndDialog(sHwndMain, sMsg);
			break;

		case WM_COMMAND: //no other controls on this dialog window
			break;

		default:
			return FALSE;
	}	
	return DefWindowProc(sHwndMain, sMsg, wParam, lParam);
}