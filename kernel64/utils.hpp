#pragma once

#include "types.hpp"
#include "keyboardManager.hpp"

class kUtils
{
public:
    bool kPrintString(int iX, int iY, const char* pcString);
    void kShell(kKeyboardManager& clKM, DWORD& dwline);
};

