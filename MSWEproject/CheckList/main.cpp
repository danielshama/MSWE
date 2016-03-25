#include <windows.h>
#include <stdio.h>
#include <string>
#include "ItemList.h"
#include "CheckList.h"
using namespace std;

HANDLE hStdin;
DWORD fdwSaveOldMode;

VOID ErrorExit(LPSTR);
VOID KeyEventProc(KEY_EVENT_RECORD);
/*VOID MouseEventProc(MOUSE_EVENT_RECORD);*/
VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);

int main(VOID)
{
	ItemList cl = ItemList(10,10,"daniel");
	cl.create();
	getchar();

	return 0;

}
VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
	printf("Resize event\n");
	printf("Console screen buffer is %d columns by %d rows.\n", wbsr.dwSize.X, wbsr.dwSize.Y);
}
