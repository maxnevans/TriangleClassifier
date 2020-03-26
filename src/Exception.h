#pragma once
#include <string>

class Exception
{
public:
	Exception() = default;
	Exception(std::wstring message);
	virtual std::wstring what() noexcept;

private:
	std::wstring message;
};

