/*
* The MIT License (MIT)
*
* Copyright (c) 20014 Moukhlynin Ruslan <me@ruslan.pw>
*
* mapframe.h
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

#ifndef MAPFRAME_H
#define MAPFRAME_H

#include <QWidget>

class Layer;
class MapTranslator;
class QPainter;
class Projection;

class MapFrame : public QWidget
{
    Q_OBJECT
public:
    enum MapState {
        MapStateFixed = 0,
        MapStateShift = 1,
        MapStateZoom = 2,
        MapStateMove = 3,
        MapStateEdit = 4
    };

    explicit MapFrame(QWidget *parent = 0);
    ~MapFrame();
    void setBackground(const QBrush &brush);
    Layer *AddLayer(Layer *layer = 0);
    const QList<Layer *> &GetLayers();
    MapTranslator *GetTranslator();
    void Draw(QPainter *painter);
    void DrawLabel(QPainter *painter);
    Projection *getProjection() const;
    void setProjection(Projection *projection);
    MapState getState() const;
    void setState(MapState state);
    void setDirty();
private:
    bool drag;
    bool p_isDirty;
    QPixmap *dragImage;
    QPoint dragStartPoint;
    QPoint dragCurrentPoint;
    QPixmap *shapeLayer;
    QPixmap *labelLayer;
    QBrush p_background;
    QList<Layer *> p_layers;
    MapTranslator *p_renderer;
    Projection *p_projection;
    MapState p_state;

    void paintEvent(QPaintEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

public slots:
    void updateMap();

signals:
    void paint(QPainter &painter);
    void clicked(QMouseEvent *event);
    void released(QMouseEvent *event);
    void moved(QMouseEvent *event);  
};

#endif // MAPFRAME_H
