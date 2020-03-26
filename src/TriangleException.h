#pragma once
#include "Exception.h"

namespace TriangleApp
{
	/*
		Base triangle exception.
	*/

	class TriangleException :
		public Exception
	{
		using Exception::Exception;
	};
}
