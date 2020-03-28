#include <iostream>
#include <sstream>
#include "TriangleRangeException.h"
#include "TriangleConstructException.h"
#include "InputException.h"
#include "Triangle.h"
#include "Operation.h"
#include <vector>

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

void readTriangleEdge(TriangleApp::TriangleEdges& edges, TriangleApp::TriangleEdgeId edgeId)
{
	using namespace std;
	using namespace TriangleApp;

	wstring strEdge;
	wcin >> strEdge;

	try
	{
		getTriangleEdge(edges, edgeId) = stoi(strEdge);

		if (strEdge.front() == L'0' && strEdge.size() > 1)
		{
			wstringstream message;
			message << L"Длина стороны не должна начинаться с 0!\n";

			throw InputException(message.str());
		}
			
	}
	catch (invalid_argument&)
	{
		wstringstream message;
		message << L"Стороны должны быть целыми числами в диапазоне от " << Triangle::MIN_EDGE << L" до " << Triangle::MAX_EDGE << "!\n";

		throw InputException(message.str());
	}
	catch (out_of_range&)
	{
		wstringstream message;
		message << L"Стороны должны быть целыми числами в диапазоне от " << Triangle::MIN_EDGE << L" до " << Triangle::MAX_EDGE << "!\n";

		throw InputException(message.str());
	}
}

TriangleApp::TriangleEdges readTriangleEdges()
{
	using namespace std;
	using namespace TriangleApp;

	wcout << L"Введите 3 стороны треугольника через пробелы и/или через переводы строки: ";

	TriangleEdges edges = {};
	vector<wstring> errorMessages;

	for (const auto edgeId : TriangleEdgeIdIterator)
	{
		try
		{
			readTriangleEdge(edges, edgeId);
		}
		catch (InputException& exception)
		{
			errorMessages.push_back(exception.what());
		}
	}

	if (errorMessages.size() > 0)
	{
		std::wcin.clear();
		std::wcin.seekg(std::ios::end);

		wstringstream ss;

		for (auto message : errorMessages)
			ss << message;

		throw InputException(ss.str());
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
	catch (InputException& exception)
	{
		wcout << exception.what();
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