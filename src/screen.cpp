#include <algorithm>
#include <iostream>
#include <fstream>
#include <cmath>
#include <array>
#include <src/screen.h>
#include <iomanip>  
#include "boost/program_options.hpp" 

#include "CImg.h"

using namespace cimg_library;

using std::setprecision;
using std::copy;
using std::max_element;
using std::transform;
using boost::multi_array;
using std::stringstream;

using std::array;
using namespace img_sim;
namespace po = boost::program_options; 
using rg::extract_spec;

screen::screen(const string &conf):
  rect_grid<double>(extract_spec(conf, "row"),
		    extract_spec(conf, "col"))
{}

double screen::max() const {
  return *max_element(cbegin(), cend());
}

void screen::save_img(const string& fname, 
		      double m, 
		      bool annotate,
		      bool add_border
  ) {
  CImg<unsigned char> img(num_col(), num_row(), 1, 1, 0);
  transform(cbegin(), cend(), img.begin(), screen::normalizer(m));

  if (annotate) {
    unsigned char white[] = { 255, 255 ,255 };      // Define a purple color
    
    size_t x = num_col()/10;
    size_t y = num_row()/10;
    img.draw_line(x, y, x+20, y, white);
    img.draw_line(x, y, x, y+20, white);

    stringstream ss;
    ss << setprecision(2) << fabs(delta_col()) * 1e6 << " um";
    img.draw_text(x+10, y-15, ss.str().c_str(), white);

    ss.str("");
    ss << setprecision(2) << fabs(delta_row()) * 1e6 << " um";
    img.draw_text(x-15, y+10, ss.str().c_str(), white);
  }

  if (add_border) {
    
  }

  img.save(fname.c_str());
  img.display();
}
