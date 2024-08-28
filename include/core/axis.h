#pragma once
#include <QGraphicsLineItem>
#include <QLineF>

class Axis : public QGraphicsLineItem
{
public:

	Axis(int height, int start, int end);
	~Axis();

	operator QLineF()
	{
		return QLineF(start, height, end, height);
	}
	

private:
	int height;
	int width;
	int start;
	int end;

};

