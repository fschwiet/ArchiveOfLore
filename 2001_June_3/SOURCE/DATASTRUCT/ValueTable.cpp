#include "fsGlobal.h"

#include "ValueTable.h"



//template class CBinaryValueTable< DWORD, void*>;
//typedef CBinaryValueTable< DWORD, void*> CBinaryValueTableDwP;

//template class  CBinaryValueTable< LPCSTR, void*>;
//typedef CBinaryValueTable< LPCSTR, void*> CBinaryValueTableSzP;

#include "fsGlobal.h"



template<typename T> int Compare( T a, T b )
{
  if( a < b)
	  return -1;
  else if ( a == b)
	  return 0;
  else
	  return 1;
}


template<> int Compare<LPCSTR>( LPCSTR szA, LPCSTR szB)
{
	int i = -1;

	do
	{
		i++;
		if( szA[i] < szB[i])
			return -1;
		else if (szA[i] > szB[i])
			return 1;
	}
	while( szA[i] != '\0' && szB[i] != '\0');
	
	return 0;
}


template<> int Compare<const DWORD*>( const DWORD* szA, const DWORD* szB)
{
	int i = -1;

	do
	{
		i++;
		if( szA[i] < szB[i])
			return -1;
		else if (szA[i] > szB[i])
			return 1;
	}
	while( szA[i] != 0 && szB[i] != 0);
	
	return 0;
}
