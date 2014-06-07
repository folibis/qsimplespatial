/*
* The MIT License (MIT)
*
* Copyright (c) 20014 Moukhlynin Ruslan <me@ruslan.pw>
*
* labelscheme.h
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

#ifndef LABELSCHEME_H
#define LABELSCHEME_H

#include "mapglobal.h"

#include <QFont>
#include <QPen>


class Feature;
class MapTranslator;
class QPainter;

class LabelScheme
{
public:
    LabelScheme();
    LabelScheme(const QString &fieldName);
    LabelScheme(const QString &fieldName, const QFont &font, const QPen &pen);

    bool isAllowOverlap();
    void setAllowOverlap(bool allowOverlap);

    QString getFieldName() const;
    void setFieldName(const QString &fieldName);

    QFont getFont() const;
    void setFont(const QFont &font);

    QString getExpression() const;
    void setExpression(const QString &expression);

    QPen getPen() const;
    void setPen(const QPen &pen);

    QSimpleSpatial::SimplePoint getLabelOffset();
    void setLabelOffset(const QSimpleSpatial::SimplePoint &offset);

    QSimpleSpatial::LabelPosition getPosition();
    void setPosition(QSimpleSpatial::LabelPosition position);

    void SetFilterFunction(bool (* label_filter_func )(Feature *));
    bool TestFilter(Feature *feature);

    void setPaintFunction(bool (* label_paint_func)(QPainter *, MapTranslator *, Feature *, LabelScheme *));

    void Draw(MapTranslator *renderer, Feature *feature, QPainter *painter);

    bool isDefault();

protected:
    bool p_allowOverlap;
    QString p_fieldName;
    QFont p_font;
    QString p_expression;
    QPen p_pen;
    QSimpleSpatial::SimplePoint p_offset;
    QSimpleSpatial::LabelPosition p_position;
    void init(const QString &fieldName, const QFont &font, const QPen &pen);

    bool (* p_label_filter_func )(Feature *);
    bool (* p_label_paint_func )(QPainter *, MapTranslator *, Feature *, LabelScheme *);
};

#endif // LABELSCHEME_H
