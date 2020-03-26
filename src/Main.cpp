#include <iostream>
#include "TriangleRangeException.h"
#include "TriangleConstructException.h"
#include "InputException.h"
#include "Triangle.h"

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

	// Disable sync with old C-style funcs
	ios_base::sync_with_stdio(false);

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

		if (!wcin)
			throw InputException();

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
	catch (InputException&)
	{
		wcout << L"Стороны должны быть целыми числами в диапазоне от " << Triangle::MIN_EDGE << L" до " << Triangle::MAX_EDGE << "!\n";
	}
	catch (...)
	{
		wcout << L"Случилась неизвестная ошибка!";
	}

	return 0;
}