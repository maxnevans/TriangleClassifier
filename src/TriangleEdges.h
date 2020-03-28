#pragma once
#include <array>

namespace TriangleApp
{
	static constexpr int TriangleEdgesCount = 3;
	typedef int TriangleEdgeSize;

	// Triangle 3 edges type.
	typedef std::array<TriangleEdgeSize, TriangleEdgesCount> TriangleEdges;

	// Triangle edges names.
	enum class TriangleEdgeId
	{
		A = 0,
		B = 1,
		C = 2
	};

	static constexpr std::array<TriangleEdgeId, TriangleEdgesCount> TriangleEdgeIdIterator = {
		TriangleEdgeId::A,
		TriangleEdgeId::B,
		TriangleEdgeId::C
	};

	// Use to get edge from it's name.
	inline TriangleEdges::value_type& getTriangleEdge(TriangleEdges& edges, TriangleEdgeId edgeId)
	{
		auto index = static_cast<typename std::underlying_type<TriangleEdgeId>::type>(edgeId);
		return edges.at(index);
	}

	inline TriangleEdges::value_type getTriangleEdge(const TriangleEdges& edges, TriangleEdgeId edgeId)
	{
		auto index = static_cast<typename std::underlying_type<TriangleEdgeId>::type>(edgeId);
		return edges.at(index);
	}
}
