#ifndef _SToken_H_
#define _SToken_H_


typdef struct SToken
{
private:
	LPSTR _szName;
	DWORD _dwAttributes;

public:
	SToken();
	~SToken();

	LPCSTR Name() { return _szName};

	bool Set( LPCSTR szName, DWORD dwAttributes);
} *PSToken;


class CSymbolTable
{
	CBinaryValueTable< const DWORD*, PSToken> _cTable;

public:
	CSymbolTable();
	~CSymbolTable();

	bool AddToken( LPCSTR szName, PSToken pToken = NULL);
	bool GetToken( LPCSTR szName, PSToken* ppToken);
};


#endif

CSymbolTable::CSymbolTable()
:  _cTable(32)
{
}


CSymbolTable::CSymbolTable()
{
}


bool CSymbolTable::AddToken( LPCSTR szName, PSToken pToken = NULL)
{
}


bool CSymbolToken::GetToken( LPCSTR szName, PSToken* ppToken)
{
}





SToken::SToken()
{
	_szName = NULL;
	_dwAttributes = 0;
}


SToken::~SToken()
{
	if( _szName != NULL)
		delete[] _szName;
}


bool SToken::Initialize( LPCSTR szName, DWORD dwAttributes);
{
	int iNameLength = strlen( szName);
	int iBufferLength =  sizeof(DWORD) + (iNameLength / sizeof(DWORD)) * sizeof(DWORD);

	_szName = new CHAR[ iBufferLength];

	if( _szName == NULL)
		return false;

	memset( &(_szName[ iBufferLength - 2*sizeof(DWORD)]), 0, 2*sizeof(DWORD));

	memcpy( _szName, szName, iNameLength);

	_dwAttributes = dwAttributes;

	return true;
}