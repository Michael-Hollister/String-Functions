/*******************************************************************
* Copyright (c) 2012, Michael Hollister                            *
*                                                                  *
* This source code is subject to the terms of The MIT License.     *
* If a copy of The MIT License was not distributed with this file, *
* you can obtain one at http://opensource.org/licenses/MIT.        *
*******************************************************************/

// String Functions.cpp : Defines the exported functions for the DLL application.
//
// Includes
#include "stdafx.h"
#include "resource.h"
#include "String Functions.h"
#include "Error Handler.h"
#include "Standard.h"
#include <string>
#include <vector>
#include <regex>
#include <DBPro.hpp>
#include <boost\lexical_cast.hpp>
#include <boost\algorithm\string.hpp>
#include <boost\regex.hpp> // Using boost regex as of the moment it can compile regex strings that tr1 version can't.

// below VERSION 4??
// look into regex groups...
// token iterator

// look into "StartsWith"
// get parent level ... name-path
// SF String_IsAnyOf
// combine array strings into path (combine)
//GetRandomFileName (creates a random name...) (also look into crypto services.. for the (.net for reference..))
// have commands to genereate random strings later on? (geneate alpha, generate alphanum, generate numbers ect...) 
	// extra path functions
	//
	// append
	// has_parent_path
// crypto commands , likely not...
// look at .NET string static methods and instance methods for other functions...
// regex multiple options (look at c# enumeration options...)

// random string commands (generating random strings with control on how it does it..)

// combine? (combines multiple path strings into one)
// string formating? (hex,bin,oct,$,ect...)
// stringlist functions? (loading from file) llok into win32 api if they have stringlist class


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

/////////////////////
// SF Is Functions //
/////////////////////
DWORD Contains( const char* pszString, const char* pszSubStr )
{
	// Make sure string is not null or is not a null pointer.
	if(!ValidateString(pszString))
		return false;

	// Make sure sub string to test is not null or is not a null pointer.
	if(!ValidateString(pszSubStr))
		return false;

	return boost::algorithm::contains(pszString,pszSubStr);
}
DWORD Is_Alpha( const char* pszString, int nIndex )
{
	// Make sure string is not null or is not a null pointer.  If it is, since Is_XXX is not XXX anyway.
	if(!ValidateString(pszString))
		return false;
	
	// Make sure the index is valid.
	if(IndexValid(pszString,nIndex))
		if(isalpha(pszString[nIndex-1]))
			return true;
		else
			return false;
}
DWORD Is_AlNum( const char* pszString, int nIndex )
{
	// Make sure string is not null or is not a null pointer.  If it is, since Is_XXX is not XXX anyway.
	if(!ValidateString(pszString))
		return false;
	
	// Make sure the index is valid.
	if(IndexValid(pszString,nIndex))
		if(isalnum(pszString[nIndex-1]))
			return true;
		else
			return false;
}
DWORD Is_Digit( const char* pszString, int nIndex )
{
	// Make sure string is not null or is not a null pointer.  If it is, since Is_XXX is not XXX anyway.
	if(!ValidateString(pszString))
		return false;
	
	// Make sure the index is valid.
	if(IndexValid(pszString,nIndex))
		if(isdigit(pszString[nIndex-1]))
			return true;
		else
			return false;
}
DWORD Is_Lower( const char* pszString, int nIndex )
{
	// Make sure string is not null or is not a null pointer.  If it is, since Is_XXX is not XXX anyway.
	if(!ValidateString(pszString))
		return false;
	
	// Make sure the index is valid.
	if(IndexValid(pszString,nIndex))
		if(islower(pszString[nIndex-1]))
			return true;
		else
			return false;
}
DWORD Is_Punct( const char* pszString, int nIndex )
{
	// Make sure string is not null or is not a null pointer.  If it is, since Is_XXX is not XXX anyway.
	if(!ValidateString(pszString))
		return false;

	// Make sure the index is valid.
	if(IndexValid(pszString,nIndex))
		if(ispunct(pszString[nIndex-1]))
			return true;
		else
			return false;
}
DWORD Is_Space( const char* pszString, int nIndex )
{
	// Make sure string is not null or is not a null pointer.  If it is, since Is_XXX is not XXX anyway.
	if(!ValidateString(pszString))
		return false;

	// Make sure the index is valid.
	if(IndexValid(pszString,nIndex))
		if(isspace(pszString[nIndex-1]))
			return true;
		else
			return false;
}
DWORD Is_Upper( const char* pszString, int nIndex )
{
	// Make sure string is not null or is not a null pointer.  If it is, since Is_XXX is not XXX anyway.
	if(!ValidateString(pszString))
		return false;

	// Make sure the index is valid.
	if(IndexValid(pszString,nIndex))
		if(isupper(pszString[nIndex-1]))
			return true;
		else
			return false;
}
DWORD Is_XDigit( const char* pszString, int nIndex )
{
	// Make sure string is not null or is not a null pointer.  If it is, since Is_XXX is not XXX anyway.
	if(!ValidateString(pszString))
		return false;

	// Make sure the index is valid.
	if(IndexValid(pszString,nIndex))
		if(isxdigit(pszString[nIndex-1]))
			return true;
		else
			return false;
}


