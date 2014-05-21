/*
* The MIT License (MIT)
*
* Copyright (c) 20014 Moukhlynin Ruslan <me@ruslan.pw>
*
* map.cpp
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

#include "map.h"

#include "maprenderer.h"
#include "layer.h"


Map::Map(QObject *parent) :
    QObject(parent),
    p_renderer(new MapRenderer)
{
}

Map::~Map()
{
    delete p_renderer;
    qDeleteAll(p_layers);
    p_layers.clear();
}
Layer *Map::AddLayer(Layer *layer)
{
    if(layer == 0)
        layer = new Layer();
    GetRenderer()->SetExtent(layer->GetExtent());
    p_layers.append(layer);
    return layer;
}

const QList<Layer *> &Map::GetLayers()
{
    return p_layers;
}

MapRenderer *Map::GetRenderer()
{
    return p_renderer;
}

void Map::Draw(QPainter *painter)
{
    p_renderer->painter = painter;
    for(int i = 0;i < p_layers.count();i ++) {
        if(p_layers[i]->isVisible())
            p_layers[i]->Draw(p_renderer);
    }
}

void Map::DrawLabel(QPainter *painter)
{
    p_renderer->painter = painter;
    p_renderer->CleanLabelsRegion();
    for(int i = 0;i < p_layers.count();i++) {
        p_layers[i]->DrawLabel(p_renderer);
    }
}
