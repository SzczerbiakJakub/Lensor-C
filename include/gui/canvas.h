#pragma once

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <axis.h>
#include <vector>
#include <item.h>
#include <QDebug>
#include <utility>
#include <QMouseEvent>
#include <QThread>
#include <canvasviewmodel.h>

class Canvas : public QWidget
{
	Q_OBJECT

public:
	Canvas(QWidget* parent);
	~Canvas();
	CanvasViewModel* viewModel;
	void drawPoint(int x, int y);
	void drawSomePoints();


protected:
	void createDefaultView();
	void paintEvent(QPaintEvent* event= nullptr) override;
	void draw(QPainter* painter, Item* item);
	void draw(QPainter* painter, QLineF* line);
	void draw(QPainter* painter, QPointF* point);
	void draw(QPainter* painter, std::pair<std::pair<QLineF, QLineF>, std::pair<QPointF, QPointF>>* complete_lens);
	void appendResultingPoints();
	void mousePressEvent(QMouseEvent* event) override;

	std::vector<GraphicPoint>* getGraphicPoints() { return viewModel->getGraphicPoints(); };
	std::vector<GraphicPoint>* getResultingGraphicPoints() { return viewModel->getResultingGraphicPoints(); };
	std::vector<GraphicLine>* getGraphicLines() { return viewModel->getGraphicLines(); };
	std::vector<GraphicLine>* getResultingGraphicLines() { return viewModel->getResultingGraphicLines(); };
	std::vector<GraphicLens>* getGraphicLenses() { return viewModel->getGraphicLenses(); };
	std::vector<Ray>* getRays() { return viewModel->getRays(); };


	bool getDrawingLine() { return viewModel->getDrawingLine(); };
	bool getDrawingShape() { return viewModel->getDrawingShape(); };

	void setDrawingLine(bool drawingLine) { return viewModel->setDrawingLine(drawingLine); };
	void setDrawingShape(bool drawingShape) { return viewModel->setDrawingShape(drawingShape); };

	void setLastDrawnPoint(GraphicPoint* pointPtr) { return viewModel->setLastDrawnPoint(pointPtr); };
	GraphicPoint* getLastDrawnPoint() { return viewModel->getLastDrawnPoint(); };


private:
	Axis* axis;
	Axis* buildAxis();
	GraphicLens* lens;
	void createDefaultLens(int focal);
};


class CanvasThread : public QThread {

public:
	CanvasThread(Canvas* canvas_ptr, int x, int y) :  canvas_ptr(canvas_ptr) {};
	~CanvasThread() {};

private:
	Canvas* canvas_ptr;
	int x;
	int y;
	void run() override;

};