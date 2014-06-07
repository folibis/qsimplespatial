/*
* The MIT License (MIT)
*
* Copyright (c) 20014 Moukhlynin Ruslan <me@ruslan.pw>
*
* paintscheme.h
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

#ifndef PAINTSCHEME_H
#define PAINTSCHEME_H

#include "maptranslator.h"

#include <QPen>
#include <QBrush>
#include <QMap>


class Feature;

class PaintScheme
{
public:
    PaintScheme();
    PaintScheme(const QPen &pen, const QBrush &brush);
    virtual ~PaintScheme(){}

    QPen GetPen() const;
    void setPen(const QPen &pen);

    QBrush GetBrush() const;
    void setBrush(const QBrush &brush);

    bool IsDefault();
    void SetFilterFunction(bool (* filter_func )(Feature *feature));
    bool TestFilter(Feature * feature);
    virtual QSimpleSpatial::ShapeTypes getShapeType();
    virtual void Draw(MapTranslator *renderer, Feature *feature, QPainter *painter) = 0;

protected:
    bool p_colorsInitialized;
    QPen p_pen;
    QBrush p_brush;
    QMap<Feature *,QPair<QColor,QColor> > p_ghostColors;
    bool (* p_filter_func )(Feature * feature);
    QPair<QColor,QColor> getGhostColors(Feature *feature);
    void init(const QPen &pen, const QBrush &brush);
};

inline int rrand(unsigned int min, unsigned int max){
    return (qrand() % (max-min)+1) + min;
}

#endif // PAINTSCHEME_H
