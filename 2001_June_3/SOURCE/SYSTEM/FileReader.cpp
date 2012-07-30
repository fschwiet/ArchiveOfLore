#include "fsGlobal.h" 

#include "fileutil.h"


CFileReader::CFileReader()
{
	_hFile = INVALID_HANDLE_VALUE;

	_iStartIndexBuffer = -1;
	_iStartIndex = 0;
	_iEndIndexBuffer = -1;
	_iEndIndex = 0;
}


CFileReader::~CFileReader()
{
	if( _hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle( _hFile);
		_hFile = INVALID_HANDLE_VALUE;
	}
}


bool CFileReader::loadBuffer( int iBufferIndex, HANDLE hFile)
{
	DWORD dwBytesToRead, dwBytesRead;

	dwBytesToRead = sizeof( _pBuffer[0]);

	if( 0 == ReadFile( hFile, _pBuffer[iBufferIndex], dwBytesToRead, &dwBytesRead, NULL))
		return false;

	memset( _pBuffer[iBufferIndex] + dwBytesRead, 0, dwBytesToRead - dwBytesRead);

	return true;
}


bool CFileReader::OpenFile( LPCTSTR szFilename)
{
	bool retVal = false;

	HANDLE hNewFile = CreateFile( szFilename, GENERIC_READ, 0, NULL,
		                          OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if( hNewFile == INVALID_HANDLE_VALUE)
		goto doneOpenFile;

	if( !(loadBuffer(0, hNewFile) && loadBuffer(1, hNewFile)))
	{
		goto doneOpenFile;
	}

	if( _hFile != INVALID_HANDLE_VALUE)
		CloseHandle( _hFile);

	_hFile = hNewFile;
	hNewFile = INVALID_HANDLE_VALUE;

	_iStartIndexBuffer = 0;
	_iStartIndex = 0;
	_iEndIndexBuffer = 0;
	_iEndIndex = 0;

	retVal = true;

doneOpenFile:
	if( hNewFile != INVALID_HANDLE_VALUE)
		CloseHandle( hNewFile);

	return retVal;
}


bool CFileReader::GetSelected( OUT LPSTR szSelected, IN OUT int* piSize)
{
	if( _iEndIndexBuffer == -1)
	{
		*piSize = 0;
		return false;
	}
	
	int iSelectionSize = _iEndIndexBuffer == _iStartIndexBuffer
		? _iEndIndex - _iStartIndex
		: sizeof( _pBuffer[0]) - _iStartIndex + _iEndIndex;

	if( iSelectionSize > *piSize)
	{
		*piSize = iSelectionSize;
		return false;
	}

	if( _iEndIndexBuffer == _iStartIndexBuffer)
	{
		memcpy( szSelected, _pBuffer[ _iStartIndexBuffer] + _iStartIndex, iSelectionSize);
	}
	else
	{
		memcpy( szSelected, _pBuffer[ _iStartIndexBuffer] + _iStartIndex, 
			    sizeof(_pBuffer[0]) - _iStartIndex);
		memcpy( szSelected + sizeof(_pBuffer[0]) - _iStartIndex,
				_pBuffer[_iEndIndexBuffer], _iEndIndex);
	}

	*piSize = iSelectionSize;
	return true;
}


bool CFileReader::SelectionStartToSelectionEnd()
{
	_iStartIndexBuffer = _iEndIndexBuffer;
	_iStartIndex = _iEndIndex;
	return true;
}


bool CFileReader::SelectionEndStep()
{
	if( _iEndIndex + 1 >= sizeof(_pBuffer[0]))
	{
		int iNextBuffer = (_iEndIndexBuffer + 1) % 2; 
		if( _iStartIndexBuffer == iNextBuffer)
			return false;

		if( !loadBuffer( iNextBuffer, _hFile))
			return false;

		_iEndIndexBuffer = iNextBuffer;
		_iEndIndex = 0;
		return true;
	}
	else
	{
		_iEndIndex++;
		return true;
	}
}


bool CFileReader::SelectionEndToSelectionStart()
{
	_iEndIndexBuffer = _iStartIndexBuffer;
	_iEndIndex = _iStartIndex;
	return true;
}


char CFileReader::GetCharPastSelection()
{
	return _pBuffer[ _iEndIndexBuffer][_iEndIndex];
}
