#pragma once
#include <array>

namespace TriangleApp
{
	// Triangle 3 edges type.
	typedef std::array<int, 3> TriangleEdges;

	// Triangle edges names.
	enum class TriangleEdgeId
	{
		A = 0,
		B = 1,
		C = 2
	};

	// Use to get edge from it's name.
	inline size_t getTriangleEdge(const TriangleEdges& edges, TriangleEdgeId edgeId)
	{
		auto index = static_cast<typename std::underlying_type<TriangleEdgeId>::type>(edgeId);
		return edges.at(index);
	}
}
