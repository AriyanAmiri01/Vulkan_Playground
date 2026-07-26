#pragma once
// MyHeaders.h

// Disable UNICODE and _UNICODE macros to avoid conflicts
#ifdef UNICODE
#undef UNICODE
#endif
#ifdef _UNICODE
#undef _UNICODE
#endif

// Prevent Windows headers from defining min and max macros, which can cause conflicts
#define NOMINMAX

// Set Windows version macros to target Windows 10 (build 1903 / version 0x0A00)
// This helps avoid compatibility warnings when using newer Windows API features

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 26446) // Disable specific warning during macro definitions
#endif

#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00

#ifndef _WIN32_WINNT_WIN10_RS1
#define _WIN32_WINNT_WIN10_RS1 0x0A00
#endif

#ifndef _WIN32_WINNT_WIN10_RS2
#define _WIN32_WINNT_WIN10_RS2 0x0A00
#endif

#ifndef _WIN32_WINNT_WIN10_RS3
#define _WIN32_WINNT_WIN10_RS3 0x0A00
#endif

#ifndef _WIN32_WINNT_WIN10_RS4
#define _WIN32_WINNT_WIN10_RS4 0x0A04
#endif

#ifndef _WIN32_WINNT_WIN10_RS5
#define _WIN32_WINNT_WIN10_RS5 0x0A00
#endif

#ifndef _WIN32_WINNT_WIN10_TH2
#define _WIN32_WINNT_WIN10_TH2 0x0A03  // Windows 10 Fall Creators Update
#endif

#ifdef _MSC_VER
#pragma warning(pop)
#endif

// Include main Windows API header
#include <windows.h>

// Include custom error handling classes
#include "MyExp/MyException.h"
#include "MyExp/FreeExcept.h"
#include "MyExp/windowException.h"

// Include console management utilities
#include "MyWin/myConsole.h"