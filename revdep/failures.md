# mapdeck

<details>

* Version: 0.2.1
* Source code: https://github.com/cran/mapdeck
* URL: https://symbolixau.github.io/mapdeck/articles/mapdeck.html
* BugReports: https://github.com/SymbolixAU/mapdeck/issues
* Date/Publication: 2019-01-22 09:20:03 UTC
* Number of recursive dependencies: 69

Run `revdep_details(,"mapdeck")` for more info

</details>

## Newly broken

*   checking whether package ‘mapdeck’ can be installed ... ERROR
    ```
    Installation failed.
    See ‘/Users/dave/Documents/github/geojsonsf/revdep/checks.noindex/mapdeck/new/mapdeck.Rcheck/00install.out’ for details.
    ```

## Newly fixed

*   checking installed package size ... NOTE
    ```
      installed size is  7.1Mb
      sub-directories of 1Mb or more:
        doc           1.2Mb
        htmlwidgets   1.4Mb
        libs          3.2Mb
    ```

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘htmltools’
      All declared Imports should be used.
    ```

## Installation

### Devel

```
* installing *source* package ‘mapdeck’ ...
** package ‘mapdeck’ successfully unpacked and MD5 sums checked
** using staged installation
** libs
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/new/geojsonsf/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/jsonify/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/rapidjsonr/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/Rcpp/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/spatialwidget/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include -fPIC  -Wall -g -O2  -c RcppExports.cpp -o RcppExports.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/new/geojsonsf/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/jsonify/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/rapidjsonr/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/Rcpp/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/spatialwidget/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include -fPIC  -Wall -g -O2  -c arc.cpp -o arc.o
In file included from arc.cpp:5:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/spatialwidget/include/spatialwidget/spatialwidget.hpp:7:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include/colourvalues/colours/colours_hex.hpp:5:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include/colourvalues/colours.hpp:10:
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/math/interpolators/cubic_b_spline.hpp:28:1: warning: This header is deprecated. Use <boost/math/interpolators/cardinal_cubic_b_spline.hpp> instead. [-W#pragma-messages]
BOOST_HEADER_DEPRECATED("<boost/math/interpolators/cardinal_cubic_b_spline.hpp>");
^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/config/header_deprecated.hpp:23:37: note: expanded from macro 'BOOST_HEADER_DEPRECATED'
# define BOOST_HEADER_DEPRECATED(a) BOOST_PRAGMA_MESSAGE("This header is deprecated. Use " a " instead.")
                                    ^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/config/pragma_message.hpp:24:34: note: expanded from macro 'BOOST_PRAGMA_MESSAGE'
# define BOOST_PRAGMA_MESSAGE(x) _Pragma(BOOST_STRINGIZE(message(x)))
                                 ^
<scratch space>:14:2: note: expanded from here
 message("This header is deprecated. Use " "<boost/math/interpolators/cardinal_cubic_b_spline.hpp>" " instead.")
 ^
In file included from arc.cpp:5:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/spatialwidget/include/spatialwidget/spatialwidget.hpp:14:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/spatialwidget/include/spatialwidget/geojson/geojson.hpp:8:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/new/geojsonsf/include/geojsonsf/write_geojson.hpp:6:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/new/geojsonsf/include/geojsonsf/geojson/writers/write_geojson.hpp:6:
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/new/geojsonsf/include/geojsonsf/geometrycollection/geometrycollection.hpp:6:10: fatal error: 'sfheaders/utils/utils.hpp' file not found
#include "sfheaders/utils/utils.hpp"
         ^~~~~~~~~~~~~~~~~~~~~~~~~~~
1 warning and 1 error generated.
make: *** [arc.o] Error 1
ERROR: compilation failed for package ‘mapdeck’
* removing ‘/Users/dave/Documents/github/geojsonsf/revdep/checks.noindex/mapdeck/new/mapdeck.Rcheck/mapdeck’

```
### CRAN

```
* installing *source* package ‘mapdeck’ ...
** package ‘mapdeck’ successfully unpacked and MD5 sums checked
** using staged installation
** libs
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/old/geojsonsf/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/jsonify/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/rapidjsonr/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/Rcpp/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/spatialwidget/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include -fPIC  -Wall -g -O2  -c RcppExports.cpp -o RcppExports.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/old/geojsonsf/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/jsonify/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/rapidjsonr/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/Rcpp/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/spatialwidget/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include -fPIC  -Wall -g -O2  -c arc.cpp -o arc.o
In file included from arc.cpp:5:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/spatialwidget/include/spatialwidget/spatialwidget.hpp:7:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include/colourvalues/colours/colours_hex.hpp:5:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include/colourvalues/colours.hpp:10:
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/math/interpolators/cubic_b_spline.hpp:28:1: warning: This header is deprecated. Use <boost/math/interpolators/cardinal_cubic_b_spline.hpp> instead. [-W#pragma-messages]
BOOST_HEADER_DEPRECATED("<boost/math/interpolators/cardinal_cubic_b_spline.hpp>");
^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/config/header_deprecated.hpp:23:37: note: expanded from macro 'BOOST_HEADER_DEPRECATED'
# define BOOST_HEADER_DEPRECATED(a) BOOST_PRAGMA_MESSAGE("This header is deprecated. Use " a " instead.")
                                    ^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/config/pragma_message.hpp:24:34: note: expanded from macro 'BOOST_PRAGMA_MESSAGE'
# define BOOST_PRAGMA_MESSAGE(x) _Pragma(BOOST_STRINGIZE(message(x)))
                                 ^
<scratch space>:14:2: note: expanded from here
 message("This header is deprecated. Use " "<boost/math/interpolators/cardinal_cubic_b_spline.hpp>" " instead.")
 ^
1 warning generated.
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/old/geojsonsf/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/jsonify/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/rapidjsonr/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/Rcpp/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/spatialwidget/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include -fPIC  -Wall -g -O2  -c geojson.cpp -o geojson.o
In file included from geojson.cpp:5:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/spatialwidget/include/spatialwidget/spatialwidget.hpp:7:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include/colourvalues/colours/colours_hex.hpp:5:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include/colourvalues/colours.hpp:10:
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/math/interpolators/cubic_b_spline.hpp:28:1: warning: This header is deprecated. Use <boost/math/interpolators/cardinal_cubic_b_spline.hpp> instead. [-W#pragma-messages]
BOOST_HEADER_DEPRECATED("<boost/math/interpolators/cardinal_cubic_b_spline.hpp>");
^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/config/header_deprecated.hpp:23:37: note: expanded from macro 'BOOST_HEADER_DEPRECATED'
# define BOOST_HEADER_DEPRECATED(a) BOOST_PRAGMA_MESSAGE("This header is deprecated. Use " a " instead.")
                                    ^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/config/pragma_message.hpp:24:34: note: expanded from macro 'BOOST_PRAGMA_MESSAGE'
# define BOOST_PRAGMA_MESSAGE(x) _Pragma(BOOST_STRINGIZE(message(x)))
                                 ^
<scratch space>:14:2: note: expanded from here
 message("This header is deprecated. Use " "<boost/math/interpolators/cardinal_cubic_b_spline.hpp>" " instead.")
 ^
1 warning generated.
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/old/geojsonsf/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/jsonify/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/rapidjsonr/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/Rcpp/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/spatialwidget/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include -fPIC  -Wall -g -O2  -c grid.cpp -o grid.o
In file included from grid.cpp:5:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/spatialwidget/include/spatialwidget/spatialwidget.hpp:7:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include/colourvalues/colours/colours_hex.hpp:5:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include/colourvalues/colours.hpp:10:
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/math/interpolators/cubic_b_spline.hpp:28:1: warning: This header is deprecated. Use <boost/math/interpolators/cardinal_cubic_b_spline.hpp> instead. [-W#pragma-messages]
BOOST_HEADER_DEPRECATED("<boost/math/interpolators/cardinal_cubic_b_spline.hpp>");
^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/config/header_deprecated.hpp:23:37: note: expanded from macro 'BOOST_HEADER_DEPRECATED'
# define BOOST_HEADER_DEPRECATED(a) BOOST_PRAGMA_MESSAGE("This header is deprecated. Use " a " instead.")
                                    ^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/config/pragma_message.hpp:24:34: note: expanded from macro 'BOOST_PRAGMA_MESSAGE'
# define BOOST_PRAGMA_MESSAGE(x) _Pragma(BOOST_STRINGIZE(message(x)))
                                 ^
<scratch space>:14:2: note: expanded from here
 message("This header is deprecated. Use " "<boost/math/interpolators/cardinal_cubic_b_spline.hpp>" " instead.")
 ^
1 warning generated.
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/old/geojsonsf/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/jsonify/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/rapidjsonr/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/Rcpp/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/spatialwidget/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include -fPIC  -Wall -g -O2  -c hexagon.cpp -o hexagon.o
In file included from hexagon.cpp:5:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/spatialwidget/include/spatialwidget/spatialwidget.hpp:7:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include/colourvalues/colours/colours_hex.hpp:5:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include/colourvalues/colours.hpp:10:
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/math/interpolators/cubic_b_spline.hpp:28:1: warning: This header is deprecated. Use <boost/math/interpolators/cardinal_cubic_b_spline.hpp> instead. [-W#pragma-messages]
BOOST_HEADER_DEPRECATED("<boost/math/interpolators/cardinal_cubic_b_spline.hpp>");
^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/config/header_deprecated.hpp:23:37: note: expanded from macro 'BOOST_HEADER_DEPRECATED'
# define BOOST_HEADER_DEPRECATED(a) BOOST_PRAGMA_MESSAGE("This header is deprecated. Use " a " instead.")
                                    ^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/config/pragma_message.hpp:24:34: note: expanded from macro 'BOOST_PRAGMA_MESSAGE'
# define BOOST_PRAGMA_MESSAGE(x) _Pragma(BOOST_STRINGIZE(message(x)))
                                 ^
<scratch space>:14:2: note: expanded from here
 message("This header is deprecated. Use " "<boost/math/interpolators/cardinal_cubic_b_spline.hpp>" " instead.")
 ^
1 warning generated.
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/old/geojsonsf/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/jsonify/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/rapidjsonr/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/Rcpp/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/spatialwidget/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include -fPIC  -Wall -g -O2  -c line.cpp -o line.o
In file included from line.cpp:5:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/spatialwidget/include/spatialwidget/spatialwidget.hpp:7:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include/colourvalues/colours/colours_hex.hpp:5:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include/colourvalues/colours.hpp:10:
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/math/interpolators/cubic_b_spline.hpp:28:1: warning: This header is deprecated. Use <boost/math/interpolators/cardinal_cubic_b_spline.hpp> instead. [-W#pragma-messages]
BOOST_HEADER_DEPRECATED("<boost/math/interpolators/cardinal_cubic_b_spline.hpp>");
^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/config/header_deprecated.hpp:23:37: note: expanded from macro 'BOOST_HEADER_DEPRECATED'
# define BOOST_HEADER_DEPRECATED(a) BOOST_PRAGMA_MESSAGE("This header is deprecated. Use " a " instead.")
                                    ^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/config/pragma_message.hpp:24:34: note: expanded from macro 'BOOST_PRAGMA_MESSAGE'
# define BOOST_PRAGMA_MESSAGE(x) _Pragma(BOOST_STRINGIZE(message(x)))
                                 ^
<scratch space>:14:2: note: expanded from here
 message("This header is deprecated. Use " "<boost/math/interpolators/cardinal_cubic_b_spline.hpp>" " instead.")
 ^
1 warning generated.
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/old/geojsonsf/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/jsonify/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/rapidjsonr/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/Rcpp/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/spatialwidget/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include -fPIC  -Wall -g -O2  -c path.cpp -o path.o
In file included from path.cpp:5:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/spatialwidget/include/spatialwidget/spatialwidget.hpp:7:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include/colourvalues/colours/colours_hex.hpp:5:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include/colourvalues/colours.hpp:10:
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/math/interpolators/cubic_b_spline.hpp:28:1: warning: This header is deprecated. Use <boost/math/interpolators/cardinal_cubic_b_spline.hpp> instead. [-W#pragma-messages]
BOOST_HEADER_DEPRECATED("<boost/math/interpolators/cardinal_cubic_b_spline.hpp>");
^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/config/header_deprecated.hpp:23:37: note: expanded from macro 'BOOST_HEADER_DEPRECATED'
# define BOOST_HEADER_DEPRECATED(a) BOOST_PRAGMA_MESSAGE("This header is deprecated. Use " a " instead.")
                                    ^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/config/pragma_message.hpp:24:34: note: expanded from macro 'BOOST_PRAGMA_MESSAGE'
# define BOOST_PRAGMA_MESSAGE(x) _Pragma(BOOST_STRINGIZE(message(x)))
                                 ^
<scratch space>:14:2: note: expanded from here
 message("This header is deprecated. Use " "<boost/math/interpolators/cardinal_cubic_b_spline.hpp>" " instead.")
 ^
1 warning generated.
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/old/geojsonsf/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/jsonify/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/rapidjsonr/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/Rcpp/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/spatialwidget/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include -fPIC  -Wall -g -O2  -c pointcloud.cpp -o pointcloud.o
In file included from pointcloud.cpp:5:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/spatialwidget/include/spatialwidget/spatialwidget.hpp:7:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include/colourvalues/colours/colours_hex.hpp:5:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include/colourvalues/colours.hpp:10:
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/math/interpolators/cubic_b_spline.hpp:28:1: warning: This header is deprecated. Use <boost/math/interpolators/cardinal_cubic_b_spline.hpp> instead. [-W#pragma-messages]
BOOST_HEADER_DEPRECATED("<boost/math/interpolators/cardinal_cubic_b_spline.hpp>");
^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/config/header_deprecated.hpp:23:37: note: expanded from macro 'BOOST_HEADER_DEPRECATED'
# define BOOST_HEADER_DEPRECATED(a) BOOST_PRAGMA_MESSAGE("This header is deprecated. Use " a " instead.")
                                    ^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/config/pragma_message.hpp:24:34: note: expanded from macro 'BOOST_PRAGMA_MESSAGE'
# define BOOST_PRAGMA_MESSAGE(x) _Pragma(BOOST_STRINGIZE(message(x)))
                                 ^
<scratch space>:14:2: note: expanded from here
 message("This header is deprecated. Use " "<boost/math/interpolators/cardinal_cubic_b_spline.hpp>" " instead.")
 ^
1 warning generated.
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/old/geojsonsf/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/jsonify/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/rapidjsonr/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/Rcpp/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/spatialwidget/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include -fPIC  -Wall -g -O2  -c polygon.cpp -o polygon.o
In file included from polygon.cpp:5:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/spatialwidget/include/spatialwidget/spatialwidget.hpp:7:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include/colourvalues/colours/colours_hex.hpp:5:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include/colourvalues/colours.hpp:10:
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/math/interpolators/cubic_b_spline.hpp:28:1: warning: This header is deprecated. Use <boost/math/interpolators/cardinal_cubic_b_spline.hpp> instead. [-W#pragma-messages]
BOOST_HEADER_DEPRECATED("<boost/math/interpolators/cardinal_cubic_b_spline.hpp>");
^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/config/header_deprecated.hpp:23:37: note: expanded from macro 'BOOST_HEADER_DEPRECATED'
# define BOOST_HEADER_DEPRECATED(a) BOOST_PRAGMA_MESSAGE("This header is deprecated. Use " a " instead.")
                                    ^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/config/pragma_message.hpp:24:34: note: expanded from macro 'BOOST_PRAGMA_MESSAGE'
# define BOOST_PRAGMA_MESSAGE(x) _Pragma(BOOST_STRINGIZE(message(x)))
                                 ^
<scratch space>:14:2: note: expanded from here
 message("This header is deprecated. Use " "<boost/math/interpolators/cardinal_cubic_b_spline.hpp>" " instead.")
 ^
1 warning generated.
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/old/geojsonsf/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/jsonify/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/rapidjsonr/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/Rcpp/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/spatialwidget/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include -fPIC  -Wall -g -O2  -c scatterplot.cpp -o scatterplot.o
In file included from scatterplot.cpp:6:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/spatialwidget/include/spatialwidget/spatialwidget.hpp:7:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include/colourvalues/colours/colours_hex.hpp:5:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include/colourvalues/colours.hpp:10:
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/math/interpolators/cubic_b_spline.hpp:28:1: warning: This header is deprecated. Use <boost/math/interpolators/cardinal_cubic_b_spline.hpp> instead. [-W#pragma-messages]
BOOST_HEADER_DEPRECATED("<boost/math/interpolators/cardinal_cubic_b_spline.hpp>");
^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/config/header_deprecated.hpp:23:37: note: expanded from macro 'BOOST_HEADER_DEPRECATED'
# define BOOST_HEADER_DEPRECATED(a) BOOST_PRAGMA_MESSAGE("This header is deprecated. Use " a " instead.")
                                    ^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/config/pragma_message.hpp:24:34: note: expanded from macro 'BOOST_PRAGMA_MESSAGE'
# define BOOST_PRAGMA_MESSAGE(x) _Pragma(BOOST_STRINGIZE(message(x)))
                                 ^
<scratch space>:14:2: note: expanded from here
 message("This header is deprecated. Use " "<boost/math/interpolators/cardinal_cubic_b_spline.hpp>" " instead.")
 ^
1 warning generated.
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/old/geojsonsf/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/jsonify/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/rapidjsonr/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/Rcpp/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/spatialwidget/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include -fPIC  -Wall -g -O2  -c screengrid.cpp -o screengrid.o
In file included from screengrid.cpp:5:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/spatialwidget/include/spatialwidget/spatialwidget.hpp:7:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include/colourvalues/colours/colours_hex.hpp:5:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include/colourvalues/colours.hpp:10:
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/math/interpolators/cubic_b_spline.hpp:28:1: warning: This header is deprecated. Use <boost/math/interpolators/cardinal_cubic_b_spline.hpp> instead. [-W#pragma-messages]
BOOST_HEADER_DEPRECATED("<boost/math/interpolators/cardinal_cubic_b_spline.hpp>");
^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/config/header_deprecated.hpp:23:37: note: expanded from macro 'BOOST_HEADER_DEPRECATED'
# define BOOST_HEADER_DEPRECATED(a) BOOST_PRAGMA_MESSAGE("This header is deprecated. Use " a " instead.")
                                    ^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/config/pragma_message.hpp:24:34: note: expanded from macro 'BOOST_PRAGMA_MESSAGE'
# define BOOST_PRAGMA_MESSAGE(x) _Pragma(BOOST_STRINGIZE(message(x)))
                                 ^
<scratch space>:14:2: note: expanded from here
 message("This header is deprecated. Use " "<boost/math/interpolators/cardinal_cubic_b_spline.hpp>" " instead.")
 ^
1 warning generated.
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/old/geojsonsf/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/jsonify/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/rapidjsonr/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/Rcpp/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/spatialwidget/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include -fPIC  -Wall -g -O2  -c text.cpp -o text.o
In file included from text.cpp:5:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/spatialwidget/include/spatialwidget/spatialwidget.hpp:7:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include/colourvalues/colours/colours_hex.hpp:5:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/colourvalues/include/colourvalues/colours.hpp:10:
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/math/interpolators/cubic_b_spline.hpp:28:1: warning: This header is deprecated. Use <boost/math/interpolators/cardinal_cubic_b_spline.hpp> instead. [-W#pragma-messages]
BOOST_HEADER_DEPRECATED("<boost/math/interpolators/cardinal_cubic_b_spline.hpp>");
^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/config/header_deprecated.hpp:23:37: note: expanded from macro 'BOOST_HEADER_DEPRECATED'
# define BOOST_HEADER_DEPRECATED(a) BOOST_PRAGMA_MESSAGE("This header is deprecated. Use " a " instead.")
                                    ^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/mapdeck/BH/include/boost/config/pragma_message.hpp:24:34: note: expanded from macro 'BOOST_PRAGMA_MESSAGE'
# define BOOST_PRAGMA_MESSAGE(x) _Pragma(BOOST_STRINGIZE(message(x)))
                                 ^
<scratch space>:14:2: note: expanded from here
 message("This header is deprecated. Use " "<boost/math/interpolators/cardinal_cubic_b_spline.hpp>" " instead.")
 ^
1 warning generated.
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -dynamiclib -Wl,-headerpad_max_install_names -undefined dynamic_lookup -single_module -multiply_defined suppress -L/Library/Frameworks/R.framework/Resources/lib -L/usr/local/clang8/lib -o mapdeck.so RcppExports.o arc.o geojson.o grid.o hexagon.o line.o path.o pointcloud.o polygon.o scatterplot.o screengrid.o text.o -F/Library/Frameworks/R.framework/.. -framework R -Wl,-framework -Wl,CoreFoundation
ld: warning: text-based stub file /System/Library/Frameworks//CoreFoundation.framework/CoreFoundation.tbd and library file /System/Library/Frameworks//CoreFoundation.framework/CoreFoundation are out of sync. Falling back to library file for linking.
installing to /Users/dave/Documents/github/geojsonsf/revdep/checks.noindex/mapdeck/old/mapdeck.Rcheck/00LOCK-mapdeck/00new/mapdeck/libs
** R
** data
*** moving datasets to lazyload DB
** inst
** byte-compile and prepare package for lazy loading
** help
*** installing help indices
** building package indices
** installing vignettes
** testing if installed package can be loaded from temporary location
** checking absolute paths in shared objects and dynamic libraries
** testing if installed package can be loaded from final location
** testing if installed package keeps a record of temporary installation path
* DONE (mapdeck)

```
# spatialwidget

<details>

* Version: 0.2
* Source code: https://github.com/cran/spatialwidget
* URL: https://symbolixau.github.io/spatialwidget/articles/spatialwidget.html
* Date/Publication: 2019-01-18 09:40:03 UTC
* Number of recursive dependencies: 59

Run `revdep_details(,"spatialwidget")` for more info

</details>

## Newly broken

*   checking whether package ‘spatialwidget’ can be installed ... ERROR
    ```
    Installation failed.
    See ‘/Users/dave/Documents/github/geojsonsf/revdep/checks.noindex/spatialwidget/new/spatialwidget.Rcheck/00install.out’ for details.
    ```

## Installation

### Devel

```
* installing *source* package ‘spatialwidget’ ...
** package ‘spatialwidget’ successfully unpacked and MD5 sums checked
** using staged installation
** libs
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/colourvalues/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/new/geojsonsf/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/jsonify/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/rapidjsonr/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include -fPIC  -Wall -g -O2  -c RcppExports.cpp -o RcppExports.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/colourvalues/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/new/geojsonsf/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/jsonify/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/rapidjsonr/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include -fPIC  -Wall -g -O2  -c data_construction.cpp -o data_construction.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/colourvalues/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/new/geojsonsf/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/jsonify/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/rapidjsonr/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include -fPIC  -Wall -g -O2  -c geojson.cpp -o geojson.o
In file included from geojson.cpp:2:
In file included from ../inst/include/spatialwidget/spatialwidget.hpp:7:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/colourvalues/include/colourvalues/colours/colours_hex.hpp:5:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/colourvalues/include/colourvalues/colours.hpp:10:
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include/boost/math/interpolators/cubic_b_spline.hpp:28:1: warning: This header is deprecated. Use <boost/math/interpolators/cardinal_cubic_b_spline.hpp> instead. [-W#pragma-messages]
BOOST_HEADER_DEPRECATED("<boost/math/interpolators/cardinal_cubic_b_spline.hpp>");
^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include/boost/config/header_deprecated.hpp:23:37: note: expanded from macro 'BOOST_HEADER_DEPRECATED'
# define BOOST_HEADER_DEPRECATED(a) BOOST_PRAGMA_MESSAGE("This header is deprecated. Use " a " instead.")
                                    ^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include/boost/config/pragma_message.hpp:24:34: note: expanded from macro 'BOOST_PRAGMA_MESSAGE'
# define BOOST_PRAGMA_MESSAGE(x) _Pragma(BOOST_STRINGIZE(message(x)))
                                 ^
<scratch space>:14:2: note: expanded from here
 message("This header is deprecated. Use " "<boost/math/interpolators/cardinal_cubic_b_spline.hpp>" " instead.")
 ^
In file included from geojson.cpp:2:
In file included from ../inst/include/spatialwidget/spatialwidget.hpp:14:
In file included from ../inst/include/spatialwidget/geojson/geojson.hpp:8:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/new/geojsonsf/include/geojsonsf/write_geojson.hpp:6:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/new/geojsonsf/include/geojsonsf/geojson/writers/write_geojson.hpp:6:
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/new/geojsonsf/include/geojsonsf/geometrycollection/geometrycollection.hpp:6:10: fatal error: 'sfheaders/utils/utils.hpp' file not found
#include "sfheaders/utils/utils.hpp"
         ^~~~~~~~~~~~~~~~~~~~~~~~~~~
1 warning and 1 error generated.
make: *** [geojson.o] Error 1
ERROR: compilation failed for package ‘spatialwidget’
* removing ‘/Users/dave/Documents/github/geojsonsf/revdep/checks.noindex/spatialwidget/new/spatialwidget.Rcheck/spatialwidget’

```
### CRAN

```
* installing *source* package ‘spatialwidget’ ...
** package ‘spatialwidget’ successfully unpacked and MD5 sums checked
** using staged installation
** libs
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/colourvalues/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/old/geojsonsf/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/jsonify/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/rapidjsonr/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include -fPIC  -Wall -g -O2  -c RcppExports.cpp -o RcppExports.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/colourvalues/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/old/geojsonsf/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/jsonify/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/rapidjsonr/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include -fPIC  -Wall -g -O2  -c data_construction.cpp -o data_construction.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/colourvalues/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/old/geojsonsf/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/jsonify/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/rapidjsonr/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include -fPIC  -Wall -g -O2  -c geojson.cpp -o geojson.o
In file included from geojson.cpp:2:
In file included from ../inst/include/spatialwidget/spatialwidget.hpp:7:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/colourvalues/include/colourvalues/colours/colours_hex.hpp:5:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/colourvalues/include/colourvalues/colours.hpp:10:
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include/boost/math/interpolators/cubic_b_spline.hpp:28:1: warning: This header is deprecated. Use <boost/math/interpolators/cardinal_cubic_b_spline.hpp> instead. [-W#pragma-messages]
BOOST_HEADER_DEPRECATED("<boost/math/interpolators/cardinal_cubic_b_spline.hpp>");
^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include/boost/config/header_deprecated.hpp:23:37: note: expanded from macro 'BOOST_HEADER_DEPRECATED'
# define BOOST_HEADER_DEPRECATED(a) BOOST_PRAGMA_MESSAGE("This header is deprecated. Use " a " instead.")
                                    ^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include/boost/config/pragma_message.hpp:24:34: note: expanded from macro 'BOOST_PRAGMA_MESSAGE'
# define BOOST_PRAGMA_MESSAGE(x) _Pragma(BOOST_STRINGIZE(message(x)))
                                 ^
<scratch space>:14:2: note: expanded from here
 message("This header is deprecated. Use " "<boost/math/interpolators/cardinal_cubic_b_spline.hpp>" " instead.")
 ^
1 warning generated.
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/colourvalues/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/old/geojsonsf/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/jsonify/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/rapidjsonr/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include -fPIC  -Wall -g -O2  -c geometrycollection.cpp -o geometrycollection.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/colourvalues/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/old/geojsonsf/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/jsonify/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/rapidjsonr/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include -fPIC  -Wall -g -O2  -c palette.cpp -o palette.o
In file included from palette.cpp:2:
In file included from ../inst/include/spatialwidget/palette/palette.hpp:6:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/colourvalues/include/colourvalues/colours/colours_hex.hpp:5:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/colourvalues/include/colourvalues/colours.hpp:10:
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include/boost/math/interpolators/cubic_b_spline.hpp:28:1: warning: This header is deprecated. Use <boost/math/interpolators/cardinal_cubic_b_spline.hpp> instead. [-W#pragma-messages]
BOOST_HEADER_DEPRECATED("<boost/math/interpolators/cardinal_cubic_b_spline.hpp>");
^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include/boost/config/header_deprecated.hpp:23:37: note: expanded from macro 'BOOST_HEADER_DEPRECATED'
# define BOOST_HEADER_DEPRECATED(a) BOOST_PRAGMA_MESSAGE("This header is deprecated. Use " a " instead.")
                                    ^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include/boost/config/pragma_message.hpp:24:34: note: expanded from macro 'BOOST_PRAGMA_MESSAGE'
# define BOOST_PRAGMA_MESSAGE(x) _Pragma(BOOST_STRINGIZE(message(x)))
                                 ^
<scratch space>:14:2: note: expanded from here
 message("This header is deprecated. Use " "<boost/math/interpolators/cardinal_cubic_b_spline.hpp>" " instead.")
 ^
1 warning generated.
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/colourvalues/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/old/geojsonsf/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/jsonify/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/rapidjsonr/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include -fPIC  -Wall -g -O2  -c spatialwidget_defaults.cpp -o spatialwidget_defaults.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/colourvalues/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/old/geojsonsf/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/jsonify/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/rapidjsonr/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include -fPIC  -Wall -g -O2  -c utils.cpp -o utils.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/colourvalues/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/old/geojsonsf/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/jsonify/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/rapidjsonr/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include -fPIC  -Wall -g -O2  -c widget_line.cpp -o widget_line.o
In file included from widget_line.cpp:2:
In file included from ../inst/include/spatialwidget/spatialwidget.hpp:7:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/colourvalues/include/colourvalues/colours/colours_hex.hpp:5:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/colourvalues/include/colourvalues/colours.hpp:10:
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include/boost/math/interpolators/cubic_b_spline.hpp:28:1: warning: This header is deprecated. Use <boost/math/interpolators/cardinal_cubic_b_spline.hpp> instead. [-W#pragma-messages]
BOOST_HEADER_DEPRECATED("<boost/math/interpolators/cardinal_cubic_b_spline.hpp>");
^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include/boost/config/header_deprecated.hpp:23:37: note: expanded from macro 'BOOST_HEADER_DEPRECATED'
# define BOOST_HEADER_DEPRECATED(a) BOOST_PRAGMA_MESSAGE("This header is deprecated. Use " a " instead.")
                                    ^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include/boost/config/pragma_message.hpp:24:34: note: expanded from macro 'BOOST_PRAGMA_MESSAGE'
# define BOOST_PRAGMA_MESSAGE(x) _Pragma(BOOST_STRINGIZE(message(x)))
                                 ^
<scratch space>:14:2: note: expanded from here
 message("This header is deprecated. Use " "<boost/math/interpolators/cardinal_cubic_b_spline.hpp>" " instead.")
 ^
1 warning generated.
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/colourvalues/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/old/geojsonsf/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/jsonify/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/rapidjsonr/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include -fPIC  -Wall -g -O2  -c widget_point.cpp -o widget_point.o
In file included from widget_point.cpp:2:
In file included from ../inst/include/spatialwidget/spatialwidget.hpp:7:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/colourvalues/include/colourvalues/colours/colours_hex.hpp:5:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/colourvalues/include/colourvalues/colours.hpp:10:
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include/boost/math/interpolators/cubic_b_spline.hpp:28:1: warning: This header is deprecated. Use <boost/math/interpolators/cardinal_cubic_b_spline.hpp> instead. [-W#pragma-messages]
BOOST_HEADER_DEPRECATED("<boost/math/interpolators/cardinal_cubic_b_spline.hpp>");
^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include/boost/config/header_deprecated.hpp:23:37: note: expanded from macro 'BOOST_HEADER_DEPRECATED'
# define BOOST_HEADER_DEPRECATED(a) BOOST_PRAGMA_MESSAGE("This header is deprecated. Use " a " instead.")
                                    ^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include/boost/config/pragma_message.hpp:24:34: note: expanded from macro 'BOOST_PRAGMA_MESSAGE'
# define BOOST_PRAGMA_MESSAGE(x) _Pragma(BOOST_STRINGIZE(message(x)))
                                 ^
<scratch space>:14:2: note: expanded from here
 message("This header is deprecated. Use " "<boost/math/interpolators/cardinal_cubic_b_spline.hpp>" " instead.")
 ^
1 warning generated.
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -DSTRICT_R_HEADERS -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/colourvalues/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/geojsonsf/old/geojsonsf/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/jsonify/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/rapidjsonr/include" -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I../inst/include -fPIC  -Wall -g -O2  -c widget_polygon.cpp -o widget_polygon.o
In file included from widget_polygon.cpp:2:
In file included from ../inst/include/spatialwidget/spatialwidget.hpp:7:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/colourvalues/include/colourvalues/colours/colours_hex.hpp:5:
In file included from /Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/colourvalues/include/colourvalues/colours.hpp:10:
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include/boost/math/interpolators/cubic_b_spline.hpp:28:1: warning: This header is deprecated. Use <boost/math/interpolators/cardinal_cubic_b_spline.hpp> instead. [-W#pragma-messages]
BOOST_HEADER_DEPRECATED("<boost/math/interpolators/cardinal_cubic_b_spline.hpp>");
^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include/boost/config/header_deprecated.hpp:23:37: note: expanded from macro 'BOOST_HEADER_DEPRECATED'
# define BOOST_HEADER_DEPRECATED(a) BOOST_PRAGMA_MESSAGE("This header is deprecated. Use " a " instead.")
                                    ^
/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/spatialwidget/BH/include/boost/config/pragma_message.hpp:24:34: note: expanded from macro 'BOOST_PRAGMA_MESSAGE'
# define BOOST_PRAGMA_MESSAGE(x) _Pragma(BOOST_STRINGIZE(message(x)))
                                 ^
<scratch space>:14:2: note: expanded from here
 message("This header is deprecated. Use " "<boost/math/interpolators/cardinal_cubic_b_spline.hpp>" " instead.")
 ^
1 warning generated.
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -dynamiclib -Wl,-headerpad_max_install_names -undefined dynamic_lookup -single_module -multiply_defined suppress -L/Library/Frameworks/R.framework/Resources/lib -L/usr/local/clang8/lib -o spatialwidget.so RcppExports.o data_construction.o geojson.o geometrycollection.o palette.o spatialwidget_defaults.o utils.o widget_line.o widget_point.o widget_polygon.o -F/Library/Frameworks/R.framework/.. -framework R -Wl,-framework -Wl,CoreFoundation
ld: warning: text-based stub file /System/Library/Frameworks//CoreFoundation.framework/CoreFoundation.tbd and library file /System/Library/Frameworks//CoreFoundation.framework/CoreFoundation are out of sync. Falling back to library file for linking.
installing to /Users/dave/Documents/github/geojsonsf/revdep/checks.noindex/spatialwidget/old/spatialwidget.Rcheck/00LOCK-spatialwidget/00new/spatialwidget/libs
** R
** data
*** moving datasets to lazyload DB
** inst
** byte-compile and prepare package for lazy loading
** help
*** installing help indices
** building package indices
** installing vignettes
** testing if installed package can be loaded from temporary location
** checking absolute paths in shared objects and dynamic libraries
** testing if installed package can be loaded from final location
** testing if installed package keeps a record of temporary installation path
* DONE (spatialwidget)

```
# vapour

<details>

* Version: 0.5.0
* Source code: https://github.com/cran/vapour
* URL: https://github.com/hypertidy/vapour
* BugReports: https://github.com/hypertidy/vapour/issues
* Date/Publication: 2020-01-30 09:20:02 UTC
* Number of recursive dependencies: 64

Run `revdep_details(,"vapour")` for more info

</details>

## In both

*   checking whether package ‘vapour’ can be installed ... ERROR
    ```
    Installation failed.
    See ‘/Users/dave/Documents/github/geojsonsf/revdep/checks.noindex/vapour/new/vapour.Rcheck/00install.out’ for details.
    ```

## Installation

### Devel

```
* installing *source* package ‘vapour’ ...
** package ‘vapour’ successfully unpacked and MD5 sums checked
** using staged installation
configure: CC: ccache /usr/local/clang8/bin/clang
configure: CXX: ccache /usr/local/clang8/bin/clang++ -std=gnu++11
checking for gdal-config... /usr/local/bin/gdal-config
checking gdal-config usability... yes
configure: GDAL: 3.0.2
checking GDAL version >= 2.0.1... yes
checking for gcc... ccache /usr/local/clang8/bin/clang
checking whether the C compiler works... yes
checking for C compiler default output file name... a.out
checking for suffix of executables... 
checking whether we are cross compiling... no
checking for suffix of object files... o
checking whether we are using the GNU C compiler... yes
checking whether ccache /usr/local/clang8/bin/clang accepts -g... yes
checking for ccache /usr/local/clang8/bin/clang option to accept ISO C89... none needed
checking how to run the C preprocessor... ccache /usr/local/clang8/bin/clang -E
checking for grep that handles long lines and -e... /usr/bin/grep
checking for egrep... /usr/bin/grep -E
checking for ANSI C header files... rm: conftest.dSYM: is a directory
rm: conftest.dSYM: is a directory
yes
checking for sys/types.h... yes
checking for sys/stat.h... yes
checking for stdlib.h... yes
checking for string.h... yes
checking for memory.h... yes
checking for strings.h... yes
checking for inttypes.h... yes
checking for stdint.h... yes
checking for unistd.h... yes
checking gdal.h usability... yes
checking gdal.h presence... yes
checking for gdal.h... yes
checking GDAL: linking with --libs only... yes
checking GDAL: /usr/local/Cellar/osgeo-gdal/3.0.2/share/gdal/pcs.csv readable... no
configure: Package CPP flags:  -I/usr/local/Cellar/osgeo-gdal/3.0.2/include
configure: Package LIBS:  -L/usr/local/Cellar/osgeo-gdal/3.0.2/lib -lgdal
configure: creating ./config.status
config.status: creating src/Makevars
** libs
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -I/usr/local/Cellar/osgeo-gdal/3.0.2/include -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/vapour/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include  -fPIC  -Wall -g -O2  -c RcppExports.cpp -o RcppExports.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -I/usr/local/Cellar/osgeo-gdal/3.0.2/include -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/vapour/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include  -fPIC  -Wall -g -O2  -c VSIReadDirEx.cpp -o VSIReadDirEx.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -I/usr/local/Cellar/osgeo-gdal/3.0.2/include -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/vapour/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include  -fPIC  -Wall -g -O2  -c binary-geom.cpp -o binary-geom.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -I/usr/local/Cellar/osgeo-gdal/3.0.2/include -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/vapour/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include  -fPIC  -Wall -g -O2  -c contourize.cpp -o contourize.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -I/usr/local/Cellar/osgeo-gdal/3.0.2/include -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/vapour/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include  -fPIC  -Wall -g -O2  -c gdal_utils.cpp -o gdal_utils.o
ccache /usr/local/clang8/bin/clang -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -I/usr/local/Cellar/osgeo-gdal/3.0.2/include -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/vapour/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include  -fPIC  -Wall -g -O2  -c init.c -o init.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -I/usr/local/Cellar/osgeo-gdal/3.0.2/include -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/vapour/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include  -fPIC  -Wall -g -O2  -c raster_warp.cpp -o raster_warp.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -I/usr/local/Cellar/osgeo-gdal/3.0.2/include -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/vapour/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include  -fPIC  -Wall -g -O2  -c rasterio.cpp -o rasterio.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -I/usr/local/Cellar/osgeo-gdal/3.0.2/include -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/vapour/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include  -fPIC  -Wall -g -O2  -c sds_io.cpp -o sds_io.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -I/usr/local/Cellar/osgeo-gdal/3.0.2/include -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/vapour/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include  -fPIC  -Wall -g -O2  -c srs.cpp -o srs.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -I/usr/local/Cellar/osgeo-gdal/3.0.2/include -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/vapour/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include  -fPIC  -Wall -g -O2  -c vapour.cpp -o vapour.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -dynamiclib -Wl,-headerpad_max_install_names -undefined dynamic_lookup -single_module -multiply_defined suppress -L/Library/Frameworks/R.framework/Resources/lib -L/usr/local/clang8/lib -o vapour.so RcppExports.o VSIReadDirEx.o binary-geom.o contourize.o gdal_utils.o init.o raster_warp.o rasterio.o sds_io.o srs.o vapour.o -L/usr/local/Cellar/osgeo-gdal/3.0.2/lib -lgdal -F/Library/Frameworks/R.framework/.. -framework R -Wl,-framework -Wl,CoreFoundation
ld: warning: text-based stub file /System/Library/Frameworks//CoreFoundation.framework/CoreFoundation.tbd and library file /System/Library/Frameworks//CoreFoundation.framework/CoreFoundation are out of sync. Falling back to library file for linking.
installing to /Users/dave/Documents/github/geojsonsf/revdep/checks.noindex/vapour/new/vapour.Rcheck/00LOCK-vapour/00new/vapour/libs
** R
** data
*** moving datasets to lazyload DB
** inst
** byte-compile and prepare package for lazy loading
** help
*** installing help indices
*** copying figures
** building package indices
** installing vignettes
** testing if installed package can be loaded from temporary location
Error: package or namespace load failed for ‘vapour’ in dyn.load(file, DLLpath = DLLpath, ...):
 unable to load shared object '/Users/dave/Documents/github/geojsonsf/revdep/checks.noindex/vapour/new/vapour.Rcheck/00LOCK-vapour/00new/vapour/libs/vapour.so':
  dlopen(/Users/dave/Documents/github/geojsonsf/revdep/checks.noindex/vapour/new/vapour.Rcheck/00LOCK-vapour/00new/vapour/libs/vapour.so, 6): Library not loaded: /usr/local/opt/giflib/lib/libgif.7.dylib
  Referenced from: /usr/local/opt/osgeo-gdal/lib/libgdal.26.dylib
  Reason: Incompatible library version: libgdal.26.dylib requires version 8.0.0 or later, but libgif.7.dylib provides version 0.0.0
Error: loading failed
Execution halted
ERROR: loading failed
* removing ‘/Users/dave/Documents/github/geojsonsf/revdep/checks.noindex/vapour/new/vapour.Rcheck/vapour’

```
### CRAN

```
* installing *source* package ‘vapour’ ...
** package ‘vapour’ successfully unpacked and MD5 sums checked
** using staged installation
configure: CC: ccache /usr/local/clang8/bin/clang
configure: CXX: ccache /usr/local/clang8/bin/clang++ -std=gnu++11
checking for gdal-config... /usr/local/bin/gdal-config
checking gdal-config usability... yes
configure: GDAL: 3.0.2
checking GDAL version >= 2.0.1... yes
checking for gcc... ccache /usr/local/clang8/bin/clang
checking whether the C compiler works... yes
checking for C compiler default output file name... a.out
checking for suffix of executables... 
checking whether we are cross compiling... no
checking for suffix of object files... o
checking whether we are using the GNU C compiler... yes
checking whether ccache /usr/local/clang8/bin/clang accepts -g... yes
checking for ccache /usr/local/clang8/bin/clang option to accept ISO C89... none needed
checking how to run the C preprocessor... ccache /usr/local/clang8/bin/clang -E
checking for grep that handles long lines and -e... /usr/bin/grep
checking for egrep... /usr/bin/grep -E
checking for ANSI C header files... rm: conftest.dSYM: is a directory
rm: conftest.dSYM: is a directory
yes
checking for sys/types.h... yes
checking for sys/stat.h... yes
checking for stdlib.h... yes
checking for string.h... yes
checking for memory.h... yes
checking for strings.h... yes
checking for inttypes.h... yes
checking for stdint.h... yes
checking for unistd.h... yes
checking gdal.h usability... yes
checking gdal.h presence... yes
checking for gdal.h... yes
checking GDAL: linking with --libs only... yes
checking GDAL: /usr/local/Cellar/osgeo-gdal/3.0.2/share/gdal/pcs.csv readable... no
configure: Package CPP flags:  -I/usr/local/Cellar/osgeo-gdal/3.0.2/include
configure: Package LIBS:  -L/usr/local/Cellar/osgeo-gdal/3.0.2/lib -lgdal
configure: creating ./config.status
config.status: creating src/Makevars
** libs
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -I/usr/local/Cellar/osgeo-gdal/3.0.2/include -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/vapour/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include  -fPIC  -Wall -g -O2  -c RcppExports.cpp -o RcppExports.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -I/usr/local/Cellar/osgeo-gdal/3.0.2/include -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/vapour/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include  -fPIC  -Wall -g -O2  -c VSIReadDirEx.cpp -o VSIReadDirEx.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -I/usr/local/Cellar/osgeo-gdal/3.0.2/include -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/vapour/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include  -fPIC  -Wall -g -O2  -c binary-geom.cpp -o binary-geom.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -I/usr/local/Cellar/osgeo-gdal/3.0.2/include -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/vapour/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include  -fPIC  -Wall -g -O2  -c contourize.cpp -o contourize.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -I/usr/local/Cellar/osgeo-gdal/3.0.2/include -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/vapour/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include  -fPIC  -Wall -g -O2  -c gdal_utils.cpp -o gdal_utils.o
ccache /usr/local/clang8/bin/clang -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -I/usr/local/Cellar/osgeo-gdal/3.0.2/include -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/vapour/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include  -fPIC  -Wall -g -O2  -c init.c -o init.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -I/usr/local/Cellar/osgeo-gdal/3.0.2/include -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/vapour/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include  -fPIC  -Wall -g -O2  -c raster_warp.cpp -o raster_warp.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -I/usr/local/Cellar/osgeo-gdal/3.0.2/include -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/vapour/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include  -fPIC  -Wall -g -O2  -c rasterio.cpp -o rasterio.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -I/usr/local/Cellar/osgeo-gdal/3.0.2/include -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/vapour/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include  -fPIC  -Wall -g -O2  -c sds_io.cpp -o sds_io.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -I/usr/local/Cellar/osgeo-gdal/3.0.2/include -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/vapour/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include  -fPIC  -Wall -g -O2  -c srs.cpp -o srs.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG -I/usr/local/Cellar/osgeo-gdal/3.0.2/include -I"/Users/dave/Documents/github/geojsonsf/revdep/library.noindex/vapour/Rcpp/include" -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include  -fPIC  -Wall -g -O2  -c vapour.cpp -o vapour.o
ccache /usr/local/clang8/bin/clang++ -std=gnu++11 -dynamiclib -Wl,-headerpad_max_install_names -undefined dynamic_lookup -single_module -multiply_defined suppress -L/Library/Frameworks/R.framework/Resources/lib -L/usr/local/clang8/lib -o vapour.so RcppExports.o VSIReadDirEx.o binary-geom.o contourize.o gdal_utils.o init.o raster_warp.o rasterio.o sds_io.o srs.o vapour.o -L/usr/local/Cellar/osgeo-gdal/3.0.2/lib -lgdal -F/Library/Frameworks/R.framework/.. -framework R -Wl,-framework -Wl,CoreFoundation
ld: warning: text-based stub file /System/Library/Frameworks//CoreFoundation.framework/CoreFoundation.tbd and library file /System/Library/Frameworks//CoreFoundation.framework/CoreFoundation are out of sync. Falling back to library file for linking.
installing to /Users/dave/Documents/github/geojsonsf/revdep/checks.noindex/vapour/old/vapour.Rcheck/00LOCK-vapour/00new/vapour/libs
** R
** data
*** moving datasets to lazyload DB
** inst
** byte-compile and prepare package for lazy loading
** help
*** installing help indices
*** copying figures
** building package indices
** installing vignettes
** testing if installed package can be loaded from temporary location
Error: package or namespace load failed for ‘vapour’ in dyn.load(file, DLLpath = DLLpath, ...):
 unable to load shared object '/Users/dave/Documents/github/geojsonsf/revdep/checks.noindex/vapour/old/vapour.Rcheck/00LOCK-vapour/00new/vapour/libs/vapour.so':
  dlopen(/Users/dave/Documents/github/geojsonsf/revdep/checks.noindex/vapour/old/vapour.Rcheck/00LOCK-vapour/00new/vapour/libs/vapour.so, 6): Library not loaded: /usr/local/opt/giflib/lib/libgif.7.dylib
  Referenced from: /usr/local/opt/osgeo-gdal/lib/libgdal.26.dylib
  Reason: Incompatible library version: libgdal.26.dylib requires version 8.0.0 or later, but libgif.7.dylib provides version 0.0.0
Error: loading failed
Execution halted
ERROR: loading failed
* removing ‘/Users/dave/Documents/github/geojsonsf/revdep/checks.noindex/vapour/old/vapour.Rcheck/vapour’

```
