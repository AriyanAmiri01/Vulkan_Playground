#pragma once
// WindowClass.h
#include "MyHeaders.h"
#include "windowProcedure.h"
#include "windowStaticInitializer.h"
#include <string>


class windowClass
{
public:
	windowClass(HINSTANCE& xHInstance);
	~windowClass();
public:
	const std::string& getClassName() const;
private:
	std::string className = "class's name";
	std::string menuName = "menu's name";
	WNDCLASS wc = {};
};


