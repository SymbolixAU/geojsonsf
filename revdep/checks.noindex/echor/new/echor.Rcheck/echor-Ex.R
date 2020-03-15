pkgname <- "echor"
source(file.path(R.home("share"), "R", "examples-header.R"))
options(warn = 1)
library('echor')

base::assign(".oldSearch", base::search(), pos = 'CheckExEnv')
base::assign(".old_wd", base::getwd(), pos = 'CheckExEnv')
cleanEx()
nameEx("downloadDMRs")
### * downloadDMRs

flush(stderr()); flush(stdout())

### Name: downloadDMRs
### Title: Download Multiple DMRs
### Aliases: downloadDMRs

### ** Examples




cleanEx()
nameEx("echoAirGetFacilityInfo")
### * echoAirGetFacilityInfo

flush(stderr()); flush(stdout())

### Name: echoAirGetFacilityInfo
### Title: Downloads EPA ECHO permitted air emitter information
### Aliases: echoAirGetFacilityInfo

### ** Examples




cleanEx()
nameEx("echoAirGetMeta")
### * echoAirGetMeta

flush(stderr()); flush(stdout())

### Name: echoAirGetMeta
### Title: Downloads EPA ECHO Air Facility Metadata
### Aliases: echoAirGetMeta

### ** Examples




cleanEx()
nameEx("echoGetCAAPR")
### * echoGetCAAPR

flush(stderr()); flush(stdout())

### Name: echoGetCAAPR
### Title: Download EPA ECHO emissions inventory report data
### Aliases: echoGetCAAPR

### ** Examples





cleanEx()
nameEx("echoGetEffluent")
### * echoGetEffluent

flush(stderr()); flush(stdout())

### Name: echoGetEffluent
### Title: Downloads EPA ECHO DMR records of dischargers with NPDES permits
### Aliases: echoGetEffluent

### ** Examples




cleanEx()
nameEx("echoSDWGetMeta")
### * echoSDWGetMeta

flush(stderr()); flush(stdout())

### Name: echoSDWGetMeta
### Title: Downloads EPA ECHO Safe Drinking Water Facilities Metadata
### Aliases: echoSDWGetMeta

### ** Examples




cleanEx()
nameEx("echoSDWGetSystems")
### * echoSDWGetSystems

flush(stderr()); flush(stdout())

### Name: echoSDWGetSystems
### Title: Downloads public water system information
### Aliases: echoSDWGetSystems

### ** Examples




cleanEx()
nameEx("echoWaterGetFacilityInfo")
### * echoWaterGetFacilityInfo

flush(stderr()); flush(stdout())

### Name: echoWaterGetFacilityInfo
### Title: Downloads EPA ECHO water facility information
### Aliases: echoWaterGetFacilityInfo

### ** Examples





cleanEx()
nameEx("echoWaterGetMeta")
### * echoWaterGetMeta

flush(stderr()); flush(stdout())

### Name: echoWaterGetMeta
### Title: Downloads EPA ECHO Water Facility Metadata
### Aliases: echoWaterGetMeta

### ** Examples




cleanEx()
nameEx("echoWaterGetParams")
### * echoWaterGetParams

flush(stderr()); flush(stdout())

### Name: echoWaterGetParams
### Title: Search parameter codes for Clean Water Act permits on EPA ECHO
### Aliases: echoWaterGetParams

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
