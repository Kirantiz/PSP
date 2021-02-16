
#include <iostream>
#include <Windows.h>
#include <string>

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
    case ERROR_PIPE_CONNECTED: msgText = "ERROR_PIPE_CONNECTED"; break;
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
    int msg;
    char buf[128];
    string str;
    DWORD lBuf, bWrite = 128;
    char mes[128] = "Hello from Client";
    try
    {
     
        if ((hPipe = CreateFile(TEXT("\\\\.\\pipe\\Tube"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL)) == INVALID_HANDLE_VALUE)
            throw  SetPipeError("createfile:", GetLastError());
            
  
        //\\servname\pipe\xxxxx
        cout << "Enter number of message: " << endl;
        cin >> msg;
        DWORD dwMode = PIPE_READMODE_MESSAGE; //канал открыт в режиме   передачи сообщениями
        SetNamedPipeHandleState(hPipe, &dwMode, NULL, NULL); //изменяем характеристики канала

        for (int i = 0; i < msg; i++) 
        {

            str = "Hello from Client" +to_string(i + 1);
           // strcpy_s(mes, mess.c_str());
  
            TransactNamedPipe(hPipe, mes, sizeof(mes), buf, sizeof(buf), &lBuf, NULL);
            cout << "Otvet ot serv:_";
            cout << buf << endl;

        }

        WriteFile(hPipe, "stop", sizeof("stop"), &lBuf, NULL);
        CloseHandle(hPipe);
        //.................................................................. 


    }
    catch (string ErrorPipeText)
    {
        cout << endl << ErrorPipeText;
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
