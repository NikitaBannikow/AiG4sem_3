#include "Header.h"

void test_and_print(Graph* graph, string from, string to) {
	int cost = graph->minimalCostBellmanFord(from, to);

	if (cost == INT_MAX) {
		cout << from << "->" << to << ":\tNO FLIGHTS (or error)" << endl;
	}
	else {
		cout << from << "->" << to << ":\t" << cost << endl;
	}
}

int main() {
	try {
		Graph* graph = new Graph;
		cout << "Loading graph from a 'graph_data.txt' file..." << endl;
		graph->load_from_file("graph_data.txt");
		cout << "From->To \tMinimalCost" << endl;
		cout << "---------------------------------------" << endl;

		test_and_print(graph, "Madrid", "Rome");
		test_and_print(graph, "Rome", "Madrid");
		test_and_print(graph, "Chicago", "Moscow");
		test_and_print(graph, "Madrid", "Paris");
		test_and_print(graph, "Paris", "Madrid");
		test_and_print(graph, "Chicago", "Madrid");
		test_and_print(graph, "Madrid", "Chicago");
		test_and_print(graph, "Paris", "Rome");
		delete graph;
	}
	catch (const std::exception& exc) {
		std::cerr << "Error: " << exc.what();
	}

	return 0;
}
