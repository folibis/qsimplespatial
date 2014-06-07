/*
* The MIT License (MIT)
*
* Copyright (c) 20014 Moukhlynin Ruslan <me@ruslan.pw>
*
* paintschemepolyline.cpp
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

#include "paintschemepolyline.h"

#include "polylinefeature.h"
#include "maptranslator.h"


PaintSchemePolyline::PaintSchemePolyline() :
    PaintScheme(),
    p_borderWidth(0),
    p_lineWidth(1),
    p_lineSimplified(true)
{
}

PaintSchemePolyline::PaintSchemePolyline(const QPen &pen) :
    PaintScheme(pen,QBrush()),
    p_borderWidth(0),
    p_lineWidth(pen.width()),
    p_lineSimplified(true)
{
}

PaintSchemePolyline::PaintSchemePolyline(const QPen &pen, const QBrush &brush, int width) :
    PaintScheme(pen,brush),
    p_borderWidth(pen.width()),
    p_lineWidth(width - p_borderWidth * 2),
    p_lineSimplified(true)
{
}

QSimpleSpatial::ShapeTypes PaintSchemePolyline::getShapeType()
{
    return QSimpleSpatial::PolyLine;
}

void PaintSchemePolyline::Draw(MapTranslator *renderer, Feature *feature, QPainter *painter)
{
    PolylineFeature *pf = static_cast<PolylineFeature *>(feature);
    double x,y,prev_x,prev_y;
    const QVector<Points *> *array = pf->getPointsArray();
    int cycles = (p_borderWidth > 0 && p_brush.style() != Qt::NoBrush) ? 2 : 1;
    for(int c = 0;c < cycles; c ++) {
        if(c == 0) {
            p_pen.setWidth(p_lineWidth > 0 ? p_borderWidth * 2 + p_lineWidth : p_borderWidth);
            painter->setPen(p_pen);

        } else {
            painter->setPen(QPen(p_brush,p_lineWidth));
        }
        for(int i = 0;i < array->count();i ++) {
            Points *points = array->at(i);
            prev_x = points->x[0];
            prev_y = points->y[0];
            renderer->Coord2Screen(&prev_x,&prev_y);
            int j;
            for(j = 1;j < (points->count - 1);j ++) {
                x = points->x[j];
                y = points->y[j];
                renderer->Coord2Screen(&x,&y);
                if(!p_lineSimplified || qAbs(x - prev_x) > 1 || qAbs(y - prev_y) > 1) {
                    painter->drawLine(prev_x,prev_y,x,y);
                    prev_x = x;
                    prev_y = y;
                }
            }
            x = points->x[j];
            y = points->y[j];
            renderer->Coord2Screen(&x,&y);
            painter->drawLine(prev_x,prev_y,x,y);
        }
    }
}

bool PaintSchemePolyline::isLineSimplified()
{
    return p_lineSimplified;
}

void PaintSchemePolyline::setLineSimplified(bool lineSimplified)
{
    p_lineSimplified = lineSimplified;
}
