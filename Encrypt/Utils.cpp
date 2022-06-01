#include "Utils.h"

void Utils::readme(String path) 
{
    HANDLE hFile = CreateFile(
        path.c_str(),
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (hFile != INVALID_HANDLE_VALUE)
    {
        std::vector<String> message
        {
            _T("Your text.\n"),
            _T("bla bla bla.\n")
        };

        for (const auto& msg : message)
        {
            DWORD dwBytesToWrite{ (DWORD)_tcslen(msg.c_str()) * sizeof(TCHAR) };
            DWORD dwBytesWritten{ 0 };

            WriteFile(
                hFile,
                msg.c_str(),
                dwBytesToWrite,
                &dwBytesWritten,
                NULL);
        }

        CloseHandle(hFile);
    }
}