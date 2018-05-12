#pragma once
#include "NODE.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue> 

class Graph
{
private:
	std::ifstream in;
	std::ofstream out;

	int start, end, soCanh, soDinh;
	int * visited;
	int * tracer;
	std::string **nameStreet;

	float length;
	std::vector<int> *dinh;
	std::vector<float> *cost;
	std::vector<std::string> result;

	bool UCS();
	bool inQueue(std::priority_queue<NODE>, int);
	NODE getNodeinQueue(std::priority_queue<NODE>, int);
public:
	Graph(char*);
	void path(char*);
};

