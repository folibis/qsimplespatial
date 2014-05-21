/*
* The MIT License (MIT)
*
* Copyright (c) 20014 Moukhlynin Ruslan <me@ruslan.pw>
*
* feature.cpp
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

#include "feature.h"

#include "layer.h"


Feature::Feature(Layer *parent) :
    p_labelScheme(0),
    p_layer(parent),
    p_minZoom(-1),
    p_maxZoom(-1),
    p_shapeType(QSimpleSpatial::NullShape),
    p_scheme(0)
{
}

QSimpleSpatial::ShapeTypes Feature::ShapeType()
{
    return p_shapeType;
}

void Feature::AddField(const QString &name, const QString &value)
{
    p_fields[name] = value;
}

QString &Feature::GetFieldValue(const QString &name)
{
    return p_fields[name];
}

QSimpleSpatial::SimplePoint Feature::getCenter() const
{
    return p_center;
}

QSimpleSpatial::SimplePoint Feature::getCentroid() const
{
    return p_center;
}

QSimpleSpatial::Extent Feature::GetExtent() const
{
    return p_extent;
}

void Feature::setExtent(const QSimpleSpatial::SimplePoint &p1,
                        const QSimpleSpatial::SimplePoint &p2)
{
    p_extent.Update(p1, p2);
    p_center.X = (p_extent.p1().X + p_extent.p2().X) / 2;
    p_center.Y = (p_extent.p1().Y + p_extent.p2().Y) / 2;
}

QSimpleSpatial::SimplePoint Feature::getLabelPosition(QSimpleSpatial::LabelPosition position) const
{
    Q_UNUSED(position)
    return p_center;
}

Layer *Feature::GetLayer()
{
    return p_layer;
}

DataFields const &Feature::GetDataFields() const
{
    return p_fields;
}

PaintScheme *Feature::getScheme() const
{
    return p_scheme;
}

void Feature::SetScheme(PaintScheme *scheme)
{
    p_scheme = scheme;
}

LabelScheme *Feature::getLabelScheme() const
{
    return p_labelScheme;
}

void Feature::SetLabelScheme(LabelScheme *scheme)
{
    p_labelScheme = scheme;
}

void Feature::setMinZoom(double zoom)
{
    p_minZoom = zoom;
}

double Feature::getMinZoom()
{
    return p_minZoom;
}

void Feature::setMaxZoom(double zoom)
{
    p_maxZoom = zoom;
}

double Feature::getMaxZoom()
{
    return p_maxZoom;
}
