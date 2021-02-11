#include <iostream>
#include "string"
#include "Winsock2.h"  // заголовок WS2_32.dll
#pragma comment (lib, "WS2_32.lib") // экспорт WS2_32.dll

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

string  SetErrorMsgText(string msgText, int code)
{
    return  msgText + GetErrorMsgText(code);
};



int main()
{
    WSADATA wsaData;
    SOCKET sS; // дескриптор сокета


        //...........................................................
        try
        {


            if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)  //Инициализация  библиотеки Windows Sockets
                throw  SetErrorMsgText("Startup:", WSAGetLastError());
            if ((sS = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET) // Создание сокета
                throw  SetErrorMsgText("socket:", WSAGetLastError());
   
            
            //.............................................................
   
     
            if (closesocket(sS) == SOCKET_ERROR)                            //Закрытие сокета
                throw  SetErrorMsgText("closesocket:", WSAGetLastError());


            if (WSACleanup() == SOCKET_ERROR) //Завершение работы с библиотекой  Windows Sockets
                throw  SetErrorMsgText("Cleanup:", WSAGetLastError());
        }
        catch (string errorMsgText)
        {
            cout << endl << errorMsgText;
        }

        //................................................................
        return 0;
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
