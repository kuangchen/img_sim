#ifndef __psf_H
#define __psf_H

#include <src/obj_dist.h>
#include <string>
#include <include/types.h>
#include <src/screen.h>
#include <src/zemax_psf_image_array.h>
#include <include/rect_grid.h>

using std::string;
using rg::v2i;
using rg::v2d;
using rg::v3d;

namespace img_sim {

  class psf {
  private:
    zemax_psf_image_array img_array;

  private:
    void rotate(const v3d &obj, const v2d &img, 
		v3d &new_obj, v2d &new_img);

    const static double epsilon;

  public:
    psf(const string &conf);

    void simulate(const obj_dist& o, screen& s);

    double eval(const v3d& obj_coord, const v2d& img_coord);
  };


  // class psf {
  // private:

  // public:
  //   psf() {};
  //   virtual double Eval(const v3d obj, const v2d img) = 0;

  //   void SimImage(const vector<v3d> &obj_list, 
  // 		  const vector<v2d> &img_list, 
  // 		  vector<double> &intensity);

  // };

}

#endif
