#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_neweststudentai.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QPen>
#include <canvas.h>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::NewestStudentAIClass ui;
    QGraphicsScene* scene;
    Canvas* canvas;
    void threadFunction();
    QPushButton* button;
    void keyPressEvent(QKeyEvent* event) override;


private slots:
    void on_graphicProjectButton_clicked();
    void onCreateShape();
    void onCreateLine();

};