#pragma once
#include "TriangleException.h"

namespace TriangleApp
{
	/*
		Thrown by Triangle in case of edge size.
		E.g.: -1 or 0 or max(int).
	*/
	class TriangleRangeException :
		public TriangleException
	{
		using TriangleException::TriangleException;
	};
}
