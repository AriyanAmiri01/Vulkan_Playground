#pragma once
// WindowProcedure.cpp
#include "WindowProcedure.h"
#include "Window.h"


////////////////////////////////////////////////////////////////////////////
/// MAIN WINDOW PROCEDURE - MESSAGE HANDLER
LRESULT windowProcedure::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, window* xMyWindow)
{
    // Handle incoming window messages
    switch(msg)
    {
        // Window position and size change messages
    case(WM_MOVE):
        {
            moveHandler(lParam, xMyWindow);
            break;
        }
    case(WM_WINDOWPOSCHANGED):
        {
            handleChangeWindow(hwnd, lParam, xMyWindow);
            break;
        }
        // Mouse input messages
    case(WM_MOUSEMOVE):
        {
            handleMouseMove(lParam, xMyWindow);
            break;
        }

    case(WM_RBUTTONDOWN):
        {
            handleRPress(wParam, lParam, xMyWindow);
            break;
        }
    case(WM_RBUTTONUP):
        {
            handleRRelease(wParam, lParam, xMyWindow);
            break;
        }
    case(WM_LBUTTONDOWN):
        {
            handleLPress(wParam, lParam, xMyWindow);
            break;
        }
    case(WM_LBUTTONUP):
        {
            handleLRelease(wParam, lParam, xMyWindow);
            break;
        }
    case(WM_MBUTTONDOWN):
        {
            handleMPress(wParam, lParam, xMyWindow);
            break;
        }
    case(WM_MBUTTONUP):
        {
            handleMRelease(wParam, lParam, xMyWindow);
            break;
        }
    case(WM_LBUTTONDBLCLK):
        {
            // Double-click left button (currently unused)
            break;
        }
    case(WM_RBUTTONDBLCLK):
        {
            // Double-click right button (currently unused)
            break;
        }
    case(WM_MOUSEWHEEL):
        {
            handleMouseScroll(wParam, xMyWindow);
            break;
        }
        // Keyboard input messages
    case(WM_KEYDOWN):
        {
            handleKeyDown(wParam, lParam, xMyWindow);
            break;
        }
    case(WM_KEYUP):
        {
            handleKeyUp(wParam, xMyWindow);
            break;
        }
    case(WM_CHAR):
        {
            handleChar(wParam, xMyWindow);
            break;
        }
    case(WM_SYSKEYDOWN):
        {
            handleSyskeyDown(wParam, lParam, xMyWindow);
            break;
        }
    case(WM_SYSKEYUP):
        {
            handleSyskeyUp(wParam, xMyWindow);
            break;
        }
        // Special window messages
    case WM_CLOSE:
    {
        PostQuitMessage(0);
        return 0;
    }
    case(WM_KILLFOCUS):
        {
            xMyWindow->myKeyboard.ClearState(); // Clear keyboard state when window loses focus
            break;
        }
    default:
        {
            return DefWindowProc(hwnd, msg, wParam, lParam); // Default message handling
        }
    }
    return 0;
}


//////////////////////////////////////////////////////
/// INDIVIDUAL MESSAGE HANDLER FUNCTIONS
void windowProcedure::moveHandler(LPARAM xLParam, window* xMyWindow)
{
    // Update window position coordinates
    xMyWindow->myWindowManager.changeWindowX((int)(short)LOWORD(xLParam));
    xMyWindow->myWindowManager.changeWindowY((int)(short)HIWORD(xLParam));
}
void windowProcedure::handleChangeWindow(HWND xHwnd, LPARAM xLParam, window* xMyWindow)
{
    // Update window client area rectangle when window position or size changes
    WINDOWPOS* pos = (WINDOWPOS*)xLParam;
    RECT clientRect;
    GetClientRect(xHwnd, &clientRect);
    xMyWindow->myWindowManager.changeWindowRect(clientRect);
}
void windowProcedure::handleChar(WPARAM wParam, window* xMyWindow)
{
    // Process character input for text input handling
    xMyWindow->myKeyboard.CharSignal(static_cast<unsigned char>(wParam));
}
void windowProcedure::handleKeyDown(WPARAM wParam, LPARAM lParam, window* xMyWindow)
{
    // Handle key press, ignoring autorepeat if disabled
    if(!((lParam & 0x40000000) || (xMyWindow->myKeyboard.AutorepeatIsEnable())))
    {
        xMyWindow->myKeyboard.KeyPressSignal(static_cast<unsigned char>(wParam));
    }
}
void windowProcedure::handleKeyUp(WPARAM wParam, window* xMyWindow)
{
    // Handle key release event
    xMyWindow->myKeyboard.KeyReleaseSignal(static_cast<unsigned char>(wParam));
}
void windowProcedure::handleSyskeyDown(WPARAM wParam, LPARAM lParam, window* xMyWindow)
{
    // Handle system key press (Alt or other system keys), ignoring autorepeat if disabled
    if(!((lParam & 0x40000000) || (xMyWindow->myKeyboard.AutorepeatIsEnable())))
    {
        xMyWindow->myKeyboard.KeyPressSignal(static_cast<unsigned char>(wParam));
    }
}
void windowProcedure::handleSyskeyUp(WPARAM wParam, window* xMyWindow)
{
    // Handle system key release event
    xMyWindow->myKeyboard.KeyReleaseSignal(static_cast<unsigned char>(wParam));
}


