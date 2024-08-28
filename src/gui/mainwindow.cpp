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

    QAction* clearSketch = new QAction("Clear sketch...", this);
    connect(clearSketch, &QAction::triggered, this, &MainWindow::onClearSketch);

    QMenu* fileMenu = menuBar()->addMenu("Sketch");
    fileMenu->addAction(createLine);
    fileMenu->addAction(createShape);
    fileMenu->addAction(clearSketch);
 
   
}

MainWindow::~MainWindow()
{}

void MainWindow::on_graphicProjectButton_clicked()
{
    ui.graphicProjectButton->setVisible(false);
    ui.numericProjectButton->setVisible(false);

    canvas->createDefaultGraphicView();
    canvas->setVisible(true);
}

void MainWindow::on_numericProjectButton_clicked()
{
    ui.graphicProjectButton->setVisible(false);
    ui.numericProjectButton->setVisible(false);

    canvas->createDefaultNumericView();
    canvas->setVisible(true);

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

void MainWindow::onClearSketch() {
    canvas->viewModel->clearAllData();
    canvas->repaint();
}

void MainWindow::threadFunction() {
    canvas->drawSomePoints();
}