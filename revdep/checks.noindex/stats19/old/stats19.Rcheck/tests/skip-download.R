# To run download functions you need an internet connection.
# pref a fast one
skip_download = function() {
  if(!curl::has_internet() |
     identical(Sys.getenv("DONT_DOWNLOAD_ANYTHING"), "true"))
    skip("No connection to run download function.")
}
