#include "fsGlobal.h"


#define WHITESPACE       0x01
#define ALPHA            0x02
#define ALPHA_UPPER      0x04
#define ALPHA_LOWER      0x08
#define NUMERIC          0x16
#define OPERATOR         0x32



void CToken::resetValue()
{
	if( _type == NAME)
	{
		delete[] _szValue;
		_szValue = NULL;
	}
	
	_type = INT;
	_lValue = 0;
}


CToken::CToken()
{
	_type = INT;
	_lValue = 0;
}


CToken::~CToken()
{
	resetValue();
}


bool CToken::SetNameValue( LPCSTR szValue, int iSize)
{
	resetValue();
	
	LPSTR pNew = new char( iSize);
	if( pNew == NULL)
		return FALSE;

	memcpy( pNew, szValue, iSize);
	pNew[iSize-1] = '\0';
	
	_type = NAME;
	szValue = pNew;
	
	return true;
}


bool CToken::SetIntValue( long lValue)
{
	resetValue();
	_type = INT;
	_lValue = lValue;
	return true;
}


bool CToken::SetFloatValue( float fValue)
{
	resetValue();
	_type = FLOAT;
	_fValue = fValue;
	return true;
}


CToken::enumTokenType CToken::GetType()
{
	return _type;
}


bool CToken::GetNameValue( IN LPSTR szValue, IN OUT int* piSize)
{
	int iBufferSize = *piSize;
	*piSize = 0;

	if( _type != NAME)
		return false;

	*piSize = strlen( _szValue) + 1;

	if( iBufferSize < *piSize)
	{
		return false;
	}

	memcpy( szValue, _szValue, *piSize);

	return true;
}


bool CToken::GetIntValue( OUT long* plValue)
{
	if( _type == INT)
	{
		*plValue = _lValue;
		return true;
	}
	else if ( _type == FLOAT)
	{
		*plValue = (int)_fValue;
		return true;
	}
	else
		return false;
}


bool CToken::GetFloatValue( OUT float* pfValue)
{
	if( _type == INT)
	{
		*pfValue = (float)_lValue;
		return true;
	}
	else if ( _type == FLOAT)
	{
		*pfValue = _fValue;
		return true;
	}
	else
		return false;
}


void CTokenizer::initializeCharType()
{
	memset( _abCharType, 0, sizeof(_abCharType));
	for( int i = 0; i < 128; i++)
	{
		if( 'a' <= i && i <= 'z')
		{
			_abCharType[i] |= ALPHA;
			_abCharType[i] |= ALPHA_LOWER;
		}
		if( 'a' <= i && i <= 'z')
		{
			_abCharType[i] |= ALPHA;
			_abCharType[i] |= ALPHA_LOWER;
		}
		if( '0' <= i && i <= '9')
		{
			_abCharType[i] |= NUMERIC;
		}
		else if( i == ' ' || i == '\t' || i == '\n')
		{
			_abCharType[i] |= WHITESPACE;
		}
		else if( i == '{' || i == '}') //bugbug...
		{
			_abCharType[i] |= OPERATOR;
		}
	}
}



CTokenizer::CTokenizer()
{
	initializeCharType();
	_iLine = -1;
	_iColumn = -1;
}


CTokenizer::~CTokenizer()
{
}


bool CTokenizer::OpenFile( IN LPCSTR szFilename)
{
	if( _cFile.OpenFile( szFilename))
	{
		_iLine = 0;
		_iColumn = 0;
		return true;
	}
	else
		return false;
}


bool CTokenizer::GetNextToken( IN OUT PCToken pToken, OUT int* piLine, OUT int* piColumn)
{
	//  skip whitespace
	char chr = _cFile.GetCharPastSelection();
	while( WHITESPACE & _abCharType[ chr])
	{
		if( chr == '\n')
		{
			_iColumn = 0;
			_iLine++;
		}
		else
			_iColumn++;

		_cFile.SelectionEndStep();
	}
	_cFile.SelectionStartToSelectionEnd();

	return true;
}


bool CTokenizer::scanNumeric()
{
	bool retVal = false;

doneScanNumeric:
	if( !retVal)
		_cFile.SelectionEndToSelectionStart();

	return retVal;
}


bool CTokenizer::scanName()
{
	bool retVal = false;

doneScanName:
	if( !retVal)
		_cFile.SelectionEndToSelectionStart();

	return retVal;
}

