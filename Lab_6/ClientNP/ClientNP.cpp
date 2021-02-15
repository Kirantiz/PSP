
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

    try
    {
     
        if ((hPipe = CreateFile(TEXT("\\\\.\\pipe\\Tube"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL)) == INVALID_HANDLE_VALUE)
            throw  SetPipeError("createfile:", GetLastError());
        //.................................................................. 


    }
    catch (string ErrorPipeText)
    {
        cout << endl << ErrorPipeText;
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