///////////////////////
// SF Misc Functions //
///////////////////////
char* Bool_To_Str( const char* pszOldString, DWORD bvalue )
{
	// Delete old string
	DBPro::StringDeleter D( pszOldString );

	switch(bvalue)
	{
	case true:
		return DBPro::CreateString("True");
	case false:
		return DBPro::CreateString("False");
	}
	
	// Raise a error since the value was not a boolean value.
	DBPro::ErrorHandler::ThrowError(DBPro::ErrorHandler::NONBOOLEANVALUE,ERROR_TITLE,ERROR_NONBOOLEANVALUE);
	return NULL;
}
// Update in next version to use regular expressions?
/*
char* Mixedcase( const char* pszOldString, char* pszString, DWORD bConvertType )
{
	// Delete old string
	DBPro::StringDeleter D( pszOldString );

	// Enclose in a try/catch block incase the expression is invalid.
	try
	{
		// Assign a regular expression to the appropriate convert mode. (Sentence format or every first letter in word is capital)
		if(bConvertType)
			 // The first char must NOT be a whitespace char.  followed by any string of words,chars that do not contain a '.'.
			RegEx.assign("\\S[ \\w#$%=@!{},`~&*()'<>?:;|^/\\-\\+\\t\\r\\n\\[\\]\\/\"]+\\.");
		else
			// Match every word.
			RegEx.assign("\\S+");
		
		string strUserString = pszString;
		string strReplaceString;
		int nLastPosition = -1;

		// Declare iterators to iterate through the sub matches and process the string.
		boost::sregex_iterator Matches(strUserString.begin(),strUserString.end(),RegEx);
		boost::sregex_iterator MatchEnd;

		while( Matches != MatchEnd )
		{
			// Replace the first word in the string with a capital letter.
			strUserString.replace(Matches->position(),1,1,toupper(strUserString[Matches->position()]));

			// Must iterate over this loop at least once.
			if(nLastPosition != -1)
			{
				// Convert the rest of the word to lower case.
				boost::algorithm::to_lower(strReplaceString = strUserString.substr(nLastPosition + 1,Matches->position() - (nLastPosition + 1)));
				strUserString.replace(nLastPosition + 1,Matches->position() - (nLastPosition + 1),strReplaceString);
			}
			// Store the last position of the match for converting the word to lower case later on.
			nLastPosition = Matches->position();
			
			// Increment the iterator.
			*Matches++;		
		}


		// Sentance conversion.
		if(bConvertType)
		{
			//
		}
		else
		{
			// Since the last word will not be converted to lower case it must be done here.
			if(nLastPosition != -1)
			{
				boost::algorithm::to_lower(strReplaceString = strUserString.substr(nLastPosition + 1));
				strUserString.replace(nLastPosition + 1,strUserString.length(),strReplaceString);
			}
		}

		return DBPro::CreateString(strUserString.c_str());
	}
	// Regular expression error.
	catch(boost::bad_expression &Exception)
	{
		// Possible could use strcat or sprintf but this will be used for easier concatenation atm.
		string ExceptionString = ERROR_REGEX_INVALIDEXPRESSION; 
		ExceptionString += Exception.what();
		DBPro::ErrorHandler::ThrowError(DBPro::ErrorHandler::REGEX_INVALIDEXPRESSION,ERROR_TITLE,ExceptionString);
	}
	// This gets thrown under 3 conditions that are not likely to happen very much or at all.  So this will just throw a UNKNOWNERROR.
	// Reference: http://www.boost.org/doc/libs/1_49_0/libs/regex/doc/html/boost_regex/ref/regex_match.html
	catch(runtime_error& Exception)
	{
		DBPro::ErrorHandler::ThrowError(DBPro::ErrorHandler::UNKNOWNERROR,ERROR_TITLE,Exception.what());
	}
	// Catch anything else...
	catch(...)
	{
		DBPro::ErrorHandler::ThrowError(DBPro::ErrorHandler::UNKNOWNERROR,ERROR_TITLE,ERROR_UNKNOWN);
	}

	return false; // If there was a exception, return NULL.
}
*/



