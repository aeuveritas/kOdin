#pragma once

#include "types.hpp"
#include "utils.hpp"
#include "keyboard.hpp"

#pragma pack(push, 1)

/// Class for shell [IA-32e Mode]
class kShell
{
    kKeyboard* a_pclKeyboard;
    
public:
    kShell(void);
    ~kShell(void);
    
    void kInitializeShell(kKeyboard* _kKeyboard);
    void kPrompt(void);
};

#pragma pakc(pop)