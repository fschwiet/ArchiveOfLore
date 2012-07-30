#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_


typedef class CToken
{
public:
	CToken();
	~CToken();

	bool SetNameValue( LPCSTR szValue, int iSize);
	bool SetIntValue( long lValue);
	bool SetFloatValue( float fValue);

	enum enumTokenType
	{
		NAME, INT, FLOAT
	};

	enumTokenType GetType();
	bool GetNameValue( IN LPSTR szValue, IN OUT int* piSize);
	bool GetIntValue( OUT long* plValue);
	bool GetFloatValue( OUT float* pfValue);

private:

	enumTokenType _type;
	
	union
	{
		LPSTR _szValue;
		float _fValue;
		long _lValue;
	};

	void resetValue();

} *PCToken;



typedef class CTokenizer
{
public:
	CTokenizer();
	~CTokenizer();

	bool OpenFile( IN LPCSTR szFilename);
	bool GetNextToken( IN OUT PCToken pToken, OUT int* piLine, OUT int* piColumn);

private:
	CSimpleFileReader _cFile;

	int _iLine, _iColumn;

	BYTE _abCharType[256];
	void initializeCharType();

	bool scanNumeric();
	bool scanName();

} *PCTokenizer;


#endif