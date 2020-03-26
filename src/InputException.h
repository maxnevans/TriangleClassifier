#pragma once
#include "Exception.h"

/*
	Thrown in Main.cpp by main function to indicate bad user input.
*/

class InputException :
	public Exception
{
	using Exception::Exception;
};