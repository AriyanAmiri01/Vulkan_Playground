//WindowClass.cpp
#include "windowClass.h"


///////////////////////////////////////////////////
/// WINDOW CLASS MANAGEMENT STUFF
windowClass::windowClass(HINSTANCE& xHInstance)
{
    // Creating the window class
    wc.style =  CS_OWNDC | CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = windowStaticInitializer::WndStaticProc; // This MUST be a valid function pointer
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = xHInstance;
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = NULL;
    wc.lpszClassName = className.c_str();
    wc.lpszMenuName = nullptr; // Or menuName.c_str() if you have one

    RegisterClass(&wc);
}
windowClass::~windowClass()
{
	UnregisterClass(wc.lpszClassName, wc.hInstance);
}


///////////////////////////////////////////////////
/// WINDOW CLASS GETTERS
const std::string& windowClass::getClassName() const
{
	return className;
}