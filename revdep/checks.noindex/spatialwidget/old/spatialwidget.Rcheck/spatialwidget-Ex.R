pkgname <- "spatialwidget"
source(file.path(R.home("share"), "R", "examples-header.R"))
options(warn = 1)
library('spatialwidget')

base::assign(".oldSearch", base::search(), pos = 'CheckExEnv')
base::assign(".old_wd", base::getwd(), pos = 'CheckExEnv')
cleanEx()
nameEx("widget_line")
### * widget_line

flush(stderr()); flush(stdout())

### Name: widget_line
### Title: Widget Line
### Aliases: widget_line

### ** Examples


## use default stroke options
l <- widget_line( widget_roads, legend = TRUE )




cleanEx()
nameEx("widget_od")
### * widget_od

flush(stderr()); flush(stdout())

### Name: widget_od
### Title: Widget OD
### Aliases: widget_od

### ** Examples


l <- widget_od( data = widget_arcs, origin = "origin", destination = "destination", legend = FALSE )




cleanEx()
nameEx("widget_point")
### * widget_point

flush(stderr()); flush(stdout())

### Name: widget_point
### Title: Widget Point
### Aliases: widget_point

### ** Examples


l <- widget_point( data = widget_capitals, legend = FALSE )




cleanEx()
nameEx("widget_polygon")
### * widget_polygon

flush(stderr()); flush(stdout())

### Name: widget_polygon
### Title: Widget Polygon
### Aliases: widget_polygon

### ** Examples


l <- widget_polygon( widget_melbourne, legend = FALSE )
l <- widget_polygon( widget_melbourne, fill_colour = "AREASQKM16", legend = TRUE )




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
