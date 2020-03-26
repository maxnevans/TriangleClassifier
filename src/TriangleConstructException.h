#pragma once
#include "TriangleException.h"

namespace TriangleApp
{

	/*
		Thrown from Triangle in case of invalid edge sizes.
		E.g.: 1, 2, 3.		1 + 2 = 3		- wrong edge sizes.
	*/

	class TriangleConstructException :
		public TriangleException
	{
		using TriangleException::TriangleException;
	};
}
