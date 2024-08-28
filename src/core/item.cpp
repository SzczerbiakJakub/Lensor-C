#include "item.h"
#include <exception>
#include <limits>


class ZeroDivisionError : public std::exception {
public:
	const char* what() const noexcept override {
		return "Division by zero error";
	}
};




Ray::Ray(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {

	this->linearFactor = Ray::solveLinearFactor(x1, y1, x2, y2);

}

Ray::Ray(int x1, int y1, int x2, int y2, int start, int end) {

	linearFactor = Ray::solveLinearFactor(x1, y1, x2, y2);

	this->x1 = start;
	this->y1 = (int)(linearFactor.first * (start)) + int(linearFactor.second);

	this->x2 = end;
	this->y2 = (int)(linearFactor.first * (end)) + int(linearFactor.second);

	this->linearFactor = linearFactor;


	qDebug() << x1 << ", " << y1 << "; " << x2 << ", " << y2 << "; linefactor: " << linearFactor << ", end: " << end;
	qDebug() << this->x1 << ", " << this->y1 << "; " << this->x2 << ", " << this->y2;

}

Ray::~Ray() {}


std::pair<double, double> Ray::solveLinearFactor(int x1, int y1, int x2, int y2) {

	double factorA;
	if (x2 - x1 != 0)
		factorA = (y2 - y1) / (double)(x2 - x1);
	else
		factorA = std::numeric_limits<double>::infinity();

	double factorB = (int)y2 - factorA * (x2);

	return std::pair<double, double>(factorA, factorB);
}



std::pair<int, int> Ray::solveRayIntersection(Ray ray1, Ray ray2) {

	int x = (int)((ray2.getLinearFactor().second - ray1.getLinearFactor().second) / (ray1.getLinearFactor().first - ray2.getLinearFactor().first));
	int y = (int)(x * ray1.getLinearFactor().first + ray1.getLinearFactor().second);
	
	return std::pair<int, int>(x, y);
}

Item::Item(int x, int y) : x(x), y(y) {
}

Item::~Item() {}


void Item::setX(int x) {
	//this->x = &x;
}

void Item::setY(int y) {
	//this->y = &y;
}

Focus::Focus(int x=0, int y=1) : Item(x, y) {

}

GraphicLens::GraphicLens(int x, int y, double focal, int width, int height) : Item(x, y), focal(focal), width(width), height(height) {
	int focus_x = x - int(focal);
	Focus real_focus_object(focus_x, y);
	real_focus = real_focus_object;
	focus_x = x + int(focal);
	Focus imag_focus_object(focus_x, y);
	imag_focus = imag_focus_object;
}

GraphicLens::~GraphicLens() {}

GraphicLine::GraphicLine(GraphicPoint* pointAPtr, GraphicPoint* pointBPtr, bool real) : pointA(*pointAPtr), pointB(*pointBPtr), real(real) {

	if (real) {
		GraphicPoint* resultingPointA = pointAPtr->getResultingPoint();
		GraphicPoint* resultingPointB = pointBPtr->getResultingPoint();
		resultingLine = new GraphicLine(resultingPointA, resultingPointB, false);
	}
	
}


bool GraphicLine::crossedRealFocusX(GraphicLens * lensPtr) {

	bool crossed = false;
	int xA = pointA.getX(), xB = pointB.getX(), xFocus = lensPtr->getRealFocus().getX();

	if (xA < xB)
	{
		if (xA < xFocus and xB > xFocus)
			crossed = true;
	}
	else
	{
		if (xA >= xFocus and xB < xFocus)
			crossed = true;
	}
	return crossed;
}

std::pair<std::pair<int, int>, std::pair<int, int>> GraphicLine::getPointsNearbyRealFocus(GraphicLens* lensPtr) {
	
	int realFocusX(lensPtr->getRealFocus().getX()), xDeviation = 40;

	std::pair<double, double> linearFactor = Ray::solveLinearFactor(pointA.getX(), pointA.getY(), pointB.getX(), pointB.getY());

	std::pair<int, int>  coordsOfA, coordsOfB;

	if (getPointA().getX() < getPointB().getX())
	{
		coordsOfA = getPointA().getLinearPointCoords(realFocusX - xDeviation, linearFactor.first);
		coordsOfB = getPointA().getLinearPointCoords(realFocusX + xDeviation, linearFactor.first);
	}
	else
	{
		coordsOfA = getPointA().getLinearPointCoords(realFocusX + xDeviation, linearFactor.first);
		coordsOfB = getPointA().getLinearPointCoords(realFocusX - xDeviation, linearFactor.first);
	}
	

	return std::pair<std::pair<int, int>, std::pair<int, int>>(coordsOfA, coordsOfB);

}


InfinityGraphicLine::InfinityGraphicLine(GraphicPoint* pointAPtr, GraphicPoint* pointBPtr, GraphicPoint* extensionOfAPtr, GraphicPoint* extensionOfBPtr) {
	pointA = *pointAPtr;
	pointB = *pointBPtr;
	extensionOfA = *extensionOfAPtr;
	extensionOfB = *extensionOfBPtr;
}

GraphicPoint::GraphicPoint(int x, int y, bool real, GraphicLens* lensPtr) : Item(x, y), real(real), lensPtr(lensPtr) {
	if (real) {
		setRealFocusRay(lensPtr);
		setImagFocusRay(lensPtr);
		setResultingPointPtr();
	}
	else
	{
		resultingPoint = nullptr;
	}
}


//GraphicPoint::GraphicPoint(GraphicPoint& point): Item(point.getX(), point.getY()) {
//	real = point.isReal();
//	lensPtr = point.getLensPtr();
//	if (real) {
//		setRealFocusRay(lensPtr);
//		setImagFocusRay(lensPtr);
//		setResultingPointPtr();
//	}
//	else
//	{
//		resultingPoint = nullptr;
//	}
//}


GraphicPoint::~GraphicPoint() {}

//GraphicPoint GraphicPoint::getLinearPoint(int pointBx, double linearFactor) {
//	int pointBy = int(solveLinearY(x, y, pointBx, linearFactor));
//	return GraphicPoint(pointBx, pointBy, true, lensPtr);
//}


std::pair<int, int>  GraphicPoint::getLinearPointCoords(int pointBx, double linearFactor) {
	int pointBy = int(solveLinearY(x, y, pointBx, linearFactor));
	return std::pair<int, int>(pointBx, pointBy);
}

void GraphicPoint::setRealFocusRay(GraphicLens * lens) {

	std::pair<int, int> realFocus(lens->getRealFocus()), endPoint(1, 1);
	Ray ray1(x, y, realFocus.first, realFocus.second, 0, lens->getRealPlaneX());

	int rayPlaneY = (int)(ray1.getLinearFactor().first * (lens->getImagPlaneX())) + int(ray1.getLinearFactor().second);

	Ray ray2(lens->getImagPlaneX(), rayPlaneY, 1300, rayPlaneY);
	std::pair<Ray, Ray> ray12(ray1, ray2);
	realFocusRay = ray12;

}

void GraphicPoint::setImagFocusRay(GraphicLens* lens) {

	std::pair<int, int> imagFocus(lens->getImagFocus()), endPoint(1, 1);
	Ray ray1(x, y, imagFocus.first, imagFocus.second, lens->getImagPlaneX(), 1300);

	int rayPlaneY = (int)(ray1.getLinearFactor().first * (lens->getRealPlaneX())) + int(ray1.getLinearFactor().second);

	Ray ray2(0, rayPlaneY, lens->getRealPlaneX(), rayPlaneY);
	std::pair<Ray, Ray> ray12(ray1, ray2);
	imagFocusRay = ray12;
}

void GraphicPoint::setResultingPointPtr() {

	std::pair<int, int> intersectionCoords(Ray::solveRayIntersection(getRealFocusRay().second, getImagFocusRay().first));
	GraphicPoint *resulting = new GraphicPoint(intersectionCoords.first, intersectionCoords.second, false, lensPtr);
	resultingPoint = resulting;
}


void GraphicPoint::setId(std::string* id) {
	if (isReal())
		this->id = *id;
	else
		this->id = *id + "'";
}

NumericPoint::NumericPoint(int x, int y) : Item(x, y) {}

NumericPoint::~NumericPoint() {}
