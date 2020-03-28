#pragma once
#include "TriangleEdges.h"
#include "TriangleType.h"
#include <limits>

namespace TriangleApp
{
	/*
		Triangle. Could be any possible and impossible triangle.
		Use Triangle::test to verify triangle.
	*/

	class Triangle
	{
	public:
		Triangle() = default;
		Triangle(const TriangleEdges& edges);
		TriangleEdgeSize edgeA() const;
		TriangleEdgeSize edgeB() const;
		TriangleEdgeSize edgeC() const;
		TriangleEdgeSize edge(TriangleEdgeId edgeId) const;
		TriangleType classify();

	private:
		void verify();
		bool isValidRange();
		bool isValidEdges();
		TriangleEdges::value_type getExclusiveEdgesSum(TriangleEdgeId edgeId);

	public:
		// to prevent overflow when verifing if sum of 2 edge weights is greater than the one being compared
		static constexpr TriangleEdgeSize MAX_EDGE = std::numeric_limits<TriangleEdgeSize>::max() / 2;
		static constexpr TriangleEdgeSize MIN_EDGE = 1;
		static constexpr TriangleEdgeSize INVALID_EDGE = -1;

	private:
		TriangleEdges edges = { MIN_EDGE, MIN_EDGE, MIN_EDGE };
		bool verified = true;

	};
}
