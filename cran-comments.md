## Release Summary

* Updates v1.0 to v1.1
* Removed dependencies on undeclared packages from unit tests, as per CRAN request - email "CRAN packages maintained by you" from Kurt Hornik, 2018-05-18 (https://cran.r-project.org/web/checks/check_results_geojsonsf.html)
* Build Note - Fedora clang & gcc  : installed size is 5.5mb / 6.8mb
  - The builds says the `libs` file is 3.7mb/5.0mb. I can't reduce this file size, all the compiled c++ headers and files are required. 
* New gcc compiler warning : https://www.stats.ox.ac.uk/pub/bdr/gcc8/geojsonsf.out
  - this warning references the souce C++ library `rapidjson`. There is an issue on their github page to fix this (https://github.com/Tencent/rapidjson/issues/1205). I will update this package once rapidjson has fixed this warning. 

## Test Environments

* local OS X 15.6.0 (High Sierra) install, R 3.5.0
* travis-ci (ubuntu 14.04.5, R Under development r74781)
* win-builder (devel and release)


## R CMD check results

* ERRORS : 0 
* WARNINGS : 0
* NOTES : 0
