#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "mapglobal.h"


namespace Ui {

class MainWindow;
}

class Layer;
class MapFrame;
class Projection;
class ShapeMapReader;
class QListWidgetItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void keyPressEvent(QKeyEvent *event);
private:
    Ui::MainWindow *ui;
    MapFrame *mf;
    int newLayerCount;
    Layer *addLayer(const QString &fileName,
                    ShapeMapReader *smr,
                    Projection *proj,
                    QSimpleSpatial::ShapeTypes shapeType = QSimpleSpatial::NullShape);
    QList<QSimpleSpatial::SimplePoint> p_points;

protected slots:
    void paint(QPainter &painter);
    void mapClicked(QMouseEvent *event);
    void mapReleased(QMouseEvent *event);

private slots:
    void addPointLayer();
    void addPolylineLayer();
    void addPolygonLayer();
    void addPointTriggered(bool checked);
    void saveLayer();
    void zoom();
    void zoomIn();
    void zoomOut();
    void layerListChanged(QListWidgetItem *item);
    void layerListSelected();
    void shapeInfo();
};

#endif // MAINWINDOW_H
