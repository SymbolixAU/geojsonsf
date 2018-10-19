## Release Summary

* Updates v1.1 to v1.2
* fixes a bug in handling `Date` and `Posix` clases
* fixes gcc compiler warning : https://www.stats.ox.ac.uk/pub/bdr/gcc8/geojsonsf.out 
 - fixed in `rapidjsonr` v1.1, accepted on CRAN 22nd September 2018
* various performance improvements

* Build Note - Fedora clang : installed size is 5.7mb
  - The builds says the `libs` file is 3.9mb. I can't reduce this file size, all the compiled c++ headers and files are required.
  

