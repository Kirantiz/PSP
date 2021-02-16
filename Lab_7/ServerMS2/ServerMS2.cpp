
#include <iostream>
#include <Windows.h>
#include <string>
#include <time.h>
#include <ctime>  

using namespace std;



int main()
{
    HANDLE      ss, sc, sc2r;
    LPCTSTR     errMsg;


    ss = CreateMailslot(L"\\\\.\\mailslot\\ss", 0, MAILSLOT_WAIT_FOREVER, NULL);
    if (ss == INVALID_HANDLE_VALUE)
    {
        printf("Invalid ss value");
        return -1;
    }

    for (;;)
    {
        DWORD   msgSize;
        DWORD nr;
        BOOL    err;

        /* Get the size of the next record */
        err = GetMailslotInfo(ss, 0, &msgSize, 0, 0);
        char x[100];
        char nrr[10];

        if (msgSize != (DWORD)MAILSLOT_NO_MESSAGE)
        {
            DWORD   numRead;
            /* Read the record */
            err = ReadFile(ss, x, msgSize, &numRead, 0);
            int wrds = count(x) + 1;
            sc = CreateFile(L"\\\\*\\mailslot\\sc", GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
            itoa(wrds, nrr, 10);

            err = WriteFile(sc, nrr, sizeof(nrr), &nr, 0);
            //cout<<err<<endl;

            //cout<<x;

            //cout<<err;
            strrev(x);
            err = WriteFile(sc, x, sizeof(x), &nr, 0);
        }
    }
    return(0);
}