#include "Utils.h"

void Utils::readme(String path) 
{
    HANDLE hFile = CreateFile(path.c_str(),
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);


}