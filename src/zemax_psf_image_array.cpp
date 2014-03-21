#include <src/zemax_psf_image_array.h>
#include <include/rect_grid_spec.h>
#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>
#include <boost/format.hpp> 


namespace po = boost::program_options; 

using namespace img_sim;
using boost::format;
using std::cout;
using rg::v2i;
using rg::extract_spec;
using std::ifstream;
using std::stringstream;

zemax_psf_image_array::zemax_psf_image_array(const string &fname) : 
  rect_grid< shared_ptr<zemax_psf_image> >(extract_spec(fname, "row"),
					   extract_spec(fname, "col")) {

  ifstream is(fname);
  string data_fname_pattern, conf_fname_pattern;
  po::variables_map vm; 
  po::options_description desc("Configuration"); 
  desc.add_options()
    ("pattern.data_fname",  po::value<string>(&data_fname_pattern)->required(), "data fname pattern")
    ("pattern.conf_fname",  po::value<string>(&conf_fname_pattern)->required(), "conf fname pattern");

  po::store(po::parse_config_file(is, desc, true), vm); 
  po::notify(vm);

  format conf_fmt(conf_fname_pattern), data_fmt(data_fname_pattern);

  for (const v2i& index: get_index_list() ) {
    size_t i = index[0];
    size_t j = index[1];
    (*this)[index].reset(new zemax_psf_image((conf_fmt % i % j).str(), 
					     (data_fmt % i % j).str()));
  }
  
}
