#include "fsGlobal.h" 

#include "Error.h"



CError::CError()
{
}


CError::~CError()
{
}


//bugbug..move
#define MAX_LANG_ERROR_STR 2048

bool CError::NotifyError( LPSTR szFilename, int iLine, int iColumn, DWORD dwStrResourceDescription)
{
	WCHAR szBuffer[ MAX_LANG_ERROR_STR];

	if( 0 >= LoadStringW( NULL, dwStrResourceDescription, szBuffer, sizeof(szBuffer)))
		return FALSE;

	return NotifyError( szFilename, iLine, iColumn, szBuffer);
}


bool CError::NotifyError( LPSTR szFilename, int iLine, int iColumn, LPCWSTR szDescription)
{
	//bugbug
	return true;
}
