#include "pch.h"
#include <windows.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <math.h>
using namespace std;
bool wayToSort(double i, double j) { return i > j; }
int main()
{
	HANDLE   hNamedPipe;
	DWORD   dwBytesRead;     // для количества прочитанных байтов
	DWORD   dwBytesWrite;    // для количества записанных байтов
	LPCSTR     pchMessage[3];   // для сообщения
	int    nMessageLength;   // длина сообщения
	char  pchResponse[80];
	double arrsum = 0;
	double arrmult = 1;
	double arrminabs = DBL_MAX;
	double arrmaxabs = DBL_MIN;
	int iminabs;
	int imaxabs;

	// создаем именованный канал для чтения и записи
	hNamedPipe = CreateNamedPipe(
		L"\\\\.\\pipe\\demo_pipe",  // имя канала
		PIPE_ACCESS_DUPLEX,        // читаем из канала и пишем в канал
		PIPE_TYPE_MESSAGE | PIPE_WAIT,   // синхронная передача сообщений
		1,         // максимальное количество экземпляров канала 
		0,         // размер выходного буфера по умолчанию
		0,         // размер входного буфера по умолчанию
		INFINITE,  // клиент ждет связь бесконечно долго
		NULL       // безопасность по умолчанию
	);
	// проверяем на успешное создание
	if (hNamedPipe == INVALID_HANDLE_VALUE)
	{
		cerr << "Create named pipe failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		cout << "Press any key to exit.";
		cin.get();

		return 0;
	}

	// ждем, пока клиент свяжется с каналом
	cout << "The server is waiting for connection with a client." << endl;
	if (!ConnectNamedPipe(
		hNamedPipe,    // дескриптор канала
		NULL      // связь синхронная
	))
	{
		cerr << "Connect named pipe failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hNamedPipe);
		cout << "Press any key to exit.";
		cin.get();

		return 0;
	}
	// читаем сообщение от клиента
	if (!ReadFile(
		hNamedPipe,      // дескриптор канала
		pchMessage,      // адрес буфера для ввода данных
		sizeof(pchMessage)+1,  // количество читаемых байтов
		&dwBytesRead,    // количество прочитанных байтов
		NULL))           // передача данных синхронная
	{
		cerr << "Data reading from the named pipe failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hNamedPipe);
		cout << "Press any key to exit.";
		cin.get();

		return 0;
	}

	// выводим полученное от клиента сообщение на консоль
	cout << "The server received the message from a client: " << endl;
	for (int i = 0; i < sizeof(pchMessage); i++)
	{
		cout << pchMessage[i];
	}


	// cout<<pchResponse<< endl;
	// отвечаем клиенту
	/*if (!WriteFile(
		hNamedPipe,      // дескриптор канала
		pchResponse,      // адрес буфера для вывода данных
		nMessageLength,  // количество записываемых байтов
		&dwBytesWrite,   // количество записанных байтов
		NULL             // передача данных синхронная
	))
	{
		cerr << "Write file failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hNamedPipe);
		cout << "Press any key to exit.";
		cin.get();

		return 0;
	}*/

	// выводим посланное клиенту сообщение на консоль
	//cout << "The server sent the message to a client: "
	//	<< endl << '\t' << pchResponse << endl;

	// закрываем дескриптор канала 
	CloseHandle(hNamedPipe);
	// завершаем процесс
	cout << "Press any key to exit.";
	cin.get();

	return 0;
}