# v0.8.3

* updated s3 generic method arguments

# v0.8.2

* updated to C++14 due to Boost requirements [issue 49](https://github.com/SymbolixAU/googlePolylines/issues/49)
* removed pointless R dependency

# v0.8.1

* fixed erroneous console print

# v0.8

* chnaged licence to MIT
* fix [issue #40](https://github.com/SymbolixAU/googlePolylines/issues/40)

# v0.7.2

* [`decode()`](https://github.com/SymbolixAU/googlePolylines/pull/35) and [`encode()`](https://github.com/SymbolixAU/googlePolylines/pull/37) refactored for speed. Thanks [ChrisMuir](https://github.com/ChrisMuir)

# v0.7.1

* `sf` Z and M [dimensions correctly handled (ignored)](https://github.com/SymbolixAU/googlePolylines/issues/27)
* `tbl_df` [supported](https://github.com/SymbolixAU/googlePolylines/issues/16) in `[`


# v0.6.2

* `encode.data.frame` gets `byrow` argument
* `polyline_wkt` gets `std::to_string()` around lon/lat to keep precision

# v0.6.1

* added `sf` to suggests

# v0.6.0

* Example converting to `sfc` and `sf`
* `as.data.frame.sfencoded()` to convert back to `data.frame` class
* `decode()` - decodes encoded polylines to lat/lon

# v0.4.0

* `[.sfencoded` subset to keep encoded attributes
* `print.sfencoded` to nicely print the encoded columns