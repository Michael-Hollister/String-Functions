#pragma once
#ifndef RESOURCE_H
#define RESOURCE_H


// Resource strings
#define IDRES_STR1		1
#define IDRES_STR2		2
#define IDRES_STR3		3
#define IDRES_STR4		4
#define IDRES_STR5		5
#define IDRES_STR6		6
#define IDRES_STR7		7
#define IDRES_STR8		8
#define IDRES_STR9		9
#define IDRES_STR10		10
#define IDRES_STR11		11
#define IDRES_STR12		12
#define IDRES_STR13 	13
#define IDRES_STR14 	14
#define IDRES_STR15 	15
#define IDRES_STR16 	16
#define IDRES_STR17 	17
#define IDRES_STR18 	18
#define IDRES_STR19 	19
#define IDRES_STR20 	20
#define IDRES_STR21 	21
#define IDRES_STR22 	22
#define IDRES_STR23 	23
#define IDRES_STR24 	24
#define IDRES_STR25 	25
#define IDRES_STR26 	26
#define IDRES_STR27 	27
#define IDRES_STR28 	28
#define IDRES_STR29 	29
#define IDRES_STR30 	30
#define IDRES_STR31 	31
#define IDRES_STR32 	32
#define IDRES_STR33 	33
#define IDRES_STR34 	34
#define IDRES_STR35 	35

// Error Strings
#define ERROR_TITLE "String Functions DLL Error"

#define ERROR_UNKNOWN "A unknown error has occurred."
#define ERROR_MUSTBEPOSITIVEVALUE "The character index specified must be positive."
#define ERROR_INDEXOUTOFRANGE "The index specified is greater than the length of the string."
#define ERROR_UNKNOWNBOOLSTRING "String was not recognized as a valid Boolean."
#define ERROR_NONBOOLEANVALUE "The argument was not a Boolean value."
#define ERROR_ARRAYNOTSTRING "The array was not a string array."

#define ERROR_PATH_INVALIDCHARS "Illegal characters in path."
#define ERROR_PATH_MAXPATH "The specified path, file name, or both are too long. The fully qualified path name must be less than 260 characters."
#define ERROR_PATH_RESERVEDNAME "The specified path contains a reserved filename."

#define ERROR_REGEX_INVALIDEXPRESSION "The specified regular expression was invalid.\n\nDetails: "
#define ERROR_REGEX_MATCHINDEXOUTOFBOUNDS "The specified index was out of bounds."


// Error Codes
#define ERRORCODE_PATH_NULLPATH 0
#define ERRORCODE_PATH_INVALIDCHARS -1
#define ERRORCODE_PATH_MAXPATH -2
#define ERRORCODE_PATH_RESERVEDNAME -3

// Macros
#define DEBUG_PROMPT( pszMessage ) MessageBoxA(NULL, (LPCSTR)pszMessage, (LPCSTR)"Debug Informaion", MB_OK)


#endif // RESOURCE_H
