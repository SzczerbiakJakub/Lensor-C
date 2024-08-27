#include "canvasviewmodel.h"

CanvasViewModel::CanvasViewModel(CanvasData* dataPtr) : dataPtr(dataPtr) {}


void CanvasViewModel::addPoint(int x, int y, GraphicLens* lensPtr) {
	dataPtr->addGraphicPoint(x, y, lensPtr);
	/*GraphicPoint point = dataPtr->getGraphicPoint(-1);
	if (dataPtr->getDrawingLine())
	{

		if (dataPtr->getLastDrawnPointPtr() == nullptr)
		{
			GraphicPoint* pointPtr = &point;
			dataPtr->setLastDrawnPoint(pointPtr);
			qDebug() << "LAST DRAWN POINT: " << dataPtr->getLastDrawnPoint().getX() << ", " << dataPtr->getLastDrawnPoint().getY();
		}
		else
		{
			qDebug() << "POINT: " << point.getX() << ", " << point.getY();
			GraphicPoint lastDrawnPoint = dataPtr->getLastDrawnPoint();
			qDebug() << "LAST DRAWN POINT HERE: " << lastDrawnPoint.getX() << ", " << lastDrawnPoint.getY();
			GraphicLine* linePtr = new GraphicLine(&point, &lastDrawnPoint, true);
			qDebug() << "LINE: " << linePtr->getPointA().getX() << ", " << linePtr->getPointA().getY() << "; " << linePtr->getPointB().getX() << ", " << linePtr->getPointB().getY();
			dataPtr->addGraphicLine(linePtr);
			dataPtr->resetLastDrawnPoint();
			dataPtr->setDrawingLine(false);
		}
	}
	if (dataPtr->getDrawingShape())
	{
		if (dataPtr->getFirstDrawnPointPtr() == nullptr)
		{
			GraphicPoint* pointPtr = new GraphicPoint(point);
			dataPtr->setFirstDrawnPoint(pointPtr);
		}


		
		if (dataPtr->getLastDrawnPointPtr() == nullptr)
		{
			GraphicPoint* pointPtr = new GraphicPoint(point);
			dataPtr->setLastDrawnPoint(pointPtr);
		}
		else
		{
			GraphicPoint lastDrawnPoint = dataPtr->getLastDrawnPoint();
			GraphicLine* linePtr = new GraphicLine(&point, &lastDrawnPoint, true);
			dataPtr->addGraphicLine(linePtr);
			GraphicPoint* pointPtr = new GraphicPoint(point);
			dataPtr->setLastDrawnPoint(pointPtr);
		}
		
		
	}*/

}

void CanvasViewModel::checkLineDrawing(GraphicPoint* point) {

	if (dataPtr->getLastDrawnPointPtr() == nullptr)
	{
		dataPtr->setLastDrawnPoint(point);
		qDebug() << "LAST DRAWN POINT: " << dataPtr->getLastDrawnPoint().getX() << ", " << dataPtr->getLastDrawnPoint().getY();
	}
	else
	{
		qDebug() << "POINT: " << point->getX() << ", " << point->getY();
		GraphicPoint* lastDrawnPoint = dataPtr->getLastDrawnPointPtr();
		qDebug() << "LAST DRAWN POINT HERE: " << lastDrawnPoint->getX() << ", " << lastDrawnPoint->getY();
		GraphicLine* linePtr = new GraphicLine(point, lastDrawnPoint, true);
		qDebug() << "LINE: " << linePtr->getPointA().getX() << ", " << linePtr->getPointA().getY() << "; " << linePtr->getPointB().getX() << ", " << linePtr->getPointB().getY();
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
	//addLine
	dataPtr->drawFinishedShape();
}