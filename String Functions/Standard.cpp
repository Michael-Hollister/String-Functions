#include "stdafx.h"
#include <DBPro.hpp>

// Global Declrations...
GlobStruct* CorePtr = NULL;

// Extern function prototypes
extern void SF_Init();


// DBPro Interface implementation
GlobStruct* DBPro::GetCore() { return CorePtr; }

/*
// XXXX If your code has no external dependencies, then you should delete from here ...
static const char* Dependencies[] =
{
	//"DBProCore.dll",
	//"xxxxxxxx.dll",          // List all of your DLL dependencies here as comma-separated literal strings.
};



EXPORT int GetNumDependencies(void)
{
    return sizeof(Dependencies) / sizeof(const char*);
}

EXPORT const char* GetDependencyID(int ID)
{
    return Dependencies[ID];
}
// XXXX ... to here.
*/

EXPORT void ReceiveCoreDataPtr(void* InCorePtr)
{
	// Get references to runtime data
	CorePtr = (GlobStruct*)InCorePtr;
	SF_Init();
}

EXPORT void PreDestructor(void)
{
    // Early shutdown stuff goes here
}

EXPORT void Destructor(void)
{
	// Final shutdown stuff goes here
}

