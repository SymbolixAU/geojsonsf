
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <cstdio>

#include <Rcpp.h>

using namespace Rcpp;
using namespace rapidjson;

// [[Rcpp::export]]
void rcpp_stream_in(std::string url) {

	//FILE* fp = fopen("http://eric.clst.org/assets/wiki/uploads/Stuff/gz_2010_us_050_00_500k.json", "rb"); // non-Windows use "r"
	//char readBuffer[65536];
	//FileReadStream is(fp, readBuffer, sizeof(readBuffer));
  //Document d;
	//d.ParseStream(is);
	//fclose(fp);

}

