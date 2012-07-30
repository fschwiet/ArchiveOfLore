#ifndef _WIN32_FILEREADER_H_
#define _WIN32_FILEREADER_H_


#define FILEREADER_PAGESIZE 1024



class CFileReader
{
public:
	CFileReader();
	~CFileReader();
	bool OpenFile( IN LPCSTR szFilename);

	bool GetSelected( IN LPSTR szSelected, IN OUT int* piSize);
	bool SelectionStartToSelectionEnd();
	bool SelectionEndStep();
	bool SelectionEndToSelectionStart();
	char GetCharPastSelection();

private:
	HANDLE _hFile;

	char _pBuffer[2][FILEREADER_PAGESIZE];

	int _iStartIndexBuffer;
	int _iStartIndex;
	int _iEndIndexBuffer;
	int _iEndIndex;

	bool loadBuffer( int iBufferIndex, HANDLE hFile);
};



#endif
