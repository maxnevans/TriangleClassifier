#include "Triangle.h"
#include <algorithm>
#include "TriangleRangeException.h"
#include "TriangleConstructException.h"

TriangleApp::Triangle::Triangle(const TriangleEdges& edges)
	:
	edges(edges)
{
	verified = false;
}

TriangleApp::TriangleEdges::value_type TriangleApp::Triangle::edgeA() const
{
	return TriangleApp::getTriangleEdge(edges, TriangleEdgeId::A);
}

TriangleApp::TriangleEdges::value_type TriangleApp::Triangle::edgeB() const
{
	return TriangleApp::getTriangleEdge(edges, TriangleEdgeId::B);
}

TriangleApp::TriangleEdges::value_type TriangleApp::Triangle::edgeC() const
{
	return TriangleApp::getTriangleEdge(edges, TriangleEdgeId::C);
}

TriangleApp::TriangleEdges::value_type TriangleApp::Triangle::edge(TriangleEdgeId edgeId) const
{
	return TriangleApp::getTriangleEdge(edges, edgeId);
}

TriangleApp::TriangleType TriangleApp::Triangle::classify()
{
	if (!verified)
		verify();

	// shortcuts for edges
	auto a = edgeA();
	auto b = edgeB();
	auto c = edgeC();

	// equilateral triangle test
	if (a == b && b == c)
		return TriangleType::EQUILATERAL;

	// isosceles triangle test
	if (b == c)
		return TriangleType::ISOSCELES;

	return TriangleType::BASIC;
}

void TriangleApp::Triangle::verify()
{
	std::sort(edges.begin(), edges.end());

	if (!isValidRange())
		throw TriangleRangeException();

	if (!isValidEdges())
		throw TriangleConstructException();

	verified = true;
}

bool TriangleApp::Triangle::isValidRange()
{
	for (const auto& edge : edges)
		if (edge < MIN_EDGE || edge > MAX_EDGE)
			return false;

	return true;
}

bool TriangleApp::Triangle::isValidEdges()
{
	for (const auto& edge : edges)
		if (edge >= getExclusiveEdgesSum(TriangleEdgeId(&edge - &edges[0])))
			return false;

	return true;
}

TriangleApp::TriangleEdges::value_type TriangleApp::Triangle::getExclusiveEdgesSum(TriangleEdgeId edgeId)
{
	TriangleEdges::value_type sum = 0;

	for (const auto& e : edges)
		sum += e;

	sum -= edge(edgeId);

	return sum;
}
