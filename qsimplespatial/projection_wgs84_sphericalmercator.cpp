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

#include "projection_wgs84_sphericalmercator.h"

#define D_R (M_PI / 180.0)
#define R_MAJOR 6378137.0


Projection_WGS84_SphericalMercator::Projection_WGS84_SphericalMercator()
{
}

QSimpleSpatial::SimplePoint Projection_WGS84_SphericalMercator::toCartesian(double lon, double lat)
{
    QSimpleSpatial::SimplePoint point;
    point.X = lon2merc(lon);
    point.Y = lat2merc(lat);
    return point;
}

void Projection_WGS84_SphericalMercator::toCartesian(int count, double *lon, double *lat, double *z)
{
    Q_UNUSED(z)
    for(int i = 0;i < count;i ++) {
        if(lon) lon[i] = lon2merc(lon[i]);
        if(lat) lat[i] = lat2merc(lat[i]);
    }
}

double Projection_WGS84_SphericalMercator::toCartesianLat(double lat)
{
    return lat2merc(lat);
}

double Projection_WGS84_SphericalMercator::toCartesianLon(double lon)
{
    return lon2merc(lon);
}

QSimpleSpatial::SimplePoint Projection_WGS84_SphericalMercator::toGeodetic(double X, double Y)
{
    QSimpleSpatial::SimplePoint point;
    point.X = merc2lat(X);
    point.X = merc2lon(Y);
    return point;
}

double Projection_WGS84_SphericalMercator::lon2merc(double lon)
{
    return R_MAJOR * deg_rad (lon);
}

double Projection_WGS84_SphericalMercator::lat2merc(double lat)
{
    lat = fmin (89.5, fmax (lat, -89.5));
    return R_MAJOR * log(tan(M_PI / 4 + deg_rad(lat)/2 ));
}

double Projection_WGS84_SphericalMercator::merc2lon(double x)
{
    return rad_deg(x / R_MAJOR);
}

double Projection_WGS84_SphericalMercator::merc2lat(double y)
{
    return rad_deg(2 * atan(exp( (y / R_MAJOR ) )) - M_PI/2);
}
