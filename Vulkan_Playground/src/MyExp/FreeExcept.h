#pragma once
#include "MyException.h"


class freeExcept : public MyException
{
	using MyException::MyException;
public:
	freeExcept(std::string xWhat, int xLine, const char* xFile);
	virtual const char* GetType() const noexcept;
};

#define EXCEPT_FREE(x)  throw freeExcept(x, __LINE__, __FILE__)