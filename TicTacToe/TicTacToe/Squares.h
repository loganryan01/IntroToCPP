#pragma once
#include "Point2D.h"

class Squares
{
public:
	Squares();
	~Squares();

	void setPosition(Point2D position);
	void setType(int type);
	int getType();
	void draw();

private:
	Point2D m_gridPosition; 
	int m_type; 
};