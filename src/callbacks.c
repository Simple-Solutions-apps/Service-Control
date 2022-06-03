/*-------------------------------------------
  Copyright Simple Solutions, 2022
  Revised: 2022/05/30 09:36
-------------------------------------------*/

//standard includes
#include <windows.h>
#include <commctrl.h>
#include <fileapi.h>

//custom includes
#include "..\include\resource.h"
#include "..\include\controls.h"
#include "..\include\callbacks.h"

//globals

//declarations
HWND sDlgToolbar;
HWND sDlgLogIn;
HGLOBAL sSelectedlist;

UINT iReturn;
int *iListItems;
LPCSTR cFileSaved[MAX_PATH];
LPCSTR cFileCurrent[MAX_PATH];
BOOL bFileModified = FALSE;


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_CREATE:
			{				
				CreateControls(hwnd); //function to create all controls. Review controls.h and controls.c
			}	
			break;

		case WM_SIZE:

			break;
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_COMMAND:
			switch(LOWORD(wParam))
				{	
					//main menu cases defined in resource.h					
					case IDMI_MAINMENU_FILE_EXIT:
						PostQuitMessage(0);
						break;

					case IDMI_MAINMENU_FILE_MIN:
						ShowWindow(hwnd, SW_MINIMIZE);
						break;
					
					case IDMI_MAINMENU_HELP_ABOUT:
						//this is a Model dialog box creation (execution stops for everything else)					
						iReturn = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUT), hwnd, (DLGPROC) AboutDlgProc);

						if(iReturn == IDOK)
						{
							MessageBox(hwnd, "Dialog exited with IDOK.", "Notice", MB_OK | MB_ICONINFORMATION);
						}
						else if(iReturn == IDCANCEL)
						{
							MessageBox(hwnd, "Dialog exited with IDCANCEL.", "Notice", MB_OK | MB_ICONINFORMATION);
						}
						else if(iReturn == -1)
						{
							MessageBox(hwnd, "Dialog failed!", "Error", MB_OK | MB_ICONINFORMATION);
						}
						break;

					case IDC_MAIN_TOOLBAR_FILE_OPEN:

						break;
					case IDC_MAIN_TOOLBAR_FILE_SAVEAS:

						break;					
				}
				break;
				//Other menu commands...
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
		case WM_INITDIALOG:
			return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDOK:
					EndDialog(hwnd, IDOK);
					break;
				case IDCANCEL:
					EndDialog(hwnd, IDCANCEL);
					break;
			}
			break;
		default:
			return FALSE;
	}
	return TRUE;
}

BOOL CALLBACK AuthDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
		case WM_CLOSE:
			EndDialog(hwnd, Message);
			break;

		case WM_DESTROY:
			EndDialog(hwnd, Message);
			break;

		case WM_INITDIALOG:
			return TRUE;

		case WM_COMMAND:
			switch(LOWORD(wParam))				
			break;

		default:
			return FALSE;
	}
	return TRUE;
}