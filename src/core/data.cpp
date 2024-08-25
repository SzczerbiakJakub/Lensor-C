#include "data.h"


CanvasData::CanvasData() {
	items = new std::vector<Item>;
	graphicPoints = new std::vector<GraphicPoint>;
	resultingGraphicPoints = new std::vector<GraphicPoint>;
	graphicLenses = new std::vector<GraphicLens>;
	resultingGraphicLines = new std::vector<GraphicLine>;
	graphicLines = new std::vector<GraphicLine>;
	numericPoints = new std::vector<NumericPoint>;
	rays = new std::vector<Ray>;

	lastDrawnPointPtr = nullptr;
	drawingLine = false;
	drawingShape = false;
}


CanvasData::~CanvasData() {
	delete items;
	delete graphicPoints;
	delete resultingGraphicPoints;
	delete graphicLenses;
	delete numericPoints;
	delete rays;
}


void CanvasData::addGraphicPoint(int x, int y, GraphicLens* lensPtr) {
	
	GraphicPoint* point = new GraphicPoint(x, y, true, lensPtr);
	GraphicPoint* resultingPoint = point->getResultingPoint();
	graphicPoints->push_back(*point);
	addResultingGraphicPoint(resultingPoint);
}

GraphicPoint* CanvasData::getGraphicPoint(int index) {

	std::vector<GraphicPoint> points = *getGraphicPoints();
	int vectorSize = static_cast<int>(points.size()), processed_index = index;
	if (index < 0)
	{
		processed_index = (vectorSize + index)%vectorSize;
	}
	return &points[processed_index];

}

void CanvasData::addResultingGraphicPoint(GraphicPoint * pointPtr) {

	resultingGraphicPoints->push_back(*pointPtr);
}


void CanvasData::addGraphicLens(GraphicLens* lensPtr) {

	graphicLenses->push_back(*lensPtr);
}


void CanvasData::addGraphicLine(GraphicLine* linePtr) {

	GraphicLine line = *linePtr, resultingLine = line.getResultingLine();
	graphicLines->push_back(line);
	addResultingGraphicLine(&resultingLine);
}


void CanvasData::addResultingGraphicLine(GraphicLine* linePtr) {

	resultingGraphicLines->push_back(*linePtr);
}


void clearItems();
void clearGraphicPoints();
void clearResultingGraphicPoints();
void clearGraphicLines();
void clearResultingGraphicLines();
void clearGraphicLenses();


void CanvasData::clearItems() {
	while (items->empty()) {
		
	}
}


void CanvasData::clearAllData() {
	items = new std::vector<Item>;
	graphicPoints = new std::vector<GraphicPoint>;
	resultingGraphicPoints = new std::vector<GraphicPoint>;
	graphicLenses = new std::vector<GraphicLens>;
	resultingGraphicLines = new std::vector<GraphicLine>;
	graphicLines = new std::vector<GraphicLine>;
	numericPoints = new std::vector<NumericPoint>;
	rays = new std::vector<Ray>;
}