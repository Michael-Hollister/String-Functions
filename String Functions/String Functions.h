/*******************************************************************
* Copyright (c) 2012, Michael Hollister                            *
*                                                                  *
* This source code is subject to the terms of The MIT License.     *
* If a copy of The MIT License was not distributed with this file, *
* you can obtain one at http://opensource.org/licenses/MIT.        *
*******************************************************************/

#pragma once
#ifndef STRING_FUNCTIONS_H
#define STRING_FUNCTIONS_H


// Includes
#include "stdafx.h"
#include "resource.h"
#include "Error Handler.h"
#include <DBPro.hpp>
#include <string>
#include <vector>
#include <map>
#include <boost\lexical_cast.hpp>
#include <boost\regex.hpp> // Using boost regex as of the moment it can compile regex strings that tr1 version can't.


//Function prototypes

///////////////////////
//  SF Is Functions  //
///////////////////////
EXPORTC DWORD Contains( const char* pszString, const char* pszSubStr );
EXPORTC DWORD Is_Alpha( const char* pszString, int nIndex );
EXPORTC DWORD Is_AlNum( const char* pszString, int nIndex );
EXPORTC DWORD Is_Digit( const char* pszString, int nIndex );
EXPORTC DWORD Is_Lower( const char* pszString, int nIndex );
EXPORTC DWORD Is_Punct( const char* pszString, int nIndex );
EXPORTC DWORD Is_Space( const char* pszString, int nIndex );
EXPORTC DWORD Is_Upper( const char* pszString, int nIndex );
EXPORTC DWORD Is_XDigit( const char* pszString, int nIndex );


///////////////////////
// SF Misc Functions //
///////////////////////
EXPORTC char* Bool_To_Str( const char* pszOldString, DWORD bvalue );
EXPORTC char* Mixedcase( const char* pszOldString, char* pszString, DWORD bConvertType );
EXPORT void SplitStrToArray( DWORD* pnArrayPtr, const char* pszString, const char* pszDelimiter );
EXPORT void SplitStrToArray( DWORD* pnArrayPtr, const char* pszString, const char* pszDelimiter, DWORD bRemoveEmptyStrings );
EXPORTC DWORD Str_To_Bool( char* pszString );
EXPORTC int String_Distance( const char* pszString1, const char* pszString2 );
EXPORTC void ToCharArray( DWORD* pnArrayPtr, const char* pszString );

///////////////////////
// SF Path Functions //
///////////////////////
EXPORT char* Path_GetFileName( const char* pszOldString, const char* pszString );
EXPORT char* Path_GetFileName( const char* pszOldString, const char* pszString, DWORD bReturnExtension );
EXPORTC char* Path_ChangeFileExtension( const char* pszOldString, const char* pszString, const char* pszNewExtension );
EXPORTC char* Path_GetFileExtension( const char* pszOldString, const char* pszString );
EXPORTC char* Path_GetParent( const char* pszOldString, const char* pszString );
EXPORTC char* Path_GetParentName( const char* pszOldString, const char* pszString );
EXPORTC char* Path_GetPathRoot( const char* pszOldString, const char* pszString );
EXPORTC DWORD Path_HasExtension( const char* pszString );
EXPORTC int Path_Valid( const char* pszString );

////////////////////////
// SF RegEx Functions //
////////////////////////

EXPORTC int RegEx_GetMatchCount();
EXPORTC int RegEx_GetMatchPosition( int nIndex );
EXPORTC char* RegEx_GetMatchStr( const char* pszOldString, int nIndex );
EXPORTC DWORD RegEx_IsMatch( const char* pszString, const char* pszPattern );
EXPORTC DWORD RegEx_IsPartialMatch( const char* pszString, const char* pszPattern );
EXPORTC int RegEx_Match( const char* pszString, const char* pszPattern );
EXPORTC char* RegEx_Replace( const char* pszOldString, const char* pszString, const char* pszPattern, const char* pszFormatter );


//EXPORTC DWORD RegEx_Split( const char* pszString, const char* pszPattern  );

//EXPORTC DWORD RegEx_SetDefaultSyntaxFlags();



// Using directives
using namespace std;


//Enum Declarations
enum ReservedPathNames
{
	VALIDNAME,CON,PRN,AUX,NUL,COM1,COM2,COM3,COM4,COM5,COM6,COM7,COM8,COM9,LPT1,LPT2,LPT3,LPT4,LPT5,LPT6,LPT7,LPT8,LPT9
};

// Structs
struct RegExInfo
{
	int nPosition;
	string strMatch;

};

// Global Declrations
map<string,ReservedPathNames> Path_ReservedFileNames;
boost::regex RegEx;
vector<RegExInfo> RegEx_UserMatches;

//////////////////////////////
//  Non Exported Functions  //
//////////////////////////////

