#include "canvas.h"
#include <windows.h>

Canvas::Canvas(QWidget* parent = nullptr) : QWidget(parent) {

    this->setGeometry(5, 5, 1300, 700);
    CanvasData* canvasData = new CanvasData();
    viewModel = new CanvasViewModel(canvasData);

}

Canvas::~Canvas() {

}

void Canvas::createDefaultGraphicView() {
    axis = buildAxis();
    createDefaultLens(150);
    paintEvent();
    //drawPoint(100, 200);
}

void Canvas::createDefaultNumericView() {
    axis = buildAxis();
    paintEvent();
    //createDefaultLens(150);
    //drawPoint(100, 200);
}

void Canvas::createDefaultLens(int focal) {
    lens = new GraphicLens(650, 350, focal, 100, 500);
    viewModel->addLens(lens);
}

void Canvas::drawPoint(int x, int y) {
    //graphicPoints.push_back(GraphicPoint(x, y, true, &graphicLenses.back()));
    //resultingGraphicPoints.push_back(graphicPoints.back().getResultingPoint());
    viewModel->addPoint(x, y, lens);
    paintEvent();
    update();
}

void Canvas::drawSomePoints() {
    for (int i = 200; i < 400; i += 1)
    {
        CanvasThread* thread = new CanvasThread(this, i, 250);
        thread->start();
        Sleep(30);
    }
}

void Canvas::paintEvent(QPaintEvent* event) {


    QPainter * painter = new QPainter(this);
    painter->fillRect(this->rect(), QColor("white"));
    QPen realPointPen(Qt::black, 5), resultingPointPen(Qt::red, 5), realPointPenId(Qt::black, 2), resultingPointPenId(Qt::red, 2);
    painter->setPen(QPen((Qt::black, 2)));
    QLineF line = QLineF(*axis);
    draw(painter, &line); 
    
    painter->setPen(QPen(Qt::gray, 1));


    //      FOR RAY DRAWING UNCODE THE SNIPPET BELOW

    /*for (Ray ray : *viewModel->getRays()) {
        QLineF rayLine(ray);
        draw(painter, &rayLine);
    }

    for (GraphicPoint graphicPoint : *viewModel->getGraphicPoints()) {
        std::pair<Ray, Ray> realFocusRay = graphicPoint.getRealFocusRay(), imagFocusRay = graphicPoint.getImagFocusRay();
        QLineF a = QLineF(graphicPoint.getRealFocusRay().first), b = QLineF(graphicPoint.getRealFocusRay().second),
            c = QLineF(graphicPoint.getImagFocusRay().first), d = QLineF(graphicPoint.getImagFocusRay().second);;
        draw(painter, &a);
        draw(painter, &b);
        draw(painter, &c);
        draw(painter, &d);
    }*/
    
    painter->setPen(QPen(Qt::black, 5));

    for (GraphicLens graphicLens : *viewModel->getGraphicLenses()) {
        std::pair<std::pair<QLineF, QLineF>, std::pair<QPointF, QPointF>> complete_lens(graphicLens);
        draw(painter, &complete_lens);
    }

    for (GraphicPoint graphicPoint : *viewModel->getGraphicPoints()) {
        QPointF point(graphicPoint);
        draw(painter, &point, &realPointPen);
        draw_id(painter, &graphicPoint, &realPointPenId);
    }
    
    for (GraphicLine line : *viewModel->getGraphicLines()) {
        QLineF lineF(line);
        draw(painter, &lineF);
    }

    painter->setPen(QPen(Qt::red, 5));

    for (GraphicPoint graphicPoint : *viewModel->getResultingGraphicPoints()) {
        QPointF point(graphicPoint);
        draw(painter, &point, &resultingPointPen);
        draw_id(painter, &graphicPoint, &resultingPointPenId);
    }

    for (GraphicLine line : *viewModel->getResultingGraphicLines()) {
        QLineF lineF(line);
        draw(painter, &lineF);
    }

    for (InfinityGraphicLine line : *viewModel->getInfinityGraphicLines()) {
        std::pair<QLineF, QLineF> infinityLine(line);
        QLineF firstLineF(infinityLine.first), secondLineF(infinityLine.second);
        draw(painter, &firstLineF);
        draw(painter, &secondLineF);
    }

    
    
    painter->end();

}

// void Canvas::draw(QPainter* painter, Item* item) {
//     painter->drawLine(*item);
// }


void Canvas::draw(QPainter* painter, QLineF* line) {
    painter->drawLine(*line);

}

void Canvas::draw(QPainter* painter, QPointF* point, QPen* pen) {
    painter->setPen(*pen);
    painter->drawPoint(*point);

}


void Canvas::draw_id(QPainter* painter, Item* item, QPen* pen) {

    QString id = QString::fromStdString(item->getId());
    qreal x = item->getX(), y = item->getY();

    QPainterPath path;
    QFont font("Arial", 30, 20, true);


    painter->setFont(font);
    painter->setPen(*pen);


    path.addText(x+15, y, font, id);
    painter->drawPath(path);

}


void Canvas::draw(QPainter* painter, std::pair<std::pair<QLineF, QLineF>, std::pair<QPointF, QPointF>> * complete_lens) {

    QPen pen(Qt::black, 5);

    this->draw(painter, &complete_lens->first.first);
    this->draw(painter, &complete_lens->first.second);
    this->draw(painter, &complete_lens->second.first, &pen);
    this->draw(painter, &complete_lens->second.second, &pen);

}


void Canvas::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        QPoint point = event->pos();
        drawPoint(point.x(), point.y());
    }
    else if (event->button() == Qt::RightButton) {
        
    }
    //drawSomePoints();
    
}

Axis* Canvas::buildAxis() {
    Axis * axis = new Axis(350, 100, 1200);
    return axis;
}


void CanvasThread::run() {

    //canvas_ptr->drawSomePoints();
    canvas_ptr->drawPoint(x, y);
}