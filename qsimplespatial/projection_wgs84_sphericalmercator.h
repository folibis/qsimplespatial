/*
* The MIT License (MIT)
*
* Copyright (c) 20014 Moukhlynin Ruslan <me@ruslan.pw>
*
* projection_wgs84_sphericalmercator.h
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

#ifndef PROJECTION_WGS84_SPHERICALMERCATOR_H
#define PROJECTION_WGS84_SPHERICALMERCATOR_H

#include "projection.h"

class Projection_WGS84_SphericalMercator : public Projection
{
public:
    Projection_WGS84_SphericalMercator();
    QSimpleSpatial::SimplePoint toCartesian(double lon, double lat);
    void toCartesian(int count, double *lon, double *lat, double *z = 0);
    double toCartesianLat(double lat);
    double toCartesianLon(double lon);
    QSimpleSpatial::SimplePoint toGeodetic(double X, double Y);

private:
    double lon2merc(double lon);
    double lat2merc(double lat);
    double merc2lon(double x);
    double merc2lat(double y);

};

#endif // PROJECTION_WGS84_SPHERICALMERCATOR_H
