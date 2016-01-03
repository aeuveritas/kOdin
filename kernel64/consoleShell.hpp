#pragma once

#include "types.hpp"
#include "consoleCommand.hpp"

#define CONSOLESHELL_MAXCOMMANDBUFFERCOUNT         300
#define CONSOLESHELL_PROMPT                        "kOdin$ "

#pragma pack(push, 1)

/// Class for console shell [IA-32e Mode]
class kConsoleShell
{
    kConsoleCommand clConsoleCommand;
    
public:
    kConsoleShell(void);
    ~kConsoleShell(void);
    
    void kInitializeConsoleShell(void);
    
    // Shell itself
    void kActivateConsoleShell(void);
};

#pragma pakc(pop)