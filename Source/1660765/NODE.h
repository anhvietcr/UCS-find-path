#pragma once
class NODE
{
private:
	int vertex;
	float cost;

public:
	NODE();
	int getVertex() const;
	float getCost() const;
	void setVertex(int);
	void setCost(float);
	
	friend bool operator<(const NODE &a, const NODE &b) { return a.getCost() < b.getCost(); }
};
