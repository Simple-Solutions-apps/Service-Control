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

//declare globals
BOOL iReturn;
HMODULE vModHandle;
LOGFONT sFontAttributes;
NONCLIENTMETRICS sFontMetrics;
HFONT sFontMainWindow;
BOOL iResult;

//main window callback procedure
LRESULT CALLBACK WndProc(HWND sHdlWinMain, UINT sMsg, WPARAM wParam, LPARAM lParam)
{
	//define handle to this module/executable
	vModHandle = GetModuleHandle(NULL);

	switch(sMsg)
		{
			case WM_CREATE:
				/*
				//set the the correct size of font metrics structure
				sFontMetrics.cbSize = sizeof(NONCLIENTMETRICS);

				//attempt to retrieve sysytem font
				iResult = (BOOL) SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof (NONCLIENTMETRICS), &sFontMetrics, 0);

				//verify the font metrics was retrieved successfully
				if(iResult == 0)
				{
					MessageBox(sHdlWinMain, "unable to retrieve font metrics", "Font metrics error", MB_ICONINFORMATION | MB_OK);
				}

				//sFontMainWindow = (HFONT) ;
				*/

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
				switch(LOWORD(wParam))
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
						iReturn = DialogBox(vModHandle, MAKEINTRESOURCE(IDD_ABOUT), sHdlWinMain, (DLGPROC) AboutDlgProc);
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