char* Mixedcase( const char* pszOldString, char* pszString, DWORD bConvertType )
{
	// Delete old string
	DBPro::StringDeleter D( pszOldString );

	// Make sure string is not null or is not a null pointer 
	if(!ValidateString(pszString))
		return NULL;

	bool bUConvert = false;
	bool bLConvert = false;
	bool bUDone = false;

	if(bConvertType)
	{
		for(int x = 0; x < strlen(pszString); ++x)
		{
			if(x == 0 && islower(pszString[0]))
				pszString[0] = toupper(pszString[0]);
			else
			{
				if(bUConvert && !isspace(pszString[x]))
				{ bUConvert = false; bUDone = false; pszString[x] = toupper(pszString[x]); }

				if(pszString[x] == 0x2E)
					bUConvert = true;
				else
					if(bUDone && isupper(pszString[x]))
						bLConvert = true;
				if(bLConvert)	
					{ bLConvert = false; pszString[x] = tolower(pszString[x]); }
				if(bUDone == false)
					bUDone = true;
			}
		}
	}
	else
	{
		for(int x = 0; x < strlen(pszString); ++x)
		{
			if(x == 0 && islower(pszString[0]))
				pszString[0] = toupper(pszString[0]);
			else
			{
				if(bUConvert)
				{ bUConvert = false; bUDone = false; pszString[x] = toupper(pszString[x]); }

				if(isspace(pszString[x]))
					bUConvert = true;
				else
					if(bUDone && isupper(pszString[x]))
						bLConvert = true;
				if(bLConvert)	
					{ bLConvert = false; pszString[x] = tolower(pszString[x]); }
				if(bUDone == false)
					bUDone = true;
			}
		}
	}
	
	return DBPro::CreateString(pszString);
}
void SplitStrToArray( DWORD* pnArrayPtr, const char* pszString, const char* pszDelimiter )
{
	SplitStrToArray(pnArrayPtr,pszString,pszDelimiter,true);
}
void SplitStrToArray( DWORD* pnArrayPtr, const char* pszString, const char* pszDelimiter, DWORD bRemoveEmptyStrings )
{
	// Make sure string is not null or is not a null pointer 
	if(!ValidateString(pszString))
		return;

	// Check to see if the array is a string array.
	if(DBPro::Array::Type(pnArrayPtr) != DBPro::ArrayType::String)
		DBPro::ErrorHandler::ThrowError(DBPro::ErrorHandler::ARRAYNOTSTRING,ERROR_TITLE,ERROR_ARRAYNOTSTRING);

	// Declare variables.
	string strUserString = pszString;
	int nDelimIndex = 0, nLastDelimIndex = 0, nCurrentArrayIndex = 0;
	
	do
	{
		// Find the next delimiter character.
		nDelimIndex = strUserString.find(pszDelimiter,nLastDelimIndex);
		
		// If it does not find the delimiter, then copy the last substring.
		if(nDelimIndex == strUserString.npos)
		{
			// Assign the substring to the current array index.
			*(DWORD*)DBPro::Array::Item(pnArrayPtr,nCurrentArrayIndex) = (DWORD)DBPro::CreateString(
				strUserString.substr(nLastDelimIndex,strUserString.length() - nLastDelimIndex).c_str());
			break;
		}
		else
		{
			// If the flag is true then do nothing on null strings.
			if(bRemoveEmptyStrings && strUserString.substr(nLastDelimIndex,nDelimIndex - nLastDelimIndex).c_str()[0] == '\0')
				; // Do nothing if string is null.
			else
			{
			// Assign the substring to the array and increase the index to store the next substring.
			*(DWORD*)DBPro::Array::Item(pnArrayPtr,nCurrentArrayIndex++) = (DWORD)DBPro::CreateString(
				strUserString.substr(nLastDelimIndex,nDelimIndex - nLastDelimIndex).c_str());
			}
		}
		
		// If the array size is less than the amount of tokens, then return early.
		if(nCurrentArrayIndex >= DBPro::Array::Size(pnArrayPtr))
			return;

		// Assign the last delimiter to the current index.
		nLastDelimIndex = nDelimIndex + 1;
	} while(true);

	// If the array size is greater than the amount of tokens in the string, then set the rest of the array to null strings.
	for(int x = nCurrentArrayIndex + 1; x < DBPro::Array::Size(pnArrayPtr); x++)
	{
		// Create the buffer of the null string and assign it to the array.
		char* szBuffer = DBPro::CreateString(1);
		szBuffer[0] = '\0';
		*(DWORD*)DBPro::Array::Item(pnArrayPtr,x) = (DWORD)szBuffer;
	}

	return;
}
DWORD Str_To_Bool( char* pszString )
{
	// Make sure string is not null or is not a null pointer 
	if(!ValidateString(pszString))
	{
		DBPro::ErrorHandler::ThrowError(DBPro::ErrorHandler::UNKNOWNBOOLSTRING,ERROR_TITLE,ERROR_UNKNOWNBOOLSTRING);
		return false; // Fix for multiple error popups.
	}
	
	// Convert string to lowercase.
	for(int x = 0; x < 6; ++x)
		pszString[x] = tolower(pszString[x]);
	  
	if(strcmp(pszString,"true") == 0)
		return true;
	else
	{
		if(strcmp(pszString,"false") == 0)
			return false;
		else
			DBPro::ErrorHandler::ThrowError(DBPro::ErrorHandler::UNKNOWNBOOLSTRING,ERROR_TITLE,ERROR_UNKNOWNBOOLSTRING);
	}
}
int String_Distance( const char* pszString1, const char* pszString2 )
{
	// If one of the input strings is null, then return strlen.
	if(!ValidateString(pszString1) || !ValidateString(pszString2))
		if(!ValidateString(pszString1))
			return strlen(pszString2);
		else
			return strlen(pszString1);

	// Declare and resize vector to hold the elements.
	vector<std::vector<int>> Dist;
	Dist.resize(strlen(pszString1));

	for(int x = 0; x < strlen(pszString1); ++x)
		Dist[x].resize(strlen(pszString2));

	// Fill the vector with the elements.
	for(int x = 0; x < strlen(pszString1); ++x)
		Dist[x][0] = x;

	for(int x = 0; x < strlen(pszString2); ++x)
		Dist[0][x] = x;

	//
	for(int x = 1; x < strlen(pszString1); ++x)
	{
		for(int y = 1; y < strlen(pszString2); ++y)
		{
			if(pszString1[x-1] == pszString2[y-1])
				Dist[x][y] = Dist[x-1][y-1];
			else
			{
				int temp = min(Dist[x-1][y] + 1,Dist[x][y-1] + 1);
				Dist[x][y] = min(temp,Dist[x-1][y-1] + 1);
			}
		}
	}
	
	// Return the string distance.
	int result = Dist[strlen(pszString1)-1][strlen(pszString2)-1];

	return result;
}
void ToCharArray( DWORD* pnArrayPtr, const char* pszString )
{
	// Make sure string is not null or is not a null pointer 
	if(!ValidateString(pszString))
		return;

	// Check to see if the array is a string array.
	if(DBPro::Array::Type(pnArrayPtr) != DBPro::ArrayType::String)
		DBPro::ErrorHandler::ThrowError(DBPro::ErrorHandler::ARRAYNOTSTRING,ERROR_TITLE,ERROR_ARRAYNOTSTRING);

	// Insert each character in the string into the array.
	for(int x = 0; x < DBPro::Array::Size(pnArrayPtr); x++)
	{
		// Create the buffer of the char and assign value.
		char* szBuffer = DBPro::CreateString(1);
		
		// If the end of the string is reached, then the rest of the characters will be null.
		if(x > strlen(pszString))
			szBuffer[0] = '\0';
		else
		{ szBuffer[0] = pszString[x]; szBuffer[1] = '\0'; }
		
		*(DWORD*)DBPro::Array::Item(pnArrayPtr,x) = (DWORD)szBuffer;
	}
}


