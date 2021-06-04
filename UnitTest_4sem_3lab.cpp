// This program was made by Bannikov Nikita, group 9309 
#include "pch.h"
#include "CppUnitTest.h"
#include <stdexcept>
#include <windows.h>
#include "../4sem_3lab/Header.h"
#include "../4sem_3lab/Implementation.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BellmanFord
{
	TEST_CLASS(PathCostUnitTest)
	{
	public:
		PathCostUnitTest() {
			graph = new Graph;
			graph->addEdge("Madrid", "Moscow", 10);
			graph->addEdge("Moscow", "Madrid", 5);
			graph->addEdge("Moscow", "Paris", 40);
			graph->addEdge("Madrid", "Rome", 100);
			graph->addEdge("Moscow", "Rome", 20);
			graph->addEdge("Moscow", "Chicago", 10);
			graph->addEdge("Chicago", "Moscow", 6);
			graph->addEdge("Chicago", "Paris", 10);
			graph->addEdge("Paris", "Chicago", 20);
			graph->addEdge("Chicago", "Rome", 20);
		}

		~PathCostUnitTest() {
			delete graph;
		}
		
		TEST_METHOD(TestMadridRome)
		{
			int cost = graph->minimalCostBellmanFord("Madrid", "Rome");
			Assert::AreEqual(30, cost);
		}

		TEST_METHOD(TestMoscowRome)
		{
			int cost = graph->minimalCostBellmanFord("Moscow", "Rome");
			Assert::AreEqual(20, cost);
		}

		TEST_METHOD(TestChicagoMoscow)
		{
			int cost = graph->minimalCostBellmanFord("Chicago", "Moscow");
			Assert::AreEqual(6, cost);
		}

		TEST_METHOD(TestRomeMadridNotExists)
		{
			int cost = graph->minimalCostBellmanFord("Rome", "Madrid");
			Assert::AreEqual(INT_MAX, cost);
		}

		TEST_METHOD(TestMadridParis)
		{
			int cost = graph->minimalCostBellmanFord("Madrid", "Paris");
			Assert::AreEqual(30, cost);
		}

		TEST_METHOD(TestParisMadrid)
		{
			int cost = graph->minimalCostBellmanFord("Paris", "Madrid");
			Assert::AreEqual(31, cost);
		}

		TEST_METHOD(TestChicagoMadrid)
		{
			int cost = graph->minimalCostBellmanFord("Chicago", "Madrid");
			Assert::AreEqual(11, cost);
		}

		TEST_METHOD(TestMadridChicago)
		{
			int cost = graph->minimalCostBellmanFord("Madrid", "Chicago");
			Assert::AreEqual(20, cost);
		}

		TEST_METHOD(TestParisRome)
		{
			int cost = graph->minimalCostBellmanFord("Paris", "Rome");
			Assert::AreEqual(40, cost);
		}
	private:
		Graph* graph;
	};

	TEST_CLASS(MethodsUnitTest)
	{
	public:
		MethodsUnitTest() {
			graph = new Graph;
		}

		~MethodsUnitTest() {
			delete graph;
		}

		TEST_METHOD(FileDoesNotExist)
		{
			bool exceptionThrown = false;
			try {
				graph->load_from_file("../file_does_not _exists.txt");
			}
			catch (...) {
				exceptionThrown = true;
			}
			Assert::AreEqual(true, exceptionThrown);
		}

		TEST_METHOD(InvalidFileFormat1)
		{
			bool exceptionThrown = false;
			try {
				graph->load_from_file("../invalid_graph_data_1.txt");
			}
			catch (const std::exception& exc) {
				Logger::WriteMessage(exc.what());
				exceptionThrown = true;
			}
			Assert::AreEqual(true, exceptionThrown);
		}

		TEST_METHOD(InvalidFileFormat2)
		{
			bool exceptionThrown = false;
			try {
				graph->load_from_file("../invalid_graph_data_2.txt");
			}
			catch (const std::exception& exc) {
				Logger::WriteMessage(exc.what());
				exceptionThrown = true;
			}
			Assert::AreEqual(true, exceptionThrown);
		}

		TEST_METHOD(InvalidPrice)
		{
			bool exceptionThrown = false;
			try {
				graph->addEdge("Chicago", "Rome", -1);
			}
			catch (const std::exception& exc) {
				exceptionThrown = true;
			}
			Assert::AreEqual(true, exceptionThrown);
		}

		TEST_METHOD(InvalidFrom)
		{
			bool exceptionThrown = false;
			try {
				graph->addEdge("    ", "Rome", 10);
			}
			catch (const std::exception& exc) {
				exceptionThrown = true;
			}
			Assert::AreEqual(true, exceptionThrown);
		}

		TEST_METHOD(InvalidTo)
		{
			bool exceptionThrown = false;
			try {
				graph->addEdge("AAA", "    ", 10);
			}
			catch (const std::exception& exc) {
				exceptionThrown = true;
			}
			Assert::AreEqual(true, exceptionThrown);
		}

	private:
		std::string workingdir(const string& file_name)
		{
			char buf[256];
			GetCurrentDirectoryA(2048, buf);
			return std::string(buf) + '\\' + file_name;
		}

		Graph* graph;
	};
}
