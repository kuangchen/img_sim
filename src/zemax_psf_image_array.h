#ifndef _ZEMAX_PSF_IMAGE_ARRAY_H
#define _ZEMAX_PSF_IMAGE_ARRAY_H

#include <memory>
#include <string>
#include <src/zemax_psf_image.h>
#include <include/rect_grid.h>

using std::shared_ptr;
using std::string;
using rg::rect_grid;

namespace img_sim {

  class zemax_psf_image_array :public rect_grid<shared_ptr<zemax_psf_image> > {
  private:

  public:
    zemax_psf_image_array(const string &conf);
  };
}

#endif