///////////////////////
// SF Path Functions //
///////////////////////

char* Path_GetFileName( const char* pszOldString, const char* pszString )
{
	return Path_GetFileName(pszOldString,pszString,false);
}
char* Path_GetFileName( const char* pszOldString, const char* pszString, DWORD bReturnExtension )
{
	// Delete old string
	DBPro::StringDeleter D( pszOldString );
	
	// Make sure string is not null or is not a null pointer 
	if(!ValidateString(pszString))
		return NULL;

	// Make sure the string does not have invalid characters or the length of the path is to long.
	if(ValidatePath(pszString))
	{
		string strReturnString = pszString;
		int nIndex = Path_RFindSlashes(strReturnString) + 1;

		// If it can't find any '\' chars, return null.
		if(nIndex-1 == string::npos)
			return NULL;
		else
			if(bReturnExtension)
				return DBPro::CreateString(strReturnString.substr(nIndex,strReturnString.length()).c_str());
			else
			{
				int nFileExtIndex = strReturnString.rfind('.');
				// If the path is a folder, then return folder name.
				if(nFileExtIndex == string::npos || !ValidateFileExtension(strReturnString,nFileExtIndex))
					return DBPro::CreateString(strReturnString.substr(nIndex,strReturnString.length()).c_str());
				else
					return DBPro::CreateString(strReturnString.substr(nIndex,(strReturnString.length() - nIndex) - (strReturnString.length() - nFileExtIndex)).c_str());	
			}
	}
}
char* Path_ChangeFileExtension( const char* pszOldString, const char* pszString, const char* pszNewExtension )
{
	// Delete old string
	DBPro::StringDeleter D( pszOldString );
	
	// Make sure string is not null or is not a null pointer 
	if(!ValidateString(pszString))
		return NULL;

	// Make sure the string does not have invalid characters or the length of the path is to long.
	if(ValidatePath(pszString))
	{
		// Change the file extension.
		string strTempPath = pszString;
		int nExtStart = strTempPath.rfind('.');

		// If the . is past the first folder mark but NewExt is not null, then add the following extension.
		if(!ValidateFileExtension(strTempPath,nExtStart) && ValidateString(pszString))
		{
			// Add the '.' character if the user did not add it.
			if(pszNewExtension[0] != '.')
			{
				strTempPath += ".";
				strTempPath += pszNewExtension;
			}
			else
				strTempPath += pszNewExtension;
			
			if(ValidatePath(strTempPath.c_str()))
				return DBPro::CreateString(strTempPath.c_str());
		}
		else
		{
			// Null string to remove file extension.
			if(!ValidateString(pszNewExtension))
			{
				if(nExtStart != std::string::npos)
					strTempPath.erase(nExtStart,strTempPath.length());
				
				if(ValidatePath(strTempPath.c_str()))
					return DBPro::CreateString(strTempPath.c_str());
			}
			else
			{
				strTempPath.erase(nExtStart,strTempPath.length());

				// Add the '.' character if the user did not add it.
				if(pszNewExtension[0] != '.')
				{
					strTempPath += ".";
					strTempPath += pszNewExtension;
				}
				else
					strTempPath += pszNewExtension;

				if(ValidatePath(strTempPath.c_str()))
					return DBPro::CreateString(strTempPath.c_str());
			}
		}
	}
}
char* Path_GetFileExtension( const char* pszOldString, const char* pszString )
{
	// Delete old string
	DBPro::StringDeleter D( pszOldString );
	
	// Make sure string is not null or is not a null pointer 
	if(!ValidateString(pszString))
		return NULL;

	// Make sure the string does not have invalid characters or the length of the path is to long.
	if(ValidatePath(pszString))
	{
		// Get the '.' index.
		string strTemp = pszString;
		int nIndex = strTemp.rfind('.');

		// If it can't find '.' char, return null.
		if(nIndex == string::npos || !ValidateFileExtension(strTemp,nIndex))
			return NULL;
		else
			return DBPro::CreateString(strTemp.substr(nIndex,strTemp.length()).c_str());
	}
}
char* Path_GetParent( const char* pszOldString, const char* pszString )
{
	// Delete old string
	DBPro::StringDeleter D( pszOldString );
	
	// Make sure string is not null or is not a null pointer 
	if(!ValidateString(pszString))
		return NULL;

	// Make sure the string does not have invalid characters or the length of the path is to long.
	if(ValidatePath(pszString))
	{	
		string strTemp = pszString;
		int nIndex = Path_RFindSlashes(strTemp);
	
		// If it can't find any '\' chars, return null.
		if(nIndex == string::npos)
			return NULL;
		else
			return DBPro::CreateString(strTemp.substr(0,nIndex).c_str());
	}
}
char* Path_GetParentName( const char* pszOldString, const char* pszString )
{
	// Delete old string
	DBPro::StringDeleter D( pszOldString );
	
	// Make sure string is not null or is not a null pointer 
	if(!ValidateString(pszString))
		return NULL;

	// Make sure the string does not have invalid characters or the length of the path is to long.
	if(ValidatePath(pszString))
	{	
		string strTemp = pszString;
		int nIndex = Path_RFindSlashes(strTemp);
	
		// If it can't find any '\' chars, return null.
		if(nIndex == string::npos)
			return NULL;
		else
		{
			int nNameIndex = Path_RFindSlashes(strTemp,nIndex-1);
		
			if(nNameIndex == string::npos)
				return DBPro::CreateString(strTemp.substr(0,nIndex).c_str());
			else
				return DBPro::CreateString(strTemp.substr(nNameIndex+1,nIndex - (nNameIndex+1)).c_str());
		}
	}
}
char* Path_GetPathRoot( const char* pszOldString, const char* pszString )
{
	// Delete old string
	DBPro::StringDeleter D( pszOldString );
	
	// Make sure string is not null or is not a null pointer 
	if(!ValidateString(pszString))
		return NULL;

	// Make sure the string does not have invalid characters or the length of the path is to long.
	if(ValidatePath(pszString))
	{
		string strTemp = pszString;
		int nIndex = Path_FindSlashes(strTemp);
	
		// If it can't find any '\' chars, return null.
		if(nIndex == string::npos)
			return DBPro::CreateString(strTemp.c_str());
		else
			return DBPro::CreateString(strTemp.substr(0,nIndex).c_str());
	}
}
DWORD Path_HasExtension( const char* pszString )
{
	// Make sure string is not null, is not a null pointer.
	if(!ValidateString(pszString))
		return NULL;

	if(ValidatePath(pszString))
	{
		string strTemp = pszString;
		
		if(ValidateFileExtension(strTemp,strTemp.rfind('.')))
			return true;
		else
			return false;
	}
}
// File management article: http://msdn.microsoft.com/en-us/library/windows/desktop/aa365247(v=vs.85).aspx
int Path_Valid( const char* pszString  )
{
	// Make sure string is not null, is not a null pointer or to long.
	if(!ValidateString(pszString))
		return ERRORCODE_PATH_NULLPATH;

	// Check for the length of the path string.
	if(Path_HasExtensionNoValidate(pszString))
	{
		//File
		if(strlen(pszString) > MAX_PATH - 12)
			return ERRORCODE_PATH_MAXPATH;
		
		// Determine if the filename is a reserved name.
		string strValidFileName = pszString;
		strValidFileName = strValidFileName.substr(Path_RFindSlashes(strValidFileName) + 1,strValidFileName.length() - (strValidFileName.find('.') + 1));
		boost::algorithm::to_lower(strValidFileName);
		
		switch(Path_ReservedFileNames[strValidFileName])
		{
		case ReservedPathNames::PRN:
		case ReservedPathNames::AUX:
		case ReservedPathNames::NUL:
		case ReservedPathNames::COM1:
		case ReservedPathNames::COM2:
		case ReservedPathNames::COM3:
		case ReservedPathNames::COM4:
		case ReservedPathNames::COM5:
		case ReservedPathNames::COM6:
		case ReservedPathNames::COM7:
		case ReservedPathNames::COM8:
		case ReservedPathNames::COM9:
		case ReservedPathNames::LPT1:
		case ReservedPathNames::LPT2:
		case ReservedPathNames::LPT3:
		case ReservedPathNames::LPT4:
		case ReservedPathNames::LPT5:
		case ReservedPathNames::LPT6:
		case ReservedPathNames::LPT7:
		case ReservedPathNames::LPT8:
		case ReservedPathNames::LPT9:
			return ERRORCODE_PATH_RESERVEDNAME;
			break;
		}
	}
	else
		//Folder
		// Needs -12 for the 8.3 naming convention.
		if(strlen(pszString) > MAX_PATH - 12)
			return ERRORCODE_PATH_MAXPATH;

	string strTemp = pszString;
	int nDrivePosition = Path_FindSlashes(strTemp);

	// Check for invalid chars.
	for(int x = strTemp.length()-1; x > 0 ; x--)
	{
		switch(tolower((int)pszString[x]))
		{
		// Invalid chars for filenames...
		case 0x0022:
		case 0x003C:
		case 0x003E:
		case 0x007C:
		case 0x0000:
		case 0x0001:
		case 0x0002:
		case 0x0003:
		case 0x0004:
		case 0x0005:
		case 0x0006:
		case 0x0007:
		case 0x0008:
		case 0x0009:
		case 0x000A:
		case 0x000B:
		case 0x000C:
		case 0x000D:
		case 0x000E:
		case 0x000F:
		case 0x0010:
		case 0x0011:
		case 0x0012:
		case 0x0013:
		case 0x0014:
		case 0x0015:
		case 0x0016:
		case 0x0017:
		case 0x0018:
		case 0x0019:
		case 0x001A:
		case 0x001B:
		case 0x001C:
		case 0x001D:
		case 0x001E:
		case 0x001F:
		case 0x002A:
		case 0x003F:
			return ERRORCODE_PATH_INVALIDCHARS;
			break;
		
		case 0x003A:
			// Check to make sure there are only 2 characters when the ':' is in the path string.
			if(strTemp.substr(0,Path_FindSlashes(strTemp)).length() != 2 || x > nDrivePosition || nDrivePosition == string::npos )
				return ERRORCODE_PATH_INVALIDCHARS;
				break;

		//Check for reserved filenames.
		case 0x2F: //"/"
		case 0x5C: // "\"
			string strReservedName = strTemp.substr(x+1,Path_FindSlashes(strTemp,x+1) - (x + 1));
			boost::algorithm::to_lower(strReservedName);

			switch(Path_ReservedFileNames[strReservedName])
			{
			case ReservedPathNames::PRN:
			case ReservedPathNames::AUX:
			case ReservedPathNames::NUL:
			case ReservedPathNames::COM1:
			case ReservedPathNames::COM2:
			case ReservedPathNames::COM3:
			case ReservedPathNames::COM4:
			case ReservedPathNames::COM5:
			case ReservedPathNames::COM6:
			case ReservedPathNames::COM7:
			case ReservedPathNames::COM8:
			case ReservedPathNames::COM9:
			case ReservedPathNames::LPT1:
			case ReservedPathNames::LPT2:
			case ReservedPathNames::LPT3:
			case ReservedPathNames::LPT4:
			case ReservedPathNames::LPT5:
			case ReservedPathNames::LPT6:
			case ReservedPathNames::LPT7:
			case ReservedPathNames::LPT8:
			case ReservedPathNames::LPT9:
				return ERRORCODE_PATH_RESERVEDNAME;
				break;
			}
			break;
		}
	}
	// Return true since path is valid.
	return true;
}

