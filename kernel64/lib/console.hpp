#pragma once

#include <types.hpp>
#include <keyboard.hpp>
#include "port.hpp"

/// Macros

/// Properties of Video Memory
#define CONSOLE_BACKGROUND_BLACK            0x00
#define CONSOLE_BACKGROUND_BLUE             0x10
#define CONSOLE_BACKGROUND_GREEN            0x20
#define CONSOLE_BACKGROUND_CYAN             0x30
#define CONSOLE_BACKGROUND_RED              0x40
#define CONSOLE_BACKGROUND_MAGENTA          0x50
#define CONSOLE_BACKGROUND_BROWN            0x60
#define CONSOLE_BACKGROUND_WHITE            0x70
#define CONSOLE_BACKGROUND_BLINK            0x80
#define CONSOLE_FOREGROUND_DARKBLACK        0x00
#define CONSOLE_FOREGROUND_DARKBLUE         0x01
#define CONSOLE_FOREGROUND_DARKGREEN        0x02
#define CONSOLE_FOREGROUND_DARKCYAN         0x03
#define CONSOLE_FOREGROUND_DARKRED          0x04
#define CONSOLE_FOREGROUND_DARKMAGENTA      0x05
#define CONSOLE_FOREGROUND_DARKBROWN        0x06
#define CONSOLE_FOREGROUND_DARKWHITE        0x07
#define CONSOLE_FOREGROUND_BRIGHTBLACK      0x08
#define CONSOLE_FOREGROUND_BRIGHTBLUE       0x09
#define CONSOLE_FOREGROUND_BRIGHTGREEN      0x0A
#define CONSOLE_FOREGROUND_BRIGHTCYAN       0x0B
#define CONSOLE_FOREGROUND_BRIGHTRED        0x0C
#define CONSOLE_FOREGROUND_BRIGHTMAGENTA    0x0D
#define CONSOLE_FOREGROUND_BRIGHTYELLOW     0x0E
#define CONSOLE_FOREGROUND_BRIGHTWHITE      0x0F

/// Default color of character
#define CONSOLE_DEFAULTTEXTCOLOR            (CONSOLE_BACKGROUND_BLACK | \
                                             CONSOLE_FOREGROUND_BRIGHTGREEN)

/// Width and Hight of console
#define CONSOLE_WIDTH                       80
#define CONSOLE_HEIGHT                      25

/// Start address of video memory
#define CONSOLE_VIDEOMEMORYADDRESS          0xB8000

/// I/O ports of video controller
#define VGA_PORT_INDEX                      0x3D4
#define VGA_PORT_DATA                       0x3D5

/// Registers of video controller
#define VGA_INDEX_UPPERCURSOR               0x0E
#define VGA_INDEX_LOWERCURSOR               0x0F

#define TAB_SIZE                            4

#pragma pack(push, 1)

/// Console [IA-32e Mode] 
class kConsole
{
    // Class pointer for kPort
    kPort* a_pclPort;
    
    // Class pointer for kKeyboard
    kKeyboard* a_pclKeyboard;
    
    // Location of cursor
    int iCursorLocationStamp;
    
    int iCursorX;
    int iCursorY;
    
    int iPairY;
    
public:
    kConsole(void);
    ~kConsole(void);
    
    void kInitializeConsole(kPort* pcPort, kKeyboard* pcKeyboard, int iCursorX, int iCursorY);
    void kSetCursor(int iX, int iY);
    void kGetCursor(int* piX, int* piY);
    void kPrintf(const char* pcFormatString, ...);
    int kConsolePrintString(const char* pcBuffer);
    void kClearScreen(void);
    BYTE kGetCh(void);
    void kPrintStringXY(int iX, int iY, const char* pcString);
    void kPrintTry(const char* pcBuffer);
    void kPrintResultIntValue(const int iValue);
    void kPrintResultStrValue(const char* pcVuffer);
    void kPrintResult(const char* pcBuffer);

    void kReboot(void);
};

#pragma pack(pop)