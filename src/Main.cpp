#include <iostream>
#include "TriangleRangeException.h"
#include "TriangleConstructException.h"
#include "Triangle.h"
#include <limits>

void printTriangleType(TriangleApp::TriangleType tType)
{
	using namespace std;
	using namespace TriangleApp;

	wcout << L"Треугольник ";

	switch (tType)
	{
		case TriangleType::BASIC:
			wcout << L"обычный";
			break;
		case TriangleType::EQUILATERAL:
			wcout << L"равносторонний";
			break;
		case TriangleType::ISOSCELES:
			wcout << L"равнобедренный";
			break;
		default:
			wcout << L"неизвестного типа";
	}

	wcout << L".\n";
}

int wmain()
{
	using namespace std;
	using namespace TriangleApp;

	setlocale(LC_ALL, "ru-RU");

	try 
	{
		wcout << L"Введите 3 стороны треугольника через пробелы: ";

		TriangleEdges::value_type a = 0;
		TriangleEdges::value_type b = 0;
		TriangleEdges::value_type c = 0;

		wcin >> a;
		wcin >> b;
		wcin >> c;

		Triangle triangle({a, b, c});

		auto type = triangle.classify();

		printTriangleType(type);
	}
	catch (TriangleRangeException&)
	{
		wcout << L"Стороны должны быть целыми числами в диапазоне от " << Triangle::MIN_EDGE << L" до " << Triangle::MAX_EDGE << "!\n";
	}
	catch (TriangleConstructException&)
	{
		wcout << L"Стороны не образуют треугольник!\n";
	}

	return 0;
}