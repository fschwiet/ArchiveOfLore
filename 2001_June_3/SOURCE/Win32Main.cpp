#include "fsGlobal.h"

#include "stdio.h"

void testValueTable();
void testSimpleFileReader();


int main(int argc, char* argv[])
{
	testSimpleFileReader();

	return 0;
}


void testValueTable()
{
	CBinaryValueTableSzP cvTest;
	void* pStr;

	cvTest.AddElement( "hello10", "hello10");
	cvTest.AddElement( "hello0", "hello0");
	cvTest.AddElement( "hello2", "hello2");
	cvTest.AddElement( "hello3", "hello3");
	cvTest.AddElement( "hello4", "hello4");
	cvTest.AddElement( "hello1", "hello1");
	cvTest.AddElement( "hello6", "hello6");
	cvTest.AddElement( "hello7", "hello7");
	cvTest.AddElement( "hello8", "hello8");
	cvTest.AddElement( "hello9", "hello9");
	cvTest.AddElement( "hello5", "hello5");
	cvTest.AddElement( "hello11", "hello11");

	if( cvTest.GetElement( "hello8", &pStr))
	{
		printf("\nhello8=%s", pStr);
	}
	if( cvTest.GetElement( "hello20", &pStr))
	{
		printf("\nhello20=%s", pStr);
	}

	cvTest.RemoveElement( "hello11");
	cvTest.RemoveElement( "hello4");
	cvTest.AddElement( "hello20", "hello20");
	cvTest.RemoveElement( "hello8");

	printf("\nand then..");

	if( cvTest.GetElement( "hello8", &pStr))
	{
		printf("\nhello8=%s", pStr);
	}
	if( cvTest.GetElement( "hello20", &pStr))
	{
		printf("\nhello20=%s", pStr);
	}
	NULL;
}


void testSimpleFileReader()
{
	CSimpleFileReader cTest;

	if( !cTest.OpenFile("d:\\frank\\_emacs~"))
		goto doneTestSimpleFileReader;

	int size;
	char buffer[12];
	buffer[11] = '\0';

	do
	{
		for( int i = 0; i < sizeof(buffer)-1; i++)
		{
			//printf("%c", cTest.GetCharPastSelection());
			cTest.SelectionEndStep();
		}
		size = sizeof(buffer) - 1;
		cTest.GetSelected( buffer, &size);
		cTest.SelectionStartToSelectionEnd();
		printf("%s", buffer);
	}
	while( size != sizeof(buffer));

doneTestSimpleFileReader:
	return;
}