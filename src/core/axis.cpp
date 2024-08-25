#include "axis.h"
#include <iostream>
#include <QDebug>
#include <QApplication>

Axis::Axis(int height, int start, int end) : height(height), width(5), start(start), end(end) {}


Axis::~Axis() {}


void Axis::printAtributesOut() {
	qDebug() << height << " " << width;
}