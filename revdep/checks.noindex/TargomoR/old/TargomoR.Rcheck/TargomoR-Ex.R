pkgname <- "TargomoR"
source(file.path(R.home("share"), "R", "examples-header.R"))
options(warn = 1)
library('TargomoR')

base::assign(".oldSearch", base::search(), pos = 'CheckExEnv')
base::assign(".old_wd", base::getwd(), pos = 'CheckExEnv')
cleanEx()
nameEx("attribution")
### * attribution

flush(stderr()); flush(stdout())

### Name: attribution
### Title: Add Targomo Attributions
### Aliases: attribution attributionFreeIframe attributionOtherIframe
###   attributionLink addTargomoAttribution

### ** Examples

# return the attribution link
attributionLink()




cleanEx()
nameEx("capabilities")
### * capabilities

flush(stderr()); flush(stdout())

### Name: capabilities
### Title: Get Account Capabilities
### Aliases: capabilities getTargomoCapabilities print.tgm_capabilities

### ** Examples





cleanEx()
nameEx("formatting")
### * formatting

flush(stderr()); flush(stdout())

### Name: formatting
### Title: Format Edgeweights (times and distances)
### Aliases: formatting numericEdgeWeight prettyEdgeWeight

### ** Examples

numericEdgeWeight("1hr 30m", "time") # 5400
numericEdgeWeight("1ml", "distance") # 1609

prettyEdgeWeight(1245, "time") # 30min 45s
prettyEdgeWeight(1245, "distance") # 1km 245m




cleanEx()
nameEx("getTargomoMapURL")
### * getTargomoMapURL

flush(stderr()); flush(stdout())

### Name: getTargomoMapURL
### Title: Targomo Map Tiles URL
### Aliases: getTargomoMapURL

### ** Examples

getTargomoMapURL(style = "toner", api_key = NULL)




cleanEx()
nameEx("getTargomoPolygons")
### * getTargomoPolygons

flush(stderr()); flush(stdout())

### Name: getTargomoPolygons
### Title: Add Targomo Polygons to a Leaflet Map
### Aliases: getTargomoPolygons drawTargomoPolygons addTargomoPolygons

### ** Examples





cleanEx()
nameEx("options")
### * options

flush(stderr()); flush(stdout())

### Name: options
### Title: Set Targomo Options
### Aliases: options targomoOptions

### ** Examples

targomoOptions(travelType = "transit")
targomoOptions(travelTimes = list("15m", "30m", "45m", "1h"), maxEdgeWeight = "1h")




cleanEx()
nameEx("polygonDrawOptions")
### * polygonDrawOptions

flush(stderr()); flush(stdout())

### Name: polygonDrawOptions
### Title: Options for Drawing Polygons on the Map
### Aliases: polygonDrawOptions

### ** Examples

# show the list
polygonDrawOptions()




cleanEx()
nameEx("routeDrawOptions")
### * routeDrawOptions

flush(stderr()); flush(stdout())

### Name: routeDrawOptions
### Title: Options for Drawing Routes on the Map
### Aliases: routeDrawOptions

### ** Examples

# show the list
routeDrawOptions()




cleanEx()
nameEx("routes")
### * routes

flush(stderr()); flush(stdout())

### Name: routes
### Title: Add Targomo Routes to a Leaflet Map
### Aliases: routes getTargomoRoutes drawTargomoRoutes addTargomoRoutes

### ** Examples





cleanEx()
nameEx("setTargomoVariables")
### * setTargomoVariables

flush(stderr()); flush(stdout())

### Name: setTargomoVariables
### Title: Set Targomo Environment Variables
### Aliases: setTargomoVariables

### ** Examples

## Not run: 
##D # write to a global file at Sys.getenv("HOME")
##D setTargomoVariables(api_key = "YOUR_SECRET_KEY", region = "asia", overwrite = TRUE, global = TRUE)
## End(Not run)




cleanEx()
nameEx("tiles")
### * tiles

flush(stderr()); flush(stdout())

### Name: tiles
### Title: Add Targomo Basemaps to a Leaflet Map
### Aliases: tiles addTargomoTiles targomoMapStyles

### ** Examples

# list Targomo Map Styles
targomoMapStyles()




cleanEx()
nameEx("timeDrawOptions")
### * timeDrawOptions

flush(stderr()); flush(stdout())

### Name: timeDrawOptions
### Title: Options for Drawing Times on the Map
### Aliases: timeDrawOptions

### ** Examples

# show the list
timeDrawOptions()




cleanEx()
nameEx("timeLegendOptions")
### * timeLegendOptions

flush(stderr()); flush(stdout())

### Name: timeLegendOptions
### Title: Time Legend Options
### Aliases: timeLegendOptions

### ** Examples

# show the list
timeLegendOptions()




cleanEx()
nameEx("times")
### * times

flush(stderr()); flush(stdout())

### Name: times
### Title: Add Targomo Times to a Leaflet Map
### Aliases: times getTargomoTimes drawTargomoTimes addTargomoTimes

### ** Examples





### * <FOOTER>
###
cleanEx()
options(digits = 7L)
base::cat("Time elapsed: ", proc.time() - base::get("ptime", pos = 'CheckExEnv'),"\n")
grDevices::dev.off()
###
### Local variables: ***
### mode: outline-minor ***
### outline-regexp: "\\(> \\)?### [*]+" ***
### End: ***
quit('no')
