#ifndef SHAPEGLOBAL_H
#define SHAPEGLOBAL_H

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

#endif // SHAPEGLOBAL_H
