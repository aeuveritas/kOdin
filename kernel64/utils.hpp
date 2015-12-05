#pragma once

#include "types.hpp"
#include "keyboard.hpp"

/// Class for Utilities
class kUtils
{
public:
    bool kPrintString(int iX, int iY, const char* pcString);
    void kShell(kKeyboard& clKeyboard, DWORD& dwline);
};

