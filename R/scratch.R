#
#
# library(sf)
#
# pt1 <- sf::st_sf( geometry = sf::st_sfc( sf::st_point(c(0,0))))
# mp1 <- sf::st_sf( geometry = sf::st_sfc( sf::st_multipoint(x = matrix(1:6, ncol = 2))))
# mp2 <- sf::st_sf( geometry = sf::st_sfc( sf::st_multipoint(x = matrix(1:6, ncol = 3))))
# mp3 <- sf::st_sf( geometry = sf::st_sfc( sf::st_multipoint(x = matrix(1:8, ncol = 4))))
# pt2 <- sf::st_sf( geometry = sf::st_sfc( sf::st_point(c(1,1,3,4))))
# ls1 <- sf::st_sf( geometry = sf::st_sfc( sf::st_linestring(x = matrix(1:6, ncol = 2))))
# ls2 <- sf::st_sf( geometry = sf::st_sfc( sf::st_linestring(x = matrix(1:6, ncol = 3))))
# mls1 <- sf::st_sf( geometry = sf::st_sfc( sf::st_multilinestring(x = list(matrix(1:6, ncol = 2), matrix(6:1, ncol = 2), matrix(1:6, ncol = 2)))))
#
# js <- '{"type":"MultiPolygon","coordinates":[[[[0.0,0.0],[0.0,1.0],[1.0,1.0],[1.0,0.0],[0.0,0.0]],[[0.5,0.5],[0.5,0.75],[0.75,0.75],[0.75,0.5],[0.5,0.5]]],[[[2.0,2.0],[2.0,3.0],[3.0,3.0],[3.0,2.0],[2.0,2.0]]]]}'
# mp <- geojson_sf( js )
# sf::st_crs( mp ) <- sf::st_crs( mls1 )
#
# sf <- rbind(pt1, mp1, mp2, mp3, pt2, ls1, ls2, mls1, mp)
# sf$id <- 1:nrow(sf)
#
# sf_geojson( sf )
#
#
# geojsonsf:::rcpp_sf_to_geojson_downcast( sf[1, ] )
# geojsonsf:::rcpp_sf_to_geojson_downcast( sf[2, ] )
#
# geojsonsf:::rcpp_sf_to_geojson_downcast( sf[9, ] )
#
#
#
# nc <- st_read(system.file("shape/nc.shp", package="sf"))
# nc_poly <- sf::st_cast( nc, to = "POLYGON" )
#
# geo <- geojsonsf:::rcpp_sf_to_geojson_downcast( nc )
# sf <- geojsonsf::geojson_sf( geo )
#
# sf
# nc_poly
#
# geojsonsf:::rcpp_sf_to_geojson_downcast( nc[4, ])
#
#
# nc <- sf::st_read(system.file("shape/nc.shp", package="sf"))
#
# geo_down <- geojsonsf:::rcpp_sf_to_geojson_downcast( nc )
# sf_down <- geojsonsf::geojson_sf( geo_down )
#
# library(microbenchmark)
#
# microbenchmark(
# 	sf = {
# 		nc_poly <- sf::st_cast( nc, to = "POLYGON")
# 		geo_poly <- geojsonsf::sf_geojson( nc_poly )
# 	},
# 	geojsonsf = {
# 		geo_sf <- geojsonsf:::rcpp_sf_to_geojson_downcast( nc )
# 	},
# 	times = 5
# )
#
# # Unit: milliseconds
# #      expr       min        lq      mean    median        uq       max neval
# #        sf 16.019968 16.952798 20.264359 17.283295 19.396397 31.669338     5
# # geojsonsf  2.348934  2.597222  3.203101  2.847933  3.017071  5.204344     5
#
# microbenchmark(
# 	sf = {
# 		nc_poly <- sf::st_cast( nc, to = "POLYGON")
# 		geo_poly <- geojsonsf::sf_geojson( nc_poly )
# 	},
# 	geojsonsf = {
# 		geo_sf <- geojsonsf:::rcpp_sf_to_geojson_downcast( nc )
# 		nc2 <- geojsonsf::geojson_sf( geo_sf )
# 	},
# 	times = 5
# )
#
# # Unit: milliseconds
# #      expr      min       lq     mean   median       uq      max neval
# #        sf 13.75293 14.42003 16.96273 14.93394 15.38814 26.31861     5
# # geojsonsf 10.78687 11.34112 11.60321 11.63283 11.75583 12.49937     5
#
# sf$geometry
#
# types <- vapply(sf$geometry, function(x) class(x)[[2]], "")
# downcast <- gsub("MULTI","",types)
#
# types[ types != downcast ]
#
# matrix(c(types, downcast), ncol = 2)
#
# ## given the geometry type (MULTIPIONT, MULTILINESTRING, MULTIPOLYGON)
# ## calculate how many of each POINT, LINESTRING, POLYGON are within the MULTI
#
# dim( sf[2, 'geometry'][[1]][[1]] )
#
# dim( sf[8, 'geometry'][[1]][[1]][[1]] )
#
#
# library(Rcpp)
#
# ##
#
# cppFunction('int mls_multiplier( Rcpp::List mls ) {
#   int multiplier = 1;
#   return mls.size();
# }')
#
# mls_multiplier( sf[8, ]$geometry[[1]] )
#
# cppFunction('int mp_multiplier( Rcpp::NumericMatrix mp ){
#   return mp.nrow();
# }')
#
# mp_multiplier( sf[2, ]$geometry[[1]] )
# mp_multiplier( sf[3, ]$geometry[[1]] )
# mp_multiplier( sf[4, ]$geometry[[1]] )
#
# cppFunction('int mpoly_multiplier( Rcpp::List mp ){
#
#   Rcpp::List pl = mp[0];
#   return pl.size();
#
#   return mp.size();
#   int multiplier = 1;
#   for( int i = 0; i < mp.size(); i++ ) {
#     Rcpp::List poly = mp[i];
#     multiplier = multiplier + poly.size();
#   }
#   return multiplier;
# }')
#
# mpoly_multiplier( sf[9, ]$geometry )
#
# mpoly_multiplier( nc[4, ]$geometry )
#
# sf_geojson(sf[9,])
