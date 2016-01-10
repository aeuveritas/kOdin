#pragma once

#include "types.hpp"
#include "consoleCommand.hpp"

#define CONSOLESHELL_MAXCOMMANDBUFFERCOUNT         300
#define CONSOLESHELL_PROMPT                        "kOdin $ "

#pragma pack(push, 1)

/// Console shell [IA-32e Mode]
class kConsoleShell
{
    kConsoleCommand clConsoleCommand;
    
    void kUpdateCursorLocation(void);
    
public:
    kConsoleShell(void);
    ~kConsoleShell(void);
    
    void kInitializeConsoleShell(void);

    void kActivateConsoleShell(void);
};

#pragma pakc(pop)