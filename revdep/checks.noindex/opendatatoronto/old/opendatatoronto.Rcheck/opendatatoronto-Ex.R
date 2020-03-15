pkgname <- "opendatatoronto"
source(file.path(R.home("share"), "R", "examples-header.R"))
options(warn = 1)
library('opendatatoronto')

base::assign(".oldSearch", base::search(), pos = 'CheckExEnv')
base::assign(".old_wd", base::getwd(), pos = 'CheckExEnv')
cleanEx()
nameEx("browse_package")
### * browse_package

flush(stderr()); flush(stdout())

### Name: browse_package
### Title: Open the package's page in your browser
### Aliases: browse_package

### ** Examples




cleanEx()
nameEx("browse_portal")
### * browse_portal

flush(stderr()); flush(stdout())

### Name: browse_portal
### Title: Open the City of Toronto Open Data Portal in your browser
### Aliases: browse_portal

### ** Examples




cleanEx()
nameEx("browse_resource")
### * browse_resource

flush(stderr()); flush(stdout())

### Name: browse_resource
### Title: Open the resource's package page in your browser
### Aliases: browse_resource

### ** Examples




cleanEx()
nameEx("get_resource")
### * get_resource

flush(stderr()); flush(stdout())

### Name: get_resource
### Title: Download a resource into your R session
### Aliases: get_resource

### ** Examples




cleanEx()
nameEx("list_package_resources")
### * list_package_resources

flush(stderr()); flush(stdout())

### Name: list_package_resources
### Title: List resources for a package
### Aliases: list_package_resources

### ** Examples




cleanEx()
nameEx("list_packages")
### * list_packages

flush(stderr()); flush(stdout())

### Name: list_packages
### Title: List packages
### Aliases: list_packages

### ** Examples




cleanEx()
nameEx("search_packages")
### * search_packages

flush(stderr()); flush(stdout())

### Name: search_packages
### Title: Search packages by title
### Aliases: search_packages

### ** Examples




cleanEx()
nameEx("show_package")
### * show_package

flush(stderr()); flush(stdout())

### Name: show_package
### Title: Show a package's metadata
### Aliases: show_package

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
