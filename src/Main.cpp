#include <iostream>
#include "TriangleRangeException.h"
#include "TriangleConstructException.h"
#include "InputException.h"
#include "Triangle.h"
#include "Operation.h"

void printTriangleType(TriangleApp::TriangleType tType)
{
	using namespace std;
	using namespace TriangleApp;

	wcout << L"Треугольник ";

	switch (tType)
	{
		case TriangleType::BASIC:
			wcout << L"неравносторонний";
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

void checkWcinError(bool& error)
{
	if (!std::wcin)
	{
		std::wcin.clear();
		error = true;
	}
}

TriangleApp::TriangleEdges readTriangleEdges()
{
	using namespace std;
	using namespace TriangleApp;

	wcout << L"Введите 3 стороны треугольника через пробелы и/или через переводы строки: ";

	TriangleEdges edges;

	bool hasError = false;

	wcin >> getTriangleEdge(edges, TriangleEdgeId::A);
	checkWcinError(hasError);
	wcin >> getTriangleEdge(edges, TriangleEdgeId::B);
	checkWcinError(hasError);
	wcin >> getTriangleEdge(edges, TriangleEdgeId::C);
	checkWcinError(hasError);

	if (hasError)
	{
		std::wcin.seekg(std::ios::end);
		throw InputException();
	}
		

	return edges;
}


Operation readOperation()
{
	using namespace std;

	wcout << L"1. Для выполнения вычислений введите ""/calc"".\n";
	wcout << L"2. Для подсказки введите ""/help"".\n";
	wcout << L"3. Для выхода из программы введите ""/exit"".\n";
	std::wstring strOperation;
	wcin >> strOperation;

	if (strOperation == L"/calc")
		return Operation::CALC;

	if (strOperation == L"/help")
		return Operation::HELP;

	if (strOperation == L"/exit")
		return Operation::EXIT;

	return Operation::UNKNOWN;
}

void printGreetings()
{
	using namespace std;
	using namespace TriangleApp;

	std::wcout << L"Добро пожаловать!\n"
		"Программа определяет тип треугольника\n"
		"Необходимо ввести 3 целых положительных числа в диапазоне от " << Triangle::MIN_EDGE << L" до " << Triangle::MAX_EDGE << L".\n"
		"Треугольник существует, если сумма любых двух сторон больше третьей.\n"
		"Равносторонний - треугольник, у которого все стороны равны.\n"
		"Равнобедренный - треугольник, у которого 2 стороны равны.\n"
		"Неравностороний - треугольник, у которого все стороны различны.\n";
}

void mainFunction()
{
	using namespace std;
	using namespace TriangleApp;

	try
	{
		auto edges = readTriangleEdges();

		Triangle triangle(edges);

		auto type = triangle.classify();

		printTriangleType(type);
	}
	catch (TriangleRangeException&)
	{
		wcout << L"Стороны должны быть целыми числами в диапазоне от " << Triangle::MIN_EDGE << L" до " << Triangle::MAX_EDGE << "!\n";
	}
	catch (TriangleConstructException&)
	{
		wcout << L"Стороны не образуют треугольник!Треугольник существует тогда и только тогда, когда сумма любых двух его сторон больше третьей (А+В>C, A+C>B, B+C>A, где А, В, С – длины сторон треугольника).\n";
	}
	catch (InputException&)
	{
		wcout << L"Стороны должны быть целыми числами в диапазоне от " << Triangle::MIN_EDGE << L" до " << Triangle::MAX_EDGE << "!\n";
	}
}

void operationLoop(bool& shouldExit)
{
	using namespace std;

	bool successOperation = true;
	do
	{
		auto operation = readOperation();

		switch (operation)
		{
		case Operation::EXIT:
			successOperation = true;
			shouldExit = true;
			break;
		case Operation::CALC:
			successOperation = true;			
			mainFunction();
			break;
		case Operation::HELP:
			successOperation = true;
			printGreetings();
			break;
		case Operation::UNKNOWN:
		default:
			successOperation = false;
			wcout << L"Неизвестная операция! Повторите ввода заново!\n";
			break;
		}
	} while (!successOperation);
}


int wmain()
{
	using namespace std;
	using namespace TriangleApp;

	// Disable sync with old C-style funcs
	ios_base::sync_with_stdio(false);

	setlocale(LC_ALL, "ru-RU");

	printGreetings();

	try
	{
		bool shouldExit = false;
		do
		{
			operationLoop(shouldExit);
		} while (!shouldExit);
	}
	catch (...)
	{
		wcout << L"Случилась неизвестная ошибка!";
	}

	return 0;
}