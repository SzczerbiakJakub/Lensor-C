#include "data.h"


CanvasData::CanvasData() {
	items = new std::vector<Item>;
	graphicPoints = new std::vector<GraphicPoint>;
	resultingGraphicPoints = new std::vector<GraphicPoint>;
	graphicLenses = new std::vector<GraphicLens>;
	resultingGraphicLines = new std::vector<GraphicLine>;
	graphicLines = new std::vector<GraphicLine>;
	infinityGraphicLines = new std::vector<InfinityGraphicLine>;
	numericPoints = new std::vector<NumericPoint>;
	rays = new std::vector<Ray>;
	linePoints = new std::vector<GraphicPoint>;
	shapePoints = new std::vector<GraphicPoint>;

	firstDrawnPointPtr = nullptr;
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
	delete linePoints;
	delete infinityGraphicLines;
	delete shapePoints;
}


void CanvasData::addGraphicPoint(int x, int y, GraphicLens* lensPtr) {
	
	GraphicPoint* point = new GraphicPoint(x, y, true, lensPtr);
	GraphicPoint* resultingPoint = point->getResultingPoint();

	std::string pointNewId = defineNewId();

	point->setId(&pointNewId);
	resultingPoint->setId(&pointNewId);

	graphicPoints->push_back(*point);
	addResultingGraphicPoint(resultingPoint);

	if (getDrawingLine())
	{
		linePoints->push_back(*point);

		if (static_cast<int>(linePoints->size()) == 2)
		{
			setDrawingLine(false);
			GraphicPoint point1=linePoints->front(), point2 = linePoints->back();
			GraphicLine* linePtr = new GraphicLine(&point1, &point2, true);
			//qDebug() << "LINE: " << linePtr->getPointA().getX() << ", " << linePtr->getPointA().getY() << "; " << linePtr->getPointB().getX() << ", " << linePtr->getPointB().getY();
			addGraphicLine(linePtr);
			delete linePoints;
			linePoints = new std::vector<GraphicPoint>;
		}
		
	}

	if (getDrawingShape())
	{
		shapePoints->push_back(*point);
		int shapePointsSize = static_cast<int>(shapePoints->size());

		if (shapePointsSize >= 2)
		{
			std::vector<GraphicPoint> points = *shapePoints;
			GraphicPoint point1 = points[shapePointsSize - 2], point2 = points[shapePointsSize - 1];
			GraphicLine* linePtr = new GraphicLine(&point1, &point2, true);
			addGraphicLine(linePtr);
		}
		
		
	}

}

void CanvasData::drawFinishedShape() {

	setDrawingShape(false);

	int shapePointsSize = static_cast<int>(shapePoints->size());

	std::vector<GraphicPoint> points = *shapePoints;
	GraphicPoint point1 = points[shapePointsSize-1], point2 = points[0];
	GraphicLine* linePtr = new GraphicLine(&point1, &point2, true);
	
	addGraphicLine(linePtr);
	delete shapePoints;
	shapePoints = new std::vector<GraphicPoint>;
}

GraphicPoint CanvasData::getGraphicPoint(int index) {

	std::vector<GraphicPoint> points = *getGraphicPoints();
	int vectorSize = static_cast<int>(points.size()), processed_index = index;
	if (index < 0)
	{
		processed_index = (vectorSize + index)%vectorSize;
	}

	GraphicPoint point = points[processed_index];

	return points[processed_index];

}

void CanvasData::addResultingGraphicPoint(GraphicPoint * pointPtr) {

	resultingGraphicPoints->push_back(*pointPtr);
}


void CanvasData::addGraphicLens(GraphicLens* lensPtr) {

	graphicLenses->push_back(*lensPtr);
}


void CanvasData::addGraphicLine(GraphicLine* linePtr) {

	GraphicLine line = *linePtr;
	graphicLines->push_back(line);

	if (linePtr->crossedRealFocusX(&getGraphicLenses()->back()))
	{
		bool whileDrawingShape = getDrawingShape() ? true : false;
		GraphicLens* lensPtr = linePtr->getPointA().getLensPtr();

		setDrawingShape(false);
		std::pair<std::pair<int, int>, std::pair<int, int>> focusPointsCoords = linePtr->getPointsNearbyRealFocus(lensPtr);
		GraphicPoint pointA = *linePtr->getPointA().getResultingPoint(), pointB = *linePtr->getPointB().getResultingPoint(), extensionOfA, extensionOfB;
		addGraphicPoint(focusPointsCoords.first.first, focusPointsCoords.first.second, lensPtr);
		extensionOfA = *graphicPoints->back().getResultingPoint();
		addGraphicPoint(focusPointsCoords.second.first, focusPointsCoords.second.second, lensPtr);
		extensionOfB = *graphicPoints->back().getResultingPoint();

		InfinityGraphicLine* infinityLine = new InfinityGraphicLine(&pointA, &pointB, &extensionOfA, &extensionOfB);
			
		addInfinityGraphicLine(infinityLine);

		if (whileDrawingShape)
			setDrawingShape(true);

	}
	else
	{
		GraphicLine resultingLine = line.getResultingLine();
		addResultingGraphicLine(&resultingLine);
	}
	
}


void CanvasData::addResultingGraphicLine(GraphicLine* linePtr) {

	resultingGraphicLines->push_back(*linePtr);
}


void CanvasData::addInfinityGraphicLine(InfinityGraphicLine* linePtr) {
	infinityGraphicLines->push_back(*linePtr);
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
	delete items;
	items = new std::vector<Item>;
	delete graphicPoints;
	graphicPoints = new std::vector<GraphicPoint>;
	delete resultingGraphicPoints;
	resultingGraphicPoints = new std::vector<GraphicPoint>;
	delete resultingGraphicLines;
	resultingGraphicLines = new std::vector<GraphicLine>;
	delete graphicLines;
	graphicLines = new std::vector<GraphicLine>;
	delete infinityGraphicLines;
	infinityGraphicLines = new std::vector<InfinityGraphicLine>;
	delete numericPoints;
	numericPoints = new std::vector<NumericPoint>;
	delete rays;
	rays = new std::vector<Ray>;
}


std::string CanvasData::defineNewId() {
	int asciiIndex = 65 + graphicPoints->size();
	std::string id = "";

	while (asciiIndex > 90)
	{
		id += "A";
		asciiIndex -= 26;
	}
	id += char(asciiIndex);

	return id;
}

