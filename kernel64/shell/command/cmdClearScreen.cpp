#include "cmdClearScreen.hpp"
#include "console.hpp"

extern kConsole* g_pclConsole;

/// Constructor of kCommandClearScreen
kCommandClearScreen::kCommandClearScreen(void)
{
    // Command Name
    pcCommandName = "cls";
    
    // Help message
    pcHelp = "Clear screen";
}

/// Destructor of kCommandClearScreen
kCommandClearScreen::~kCommandClearScreen(void)
{

}

/// kInitialize kCommandClearScreen
void kCommandClearScreen::kInitializeCommandClearScreen(void)
{

}

/// Execute to clear screen
void kCommandClearScreen::kTask_do(const char* pcParameter)
{
    if (pcParameter == nullptr)
    {
        return;
    }
    
    g_pclConsole->kClearScreen();
    
    return;
}