/*-------------------------------------------
  Copyright Simple Solutions, 2022
  Revised: 2022/05/30 09:36
-------------------------------------------*/

//standard includes
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>

//custom includes
#include "..\include\resource.h"
#include "..\include\controls.h"
#include "..\include\callbacks.h"

//declarations
HMODULE vHmodInst;		
EDITBALLOONTIP sTipAcc;
int iComboIndex;
int iTextLen;
int iCMDLineLen;
char *cTempBuff;	
wchar_t *cUniTitleAcc;
wchar_t *cUniTextAcc;

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
char *cFile;
	
//main window callback procedure
LRESULT CALLBACK WndProc(HWND sHwndMain, UINT sMsg, WPARAM wParam, LPARAM lParam)
{	
	//define module/executable handle
	vHmodInst = GetModuleHandle(NULL);
	//verify if module instance handle was created correctly
	if(vHmodInst == NULL)
	{
		MessageBox(sHwndMain, "Could not create module instance handle.", "Error", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	//definitions
	HWND sHwndCtlEdtDes = GetDlgItem(sHwndMain, IDC_EDIT_DESC);
	HWND sHwndCtlEdtSvr = GetDlgItem(sHwndMain, IDC_EDIT_SVRNAME);
	HWND sHwndCtlEdtSvc = GetDlgItem(sHwndMain, IDC_EDIT_SVCNAME);
	HWND sHwndCtlCmbType = GetDlgItem(sHwndMain, IDC_COMBO_TYPE);
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

	HWND sHwndCtlCmbInteract = GetDlgItem(sHwndMain, IDC_COMBO_INTERACT);
	HWND sHwndCtlCmbStart = GetDlgItem(sHwndMain, IDC_COMBO_START);
	HWND sHwndCtlCmbErr = GetDlgItem(sHwndMain, IDC_COMBO_ERROR);	
	HWND sHwndCtlCmbTag = GetDlgItem(sHwndMain, IDC_COMBO_TAG);	
	HWND sHwndCtlCmbQyType = GetDlgItem(sHwndMain, IDC_COMBO_QYTYPE);
	HWND sHwndCtlCmbState = GetDlgItem(sHwndMain, IDC_COMBO_STATE);

	HWND sHwndCtlBtnBrowse = GetDlgItem(sHwndMain, IDC_BTN_BROWSE);

	switch(sMsg)
	{
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
			cStart = calloc(20, sizeof (char));
			cErr = calloc(20, sizeof (char));
			cBin = calloc(PATH_MAX, sizeof (char)); //PATH_MAX = 260
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
			cFile = calloc(1, sizeof (char));

			//define edit box tooltip structure for account name and object name parameters.
			sTipAcc.cbStruct = sizeof (EDITBALLOONTIP);
			strcpy(cTempBuff, "Account or object name");
			MultiByteToWideChar(CP_ACP, 0, cTempBuff, -1, cUniTitleAcc, 23);
			sTipAcc.pszTitle = (LPCWSTR) cUniTitleAcc;
			strcpy(cTempBuff, "Either account name or object\nname is allowed but not both");
			MultiByteToWideChar(CP_ACP, 0, cTempBuff, -1, cUniTextAcc, 60);
			sTipAcc.pszText = (LPCWSTR) cUniTextAcc;
			sTipAcc.ttiIcon = TTI_INFO;

			if(CreateControls(sHwndMain) != 0) //function to create all controls. Review controls.h and controls.c
			{
				MessageBox(sHwndMain, "Could not create controls", "Error", MB_OK | MB_ICONERROR);
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
				case IDC_MAIN_TOOLBAR_FILE_NEW:
					break;

				case IDC_MAIN_TOOLBAR_FILE_OPEN:
					break;

				case IDC_MAIN_TOOLBAR_FILE_SAVETXT:
					break;

				case IDC_MAIN_TOOLBAR_FILE_SAVEBAT:
					break;

				case IDC_MAIN_TOOLBAR_SVC_OPEN:
					break;

				case IDC_MAIN_TOOLBAR_ABOUT:
					DialogBox(vHmodInst, MAKEINTRESOURCE(IDD_ABOUT), sHwndMain, (DLGPROC) AboutDlgProc);
					break;

				case IDC_COMBO_COMMAND:
					switch(HIWORD (wParam))
					{
						case CBN_SELCHANGE:
							EnableWindow(sHwndCtlEdtSvr, TRUE);
							EnableWindow(sHwndCtlEdtSvr, TRUE);
							EnableWindow(sHwndCtlCmbType, TRUE);
							EnableWindow(sHwndCtlCmbInteract, FALSE);
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
							EnableWindow(sHwndCtlCmbQyType, FALSE);
							EnableWindow(sHwndCtlCmbState, FALSE);
							EnableWindow(sHwndCtlEdtBuf, FALSE);
							EnableWindow(sHwndCtlEdtResm, FALSE);
							SendMessage(sHwndCtlCmbType, CB_SETCURSEL, (WPARAM) -1, (LPARAM)0);
							SendMessage(sHwndCtlCmbQyType, CB_SETCURSEL, (WPARAM) -1, (LPARAM)0);
							SendMessage(sHwndCtlCmbState, CB_SETCURSEL, (WPARAM) -1, (LPARAM)0);
							SendMessage(sHwndCtlCmbInteract, CB_SETCURSEL, (WPARAM) -1, (LPARAM)0);
							iComboIndex = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
							iCMDLineLen = 8;

							switch(iComboIndex)
							{
								case 0:
									LoadString(vHmodInst, IDS_COMMAND_CREATE, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									strcpy(cCommand, " create");									
									break;

								case 1:
									LoadString(vHmodInst, IDS_COMMAND_CONF, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									strcpy(cCommand, " config");
									break;

								case 2:
									LoadString(vHmodInst, IDS_COMMAND_DELETE, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									strcpy(cCommand, " delete");
									SendMessage(sHwndCtlCmbType,  CB_SETCURSEL, 0, 0);
									SendMessage(sHwndCtlCmbInteract,  CB_SETCURSEL, -1, 0);
									SendMessage(sHwndCtlCmbStart,  CB_SETCURSEL, 0, 0);
									SendMessage(sHwndCtlCmbErr,  CB_SETCURSEL, 0, 0);
									SendMessage(sHwndCtlEdtBin,  WM_SETTEXT, 0, (LPARAM) "");
									SendMessage(sHwndCtlEdtGrp,  WM_SETTEXT, 0, (LPARAM) "");
									SendMessage(sHwndCtlCmbTag,  CB_SETCURSEL, 0, 0);
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
									break;

								case 3:
									LoadString(vHmodInst, IDS_COMMAND_QUERY, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									strcpy(cCommand, " query");									
									SendMessage(sHwndCtlCmbStart,  CB_SETCURSEL, 0, 0);
									SendMessage(sHwndCtlCmbErr,  CB_SETCURSEL, 0, 0);
									SendMessage(sHwndCtlEdtBin,  WM_SETTEXT, 0, (LPARAM) "");
									SendMessage(sHwndCtlCmbTag,  CB_SETCURSEL, 0, 0);
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
									SendMessage(sHwndCtlCmbQyType, CB_SETCURSEL, (WPARAM) 0, (LPARAM)0);
									SendMessage(sHwndCtlCmbState, CB_SETCURSEL, (WPARAM) 0, (LPARAM)0);
									break;
							}
							sprintf(cCMDLine, "sc.exe%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
							cSvr, cCommand, cSvc, cType, cInteract, cStart, cErr, cBin, cGrp, cTag, cDpd, cAcc, cDisp, cPw);						
							break;
					}
					
					SendMessage(sHwndCtlEdtCMDLine,  WM_SETTEXT, 0, (LPARAM) cCMDLine);
					break;
				
				case IDC_EDIT_SVRNAME:
					switch(HIWORD (wParam))
					{
						case EN_SETFOCUS:
							LoadString(vHmodInst, IDS_SVRNAME, cTempBuff, 399);
							SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
							break;

						case  EN_CHANGE:
							SendMessage(sHwndCtlEdtSvr, WM_GETTEXT, (WPARAM) 400,(LPARAM) cTempBuff);
							if(strcmp(cTempBuff, "") != 0)
								{
									strcpy(cSvr, " ");
									strcat(cSvr, cTempBuff);									
								}
								else
								{
									strcpy(cSvr, "");
								}
							sprintf(cCMDLine, "sc.exe%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
							cSvr, cCommand, cSvc, cType, cInteract, cStart, cErr, cBin, cGrp, cTag, cDpd, cAcc, cDisp, cPw);
							SendMessage(sHwndCtlEdtCMDLine,  WM_SETTEXT, 0, (LPARAM) cCMDLine);								
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

						case  EN_CHANGE:
							SendMessage(sHwndCtlEdtSvc, WM_GETTEXT, (WPARAM) 400,(LPARAM) cTempBuff);
							if(strcmp(cTempBuff, "") != 0)
								{
									strcpy(cSvc, " ");
									strcat(cSvc, cTempBuff);									
								}
								else
								{
									strcpy(cSvc, "");
								}
							sprintf(cCMDLine, "sc.exe%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
							cSvr, cCommand, cSvc, cType, cInteract, cStart, cErr, cBin, cGrp, cTag, cDpd, cAcc, cDisp, cPw);
							SendMessage(sHwndCtlEdtCMDLine,  WM_SETTEXT, 0, (LPARAM) cCMDLine);								
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
									SendMessage(sHwndCtlCmbInteract, CB_SETCURSEL, (WPARAM) -1, (LPARAM)0);
									strcpy(cType, "");
									strcpy(cInteract, "");
									EnableWindow(sHwndCtlCmbInteract, FALSE);									
									break;

								case 1:
									LoadString(vHmodInst, IDS_TYPE_OWN, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									SendMessage(sHwndCtlCmbInteract, CB_SETCURSEL, (WPARAM) -1, (LPARAM)0);
									strcpy(cType, " type= own");
									strcpy(cInteract, "");
									EnableWindow(sHwndCtlCmbInteract, FALSE);									
									break;

								case 2:
									LoadString(vHmodInst, IDS_TYPE_SHARE, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									SendMessage(sHwndCtlCmbInteract, CB_SETCURSEL, (WPARAM) -1, (LPARAM)0);
									strcpy(cType, " type= share");
									strcpy(cInteract, "");
									EnableWindow(sHwndCtlCmbInteract, FALSE);									
									break;

								case 3:
									LoadString(vHmodInst, IDS_TYPE_KERNEL, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									SendMessage(sHwndCtlCmbInteract, CB_SETCURSEL, (WPARAM) -1, (LPARAM)0);
									strcpy(cType, " type= kernal");
									strcpy(cInteract, "");
									EnableWindow(sHwndCtlCmbInteract, FALSE);									
									break;

								case 4:
									LoadString(vHmodInst, IDS_TYPE_FILSYS, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									SendMessage(sHwndCtlCmbInteract, CB_SETCURSEL, (WPARAM) -1, (LPARAM)0);
									strcpy(cType, " type= filesys");
									strcpy(cInteract, "");
									EnableWindow(sHwndCtlCmbInteract, FALSE);
									
									break;

								case 5:
									LoadString(vHmodInst, IDS_TYPE_REC, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									SendMessage(sHwndCtlCmbInteract, CB_SETCURSEL, (WPARAM) -1, (LPARAM)0);
									strcpy(cType, " type= rec");
									strcpy(cInteract, "");
									EnableWindow(sHwndCtlCmbInteract, FALSE);									
									break;

								case 6:
									LoadString(vHmodInst, IDS_TYPE_INTERACT, cTempBuff, 399);
									SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									strcpy(cType, " type= interact");
									strcpy(cInteract, " type= own");
									EnableWindow(sHwndCtlCmbInteract, TRUE);
									SendMessage(sHwndCtlCmbInteract, CB_SETCURSEL, (WPARAM) 0, (LPARAM)0);									
									break;
							}
							sprintf(cCMDLine, "sc.exe%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
							cSvr, cCommand, cSvc, cType, cInteract, cStart, cErr, cBin, cGrp, cTag, cDpd, cAcc, cDisp, cPw);
							SendMessage(sHwndCtlEdtCMDLine,  WM_SETTEXT, 0, (LPARAM) cCMDLine);							
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
										break;

									case 1:
										LoadString(vHmodInst, IDS_INTERACT_SHARE, cTempBuff, 399);
										SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);										
										break;
								}							
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
										
										break;

									case 1:
										LoadString(vHmodInst, IDS_START_BOOT, cTempBuff, 399);
										SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										
										break;

									case 2:
										LoadString(vHmodInst, IDS_START_SYSTEM, cTempBuff, 399);
										SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										
										break;

									case 3:
										LoadString(vHmodInst, IDS_START_AUTO, cTempBuff, 399);
										SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										
										break;

									case 4:
										LoadString(vHmodInst, IDS_START_DEMAND, cTempBuff, 399);
										SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										
										break;

									case 5:
										LoadString(vHmodInst, IDS_START_DISABLED, cTempBuff, 399);
										SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										
										break;

								}							
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
										
										break;

									case 1:
										LoadString(vHmodInst, IDS_ERROR_NORMAL, cTempBuff, 399);
										SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										
										break;

									case 2:
										LoadString(vHmodInst, IDS_ERROR_SEVERE, cTempBuff, 399);
										SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										
										break;

									case 3:
										LoadString(vHmodInst, IDS_ERROR_CRITICAL, cTempBuff, 399);
										SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										
										break;

									case 4:
										LoadString(vHmodInst, IDS_ERROR_IGNORE, cTempBuff, 399);
										SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										
										break;

								}							
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
						}
						break;

					case IDC_EDIT_GROUP:
						switch(HIWORD (wParam))
						{
							case EN_SETFOCUS:
								LoadString(vHmodInst, IDS_GROUP, cTempBuff, 399);
								SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
								
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
										
										break;

									case 1:
										LoadString(vHmodInst, IDS_TAG_YES, cTempBuff, 399);
										SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										
										break;

									case 2:
										LoadString(vHmodInst, IDS_TAG_NO, cTempBuff, 399);
										SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										
										break;

								}							
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
								}
								else
								{
									EnableWindow(sHwndCtlEdtObj, TRUE);
								}
								
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
								}
								else
								{
									EnableWindow(sHwndCtlEdtAcc, TRUE);
								}
								
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
						}
						break;

					case IDC_EDIT_PW:
						switch(HIWORD (wParam))
						{
							case EN_SETFOCUS:
								LoadString(vHmodInst, IDS_PW, cTempBuff, 399);
								SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
								
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
										
										break;

									case 1:
										LoadString(vHmodInst, IDS_QYTYPE_DRIVER, cTempBuff, 399);
										SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										
										break;

									case 2:
										LoadString(vHmodInst, IDS_QYTYPE_ALL, cTempBuff, 399);
										SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										
										break;

								}							
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
										
										break;

									case 1:
										LoadString(vHmodInst, IDS_STATE_INACTIVE, cTempBuff, 399);
										SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										
										break;

									case 2:
										LoadString(vHmodInst, IDS_STATE_ALL, cTempBuff, 399);
										SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										
										break;

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
						}
						break;

				case IDC_EDIT_RESUME:
						switch(HIWORD (wParam))
						{
							case EN_SETFOCUS:
								LoadString(vHmodInst, IDS_RESUME, cTempBuff, 399);
								SendMessage(sHwndCtlEdtDes,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
								
								break;
						}
						break;					

			}

		default:
			return DefWindowProc(sHwndMain, sMsg, wParam, lParam);
	}
	return DefWindowProc(sHwndMain, sMsg, wParam, lParam);
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