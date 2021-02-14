#include <iostream>
#include "string"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include "Winsock2.h"  // заголовок WS2_32.dll
#pragma comment (lib, "WS2_32.lib") // экспорт WS2_32.dll
#pragma warning(disable : 4996)


using namespace std;

string  GetErrorMsgText(int code)    // формируется текст ошибки 
{
    string msgText;
    switch (code)                      // проверка кода возврата  
    {
    case WSAEINTR:          msgText = "WSAEINTR";         break;
    case WSAEACCES:         msgText = "WSAEACCES";        break;
    case WSAHOST_NOT_FOUND: msgText = "WSAHOST_NOT_FOUND";break;
    case WSATRY_AGAIN:      msgText = "WSATRY_AGAIN";     break;
    case WSAEADDRNOTAVAIL:  msgText = "WSAEADDRNOTAVAIL"; break;
    case WSAENOTCONN:       msgText = "WSAENOTCONN";      break;
    case WSAEHOSTUNREACH:   msgText = "WSAEHOSTUNREACH";  break;
    case WSAEHOSTDOWN:      msgText = "WSAEHOSTDOWN";     break;
    case WSAECONNREFUSED:   msgText = "WSAECONNREFUSED";  break;
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
    SOCKET cC; // дескриптор сокета
    int maxlen = 512; //размер буфера
    char* result_string = new char[maxlen];


        //...........................................................
    try
    {

        for (int i = 1; i <= 200; i++) {
            if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)  //Инициализация  библиотеки Windows Sockets
                throw  SetErrorMsgText("Startup:", WSAGetLastError());
            if ((cC = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET) // Создание сокета
                throw  SetErrorMsgText("socket:", WSAGetLastError());

            SOCKADDR_IN serv;                    // параметры  сокета сервера
            serv.sin_family = AF_INET;           // используется IP-адресация  
            serv.sin_port = htons(2000);                   // TCP-порт 2000
            serv.sin_addr.s_addr = inet_addr("127.0.0.1");  // адрес сервера


            if ((connect(cC, (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR)
                throw  SetErrorMsgText("connect:", WSAGetLastError());


            char obuf[50] = "Hello from Client_";  //буфер вывода
            char ibuf[512];                     // буфер приёма
            int  lobuf = 0;                    //количество отправленных байт 
            int libuf = 0;                     //количество принятых байт
            
            _itoa(lobuf+i, obuf + 18, 10);

            if ((lobuf = send(cC, obuf, strlen(obuf) + 1, NULL)) == SOCKET_ERROR)
                throw  SetErrorMsgText("send:", WSAGetLastError());
            cout << "Send: " << obuf << endl;
            i++;
            
            if ((libuf = recv(cC, ibuf, sizeof(ibuf), 0)) == SOCKET_ERROR)
                throw  SetErrorMsgText("recv:", WSAGetLastError());
            _itoa(i, ibuf + 18, 10);
            cout << ibuf << endl;

            // for (int i = 1; i <= 1000; i++) 
             //{



      //  }
        //.............................................................


            if (closesocket(cC) == SOCKET_ERROR)                            //Закрытие сокета
                throw  SetErrorMsgText("closesocket:", WSAGetLastError());


            if (WSACleanup() == SOCKET_ERROR) //Завершение работы с библиотекой  Windows Sockets
                throw  SetErrorMsgText("Cleanup:", WSAGetLastError());
        }
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
