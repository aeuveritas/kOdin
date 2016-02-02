#pragma once

#include <types.hpp>
#include "command/consoleCommand.hpp"

#define CONSOLESHELL_MAXCOMMANDBUFFERCOUNT         300
#define CONSOLESHELL_PROMPT                        "kOdin $ "

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