#include <windows.h>
#include <stdio.h>
#include <iostream>
#include<windows.h>

int main()
{
    // Define the five bytes to send ("hello")
    std::string data;
    char output[256] = { "\0" };
    // Declare variables and structures
    HANDLE hSerial;
    DCB dcbSerialParams = { 0 };
    COMMTIMEOUTS timeouts = { 0 };
    DWORD dwBytesWritten;
    DWORD  dwBytesRead;

    // Open the highest available serial port number
    fprintf(stderr, "Opening serial port...");
    hSerial = CreateFile(
        L"\\\\.\\COM4", GENERIC_READ | GENERIC_WRITE, 0, NULL,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSerial == INVALID_HANDLE_VALUE)
    {
        fprintf(stderr, "Error\n");
        return 1;
    }
    else fprintf(stderr, "OK\n");

    // Set device parameters (1200 baud, 1 start bit,
    // 1 stop bit, no parity)
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (GetCommState(hSerial, &dcbSerialParams) == 0)
    {
        fprintf(stderr, "Error getting device state\n");
        CloseHandle(hSerial);
        return 1;
    }

    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (SetCommState(hSerial, &dcbSerialParams) == 0)
    {
        fprintf(stderr, "Error setting device parameters\n");
        CloseHandle(hSerial);
        return 1;
    }

    // Set COM port timeout settings
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    if (SetCommTimeouts(hSerial, &timeouts) == 0)
    {
        fprintf(stderr, "Error setting timeouts\n");
        CloseHandle(hSerial);
        return 1;
    }

    // Lav sådan at while loopet også har en read funktion og kna skifte ligesom en walkie talkie så man kan med en kanp aktiverer
    // write også bagefter reader den også kan man slukke sin write ved at skrive  noget der afslutter loopet
    while (data[0] != 's') {

        std::cout << std::endl << "Enter the data to be sent: ";
        std::cin >> data;

        BOOL bWriteRC = false;
        BOOL bReadRC = false;

        output[0] = 'l';


        Sleep(1000);

        bWriteRC = WriteFile(hSerial, &data, (DWORD)sizeof(data), &dwBytesWritten, NULL);
        Sleep(1000);
        bReadRC = ReadFile(hSerial, &output, sizeof(output), &dwBytesRead, NULL);

        if (bWriteRC)
        {

            if (output[0] == 's')
            {
                std::cout << "Program shutting down: " << std::endl;
                FlushFileBuffers(hSerial);
            }
            else
            {

                std::cout << "Data sent: " << data << std::endl;



                while (output[0] != 'p')
                {
                    bReadRC = ReadFile(hSerial, &output, sizeof(output), &dwBytesRead, NULL);
                }

                if (bReadRC) {
                    // std::cout << "Data received1: " << sizeof(output) << std::endl;
                    // std::cout << "Data received2: " << output << std::endl;
                    std::cout << "Dit input var: ";
                    for (int i = 1; i < sizeof(output); i++) {

                        std::cout << output[i];
                    }
                    std::cout << std::endl;

                }
                else
                {
                    fprintf(stderr, "Error\n");
                    CloseHandle(hSerial);
                    return 1;
                }
            }
        }
        else
        {
			fprintf(stderr, "Error\n");
			CloseHandle(hSerial);
			return 1;
		}
    }
    // Close serial port
    fprintf(stderr, "Closing serial port...");
    if (CloseHandle(hSerial) == 0)
    {
        fprintf(stderr, "Error\n");
        return 1;
    }
    fprintf(stderr, "OK\n");

    // exit normally
    return 0;
}