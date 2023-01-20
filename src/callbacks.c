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
wchar_t *cUniTitleAcc;
wchar_t *cUniTextAcc;
HMODULE vHmodInst;		
EDITBALLOONTIP sTipAcc;
OPENFILENAME sOpenFileName;
LPCWSTR cPathFileSaveText;
LPCWSTR cTempBuff;
HANDLE hFileToOpen;
HANDLE hFileToSave;
HRESULT hResult;
BOOL bResult;
LPWSTR cPathFolderPersonal;
int iComboIndex;
int iTextLen;
int iFileModified;
char *cWinTitle;
char *cCMDLine;
char *cCommand;
char *cSvr;
char *cSvc;
char *cType;
char *cInteract;
char *cStart;
char *cErr;
char *cBin;
char *cGrp;
char *cTag;
char *cDpd;
char *cAcc;
char *cObj;
char *cDisp;
char *cPw;
char *cQyType;
char *cState;
char *cBuf;
char *cResm;
char *cRslt;
char *cPathFileSaveBat;
char *cPathFolderUserProfile;
char *cFileName;
char *cContentsResult;
	
//main window callback procedure
LRESULT CALLBACK WndProc(HWND sHwndMain, UINT sMsg, WPARAM wParam, LPARAM lParam)
{	
	//define module/executable handle
	vHmodInst = GetModuleHandle(NULL);	

	//verify if module instance handle was created correctly
	if(vHmodInst == NULL)
	{
		MessageBox(sHwndMain, TEXT("Could not create module instance handle."), TEXT("Error"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	//definitions
	HWND sHwndCtlEdtDes = GetDlgItem(sHwndMain, IDC_EDIT_DESC);
	HWND sHwndCtlEdtReq = GetDlgItem(sHwndMain, IDC_EDIT_REQ);
	HWND sHwndCtlEdtSvr = GetDlgItem(sHwndMain, IDC_EDIT_SVRNAME);
	HWND sHwndCtlEdtSvc = GetDlgItem(sHwndMain, IDC_EDIT_SVCNAME);
	HWND sHwndCtlEdtGrp = GetDlgItem(sHwndMain, IDC_EDIT_GROUP);
	HWND sHwndCtlEdtBin = GetDlgItem(sHwndMain, IDC_EDIT_PATHBIN);
	HWND sHwndCtlEdtDpd = GetDlgItem(sHwndMain, IDC_EDIT_DEPEND);
	HWND sHwndCtlEdtAcc = GetDlgItem(sHwndMain, IDC_EDIT_ACCNAME);
	HWND sHwndCtlEdtObj = GetDlgItem(sHwndMain, IDC_EDIT_OBJNAME);
	HWND sHwndCtlEdtDisp = GetDlgItem(sHwndMain, IDC_EDIT_DISPNAME);
	HWND sHwndCtlEdtPw = GetDlgItem(sHwndMain, IDC_EDIT_PW);
	HWND sHwndCtlEdtBuf = GetDlgItem(sHwndMain, IDC_EDIT_BUFF);
	HWND sHwndCtlEdtResm = GetDlgItem(sHwndMain, IDC_EDIT_RESUME);
	HWND sHwndCtlEdtCMDLine = GetDlgItem(sHwndMain, IDC_EDIT_CMDLINE);
	HWND sHwndCtlEdtRslt = GetDlgItem(sHwndMain, IDC_EDIT_RSLT);
	HWND sHwndCtlCmbCmd = GetDlgItem(sHwndMain, IDC_COMBO_COMMAND);
	HWND sHwndCtlCmbType = GetDlgItem(sHwndMain, IDC_COMBO_TYPE);
	HWND sHwndCtlCmbInteract = GetDlgItem(sHwndMain, IDC_COMBO_INTERACT);
	HWND sHwndCtlCmbStart = GetDlgItem(sHwndMain, IDC_COMBO_START);
	HWND sHwndCtlCmbErr = GetDlgItem(sHwndMain, IDC_COMBO_ERROR);	
	HWND sHwndCtlCmbTag = GetDlgItem(sHwndMain, IDC_COMBO_TAG);	
	HWND sHwndCtlCmbQyType = GetDlgItem(sHwndMain, IDC_COMBO_QYTYPE);
	HWND sHwndCtlCmbState = GetDlgItem(sHwndMain, IDC_COMBO_STATE);
	HWND sHwndCtlBtnBrowse = GetDlgItem(sHwndMain, IDC_BTN_BROWSE);
	HWND sHwndCtlBtnRun = GetDlgItem(sHwndMain, IDC_BTN_RUN);	
	
	switch(sMsg)
	{

		//begin window messages

		case WM_CREATE:
			//initializations	
			cTempBuff = malloc(400 * sizeof (char));
			cUniTitleAcc = malloc(23 * sizeof (wchar_t));
			cUniTextAcc = malloc(60 * sizeof (wchar_t));
			cCMDLine = calloc(1500, sizeof (char)); //The maximum command line length for the CreateProcess function is 32767 characters.
			cCommand = calloc(10, sizeof (char));			
			cSvr = calloc(17, sizeof (char));
			cSvc = calloc(257, sizeof (char));
			cType = calloc(30, sizeof (char));
			cInteract = calloc(20, sizeof (char));
			cStart = calloc(22, sizeof (char));
			cErr = calloc(20, sizeof (char));
			cBin = calloc(MAX_PATH, sizeof (char));
			cGrp = calloc(80, sizeof (char));
			cTag = calloc(5, sizeof (char));
			cDpd = calloc(190, sizeof (char));
			cAcc = calloc(257, sizeof (char));
			cObj = calloc(267, sizeof (char));
			cDisp = calloc(287, sizeof (char));
			cPw = calloc(27, sizeof (char));
			cQyType = calloc(20, sizeof (char));
			cState = calloc(20, sizeof (char));
			cBuf = calloc(25, sizeof (char));
			cResm = calloc(8, sizeof (char));
			cRslt = calloc(1, sizeof (char));
			cPathFileSaveText = calloc(40, sizeof (char));
			cPathFileSaveBat = calloc(40, sizeof (char));
			cPathFolderPersonal = calloc(MAX_PATH, sizeof (char));
			cFileName = calloc(50, sizeof (char));
			cContentsResult = calloc(128, sizeof (char));			

			//define path defaults
			hResult = SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, SHGFP_TYPE_CURRENT, cPathFolderPersonal);
			if(hResult != S_OK)
			{
				MessageBox(sHwndMain, TEXT("Could not find user profile folder"), TEXT("Error"), MB_OK | MB_ICONERROR);
				return FALSE;
			}
			cPathFileSaveText = realloc((void *) cPathFileSaveText, (strlen((char *) cPathFolderPersonal) +  15) * sizeof(char));
			strcpy_s((char *) cPathFileSaveText, 40, cPathFolderPersonal);
			strcat(cPathFileSaveText, "\\results.txt");
			strcpy_s((char *) cPathFileSaveBat, 40, cPathFolderPersonal);
			strcat(cPathFileSaveBat, "\\results.txt");			

			//define edit box tooltip structure for account name and object name parameters.
			sTipAcc.cbStruct = sizeof (EDITBALLOONTIP);
			strcpy_s(cTempBuff,  40, "Account or object name");
			MultiByteToWideChar(CP_ACP, 0, cTempBuff, -1, cUniTitleAcc, 23);
			sTipAcc.pszTitle = (LPCWSTR) cUniTitleAcc;
			strcpy_s(cTempBuff,  40, "Either account name or object\nname is allowed but not both");
			MultiByteToWideChar(CP_ACP, 0, cTempBuff, -1, cUniTextAcc, 60);
			sTipAcc.pszText = (LPCWSTR) cUniTextAcc;
			sTipAcc.ttiIcon = TTI_INFO;

			if(CreateControls(sHwndMain) != 0) //function to create all controls. Review controls.h and controls.c
			{
				MessageBox(sHwndMain, TEXT("Could not create controls"), TEXT("Error"), MB_OK | MB_ICONERROR);
				return FALSE;
			}					
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
					SendMessage(sHwndCtlCmbCmd, CB_SETCURSEL, (WPARAM) 0, (LPARAM)0);
					SendMessage(sHwndCtlEdtSvr, WM_SETTEXT, (WPARAM) 0, (LPARAM) "");
					SendMessage(sHwndCtlEdtSvc, WM_SETTEXT, (WPARAM) 0, (LPARAM) "");
					SendMessage(sHwndCtlCmbType, CB_SETCURSEL, (WPARAM) 0, (LPARAM) 0);					
					SendMessage(sHwndCtlCmbInteract, CB_SETCURSEL, (WPARAM) 0, (LPARAM) 0);
					SendMessage(sHwndCtlCmbStart, CB_SETCURSEL, (WPARAM) 0, (LPARAM) 0);
					SendMessage(sHwndCtlCmbErr, CB_SETCURSEL, (WPARAM) 0, (LPARAM) 0);
					SendMessage(sHwndCtlEdtBin, WM_SETTEXT, (WPARAM) 0, (LPARAM) "");
					SendMessage(sHwndCtlCmbQyType, CB_SETCURSEL, (WPARAM) 0, (LPARAM) 0);
					SendMessage(sHwndCtlCmbState, CB_SETCURSEL, (WPARAM) 0, (LPARAM) 0);
					SendMessage(sHwndCtlEdtGrp, WM_SETTEXT, (WPARAM) 0, (LPARAM) "");
					SendMessage(sHwndCtlCmbTag, CB_SETCURSEL, (WPARAM) 0, (LPARAM) 0);
					SendMessage(sHwndCtlEdtDpd, WM_SETTEXT, (WPARAM) 0, (LPARAM) "");
					SendMessage(sHwndCtlEdtAcc, WM_SETTEXT, (WPARAM) 0, (LPARAM) "");
					SendMessage(sHwndCtlEdtObj, WM_SETTEXT, (WPARAM) 0, (LPARAM) "");
					SendMessage(sHwndCtlEdtDisp, WM_SETTEXT, (WPARAM) 0, (LPARAM) "");
					SendMessage(sHwndCtlEdtPw, WM_SETTEXT, (WPARAM) 0, (LPARAM) "");
					SendMessage(sHwndCtlEdtBuf, WM_SETTEXT, (WPARAM) 0, (LPARAM) "");
					SendMessage(sHwndCtlEdtResm, WM_SETTEXT, (WPARAM) 0, (LPARAM) "");					
					strcpy_s(cCommand, 10, "");
					strcpy_s(cSvr, 17, "");
					strcpy_s(cSvc, 257, "");
					strcpy_s(cType, 30, "");
					strcpy_s(cInteract, 20, "");
					strcpy_s(cStart, 22, "");
					strcpy_s(cErr, 20, "");
					strcpy_s(cBin, MAX_PATH, "");
					strcpy_s(cQyType, 20, "");
					strcpy_s(cState, 20, "");
					strcpy_s(cGrp, "");
					strcpy_s(cTag, "");
					strcpy_s(cDpd, "");
					strcpy_s(cAcc, "");
					strcpy_s(cObj, "");
					strcpy_s(cDisp, "");
					strcpy_s(cPw, "");
					strcpy_s(cBuf, "");					
					iTextLen = SendMessage(sHwndCtlEdtRslt, WM_GETTEXTLENGTH, 0, 0);
					if(iTextLen != 0 && MessageBox(sHwndMain, TEXT("Save results to current file?"), TEXT("Save file"), MB_YESNO|MB_ICONQUESTION) == IDYES)
					{						
						
					}
					SendMessage(sHwndCtlEdtRslt, WM_SETTEXT, (WPARAM) 0, (LPARAM) "");
					strcpy_s(cRslt, "");
					SendMessage(sHwndCtlCmbCmd, CB_SETCURSEL, (WPARAM) 0, (LPARAM)0);
					SendMessage(sHwndMain, WM_COMMAND, (WPARAM) MAKELONG(IDC_COMBO_COMMAND, CBN_SELCHANGE), (LPARAM) sHwndCtlCmbCmd);					
					break;

				case IDC_BTN_TBTEXT:
					iTextLen = SendMessage(sHwndCtlEdtRslt, WM_GETTEXTLENGTH, 0, 0);
					
					if(iTextLen == 0)
					{	
						MessageBox(sHwndMain, TEXT("There are no results to save."), TEXT("Save results as text"), MB_OK | MB_ICONINFORMATION);					
						break;
					}				

					//realloc(cTempBuff, iTextLen * sizeof (char));
					//SendMessage(sHwndCtlEdtRslt, WM_GETTEXT, (WPARAM) iTextLen,(LPARAM) cTempBuff);

					ZeroMemory(&sOpenFileName, sizeof (sOpenFileName));
					sOpenFileName.lStructSize = sizeof (sOpenFileName);
					sOpenFileName.hwndOwner = sHwndMain;
					sOpenFileName.hInstance = NULL;
					sOpenFileName.lpstrFilter = TEXT("Text Files (*.txt)\0*.txt\0\0");
					sOpenFileName.lpstrCustomFilter = NULL;
					sOpenFileName.nMaxCustFilter = 0;
					sOpenFileName.nFilterIndex = 1;
					sOpenFileName.lpstrFile = cPathFileSaveText;
					sOpenFileName.nMaxFile = MAX_PATH;
					sOpenFileName.lpstrFileTitle = NULL;
					sOpenFileName.nMaxFileTitle = 0;
					sOpenFileName.lpstrInitialDir = NULL;
					sOpenFileName.lpstrTitle = TEXT("Save as text file");
					//sOpenFileName.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY; //For opening a file				
					sOpenFileName.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT; //For saving a file					
					sOpenFileName.nFileOffset = 0;
					sOpenFileName.nFileExtension = 0;
					sOpenFileName.lpstrDefExt = TEXT("txt");
					sOpenFileName.lCustData = 0;
					sOpenFileName.lpfnHook = NULL;
					sOpenFileName.lpTemplateName = NULL;
					//sOpenFileName.lpEditInfo = NULL; //applicable only to Motorola 68K Macintosh computers, and not to Windows client operating systems.
					//sOpenFileName.lpstrPrompt = NULL; //"

					//if(GetOpenFileName(&sOpenFileName) != 0) //for opening a file
					if(GetSaveFileName(&sOpenFileName) != 0) //for saving a file
					{
						//strcpy_s(cFileName, basename(cPathFileSaveText));
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
						SendMessage(sHwndMain,  WM_SETTEXT, 0, (LPARAM) strcat(cFileName, TEXT(" - Service Control")));				
						CloseHandle(hFileToSave);
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
							SendMessage(sHwndCtlEdtBuf,  WM_SETTEXT, 0, (LPARAM) "");
							SendMessage(sHwndCtlEdtResm,  WM_SETTEXT, 0, (LPARAM) "");
							SendMessage(sHwndCtlEdtPw,  WM_SETTEXT, 0, (LPARAM) "");
							SendMessage(sHwndCtlCmbType, CB_DELETESTRING,(WPARAM) 7, 0);
							EnableWindow(sHwndCtlEdtSvr, TRUE);
							EnableWindow(sHwndCtlEdtSvr, TRUE);
							EnableWindow(sHwndCtlCmbType, TRUE);
							EnableWindow(sHwndCtlCmbInteract, FALSE);
							EnableWindow(sHwndCtlCmbStart, TRUE);
							EnableWindow(sHwndCtlCmbErr, TRUE);
							EnableWindow(sHwndCtlEdtBin, TRUE);
							EnableWindow(sHwndCtlBtnBrowse, TRUE);
							EnableWindow(sHwndCtlEdtGrp, TRUE);
							EnableWindow(sHwndCtlCmbTag, TRUE);
							EnableWindow(sHwndCtlEdtDpd, TRUE);
							EnableWindow(sHwndCtlEdtAcc, TRUE);
							EnableWindow(sHwndCtlEdtObj, TRUE);
							EnableWindow(sHwndCtlEdtDisp, TRUE);
							EnableWindow(sHwndCtlEdtPw, TRUE);						
							EnableWindow(sHwndCtlCmbQyType, FALSE);
							EnableWindow(sHwndCtlCmbState, FALSE);
							EnableWindow(sHwndCtlEdtBuf, FALSE);
							EnableWindow(sHwndCtlEdtResm, FALSE);
							EnableWindow(sHwndCtlEdtPw, FALSE);
							EnableWindow(sHwndCtlBtnRun, FALSE);
							SendMessage(sHwndCtlCmbType, CB_SETCURSEL, 0, 0);
							SendMessage(sHwndCtlCmbQyType, CB_SETCURSEL, (WPARAM) -1, 0);
							SendMessage(sHwndCtlCmbState, CB_SETCURSEL, (WPARAM) -1, 0);
							SendMessage(sHwndCtlCmbInteract, CB_SETCURSEL, (WPARAM) -1, 0);
							strcpy_s(cQyType, "");
							strcpy_s(cState, "");
							strcpy_s(cBuf, "");
							strcpy_s(cResm, "");
							strcpy_s(cType, "");
							strcpy_s(cInteract, "");

							iComboIndex = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);

							switch(iComboIndex)
							{
								case 0:
									LoadString(vHmodInst, IDS_COMMAND_CREATE, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									SendMessage(sHwndCtlEdtReq,  WM_SETTEXT, 0, (LPARAM) "Required parameters:\r\n Service name, Binary Path.");
									strcpy_s(cCommand, " create");
									break;

								case 1:
									LoadString(vHmodInst, IDS_COMMAND_CONF, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									SendMessage(sHwndCtlEdtReq,  WM_SETTEXT, 0, (LPARAM) "Required parameters:\r\n Service name, one other parameter to modify.");
									strcpy_s(cCommand, " config");
									SendMessage(sHwndCtlCmbType, CB_ADDSTRING,0,(LPARAM) "adapt");
									break;

								case 2:
									LoadString(vHmodInst, IDS_COMMAND_DELETE, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									SendMessage(sHwndCtlEdtReq,  WM_SETTEXT, 0, (LPARAM) "Required parameters:\r\n Service name.");
									strcpy_s(cCommand, " delete");									
									SendMessage(sHwndCtlCmbType,  CB_SETCURSEL, 0, 0);
									SendMessage(sHwndCtlCmbInteract,  CB_SETCURSEL, -1, 0);
									SendMessage(sHwndCtlCmbStart,  CB_SETCURSEL, 0, 0);
									SendMessage(sHwndCtlCmbErr,  CB_SETCURSEL, 0, 0);
									SendMessage(sHwndCtlCmbTag,  CB_SETCURSEL, 0, 0);
									SendMessage(sHwndCtlEdtBin,  WM_SETTEXT, 0, (LPARAM) "");
									SendMessage(sHwndCtlEdtGrp,  WM_SETTEXT, 0, (LPARAM) "");
									SendMessage(sHwndCtlEdtDpd,  WM_SETTEXT, 0, (LPARAM) "");
									SendMessage(sHwndCtlEdtAcc,  WM_SETTEXT, 0, (LPARAM) "");
									SendMessage(sHwndCtlEdtObj,  WM_SETTEXT, 0, (LPARAM) "");
									SendMessage(sHwndCtlEdtDisp,  WM_SETTEXT, 0, (LPARAM) "");
									SendMessage(sHwndCtlEdtPw,  WM_SETTEXT, 0, (LPARAM) "");																											
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
									strcpy_s(cType, "");
									strcpy_s(cInteract, "");
									strcpy_s(cStart, "");
									strcpy_s(cErr, "");
									strcpy_s(cTag, "");
									strcpy_s(cBin, "");
									strcpy_s(cGrp, "");
									strcpy_s(cDpd, "");
									strcpy_s(cAcc, "");
									strcpy_s(cDisp, "");
									strcpy_s(cPw, "");
									break;

								case 3:
									LoadString(vHmodInst, IDS_COMMAND_QUERY, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									SendMessage(sHwndCtlEdtReq,  WM_SETTEXT, 0, (LPARAM) "Required parameters:\r\n Service name.");
									strcpy_s(cCommand, " query");
									SendMessage(sHwndCtlCmbType, CB_ADDSTRING,0,(LPARAM) "adapt");									
									SendMessage(sHwndCtlCmbStart,  CB_SETCURSEL, 0, 0);
									SendMessage(sHwndCtlCmbErr,  CB_SETCURSEL, 0, 0);
									SendMessage(sHwndCtlCmbTag,  CB_SETCURSEL, 0, 0);
									SendMessage(sHwndCtlEdtBin,  WM_SETTEXT, 0, (LPARAM) "");									
									SendMessage(sHwndCtlEdtDpd,  WM_SETTEXT, 0, (LPARAM) "");
									SendMessage(sHwndCtlEdtAcc,  WM_SETTEXT, 0, (LPARAM) "");
									SendMessage(sHwndCtlEdtObj,  WM_SETTEXT, 0, (LPARAM) "");
									SendMessage(sHwndCtlEdtDisp,  WM_SETTEXT, 0, (LPARAM) "");
									SendMessage(sHwndCtlEdtPw,  WM_SETTEXT, 0, (LPARAM) "");									
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
									strcpy_s(cStart, "");
									strcpy_s(cErr, "");
									strcpy_s(cTag, "");
									strcpy_s(cBin, "");
									strcpy_s(cDpd, "");
									strcpy_s(cAcc, "");
									strcpy_s(cDisp, "");
									strcpy_s(cPw, "");
									strcpy_s(cQyType, " type= service");
									strcpy_s(cState, " state= active");
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
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) "Exclude this paramater (Type)");
									SendMessage(sHwndCtlCmbInteract, CB_SETCURSEL, (WPARAM) -1, 0);
									strcpy_s(cType, "");
									strcpy_s(cInteract, "");
									EnableWindow(sHwndCtlCmbInteract, FALSE);									
									break;

								case 1:
									LoadString(vHmodInst, IDS_TYPE_OWN, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									SendMessage(sHwndCtlCmbInteract, CB_SETCURSEL, (WPARAM) -1, 0);
									strcpy_s(cType, " type= own");
									strcpy_s(cInteract, "");
									EnableWindow(sHwndCtlCmbInteract, FALSE);									
									break;

								case 2:
									LoadString(vHmodInst, IDS_TYPE_SHARE, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									SendMessage(sHwndCtlCmbInteract, CB_SETCURSEL, (WPARAM) -1, 0);
									strcpy_s(cType, " type= share");
									strcpy_s(cInteract, "");
									EnableWindow(sHwndCtlCmbInteract, FALSE);									
									break;

								case 3:
									LoadString(vHmodInst, IDS_TYPE_KERNEL, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									SendMessage(sHwndCtlCmbInteract, CB_SETCURSEL, (WPARAM) -1, 0);
									strcpy_s(cType, " type= kernal");
									strcpy_s(cInteract, "");
									EnableWindow(sHwndCtlCmbInteract, FALSE);									
									break;

								case 4:
									LoadString(vHmodInst, IDS_TYPE_FILSYS, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									SendMessage(sHwndCtlCmbInteract, CB_SETCURSEL, (WPARAM) -1, 0);
									strcpy_s(cType, " type= filesys");
									strcpy_s(cInteract, "");
									EnableWindow(sHwndCtlCmbInteract, FALSE);									
									break;

								case 5:
									LoadString(vHmodInst, IDS_TYPE_REC, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									SendMessage(sHwndCtlCmbInteract, CB_SETCURSEL, (WPARAM) -1, 0);
									strcpy_s(cType, " type= rec");
									strcpy_s(cInteract, "");
									EnableWindow(sHwndCtlCmbInteract, FALSE);									
									break;

								case 6:
									LoadString(vHmodInst, IDS_TYPE_INTERACT, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									strcpy_s(cType, " type= interact");
									strcpy_s(cInteract, " type= own");
									EnableWindow(sHwndCtlCmbInteract, TRUE);
									SendMessage(sHwndCtlCmbInteract, CB_SETCURSEL, 0, 0);									
									break;

								case 7:
									LoadString(vHmodInst, IDS_TYPE_ADAPT, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									strcpy_s(cType, " type= adapt");
									strcpy_s(cInteract, "");
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
									LoadString(vHmodInst, IDS_INTERACT_OWN, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									strcpy_s(cInteract, " type= own");										
									break;

								case 1:
									LoadString(vHmodInst, IDS_INTERACT_SHARE, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									strcpy_s(cInteract, " type= share");									
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
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) "Exclude this paramater (Start)");
									strcpy_s(cStart, "");
									break;

								case 1:
									LoadString(vHmodInst, IDS_START_BOOT, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									strcpy_s(cStart, " start= boot");
									break;

								case 2:
									LoadString(vHmodInst, IDS_START_SYSTEM, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									strcpy_s(cStart, " start= system");
									break;

								case 3:
									LoadString(vHmodInst, IDS_START_AUTO, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									strcpy_s(cStart, " start= auto");
									break;

								case 4:
									LoadString(vHmodInst, IDS_START_DEMAND, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									strcpy_s(cStart, " start= demand");
									break;

								case 5:
									LoadString(vHmodInst, IDS_START_DISABLED, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									strcpy_s(cStart, " start= disabled");
									break;

								case 6:
									LoadString(vHmodInst, IDS_START_DELAYED, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									strcpy_s(cStart, " start= delayed-auto");
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
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) "Exclude this paramater (Error)");
									strcpy_s(cErr, "");
									break;

								case 1:
									LoadString(vHmodInst, IDS_ERROR_NORMAL, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									strcpy_s(cErr, " error= normal");
									break;

								case 2:
									LoadString(vHmodInst, IDS_ERROR_SEVERE, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									strcpy_s(cErr, " error= severe");
									break;

								case 3:
									LoadString(vHmodInst, IDS_ERROR_CRITICAL, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									strcpy_s(cErr, " error= critical");
									break;

								case 4:
									LoadString(vHmodInst, IDS_ERROR_IGNORE, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									strcpy_s(cErr, " error= ignore");
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
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) "Exclude this paramater (Tag)");
									strcpy_s(cTag, "");
									break;

								case 1:
									LoadString(vHmodInst, IDS_TAG_YES, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									strcpy_s(cTag, " tag= yes");
									break;

								case 2:
									LoadString(vHmodInst, IDS_TAG_NO, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									strcpy_s(cTag, " tag= no");
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
										LoadString(vHmodInst, IDS_QYTYPE_SERVICE, cTempBuff, 399);
										SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										strcpy_s(cQyType, " type= service");
										break;

									case 1:
										LoadString(vHmodInst, IDS_QYTYPE_DRIVER, cTempBuff, 399);
										SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										strcpy_s(cQyType, " type= driver");
										break;

									case 2:
										LoadString(vHmodInst, IDS_QYTYPE_ALL, cTempBuff, 399);
										SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										strcpy_s(cQyType, " type= all");
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
										LoadString(vHmodInst, IDS_STATE_ACTIVE, cTempBuff, 399);
										SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										strcpy_s(cState, " state= active");
										break;

									case 1:
										LoadString(vHmodInst, IDS_STATE_INACTIVE, cTempBuff, 399);
										SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										strcpy_s(cState, " state= inactive");
										break;

									case 2:
										LoadString(vHmodInst, IDS_STATE_ALL, cTempBuff, 399);
										SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										strcpy_s(cState, " state= all");
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
							LoadString(vHmodInst, IDS_SVRNAME, cTempBuff, 399);
							SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
							break;

						case EN_CHANGE:
							SendMessage(sHwndCtlEdtSvr, WM_GETTEXT, (WPARAM) 400,(LPARAM) cTempBuff);
							if(strcmp(cTempBuff, "") != 0)
							{
								strcpy_s(cSvr, " ");
								strcat(cSvr, cTempBuff);									
							}
							else
							{
								strcpy_s(cSvr, "");
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
							LoadString(vHmodInst, IDS_SVCNAME, cTempBuff, 399);
							SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);							
							break;

						case EN_CHANGE:
							SendMessage(sHwndCtlEdtSvc, WM_GETTEXT, (WPARAM) 400,(LPARAM) cTempBuff);
							if(strcmp(cTempBuff, "") != 0)
							{
								strcpy_s(cSvc, " ");
								strcat(cSvc, cTempBuff);									
							}
							else
							{
								strcpy_s(cSvc, "");
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
							LoadString(vHmodInst, IDS_PATHBIN, cTempBuff, 399);
							SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);								
							break;

						case  EN_CHANGE:
						SendMessage(sHwndCtlEdtBin , WM_GETTEXT, (WPARAM) 400,(LPARAM) cTempBuff);
						if(strcmp(cTempBuff, "") != 0)
						{
							strcpy_s(cBin, " binpath= \"");
							strcat(cBin, cTempBuff);
							strcat(cBin, "\"");								
						}
						else
						{
							strcpy_s(cBin, "");
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
							LoadString(vHmodInst, IDS_GROUP, cTempBuff, 399);
							SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);								
							break;
						
						case  EN_CHANGE:
						SendMessage(sHwndCtlEdtGrp, WM_GETTEXT, (WPARAM) 400,(LPARAM) cTempBuff);
						if(strcmp(cTempBuff, "") != 0)
						{
							strcpy_s(cGrp, " group= TEXT(");
							strcat(cGrp, cTempBuff);									
						}
						else
						{
							strcpy_s(cGrp, "");
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
							LoadString(vHmodInst, IDS_DEPEND, cTempBuff, 399);
							SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);								
							break;

						case  EN_CHANGE:
							SendMessage(sHwndCtlEdtDpd, WM_GETTEXT, (WPARAM) 400,(LPARAM) cTempBuff);
							if(strcmp(cTempBuff, "") != 0)
							{
								strcpy_s(cDpd, " depend= TEXT(");
								strcat(cDpd, cTempBuff);									
							}
							else
							{
								strcpy_s(cDpd, "");
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
							LoadString(vHmodInst, IDS_ACCNAME, cTempBuff, 399);
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
							if(strcmp(cTempBuff, "") != 0)
							{
								strcpy_s(cAcc, " obj= TEXT(");
								strcat(cAcc, cTempBuff);									
							}
							else
							{
								strcpy_s(cAcc, "");
							}
							SetTextCMDLine(sHwndCtlEdtCMDLine);
							EnableBtnRun(sHwndCtlBtnRun, sHwndCtlCmbCmd);								
							break;

						case EN_KILLFOCUS:
							if(SendMessage(sHwndCtlEdtAcc,  WM_GETTEXTLENGTH, 0, 0) <= 0)
							{
								SendMessage(sHwndCtlEdtPw,  WM_SETTEXT, 0, (LPARAM) "");
								EnableWindow(sHwndCtlEdtPw, FALSE);
								strcpy_s(cPw, "");
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
							LoadString(vHmodInst, IDS_OBJNAME, cTempBuff, 399);
							SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
							SendMessage(sHwndCtlEdtObj,  EM_SHOWBALLOONTIP, 0, (LPARAM) &sTipAcc);								
							break;

						case EN_CHANGE:
							if(SendMessage(sHwndCtlEdtObj,  WM_GETTEXTLENGTH, 0, 0) > 0)
							{
								SendMessage(sHwndCtlEdtAcc,  WM_SETTEXT, 0, (LPARAM) "");
								EnableWindow(sHwndCtlEdtAcc, FALSE);
								EnableWindow(sHwndCtlEdtPw, TRUE);
							}
							else
							{
								EnableWindow(sHwndCtlEdtAcc, TRUE);
								EnableWindow(sHwndCtlEdtPw, FALSE);
							}
							SendMessage(sHwndCtlEdtObj, WM_GETTEXT, (WPARAM) 400,(LPARAM) cTempBuff);
							if(strcmp(cTempBuff, "") != 0)
							{
								strcpy_s(cAcc, " obj= TEXT(");
								strcat(cAcc, cTempBuff);									
							}
							else
							{
								strcpy_s(cAcc, "");
							}								
							SetTextCMDLine(sHwndCtlEdtCMDLine);
							EnableBtnRun(sHwndCtlBtnRun, sHwndCtlCmbCmd);
							break;

						case EN_KILLFOCUS:
							if(SendMessage(sHwndCtlEdtObj,  WM_GETTEXTLENGTH, 0, 0) <= 0)
							{
								SendMessage(sHwndCtlEdtPw,  WM_SETTEXT, 0, (LPARAM) "");
								EnableWindow(sHwndCtlEdtPw, FALSE);
								strcpy_s(cPw, "");
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
							LoadString(vHmodInst, IDS_DISPNAME, cTempBuff, 399);
							SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);								
							break;

						case EN_CHANGE:
							SendMessage(sHwndCtlEdtDisp, WM_GETTEXT, (WPARAM) 400,(LPARAM) cTempBuff);
							if(strcmp(cTempBuff, "") != 0)
							{
								strcpy_s(cDisp, " displayname= TEXT(");
								strcat(cDisp, cTempBuff);									
							}
							else
							{
								strcpy_s(cDisp, "");
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
							LoadString(vHmodInst, IDS_PW, cTempBuff, 399);
							SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);								
							break;

						case EN_CHANGE:
							SendMessage(sHwndCtlEdtPw, WM_GETTEXT, (WPARAM) 400,(LPARAM) cTempBuff);
							if(strcmp(cTempBuff, "") != 0)
							{
								strcpy_s(cPw, " password= TEXT(");
								strcat(cPw, cTempBuff);									
							}
							else
							{
								strcpy_s(cPw, "");
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
							LoadString(vHmodInst, IDS_CMDLINE, cTempBuff, 399);
							SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);								
							break;

						case EN_CHANGE:
							SendMessage(sHwndCtlEdtCMDLine, WM_GETTEXT, (WPARAM) 400,(LPARAM) cTempBuff);
							if(strcmp(cTempBuff, "") != 0)
							{
								strcpy_s(cCMDLine, cTempBuff);									
							}
							break;
					}
					break;

				case IDC_EDIT_BUFF:
						switch(HIWORD (wParam))
						{
							case EN_SETFOCUS:
								LoadString(vHmodInst, IDS_BUFF, cTempBuff, 399);
								SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);								
								break;

							case EN_CHANGE:
								SendMessage(sHwndCtlEdtBuf, WM_GETTEXT, (WPARAM) 400,(LPARAM) cTempBuff);
								if(strcmp(cTempBuff, "") != 0)
								{
									strcpy_s(cBuf, " bufsize= TEXT(");
									strcat(cBuf, cTempBuff);									
								}
								else
								{
									strcpy_s(cBuf, "");
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
								LoadString(vHmodInst, IDS_RESUME, cTempBuff, 399);
								SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);								
								break;

							case EN_CHANGE:
								SendMessage(sHwndCtlEdtResm, WM_GETTEXT, (WPARAM) 400,(LPARAM) cTempBuff);
								if(strcmp(cTempBuff, "") != 0)
								{
									strcpy_s(cResm, " ri= TEXT(");
									strcat(cResm, cTempBuff);									
								}
								else
								{
									strcpy_s(cResm, "");
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
							if(strcmp(cTempBuff, "") != 0)
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
					sOpenFileName.lStructSize = sizeof (sOpenFileName);
					sOpenFileName.hwndOwner = sHwndMain;
					sOpenFileName.lpstrFile = NULL;
					sOpenFileName.lpstrFile[0] = '\0';
					sOpenFileName.nMaxFile = MAX_PATH;
					sOpenFileName.lpstrFilter = TEXT("Executable Files (*.exe)\0*.exe\0");					
					sOpenFileName.nFilterIndex = 1;
					sOpenFileName.lpstrFileTitle = TEXT("Open executable");
					sOpenFileName.nMaxFileTitle = 0;
					sOpenFileName.lpstrInitialDir = TEXT("C:\\Windows\\System32");
					sOpenFileName.lpstrDefExt = TEXT("exe");
					//For opening a file
					sOpenFileName.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;					
					//For saving a file
					//sOpenFileName.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT; 					
					if(GetOpenFileName(&sOpenFileName) != 0) //for opening a file
					//if(GetSaveFileName(&sOpenFileName) > 0) //for saving a file
					{
						SendMessage(sHwndCtlEdtBin,  WM_SETTEXT, 0, (LPARAM) "cPathFileToOpen");
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

LRESULT SetTextCMDLine(HWND sHwndCtlEdtCMDLine)
{
	sprintf(cCMDLine, "sc.exe%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
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
			if(strcmp(cSvc, "") != 0 && strcmp(cBin, "") != 0)
			{
				EnableWindow(sHwndCtlBtnRun, TRUE);
			}
			else
			{
				EnableWindow(sHwndCtlBtnRun, FALSE);
			}				
			break;

		case 1:
			if(strcmp(cSvc, "") != 0 &&
			(strcmp(cBin, "") != 0 ||
			strcmp(cType, "") != 0 ||
			strcmp(cStart, "") != 0 ||
			strcmp(cErr, "") != 0 ||
			strcmp(cGrp, "") != 0 ||
			strcmp(cTag, "") != 0 ||
			strcmp(cDpd, "") != 0 ||
			strcmp(cAcc, "") != 0 ||
			strcmp(cDisp, "") != 0))
			{
				EnableWindow(sHwndCtlBtnRun, TRUE);
			}
			else
			{
				EnableWindow(sHwndCtlBtnRun, FALSE);
			}
			break;

		case 2:
			if(strcmp(cSvc, "") != 0 )
			{
				EnableWindow(sHwndCtlBtnRun, TRUE);
			}
			else
			{
				EnableWindow(sHwndCtlBtnRun, FALSE);
			}
			break;

		case 3:
			if(strcmp(cSvc, "") != 0)
			{
				EnableWindow(sHwndCtlBtnRun, TRUE);
			}
			else
			{
				EnableWindow(sHwndCtlBtnRun, FALSE);
			}
			break;			
	}
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