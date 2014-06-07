#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mapframe.h"
#include "shapemapreader.h"
#include "maptranslator.h"
#include "feature.h"
#include "pointfeature.h"
#include "polylinefeature.h"
#include "polygonfeature.h"
#include "layer.h"
#include "paintschemepoint.h"
#include "paintschemepolygon.h"
#include "paintschemepolyline.h"
#include "labelscheme.h"
#include "projection_wgs84_sphericalmercator.h"

#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QMenu>
#include <QListWidgetItem>
#include <QFile>
#include <QMessageBox>

class LayerListItem : public QListWidgetItem
{
public:
    LayerListItem(QListWidget *parent = 0) :
        QListWidgetItem(parent),
        p_layer(NULL)
    {}
    Layer *getLayer()
    {
        return p_layer;
    }

    void setLayer(Layer *layer)
    {
        p_layer = layer;
    }

protected:
    Layer *p_layer;
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    newLayerCount(1)
{
    ui->setupUi(this);

    mf = new MapFrame(ui->mapFrame);
    QBrush bg(QPixmap(":/images/cell.png"));
    mf->setBackground(bg);
    connect(mf,SIGNAL(paint(QPainter&)),this,SLOT(paint(QPainter&)));
    connect(mf,SIGNAL(clicked(QMouseEvent*)),this,SLOT(mapClicked(QMouseEvent*)));
    connect(mf,SIGNAL(released(QMouseEvent*)),this,SLOT(mapReleased(QMouseEvent*)));

    ui->verticalLayoutMap->addWidget(mf);

    Projection_WGS84_SphericalMercator *proj = new Projection_WGS84_SphericalMercator;
    mf->setProjection(proj);
    ShapeMapReader * smr = new ShapeMapReader(this);

    Layer *layer1 = addLayer("./maps/landuse.shp",smr,proj);
    layer1->setName("Landuse");
    PaintSchemePolygon *scheme1 = new PaintSchemePolygon();
    layer1->AddScheme(scheme1);
    LabelScheme * labelScheme1 = new LabelScheme("name",QFont("Tahoma",9),QPen(Qt::darkGreen));
    layer1->AddLabelScheme(labelScheme1);
    mf->AddLayer(layer1);
    QListWidgetItem item1;
    item1.setIcon(QIcon(":/images/polygon.png"));



    Layer * layer2 = addLayer("./maps/places.shp",smr,proj);
    layer2->setName("Places");
    PaintSchemePoint *scheme2 = new PaintSchemePoint(QPen(Qt::black),QBrush(Qt::red),4);
    layer2->AddScheme(scheme2);
    PaintSchemePoint *scheme21 = new PaintSchemePoint(QPixmap(":/images/star.png"));
    scheme21->SetFilterFunction([](Feature * feature) -> bool {
        QString &type = feature->GetFieldValue("type");
        if(type == "town")
            return true;
        return false;
    });
    layer2->AddScheme(scheme21);
    LabelScheme *labelScheme2 = new LabelScheme("name",QFont("Tahoma",9),QPen(Qt::darkBlue));
    QSimpleSpatial::SimplePoint offset;
    offset.X = 0;
    offset.Y = 20;
    labelScheme2->setLabelOffset(offset);
    layer2->AddLabelScheme(labelScheme2);
    mf->AddLayer(layer2);

    Layer *layer3 = addLayer("./maps/natural.shp",smr,proj);
    layer3->setName("Natural");
    PaintSchemePolygon *scheme3 = new PaintSchemePolygon();
    layer3->AddScheme(scheme3);
    LabelScheme *labelScheme3 = new LabelScheme("name",QFont("Tahoma",9),QPen(Qt::red));
    layer3->AddLabelScheme(labelScheme3);
    mf->AddLayer(layer3);

    Layer *layer4 = addLayer("./maps/waterways.shp",smr,proj);
    layer4->setName("Waterways");
    PaintSchemePolyline *scheme4 = new PaintSchemePolyline(QPen(Qt::blue));
    layer4->AddScheme(scheme4);
    LabelScheme *labelScheme4 = new LabelScheme("name",QFont("Tahoma",9),QPen(Qt::magenta));
    layer4->AddLabelScheme(labelScheme4);
    mf->AddLayer(layer4);

    Layer *layer5 = addLayer("./maps/roads.shp",smr,proj);
    layer5->setName("Roads");
    layer5->SetMaxZoomFilter([](Feature *feature) -> double {
        QString &type = feature->GetFieldValue("type");
        if(type == "primary") return 1;
        return 0.05;
    });
    QPen pen5(qRgb(210,210,250));
    pen5.setWidth(8);
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
    LabelScheme *labelScheme5 = new LabelScheme("name",QFont("Tahoma",6),QPen(qRgb(110,110,110)));
    labelScheme5->setPosition(QSimpleSpatial::FollowPath);
    offset.X = 0;
    offset.Y = 3;
    labelScheme5->setLabelOffset(offset);
    layer5->AddLabelScheme(labelScheme5);
    LabelScheme *labelScheme51 = new LabelScheme("name");
    labelScheme51->setPosition(QSimpleSpatial::FollowPath);
    labelScheme51->SetFilterFunction([](Feature *feature) -> bool {
        QString &type = feature->GetFieldValue("type");
        if(type == "primary") return true;
        return false;
    });
    labelScheme51->setPaintFunction([](QPainter *painter, MapTranslator *renderer, Feature *feature, LabelScheme *lscheme) -> bool {

        QString name = feature->GetFieldValue(lscheme->getFieldName());
        QSimpleSpatial::SimplePoint center = feature->getLabelPosition(QSimpleSpatial::Centroid);
        QSimpleSpatial::SimplePoint point = renderer->Coord2Screen(center);
        QRect rect = painter->fontMetrics().boundingRect(name);
        rect.moveTo(point.X - rect.width() / 2 + lscheme->getLabelOffset().X,
                    point.Y - rect.height() / 2 + lscheme->getLabelOffset().Y);

        if(!renderer->isLabelIntersects(rect))
        {
            painter->setBrush(QColor(qRgb(250,128,0)));
            painter->setPen(Qt::white);
            painter->setFont(QFont("Tahoma",6));
            painter->drawRoundedRect(rect,5,5);
            painter->drawText(rect, Qt::AlignCenter, name);
            renderer->addLabelRect(rect);
        }
        return true;
    });
    layer5->AddLabelScheme(labelScheme51);
    mf->AddLayer(layer5);

    Layer *layer6 = addLayer("./maps/railways.shp",smr,proj);
    layer6->setName("Railways");
    layer6->setMaxZoom(0.05);
    QPen pen6(qRgb(60,60,60));
    pen6.setWidth(3);
    PaintSchemePolyline *scheme6 = new PaintSchemePolyline(pen6);
    layer6->AddScheme(scheme6);
    LabelScheme *labelScheme6 = new LabelScheme("name",QFont("Tahoma",9),QPen(qRgb(150,158,150)));
    layer6->AddLabelScheme(labelScheme6);
    mf->AddLayer(layer6);

    Layer *layer7 = addLayer("./maps/buildings.shp",smr,proj);
    layer7->setMaxZoom(0.01);
    PaintSchemePolygon *scheme7 = new PaintSchemePolygon(QPen(qRgb(200,200,200)), QBrush(qRgb(240,180,200)));
    layer7->AddScheme(scheme7);
    LabelScheme *labelScheme7 = new LabelScheme("name",QFont("Tahoma",8),QPen(Qt::gray));
    layer7->AddLabelScheme(labelScheme7);
    mf->AddLayer(layer7);

    Layer *layer8 = addLayer("./maps/points.shp",smr,proj);
    layer8->setName("Points");
    layer8->setMaxZoom(0.01);
    PaintSchemePoint * scheme8 = new PaintSchemePoint(QPen(Qt::black),QBrush(Qt::yellow),4);
    layer8->AddScheme(scheme8);
    LabelScheme *labelScheme8 = new LabelScheme("name",QFont("Tahoma",8),QPen(Qt::darkGray));
    QSimpleSpatial::SimplePoint offset8;
    offset8.X = 0;
    offset8.Y = 20;
    labelScheme8->setLabelOffset(offset8);
    layer8->AddLabelScheme(labelScheme8);
    mf->AddLayer(layer8);

    QMenu *addLayerMenu = new QMenu(ui->toolBar);
    QAction *pointLayer = new QAction("Point layer",addLayerMenu);
    QAction *polylineLayer = new QAction("Polyline layer",addLayerMenu);
    QAction *polygonLayer = new QAction("Polygon layer",addLayerMenu);
    addLayerMenu->addAction(pointLayer);
    addLayerMenu->addAction(polylineLayer);
    addLayerMenu->addAction(polygonLayer);
    ui->actionAddLayer->setMenu(addLayerMenu);
    connect(pointLayer,SIGNAL(triggered()),this,SLOT(addPointLayer()));
    connect(polylineLayer,SIGNAL(triggered()),this,SLOT(addPolylineLayer()));
    connect(polygonLayer,SIGNAL(triggered()),this,SLOT(addPolygonLayer()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return && (mf->getState() & MapFrame::MapStateEdit)) {
        LayerListItem *item = static_cast<LayerListItem *>(ui->layerList->currentItem());
        QSimpleSpatial::ShapeTypes type =  item->getLayer()->GetShapeType();
        {
            if(type == QSimpleSpatial::PolyLine ||type == QSimpleSpatial::Polygon) {
                Points *points = new Points;
                points->count = p_points.count();
                points->x = new double[points->count];
                points->y = new double[points->count];
                for(int i = 0;i < p_points.count(); i ++) {
                    QSimpleSpatial::SimplePoint &point = p_points[i];
                    point = mf->GetTranslator()->Screen2Coord(point);
                    points->x[i] = point.X;
                    points->y[i] = point.Y;
                }
                p_points.clear();

                if(type == QSimpleSpatial::PolyLine) {
                    PolylineFeature *feature = new PolylineFeature(item->getLayer());
                    feature->AddField("name","Test line");
                    feature->AddPoints(points);
                    item->getLayer()->AddFeature(feature);
                } else {
                    PolygonFeature *feature = new PolygonFeature(item->getLayer());
                    feature->AddField("name","Test polygon");
                    feature->AddPoints(points);
                    item->getLayer()->AddFeature(feature);
                }
            }
        }
        mf->setDirty();
        mf->setState(MapFrame::MapStateMove);
        ui->actionAddPoint->setChecked(false);
        mf->update();
    }
}

Layer *MainWindow::addLayer(const QString &fileName, ShapeMapReader *smr, Projection *proj,QSimpleSpatial::ShapeTypes shapeType)
{
    Layer *layer;
    if(QFile::exists(fileName))
        layer = smr->ReadFile(fileName,proj);
    else {
        layer = new Layer(shapeType,this);
        layer->setName(fileName);
    }
    QIcon icon;
    switch(layer->GetShapeType())
    {
        case QSimpleSpatial::Point:
            icon.addPixmap(QPixmap(":/images/point.png"));
            break;
        case QSimpleSpatial::PolyLine:
            icon.addPixmap(QPixmap(":/images/polyline.png"));
            break;
        case QSimpleSpatial::Polygon:
            icon.addPixmap(QPixmap(":/images/polygon.png"));
            break;
        default:
            break;
    }
    LayerListItem *item = new LayerListItem(ui->layerList);
    item->setCheckState(Qt::Checked);
    item->setIcon(icon);
    item->setText(fileName);
    item->setLayer(layer);
    ui->layerList->addItem(item);
    return layer;
}

void MainWindow::paint(QPainter &painter)
{
    MapFrame *mf = dynamic_cast<MapFrame *>(sender());
    painter.setPen(Qt::black);
    double X = mf->width() - 110;
    double Y = mf->height() - 50;
    painter.drawLine(X,Y,X + 100,Y);
    painter.drawLine(X + 50,Y,X + 50,Y + 10);
    for(double xx = X;xx <= X + 100;xx += 10)
    {
        painter.drawLine(xx,Y,xx,Y - 5);
    }
    double factor = 1.0 / mf->GetTranslator()->getScaleFactor();
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
    double zoom = mf->GetTranslator()->getZoom();
    painter.drawText(QRectF(X,Y + 5,50,25),
                     Qt::AlignLeft,
                     QString::number(zoom,'f',5));

    if(p_points.count() > 0) {
        painter.setPen(Qt::blue);
        for(int i = 1;i < p_points.count();i ++) {
            painter.drawLine(p_points[i - 1].X,p_points[i - 1].Y,p_points[i].X,p_points[i].Y);
        }
        painter.setPen(Qt::green);
        for(int i = 0;i < p_points.count();i ++) {
            painter.drawEllipse(p_points[i].X - 5,p_points[i].Y - 5,10,10);
        }
    }

}

void MainWindow::mapClicked(QMouseEvent *event)
{
    if(ui->actionShapeInfo->isChecked()) {
        QPoint clickPoint = event->pos();
        QSimpleSpatial::SimplePoint mapPointTopLeft = mf->GetTranslator()->Screen2Coord(clickPoint.x() - 10, clickPoint.y() - 10);
        QSimpleSpatial::SimplePoint mapPointBottomRight = mf->GetTranslator()->Screen2Coord(clickPoint.x() + 10, clickPoint.y() + 10);
        QSimpleSpatial::Extent extent(mapPointTopLeft,mapPointBottomRight);
        QString output;
        foreach(Layer *layer, mf->GetLayers()) {
            if(layer->isVisible()) {
                foreach(Feature *feature, layer->getFeatures()) {
                    if(extent.IsIntersect(feature->GetExtent())) {
                        DataFields data = feature->GetDataFields();
                        QMapIterator<QString, QString> i(data);
                        output += QString("%1\n==============\n").arg(layer->getName());
                        while (i.hasNext()) {
                            i.next();
                            output +=  QString("%1:%2; ").arg(i.key()).arg(i.value());
                        }
                        output += QString("\n------------------\n");
                    }
                }
            }
        }
        QMessageBox::information(this,"Found shapes",output);
    }
}

void MainWindow::mapReleased(QMouseEvent *event)
{
    Q_UNUSED(event)
    if(mf->getState() & MapFrame::MapStateEdit)
    {
        LayerListItem *item = static_cast<LayerListItem *>(ui->layerList->currentItem());
        if(item && item->getLayer()) {
            double x = event->x();
            double y = event->y();
            QSimpleSpatial::SimplePoint point;
            switch(item->getLayer()->GetShapeType())
            {
                case QSimpleSpatial::Point:
                {
                    PointFeature *feature = new PointFeature(item->getLayer(),mf->GetTranslator()->Screen2Coord(x,y));
                    feature->AddField("name","Test point");
                    item->getLayer()->AddFeature(feature);
                }
                    break;
                case QSimpleSpatial::PolyLine:
                case QSimpleSpatial::Polygon:
                    point.X = x;
                    point.Y = y;
                    p_points.append(point);
                    mf->update();
                    break;
                default:
                    break;
            }
            if(item->getLayer()->GetShapeType() == QSimpleSpatial::Point) {
                ui->actionAddPoint->setChecked(false);
                mf->setState(MapFrame::MapStateMove);
            }
            mf->update();
        }
    }
}

void MainWindow::addPointLayer()
{
    Layer *layer = addLayer("New point layer " + QString::number(newLayerCount++),
                            NULL,
                            mf->getProjection(),
                            QSimpleSpatial::Point);
    PaintSchemePoint *schemeCustom = new PaintSchemePoint(QPen(Qt::green),QBrush(Qt::yellow),10);
    layer->AddScheme(schemeCustom);
    mf->AddLayer(layer);

}

void MainWindow::addPolylineLayer()
{
    Layer *layer = addLayer("New polyline layer " + QString::number(newLayerCount++),
                            NULL,
                            mf->getProjection(),
                            QSimpleSpatial::PolyLine);
    PaintSchemePolyline *schemeCustom = new PaintSchemePolyline(QPen(Qt::green),QBrush(Qt::yellow),6);
    layer->AddScheme(schemeCustom);
    mf->AddLayer(layer);
}

void MainWindow::addPolygonLayer()
{
    Layer *layer = addLayer("New polygon layer " + QString::number(newLayerCount++),
                            NULL,
                            mf->getProjection(),
                            QSimpleSpatial::Polygon);

    PaintSchemePolygon *schemeCustom = new PaintSchemePolygon(QPen(Qt::green),QBrush(Qt::yellow));
    layer->AddScheme(schemeCustom);
    mf->AddLayer(layer);
}

void MainWindow::addPointTriggered(bool checked)
{
    if(checked)
        mf->setState(MapFrame::MapStateEdit);
    else
        mf->setState(MapFrame::MapStateMove);
}

void MainWindow::saveLayer()
{

}

void MainWindow::zoom()
{
    mf->GetTranslator()->ZoomTo(1.0);
    mf->updateMap();
}

void MainWindow::zoomIn()
{
    mf->GetTranslator()->ZoomIn();
    mf->updateMap();
}

void MainWindow::zoomOut()
{
    mf->GetTranslator()->ZoomOut();
    mf->updateMap();
}

void MainWindow::layerListChanged(QListWidgetItem *item)
{
    LayerListItem *listItem = static_cast<LayerListItem *>(item);
    if(listItem) {
        if(listItem->checkState() == Qt::Unchecked && listItem->getLayer() && listItem->getLayer()->isVisible()) {
            listItem->getLayer()->setVisible(false);
            mf->updateMap();
        }
        else if(listItem->checkState() == Qt::Checked && listItem->getLayer() && !listItem->getLayer()->isVisible()) {
            listItem->getLayer()->setVisible(true);
            mf->updateMap();
        }
    }
}

void MainWindow::layerListSelected()
{
    if(ui->layerList->currentItem())
    {
        ui->actionAddPoint->setEnabled(true);
    }
}

void MainWindow::shapeInfo()
{
    if(!ui->actionShapeInfo->isChecked()) {
        mf->setState(MapFrame::MapStateMove);
        mf->setCursor(Qt::ArrowCursor);
    } else {
        mf->setState(MapFrame::MapStateFixed);
        mf->setCursor(Qt::WhatsThisCursor);
    }
}
