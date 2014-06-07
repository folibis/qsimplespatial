/*
* The MIT License (MIT)
*
* Copyright (c) 20014 Moukhlynin Ruslan <me@ruslan.pw>
*
* maptranslator.cpp
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

#include "maptranslator.h"

MapTranslator::MapTranslator()
{
    border = 20.0;
    zoomFactor = 0.5;
    p_zoom = 1;
}

void MapTranslator::SetExtent(const QSimpleSpatial::Extent &extent)
{
    p_currentExtent = extent;
    p_baseExtent = extent;
}

QSimpleSpatial::Extent MapTranslator::getBaseExtent() const
{
    return p_baseExtent;
}

QSimpleSpatial::Extent MapTranslator::getCurrentExtent() const
{
    return p_currentExtent;
}

double MapTranslator::getScaleFactor() const
{
    return factor;
}

void MapTranslator::Coord2Screen(double *x, double *y)
{
    *x = p_frameCenter.X + (*x - p_mapCenter.X) * factor;
    *y = p_frameCenter.Y + (p_mapCenter.Y - *y) * factor;
}

QSimpleSpatial::SimplePoint MapTranslator::Coord2Screen(double x, double y)
{
    QSimpleSpatial::SimplePoint point;
    point.X = p_frameCenter.X + (x - p_mapCenter.X) * factor;
    point.Y = p_frameCenter.Y + (p_mapCenter.Y - y) * factor;
    return point;
}

QSimpleSpatial::SimplePoint MapTranslator::Coord2Screen(const QSimpleSpatial::SimplePoint &point)
{
    QSimpleSpatial::SimplePoint p;
    p.X = p_frameCenter.X + (point.X - p_mapCenter.X) * factor;
    p.Y = p_frameCenter.Y + (p_mapCenter.Y - point.Y) * factor;
    return p;
}

QPoint MapTranslator::Coord2ScreenPoint(double x, double y)
{
    return QPoint(p_frameCenter.X + (x - p_mapCenter.X) * factor
                  ,p_frameCenter.Y + (p_mapCenter.Y - y) * factor);

}

QPoint MapTranslator::Coord2ScreenPoint(const QSimpleSpatial::SimplePoint &point)
{
    return QPoint(p_frameCenter.X + (point.X - p_mapCenter.X) * factor
                  ,p_frameCenter.Y + (p_mapCenter.Y - point.Y) * factor);
}

QSimpleSpatial::SimplePoint MapTranslator::Screen2Coord(double x, double y)
{
    QSimpleSpatial::SimplePoint point;
    point.X = p_mapCenter.X - (p_frameCenter.X - x) / factor;
    point.Y = p_mapCenter.Y - (y - p_frameCenter.Y) / factor;
    return point;
}

QSimpleSpatial::SimplePoint MapTranslator::Screen2Coord(const QSimpleSpatial::SimplePoint &point)
{
    return Screen2Coord(point.X, point.Y);
}

double MapTranslator::XCoordByPixel(double X)
{
    return X / factor;
}

double MapTranslator::YCoordByPixel(double Y)
{
    return Y / factor;
}

double MapTranslator::XPixel2MapCoord(double X)
{
    return p_mapCenter.X - (p_frameCenter.X - X) / factor;
}
double MapTranslator::YPixel2MapCoord(double Y)
{
    return p_mapCenter.Y - (p_frameCenter.Y - Y) / factor;
}

void MapTranslator::ZoomIn()
{
    p_currentExtent.Decrease(zoomFactor);
    p_zoom = (p_currentExtent.GetWidth()) / (p_baseExtent.GetWidth());
    p_labelRegion = QRegion();
    updateSize();
}

void MapTranslator::ZoomOut()
{
    p_currentExtent.Increase(zoomFactor);
    p_zoom = (p_currentExtent.GetWidth()) / (p_baseExtent.GetWidth());
    p_labelRegion = QRegion();
    updateSize();
}

void MapTranslator::ZoomBy(double zoom)
{
    if(zoom >= 0)
        p_currentExtent.Decrease(zoomFactor);
    else
        p_currentExtent.Increase(qAbs(zoom));
    zoom = (p_currentExtent.GetWidth()) / (p_baseExtent.GetWidth());
    p_labelRegion = QRegion();
    updateSize();
}

void MapTranslator::ZoomTo(double zoom)
{
    p_currentExtent.Update(p_baseExtent.p1().X * zoom,
                         p_baseExtent.p1().Y * zoom,
                         p_baseExtent.p2().X * zoom,
                         p_baseExtent.p2().Y * zoom);
    this->p_zoom = zoom;
    p_labelRegion = QRegion();
    updateSize();
}

void MapTranslator::updateSize()
{

    QSimpleSpatial::SimplePoint p1 = p_currentExtent.p1();
    QSimpleSpatial::SimplePoint p2 = p_currentExtent.p2();
    mapWidth = qAbs(p2.X - p1.X);
    mapHeight = qAbs(p2.Y - p1.Y);
    double frameK = frameWidth / frameHeight;
    double mapK = mapWidth / mapHeight;

    if(frameK >= mapK)
        factor = frameHeight /mapHeight;
    else
        factor = frameWidth /mapWidth;
    p_mapCenter.X = (p1.X + p2.X) / 2;
    p_mapCenter.Y = (p1.Y + p2.Y) / 2;
    p_frameCenter.X = frameWidth / 2;
    p_frameCenter.Y = frameHeight / 2;
    p_viewport = QSimpleSpatial::Extent(Screen2Coord(0,frameHeight),
                                      Screen2Coord(frameWidth,0));
}

void MapTranslator::moveBy(double X, double Y)
{
    p_currentExtent.MoveBy(X,Y);
}

void MapTranslator::CleanLabelsRegion()
{
    p_labelRegion = QRegion();
}

double MapTranslator::getZoom()
{
    return p_zoom;
}

void MapTranslator::setFrameSize(int width, int height)
{
    frameWidth = width;
    frameHeight = height;
}

const QSimpleSpatial::Extent &MapTranslator::getViewport()
{
    return p_viewport;
}

void MapTranslator::addLabelRect(const QRect &rect)
{
    p_labelRegion = p_labelRegion.united(rect);
}

bool MapTranslator::isLabelIntersects(const QRect &rect)
{
    return p_labelRegion.intersects(rect);
}



