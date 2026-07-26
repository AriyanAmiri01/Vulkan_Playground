// FreeExcept.cpp
#include "FreeExcept.h"


////////////////////////////////////////////////////////////////////
/// FREE EXCEPTION MANAGEMENT STUFFS
freeExcept::freeExcept(std::string xWhat, int xLine, const char* xFile)
	:
	MyException(xLine, xFile)
{
	whatBuffer = xWhat;
}
const char* freeExcept::GetType() const noexcept
{
	return "Free window Exception";
}