/*
* The MIT License (MIT)
*
* Copyright (c) 20014 Moukhlynin Ruslan <me@ruslan.pw>
*
* mapframe.cpp
* This file is part of the QSimpleSpatial.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#include "mapframe.h"

#include "maprenderer.h"

#include <QWheelEvent>
#include <QDebug>


MapFrame::MapFrame(QWidget *parent) :
    QWidget(parent),
    p_background(Qt::white)
{
    drag = false;
    shapeLayer = new QPixmap();
    labelLayer = new QPixmap();
}

MapFrame::~MapFrame()
{
    delete shapeLayer;
    delete labelLayer;
}

void MapFrame::SetMap(Map *map)
{
    p_map = map;
    p_map->GetRenderer()->frameWidth = (double)width();
    p_map->GetRenderer()->frameHeight = (double)height();
}

void MapFrame::setBackground(const QBrush &brush)
{
    p_background = brush;
}

void MapFrame::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    if(drag)
    {
        double X = dragCurrentPoint.x() - dragStartPoint.x();
        double Y = dragCurrentPoint.y() - dragStartPoint.y();
        p.drawPixmap(X,Y,*dragImage);

    }
    else
    {
        shapeLayer->fill();
        QPainter painter(shapeLayer);
        painter.setClipRect(rect());
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(p_background);
        painter.setPen(Qt::green);
        painter.drawRect(rect());
        p_map->Draw(&painter);
        labelLayer->fill(Qt::transparent);
        QPainter painter2(labelLayer);
        p_map->DrawLabel(&painter2);
        p.drawPixmap(0,0,width(),height(),*shapeLayer);
        p.drawPixmap(0,0,width(),height(),*labelLayer);
    }
    emit paint(p);
}

void MapFrame::wheelEvent(QWheelEvent *event)
{
    QPoint p = event->pos();
    QPoint center(width() / 2, height() / 2);
    double X = p_map->GetRenderer()->XCoordByPixel(center.x() - p.x());
    double Y = p_map->GetRenderer()->YCoordByPixel(center.y() - p.y());
    p_map->GetRenderer()->moveBy(X,Y);
    p_map->GetRenderer()->updateSize();

    if(event->delta() > 0)
        p_map->GetRenderer()->ZoomIn();
    else
        p_map->GetRenderer()->ZoomOut();
    repaint();
}

void MapFrame::mouseMoveEvent(QMouseEvent *event)
{
    if(drag) {
        dragCurrentPoint = event->pos();
        repaint();
    }
}

void MapFrame::mousePressEvent(QMouseEvent *event)
{
    setCursor(Qt::SizeAllCursor);
    dragImage = new QPixmap(size());
    QPainter painter(dragImage);
    painter.drawPixmap(0,0,width(),height(),*shapeLayer);
    painter.drawPixmap(0,0,width(),height(),*labelLayer);
    drag = true;
    dragStartPoint = event->pos();
}

void MapFrame::mouseReleaseEvent(QMouseEvent *event)
{
    drag = false;
    delete dragImage;
    QPoint point = event->pos();
    double X = p_map->GetRenderer()->XCoordByPixel(point.x() - dragStartPoint.x());
    double Y = p_map->GetRenderer()->YCoordByPixel(point.y() - dragStartPoint.y());
    p_map->GetRenderer()->moveBy(X,Y);
    p_map->GetRenderer()->updateSize();
    repaint();
    setCursor(Qt::ArrowCursor);
}

void MapFrame::resizeEvent(QResizeEvent *)
{
    p_map->GetRenderer()->frameWidth = (double)width();
    p_map->GetRenderer()->frameHeight = (double)height();
    p_map->GetRenderer()->updateSize();
    delete shapeLayer;
    shapeLayer = new QPixmap(width(),height());
    delete labelLayer;
    labelLayer = new QPixmap(width(),height());
    repaint();
}
