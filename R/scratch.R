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
#
# sf <- rbind(sf1, sf2, sf3, sf4, sf5, sf6, sf7)
# sf$id <- 1:7
# sf$val <- letters[1:7]
#
# geojsonsf:::test_sf_to_json( sf )
# sf_geojson( sf )
# sf_geojson( sf , atomise = T )
