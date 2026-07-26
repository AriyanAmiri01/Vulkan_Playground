// MyException.cpp
#include "MyException.h"
#include <sstream>
#include <exception>
#include <stdexcept>


//////////////////////////////////////////////////////////
/// MY EXCEPTION MANAGEMENT STUFFS
MyException::MyException(int pLine, const char* pFile) noexcept
	:
	line(pLine),
	file(pFile)
{}
const char* MyException::what() const noexcept
{
	std::ostringstream oss;
	oss << "[The Error Type:" << GetType() << "]" << std::endl
		<< "[Description:" << whatBuffer << "]" << std::endl
		<< FinishString() <<std::endl;
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}
std::string MyException::FinishString() const noexcept
{
	std::ostringstream oss;
	oss << "[File]:" << std::endl << "[" << file << "]" << std::endl
		<< "[Line]: " << std::endl << "[" << line << "]" << std::endl;
	return oss.str();
}


//////////////////////////////////////////////////////////
/// MY EXCEPTION GETTERS STUFFS
const char* MyException::GetType() const noexcept
{
	return "Ariyan's The Root Based Exception";
}
int MyException::GetLine() const noexcept
{
	return line;
}
const std::string& MyException::GetFile() const noexcept
{
	return file;
}