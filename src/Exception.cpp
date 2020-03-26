#include "Exception.h"

Exception::Exception(std::wstring message)
	:
	message(message)
{
}

std::wstring Exception::what() noexcept
{
	return this->message;
}
