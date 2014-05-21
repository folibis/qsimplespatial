qsimplespatial
==============

`QSimpleSpatial` is very simple Qt widget for visualization of spatial data.

Currently `QSimpleSpatial` supports only `SHAPE` files from ESRI. It is assumed that the data uses WGS84 coordinate system. The data may be projected using [World Mercator projection (EPSG:3395)](http://spatialreference.org/ref/epsg/3395/) or [Spherical Mercator / Web Mercator (EPSG:3857)](http://spatialreference.org/ref/sr-org/7483/) used by Google maps. That should be enough, for most projects.

if you need to use some advanced features in your project, please refer to appropriate libraries like [QGis](https://github.com/qgis/).


#####Features:
- QSimpleSpatial can read data from ESRI shapefiles. Currently supported shapes:
  * Points
  * Polylines
  * Polygons
- QWidget as a canvas for drawing map data
- Unlimited zoom. It is possible to define minimal/maximal zoom visible level
- Unlimited layers
- Paint schemes. It is possible to define custom paint sceme for each layer or features group
- Labels. It is possible to define custom paint sceme for each label layer or features group
- and much more ...


#####TODO:
- Label title along the path
- Ability to save data to shapefiles
- Documentation
- More projection (may be through proj.4 library)
- More supported formats
- repalce QPainter with OpenGL painting system
- QML plugin
- and much more ...


