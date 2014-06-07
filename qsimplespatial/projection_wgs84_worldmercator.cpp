/*
* The MIT License (MIT)
*
* Copyright (c) 20014 Moukhlynin Ruslan <me@ruslan.pw>
*
* projection_wgs84_worldmercator.cpp
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

#include "projection_wgs84_worldmercator.h"

#include <QApplication>
#include <QDebug>

#define R_MAJOR 6378137.0
#define R_MINOR 6356752.3142
#define RATIO (R_MINOR/R_MAJOR)
#define ECCENT (sqrt(1.0 - (RATIO * RATIO)))
#define COM (0.5 * ECCENT)


Projection_WGS84_WorldMercator::Projection_WGS84_WorldMercator()
{
}

QSimpleSpatial::SimplePoint Projection_WGS84_WorldMercator::toCartesian(double lon, double lat)
{
    QSimpleSpatial::SimplePoint point;
    point.X = lon2merc(lon);
    point.Y = lat2merc(lat);
    return point;
}

void Projection_WGS84_WorldMercator::toCartesian(int count,double *lon,double *lat,double *z)
{
    Q_UNUSED(z)
    for(int i = 0;i < count;i ++) {
        if(lon) lon[i] = lon2merc(lon[i]);
        if(lat) lat[i] = lat2merc(lat[i]);
    }
}

double Projection_WGS84_WorldMercator::toCartesianLat(double lat)
{
    return lat2merc(lat);
}

double Projection_WGS84_WorldMercator::toCartesianLon(double lon)
{
    return lon2merc(lon);
}

QSimpleSpatial::SimplePoint Projection_WGS84_WorldMercator::toGeodetic(double X, double Y)
{
    QSimpleSpatial::SimplePoint point;
    point.X = merc2lon(X);
    point.Y = merc2lat(Y);
    return point;
}

double Projection_WGS84_WorldMercator::lon2merc (double lon) {
    return R_MAJOR * deg_rad (lon);
}

double Projection_WGS84_WorldMercator::lat2merc (double lat) {
    lat = fmin (89.5, fmax (lat, -89.5));
    double phi = deg_rad(lat);
    double sinphi = sin(phi);
    double con = ECCENT * sinphi;
    con = pow((1.0 - con) / (1.0 + con), COM);
    double ts = tan(0.5 * (M_PI * 0.5 - phi)) / con;
    return 0 - R_MAJOR * log(ts);
}

double Projection_WGS84_WorldMercator::merc2lon (double x) {
    return rad_deg(x) / R_MAJOR;
}

double Projection_WGS84_WorldMercator::merc2lat (double y) {
    double ts = exp ( -y / R_MAJOR);
    double phi = M_PI_2 - 2 * atan(ts);
    double dphi = 1.0;
    int i;
    for (i = 0; fabs(dphi) > 0.000000001 && i < 15; i++) {
        double con = ECCENT * sin (phi);
        dphi = M_PI_2 - 2 * atan (ts * pow((1.0 - con) / (1.0 + con), COM)) - phi;
        phi += dphi;
    }
    return rad_deg (phi);
}
