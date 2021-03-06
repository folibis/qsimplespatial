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
- QWidget as a canvas for map data painting
- Unlimited zoom. It is possible to define minimal/maximal zoom visible level for layer/features groups
- Unlimited layers
- Paint schemes. It is possible to define custom paint scheme for each layer or features group
- Labels. It is possible to define custom paint sceme for each label layer or features group
- and much more ...


#####TODO:
- Label title along the path
- Ability to save data to shapefiles
- Documentation
- More projections (may be through proj.4 library)
- More supported formats
- OpenGL painting system instead of QPainter
- QML plugin
- and much more ...

#####License:
The MIT License (MIT)

#####External resources:
- [qdbf](https://code.google.com/p/qdbf/)
- sample shapefiles from [Geofabrik](http://download.geofabrik.de/)
- spatial data exported from [OpenStreetMap](http://openstreetmap.org/)
- icons from [Iconfinder](http://iconfinder.com/)