////////////////////////
// SF RegEx Functions //
////////////////////////

int RegEx_GetMatchCount() { return RegEx_UserMatches.size(); }
int RegEx_GetMatchPosition( int nIndex )
{
	// Make sure the index is not out of bounds.
	if(nIndex >= RegEx_UserMatches.size())
	{
		DBPro::ErrorHandler::ThrowError(DBPro::ErrorHandler::REGEX_MATCHINDEXOUTOFBOUNDS,ERROR_TITLE,ERROR_REGEX_MATCHINDEXOUTOFBOUNDS);
		return 0;
	}
	return RegEx_UserMatches[nIndex].nPosition;
}
char* RegEx_GetMatchStr( const char* pszOldString, int nIndex )
{
	// Delete old string
	DBPro::StringDeleter D( pszOldString );

	// Make sure the index is not out of bounds.
	if(nIndex >= RegEx_UserMatches.size())
	{
		DBPro::ErrorHandler::ThrowError(DBPro::ErrorHandler::REGEX_MATCHINDEXOUTOFBOUNDS,ERROR_TITLE,ERROR_REGEX_MATCHINDEXOUTOFBOUNDS);
		return DBPro::CreateString("");
	}
	return DBPro::CreateString(RegEx_UserMatches[nIndex].strMatch.c_str());
}
DWORD RegEx_IsMatch( const char* pszString, const char* pszPattern )
{
	// Enclose in a try/catch block incase the expression is invalid.
	try
	{
		RegEx.assign(pszPattern);
		return boost::regex_match(pszString,RegEx);
	}
	// Regular expression error.
	catch(boost::bad_expression &Exception)
	{
		// Possible could use strcat or sprintf but this will be used for easier concatenation atm.
		string ExceptionString = ERROR_REGEX_INVALIDEXPRESSION; 
		ExceptionString += Exception.what();
		DBPro::ErrorHandler::ThrowError(DBPro::ErrorHandler::REGEX_INVALIDEXPRESSION,ERROR_TITLE,ExceptionString);
	}
	// This gets thrown under 3 conditions that are not likely to happen very much or at all.  So this will just throw a UNKNOWNERROR.
	// Reference: http://www.boost.org/doc/libs/1_49_0/libs/regex/doc/html/boost_regex/ref/regex_match.html
	catch(runtime_error& Exception)
	{
		DBPro::ErrorHandler::ThrowError(DBPro::ErrorHandler::UNKNOWNERROR,ERROR_TITLE,Exception.what());
	}
	// Catch anything else...
	catch(...)
	{
		DBPro::ErrorHandler::ThrowError(DBPro::ErrorHandler::UNKNOWNERROR,ERROR_TITLE,ERROR_UNKNOWN);
	}

	return false; // If there was a exception, return false.
}
DWORD RegEx_IsPartialMatch( const char* pszString, const char* pszPattern )
{
	// Enclose in a try/catch block incase the expression is invalid.
	try
	{
		RegEx.assign(pszPattern);
		return boost::regex_search(pszString,RegEx);
	}
	// Regular expression error.
	catch(boost::bad_expression &Exception)
	{
		// Possible could use strcat or sprintf but this will be used for easier concatenation atm.
		string ExceptionString = ERROR_REGEX_INVALIDEXPRESSION; 
		ExceptionString += Exception.what();
		DBPro::ErrorHandler::ThrowError(DBPro::ErrorHandler::REGEX_INVALIDEXPRESSION,ERROR_TITLE,ExceptionString);
	}
	// This gets thrown under 3 conditions that are not likely to happen very much or at all.  So this will just throw a UNKNOWNERROR.
	// Reference: http://www.boost.org/doc/libs/1_49_0/libs/regex/doc/html/boost_regex/ref/regex_match.html
	catch(runtime_error& Exception)
	{
		DBPro::ErrorHandler::ThrowError(DBPro::ErrorHandler::UNKNOWNERROR,ERROR_TITLE,Exception.what());
	}
	// Catch anything else...
	catch(...)
	{
		DBPro::ErrorHandler::ThrowError(DBPro::ErrorHandler::UNKNOWNERROR,ERROR_TITLE,ERROR_UNKNOWN);
	}

	return false; // If there was a exception, return false.
}
int RegEx_Match( const char* pszString, const char* pszPattern )
{
	// Make sure string is not null or is not a null pointer 
	if(!ValidateString(pszString))
		return NULL;

	// Enclose in a try/catch block incase the expression is invalid.
	try
	{
		RegEx.assign(pszPattern);

		// Declare variables
		string strUserString = pszString;
		int nMatchCount = 0;
		RegEx_UserMatches.resize(1);

		// Declare iterators to iterate through the sub matches and process the string.
		boost::sregex_iterator Matches(strUserString.begin(),strUserString.end(),RegEx);
		boost::sregex_iterator MatchEnd;

		while( Matches != MatchEnd )
		{
			// Save the data so the user can retrive it later.
			RegEx_UserMatches[nMatchCount].strMatch = Matches->str();
			RegEx_UserMatches[nMatchCount].nPosition = Matches->position();

			// Increment the itterator and the match count.
			nMatchCount++;
			RegEx_UserMatches.resize(nMatchCount+1);
			Matches++;
		}

		// Resize the vector one since it is empty.
		RegEx_UserMatches.resize(nMatchCount);

		return nMatchCount;
	}
	// Regular expression error.
	catch(boost::bad_expression &Exception)
	{
		// Possible could use strcat or sprintf but this will be used for easier concatenation atm.
		string ExceptionString = ERROR_REGEX_INVALIDEXPRESSION; 
		ExceptionString += Exception.what();
		DBPro::ErrorHandler::ThrowError(DBPro::ErrorHandler::REGEX_INVALIDEXPRESSION,ERROR_TITLE,ExceptionString);
	}
	// This gets thrown under 3 conditions that are not likely to happen very much or at all.  So this will just throw a UNKNOWNERROR.
	// Reference: http://www.boost.org/doc/libs/1_49_0/libs/regex/doc/html/boost_regex/ref/regex_match.html
	catch(runtime_error& Exception)
	{
		DBPro::ErrorHandler::ThrowError(DBPro::ErrorHandler::UNKNOWNERROR,ERROR_TITLE,Exception.what());
	}
	// Catch anything else...
	catch(...)
	{
		DBPro::ErrorHandler::ThrowError(DBPro::ErrorHandler::UNKNOWNERROR,ERROR_TITLE,ERROR_UNKNOWN);
	}
}
char* RegEx_Replace( const char* pszOldString, const char* pszString, const char* pszPattern, const char* pszFormatter )
{
	// Delete old string
	DBPro::StringDeleter D( pszOldString );

	// Enclose in a try/catch block incase the expression is invalid.
	try
	{
		RegEx.assign(pszPattern);
		string strUserString = pszString;
		return DBPro::CreateString(boost::regex_replace(strUserString,RegEx,pszFormatter).c_str());
	}
	// Regular expression error.
	catch(boost::bad_expression &Exception)
	{
		// Possible could use strcat or sprintf but this will be used for easier concatenation atm.
		string ExceptionString = ERROR_REGEX_INVALIDEXPRESSION; 
		ExceptionString += Exception.what();
		DBPro::ErrorHandler::ThrowError(DBPro::ErrorHandler::REGEX_INVALIDEXPRESSION,ERROR_TITLE,ExceptionString);
	}
	// This gets thrown under 3 conditions that are not likely to happen very much or at all.  So this will just throw a UNKNOWNERROR.
	// Reference: http://www.boost.org/doc/libs/1_49_0/libs/regex/doc/html/boost_regex/ref/regex_match.html
	catch(runtime_error& Exception)
	{
		DBPro::ErrorHandler::ThrowError(DBPro::ErrorHandler::UNKNOWNERROR,ERROR_TITLE,Exception.what());
	}
	// Catch anything else...
	catch(...)
	{
		DBPro::ErrorHandler::ThrowError(DBPro::ErrorHandler::UNKNOWNERROR,ERROR_TITLE,ERROR_UNKNOWN);
	}

	return false; // If there was a exception, return NULL.
}





