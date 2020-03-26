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
		TriangleEdges::value_type edgeA() const;
		TriangleEdges::value_type edgeB() const;
		TriangleEdges::value_type edgeC() const;
		TriangleEdges::value_type edge(TriangleEdgeId edgeId) const;
		TriangleType classify();

	private:
		void verify();
		bool isValidRange();
		bool isValidEdges();
		TriangleEdges::value_type getExclusiveEdgesSum(TriangleEdgeId edgeId);

	public:
		// to prevent overflow when verifing if sum of 2 edge weights is greater than the one being compared
		static constexpr TriangleEdges::value_type MAX_EDGE = std::numeric_limits<TriangleEdges::value_type>::max() / 2;
		static constexpr TriangleEdges::value_type MIN_EDGE = 1;

	private:
		TriangleEdges edges = { MIN_EDGE, MIN_EDGE, MIN_EDGE };
		bool verified = true;

	};
}
