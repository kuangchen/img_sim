#include <src/zemax_psf_image.h>
#include <iostream>
#include <fstream>
#include "boost/program_options.hpp" 
#include <include/rect_grid_spec.h>

using namespace img_sim;
using std::ifstream;
using std::istream_iterator;
namespace po = boost::program_options; 
using rg::extract_spec;

zemax_psf_image::zemax_psf_image() :
  rect_grid<double>()
{}

zemax_psf_image::zemax_psf_image(const string &conf, 
				 const string &data):
  rect_grid(extract_spec(conf, "row"), 
	    extract_spec(conf, "col")) {

  ifstream is(data.c_str());
  istream_iterator<double> begin(is), end;
  assign(begin, end);
}
	    

