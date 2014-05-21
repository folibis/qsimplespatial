/*
* The MIT License (MIT)
*
* Copyright (c) 20014 Moukhlynin Ruslan <me@ruslan.pw>
*
* layer.h
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

#ifndef LAYER_H
#define LAYER_H

#include "feature.h"
#include "mapglobal.h"
#include "paintscheme.h"

#include <QObject>
#include <QList>


typedef QList<Feature *> Features;

class Layer : public QObject
{
    Q_OBJECT
public:
    explicit Layer(QObject *parent = 0);
    Layer(PaintScheme * scheme, QObject *parent = 0);

    Feature * AddFeature(Feature * feature);
    qint32 Count();

    void AddScheme(PaintScheme *scheme);
    void AddLabelScheme(LabelScheme *scheme);

    QSimpleSpatial::Extent GetBaseExtent();

    bool isVisible();
    void setVisible(bool visible);

    void SetExtent(const QSimpleSpatial::Extent &extent);
    QSimpleSpatial::Extent GetExtent();

    QSimpleSpatial::ShapeTypes GetShapeType();
    void SetShapeType(QSimpleSpatial::ShapeTypes shapeType);

    double GetMaxZoom(Feature *feature);
    void setMaxZoom(double zoom);

    double GetMinZoom(Feature *feature);
    void setMinZoom(double zoom);

    void SetMinZoomFilter(double (*min_zoom_filter_func)(Feature *));
    void SetMaxZoomFilter(double (*max_zoom_filter_func)(Feature *));

    void Draw(MapRenderer *renderer);
    void DrawLabel(MapRenderer *renderer);

private:
    bool p_visible;
    QList<Feature *> p_list;

    QSimpleSpatial::Extent p_baseExtent;
    QSimpleSpatial::Extent p_extent;

    QSimpleSpatial::ShapeTypes p_shapeType;

    QList<PaintScheme *> p_schemes;
    QList<LabelScheme *> p_labelSchemes;

    double p_minZoom;
    double p_maxZoom;

    double (* p_min_zoom_filter_func )(Feature *);
    double (* p_max_zoom_filter_func )(Feature *);

    void setMaxZoomForFeatures();
    void setMinZoomForFeatures();

    void setSchemeForFeatures();
    void setLabelSchemeForFeatures();
};

#endif // LAYER_H
