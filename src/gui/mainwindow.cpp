#include "mainwindow.h"
#include "axis.h"
#include "painter.h"
#include <QApplication>
#include <QScreen>
#include <thread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), scene(new QGraphicsScene(this))
{
    ui.setupUi(this);
    ui.graphicsView->setVisible(false);
    scene->setBackgroundBrush(Qt::white);
    ui.graphicsView->setScene(scene);

    //CentralWidget centralWidget(this);

    //setCentralWidget(&centralWidget);

    canvas = new Canvas(centralWidget());
    //connect(canvas, &Canvas::clicked, this, &MainWindow::onCanvasClicked);
    canvas->setVisible(false);
    //ui.graphicButton->setVisible(false);
    QAction* createLine = new QAction("Create line...", this);
    connect(createLine, &QAction::triggered, this, &MainWindow::onCreateLine);

    QAction* createShape = new QAction("Create shape...", this);
    connect(createShape, &QAction::triggered, this, &MainWindow::onCreateShape);

    QMenu* fileMenu = menuBar()->addMenu("Sketch");
    fileMenu->addAction(createLine);
    fileMenu->addAction(createShape);
 
   
}

MainWindow::~MainWindow()
{}

void MainWindow::on_graphicProjectButton_clicked()
{
    ui.graphicProjectButton->setVisible(false);
    ui.numericProjectButton->setVisible(false);
    //ui.graphicsView->setVisible(true);

    canvas->setVisible(true);

    //QScreen* screen = QApplication::primaryScreen();
    //QSize size = screen->size();
    //Axis* axis = new Axis(500, 10, 1000);
    //axis->printAtributesOut();
    ////ui.graphicsView->setGeometry(0, 0, 1800, 900);
    //Painter painter(Qt::black, Qt::blue, 2);
    //painter.begin(ui.graphicsView);
    //painter.drawLine(QLineF(*axis));

}


void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        canvas->viewModel->drawFinishedShape();
        canvas->update();
    }
}


void MainWindow::onCreateShape() {
    canvas->viewModel->setDrawingShape(true);
    canvas->viewModel->setDrawingLine(false);
}


void MainWindow::onCreateLine() {
    canvas->viewModel->setDrawingLine(true);
    canvas->viewModel->setDrawingShape(false);
}


void MainWindow::threadFunction() {
    canvas->drawSomePoints();
}