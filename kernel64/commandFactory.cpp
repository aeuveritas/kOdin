#include "commandFactory.hpp"

/// Constructor of kCommandFactory
kCommandFactory::kCommandFactory(void)
{

}

/// Destructor of kCommandFactory
kCommandFactory::~kCommandFactory(void)
{

}

/// Initialize kCommandFactory
void kCommandFactory::kInitializeCommandFactory(kCommandList* pclCommandList)
{
    a_pclCommandList = pclCommandList;
    
    clCommandHelp.kInitializeCommandHelp(a_pclCommandList);
    clCommandClearScreen.kInitializeCommandClearScreen();
    clCommandReboot.kInitializeCommandReboot();
    clCommandRamSize.kInitializeCommandRamSize();
    clCommandStringToDecimalHex.kInitializeCommandStringToDecimalHex();
    clCommandSetTimer.kInitializeCommandSetTimer();
    clCommandWait.kInitializeCommandWait();
    clCommandRDTSC.kInitializeCommandRDTSC();
    clCommandCpuSpeed.kInitializeCommandCpuSpeed();
    clCommandDate.kInitializeCommandDate();
}

/// Update command table
void kCommandFactory::kUpdateCommandTable(void)
{
    a_pclCommandList->kCountCommandTableEntry();
    
    a_pclCommandList->
        kSetTask(COMMAND_HELP, (kCommandTask*)&clCommandHelp);
    a_pclCommandList->
        kSetTask(COMMAND_CLS, (kCommandTask*)&clCommandClearScreen);
    a_pclCommandList->
        kSetTask(COMMAND_REBOOT, (kCommandTask*)&clCommandReboot);
    a_pclCommandList->
        kSetTask(COMMAND_RAMSIZE, (kCommandTask*)&clCommandRamSize);
    a_pclCommandList->
        kSetTask(COMMAND_STRTOD, (kCommandTask*)&clCommandStringToDecimalHex);
    a_pclCommandList->
        kSetTask(COMMAND_SETTIMER, (kCommandTask*)&clCommandSetTimer);
    a_pclCommandList->
        kSetTask(COMMAND_WAIT, (kCommandTask*)&clCommandWait);
    a_pclCommandList->
        kSetTask(COMMAND_RDTSC, (kCommandTask*)&clCommandRDTSC);
    a_pclCommandList->
        kSetTask(COMMAND_CPUSPEED, (kCommandTask*)&clCommandCpuSpeed);
    a_pclCommandList->
        kSetTask(COMMAND_DATE, (kCommandTask*)&clCommandDate);
    
    a_pclCommandList->kCountLongestCommandLength();
}
