/*
* The MIT License (MIT)
*
* Copyright (c) 20014 Moukhlynin Ruslan <me@ruslan.pw>
*
* paintschemepolygon.cpp
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

#include "paintschemepolygon.h"

#include "polygonfeature.h"
#include "maptranslator.h"

#include <QDateTime>


PaintSchemePolygon::PaintSchemePolygon() :
    PaintScheme(),
    p_lineSimplified(true)
{
}

PaintSchemePolygon::PaintSchemePolygon(const QPen &pen, const QBrush &brush) :
    PaintScheme(pen,brush),
    p_lineSimplified(true)
{
}

QSimpleSpatial::ShapeTypes PaintSchemePolygon::getShapeType()
{
    return QSimpleSpatial::Polygon;
}

void PaintSchemePolygon::Draw(MapTranslator *renderer, Feature *feature, QPainter *painter)
{
    PolygonFeature *pf = static_cast<PolygonFeature *>(feature);

    double x,y,prev_x,prev_y;
    const QVector<Points *> *array = pf->getPointsArray();
    QPainterPath outerPath;

    if(!p_colorsInitialized) {
        QPair<QColor,QColor> colors = getGhostColors(feature);
        painter->setPen(colors.first);
        painter->setBrush(colors.second);
    } else {
        painter->setPen(p_pen);
        painter->setBrush(p_brush);
    }
    for(int i = 0;i < array->count();i ++) {
        Points *points = array->at(i);
        outerPath.moveTo(renderer->Coord2ScreenPoint(points->x[0],points->y[0]));
        for(int j = 0;j < points->count;j ++)
        {
            x = points->x[j];
            y = points->y[j];
            renderer->Coord2Screen(&x,&y);
            if(p_lineSimplified && j > 0 && qAbs(x - prev_x) <=1 && qAbs(y - prev_y) <=1)
                continue;
            prev_x = x;
            prev_y = y;
            outerPath.lineTo(x,y);
        }
        outerPath.closeSubpath();
    }
    painter->drawPath(outerPath);
}

bool PaintSchemePolygon::isLineSimplified()
{
    return p_lineSimplified;
}

void PaintSchemePolygon::setLineSimplified(bool lineSimplified)
{
    p_lineSimplified = lineSimplified;
}

