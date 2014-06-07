/*
* The MIT License (MIT)
*
* Copyright (c) 20014 Moukhlynin Ruslan <me@ruslan.pw>
*
* projection.h
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

#ifndef PROJECTION_H
#define PROJECTION_H

#include "mapglobal.h"

#include <cmath>

#define M_PI_2		1.57079632679489661923
#define M_PI		3.14159265358979323846
#define D_R (M_PI / 180.0)
#define R_D (180.0 / M_PI)

#define RAD_TO_DEG	57.29577951308232
#define DEG_TO_RAD	.0174532925199432958


class Projection
{
public:
    Projection();
    virtual QSimpleSpatial::SimplePoint toCartesian(double X, double Y) = 0;
    virtual void toCartesian(int count, double *x, double *y, double *z = 0) = 0;
    virtual double toCartesianLat(double point) = 0;
    virtual double toCartesianLon(double point) = 0;
    virtual QSimpleSpatial::SimplePoint toGeodetic(double lat, double lon) = 0;
    double deg_rad (double ang);
    double rad_deg (double ang);
};

#endif // PROJECTION_H
