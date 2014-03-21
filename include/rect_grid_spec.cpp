#include <include/rect_grid_spec.h>
#include "boost/program_options.hpp" 
#include <fstream>
#include <cmath>

using std::ifstream;
using std::numeric_limits;


namespace po = boost::program_options; 
using namespace rg;

const size_t rg::outside_spec = numeric_limits<size_t>::max();

rect_grid_spec::rect_grid_spec(double orig, 
			       double delta, 
			       size_t size, 
			       bool center) :
  delta(delta), size(size) {
  orig = center ? orig - (size-1)/2.0 * delta : orig;
}

rect_grid_spec rg::extract_spec(const string &fname, const string &prefix) {
  ifstream is(fname);
  rect_grid_spec s;
  po::variables_map vm; 
  po::options_description desc("Configuration"); 
  desc.add_options()
    ((prefix+".orig").c_str(),  po::value<double>(&s.orig)->required(), "orig")
    ((prefix+".delta").c_str(), po::value<double>(&s.delta)->required(), "delta")
    ((prefix+".size").c_str(),  po::value<size_t>(&s.size)->required(), "size");
  
  po::store(po::parse_config_file(is, desc, true), vm); 
  po::notify(vm);

  return s;
}

size_t rect_grid_spec::nearest_neighbor(double x) const {
  double nn = (x - orig) / delta;
  if (nn < 0 || nn > size-1)
    return outside_spec;
  
  else 
    return static_cast<size_t>(floor(nn));
}
