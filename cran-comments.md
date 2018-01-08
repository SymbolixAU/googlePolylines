## Test environments
* local OS X install, R 3.4.3
* ubuntu 14.04 (on travis-ci), R 3.4.3
* win-builder (devel and release)

## R CMD check results

0 errors | 0 warnings | 1 note

* This is a new release.


## CRAN change requests

* Fixed description title case
* added a link to polyline encoding algorithm in Description. However, there is no DOI, arXiv, ISBN or author(s) listed, nor any citation specifications.
* examples that require external libraries (sf, dplyr and data.table) have been wrapped in `\dontrun{}`. Those that don't require libraries have been removed from `\dontrun{}`.
* single quotes have been added around software and package names