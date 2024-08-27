#pragma once

#include <data.h>


class CanvasViewModel
{
public:
	CanvasViewModel() {};
	CanvasViewModel(CanvasData* dataPtr);
	~CanvasViewModel() {};
	//void addPoint(GraphicPoint* pointPtr);
	void addPoint(int x, int y, GraphicLens* lensPtr);
	void addLens(GraphicLens* lensPtr);
	void addLine(GraphicLine* linePtr);

	std::vector<GraphicPoint>* getGraphicPoints() { return dataPtr->getGraphicPoints(); };
	std::vector<GraphicPoint>* getResultingGraphicPoints() { return dataPtr->getResultingGraphicPoints(); };
	std::vector<GraphicLine>* getGraphicLines() { return dataPtr->getGraphicLines(); };
	std::vector<GraphicLine>* getResultingGraphicLines() { return dataPtr->getResultingGraphicLines(); };
	std::vector<GraphicLens>* getGraphicLenses() { return dataPtr->getGraphicLenses(); };
	std::vector<Ray>* getRays() { return dataPtr->getRays(); };


	bool getDrawingLine() { return dataPtr->getDrawingLine(); };
	bool getDrawingShape() { return dataPtr->getDrawingShape(); };

	void setDrawingLine(bool drawingLine) { return dataPtr->setDrawingLine(drawingLine); };
	void setDrawingShape(bool drawingShape) { return dataPtr->setDrawingShape(drawingShape); };

	void setLastDrawnPoint(GraphicPoint* pointPtr) { return dataPtr->setLastDrawnPoint(pointPtr); };
	GraphicPoint getLastDrawnPoint() { return dataPtr->getLastDrawnPoint(); };

	void drawFinishedShape();

	void checkLineDrawing(GraphicPoint* point);
	void checkShapeDrawing(GraphicPoint* point);

private:
	CanvasData* dataPtr;
};


