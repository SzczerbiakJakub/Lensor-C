#pragma once
#include <String>
#include <QPointF>
#include <QLineF>
#include <QDebug>
#include <vector>
#include <utility>



inline double solveLinearY(int x1, int y1, int x2, double linear_factor) {
	return linear_factor * (x2 - x1) + y1;
}



class Ray
{
public:
	Ray() {};
	Ray(int x1, int y1, int x2, int y2);
	Ray(int x1, int y1, int x2, int y2, int start, int end);
	~Ray();
	void hide();
	void unhide();


	//std::pair<int, int> getPointA() { return pointA; }
	//std::pair<int, int> getPointB() { return pointB; }

	int getX1() { return x1; }
	int getY1() { return y1; }
	int getX2() { return x2; }
	int getY2() { return y2; }

	static std::pair<double, double> solveLinearFactor(int x1, int y1, int x2, int y2);
	std::pair<double, double> getLinearFactor() { return linearFactor; };

	
	//operator QLineF() {
	//	return QLineF(pointA.first, pointA.second, pointB.first, pointB.second);
	//}

	static std::pair<int, int> solveRayIntersection(Ray ray1, Ray ray2);

	operator QLineF() {
		return QLineF(x1, y1, x2, y2);
	}


protected:
	void calculateLinearFactor();
	//std::pair<double, double> linear_factors;
	std::pair<double, double> linearFactor;
	//std::pair<int, int> pointA;
	//std::pair<int, int> pointB;
	int x1;
	int y1;
	int x2;
	int y2;
	int width;
};


class MarginalRay : public Ray
{
public:
	MarginalRay();
	~MarginalRay();

};


class ChiefRay : public Ray
{
public:
	ChiefRay();
	~ChiefRay();

};


class Item
{
public:
	Item() { x = NULL; y = NULL; };
	Item(int x, int y);
	~Item();

	void setX(int x);
	void setY(int y);
	int getX() { return x; };
	int getY() { return y; };
	std::string getId() { return id; };
	void hide();
	void unhide();

	operator std::pair<int, int>() {
		return std::pair<int, int>(x, y);
	}


protected:
	int x;
	int y;
	std::string id;

};


class Focus : public Item
{
public:
	Focus(int x, int y);
	~Focus() {};

	operator QPointF()
	{
		return QPointF(x, y);
	}

	operator std::pair<int, int>() {
		return std::pair<int, int>(x, y);
	}

private:
};

class GraphicLens : public Item
{
public:
	GraphicLens(int x, int y, double focal, int width, int height);
	~GraphicLens();
	Focus getRealFocus() { return real_focus; };
	Focus getImagFocus() { return imag_focus; };
	int getRealPlaneX() { return x - width / 2; }
	int getImagPlaneX() { return x + width / 2; }
	int getY() { return y; }
	//std::string getItemID();


	operator std::pair<QLineF, QLineF>()
	{
		QLineF real_plane(x - width / 2, y - height / 2, x - width / 2, y + height / 2);
		QLineF imag_plane(x + width / 2, y - height / 2, x + width / 2, y + height / 2);
		std::pair<QLineF, QLineF> pair(real_plane, imag_plane);
		return pair;
	}

	operator std::pair<QPointF, QPointF>()
	{
		std::pair<QPointF, QPointF> pair(real_focus, imag_focus);
		return pair;
	}

	operator std::pair< std::pair<QLineF, QLineF>, std::pair<QPointF, QPointF>>()
	{
		std::pair<QLineF, QLineF> plane_pair(*this);
		std::pair<QPointF, QPointF> focus_pair(*this);
		std::pair<std::pair<QLineF, QLineF>, std::pair<QPointF, QPointF>> complete_pair(plane_pair, focus_pair);
		return complete_pair;
	}

protected:
	Focus real_focus;
	Focus imag_focus;
	double focal;
	int width;
	int height;
};

class GraphicPoint : public Item
{
public:
	GraphicPoint() { x = NULL; y = NULL; real = false; lensPtr = nullptr; };
	GraphicPoint(int x, int y, bool real, GraphicLens* lens_ptr);
	//GraphicPoint(GraphicPoint& point);
	~GraphicPoint();
	//GraphicPoint getLinearPoint(int pointBx, double linearFactor);
	std::pair<int, int> getLinearPointCoords(int pointBx, double linearFactor);
	//std::string getItemID();
	void setRealFocusRay(GraphicLens* lens);
	void setMiddleRay(GraphicLens* lens) {};
	void setImagFocusRay(GraphicLens* lens);
	std::pair<Ray, Ray> getRealFocusRay() { return realFocusRay; };
	std::pair<Ray, Ray> getMiddleRay() { return middleRay; };
	std::pair<Ray, Ray> getImagFocusRay() { return imagFocusRay; };

	void setResultingPointPtr();
	GraphicPoint* getResultingPoint() { return resultingPoint; };

	bool isReal() { return real; }
	GraphicLens* getLensPtr() { return lensPtr; }

	operator QPointF()
	{
		return QPointF((float)x, (float)y);
	}

	void setId(std::string* id);

private:
	//std::string id;
	bool real;
	std::pair<Ray, Ray> realFocusRay;
	std::pair<Ray, Ray> imagFocusRay;
	std::pair<Ray, Ray> middleRay;
	GraphicLens* lensPtr;
	GraphicPoint* resultingPoint;
};


class GraphicLine
{
public:
	GraphicLine() {};
	GraphicLine(GraphicPoint* pointAPtr, GraphicPoint* pointBPtr, bool real);
	~GraphicLine() {};

	operator QLineF() {
		return QLineF(pointA.getX(), pointA.getY(), pointB.getX(), pointB.getY());
	};

	GraphicLine getResultingLine() { return *resultingLine; };
	GraphicPoint getPointA() { return pointA; };
	GraphicPoint getPointB() { return pointB; };

	bool crossedRealFocusX(GraphicLens* lensPtr);

	std::pair<std::pair<int, int>, std::pair<int, int>> getPointsNearbyRealFocus(GraphicLens* lensPtr);

private:
	bool real;
	GraphicPoint pointA;
	GraphicPoint pointB;
	GraphicLine* resultingLine;

};


class InfinityGraphicLine
{
public:
	InfinityGraphicLine() {};
	InfinityGraphicLine(GraphicPoint* pointAPtr, GraphicPoint* pointBPtr, GraphicPoint* extensionOfAPtr, GraphicPoint* extensionOfBPtr);
	~InfinityGraphicLine() {};

	operator std::pair<QLineF, QLineF>() {
		QLineF lineA = QLineF(pointA.getX(), pointA.getY(), extensionOfA.getX(), extensionOfA.getY()),
			lineB = QLineF(pointB.getX(), pointB.getY(), extensionOfB.getX(), extensionOfB.getY());
		return std::pair<QLineF, QLineF>(lineA, lineB);
	};

protected:
	GraphicPoint pointA;
	GraphicPoint pointB;
	GraphicPoint extensionOfA;
	GraphicPoint extensionOfB;

};


class NumericPoint : public Item
{
public:
	NumericPoint(int x, int y);
	~NumericPoint();
	//std::string getItemID();

	operator QPointF()
	{
		return QPointF((float)x, (float)y);
	}

};


class Aperture : public Item
{
public:
	Aperture();
	~Aperture();
	//std::string getItemID();
	void setDiameter();
	int getDiameter();

private:
	int diameter;

};

class NumericLens : public Aperture
{
public:
	NumericLens();
	~NumericLens();
	//std::string getItemID();
	void setFocal();
	int getFocal();

private:
	int focal;

};