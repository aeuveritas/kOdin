#include "utils.hpp"

#pragma pack(push, 1)

/// Print message
bool k32Utils::kPrintString(int iX, int iY, const char* pcString)
{
    CHARACTER* pstScreen = (CHARACTER*) 0xB8000;

    pstScreen += (iY * 80) + iX;

    for (int i = 0; pcString[i] != 0; i++) {
        pstScreen[i].bCharactor = pcString[i];
    }

    return true;
}

#pragma pack(pop)
