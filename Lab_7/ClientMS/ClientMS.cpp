#include <iostream>
#include <Windows.h>
#include <string>
#include <ctime>  

using namespace std;

int main()
{

	HANDLE hM;  // дескриптор почтового ящика 
	DWORD lBuf;  // длина записанного сообщения
	int msg;
	DWORD rb;

	try 
	{

		if ((hM = CreateFile(L"\\\\.\\mailslot\\Box",
			GENERIC_WRITE, // будем писать в ящик 
			FILE_SHARE_READ | FILE_SHARE_WRITE, // разрешаем одновременно читать
			NULL,
			OPEN_EXISTING,   //  ящик уже есть
			NULL, NULL)) == INVALID_HANDLE_VALUE)
			throw "CreateFileError";
		cout << "Enter number of message: ";
		cin >> msg;
		for (int i = 0; i < msg; i++)
		{
			char buf[128] = "Hello from Maislot-client";
			strcat_s(buf, to_string(i + 1).c_str());
			if (!WriteFile(hM, buf, // буфер
				sizeof(buf),		// размер буфера
				&lBuf,				// записано
				NULL))
				throw "WriteFileError";



			if (strcmp(buf, "stop") == 0)
				break;
			cout << buf << endl;


		}

		CloseHandle(hM);
	}

	catch (char* error)
	{
		cout << error << endl;

	}
	int t = clock();
	cout << "Time: " << ((float)t) / CLOCKS_PER_SEC << " seconds" << endl;
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
