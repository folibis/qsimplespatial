/*
* The MIT License (MIT)
*
* Copyright (c) 20014 Moukhlynin Ruslan <me@ruslan.pw>
*
* paintscheme.cpp
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

#include "paintscheme.h"

#include "maptranslator.h"

#include <QColor>
#include <QDateTime>


PaintScheme::PaintScheme() :
    p_colorsInitialized(false),
    p_filter_func(NULL)
{
}

PaintScheme::PaintScheme(const QPen &pen, const QBrush &brush) :
    p_colorsInitialized(true),
    p_filter_func(NULL)

{
    init(pen,brush);
}

QPen PaintScheme::GetPen() const
{
    return p_pen;
}

void PaintScheme::setPen(const QPen &pen)
{
    p_pen = pen;
}

QBrush PaintScheme::GetBrush() const
{
    return p_brush;
}

void PaintScheme::setBrush(const QBrush &brush)
{
    p_brush = brush;
}

bool PaintScheme::IsDefault()
{
    return (p_filter_func == NULL);
}

void PaintScheme::init(const QPen &pen, const QBrush &brush)
{
    p_pen = pen;
    p_brush = brush;
}

QPair<QColor, QColor> PaintScheme::getGhostColors(Feature *feature)
{
    if(p_ghostColors.contains(feature))
        return p_ghostColors[feature];

    qsrand(QDateTime::currentMSecsSinceEpoch());
    return p_ghostColors.insert(feature,QPair<QColor,QColor>(QColor::fromRgb(rrand(130,255),rrand(130,255),rrand(130,255)),
                                       QColor::fromRgb(rrand(130,255),rrand(130,255),rrand(130,255))))
            .value();
}

void PaintScheme::SetFilterFunction(bool (*filter_func)(Feature *))
{
    p_filter_func = filter_func;
}

bool PaintScheme::TestFilter(Feature *feature)
{
    if(p_filter_func == NULL)
        return false;
    return p_filter_func(feature);
}

QSimpleSpatial::ShapeTypes PaintScheme::getShapeType()
{
    return QSimpleSpatial::NullShape;
}


