#include "commandClearScreen.hpp"
#include "console.hpp"

extern kConsole* g_pclConsole;

/// Constructor of kCommandClearScreen
kCommandClearScreen::kCommandClearScreen(void)
{
    // Command Name
    pcCommandName = "cls";
    
    // Help message
    pcHelp = "Clear screen\n";
}

/// Deconstructor of kCommandClearScreen
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
    g_pclConsole->kClearScreen();
    
    // The first line is debuggin console area, so leave it empty
    g_pclConsole->kSetCursor(0, 1);
    
    return;
}