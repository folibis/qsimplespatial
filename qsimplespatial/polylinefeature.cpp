/*
* The MIT License (MIT)
*
* Copyright (c) 20014 Moukhlynin Ruslan <me@ruslan.pw>
*
* polygonfeature.cpp
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

#include "polylinefeature.h"

#include "paintscheme.h"

#include <QPolygon>
#include <QDateTime>
#include <QDebug>
#include <QDateTime>


PolylineFeature::PolylineFeature(Layer *parent) :
    Feature(parent)
{
    p_shapeType = QSimpleSpatial::PolyLine;
}

PolylineFeature::~PolylineFeature()
{
    foreach(Points *points, p_points) {
        if(points->x) delete [] points->x;
        if(points->y) delete [] points->y;
        if(points->z) delete [] points->z;
        if(points->m) delete [] points->m;
    }
    qDeleteAll(p_points);
}

void PolylineFeature::AddPoints(Points *points)
{
    p_points.append(points);
    double xMin = points->x[0];
    double yMin = points->y[0];
    double xMax = points->x[0];
    double yMax = points->y[0];
    for(int i = 1; i < points->count;i ++) {
        if(points->x[i] < xMin)
            xMin = points->x[i];
        else if(points->x[i] > xMax)
            xMax = points->x[i];
        if(points->y[i] < yMin)
            yMin = points->y[i];
        else if(points->y[i] > yMax)
            yMax = points->y[i];
    }
    p_extent.Update(xMin,yMin,xMax,yMax);
}

const QVector<Points *> *PolylineFeature::getPointsArray()
{
    return &p_points;
}

QSimpleSpatial::Extent PolylineFeature::GetExtent() const
{
    return p_extent;
}

QSimpleSpatial::SimplePoint PolylineFeature::getLabelPosition(QSimpleSpatial::LabelPosition position) const
{
    if(position == QSimpleSpatial::Centroid)
        return getClosestPoint(p_center);
    return p_center;
}
/*
QSimpleSpatial::SimplePoint PolylineFeature::getCentroid() const
{
    QSimpleSpatial::SimplePoint centroid;
    centroid.X = 0.0;
    centroid.Y = 0.0;
    double signedArea = 0.0;
    double x0 = 0.0;
    double y0 = 0.0;
    double x1 = 0.0;
    double y1 = 0.0;
    double a = 0.0;
    int i=0;
    if(p_points.length() > 0) {
        Points *points = p_points[0];
        for (i = 0; i < points->count - 1; ++i) {
            x0 = points->x[i];
            y0 = points->y[i];
            x1 = points->x[i + 1];
            y1 = points->y[i + 1];
            a = x0 * y1 - x1 * y0;
            signedArea += a;
            centroid.X += (x0 + x1) * a;
            centroid.Y += (y0 + y1) * a;
        }

        x0 = points->x[i];
        y0 = points->y[i];
        x1 = points->y[0];
        y1 = points->y[0];
        a = x0 * y1 - x1 * y0;
        signedArea += a;
        centroid.X += (x0 + x1) * a;
        centroid.Y += (y0 + y1) * a;

        signedArea *= 0.5;
        centroid.X /= (6.0 * signedArea);
        centroid.Y /= (6.0 * signedArea);
    }

    return centroid;
}
*/
QSimpleSpatial::SimplePoint PolylineFeature::getClosestPoint(const QSimpleSpatial::SimplePoint &toPoint) const
{
    QSimpleSpatial::SimplePoint point;
    double x,y;
    double delta;
    Points *points = p_points[0];
    point.X = points->x[0];
    point.Y = points->y[0];

    delta = qAbs(toPoint.X - point.X) + qAbs(toPoint.Y + point.Y);
    for (int i = 1; i < points->count; ++i) {
        x = points->x[i];
        y = points->y[i];
        if(qAbs(toPoint.X - x) + qAbs(toPoint.Y + y) < delta)
        {
            point.X = x;
            point.Y = y;
            delta = qAbs(toPoint.X - point.X) + qAbs(toPoint.Y + point.Y);
        }
    }

    return point;
}


