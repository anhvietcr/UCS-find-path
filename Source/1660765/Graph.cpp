#include "Graph.h"

Graph::Graph(char * input)
{
	this->in.open(input, std::ios::in);
	if (!in) return;
	
	//get node start, end, number vertex, number edge
	in >> start >> end >> soCanh >> soDinh;

	//init vertex and cost
	dinh = new std::vector<int>[soDinh];
	cost = new std::vector<float>[soDinh];

	//init name street
	nameStreet = new std::string*[soDinh];
	for (int i = 0; i < soDinh; i++) {
		nameStreet[i] = new std::string[soDinh];
	}

	//get input
	std::string buffer;
	while (std::getline(in, buffer)) {
		std::stringstream ss(buffer);

		//variable temps
		int a, b;
		float price;
		std::string name;

		//read street from stringstream
		if (ss >> a >> b >> name >> price) {

			//save dinh A <-> B
			dinh[a].push_back(b);
			dinh[b].push_back(a);

			//save cost A <-> B
			cost[a].push_back(price * -1.0);
			cost[b].push_back(price * -1.0);

			//save name street A <-> B
			nameStreet[a][b] = name;
			nameStreet[b][a] = name;

			std::cout << a << " " << b << " " << name << " " << price << "\n";
		}
	}
	//init visited
	visited = new int[soDinh];
	tracer = new int[soDinh];
	memset(visited, 0, sizeof(visited));
	memset(tracer, 0, sizeof(tracer));

	this->in.close();
}

bool Graph::UCS()
{
	std::priority_queue<NODE> Q;
	NODE node;

	//add start to priority queue	
	node.setVertex(start);
	node.setCost(0);
	Q.push(node);

	//search
	while (!Q.empty()) {
		NODE s = Q.top();
		int current = s.getVertex();

		//check match GOAL
		if (current == this->end) {
			this->length = s.getCost() * -1.0;
			return true;
		}

		//remove top element in pQueue
		Q.pop();

		//mark vertex
		visited[current] = 1;

		for (int canh = 0; canh < dinh[current].size(); canh++) {

			//NODE !visited && NODE !in Q 
			if (!visited[dinh[current][canh]] && !inQueue(Q, dinh[current][canh])) {
				//push child node to PQueue
				NODE temps;
				temps.setVertex(dinh[current][canh]);
				temps.setCost(s.getCost() + cost[current][canh]);
				Q.push(temps);

				//update parent
				tracer[dinh[current][canh]] = current;

				//update new cost
				cost[current][canh] = temps.getCost();
			} 
			//NODE !visited && NODE in Q 
			if (!visited[dinh[current][canh]] && inQueue(Q, dinh[current][canh])) {
				
				//create temp node for update
				NODE ss = getNodeinQueue(Q, dinh[current][canh]);

				//update if cost exists NODE < new NODE
				if (s.getCost() + cost[current][canh] > ss.getCost()) {
					//set new cost
					ss.setCost(s.getCost() + cost[current][canh]);
					
					//update new cost
					cost[current][canh] = ss.getCost();

					//update parent
					tracer[dinh[current][canh]] = current;

					//update modify
					Q.push(ss);
				}
			}
		}
	}
	return false;
}

bool Graph::inQueue(std::priority_queue<NODE> Q, int vertex) 
{
	int el;
	while (!Q.empty()) {
		el = Q.top().getVertex(); Q.pop();

		if (el == vertex) return true;
	}
	return false;
}

NODE Graph::getNodeinQueue(std::priority_queue<NODE> Q, int vertex)
{
	NODE node;
	int el;
	while (!Q.empty()) {
		node = Q.top();
		el = Q.top().getVertex(); Q.pop();

		if (el == vertex) {
			return node;
		}
	}
	return node;
}

void Graph::path(char * output)
{
	this->out.open(output, std::ios::out);
	if (!this->out) return;

	if (!this->UCS() || start == end) {
		//not found path
		std::cout << -1;
		out << -1;
	} else {
		//found path
		out << this->length << "\n";
		std::cout << this->length << "\n";

		int i = end;
		while (tracer[i] != start) {
			result.push_back(nameStreet[i][tracer[i]]);
			i = tracer[i];
		}
		result.push_back(nameStreet[i][start]);

		//print result
		for (int i = result.size() - 1; i >= 0; --i) {
			std::cout << result[i]; out << result[i];
			if (i != 0) { std::cout << " -> "; out << " -> "; }
		}
	}
	this->out.close();
}