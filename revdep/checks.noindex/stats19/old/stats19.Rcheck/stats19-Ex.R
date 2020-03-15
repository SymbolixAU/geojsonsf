pkgname <- "stats19"
source(file.path(R.home("share"), "R", "examples-header.R"))
options(warn = 1)
library('stats19')

base::assign(".oldSearch", base::search(), pos = 'CheckExEnv')
base::assign(".old_wd", base::getwd(), pos = 'CheckExEnv')
cleanEx()
nameEx("accidents_sample")
### * accidents_sample

flush(stderr()); flush(stdout())

### Name: accidents_sample
### Title: Sample of stats19 data (2017 accidents)
### Aliases: accidents_sample accidents_sample_raw
### Keywords: datasets

### ** Examples




cleanEx()
nameEx("casualties_sample")
### * casualties_sample

flush(stderr()); flush(stdout())

### Name: casualties_sample
### Title: Sample of stats19 data (2017 casualties)
### Aliases: casualties_sample casualties_sample_raw
### Keywords: datasets

### ** Examples




cleanEx()
nameEx("check_year")
### * check_year

flush(stderr()); flush(stdout())

### Name: check_year
### Title: check and convert year argument
### Aliases: check_year

### ** Examples

# check_year("2018") # fails
# check_year(2017)
# check_year(2006)
# check_year(1985)



cleanEx()
nameEx("dl_stats19")
### * dl_stats19

flush(stderr()); flush(stdout())

### Name: dl_stats19
### Title: Download STATS19 data for a year or range of two years.
### Aliases: dl_stats19

### ** Examples




cleanEx()
nameEx("file_names")
### * file_names

flush(stderr()); flush(stdout())

### Name: file_names
### Title: stats19 file names for easy access
### Aliases: file_names file_names_old
### Keywords: datasets

### ** Examples

## Not run: 
##D  length(file_names)
##D  file_names$dftRoadSafetyData_Vehicles_2017.zip
## End(Not run)



cleanEx()
nameEx("find_file_name")
### * find_file_name

flush(stderr()); flush(stdout())

### Name: find_file_name
### Title: Find file names within stats19::file_names.
### Aliases: find_file_name

### ** Examples

find_file_name(2016)
find_file_name(2016, type = "Accidents")
find_file_name(1985, type = "Accidents")
find_file_name(type = "cas")
find_file_name(type = "accid")
find_file_name(2006)
find_file_name(2016:2017)



cleanEx()
nameEx("format_accidents")
### * format_accidents

flush(stderr()); flush(stdout())

### Name: format_accidents
### Title: Format STATS19 'accidents' data
### Aliases: format_accidents

### ** Examples




cleanEx()
nameEx("format_casualties")
### * format_casualties

flush(stderr()); flush(stdout())

### Name: format_casualties
### Title: Format STATS19 casualties
### Aliases: format_casualties

### ** Examples




cleanEx()
nameEx("format_column_names")
### * format_column_names

flush(stderr()); flush(stdout())

### Name: format_column_names
### Title: Format column names of raw STATS19 data
### Aliases: format_column_names

### ** Examples




cleanEx()
nameEx("format_ppp")
### * format_ppp

flush(stderr()); flush(stdout())

### Name: format_ppp
### Title: Convert STATS19 data into ppp (spatstat) format.
### Aliases: format_ppp

### ** Examples

if (requireNamespace("spatstat", quietly = TRUE)) {
  x_ppp = format_ppp(accidents_sample)
  spatstat::plot.ppp(spatstat::unmark(x_ppp))
}




cleanEx()
nameEx("format_sf")
### * format_sf

flush(stderr()); flush(stdout())

### Name: format_sf
### Title: Format convert STATS19 data into spatial (sf) object
### Aliases: format_sf

### ** Examples

x_sf = format_sf(accidents_sample)
sf:::plot.sf(x_sf)



cleanEx()
nameEx("format_vehicles")
### * format_vehicles

flush(stderr()); flush(stdout())

### Name: format_vehicles
### Title: Format STATS19 vehicles data
### Aliases: format_vehicles

### ** Examples




cleanEx()
nameEx("get_MOT")
### * get_MOT

flush(stderr()); flush(stdout())

### Name: get_MOT
### Title: Download vehicle data from the DVSA MOT API using VRM.
### Aliases: get_MOT

### ** Examples




cleanEx()
nameEx("get_data_directory")
### * get_data_directory

flush(stderr()); flush(stdout())

### Name: get_data_directory
### Title: Get data download dir
### Aliases: get_data_directory

### ** Examples

# get_data_directory()



cleanEx()
nameEx("get_stats19")
### * get_stats19

flush(stderr()); flush(stdout())

### Name: get_stats19
### Title: Download, read and format STATS19 data in one function.
### Aliases: get_stats19

### ** Examples




cleanEx()
nameEx("get_url")
### * get_url

flush(stderr()); flush(stdout())

### Name: get_url
### Title: Convert file names to urls
### Aliases: get_url

### ** Examples

# get_url(find_file_name(1985))



cleanEx()
nameEx("locate_one_file")
### * locate_one_file

flush(stderr()); flush(stdout())

### Name: locate_one_file
### Title: Pin down a file on disk from four parameters.
### Aliases: locate_one_file

### ** Examples




cleanEx()
nameEx("phrase")
### * phrase

flush(stderr()); flush(stdout())

### Name: phrase
### Title: Generate a phrase for data download purposes
### Aliases: phrase

### ** Examples

stats19:::phrase()



cleanEx()
nameEx("police_boundaries")
### * police_boundaries

flush(stderr()); flush(stdout())

### Name: police_boundaries
### Title: Police force boundaries in England (2016)
### Aliases: police_boundaries
### Keywords: datasets

### ** Examples

nrow(police_boundaries)
police_boundaries[police_boundaries$pfa16nm == "West Yorkshire", ]
sf:::plot.sf(police_boundaries)



cleanEx()
nameEx("read_accidents")
### * read_accidents

flush(stderr()); flush(stdout())

### Name: read_accidents
### Title: Read in STATS19 road safety data from .csv files downloaded.
### Aliases: read_accidents

### ** Examples




cleanEx()
nameEx("read_casualties")
### * read_casualties

flush(stderr()); flush(stdout())

### Name: read_casualties
### Title: Read in STATS19 road safety data from .csv files downloaded.
### Aliases: read_casualties

### ** Examples




cleanEx()
nameEx("read_vehicles")
### * read_vehicles

flush(stderr()); flush(stdout())

### Name: read_vehicles
### Title: Read in stats19 road safety data from .csv files downloaded.
### Aliases: read_vehicles

### ** Examples




cleanEx()
nameEx("select_file")
### * select_file

flush(stderr()); flush(stdout())

### Name: select_file
### Title: Interactively select from options
### Aliases: select_file

### ** Examples

# fnames = c("f1", "f2")
# stats19:::select_file(fnames)



cleanEx()
nameEx("set_data_directory")
### * set_data_directory

flush(stderr()); flush(stdout())

### Name: set_data_directory
### Title: Set data download dir
### Aliases: set_data_directory

### ** Examples

# set_data_directory("MY_PATH")



cleanEx()
nameEx("vehicles_sample")
### * vehicles_sample

flush(stderr()); flush(stdout())

### Name: vehicles_sample
### Title: Sample of stats19 data (2017 vehicles)
### Aliases: vehicles_sample vehicles_sample_raw
### Keywords: datasets

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
