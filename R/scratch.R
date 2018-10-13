#
# library(sf)
#
# sf1 <- sf::st_sf(geometry = sf::st_sfc(sf::st_point(c(0,0))))
# sf2 <- sf::st_sf(geometry = sf::st_sfc(sf::st_point(c(1,1))))
# sf3 <- sf::st_sf(geometry = sf::st_sfc(sf::st_linestring(matrix(1:6,ncol=2))))
# sf4 <- sf::st_sf(geometry = sf::st_sfc(sf::st_polygon()))
# sf5 <- sf::st_sf(geometry = sf::st_sfc(sf::st_point()))
# sf6 <- sf::st_sf(geometry = sf::st_sfc(sf::st_point(c(1,2,3))))
# sf7 <- sf::st_sf(geometry = sf::st_sfc(sf::st_linestring(matrix(1:6,ncol=3))))
# sf8 <- sf::st_sf(geometry = sf::st_sfc(sf::st_geometrycollection(x = list( sf::st_point(x = c(0,0)), sf::st_linestring(matrix(c(1,2,3,4), ncol = 2))))))
# sf9 <- sf::st_sf(geometry = sf::st_sfc(sf::st_multilinestring(x = list(sf::st_linestring(matrix(1:6, ncol = 3)), sf::st_linestring(matrix(3:11,ncol=3))))))
# ply1 <- sf::st_polygon(x = list(matrix(c(0,0,0,1,1,1,1,0,0,0), ncol= 2, byrow = T)))
# ply2 <- sf::st_polygon(x = list(matrix(c(2,2,2,3,3,3,3,2,2,2), ncol = 2, byrow = T)))
# sf10 <- sf::st_sf(geometry = sf::st_sfc(ply1))
# sf11 <- sf::st_sf(geometry = sf::st_sfc(sf::st_multipolygon(x = list(ply1, ply2))))
# sf12 <- sf::st_sf(geometry = sf::st_sfc(sf::st_multipoint(x = matrix(c(0,0,1,1),ncol = 2))))
# sf13 <- sf::st_sf(geometry = sf::st_sfc(sf::st_geometrycollection(x = list( sf::st_point(x = c(0,0)), sf::st_linestring(matrix(c(1,2,3,4), ncol = 2)), sf::st_point(), sf::st_multipolygon()))))
# sf14 <- sf::st_sf(geometry = sf::st_sfc(sf::st_geometrycollection(x = list( sf::st_point(x = c(0,0,0)), sf::st_linestring(matrix(c(1,2,1,3,4,1), ncol = 2)), sf::st_point(), sf::st_multipolygon()))))
#
#
# sf <- rbind(sf1, sf2, sf3, sf4, sf5, sf6, sf7, sf8, sf9, sf10, sf11, sf12, sf13, sf14)
# sf$id <- 1:13
# sf$val <- letters[1:13]

# js <- '{"type":"GeometryCollection","geometries":[{"type":"Polygon","coordinates":[[[0,0],[0,1],[1,1],[1,0],[0,0]]]}]}'
#
# sf <- sf::st_sf( geometry = sf::st_sfc( sf::st_geometrycollection( x = list( sf::st_polygon( x = list( matrix(c(0,0,0,1,1,1,1,0,0,0), ncol = 2, byrow = T ) ))))))
#
# str( sf )
#
# str( geojson_sf( js ) )

# geojsonsf:::sf_to_geojson( sf )
#
# jsonify::validate_json( geojsonsf:::sf_to_geojson( sf ) )
#
# sf_geojson( sf[1:3,] )
# sf_geojson( sf , atomise = T )

# ## int vs numeric
# pt <- sf::st_sf(geometry = sf::st_sfc(sf::st_point(c(1L,1L))))
# geojsonsf:::test_sf_to_json( pt )
# pt <- sf::st_sf(geometry = sf::st_sfc(sf::st_point(c(1,1))))
# geojsonsf:::test_sf_to_json( pt )
#
#
# # #
# # # geojsonsf:::test_sf_to_json( sf[8, ])
# # # jsonify::validate_json( geojsonsf:::test_sf_to_json( sf[1, ]) )
# # #
# # #
# # # sf <- geojsonsf::geojson_sf( "http://eric.clst.org/assets/wiki/uploads/Stuff/gz_2010_us_050_00_500k.json" )
# # #
# # # library(microbenchmark)
# # #
# # # microbenchmark(
# # # 	new = { geo1 <- geojsonsf:::test_sf_to_json( sf ) },
# # # 	old = { geo2 <- geojsonsf::sf_geojson( sf ) },
# # # 	times = 10
# # # )
# # # Unit: milliseconds
# # # expr       min        lq      mean    median        uq       max neval
# # #  new  295.4253  305.2067  353.1528  329.7259  384.4229  491.3823    10
# # #  old 1339.2306 1392.2578 1410.1997 1396.9011 1421.0761 1517.5825    10
# #
# #
# #
# #
