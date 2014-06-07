/*
* The MIT License (MIT)
*
* Copyright (c) 20014 Moukhlynin Ruslan <me@ruslan.pw>
*
* maptranslator.h
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


class MapTranslator
{
public:
    explicit MapTranslator();
    void SetExtent(const QSimpleSpatial::Extent &extent);
    QSimpleSpatial::Extent getBaseExtent() const;
    QSimpleSpatial::Extent getCurrentExtent() const;
    double getScaleFactor() const;

    void Coord2Screen(double *x, double *y);
    QSimpleSpatial::SimplePoint Coord2Screen(double x, double y);
    QSimpleSpatial::SimplePoint Coord2Screen(const QSimpleSpatial::SimplePoint &point);
    QPoint Coord2ScreenPoint(double x, double y);
    QPoint Coord2ScreenPoint(const QSimpleSpatial::SimplePoint &point);

    QSimpleSpatial::SimplePoint Screen2Coord(double x, double y);
    QSimpleSpatial::SimplePoint Screen2Coord(const QSimpleSpatial::SimplePoint &point);

    double XCoordByPixel(double X);
    double YCoordByPixel(double Y);
    double XPixel2MapCoord(double X);
    double YPixel2MapCoord(double Y);

    void ZoomIn();
    void ZoomOut();
    void ZoomBy(double zoom);
    void ZoomTo(double zoom);

    void updateSize();
    void moveBy(double X,double Y);
    void CleanLabelsRegion();
    double getZoom();
    void setFrameSize(int width,int height);
    const QSimpleSpatial::Extent &getViewport();
    void addLabelRect(const QRect &rect);
    bool isLabelIntersects(const QRect &rect);

private:
    double zoomFactor;
    double zoomIndex;
    double frameWidth;
    double frameHeight;
    double mapWidth;
    double mapHeight;
    double offsetX;
    double offsetY;
    double factor;
    double border;
    QSimpleSpatial::Extent p_viewport;
    QRegion p_labelRegion;
    QSimpleSpatial::Extent p_currentExtent;
    QSimpleSpatial::Extent p_baseExtent;
    QSimpleSpatial::SimplePoint p_mapCenter;
    QSimpleSpatial::SimplePoint p_frameCenter;
    double p_zoom;
};

#endif // MAPRENDERER_H
