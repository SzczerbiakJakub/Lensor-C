#pragma once
#include <item.h>
#include <vector>


class CanvasData
{

public:
	CanvasData();
	~CanvasData();
	Item getItem(int index);
	Item getItem(int x, int y);
	GraphicPoint* getGraphicPoint(int index);
	GraphicPoint getGraphicPoint(int x, int y);
	GraphicPoint getResultingGraphicPoints(int index);
	GraphicPoint getResultingGraphicPoints(int x, int y);
	GraphicLens getGraphicLens(int index);
	Ray getRay(int index);

	void addItem();
	void addGraphicPoint(int x, int y, GraphicLens* lensPtr);
	void addResultingGraphicPoint(GraphicPoint* pointPtr);
	void addGraphicLine(GraphicLine* linePtr);
	void addResultingGraphicLine(GraphicLine* linePtr);
	void addGraphicLens(GraphicLens* lensPtr);
	void addRay();


	std::vector<GraphicPoint>* getGraphicPoints() { return graphicPoints; };
	std::vector<GraphicPoint>* getResultingGraphicPoints() { return resultingGraphicPoints; };
	std::vector<GraphicLine>* getGraphicLines() { return graphicLines; };
	std::vector<GraphicLine>* getResultingGraphicLines() { return resultingGraphicLines; };
	std::vector<GraphicLens>* getGraphicLenses() { return graphicLenses; };
	std::vector<Ray>* getRays() { return rays; };

	bool getDrawingLine() { return drawingLine; };
	bool getDrawingShape() { return drawingShape; };

	void clearItems();
	void clearGraphicPoints();
	void clearResultingGraphicPoints();
	void clearGraphicLines();
	void clearResultingGraphicLines();
	void clearGraphicLenses();

	void clearAllData();

	void setDrawingLine(bool drawingLine) { this->drawingLine = drawingLine; };
	void setDrawingShape(bool drawingShape) { this->drawingShape = drawingShape; };

	void setFirstDrawnPoint(GraphicPoint* pointPtr) { firstDrawnPointPtr = pointPtr; };
	void setLastDrawnPoint(GraphicPoint* pointPtr) { lastDrawnPointPtr = pointPtr; };
	GraphicPoint* getFirstDrawnPoint() { return firstDrawnPointPtr; };
	GraphicPoint* getLastDrawnPoint() { return lastDrawnPointPtr; };



private:
	bool drawingLine;
	bool drawingShape;
	GraphicPoint* lastDrawnPointPtr;
	GraphicPoint* firstDrawnPointPtr;
	std::vector<Item>* items;
	std::vector<GraphicPoint>* graphicPoints;
	std::vector<GraphicPoint>* resultingGraphicPoints;
	std::vector<GraphicLine>* graphicLines;
	std::vector<GraphicLine>* resultingGraphicLines;
	std::vector<GraphicLens>* graphicLenses;
	std::vector<NumericPoint>* numericPoints;
	std::vector<Ray>* rays;
};

