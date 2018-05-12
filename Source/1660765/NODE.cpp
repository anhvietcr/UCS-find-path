#include "NODE.h"

NODE::NODE()
{
	this->vertex = 0;
	this->cost = 0;
}

//get
int NODE::getVertex() const
{
	return this->vertex;
}

float NODE::getCost() const
{
	return this->cost;
}

//set
void NODE::setVertex(int vertex)
{
	this->vertex = vertex;
}

void NODE::setCost(float cost)
{
	this->cost = cost;
}