#include <Windows.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

char dllName[50];

std::string line, app;
int takepid, l, i = 0;
char load[4] = { '/', '|', '\\', '+' };

DWORD pid;

char fullFilename[MAX_PATH];

void research()
{
    label:
    system("tasklist > tasklist.txt");
    std::ifstream taskm("tasklist.txt", std::ios::in);

    if (taskm.is_open())
    {
        while (!taskm.eof())
        {
            taskm >> line;
            if (line == app)
            {
                taskm >> pid;
                i++;
            }
        }
    }

    if (pid == NULL)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        goto label;
    }
}

int main() {

    HANDLE hEXE, hThread;

    PVOID address;
    SIZE_T nbytesWritten;

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTitle(L"neoinjectx64");
 
    retry:
    system("CLS");
    SetConsoleTextAttribute(h, 3);

    std::cout 
        << R"(
             .-----------------------------------------------.
             |  _   _           _____       _           _    |
             | | \ | |         |_   _|     (_)         | |   |
             | |  \| | ___  ___  | |  _ __  _  ___  ___| |_  |
             | | . ` |/ _ \/ _ \ | | | '_ \| |/ _ \/ __| __| |
             | | |\  |  __/ (_) || |_| | | | |  __/ (__| |_  |
             | |_| \_|\___|\___/_____|_| |_| |\___|\___|\__| |
             |                            _/ |               |
             |                           |__/                |
             `-----------------------------------------------`
            )";

    SetConsoleTextAttribute(h, 12);
    std::cout << "\n\t\t\t DLL 1NJ3CT0R by NEODRA\n" << std::endl;
    SetConsoleTextAttribute(h, 3);

    std::cout << "[+] DLL'in adini girin: (DLL1.dll, hack.dll vb.)\n " << std::endl;
    std::cout << ">> ";
    std::cin >> dllName;

    std::string title = dllName;
    std::string what = title + " ?";
    int dllLength = strlen(dllName);

    if (dllName[dllLength - 4] != '.' || dllName[dllLength - 3] != 'd' || dllName[dllLength - 2] != 'l' || dllName[dllLength - 1] != 'l')
    {
        int click = MessageBoxA(NULL, "Dosya, \".dll\" uzantýlý olmalý!", what.c_str(), MB_RETRYCANCEL | MB_ICONERROR);
        switch (click)
        {
        case IDRETRY:
            goto retry;
            break;
        case IDCANCEL:
            exit(0);
            break;
        default:
            exit(0);
            break;
        }
    }

    GetFullPathNameA(dllName, MAX_PATH, fullFilename, nullptr);

    std::ifstream fileisExist(fullFilename);
    if (!fileisExist.is_open())
    {
        int click = MessageBoxA(NULL, "DLL BULUNAMADI!", dllName, MB_RETRYCANCEL | MB_ICONERROR);
        switch (click)
        {
        case IDRETRY:
            goto retry;
            break;
        case IDCANCEL:
            exit(0);
            break;
        default:
            exit(0);
            break;
        }
    }

    

    retryApp:
    std::cout << "\n[+] Programin adini girin: (notepad.exe, csgo.exe vb.)\n " << std::endl;
    std::cout << ">> ";
    std::cin >> app;

    std::string title2 = app;
    std::string what2 = title2 + " ?";
    int appLength = app.size();

    if (app[appLength - 4] != '.' || app[appLength - 3] != 'e' || app[appLength - 2] != 'x' || app[appLength - 1] != 'e')
    {
        int click = MessageBoxA(NULL, "Dosya, \".exe\" uzantýlý olmalý!", what2.c_str(), MB_RETRYCANCEL | MB_ICONERROR);
        switch (click)
        {
        case IDRETRY:
            goto retryApp;
            break;
        case IDCANCEL:
            exit(0);
            break;
        default:
            exit(0);
            break;
        }
    }

    std::cout << "\n[+] PROCESS ARANIYOR... (" << app << ") ";

    std::thread process(research);

    while (true)
    {
        if (i >= 1)
        {
            l = 3;
            std::cout << load[l] << "\b";
            break;
        }
        l = 0;
        std::cout << load[l] << "\b";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (i >= 1)
        {
            l = 3;
            std::cout << load[l] << "\b";
            break;
        }
        l = 1;
        std::cout << load[l] << "\b";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (i >= 1)
        {
            l = 3;
            std::cout << load[l] << "\b";
            break;
        }
        l = 2;
        std::cout << load[l] << "\b";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (i >= 1)
        {
            l = 3;
            std::cout << load[l] << "\b";
            break;
        }
        l = 1;
        std::cout << load[l] << "\b";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    process.join();

    std::cout << "\n\n[+] PROCESS BULUNDU >> (" << app << ") PID: " << pid << std::endl;


    hEXE = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    if (hEXE == NULL)
    {
        std::cout << GetLastError() << std::endl;
        return -1;
    }

    address = VirtualAllocEx(hEXE, NULL, strlen(fullFilename) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    if (address == NULL)
    {
        std::cout << GetLastError() << std::endl;
        return -1;
    }

    if (!WriteProcessMemory(hEXE, address, fullFilename, strlen(fullFilename) + 1, &nbytesWritten))
    {
        std::cout << GetLastError() << std::endl;
        return -1;
    }

    hThread = CreateRemoteThread(hEXE, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, address, 0, NULL);

    if (hThread == NULL)
    {
        std::cout << GetLastError() << std::endl;
        return -1;
    }

    MessageBoxA(NULL, "DLL Aktif!", app.c_str(), MB_OK | MB_ICONINFORMATION);

    return 0;
}