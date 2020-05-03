#ifndef __HHELP_H
#define __HHELP_H
#include <windows.h>
#define HH_DISPLAY_TOPIC        0x0000
#define HH_HELP_FINDER          0x0000  // WinHelp equivalent
#define HH_DISPLAY_TOC          0x0001  
#define HH_DISPLAY_INDEX        0x0002  
#define HH_DISPLAY_SEARCH       0x0003  
#define HH_SET_WIN_TYPE         0x0004
#define HH_GET_WIN_TYPE         0x0005
#define HH_GET_WIN_HANDLE       0x0006
#define HH_ENUM_INFO_TYPE       0x0007  // Get Info type name, call repeatedly to enumerate, -1 at end
#define HH_SET_INFO_TYPE        0x0008  // Add Info type to filter.
#define HH_SYNC                 0x0009
#define HH_RESERVED1            0x000A
#define HH_RESERVED2            0x000B
#define HH_RESERVED3            0x000C
#define HH_KEYWORD_LOOKUP       0x000D
#define HH_DISPLAY_TEXT_POPUP   0x000E  // display string resource id or text in a popup window
#define HH_HELP_CONTEXT         0x000F  // display mapped numeric value in dwData
#define HH_TP_HELP_CONTEXTMENU  0x0010  // text popup help, same as WinHelp HELP_CONTEXTMENU
#define HH_TP_HELP_WM_HELP      0x0011  // text popup help, same as WinHelp HELP_WM_HELP
#define HH_CLOSE_ALL            0x0012  // close all windows opened directly or indirectly by the caller
#define HH_ALINK_LOOKUP         0x0013  // ALink version of HH_KEYWORD_LOOKUP
#define HH_GET_LAST_ERROR       0x0014  // not currently implemented // See HHERROR.h
#define HH_ENUM_CATEGORY        0x0015	// Get category name, call repeatedly to enumerate, -1 at end
#define HH_ENUM_CATEGORY_IT     0x0016  // Get category info type members, call repeatedly to enumerate, -1 at end
#define HH_RESET_IT_FILTER      0x0017  // Clear the info type filter of all info types.
#define HH_SET_INCLUSIVE_FILTER 0x0018  // set inclusive filtering method for untyped topics to be included in display
#define HH_SET_EXCLUSIVE_FILTER 0x0019  // set exclusive filtering method for untyped topics to be excluded from display
#define HH_INITIALIZE            0x001C  // Initializes the help system.
#define HH_UNINITIALIZE          0x001D  // Uninitializes the help system.
#define HH_PRETRANSLATEMESSAGE  0x00fd  // Pumps messages. (NULL, NULL, MSG*). 
#define HH_SET_GLOBAL_PROPERTY  0x00fc  // Set a global property. (NULL, NULL, HH_GPROP)
extern "C" HWND __declspec(dllexport)   HHelp( HWND hwndCaller,
    LPCSTR pszFile,
    UINT uCommand,
    DWORD_PTR dwData
    );
#endif