/*
* The MIT License (MIT)
*
* Copyright (c) 20014 Moukhlynin Ruslan <me@ruslan.pw>
*
* labelscheme.cpp
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

#include "labelscheme.h"

#include "feature.h"
#include "maprenderer.h"


LabelScheme::LabelScheme() :
    p_allowOverlap(false),
    p_position(QSimpleSpatial::Center),
    p_label_filter_func(0),
    p_label_paint_func(0)

{
    p_offset.X = 0;
    p_offset.Y = 0;
}

LabelScheme::LabelScheme(const QString &fieldName) :
    p_allowOverlap(false),
    p_position(QSimpleSpatial::Center),
    p_label_filter_func(0),
    p_label_paint_func(0)

{
    init(fieldName,QFont("Tahoma",8),QPen(Qt::black));
}

LabelScheme::LabelScheme(const QString &fieldName, const QFont &font, const QPen &pen) :
    p_allowOverlap(false),
    p_position(QSimpleSpatial::Center),
    p_label_filter_func(0),
    p_label_paint_func(0)
{
    init(fieldName,font,pen);
}

bool LabelScheme::isAllowOverlap()
{
    return p_allowOverlap;
}

void LabelScheme::setAllowOverlap(bool allowOverlap)
{
    p_allowOverlap = allowOverlap;
}

QString LabelScheme::getFieldName() const
{
    return p_fieldName;
}

void LabelScheme::setFieldName(const QString &fieldName)
{
    p_fieldName = fieldName;
}

QFont LabelScheme::getFont() const
{
    return p_font;
}

void LabelScheme::setFont(const QFont &font)
{
    p_font = font;
}

QString LabelScheme::getExpression() const
{
    return p_expression;
}

void LabelScheme::setExpression(const QString &expression)
{
    p_expression = expression;
}

QPen LabelScheme::getPen() const
{
    return p_pen;
}

void LabelScheme::setPen(const QPen &pen)
{
    p_pen = pen;
}

QSimpleSpatial::SimplePoint LabelScheme::getLabelOffset()
{
    return p_offset;
}

void LabelScheme::setLabelOffset(const QSimpleSpatial::SimplePoint &offset)
{
    p_offset = offset;
}

QSimpleSpatial::LabelPosition LabelScheme::getPosition()
{
    return p_position;
}

void LabelScheme::setPosition(QSimpleSpatial::LabelPosition position)
{
    p_position = position;
}

void LabelScheme::SetFilterFunction(bool (*label_filter_func)(Feature *))
{
    p_label_filter_func = label_filter_func;
}

bool LabelScheme::TestFilter(Feature *feature)
{
    if(p_label_filter_func == NULL) return false;
    return p_label_filter_func(feature);
}

void LabelScheme::setPaintFunction(bool (*label_paint_func)(MapRenderer *, Feature *, LabelScheme *))
{
    p_label_paint_func = label_paint_func;
}

void LabelScheme::Draw(MapRenderer *renderer, Feature *feature)
{
    if(p_label_paint_func) {
        if(p_label_paint_func(renderer, feature, this))
            return;
    }
    if(!p_fieldName.isEmpty()) {
        QString name = feature->GetFieldValue(p_fieldName);
        QSimpleSpatial::SimplePoint labelPosition = feature->getLabelPosition(p_position);
        QSimpleSpatial::SimplePoint point = renderer->Coord2Pixel(labelPosition);
        QRect rect = renderer->painter->fontMetrics().boundingRect(name);
        rect.moveTo(point.X - rect.width() / 2 + p_offset.X,point.Y - rect.height() / 2 + p_offset.Y);
        if(p_allowOverlap || !renderer->labels.intersects(rect)) {
            renderer->painter->setPen(p_pen);
            renderer->painter->setFont(p_font);
            renderer->painter->drawText(rect,Qt::AlignVCenter,name);
            if(!p_allowOverlap)
                renderer->labels = renderer->labels.united(rect);
        }
    }
}

bool LabelScheme::isDefault()
{
    return (p_label_filter_func == 0);
}

void LabelScheme::init(const QString &fieldName, const QFont &font, const QPen &pen)
{
    p_fieldName = fieldName;
    p_font = font;
    p_pen = pen;
    p_offset.X = 0;
    p_offset.Y = 0;
}