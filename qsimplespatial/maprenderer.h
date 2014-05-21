/*
* The MIT License (MIT)
*
* Copyright (c) 20014 Moukhlynin Ruslan <me@ruslan.pw>
*
* maprenderer.h
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

#ifndef MAPRENDERER_H
#define MAPRENDERER_H

#include "mapglobal.h"

#include <QPainter>


class MapRenderer
{
public:
    explicit MapRenderer();
    void SetExtent(const QSimpleSpatial::Extent &extent);
    QPainter *painter;
    double getScaleFactor() const;
    double zoomFactor;
    double zoomIndex;
    double frameWidth;
    double frameHeight;
    double mapWidth;
    double mapHeight;
    double offsetX;
    double offsetY;
    void Coord2Pixel(double *x, double *y);
    QSimpleSpatial::SimplePoint Coord2Pixel(double x, double y);
    QSimpleSpatial::SimplePoint Coord2Pixel(const QSimpleSpatial::SimplePoint &point);
    QPoint Coord2Point(double x, double y);
    QPoint Coord2Point(const QSimpleSpatial::SimplePoint &point);
    int XPixelByCoord(double X);
    int YPixelByCoord(double Y);
    double XCoordByPixel(double X);
    double YCoordByPixel(double Y);
    double XPixel2MapCoord(double X);
    double YPixel2MapCoord(double Y);
    void ZoomIn();
    void ZoomOut();
    void ZoomBy(double zoom);
    void updateSize();
    void moveBy(double X,double Y);
    void CleanLabelsRegion();
    double getZoom();
    double border;
    QSimpleSpatial::Extent viewport;
    QRegion labels;

private:
    double factor;
    QSimpleSpatial::Extent currentExtent;
    QSimpleSpatial::Extent baseExtent;
    QSimpleSpatial::SimplePoint mapCenter;
    QSimpleSpatial::SimplePoint frameCenter;
    double zoom;
};

#endif // MAPRENDERER_H
