#include <iostream>
#include "string"
#include <time.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include "Winsock2.h"  // заголовок WS2_32.dll
#pragma comment (lib, "WS2_32.lib") // экспорт WS2_32.dll
#pragma warning(disable : 4996)
#include <cstdlib>


using namespace std;

string  GetErrorMsgText(int code)    // формируется текст ошибки 
{
    string msgText;
    switch (code)                      // проверка кода возврата  
    {
    case WSAEINTR:          msgText = "WSAEINTR";         break;
    case WSAEACCES:         msgText = "WSAEACCES";        break;
    case WSAHOST_NOT_FOUND: msgText = "WSAHOST_NOT_FOUND"; break;
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
    int msg;
    clock_t start, stop;

    //...........................................................
    try
    {
        cout << "Enter the number of messages" << endl;
        cin >> msg;
        cout << endl;
        start = clock();
        for (int i = 1; i <= msg; i++) {
            if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)  //Инициализация  библиотеки Windows Sockets
                throw  SetErrorMsgText("Startup:", WSAGetLastError());
            if ((cC = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET) // Создание сокета
                throw  SetErrorMsgText("socket:", WSAGetLastError());

            SOCKADDR_IN serv;                    // параметры  сокета сервера
            serv.sin_family = AF_INET;           // используется IP-адресация  
            serv.sin_port = htons(2000);                   // TCP-порт 2000
            serv.sin_addr.s_addr = inet_addr("127.0.0.1");  // адрес сервера

            char* obuf = new char[maxlen];  //буфер вывода
            char* ibuf = new char[maxlen];                         // буфер приёма
            int  lobuf = 0;                       //количество отправленных байт 
            int libuf = 0;                        //количество принятых байт

         //   _itoa(lobuf + i, obuf + 20, 10);
           _snprintf_s(obuf, maxlen, maxlen, "Hello from client U_");
           _itoa(lobuf + i, obuf + 20, 10);
            if ((lobuf = sendto(cC, obuf, strlen(obuf), 0, (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR)
                throw  SetErrorMsgText("send:", WSAGetLastError());
            cout << "Send: " << obuf << endl;


            libuf = recvfrom(cC, ibuf, strlen(ibuf),0, 0,0);
            cout << "Otvet ot server: ";
            if (libuf > 0) {
                ibuf[libuf] = 0;
                cout << (char*)ibuf << endl;
            }



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
    stop = clock();
    cout << "Time: " << (stop - start) / CLK_TCK << endl;
    system("pause");
    //................................................................
    return 0;
}


/*
clock_t start, stop;
unsigned long t;
start = clock();
for (t = 0; t < 500000L; t + +);
stop = clock();
printf("Loop required %f seconds", (stop - start) / CLK_TCK);

*/



// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
