# v0.6.1

* `encode.data.frame` gets `byrow` argument
* `polyline_wkt` gets `std::to_string()` around lon/lat to keep precision

# v0.6.0

* Example converting to `sfc` and `sf`
* `as.data.frame.sfencoded()` to convert back to `data.frame` class
* `decode()` - decodes encoded polylines to lat/lon

# v0.4.0

* `[.sfencoded` subset to keep encoded attributes
* `print.sfencoded` to nicely print the encoded columns