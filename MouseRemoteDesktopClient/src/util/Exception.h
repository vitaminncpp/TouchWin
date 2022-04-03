#pragma once
#include <exception>
#include <string>
#include <sstream>
class Exception : public std::exception
{
public:
	Exception();
	Exception(const char*, const char* file, int line) noexcept;
	const char* what() const noexcept override;
	virtual const char* GetType() const noexcept;
	int GetLine() const noexcept;
	const std::string& GetFile() const noexcept;
	std::string GetOriginString() const noexcept;
private:
	int line;
	std::string file;
protected:
	mutable std::string whatBuffer;
	std::string msg;
};
