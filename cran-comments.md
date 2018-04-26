
## Release summary

* Updates v0.4.0 to v0.6.0
* `as.data.frame.sfencoded` method
* `decode` function for decoding polylines
* Fixed ASAN/UBSAN errors (https://www.stats.ox.ac.uk/pub/bdr/memtests/clang-UBSAN/googlePolylines/build_vignettes.log) and (https://www.stats.ox.ac.uk/pub/bdr/memtests/gcc-UBSAN/googlePolylines/build_vignettes.log) by explicitely defining `unsigned int` value
* Ran tests, examples and vignettes with Address Sanitizers (ASAN) and Undefined Behaviour Sanitizer (UBSAN) using `rhub::check_with_sanitizers()`
* Successful ASAN/UBSAN build log: https://builder.r-hub.io/status/googlePolylines_0.6.0.tar.gz-a342c46a4b3b4ed3b7b8017536ab5dae#L1857


## Test environments

* local OS X install, R 3.4.3
* ubuntu 14.04 (on travis-ci), R 3.4.3
* win-builder (devel and release)
* `rhub::check_with_sanitizers()`

## R CMD check results

0 errors | 0 warnings | 0 notes
