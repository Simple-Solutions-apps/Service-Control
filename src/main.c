/*-------------------------------------------
  Copyright Simple Solutions, 2022
  Revised: 2022/05/26 22:05
-------------------------------------------*/

//standard includes
#include <windows.h>
#define _WIN32_ 0x0600 //
#include <commctrl.h>

//Custom includes
#include "..\include\resource.h"
#include "..\include\callbacks.h"

//Window width and height definitions
#define WIN_WIDTH 870
#define WIN_HEIGHT 700

//windows main application entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//declarations	
	WNDCLASSEX sWinClass;
	HWND sHdlWinMain;
	MSG sMsg;
	RECT sRect;
	HANDLE vHmodInst;
	INITCOMMONCONTROLSEX sInitCtrlEx;		

	//definitions

	//define handle to this module/executable
	vHmodInst = GetModuleHandle(NULL);

	//define window class name
	LPCWSTR cWindowClassName = TEXT("CmdAppGUI"); 

	//assign window class structure
	sWinClass.cbSize = sizeof (WNDCLASSEX);
	sWinClass.style = 0;
	sWinClass.lpfnWndProc = WndProc;
	sWinClass.cbClsExtra = 0;
	sWinClass.cbWndExtra = 0;
	sWinClass.hInstance = hInstance;
	sWinClass.hCursor = (HCURSOR) LoadCursor(NULL, IDC_ARROW);
	sWinClass.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
	sWinClass.lpszClassName = cWindowClassName;
	sWinClass.hIcon = (HICON) LoadImage(vHmodInst, MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON, 256, 256, 0);
	sWinClass.hIconSm = NULL;
	sWinClass.lpszMenuName = NULL;

	//attempt to register main window class
	if(!RegisterClassEx(&sWinClass))
	{
		MessageBox(NULL, TEXT("Main window Registration Failed!"),  TEXT("Error!"), MB_ICONEXCLAMATION | MB_OK);
		return __LINE__;
	}

	//attempt to get desktop rectangle
	if(GetClientRect(GetDesktopWindow(), &sRect) == FALSE)
	{
		//attempt to create the main window with default positioning coordinates
		sHdlWinMain = CreateWindowEx(WS_EX_CLIENTEDGE, cWindowClassName,  TEXT("Service Control"),
		WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, WIN_WIDTH, WIN_HEIGHT, NULL, NULL, hInstance, NULL);
	}
	else
	{
		//calculate window center
		sRect.left = (sRect.right / 2) - (WIN_WIDTH / 2);
		//sRect.top = (sRect.bottom / 2) - (WIN_HEIGHT / 2)  - 20; //-20 for task bar presumed to be at the bottom	
		sRect.top = 10;

		//attempt to create main window with centered positioning coordinates
		sHdlWinMain = CreateWindowEx(WS_EX_CLIENTEDGE, cWindowClassName,  TEXT("Service Control"),
		WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
		sRect.left, sRect.top, WIN_WIDTH, WIN_HEIGHT, NULL, NULL, hInstance, NULL);
	}

	//verify main window has been created correctly
	if(sHdlWinMain == NULL)
	{
		MessageBox(NULL,  TEXT("Main window creation failed"),  TEXT("Error"), MB_ICONEXCLAMATION | MB_OK);
		return __LINE__;
	}

	//initiate common controls libary > V6.00 (commctrl32.dll)
	//for modern visual styles, Should be located in ..\lib folder.
	sInitCtrlEx.dwSize = sizeof (INITCOMMONCONTROLSEX);
	sInitCtrlEx.dwICC = ICC_STANDARD_CLASSES;

	//verify that common controls for modern visual styles were initiated correctly
	if(InitCommonControlsEx(&sInitCtrlEx) == FALSE)
	{
		MessageBox(sHdlWinMain,  TEXT("Standard classes Not been loaded"),  TEXT("Common controls"), MB_ICONINFORMATION | MB_OK);
	}

	ShowWindow(sHdlWinMain, nCmdShow);
	UpdateWindow(sHdlWinMain);

	//main window nervous system
	while(GetMessage(&sMsg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&sMsg);
		DispatchMessage(&sMsg);
	}
	
	return sMsg.wParam;
}