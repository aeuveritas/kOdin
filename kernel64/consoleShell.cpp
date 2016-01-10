#include "consoleShell.hpp"
#include "console.hpp"
#include "keyboard.hpp"
#include "memory.hpp"
#include "stringHelper.hpp"

extern kConsole* g_pclConsole;
extern kMemory* g_pclMemory;
extern kStringHelper* g_pclStringHelper;

/// Constructor of kConsoleShell
kConsoleShell::kConsoleShell(void)
{

}

/// Destructor of kConsoleShell
kConsoleShell::~kConsoleShell(void)
{

}

/// Initialize kConsoleShell
void kConsoleShell::kInitializeConsoleShell(void)
{
    clConsoleCommand.kInitializeConsoleCommand();
}

/// Update cursor location on the monitor
void kConsoleShell::kUpdateCursorLocation(void)
{
    int iCursorX;
    int iCursorY;
    
    char bufferX[10] = { 0, };
    char bufferY[10] = { 0, };
    
    g_pclConsole->kPrintStringXY(70, 0, "[X:  Y:  ]");
        
    g_pclConsole->kGetCursor(&iCursorX, &iCursorY);
        
    g_pclStringHelper->kDecimalToString(iCursorX, bufferX);
    g_pclStringHelper->kDecimalToString(iCursorY, bufferY);
        
    g_pclConsole->kPrintStringXY(73, 0, bufferX);
    g_pclConsole->kPrintStringXY(77, 0, bufferY);
}


/// Shell prompt
void kConsoleShell::kActivateConsoleShell()
{
    char caCommandBuffer[CONSOLESHELL_MAXCOMMANDBUFFERCOUNT];
    int iCommandBufferIndex = 0;
    BYTE bKey = 0;
    int iCursorX = 0;
    int iCursorY = 0;
    
    g_pclConsole->kPrintf(CONSOLESHELL_PROMPT);
    
    while (1)
    {
        // Update cursor location
        kUpdateCursorLocation();
        
        // Wait for key input
        bKey = g_pclConsole->kGetCh();
        
        // BACKSPACE
        if (bKey == KEY_BACKSPACE)
        {
            if (iCommandBufferIndex > 0 )
            {
                // Delete the last character from screen and command buffer
                g_pclConsole->kGetCursor(&iCursorX, &iCursorY);
                g_pclConsole->kPrintStringXY(iCursorX - 1, iCursorY, " ");
                g_pclConsole->kSetCursor(iCursorX - 1, iCursorY);
                iCommandBufferIndex--;
            }
        }
        // ENTER
        else if (bKey == KEY_ENTER)
        {
            g_pclConsole->kPrintf("\n");
            
            if (iCommandBufferIndex > 0)
            {
                // Execute command
                caCommandBuffer[iCommandBufferIndex] = '\0';
                clConsoleCommand.kExecuteCommand(caCommandBuffer);
            }
            
            // Print prompt and initialize command buffer
            g_pclConsole->kPrintf("%s", CONSOLESHELL_PROMPT);
            g_pclMemory->kMemSet(caCommandBuffer, '\0', CONSOLESHELL_MAXCOMMANDBUFFERCOUNT);
            iCommandBufferIndex = 0;
        }
        // Ignore CTRL, ALT, Shift, Caps Lock, Num Lock, Scroll Lcok
        else if ((bKey == KEY_CTRL) ||
                 (bKey == KEY_LALT) ||
                 (bKey == KEY_RSHIFT) ||
                 (bKey == KEY_LSHIFT) ||
                 (bKey == KEY_CAPSLOCK) ||
                 (bKey == KEY_NUMLOCK) ||
                 (bKey == KEY_SCROLLLOCK))
        {
            ;
        }       
        else
        {
            // Tab is empty space
            if (bKey == KEY_TAB)
            {
                bKey = ' ';
            }
            
            // If there is enough space
            if (iCommandBufferIndex < CONSOLESHELL_MAXCOMMANDBUFFERCOUNT)
            {
               caCommandBuffer[iCommandBufferIndex++] = bKey;
               g_pclConsole->kPrintf("%c", bKey);
            }       
        }       
    }
}