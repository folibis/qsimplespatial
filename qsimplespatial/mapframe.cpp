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

#include "maptranslator.h"
#include "layer.h"
#include "projection.h"

#include <QWheelEvent>
#include <QDebug>


MapFrame::MapFrame(QWidget *parent) :
    QWidget(parent),
    p_isDirty(true),
    p_background(Qt::white),
    p_renderer(new MapTranslator),
    p_state(MapStateMove)
{
    drag = false;
    p_renderer->setFrameSize(width(),height());
    shapeLayer = new QPixmap();
    labelLayer = new QPixmap();
}

MapFrame::~MapFrame()
{
    delete shapeLayer;
    delete labelLayer;
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
        if(p_isDirty) {

            shapeLayer->fill();
            QPainter painter(shapeLayer);
            painter.setClipRect(rect());
            painter.setRenderHint(QPainter::Antialiasing);
            painter.setBrush(p_background);
            painter.drawRect(rect());
            Draw(&painter);

            labelLayer->fill(Qt::transparent);
            QPainter painter2(labelLayer);
            painter2.setRenderHint(QPainter::TextAntialiasing);
            DrawLabel(&painter2);

            p_isDirty = false;
        }
        p.drawPixmap(0,0,width(),height(),*shapeLayer);
        p.drawPixmap(0,0,width(),height(),*labelLayer);
    }

    emit paint(p);
}

void MapFrame::wheelEvent(QWheelEvent *event)
{
    if(getState() & MapFrame::MapStateZoom) {
        QPoint p = event->pos();
        QPoint center(width() / 2, height() / 2);
        double X = p_renderer->XCoordByPixel(center.x() - p.x());
        double Y = p_renderer->YCoordByPixel(center.y() - p.y());
        p_renderer->moveBy(X,Y);
        p_renderer->updateSize();

        if(event->delta() > 0)
            p_renderer->ZoomIn();
        else
            p_renderer->ZoomOut();
        updateMap();
    }
}

void MapFrame::mouseMoveEvent(QMouseEvent *event)
{
    if(getState() & MapFrame::MapStateShift) {
        if(drag) {
            dragCurrentPoint = event->pos();
            updateMap();
        }
        emit moved(event);
    }
}

void MapFrame::mousePressEvent(QMouseEvent *event)
{
    if(getState() & MapFrame::MapStateShift) {
        setCursor(Qt::SizeAllCursor);
        dragImage = new QPixmap(size());
        QPainter painter(dragImage);
        painter.drawPixmap(0,0,width(),height(),*shapeLayer);
        painter.drawPixmap(0,0,width(),height(),*labelLayer);
        drag = true;
        dragStartPoint = event->pos();
    }
    emit clicked(event);
}

void MapFrame::mouseReleaseEvent(QMouseEvent *event)
{
    if(getState() & MapFrame::MapStateShift) {
        drag = false;
        delete dragImage;
        QPoint point = event->pos();
        double X = p_renderer->XCoordByPixel(point.x() - dragStartPoint.x());
        double Y = p_renderer->YCoordByPixel(point.y() - dragStartPoint.y());
        p_renderer->moveBy(X,Y);
        p_renderer->updateSize();
        updateMap();
        setCursor(Qt::ArrowCursor);
    }
    emit released(event);
}

void MapFrame::resizeEvent(QResizeEvent *)
{

    p_renderer->setFrameSize(width(),height());
    p_renderer->updateSize();

    delete shapeLayer;
    shapeLayer = new QPixmap(width(),height());
    delete labelLayer;
    labelLayer = new QPixmap(width(),height());
    updateMap();
}

void MapFrame::updateMap()
{
    p_isDirty = true;
    update();
}

Layer *MapFrame::AddLayer(Layer *layer)
{
    if(layer == 0)
        layer = new Layer();
    QSimpleSpatial::Extent e = GetTranslator()->getBaseExtent();
    e.correctSize(layer->GetExtent());
    GetTranslator()->SetExtent(e);
    p_layers.append(layer);
    return layer;
}

const QList<Layer *> &MapFrame::GetLayers()
{
    return p_layers;
}

MapTranslator *MapFrame::GetTranslator()
{
    return p_renderer;
}

void MapFrame::Draw(QPainter *painter)
{
    for(int i = 0;i < p_layers.count();i ++) {
        if(p_layers[i]->isVisible())
            p_layers[i]->Draw(p_renderer, painter);
    }
}

void MapFrame::DrawLabel(QPainter *painter)
{
    p_renderer->CleanLabelsRegion();
    for(int i = 0;i < p_layers.count();i++) {
        if(p_layers[i]->isVisible())
            p_layers[i]->DrawLabel(p_renderer, painter);
    }
}

Projection *MapFrame::getProjection() const
{
    return p_projection;
}

void MapFrame::setProjection(Projection *projection)
{
    p_projection = projection;
}

MapFrame::MapState MapFrame::getState() const
{
    return p_state;
}

void MapFrame::setState(MapFrame::MapState state)
{
    p_state = state;
}

void MapFrame::setDirty()
{
    p_isDirty = true;
}
