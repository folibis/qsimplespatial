#ifndef LAYER_H
#define LAYER_H

#include <QObject>
#include "featureset.h"
#include "feature.h"
#include "mapglobal.h"
#include "viewable.h"
#include "paintscheme.h"

class Layer : public QObject,Viewable
{
    Q_OBJECT
public:
    explicit Layer(QObject *parent = 0);
    explicit Layer(FeatureSet * set, QObject *parent = 0);
    FeatureSet * GetFeatureSet();
    void Draw(MapRenderer * renderer);
private:
    FeatureSet * set;
    PaintScheme * p_scheme;
signals:
    
public slots:
    
};

#endif // LAYER_H
