#
# library(sf)
#
# sf <- sf::st_sf(geometry = sf::st_sfc(sf::st_point(c(0,0))))
# sf2 <- sf::st_sf(geometry = sf::st_sfc(sf::st_point(c(1,1))))
# sf3 <- sf::st_sf(geometry = sf::st_sfc(sf::st_linestring(matrix(1:6,ncol=2))))
# sf <- rbind(sf, sf2, sf3)
# sf$id <- 1:3
# sf$val <- letters[1:3]
#
# geojsonsf:::test_sf_to_json( sf )
# sf_geojson( sf )
# sf_geojson( sf , atomise = T )
