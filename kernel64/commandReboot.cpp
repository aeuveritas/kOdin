#include "commandReboot.hpp"
#include "console.hpp"

extern kConsole* g_pclConsole;

/// Constructor of kCommandReboot
kCommandReboot::kCommandReboot(void)
{
    // Command name
    pcCommandName = "reboot";
    
    // Help message
    pcHelp = "Reboot kOdin";
}

/// Destructor of kCommandReboot
kCommandReboot::~kCommandReboot(void)
{

}

/// Initialize kCommandReboot
void kCommandReboot::kInitializeCommandReboot(void)
{

}

/// Execute to reboot
void kCommandReboot::kTask_do(const char* pcParameter)
{
    g_pclConsole->kPrintf("Press any key to reboot ... \n");
    g_pclConsole->kGetCh();
    
    g_pclConsole->kReboot();
}
