/*
* The MIT License (MIT)
*
* Copyright (c) 20014 Moukhlynin Ruslan <me@ruslan.pw>
*
* shapemapreader.h
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

#ifndef SHAPEMAPREADER_H
#define SHAPEMAPREADER_H

#include "mapreader.h"

#include "feature.h"
#include "layer.h"


typedef struct ShapeFileHeader {
    qint32 FileCode;
    qint32 Unused1;
    qint32 Unused2;
    qint32 Unused3;
    qint32 Unused4;
    qint32 Unused5;
    qint32 FileLength;
    qint32 Version;
    qint32 ShapeType;
    double Xmin;
    double Ymin;
    double Xmax;
    double Ymax;
    double Zmin;
    double Zmax;
    double Mmin;
    double Mmax;
} ShapeFileHeader;

typedef struct ShapeFileRecordHeader {
    qint32 RecordNumber;
    qint32 ContentLength;
} ShapeFileRecordHeader;

typedef struct ShapePoint {
    double X;
    double Y;
} ShapePoint;

class ShapeMapReader : public MapReader
{
    Q_OBJECT
public:
    explicit ShapeMapReader(QObject *parent = 0);
    Layer *ReadFile(QString path, Projection *projection);
    ShapeFileHeader fileHeader;
signals:
    
public slots:
    
};

#endif // SHAPEMAPREADER_H