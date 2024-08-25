#include "canvasviewmodel.h"

CanvasViewModel::CanvasViewModel(CanvasData* dataPtr) : dataPtr(dataPtr) {}


void CanvasViewModel::addPoint(int x, int y, GraphicLens* lensPtr) {
	dataPtr->addGraphicPoint(x, y, lensPtr);
	GraphicPoint* pointPtr = dataPtr->getGraphicPoint(-1);
	if (dataPtr->getDrawingLine())
	{
		if (dataPtr->getLastDrawnPoint() == nullptr)
		{
			dataPtr->setLastDrawnPoint(pointPtr);
		}
		else
		{
			GraphicLine* linePtr = new GraphicLine(pointPtr, dataPtr->getLastDrawnPoint(), true);
			dataPtr->addGraphicLine(linePtr);
			dataPtr->setLastDrawnPoint(nullptr);
			dataPtr->setDrawingLine(false);
		}
	}
	if (dataPtr->getDrawingShape())
	{
		if (dataPtr->getFirstDrawnPoint() == nullptr)
		{
			dataPtr->setFirstDrawnPoint(pointPtr);
		}


		
		if (dataPtr->getLastDrawnPoint() == nullptr)
		{
			dataPtr->setLastDrawnPoint(pointPtr);
		}
		else
		{
			GraphicLine* linePtr = new GraphicLine(pointPtr, dataPtr->getLastDrawnPoint(), true);
			dataPtr->addGraphicLine(linePtr);
			dataPtr->setLastDrawnPoint(pointPtr);
		}
		
		
	}

}


void CanvasViewModel::addLine(GraphicLine* linePtr) {
	dataPtr->addGraphicLine(linePtr);
}


void CanvasViewModel::addLens(GraphicLens* lensPtr) {
	dataPtr->addGraphicLens(lensPtr);
}


void CanvasViewModel::drawFinishedShape() {
	//addLine
	GraphicLine* linePtr = new GraphicLine(dataPtr->getLastDrawnPoint(), dataPtr->getFirstDrawnPoint(), true);
	dataPtr->addGraphicLine(linePtr);
	dataPtr->setFirstDrawnPoint(nullptr);
	dataPtr->setLastDrawnPoint(nullptr);
	dataPtr->setDrawingShape(false);
}