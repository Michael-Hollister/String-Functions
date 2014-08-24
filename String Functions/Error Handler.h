/*******************************************************************
* Copyright (c) 2012, Michael Hollister                            *
*                                                                  *
* This source code is subject to the terms of The MIT License.     *
* If a copy of The MIT License was not distributed with this file, *
* you can obtain one at http://opensource.org/licenses/MIT.        *
*******************************************************************/

#pragma once
#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include "stdafx.h"
#include <string>


// Using directives
using namespace std;

namespace DBPro
{
	class ErrorHandler
	{
	public:
		// Enums	
		enum SFErrorCodes
		{
			NULLERROR = 0,MUSTBEPOSITIVEVALUE = 200,INDEXOUTOFRANGE,UNKNOWNBOOLSTRING,NONBOOLEANVALUE,ARRAYNOTSTRING,PATH_INVALIDCHARS,PATH_MAXPATH,
			PATH_RESERVEDNAME,REGEX_INVALIDEXPRESSION,REGEX_MATCHINDEXOUTOFBOUNDS,UNKNOWNERROR
		};

		// Functions
		static void ThrowError( SFErrorCodes ErrorCode, LPCTSTR Title, string Message );

	private:
		// Classes
		// Runtime Error Handler Class
		class CRuntimeErrorHandler
		{
			public:
				DWORD dwErrorCode;
		};

		// Variables
		static HHOOK hhookErrorHook;
		static SFErrorCodes ErrorCode;
		static LPCSTR pszTitle;
		static string strFormatedMessage;
		static string strMessage;

		// Functions
		static LRESULT CALLBACK SetMessageBoxInfo( int nCode, WPARAM wParam, LPARAM lParam );
		static BOOL CALLBACK EnumChildProc( HWND hwnd, LPARAM lParam );
		
	};
}

#endif // ERROR_HANDLER_H


