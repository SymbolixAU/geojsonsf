## Release Summary

* Updates v1.1 to v1.2
* fixes a bug in handling `Date` and `Posix` clases

* gcc compiler warning : https://www.stats.ox.ac.uk/pub/bdr/gcc8/geojsonsf.out
  - this warning references the souce C++ library `rapidjson`. There is an issue on their github page to fix this (https://github.com/Tencent/rapidjson/issues/1205). I will update this package once rapidjson has fixed this warning. 

* Build Note - Fedora clang & gcc  : installed size is 5.7mb / 6.8mb	
  - The builds says the `libs` file is 3.7mb/5.0mb. I can't reduce this file size, all the compiled c++ headers and files are required.
  

