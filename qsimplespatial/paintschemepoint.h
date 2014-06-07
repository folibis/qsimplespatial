/*
* The MIT License (MIT)
*
* Copyright (c) 20014 Moukhlynin Ruslan <me@ruslan.pw>
*
* paintschemepoint.h
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

#ifndef POINTPAINTSCHEME_H
#define POINTPAINTSCHEME_H

#include "paintscheme.h"


class PaintSchemePoint : public PaintScheme
{
public:
    enum PointType {
        PointTypeUndefined = 0,
        PointTypeCircle,
        PointTypePolygon,
        PointTypePixmap
    };
    PaintSchemePoint();
    PaintSchemePoint(const QPen &pen, const QBrush brush, int size = 5);
    PaintSchemePoint(const QPen &pen, const QBrush brush, const QPolygon &polygon);
    PaintSchemePoint(const QPixmap &pixmap);

    QSimpleSpatial::ShapeTypes getShapeType();
    int GetSize();
    PointType getType();
    void Draw(MapTranslator *renderer, Feature *feature, QPainter *painter);

private:
    int p_size;
    QPolygon p_polygon;
    QPixmap p_pixmap;
    PointType p_type;
};

#endif // POINTPAINTSCHEME_H
