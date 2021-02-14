#include <iostream>
#include "string"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
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
    bool mem = false;
    int maxlen = 512; //размер буфера
    char* result_string = new char[maxlen];

        //...........................................................
        try
        {


            if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)  //Инициализация  библиотеки Windows Sockets
                throw  SetErrorMsgText("Startup:", WSAGetLastError());
            if ((sS = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET) // Создание сокета
                throw  SetErrorMsgText("socket:", WSAGetLastError());
   
            
            SOCKADDR_IN serv;                     // параметры  сокета sS
            serv.sin_family = AF_INET;           // используется IP-адресация  
            serv.sin_port = htons(2000);          // порт 2000
            serv.sin_addr.s_addr = INADDR_ANY;   // любой собственный IP-адрес 

            if (bind(sS, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR) // Установка параметров сокета, с помощью функции bind
                throw  SetErrorMsgText("bind:", WSAGetLastError());

            if (listen(sS, SOMAXCONN) == SOCKET_ERROR) //Переключение сокета в режим прослушивания
                throw  SetErrorMsgText("listen:", WSAGetLastError());
            while (true) {
            SOCKET cS;	                 // сокет для обмена данными с клиентом 
            SOCKADDR_IN clnt;             // параметры  сокета клиента
            memset(&clnt, 0, sizeof(clnt)); // обнулить память
            int lclnt = sizeof(clnt);    // размер SOCKADDR_IN
            
                if ((cS = accept(sS, (sockaddr*)&clnt, &lclnt)) == INVALID_SOCKET) // создание канала связи
                    throw  SetErrorMsgText("accept:", WSAGetLastError());

                if (mem == false) {
                    cout << "IP adress client: " << inet_ntoa(clnt.sin_addr) << endl;
                    cout << "Port client: " << htons(clnt.sin_port) << endl;
                    mem = true;
                }

                char ibuf[1000];                   //буфер ввода 
                int  libuf = 0;                    //количество принятых байт

                if ((libuf = recv(cS, ibuf, maxlen, 0)) == SOCKET_ERROR)
                    throw  SetErrorMsgText("recv:", WSAGetLastError());

                cout << ibuf << endl;

                //_snprintf_s(result_string, maxlen, maxlen, ibuf);

                send(cS, ibuf, strlen(ibuf), 0);
                cout << "Send answer:_" << ibuf << endl;      

   /*                            if ((libuf = recv(cS, ibuf, sizeof(ibuf), NULL)) == SOCKET_ERROR)
                    throw  SetErrorMsgText("recv:", WSAGetLastError());


                //char obuf[50] = "Hello from Client_";  //буфер вывода
                int  lobuf = 0;                    //количество отправленных байт 

                //_itoa(lobuf, ibuf + sizeof("Hello from Client_") - 1, 10);

                if ((lobuf = send(sS, ibuf, strlen(ibuf) + 1, NULL)) == SOCKET_ERROR)
                    throw  SetErrorMsgText("send:", WSAGetLastError());  

*/


            }
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
