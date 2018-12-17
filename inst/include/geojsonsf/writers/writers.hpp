#ifndef GEOJSONSF_SF_GEOJSON_H
#define GEOJSONSF_SF_GEOJSON_H

#include <Rcpp.h>

namespace geojsonsf {
namespace writers {

  template< typename Writer >
  inline void start_feature_collection( Writer& writer ) {
    writer.String("type");
    writer.String("FeatureCollection");
    writer.String("features");
  }

  template< typename Writer >
  inline void start_features( Writer& writer ) {
    writer.String("type");
    writer.String("Feature");
  }

  template< typename Writer >
  inline void start_properties( Writer& writer ) {
    writer.String("properties");
  }

  template< typename Writer >
  inline void write_coordinate_string( Writer& writer ) {
    writer.String("coordinates");
  }

  template< typename Writer >
  inline void begin_geojson_geometry( Writer& writer, std::string& geom_type ) {
    writer.StartObject();
    writer.String("type");
    if (geom_type == "POINT") {
      writer.String("Point");
      write_coordinate_string( writer );
    } else if (geom_type == "MULTIPOINT") {
      writer.String("MultiPoint");
      write_coordinate_string( writer );
      writer.StartArray();
    } else if (geom_type == "LINESTRING") {
      writer.String("LineString");
      write_coordinate_string( writer );
      writer.StartArray();
    } else if (geom_type == "MULTILINESTRING") {
      writer.String("MultiLineString");
      write_coordinate_string( writer );
      writer.StartArray();
      writer.StartArray();
    } else if (geom_type == "POLYGON") {
      writer.String("Polygon");
      write_coordinate_string( writer );
      writer.StartArray();
      writer.StartArray();
    } else if (geom_type == "MULTIPOLYGON") {
      writer.String("MultiPolygon");
      write_coordinate_string( writer );
      writer.StartArray();
      writer.StartArray();
      writer.StartArray();
    } else if (geom_type == "GEOMETRYCOLLECTION") {
      writer.String("GeometryCollection");
      writer.String("geometries");
      writer.StartArray();
    }
  }

  template< typename Writer >
  inline void end_geojson_geometry(Writer& writer, std::string& geom_type) {
    if (geom_type == "POINT") {
      writer.EndObject();
    } else if (geom_type == "MULTIPOINT") {
      writer.EndArray();
      writer.EndObject();
    } else if (geom_type == "LINESTRING") {
      writer.EndArray();
      writer.EndObject();
    } else if (geom_type == "MULTILINESTRING") {
      writer.EndArray();
      writer.EndArray();
      writer.EndObject();
    } else if (geom_type == "POLYGON") {
      writer.EndArray();
      writer.EndArray();
      writer.EndObject();
    } else if (geom_type == "MULTIPOLYGON") {
      writer.EndArray();
      writer.EndArray();
      writer.EndArray();
      writer.EndObject();
    } else if (geom_type == "GEOMETRYCOLLECTION") {
      writer.EndArray();
      writer.EndObject();
    }
  }

  template< typename Writer >
  inline void polygon_separator( Writer& writer, int i, int n ) {
    if (i < ( n - 1 ) ) {
      writer.EndArray();
      writer.EndArray();
      writer.StartArray();
      writer.StartArray();
    }
  }

  template< typename Writer >
  inline void line_separator( Writer& writer, int i, int n) {
    if ( i < ( n - 1 ) ) {
      writer.EndArray();
      writer.StartArray();
    }
  }

  template< typename Writer >
  inline void points_to_geojson( Writer& writer, Rcpp::IntegerVector& point, int& digits ) {
    int n = point.size();
    int i;
    writer.StartArray();
    for ( i = 0; i < n; i++ ) {
      writer.Int( point[i] );
    }
    writer.EndArray();
  }

  template< typename Writer >
  inline void points_to_geojson( Writer& writer, Rcpp::NumericVector& point, int& digits ) {
    int n = point.size();
    int i;
    double value;
    writer.StartArray();
    for ( i = 0; i < n; i++ ) {
    value = point[i];

    	if ( digits >= 0 ) {
    		double e = std::pow( 10.0, digits );
    		value = round( value * e ) / e;
    	}
    	writer.Double( value );
    }
    writer.EndArray();
  }

  template< typename Writer >
  inline void points_to_geojson( Writer& writer, SEXP& point, int& digits ) {
    switch( TYPEOF( point ) ) {
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( point );
      points_to_geojson( writer, iv, digits );
      break;
    }
    case REALSXP: {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( point );
      points_to_geojson( writer, nv, digits );
    break;
    }
    }
  }

  template< typename Writer >
  inline void linestring_to_geojson( Writer& writer, Rcpp::IntegerMatrix& line, int& digits ) {
    int i;
    int nrow = line.nrow();
    for ( i = 0; i < nrow; i++ ) {
      Rcpp::IntegerVector this_row = line(i, Rcpp::_ );
      points_to_geojson( writer, this_row, digits );
    }
  }

  template< typename Writer >
  inline void linestring_to_geojson( Writer& writer, Rcpp::NumericMatrix& line, int& digits ) {
    int i;
    int nrow = line.nrow();
    for ( i = 0; i < nrow; i++ ) {
      Rcpp::NumericVector this_row = line(i, Rcpp::_ );
      points_to_geojson( writer, this_row, digits );
    }
  }

  template< typename Writer >
  inline void linestring_to_geojson( Writer& writer, SEXP& line, int& digits ) {
    switch( TYPEOF( line ) ) {
    case INTSXP: {
      Rcpp::IntegerMatrix iv = Rcpp::as< Rcpp::IntegerMatrix >( line );
      linestring_to_geojson( writer, iv, digits );
      break;
    }
    case REALSXP: {
      Rcpp::NumericMatrix nv = Rcpp::as< Rcpp::NumericMatrix >( line );
      linestring_to_geojson( writer, nv, digits );
      break;
    }
    }
  }

  template< typename Writer >
  inline void polygon_to_geojson( Writer& writer, Rcpp::List& sfg, int& digits ) {
    int i;
    int n = sfg.size();
    for ( i = 0; i < n; i++ ) {
      Rcpp::NumericMatrix sfgi = sfg[i];
      linestring_to_geojson( writer, sfgi, digits );
      line_separator( writer, i, n );
    }
  }

  template< typename Writer >
  inline void multi_polygon_to_geojson( Writer& writer, Rcpp::List& sfg, int& digits ) {
    int i;
    int n = sfg.size();
    for ( i = 0; i < n; i++ ) {
      Rcpp::List sfgi = sfg[i];
      polygon_to_geojson( writer, sfgi, digits );
      polygon_separator( writer, i, n );
    }
  }

} // namespace writers
} // namespace geojsonsf

#endif
