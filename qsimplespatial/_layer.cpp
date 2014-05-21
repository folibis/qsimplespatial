#include "layer.h"


Layer::Layer(QObject *parent) :
    QObject(parent)
{
    this->set = NULL;
}

Layer::Layer(FeatureSet * set,QObject *parent) :
    QObject(parent)
{
    this->set = set;
}

FeatureSet * Layer::GetFeatureSet()
{
    return set;
}

void Layer::Draw(MapRenderer *renderer)
{
    Features * list = set->GetFeatures();
    for(int i = 0;i < list->count();i ++)
    {
        list->at(i)->Draw(renderer);
    }
}
