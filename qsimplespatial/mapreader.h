#ifndef MAPREADER_H
#define MAPREADER_H

#include <QObject>
#include "mapglobal.h"
#include "layer.h"

class Projection;

class MapReader : public QObject
{
    Q_OBJECT
public:
    explicit MapReader(QObject *){}
    virtual Layer * ReadFile(QString file, Projection *projection) = 0;
signals:
    
public slots:
    
};

#endif // MAPREADER_H
