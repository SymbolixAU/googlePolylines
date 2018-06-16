# v0.6.1

* boost geometry objects now using geographic strategy
* `[.wkt` method
* `print.wkt` method
* `geometryRow.wkt` method
* `wkt` class
* `polyline_wkt.character` and `polyline_wkt.factor` methods
* `polyline_wkt()` uses `to_string(lon)` in lon / lat stream to keep precision

# v0.6.0

* Example converting to `sfc` and `sf`
* `as.data.frame.sfencoded()` to convert back to `data.frame` class
* `decode()` - decodes encoded polylines to lat/lon

# v0.4.0

* `[.sfencoded` subset to keep encoded attributes
* `print.sfencoded` to nicely print the encoded columns