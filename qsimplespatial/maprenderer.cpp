/*
* The MIT License (MIT)
*
* Copyright (c) 20014 Moukhlynin Ruslan <me@ruslan.pw>
*
* maprenderer.cpp
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

#include "maprenderer.h"

MapRenderer::MapRenderer()
{
    border = 20.0;
    zoomFactor = 0.5;
    zoom = 1;
}

void MapRenderer::SetExtent(const QSimpleSpatial::Extent &extent)
{
    currentExtent = extent;
    baseExtent = extent;
}

double MapRenderer::getScaleFactor() const
{
    return factor;
}

void MapRenderer::Coord2Pixel(double *x, double *y)
{
    *x = frameCenter.X + (*x - mapCenter.X) * factor;
    *y = frameCenter.Y + (mapCenter.Y - *y) * factor;
}

QSimpleSpatial::SimplePoint MapRenderer::Coord2Pixel(double x, double y)
{
    QSimpleSpatial::SimplePoint point;
    point.X = frameCenter.X + (x - mapCenter.X) * factor;
    point.Y = frameCenter.Y + (mapCenter.Y - y) * factor;
    return point;
}

QSimpleSpatial::SimplePoint MapRenderer::Coord2Pixel(const QSimpleSpatial::SimplePoint &point)
{
    QSimpleSpatial::SimplePoint p;
    p.X = frameCenter.X + (point.X - mapCenter.X) * factor;
    p.Y = frameCenter.Y + (mapCenter.Y - point.Y) * factor;
    return p;
}

QPoint MapRenderer::Coord2Point(double x, double y)
{
    return QPoint(frameCenter.X + (x - mapCenter.X) * factor
                 ,frameCenter.Y + (mapCenter.Y - y) * factor);

}

QPoint MapRenderer::Coord2Point(const QSimpleSpatial::SimplePoint &point)
{
    return QPoint(frameCenter.X + (point.X - mapCenter.X) * factor
                 ,frameCenter.Y + (mapCenter.Y - point.Y) * factor);
}

int MapRenderer::XPixelByCoord(double X)
{
    return static_cast<int>(X * factor);
}

int MapRenderer::YPixelByCoord(double Y)
{
    return static_cast<int>(Y * factor);
}

double MapRenderer::XCoordByPixel(double X)
{
    return X / factor;
}

double MapRenderer::YCoordByPixel(double Y)
{
    return Y / factor;
}

double MapRenderer::XPixel2MapCoord(double X)
{
    return mapCenter.X - (frameCenter.X - X) / factor;
}
double MapRenderer::YPixel2MapCoord(double Y)
{
    return mapCenter.Y - (frameCenter.Y - Y) / factor;
}

void MapRenderer::ZoomIn()
{
    currentExtent.Decrease(zoomFactor);
    zoom = (currentExtent.GetWidth()) / (baseExtent.GetWidth());
    labels = QRegion();
    updateSize();
}

void MapRenderer::ZoomOut()
{
    currentExtent.Increase(zoomFactor);
    zoom = (currentExtent.GetWidth()) / (baseExtent.GetWidth());
    labels = QRegion();
    updateSize();
}

void MapRenderer::ZoomBy(double zoom)
{
    if(zoom >= 0)
        currentExtent.Decrease(zoomFactor);
    else
        currentExtent.Increase(qAbs(zoom));
    zoom = (currentExtent.GetWidth()) / (baseExtent.GetWidth());
    labels = QRegion();
    updateSize();
}

void MapRenderer::updateSize()
{
    double frameK = frameWidth / frameHeight;
    QSimpleSpatial::SimplePoint p1 = currentExtent.p1();
    QSimpleSpatial::SimplePoint p2 = currentExtent.p2();
    mapWidth = qAbs(p2.X - p1.X);
    mapHeight = qAbs(p2.Y - p1.Y);
    double mapK = mapWidth / mapHeight;

    if(frameK >= mapK)
        factor = frameHeight /mapHeight;
    else
        factor = frameWidth /mapWidth;
    mapCenter.X = (p1.X + p2.X) / 2;
    mapCenter.Y = (p1.Y + p2.Y) / 2;
    frameCenter.X = frameWidth / 2;
    frameCenter.Y = frameHeight / 2;
    viewport = QSimpleSpatial::Extent(XPixel2MapCoord(0),
                      YPixel2MapCoord(0),
                      XPixel2MapCoord(frameWidth),
                      YPixel2MapCoord(frameHeight));
}

void MapRenderer::moveBy(double X, double Y)
{
    currentExtent.MoveBy(X,Y);
}

void MapRenderer::CleanLabelsRegion()
{
    labels = QRegion();
}

double MapRenderer::getZoom()
{
    return zoom;
}



