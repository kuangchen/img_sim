#ifndef _ZEMAX_PSF_IMAGE_H
#define _ZEMAX_PSF_IMAGE_H

#include <string>
#include <include/rect_grid.h>

using rg::rect_grid;
using rg::rect_grid_spec;
using std::string;

namespace img_sim {
  
  class zemax_psf_image : public rect_grid<double> {
  public:

  private:

  public:
    zemax_psf_image();
    zemax_psf_image(const string &conf, const string &data);
  };

}

#endif
