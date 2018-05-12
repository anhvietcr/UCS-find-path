#include "Graph.h"

int main(int argc, char* argv[])
{
	Graph * graph = new Graph(argv[1]);
	
	graph->path(argv[2]);

	return 0;
}