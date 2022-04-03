
#include "Exception.h"


Exception::Exception() {

}


Exception::Exception(const char* msg, const char* file,int line) noexcept
	:
	line(line),
	file(file),
	msg(msg)
{}

const char* Exception::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Exception::GetType() const noexcept
{
	return "Exception";
}

int Exception::GetLine() const noexcept
{
	return line;
}

const std::string& Exception::GetFile() const noexcept
{
	return file;
}

std::string Exception::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << line;
	return oss.str();
}