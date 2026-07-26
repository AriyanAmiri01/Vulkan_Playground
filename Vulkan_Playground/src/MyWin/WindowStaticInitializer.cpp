#pragma once
// WindowStaticInitializer.cpp 
#include "windowStaticInitializer.h"
#include "window.h"


LRESULT windowStaticInitializer::WndStaticProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    window* self;
    if(msg == WM_NCCREATE){
        // After the creationg we initialize a reference to the window.h class from [CREATESTRUCT] from [LPARA]
        CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
        self = static_cast<window*>(cs->lpCreateParams);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(self));
    }
    else{
        // Now we have done creating so we get window.h class from [HWND]
       self = reinterpret_cast<window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    }

    if(self) {
        // Forward to the instance method
        return self->myWindowProcedure.WndProc(hWnd, msg, wParam, lParam, self);
        //return self->WndProc(hWnd, msg, wParam, lParam);
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}