void SF_Init()
{
	// Populate map to associate the string value to the enumeration.
	Path_ReservedFileNames["con"] = ReservedPathNames::CON;
	Path_ReservedFileNames["prn"] = ReservedPathNames::PRN;
	Path_ReservedFileNames["aux"] = ReservedPathNames::AUX;
	Path_ReservedFileNames["nul"] = ReservedPathNames::NUL;
	Path_ReservedFileNames["com1"] = ReservedPathNames::COM1;
	Path_ReservedFileNames["com2"] = ReservedPathNames::COM2;
	Path_ReservedFileNames["com3"] = ReservedPathNames::COM3;
	Path_ReservedFileNames["com4"] = ReservedPathNames::COM4;
	Path_ReservedFileNames["com5"] = ReservedPathNames::COM5;
	Path_ReservedFileNames["com6"] = ReservedPathNames::COM6;
	Path_ReservedFileNames["com7"] = ReservedPathNames::COM7;
	Path_ReservedFileNames["com8"] = ReservedPathNames::COM8;
	Path_ReservedFileNames["com9"] = ReservedPathNames::COM9;
	Path_ReservedFileNames["lpt1"] = ReservedPathNames::LPT1;
	Path_ReservedFileNames["lpt2"] = ReservedPathNames::LPT2;
	Path_ReservedFileNames["lpt3"] = ReservedPathNames::LPT3;
	Path_ReservedFileNames["lpt4"] = ReservedPathNames::LPT4;
	Path_ReservedFileNames["lpt5"] = ReservedPathNames::LPT5;
	Path_ReservedFileNames["lpt6"] = ReservedPathNames::LPT6;
	Path_ReservedFileNames["lpt7"] = ReservedPathNames::LPT7;
	Path_ReservedFileNames["lpt8"] = ReservedPathNames::LPT8;
	Path_ReservedFileNames["lpt9"] = ReservedPathNames::LPT9;

	// Initialize regex resources.
	//boost::regex RegEx();
	//boost::regex_constants::awk
}

// These functions find the index of a slash char ('/' or '\')
int inline Path_FindSlashes( string strPath, int nIndex )
{
	for(int x = nIndex; x < strPath.length(); ++x)
	{
		switch(strPath[x])
		{
		case '/':
		case '\\':
			return x;
			break;
		}
	}
	
	// Reutrn npos if can't find any slashes.
	return strPath.npos;
}
int inline Path_FindSlashes( string strPath )
{
	return Path_FindSlashes(strPath,0);
}
int inline Path_RFindSlashes( string strPath, int nIndex )
{
	for(int x = nIndex; x > -1; --x)
	{
		switch(strPath[x])
		{
		case '/':
		case '\\':
			return x;
			break;
		}
	}
	
	// Reutrn npos if can't find any slashes.
	return strPath.npos;
}
int inline Path_RFindSlashes( string strPath )
{
	return Path_RFindSlashes(strPath,strPath.length());
}

// Checks the string to see if it is not null or a null pointer.
bool inline ValidateString( const char* pszString )
{
	if( !pszString || !*pszString )
		return false;
	return true;
}
// Checks the string to see if the path has invalid characters or if the length is above MAX_PATH
bool inline ValidatePath( const char* pszString )
{
	int PathValidResult = Path_Valid(pszString);
	if(PathValidResult != true)
	{
		switch(PathValidResult)
		{
		//case ERRORCODE_PATH_NULLPATH: (case does not need to be handled...)
		case ERRORCODE_PATH_INVALIDCHARS:
			DBPro::ErrorHandler::ThrowError(DBPro::ErrorHandler::PATH_INVALIDCHARS,ERROR_TITLE,ERROR_PATH_INVALIDCHARS);
			break;
		case ERRORCODE_PATH_MAXPATH:
			DBPro::ErrorHandler::ThrowError(DBPro::ErrorHandler::PATH_MAXPATH,ERROR_TITLE,ERROR_PATH_MAXPATH);
			break;
		case ERRORCODE_PATH_RESERVEDNAME:
			DBPro::ErrorHandler::ThrowError(DBPro::ErrorHandler::PATH_RESERVEDNAME,ERROR_TITLE,ERROR_PATH_RESERVEDNAME);
			break;
		}
	}
	return true;
}
// Checks the string to see if the index where the '.' is a valid file extension.
bool inline ValidateFileExtension( string strPath, int nIndex )
{
	// Return false if the char index is not a '.'
	if(strPath[nIndex] != '.')
		return false;
	else
	{
		// If a '/' or '\' char is before the '.', then there is no file extension.
		if(Path_RFindSlashes(strPath) > nIndex)
			return false;
		else
			return true;
	}
}
// Checks the string to make sure the index is inside the bounds of the array.
bool IndexValid( const char* pszString, int nIndex )
{
	// Make sure the position is not a invalid index.
	if (nIndex < 1 || nIndex > strlen(pszString))
		if(nIndex < 1)
			DBPro::ErrorHandler::ThrowError(DBPro::ErrorHandler::MUSTBEPOSITIVEVALUE,ERROR_TITLE,ERROR_MUSTBEPOSITIVEVALUE);
		else
			DBPro::ErrorHandler::ThrowError(DBPro::ErrorHandler::INDEXOUTOFRANGE,ERROR_TITLE,ERROR_INDEXOUTOFRANGE);
	return true;
}
// Checks to see if the path strings has a file extesion but without validtating the path string.  (used when called from Path_Valid function)
int Path_HasExtensionNoValidate( const char* pszString )
{
	// Make sure string is not null, is not a null pointer.
	if(!ValidateString(pszString))
		return NULL;

	string strTemp = pszString;
		
	if(ValidateFileExtension(pszString,strTemp.rfind('.')))
		return true;
	else
		return false;
}


#endif //STRING_FUNCTIONS_H
