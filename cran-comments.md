## Release Summary

* Updates v1.0 to v1.1
* Removed dependencies on undeclared packages from unit tests, as per CRAN request - email "CRAN packages maintained by you" from Kurt Hornik, 2018-05-18
* Build Note - Fedora clang & gcc  : installed size is 5.5mb / 6.8mb
  - The builds says the `libs` file is 3.7mb/5.0mb. I can't reduce this file size, all the compiled c++ headers and files are required. 

## Test Environments

* local OS X 15.6.0 (High Sierra) install, R 3.5.0
* travis-ci (ubuntu 14.04.5, R Under development r74781)
* win-builder (devel and release)


## R CMD check results

* ERRORS : 0 
* WARNINGS : 0
* NOTES : 0