//////////////////////////////////////////////////////
/// MOUSE MESSAGE HANDLERS
void windowProcedure::handleMouseMove(LPARAM xLParam, window* xMyWindow)
{
    // Process mouse movement, track when cursor enters or exits the client area
    const POINTS pt = MAKEPOINTS(xLParam);
    if(pt.x >= 0 && pt.x < xMyWindow->myWindowManager.GetWindowWidth() &&
        pt.y >= 0 && pt.y < xMyWindow->myWindowManager.GetWindowHeight())
    {
        xMyWindow->myMouse.MouseMoveSignal(pt.x, pt.y);
        if(!xMyWindow->myMouse.GetIsInside())
        {
            SetCapture(xMyWindow->getHwnd()); // Capture mouse input when inside window
            xMyWindow->myMouse.MouseEnterSignal();
        }
    }
    else
    {
        if(xLParam & (MK_LBUTTON | MK_RBUTTON))
        {
            xMyWindow->myMouse.MouseMoveSignal(pt.x, pt.y);
        }
        else
        {
            ReleaseCapture(); // Release mouse capture when cursor leaves window
            xMyWindow->myMouse.MouseExitSignal();
        }
    }
}
void windowProcedure::handleRPress(WPARAM xWParam, LPARAM xLParam, window* xMyWindow)
{
    // Handle right mouse button press
    xMyWindow->myMouse.RightPressSignal(LOWORD(xLParam), HIWORD(xLParam), int(xWParam));
}
void windowProcedure::handleRRelease(WPARAM xWParam, LPARAM xLParam, window* xMyWindow)
{
    // Handle right mouse button release
    xMyWindow->myMouse.RightReleaseSignal(LOWORD(xLParam), HIWORD(xLParam), int(xWParam));
}
void windowProcedure::handleLPress(WPARAM xWParam, LPARAM xLParam, window* xMyWindow)
{
    // Handle left mouse button press
    xMyWindow->myMouse.LeftPressSignal(LOWORD(xLParam), HIWORD(xLParam), int(xWParam));
}
void windowProcedure::handleLRelease(WPARAM xWParam, LPARAM xLParam, window* xMyWindow)
{
    // Handle left mouse button release
    xMyWindow->myMouse.LeftReleaseSignal(LOWORD(xLParam), HIWORD(xLParam), int(xWParam));
}
void windowProcedure::handleMPress(WPARAM xWParam, LPARAM xLParam, window* xMyWindow)
{
    // Handle middle mouse button press (usually mouse wheel click)
    xMyWindow->myMouse.ScrollPressSignal(LOWORD(xLParam), HIWORD(xLParam), int(xWParam));
}
void windowProcedure::handleMRelease(WPARAM xWParam, LPARAM xLParam, window* xMyWindow)
{
    // Handle middle mouse button release
    xMyWindow->myMouse.ScrollReleaseSignal(LOWORD(xLParam), HIWORD(xLParam), int(xWParam));
}
void windowProcedure::handleMouseScroll(WPARAM xWParam, window* xMyWindow)
{
    // Handle mouse wheel scrolling input
    xMyWindow->myMouse.CursorMoveSignal(HIWORD(xWParam));
}
void windowProcedure::handleMouseEnter(window* xMyWindow)
{
    // Notify that mouse cursor has entered the window client area
    xMyWindow->myMouse.MouseEnterSignal();
}
void windowProcedure::handleMouseExit(window* xMyWindow)
{
    // Notify that mouse cursor has exited the window client area
    xMyWindow->myMouse.MouseExitSignal();
}