#include <iostream>
#include <handleapi.h>
#include <synchapi.h>
#include <windows.h>

void showMenu()
{
    std::cout << "--- Menu ---" << std::endl;
    std::cout << "0 - Exit" << std::endl;
    std::cout << "1 - Connect pipe" << std::endl;
    std::cout << "2 - Read data" << std::endl;
}

int main()
{
    // Размер передаваемого сообщения
    const int bufferSize = 100;

	HANDLE pipe = nullptr;

    char item;
    do
	{
        showMenu();
		std::cin >> item;
		switch (item)
		{
		case '1':
		    /*
		     * Подключаемся к именованному каналу
		     * */
			pipe = CreateFile(
			        "\\\\.\\pipe\\ServerPipe",
                   GENERIC_READ,
                   0,
                   nullptr,
                   OPEN_EXISTING,
                   FILE_FLAG_OVERLAPPED,
                   nullptr);
			if (pipe == INVALID_HANDLE_VALUE)
                std::cout << "Error while executing CreateFile() (error " << GetLastError() << ")" << std::endl;
			else std::cout <<"Successfully connected to the pipe" << std::endl;
			break;
		case '2':
			OVERLAPPED overlappedStruct;
			overlappedStruct.Offset = 0;
			overlappedStruct.OffsetHigh = 0;

			char buffer[bufferSize];
			// Читаем отправленное с сервера сообщение
			ReadFileEx(
                    pipe,
                    buffer,
                    bufferSize,
                    &overlappedStruct,
                    nullptr);
                std::cout << buffer << std::endl;
			break;
		case '0':
			break;
		default:
			std::cout << "Invalid item" << std::endl;
		}
	} while (item != '0');
	CloseHandle(pipe);
	return 0;
}

