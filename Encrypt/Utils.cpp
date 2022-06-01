#include "Utils.h"

VOID Utils::Readme(String path) 
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

BOOL Utils::DirectoryExists(String dir)
{
    DWORD dwAttrib{ GetFileAttributes(dir.c_str()) };

    return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
           (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

String Utils::UserName()
{
    TCHAR dataBuffer[UNLEN + 1];
    DWORD dwSize{ UNLEN + 1 };

    GetUserName(dataBuffer, &dwSize);
    return String(dataBuffer);
}

String Utils::GetFileExt(String file)
{
    return file.substr(file.find_last_of(L".") + 1);
}