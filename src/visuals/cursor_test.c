#define OEMRESOURCE

#include <windows.h>
#include <stdio.h>
#include <conio.h>

int main()
{
    HICON i = (HICON)LoadImage(0, "pink.ico", IMAGE_ICON, 128, 128, LR_LOADFROMFILE);

    ICONINFO ico;
    GetIconInfo(i, &ico);
    ico.xHotspot = 0;
    ico.yHotspot = 0;

    HCURSOR c = CreateIconIndirect(&ico);

    SetSystemCursor(c, OCR_NORMAL);
}