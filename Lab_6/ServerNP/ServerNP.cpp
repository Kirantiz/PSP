
#include <iostream>
#include <Windows.h>

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

string  SetPipeError(string msgText, int code)
{
    return  msgText + GetErrorMsgText(code);
};








int main()
{

    HANDLE hPipe; // дескриптор канала
    char buf[128];
    DWORD lBuf;
    try 
    {
        while (true) {
        if ((hPipe = CreateNamedPipe(L"\\\\.\\pipe\\Tube",
            PIPE_ACCESS_DUPLEX,           //дуплексный канал 
            PIPE_TYPE_MESSAGE | PIPE_WAIT,  // сообщения|синхронный
            1, NULL, NULL,                 // максимум 1 экземпляр
            INFINITE, NULL)) == INVALID_HANDLE_VALUE)
            throw SetPipeError("create:", GetLastError());
        cout << "Server waiting Client" << endl;
     
        if (!ConnectNamedPipe(hPipe, NULL))           // ожидать клиента   
            throw SetPipeError("connect:", GetLastError());
        else
        {
            cout << "Connected" << endl;
        }
        while (true)
        {
        ConnectNamedPipe(hPipe, NULL);
        ReadFile(hPipe, buf, sizeof(buf), &lBuf, NULL);
      
        if (strcmp(buf, "stop") == 0)
            break;
        cout << buf << endl;
        WriteFile(hPipe, buf, sizeof(buf), &lBuf, NULL);


        //.................................................................. 


        if (buf[0] == 'C')
            DisconnectNamedPipe(hPipe);
        }
        DisconnectNamedPipe(hPipe);
        CloseHandle(hPipe);
        }
    }
    catch(string ErrorPipeText)
    {
        cout << ErrorPipeText.c_str() << endl;
    }
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
