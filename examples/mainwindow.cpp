#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "map.h"
#include "mapframe.h"
#include "shapemapreader.h"
#include "maprenderer.h"
#include "feature.h"
#include "paintscheme.h"
#include "paintschemepoint.h"
#include "paintschemepolygon.h"
#include "paintschemepolyline.h"
#include "labelscheme.h"
#include "projection_wgs84_sphericalmercator.h"

#include <QDebug>
#include <QPainter>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    map = new Map();

    QSimpleSpatial::Extent e(100,100,200,200);
    e.Decrease(0.5);
    e.Increase(0.5);

    MapFrame * mf = new MapFrame(this);

    QBrush bg(QPixmap(":/images/cell.png"));
    mf->setBackground(bg);
    connect(mf,SIGNAL(paint(QPainter&)),this,SLOT(paint(QPainter&)));
    ui->horizontalLayout->addWidget(mf);
    mf->SetMap(map);

    Projection_WGS84_SphericalMercator *proj = new Projection_WGS84_SphericalMercator;
    ShapeMapReader * smr = new ShapeMapReader(this);

    Layer * layer1 = smr->ReadFile("./maps/landuse.shp",proj);
    PaintSchemePolygon *scheme1 = new PaintSchemePolygon();
    layer1->AddScheme(scheme1);
    LabelScheme * labelScheme1 = new LabelScheme("name",QFont("Tahoma",9),QPen(Qt::darkGreen));
    layer1->AddLabelScheme(labelScheme1);
    map->AddLayer(layer1);

    Layer * layer2 = smr->ReadFile("./maps/places.shp",proj);
    PaintSchemePoint * scheme2 = new PaintSchemePoint(QPen(Qt::black),QBrush(Qt::red),4);
    layer2->AddScheme(scheme2);
    PaintSchemePoint * scheme21 = new PaintSchemePoint(QPixmap(":/images/star.png"));
    scheme21->SetFilterFunction([](Feature * feature) -> bool {
        QString &type = feature->GetFieldValue("type");
        if(type == "town")
            return true;
        return false;
    });
    layer2->AddScheme(scheme21);
    LabelScheme * labelScheme2 = new LabelScheme("name",QFont("Tahoma",9),QPen(Qt::darkBlue));
    QSimpleSpatial::SimplePoint offset;
    offset.X = 0;
    offset.Y = 20;
    labelScheme2->setLabelOffset(offset);
    layer2->AddLabelScheme(labelScheme2);
    map->AddLayer(layer2);

    Layer * layer3 = smr->ReadFile("./maps/natural.shp",proj);
    PaintSchemePolygon *scheme3 = new PaintSchemePolygon();
    layer3->AddScheme(scheme3);
    LabelScheme * labelScheme3 = new LabelScheme("name",QFont("Tahoma",9),QPen(Qt::red));
    layer3->AddLabelScheme(labelScheme3);
    map->AddLayer(layer3);

    Layer * layer4 = smr->ReadFile("./maps/waterways.shp",proj);
    PaintSchemePolyline *scheme4 = new PaintSchemePolyline(QPen(Qt::blue));
    layer4->AddScheme(scheme4);
    LabelScheme * labelScheme4 = new LabelScheme("name",QFont("Tahoma",9),QPen(Qt::magenta));
    layer4->AddLabelScheme(labelScheme4);
    map->AddLayer(layer4);

    Layer * layer5 = smr->ReadFile("./maps/roads.shp",proj);
    layer5->SetMaxZoomFilter([](Feature * feature) -> double {
        QString &type = feature->GetFieldValue("type");
        if(type == "primary") return 1;
        return 0.05;
    });
    QPen pen5(qRgb(210,210,250));
    pen5.setWidth(4);
    PaintSchemePolyline *scheme5 = new PaintSchemePolyline(pen5);
    layer5->AddScheme(scheme5);
    QPen pen51(qRgb(255,128,0));
    pen51.setWidth(5);
    PaintSchemePolyline *scheme51 = new PaintSchemePolyline(pen51);
    scheme51->SetFilterFunction([](Feature * feature) -> bool {
        QString &type = feature->GetFieldValue("type");
        if(type == "primary") return true;
        return false;
    });
    layer5->AddScheme(scheme51);
    LabelScheme * labelScheme5 = new LabelScheme("name",QFont("Tahoma",9),QPen(qRgb(250,128,20)));
    layer5->AddLabelScheme(labelScheme5);
    LabelScheme * labelScheme51 = new LabelScheme("name");
    labelScheme51->SetFilterFunction([](Feature * feature) -> bool {
        QString &type = feature->GetFieldValue("type");
        if(type == "primary") return true;
        return false;
    });
    labelScheme51->setPaintFunction([](MapRenderer *renderer, Feature *feature, LabelScheme *lscheme) -> bool {

        QString name = feature->GetFieldValue(lscheme->getFieldName());
        QSimpleSpatial::SimplePoint center = feature->getLabelPosition(QSimpleSpatial::Centroid);
        QSimpleSpatial::SimplePoint point = renderer->Coord2Pixel(center);
        QRect rect = renderer->painter->fontMetrics().boundingRect(name);
        rect.moveTo(point.X - rect.width() / 2 + lscheme->getLabelOffset().X,
                    point.Y - rect.height() / 2 + lscheme->getLabelOffset().Y);

        if(!renderer->labels.intersects(rect))
        {
            renderer->painter->setBrush(QColor(qRgb(250,128,0)));
            renderer->painter->setPen(Qt::white);
            renderer->painter->setFont(QFont("Tahoma",6));
            renderer->painter->drawRoundedRect(rect,5,5);
            renderer->painter->drawText(rect, Qt::AlignCenter, name);
            renderer->labels = renderer->labels.united(rect);
        }
        return true;
    });
    layer5->AddLabelScheme(labelScheme51);
    map->AddLayer(layer5);

    Layer * layer6 = smr->ReadFile("./maps/railways.shp",proj);
    layer6->setMaxZoom(0.05);
    QPen pen6(qRgb(60,60,60));
    pen6.setWidth(3);
    PaintSchemePolyline *scheme6 = new PaintSchemePolyline(pen6);
    layer6->AddScheme(scheme6);
    LabelScheme * labelScheme6 = new LabelScheme("name",QFont("Tahoma",9),QPen(qRgb(150,158,150)));
    layer6->AddLabelScheme(labelScheme6);
    map->AddLayer(layer6);

    Layer * layer7 = smr->ReadFile("./maps/buildings.shp",proj);
    layer7->setMaxZoom(0.01);
    PaintSchemePolygon *scheme7 = new PaintSchemePolygon(QPen(qRgb(200,200,200)), QBrush(qRgb(240,180,200)));
    layer7->AddScheme(scheme7);
    LabelScheme * labelScheme7 = new LabelScheme("name",QFont("Tahoma",8),QPen(Qt::gray));
    layer7->AddLabelScheme(labelScheme7);
    map->AddLayer(layer7);

    Layer * layer8 = smr->ReadFile("./maps/points.shp",proj);
    layer8->setMaxZoom(0.01);
    PaintSchemePoint * scheme8 = new PaintSchemePoint(QPen(Qt::black),QBrush(Qt::yellow),4);
    layer8->AddScheme(scheme8);
    LabelScheme * labelScheme8 = new LabelScheme("name",QFont("Tahoma",8),QPen(Qt::darkGray));
    QSimpleSpatial::SimplePoint offset8;
    offset8.X = 0;
    offset8.Y = 20;
    labelScheme8->setLabelOffset(offset8);
    layer8->AddLabelScheme(labelScheme8);
    map->AddLayer(layer8);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paint(QPainter &painter)
{
    MapFrame * mf = dynamic_cast<MapFrame *>(sender());
    painter.setPen(Qt::black);
    double X = mf->width() - 110;
    double Y = mf->height() - 50;
    painter.drawLine(X,Y,X + 100,Y);
    painter.drawLine(X + 50,Y,X + 50,Y + 10);
    for(double xx = X;xx <= X + 100;xx += 10)
    {
        painter.drawLine(xx,Y,xx,Y - 5);
    }
    double factor = 1.0 / map->GetRenderer()->getScaleFactor();
    factor /= 10.0;
    QString postfix;
    if(factor < 2.0)
    {
        postfix = "m.";
        factor *= 1000.0;
    }
    else
    {
        postfix = "km.";
    }
    painter.drawText(QRectF(X,Y - 30,100,25),
                     Qt::AlignCenter,
                     QString("%1 %2").arg(QString::number(factor,'f',2)).arg(postfix));
    double zoom = map->GetRenderer()->getZoom();
    painter.drawText(QRectF(X,Y + 5,50,25),
                     Qt::AlignLeft,
                     QString::number(zoom,'f',5));

}
