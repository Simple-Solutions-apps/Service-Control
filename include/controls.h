//File containing contol reladed definitions and function prototypes

//conditional header guard wrapper to avoid proccesing more than once
#ifndef CONTROLLS_H
	#define CONTROLLS_H

	//Controls
	#define IDC_GRPBOX_PARAMS 1036
	#define IDC_GRPBOX_CMDLINE 1037

	#define IDC_LABEL_COMMAND 1001
	#define IDC_LABEL_SVRNAME 1002
	#define IDC_LABEL_SVCNAME 1003
	#define IDC_LABEL_TYPE 1004
	#define IDC_LABEL_INTERACT 1005
	#define IDC_LABEL_START 1006
	#define IDC_LABEL_ERROR 1007
	#define IDC_LABEL_PATHBIN 1008
	#define IDC_LABEL_GROUP 1009
	#define IDC_LABEL_TAG 1010
	#define IDC_LABEL_DEPEND 1011
	#define IDC_LABEL_ACCNAME 1012
	#define IDC_LABEL_OBJNAME 1013
	#define IDC_LABEL_DISPNAME 1014
	#define IDC_LABEL_PW 1015
	#define IDC_LABEL_CMDLINE 1038

	#define IDC_BTN_BROWSE 1016
	#define IDC_BTN_CMDRUN 1038

	#define IDC_COMBO_COMMAND 1017
	#define IDC_COMBO_TYPE 1018
	#define IDC_COMBO_INTERACT 1019
	#define IDC_COMBO_START 1020
	#define IDC_COMBO_ERROR 1021
	#define IDC_COMBO_TAG 1022

	#define IDC_EDIT_SVRNAME 1023
	#define IDC_EDIT_SVCNAME 1024
	#define IDC_EDIT_PATHBIN 1025
	#define IDC_EDIT_GROUP 1026
	#define IDC_EDIT_DEPEND 1027
	#define IDC_EDIT_ACCNAME 1028
	#define IDC_EDIT_OBJNAME 1029
	#define IDC_EDIT_DISPNAME 1030
	#define IDC_EDIT_PW 1031
	#define IDC_EDIT_CMDLINE 1039

	
	//Command IDs for tool bar
	#define IDC_MAIN_TOOLBAR_FILE_NEW 1032
	#define IDC_MAIN_TOOLBAR_FILE_OPEN 1033
	#define IDC_MAIN_TOOLBAR_FILE_SAVEAS 1034
	#define IDC_MAIN_TOOLBAR 1035

	//prototypes
	void CreateControls(HWND hwnd);

//end of wrapper
#endif