/*
* The MIT License (MIT)
*
* Copyright (c) 20014 Moukhlynin Ruslan <me@ruslan.pw>
*
* mapglobal.h
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

#ifndef MAPGLOBAL_H
#define MAPGLOBAL_H

#include <QPointF>
#include <QRectF>


namespace QSimpleSpatial
{
enum ShapeTypes {
    NullShape = 0,
    Point = 1,
    PolyLine = 3,
    Polygon = 5,
    MultiPoint = 8,
    PointZ = 11,
    PolyLineZ = 13,
    PolygonZ = 15,
    MultiPointZ = 18,
    PointM = 21,
    PolyLineM = 23,
    PolygonM = 25,
    MultiPointM = 28,
    MultiPatch = 31
};

typedef struct SimplePoint {
    double X;
    double Y;
} SimplePoint;


enum LabelPosition {
    Center,
    Centroid,
    FollowPath
};

class Extent {
public:
    explicit Extent()
    {
        p_p1.X = 0.0;
        p_p1.Y = 0.0;
        p_p2.X = 0.0;
        p_p2.Y = 0.0;
    }

    Extent(SimplePoint p1,SimplePoint p2)
    {
        p_p1 = p1;
        p_p2 = p2;
    }

    Extent(double x1,double y1,double x2,double y2)
    {
        p_p1.X = x1;
        p_p1.Y = y1;
        p_p2.X = x2;
        p_p2.Y = y2;
    }

    SimplePoint p1() const
    {
        return p_p1;
    }

    SimplePoint p2() const
    {
        return p_p2;
    }

    double GetWidth()
    {
        return qAbs(p_p2.X - p_p1.X);
    }

    double GetHeight()
    {
        return qAbs(p_p2.Y - p_p1.Y);
    }

    Extent& operator=(const Extent &src)
    {
        p_p1 = src.p1();
        p_p2 = src.p2();
        return *this;
    }

    void Update(Extent extent)
    {
        p_p1.X = extent.p1().X;
        p_p1.Y = extent.p1().Y;
        p_p2.X = extent.p2().X;
        p_p2.Y = extent.p2().Y;
    }

    void Update(SimplePoint point1,SimplePoint point2)
    {
        p_p1 = point1;
        p_p2 = point2;
    }

    void Update(double x1,double y1,double x2,double y2)
    {
        p_p1.X = x1;
        p_p1.Y = y1;
        p_p2.X = x2;
        p_p2.Y = y2;
    }

    void correctSize(const Extent &other)
    {
        if(other.IsEmpty())
            return;
        if(IsEmpty())
            Copy(other);
        else {
            if(other.p1().X < p_p1.X)
                p_p1.X = other.p1().X;
            if(other.p1().Y < p_p1.Y)
                p_p1.Y = other.p1().Y;
            if(other.p2().X > p_p2.X)
                p_p2.X = other.p2().X;
            if(other.p2().Y > p_p2.Y)
                p_p1.Y = other.p2().Y;
        }
    }
    void Copy(const Extent &other)
    {
        p_p1 = other.p1();
        p_p2 = other.p2();
    }

    void Decrease(double percent)
    {
        double dw = ((p_p2.X - p_p1.X) * (1.0 - percent)) / 2;
        double dh = ((p_p2.Y - p_p1.Y) * (1.0 - percent)) / 2;
        p_p1.X = p_p1.X + dw;
        p_p1.Y = p_p1.Y + dh;
        p_p2.X = p_p2.X - dw;
        p_p2.Y = p_p2.Y - dh;
    }
    void Increase(double percent)
    {
        double dw = ((p_p2.X - p_p1.X) * (1.0 / percent - 1.0)) / 2;
        double dh = ((p_p2.Y - p_p1.Y) * (1.0 / percent - 1.0)) / 2;
        p_p1.X = p_p1.X - dw;
        p_p1.Y = p_p1.Y - dh;
        p_p2.X = p_p2.X + dw;
        p_p2.Y = p_p2.Y + dh;
    }
    void MoveBy(double X, double Y)
    {
        p_p1.X = p_p1.X - X;
        p_p2.X = p_p2.X - X;
        p_p1.Y = p_p1.Y + Y;
        p_p2.Y = p_p2.Y + Y;
    }
    bool IsIntersect(const Extent &extent) const
    {
        SimplePoint p1 = extent.p1();
        SimplePoint p2 = extent.p2();
        if(p1.X > p_p2.X || p2.X < p_p1.X || p1.Y > p_p2.Y || p2.Y < p_p1.Y) return false;
        return true;
    }
    bool IsIntersect(const SimplePoint &point) const
    {
        if(point.X > p_p2.X || point.X < p_p1.X || point.Y > p_p2.Y || point.Y < p_p1.Y) return false;
        return true;
    }
    bool IsEmpty() const
    {
        return (p_p1.X == 0 && p_p2.X == 0 && p_p1.Y == 0 && p_p2.Y == 0);
    }

    QRectF GetRect() const {
        return QRectF(p_p1.X, p_p1.Y, qAbs(p_p1.X - p_p2.X), qAbs(p_p1.Y - p_p2.Y));
    }

private:
    SimplePoint p_p1;
    SimplePoint p_p2;
};

} // namespace

#endif // MAPGLOBAL_H
