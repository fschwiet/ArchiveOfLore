#ifndef _VALUE_TABLE_H_
#define _VALUE_TABLE_H_


template <typename Tin> int Compare( Tin tA, Tin tB);

template <typename Tin, typename Tout>
class CBinaryValueTable
{
public:
	CBinaryValueTable( long lDefaultSize = 16);
	~CBinaryValueTable();

	bool GetElement( Tin tIndex, Tout* ptValue = NULL);
	bool RemoveElement( Tin tIndex, Tout* ptValue = NULL);
	bool AddElement( Tin tIndex, Tout tValue);

	int Size();
	bool EnumElements( IN int iIndex, OUT Tin* ptIndex = NULL, OUT Tout* ptValue = NULL);

private:

	bool hasElement( Tin tIndex, long* plTableIndex);
	bool ensureSpaceForAdd();

	typedef struct STableElement
	{
		Tin tIndex;
		Tout tValue;
	} *PSTableElement;

	long _lTableAllocatedSize;
	long _lTableUsedSize;
	long _lStepSize;

	PSTableElement _pTable;
};


typedef CBinaryValueTable< DWORD, void*> CBinaryValueTableDwP;


//  CBinaryValueTable(SzP/DwzP) points to null-terminated arrays of chars/dwords
typedef CBinaryValueTable< LPCSTR, void*> CBinaryValueTableSzP;
typedef CBinaryValueTable< const DWORD*, void*> CBinaryValueTableDwzP;


template <typename Tin, typename Tout>
CBinaryValueTable<Tin,Tout>::CBinaryValueTable( long lDefaultSize)
{
	_pTable = NULL;
	_lTableAllocatedSize = 0;
	_lTableUsedSize = 0;
	_lStepSize = max( lDefaultSize, 4);
}


template <typename Tin, typename Tout>
CBinaryValueTable<Tin,Tout>::~CBinaryValueTable()
{
	if( _pTable != NULL)
	{
		delete[] _pTable;
		_pTable = NULL;
	}
}


template <typename Tin, typename Tout>
bool CBinaryValueTable<Tin,Tout>::hasElement( Tin tIndex, long* plTableIndex)
{
	long i;
	for( i = 0; i < _lTableUsedSize; i++)
	{
		int iComp = Compare( tIndex, _pTable[i].tIndex);
		if( 0 == iComp)
		{
			if( plTableIndex != NULL)
				*plTableIndex = i;

			return true;
		}
		else if( -1 == iComp)
		{
			return false;
		}
	}

	return false;
}


template <typename Tin, typename Tout>
bool CBinaryValueTable<Tin,Tout>::ensureSpaceForAdd()
{
	if( _pTable == NULL
		|| _lTableUsedSize == _lTableAllocatedSize)
	{
		long lNewSize = _lTableAllocatedSize + _lStepSize;
		PSTableElement pNewTable = new STableElement[ lNewSize];

		if( pNewTable == NULL)
			return false;

		if( _pTable != NULL)
		{
			memcpy( pNewTable, _pTable, sizeof(STableElement) * _lTableUsedSize);
			delete[] _pTable;
		}
		
		_pTable = pNewTable;
		_lTableAllocatedSize = lNewSize;
	}

	return true;
}


template <typename Tin, typename Tout>
bool CBinaryValueTable<Tin,Tout>::GetElement( Tin tIndex, Tout* ptValue)
{
	long lTableIndex;

	if( !hasElement( tIndex, &lTableIndex))
		return false;

	if( ptValue != NULL)
		*ptValue = _pTable[lTableIndex].tValue;

	return true;
}


template <typename Tin, typename Tout>
bool CBinaryValueTable<Tin,Tout>::RemoveElement( Tin tIndex, Tout* ptValue)
{
	long lTableIndex;

	if( !hasElement( tIndex, &lTableIndex))
		return false;

	if( ptValue != NULL)
		*ptValue = _pTable[lTableIndex].tValue;

	_lTableUsedSize--;

	for( ; lTableIndex < _lTableUsedSize; lTableIndex++)
	{
		_pTable[ lTableIndex] = _pTable[ lTableIndex+1];
	}
	return true;
}


template <typename Tin, typename Tout>
bool CBinaryValueTable<Tin,Tout>::AddElement( Tin tIndex, Tout tValue)
{
	int i;

	if( !ensureSpaceForAdd())
		return false;

	if( hasElement( tIndex, NULL))
		return false;
	
	int iComp = 1;
	for( i = _lTableUsedSize; i > 0; i--)
	{
		iComp = Compare( _pTable[i-1].tIndex, tIndex);

		if( 1 != iComp)
			break;
		
		_pTable[i] = _pTable[i-1];
	}

	_pTable[i].tIndex = tIndex;
	_pTable[i].tValue = tValue;
	_lTableUsedSize++;

	return true;
}


template <typename Tin, typename Tout>
int CBinaryValueTable<Tin,Tout>::Size()
{
	return _lTableUsedSize;
}


template <typename Tin, typename Tout>
bool CBinaryValueTable<Tin,Tout>::EnumElements( IN int iIndex, OUT Tin* ptIndex, OUT Tout* ptValue)
{
	if( 0 > iIndex || iIndex >= _lTableUsedSize)
		return false;

	if( ptIndex != NULL)
		*ptIndex = _pTable[iIndex].tIndex;

	if( ptValue != NULL)
		*ptValue = _pTable[iIndex].tValue;

	return true;
}





#endif
