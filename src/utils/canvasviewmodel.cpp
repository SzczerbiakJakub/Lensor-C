#include "canvasviewmodel.h"

CanvasViewModel::CanvasViewModel(CanvasData* dataPtr) : dataPtr(dataPtr) {}


void CanvasViewModel::addPoint(int x, int y, GraphicLens* lensPtr) {
	dataPtr->addGraphicPoint(x, y, lensPtr);

}

void CanvasViewModel::checkLineDrawing(GraphicPoint* point) {


	if (dataPtr->getLastDrawnPointPtr() == nullptr)
	{
		dataPtr->setLastDrawnPoint(point);
	}
	else
	{
		GraphicPoint* lastDrawnPoint = dataPtr->getLastDrawnPointPtr();
		GraphicLine* linePtr = new GraphicLine(point, lastDrawnPoint, true);
		dataPtr->addGraphicLine(linePtr);
		dataPtr->resetLastDrawnPoint();
		dataPtr->setDrawingLine(false);
	}
}

void CanvasViewModel::checkShapeDrawing(GraphicPoint* point) {

}

void CanvasViewModel::addLine(GraphicLine* linePtr) {
	dataPtr->addGraphicLine(linePtr);
}


void CanvasViewModel::addLens(GraphicLens* lensPtr) {
	dataPtr->addGraphicLens(lensPtr);
}


void CanvasViewModel::drawFinishedShape() {
	dataPtr->drawFinishedShape();
}