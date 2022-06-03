/*-------------------------------------------
  Copyright Simple Solutions, 2022
  Revised: 2022/05/26 22:05
-------------------------------------------*/

//standard includes
#include <windows.h>
#include <commctrl.h>

//Custom includes
#include "..\include\resource.h"
#include "..\include\callbacks.h"

//declare & define window class name
const char cWindowClassName[] = "CSGUI";

//Window width and height definitions
#define WIN_WIDTH 870
#define WIN_HEIGHT 700


//windows main application entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{	
	//declarations
	WNDCLASSEX sWinClass;
	MSG sMsg;
	HBRUSH sBrush;
	INITCOMMONCONTROLSEX sIcex;

	HWND hWnd; //main window handle

	HANDLE vModHandle = GetModuleHandle(NULL);

	//definitions
	sBrush = CreateSolidBrush(RGB(242, 242, 242)); //nice light gey color	

	//assign window class structure
	sWinClass.cbSize = sizeof (WNDCLASSEX);
	sWinClass.style = 0;
	sWinClass.lpfnWndProc = WndProc;
	sWinClass.cbClsExtra = 0;
	sWinClass.cbWndExtra = 0;
	sWinClass.hInstance = hInstance;
	sWinClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	sWinClass.hbrBackground = sBrush;
	sWinClass.lpszClassName = cWindowClassName;
	sWinClass.hIcon = LoadIcon(vModHandle, MAKEINTRESOURCE(IDI_APPICON));
	sWinClass.hIconSm = (HICON)LoadImage(vModHandle, MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON, 16, 16, 0);
	sWinClass.lpszMenuName = MAKEINTRESOURCE(IDM_MAINMENU);

	//assign common controls initialization structure
	sIcex.dwSize = sizeof (INITCOMMONCONTROLSEX);
	sIcex.dwICC = ICC_STANDARD_CLASSES;

	//calculate window center
	RECT sRect;
	GetClientRect(GetDesktopWindow(), &sRect);
	sRect.left = (sRect.right / 2) - (WIN_WIDTH / 2);
	sRect.top = (sRect.bottom / 2) - (WIN_HEIGHT / 2)  - 20;

	//initiate common controls libary >V6.00 (commctrl32.dll) for modern visual styles should be located in ..\\lib folder

	//verify that common controls were initiated for modern visual styles correctly
	if(InitCommonControlsEx(&sIcex) == FALSE)
	{
		MessageBox(NULL, "Standard classes could not be loaded", "Common controls", MB_ICONINFORMATION | MB_OK);
	}

	//register main window class
	if(!RegisterClassEx(&sWinClass))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONERROR | MB_OK);
		return __LINE__;
	}

	//assign window handler (create window)
	hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, cWindowClassName, "Services Control", WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
	sRect.left, sRect.top, WIN_WIDTH, WIN_HEIGHT, NULL, NULL, hInstance, NULL); 

	//verify window has been created correctly if not bail
	if(hWnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return __LINE__;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//main window nervous system
	while(GetMessage(&sMsg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&sMsg);
		DispatchMessage(&sMsg);
	}
	
	return sMsg.wParam;
}