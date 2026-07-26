#pragma once
// MyConsole.cpp
#include "MyConsole.h"
#include "MyHeaders.h" //Here to provide exception utilities and avoid circular dependencies


////////////////////////////////////////////////////////////
/// MY CONSOLE MANAGER STUFF
void myConsole::go()
{
    // Attempt to allocate a new console window.
    // If allocation fails (console already allocated), throw an exception.
    if(!AllocConsole()) {
        EXCEPT_FREE("Failed to allocate console");
    }

    // Redirect the standard IO streams to the newly allocated console:
    // - stdout and stderr for output
    // - stdin for input
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
    freopen_s(&fp, "CONIN$", "r", stdin);

    // Synchronize C++ standard streams with the C standard streams
    std::ios::sync_with_stdio();
}
myConsole::~myConsole()
{
    // Detach and destroy the console window when the object is destroyed
    FreeConsole();
}