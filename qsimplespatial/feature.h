/*
* The MIT License (MIT)
*
* Copyright (c) 20014 Moukhlynin Ruslan <me@ruslan.pw>
*
* feature.h
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

#ifndef FEATURE_H
#define FEATURE_H

#include <QObject>
#include <QMap>

#include "mapglobal.h"
#include "paintscheme.h"
#include "labelscheme.h"


typedef QMap<QString,QString> DataFields;

class Layer;

typedef struct Points
{
    int count;
    bool inner;
    bool cw;
    double * x;
    double * y;
    double * z;
    double * m;
} Points;

class Feature
{
public:
    explicit Feature(Layer *parent);
    virtual ~Feature(){}
    QSimpleSpatial::ShapeTypes ShapeType();

    QString &GetFieldValue(const QString &name);

    void AddField(const QString &name, const QString &value);
    virtual void AddPoints(Points *points){Q_UNUSED(points)}
    virtual QSimpleSpatial::SimplePoint getCenter() const;
    virtual QSimpleSpatial::SimplePoint getCentroid() const;

    virtual QSimpleSpatial::Extent GetExtent() const;
    virtual void setExtent(const QSimpleSpatial::SimplePoint &p1,
                           const QSimpleSpatial::SimplePoint &p2);

    virtual QSimpleSpatial::SimplePoint getLabelPosition(QSimpleSpatial::LabelPosition position) const;

    Layer *GetLayer();
    const DataFields &GetDataFields() const;

    PaintScheme *getScheme() const;
    void SetScheme(PaintScheme *scheme);

    LabelScheme *getLabelScheme() const;
    void SetLabelScheme(LabelScheme *scheme);

    void setMinZoom(double zoom);
    double getMinZoom();

    void setMaxZoom(double zoom);
    double getMaxZoom();

protected:
    QSimpleSpatial::SimplePoint p_center;
    QSimpleSpatial::Extent p_extent;
    DataFields p_fields;
    LabelScheme *p_labelScheme;
    Layer *p_layer;
    double p_minZoom;
    double p_maxZoom;
    QSimpleSpatial::ShapeTypes p_shapeType;
    PaintScheme *p_scheme;
};

#endif // FEATURE_H
