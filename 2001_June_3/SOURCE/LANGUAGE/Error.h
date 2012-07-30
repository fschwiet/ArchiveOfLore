#ifndef _CERROR_H_
#define _CERROR_H_

class CError
{
public:
	CError();
	~CError();

	bool NotifyError( LPSTR szFilename, int iLine, int iColumn, DWORD dwStrResourceDescription);
	bool NotifyError( LPSTR szFilename, int iLine, int iColumn, LPCWSTR szDescription);
};



#endif
