
#include <iostream>
#include <Windows.h>
#include <string>
#include <time.h>
#include <ctime>  

using namespace std;

int main()
{
    HANDLE      ss, sc, sc2;
    LPCTSTR     errMsg;
    BOOL        err;
    DWORD       numWritten;

    sc = CreateMailslot(L"\\\\.\\mailslot\\sc", 0, MAILSLOT_WAIT_FOREVER, NULL);
    ss = CreateFile(L"\\\\*\\mailslot\\ss", GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (ss == INVALID_HANDLE_VALUE)
    {
        printf("CreateFile failed. ");
        // Close any mailslot we opened
        if (ss != INVALID_HANDLE_VALUE) CloseHandle(ss);
        return -1;
    }

    char x[100];
    char z[100];

    printf("Write the damn sentence:");
    cin.getline(x, 100);
    err = WriteFile(ss, x, sizeof(x), &numWritten, 0);
    if (!err) printf("WriteFile failed. ");
    DWORD rd;

    ReadFile(sc, x, sizeof(x), &rd, NULL);
    cout << x << endl;
    ReadFile(sc, z, sizeof(z), &rd, NULL);
    cout << z;

    return 0;
}