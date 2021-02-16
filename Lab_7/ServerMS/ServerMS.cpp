
#include <iostream>
#include <Windows.h>
#include <string>
#include <time.h>
#include <ctime>  

using namespace std;

string  GetErrorMsgText(int code)    // формируется текст ошибки 
{
    string msgText;
    switch (code)                      // проверка кода возврата  
    {
    case WSAEINTR:          msgText = "WSAEINTR";         break;
    case WSAEACCES:         msgText = "WSAEACCES";        break;
        //..........коды WSAGetLastError ..........................
    case WSASYSCALLFAILURE: msgText = "WSASYSCALLFAILURE"; break;
    default:                msgText = "***ERROR***";      break;
    };
    return msgText;
};

string  SetMailError(string msgText, int code)
{
    return  msgText + GetErrorMsgText(code);
};


int main()
{
    HANDLE hM;
    DWORD rb, lBuf;
    char buf[128];
 
    try
    {
       

        cout << "Waiting..." << endl;

        if ((hM = CreateMailslot(L"\\\\.\\mailslot\\Box", // адрес имени канала Mailslot
            300, // максимальный размер сообщения
            180000, // время ожидания для чтения
            NULL //адрес структуры защиты
        )) == INVALID_HANDLE_VALUE)

            throw "CreateMailslotError";
       
        
        while (true)
        {
            
            if (!ReadFile(hM, buf, sizeof(buf), &rb, NULL))
                throw "ReadFileError";
            

            if (strcmp(buf, "stop") == 0)
                break;
            cout << buf << endl;
           







        }



        CloseHandle(hM);
    }
    catch (char* error)
    {
        cout << error << endl;
        int t = clock();
        cout << "Time: " << ((float)t) / CLOCKS_PER_SEC << " seconds" << endl;
       
    }

    system("pause");

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
