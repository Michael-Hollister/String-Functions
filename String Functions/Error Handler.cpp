
// Includes
#include "stdafx.h"
#include "resource.h"
#include "Error Handler.h"
#include <DBPro.hpp>
#include <string>
#include <boost\lexical_cast.hpp>

// Static class member declrations 
HHOOK DBPro::ErrorHandler::hhookErrorHook = NULL;
DBPro::ErrorHandler::SFErrorCodes DBPro::ErrorHandler::ErrorCode = DBPro::ErrorHandler::NULLERROR;
LPCSTR DBPro::ErrorHandler::pszTitle = NULL;
string DBPro::ErrorHandler::strFormatedMessage;
string DBPro::ErrorHandler::strMessage;


// Class Implementation
void DBPro::ErrorHandler::ThrowError( DBPro::ErrorHandler::SFErrorCodes ErrorCode, LPCTSTR Title, string Message )
{
	// Save the prameters in the class for later use.
	DBPro::ErrorHandler::pszTitle = Title;
	DBPro::ErrorHandler::strMessage = Message;
	DBPro::ErrorHandler::ErrorCode = ErrorCode;

	// Raise the error and then modify the text.
	((CRuntimeErrorHandler*)DBPro::Core->g_pErrorHandlerRef)->dwErrorCode = ErrorCode;
	
	// Install the hook.
	hhookErrorHook = SetWindowsHookEx(WH_CBT,SetMessageBoxInfo,NULL,GetWindowThreadProcessId(DBPro::Core->hWnd,NULL));
}
LRESULT CALLBACK DBPro::ErrorHandler::SetMessageBoxInfo( int nCode, WPARAM wParam, LPARAM lParam )
{
	// Since everything is not created at the time of HCBT_CREATEWND nCode, this has to be done upon activation phase.
	if(nCode == HCBT_ACTIVATE)
	{
		// Make sure the handle belongs to the DBPro window.
		if(wParam != NULL && IsWindow((HWND)wParam) && GetParent((HWND)wParam) == DBPro::Core->hWnd)
		{
			// If the error tile is the default title "Error", then set it to the new title.  Else use the user defined error title.
			LPCSTR pszMsgboxTitle[512];
			GetWindowText((HWND)wParam,(LPSTR)pszMsgboxTitle,512);

			if(!strcmp((LPCSTR)pszMsgboxTitle,"Error") == 0)
				pszTitle = (LPCSTR)pszMsgboxTitle;
			
			// Get the line which the error ocurred at to store for the Message.
			EnumChildWindows((HWND)wParam,EnumChildProc,NULL);

			// Display messagebox.
			MessageBox(DBPro::Core->hWnd,strFormatedMessage.c_str(),pszTitle,MB_OK);

			// Clean up resources.
			DestroyWindow((HWND)wParam);
		}
	}
	
	return CallNextHookEx(hhookErrorHook, nCode, wParam, lParam);
}
BOOL CALLBACK DBPro::ErrorHandler::EnumChildProc( HWND hwnd, LPARAM lParam )
{
	// Find the label with the "Runtime Error" text.
	LPSTR pszClassNameBuffer[7]; 
	GetClassName(hwnd,(LPTSTR)pszClassNameBuffer,7);
	
	// If the window is the label with the error text, then get the text and show the new error message.
	if(strcmp((LPSTR)pszClassNameBuffer,"Static") == 0)
	{
		// Format the error text. (removing the text between "Runtime Error" and " at line xxx")
		LPSTR pszErrorString[100];
		GetWindowText(hwnd,(LPSTR)pszErrorString,100);
			
		strFormatedMessage = (LPSTR)pszErrorString;	

		// Insert the message between "Runtime Error" and "at line"
		strFormatedMessage = strFormatedMessage.substr(0,strFormatedMessage.find('-') + 1) + " " + strMessage + " " + // 0-14 = "Runtime Error 200 - "
		strFormatedMessage.substr(strFormatedMessage.find("at line"));

		// Clean up
		UnhookWindowsHookEx(hhookErrorHook);
		return false; 
	}	

	// Return true to keep enumerating to find the label.
	return true;
}

