/*-------------------------------------------
  Copyright Simple Solutions, 2022
  Revised: 2022/05/30 09:36
-------------------------------------------*/

//standard includes
#include <windows.h>
#include <commctrl.h>

//custom includes
#include "..\include\resource.h"
#include "..\include\controls.h"
#include "..\include\callbacks.h"

//main window callback procedure
LRESULT CALLBACK WndProc(HWND sHdlWinMain, UINT sMsg, WPARAM wParam, LPARAM lParam)
{
	//declarations
	HMODULE vModHandle;
	EDITBALLOONTIP sTipAcc;
	RECT sWinMainRect;

	int iComboIndex;
	char *cTempBuff;
	char *cToolTipText;
	
	wchar_t *cUniTitleAcc;
	wchar_t *cUniTextAcc;
	wchar_t *cUniTextTooTip;

	TOOLINFO sToolInfo = {0};
	
	//initializations	
	cTempBuff = malloc(400 * sizeof (char));
	cToolTipText = malloc(50 * sizeof (char));
	cUniTitleAcc = malloc(23 * sizeof (wchar_t));
	cUniTextAcc = malloc(60 * sizeof (wchar_t));
	cUniTextTooTip = malloc(60 * sizeof (wchar_t));


	//definitions

	//define control handles
	HWND sHndlWinToolTip = GetDlgItem(sHdlWinMain, IDC_MAIN_TOOLTIP);
	HWND sHndlWinDesc = GetDlgItem(sHdlWinMain, IDC_EDIT_DESC);
	HWND sHndlWinSvrName = GetDlgItem(sHdlWinMain, IDC_EDIT_SVRNAME);
	HWND sHndlWinSvcName = GetDlgItem(sHdlWinMain, IDC_EDIT_SVCNAME);
	HWND sHndlWinType = GetDlgItem(sHdlWinMain, IDC_COMBO_TYPE);
	HWND sHndlWinInteract = GetDlgItem(sHdlWinMain, IDC_COMBO_INTERACT);
	HWND sHndlWinStart = GetDlgItem(sHdlWinMain, IDC_COMBO_START);
	HWND sHndlWinError = GetDlgItem(sHdlWinMain, IDC_COMBO_ERROR);
	HWND sHndlWinPathBin = GetDlgItem(sHdlWinMain, IDC_EDIT_PATHBIN);
	HWND sHndlWinGroup = GetDlgItem(sHdlWinMain, IDC_EDIT_GROUP);
	HWND sHndlWinTag = GetDlgItem(sHdlWinMain, IDC_COMBO_TAG);
	HWND sHndlWinDepend = GetDlgItem(sHdlWinMain, IDC_EDIT_DEPEND);
	HWND sHndlWinAccName = GetDlgItem(sHdlWinMain, IDC_EDIT_ACCNAME);
	HWND sHndlWinObjName = GetDlgItem(sHdlWinMain, IDC_EDIT_OBJNAME);
	HWND sHndlWinDispName = GetDlgItem(sHdlWinMain, IDC_EDIT_DISPNAME);
	HWND sHndlWinPW = GetDlgItem(sHdlWinMain, IDC_EDIT_PW);
	HWND sHndlWinQyType = GetDlgItem(sHdlWinMain, IDC_COMBO_QYTYPE);
	HWND sHndlWinState = GetDlgItem(sHdlWinMain, IDC_COMBO_STATE);
	HWND sHndlWinBuff = GetDlgItem(sHdlWinMain, IDC_EDIT_BUFF);
	HWND sHndlWinResume = GetDlgItem(sHdlWinMain, IDC_EDIT_RESUME);

	//define module/executable handle
	vModHandle = GetModuleHandle(NULL);

	//define tooltip structure for account name and object name parameters.
	sTipAcc.cbStruct = sizeof (EDITBALLOONTIP);
	strcpy(cTempBuff, "Account or object name");
	MultiByteToWideChar(CP_ACP, 0, cTempBuff, -1, cUniTitleAcc, 23);
	sTipAcc.pszTitle = (LPCWSTR) cUniTitleAcc;
	strcpy(cTempBuff, "Either account name or object\nname is allowed but not both");
	MultiByteToWideChar(CP_ACP, 0, cTempBuff, -1, cUniTextAcc, 60);
	sTipAcc.pszText = (LPCWSTR) cUniTextAcc;
	sTipAcc.ttiIcon = TTI_INFO;

	//define tool information structure
	sToolInfo.cbSize = (UINT) sizeof (TOOLINFO);
	sToolInfo.uFlags = (UINT) TTF_IDISHWND;
	//sToolInfo.hwnd = (HWND) sHdlWinMain;
	sToolInfo.uId = (UINT_PTR) sHndlWinInteract;
	GetClientRect(sHdlWinMain, &sWinMainRect);
	//sToolInfo.rect = (RECT) sWinMainRect;
	//sToolInfo.hinst = vModHandle;
	strcpy(cToolTipText, "Interact");
	MultiByteToWideChar(CP_ACP, 0, cToolTipText, -1, cUniTextTooTip, 60);
	sToolInfo.lpszText = (LPTSTR) cToolTipText;
	//sToolInfo.lParam = (LPARAM) 0;
	//sToolInfo.lpReserved = NULL;

	//SetWindowPos(sHndlWinToolTip, HWND_TOPMOST,0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

	SendMessage(sHndlWinToolTip, TTM_ACTIVATE, (WPARAM) TRUE, 0);
	//attempt to set tooltip information 
	SendMessage(sHndlWinToolTip, TTM_ADDTOOL, 0, (LPARAM) &sToolInfo);
	SendMessage(sHndlWinToolTip, TTM_ACTIVATE, (WPARAM) TRUE, 0);
	//attempt to set tooltip information 
	//SendMessage(sHndlWinToolTip, TTM_UPDATETIPTEXT, 0, (LPARAM) (LPTOOLINFO) &sToolInfo);

	//SetWindowPos(sHndlWinToolTip, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	
	//verify handle to this module/executable was created correctly
	if(vModHandle == NULL)
	{
		return FALSE;
	}

	switch(sMsg)
	{
		case WM_CREATE:
			CreateControls(sHdlWinMain); //function to create all controls. Review controls.h and controls.c
			break;

		case WM_CLOSE:
			DestroyWindow(sHdlWinMain);
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
					MessageBox(sHdlWinMain, "New File", "New File", MB_OK | MB_ICONINFORMATION);
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
					DialogBox(vModHandle, MAKEINTRESOURCE(IDD_ABOUT), sHdlWinMain, (DLGPROC) AboutDlgProc);
					break;

				case IDC_COMBO_COMMAND:
					switch(HIWORD (wParam))
					{
						case CBN_SELCHANGE:
							iComboIndex = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);

							EnableWindow(sHndlWinSvrName, TRUE);
							EnableWindow(sHndlWinSvcName, TRUE);
							EnableWindow(sHndlWinType, TRUE);
							EnableWindow(sHndlWinInteract, FALSE);
							EnableWindow(sHndlWinStart, TRUE);
							EnableWindow(sHndlWinError, TRUE);
							EnableWindow(sHndlWinPathBin, TRUE);
							EnableWindow(sHndlWinGroup, TRUE);
							EnableWindow(sHndlWinTag, TRUE);
							EnableWindow(sHndlWinDepend, TRUE);
							EnableWindow(sHndlWinAccName, TRUE);
							EnableWindow(sHndlWinObjName, TRUE);
							EnableWindow(sHndlWinDispName, TRUE);							
							EnableWindow(sHndlWinQyType, FALSE);
							EnableWindow(sHndlWinState, FALSE);
							EnableWindow(sHndlWinBuff, FALSE);
							EnableWindow(sHndlWinResume, FALSE);
							SendMessage(sHndlWinQyType, CB_SETCURSEL, (WPARAM) -1, (LPARAM)0);
							SendMessage(sHndlWinState, CB_SETCURSEL, (WPARAM) -1, (LPARAM)0);							
							//SendMessage(sHndlWinToolTip,  TTM_ACTIVATE, (WPARAM) FALSE, 0);
							
							switch(iComboIndex)
							{
								case 0:
									LoadString(vModHandle, IDS_COMMAND_CREATE, cTempBuff, 399);
									SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									return TRUE;
									break;

								case 1:
									LoadString(vModHandle, IDS_COMMAND_CONF, cTempBuff, 399);
									SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									return TRUE;
									break;

								case 2:
									LoadString(vModHandle, IDS_COMMAND_DELETE, cTempBuff, 399);
									SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									SendMessage(sHndlWinType,  CB_SETCURSEL, 0, 0);
									SendMessage(sHndlWinInteract,  CB_SETCURSEL, 0, 0);
									SendMessage(sHndlWinStart,  CB_SETCURSEL, 0, 0);
									SendMessage(sHndlWinError,  CB_SETCURSEL, 0, 0);
									SendMessage(sHndlWinPathBin,  WM_SETTEXT, 0, (LPARAM) "");
									SendMessage(sHndlWinGroup,  WM_SETTEXT, 0, (LPARAM) "");
									SendMessage(sHndlWinTag,  CB_SETCURSEL, 0, 0);
									SendMessage(sHndlWinDepend,  WM_SETTEXT, 0, (LPARAM) "");
									SendMessage(sHndlWinAccName,  WM_SETTEXT, 0, (LPARAM) "");
									SendMessage(sHndlWinObjName,  WM_SETTEXT, 0, (LPARAM) "");
									SendMessage(sHndlWinDispName,  WM_SETTEXT, 0, (LPARAM) "");
									SendMessage(sHndlWinPW,  WM_SETTEXT, 0, (LPARAM) "");
									EnableWindow(sHndlWinType, FALSE);
									EnableWindow(sHndlWinInteract, FALSE);
									EnableWindow(sHndlWinStart, FALSE);
									EnableWindow(sHndlWinError, FALSE);
									EnableWindow(sHndlWinPathBin, FALSE);
									EnableWindow(sHndlWinGroup, FALSE);
									EnableWindow(sHndlWinTag, FALSE);
									EnableWindow(sHndlWinDepend, FALSE);
									EnableWindow(sHndlWinAccName, FALSE);
									EnableWindow(sHndlWinObjName, FALSE);
									EnableWindow(sHndlWinDispName, FALSE);
									EnableWindow(sHndlWinPW, FALSE);																	
									return TRUE;
									break;

								case 3:
									LoadString(vModHandle, IDS_COMMAND_QUERY, cTempBuff, 399);
									SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									SendMessage(sHndlWinStart,  CB_SETCURSEL, 0, 0);
									SendMessage(sHndlWinError,  CB_SETCURSEL, 0, 0);
									SendMessage(sHndlWinPathBin,  WM_SETTEXT, 0, (LPARAM) "");
									SendMessage(sHndlWinTag,  CB_SETCURSEL, 0, 0);
									SendMessage(sHndlWinDepend,  WM_SETTEXT, 0, (LPARAM) "");
									SendMessage(sHndlWinAccName,  WM_SETTEXT, 0, (LPARAM) "");
									SendMessage(sHndlWinObjName,  WM_SETTEXT, 0, (LPARAM) "");
									SendMessage(sHndlWinDispName,  WM_SETTEXT, 0, (LPARAM) "");
									SendMessage(sHndlWinPW,  WM_SETTEXT, 0, (LPARAM) "");
									EnableWindow(sHndlWinStart, FALSE);
									EnableWindow(sHndlWinError, FALSE);
									EnableWindow(sHndlWinPathBin, FALSE);
									EnableWindow(sHndlWinTag, FALSE);
									EnableWindow(sHndlWinDepend, FALSE);
									EnableWindow(sHndlWinAccName, FALSE);
									EnableWindow(sHndlWinObjName, FALSE);
									EnableWindow(sHndlWinDispName, FALSE);
									EnableWindow(sHndlWinPW, FALSE);
									EnableWindow(sHndlWinQyType, TRUE);									
									EnableWindow(sHndlWinState, TRUE);									
									EnableWindow(sHndlWinBuff, TRUE);
									EnableWindow(sHndlWinResume, TRUE);
									SendMessage(sHndlWinQyType, CB_SETCURSEL, (WPARAM) 0, (LPARAM)0);
									SendMessage(sHndlWinState, CB_SETCURSEL, (WPARAM) 0, (LPARAM)0);

									return TRUE;
									break;
							}							
							break;
					}
					break;
				
				case IDC_EDIT_SVRNAME:
					switch(HIWORD (wParam))
					{
						case EN_SETFOCUS:
							LoadString(vModHandle, IDS_SVRNAME, cTempBuff, 399);
							SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
							return TRUE;
							break;
					}
					break;

				case IDC_EDIT_SVCNAME:
					switch(HIWORD (wParam))
					{
						case EN_SETFOCUS:
							LoadString(vModHandle, IDS_SVCNAME, cTempBuff, 399);
							SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
							return TRUE;
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
									SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) "Exclude this paramater (Type)");
									SendMessage(sHndlWinInteract, CB_SETCURSEL, (WPARAM) -1, (LPARAM)0);
									EnableWindow(sHndlWinInteract, FALSE);
									return TRUE;
									break;

								case 1:
									LoadString(vModHandle, IDS_TYPE_OWN, cTempBuff, 399);
									SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									SendMessage(sHndlWinInteract, CB_SETCURSEL, (WPARAM) -1, (LPARAM)0);
									EnableWindow(sHndlWinInteract, FALSE);
									return TRUE;
									break;

								case 2:
									LoadString(vModHandle, IDS_TYPE_SHARE, cTempBuff, 399);
									SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									SendMessage(sHndlWinInteract, CB_SETCURSEL, (WPARAM) -1, (LPARAM)0);
									EnableWindow(sHndlWinInteract, FALSE);
									return TRUE;
									break;

								case 3:
									LoadString(vModHandle, IDS_TYPE_KERNEL, cTempBuff, 399);
									SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									SendMessage(sHndlWinInteract, CB_SETCURSEL, (WPARAM) -1, (LPARAM)0);
									EnableWindow(sHndlWinInteract, FALSE);
									return TRUE;
									break;

								case 4:
									LoadString(vModHandle, IDS_TYPE_FILSYS, cTempBuff, 399);
									SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									SendMessage(sHndlWinInteract, CB_SETCURSEL, (WPARAM) -1, (LPARAM)0);
									EnableWindow(sHndlWinInteract, FALSE);
									return TRUE;
									break;

								case 5:
									LoadString(vModHandle, IDS_TYPE_REC, cTempBuff, 399);
									SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									SendMessage(sHndlWinInteract, CB_SETCURSEL, (WPARAM) -1, (LPARAM)0);
									EnableWindow(sHndlWinInteract, FALSE);
									return TRUE;
									break;

								case 6:
									LoadString(vModHandle, IDS_TYPE_INTERACT, cTempBuff, 399);
									SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									EnableWindow(sHndlWinInteract, TRUE);
									SendMessage(sHndlWinInteract, CB_SETCURSEL, (WPARAM) 0, (LPARAM)0);
									//SendMessage(sHndlWinToolTip,  TTM_ACTIVATE, (WPARAM) TRUE, 0);								
									return TRUE;
									break;
							}							
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
										LoadString(vModHandle, IDS_INTERACT_OWN, cTempBuff, 399);
										SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										return TRUE;
										break;

									case 1:
										LoadString(vModHandle, IDS_INTERACT_SHARE, cTempBuff, 399);
										SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										return TRUE;
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
									SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) "Exclude this paramater (Start)");
									return TRUE;
									break;

								case 1:
									LoadString(vModHandle, IDS_START_BOOT, cTempBuff, 399);
									SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									return TRUE;
									break;

								case 2:
									LoadString(vModHandle, IDS_START_SYSTEM, cTempBuff, 399);
									SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									return TRUE;
									break;

								case 3:
									LoadString(vModHandle, IDS_START_AUTO, cTempBuff, 399);
									SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									return TRUE;
									break;

								case 4:
									LoadString(vModHandle, IDS_START_DEMAND, cTempBuff, 399);
									SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									return TRUE;
									break;

								case 5:
									LoadString(vModHandle, IDS_START_DISABLED, cTempBuff, 399);
									SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									return TRUE;
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
									SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) "Exclude this paramater (Error)");
									return TRUE;
									break;

								case 1:
									LoadString(vModHandle, IDS_ERROR_NORMAL, cTempBuff, 399);
									SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									return TRUE;
									break;

								case 2:
									LoadString(vModHandle, IDS_ERROR_SEVERE, cTempBuff, 399);
									SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									return TRUE;
									break;

								case 3:
									LoadString(vModHandle, IDS_ERROR_CRITICAL, cTempBuff, 399);
									SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									return TRUE;
									break;

								case 4:
									LoadString(vModHandle, IDS_ERROR_IGNORE, cTempBuff, 399);
									SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
									return TRUE;
									break;

							}							
							break;
					}
					break;

					case IDC_EDIT_PATHBIN:
						switch(HIWORD (wParam))
						{
							case EN_SETFOCUS:
								LoadString(vModHandle, IDS_PATHBIN, cTempBuff, 399);
								SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
								return TRUE;
								break;
						}
						break;

					case IDC_EDIT_GROUP:
						switch(HIWORD (wParam))
						{
							case EN_SETFOCUS:
								LoadString(vModHandle, IDS_GROUP, cTempBuff, 399);
								SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
								return TRUE;
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
										SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) "Exclude this paramater (Tag)");
										return TRUE;
										break;

									case 1:
										LoadString(vModHandle, IDS_TAG_YES, cTempBuff, 399);
										SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										return TRUE;
										break;

									case 2:
										LoadString(vModHandle, IDS_TAG_NO, cTempBuff, 399);
										SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										return TRUE;
										break;

								}							
								break;
						}
						break;

					case IDC_EDIT_DEPEND:
						switch(HIWORD (wParam))
						{
							case EN_SETFOCUS:
								LoadString(vModHandle, IDS_DEPEND, cTempBuff, 399);
								SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
								return TRUE;
								break;
						}
						break;

					case IDC_EDIT_ACCNAME:
						switch(HIWORD (wParam))
						{
							case EN_SETFOCUS:
								LoadString(vModHandle, IDS_ACCNAME, cTempBuff, 399);
								SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
								SendMessage(sHndlWinAccName,  EM_SHOWBALLOONTIP, 0, (LPARAM) &sTipAcc);
								return TRUE;
								break;
							case EN_CHANGE:
								if(SendMessage(sHndlWinAccName,  WM_GETTEXTLENGTH, 0, 0) > 0)
								{
									SendMessage(sHndlWinObjName,  WM_SETTEXT, 0, (LPARAM) "");
									EnableWindow(sHndlWinObjName, FALSE);
								}
								else
								{
									EnableWindow(sHndlWinObjName, TRUE);
								}
								return TRUE;
								break;
						}
						break;

					case IDC_EDIT_OBJNAME:
						switch(HIWORD (wParam))
						{
							case EN_SETFOCUS:
								LoadString(vModHandle, IDS_OBJNAME, cTempBuff, 399);
								SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
								SendMessage(sHndlWinObjName,  EM_SHOWBALLOONTIP, 0, (LPARAM) &sTipAcc);
								return TRUE;
								break;
							case EN_CHANGE:
								if(SendMessage(sHndlWinObjName,  WM_GETTEXTLENGTH, 0, 0) > 0)
								{
									SendMessage(sHndlWinAccName,  WM_SETTEXT, 0, (LPARAM) "");
									EnableWindow(sHndlWinAccName, FALSE);
								}
								else
								{
									EnableWindow(sHndlWinAccName, TRUE);
								}
								return TRUE;
								break;
						}
						break;

					case IDC_EDIT_DISPNAME:
						switch(HIWORD (wParam))
						{
							case EN_SETFOCUS:
								LoadString(vModHandle, IDS_DISPNAME, cTempBuff, 399);
								SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
								return TRUE;
								break;
						}
						break;

					case IDC_EDIT_PW:
						switch(HIWORD (wParam))
						{
							case EN_SETFOCUS:
								LoadString(vModHandle, IDS_PW, cTempBuff, 399);
								SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
								return TRUE;
								break;
						}
						break;

					case IDC_EDIT_CMDLINE:
						switch(HIWORD (wParam))
						{
							case EN_SETFOCUS:
								LoadString(vModHandle, IDS_CMDLINE, cTempBuff, 399);
								SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
								return TRUE;
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
										LoadString(vModHandle, IDS_QYTYPE_SERVICE, cTempBuff, 399);
										SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										return TRUE;
										break;

									case 1:
										LoadString(vModHandle, IDS_QYTYPE_DRIVER, cTempBuff, 399);
										SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										return TRUE;
										break;

									case 2:
										LoadString(vModHandle, IDS_QYTYPE_ALL, cTempBuff, 399);
										SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										return TRUE;
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
										LoadString(vModHandle, IDS_STATE_ACTIVE, cTempBuff, 399);
										SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										return TRUE;
										break;

									case 1:
										LoadString(vModHandle, IDS_STATE_INACTIVE, cTempBuff, 399);
										SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										return TRUE;
										break;

									case 2:
										LoadString(vModHandle, IDS_STATE_ALL, cTempBuff, 399);
										SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
										return TRUE;
										break;

								}							
								break;
						}
						break;

				case IDC_EDIT_BUFF:
						switch(HIWORD (wParam))
						{
							case EN_SETFOCUS:
								LoadString(vModHandle, IDS_BUFF, cTempBuff, 399);
								SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
								return TRUE;
								break;
						}
						break;

				case IDC_EDIT_RESUME:
						switch(HIWORD (wParam))
						{
							case EN_SETFOCUS:
								LoadString(vModHandle, IDS_RESUME, cTempBuff, 399);
								SendMessage(sHndlWinDesc,  WM_SETTEXT, 0, (LPARAM) cTempBuff);
								return TRUE;
								break;
						}
						break;					

			}

		default:
			return DefWindowProc(sHdlWinMain, sMsg, wParam, lParam);
	}

	return DefWindowProc(sHdlWinMain, sMsg, wParam, lParam);
}

BOOL CALLBACK AboutDlgProc(HWND sHdlWinMain, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
		case WM_INITDIALOG:
			return TRUE;
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
			EndDialog(sHdlWinMain, Message);
			break;

		case WM_DESTROY:
			EndDialog(sHdlWinMain, Message);
			break;

		case WM_COMMAND: //no other controls on this dialog window
			break;

		default:
			return FALSE;
	}
	return TRUE;
}