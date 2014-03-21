#ifndef __SCREEN_H
#define __SCREEN_H

#include <vector>
#include <string>
#include <include/rect_grid.h>

using std::string;
using rg::rect_grid;
using rg::rect_grid_spec;


namespace img_sim {

  class screen: public rect_grid<double> {
  private:
    class normalizer {
    public:
      double m;
    public:
      normalizer(double mm) : m(mm) {};
      
      unsigned char operator() (const double x) { 
	return static_cast<unsigned char>(x/m * 255); 
      };
    };


  public:
    screen(const string& conf);
    void save_img(const string& fname, double m, bool annotate=false,
      bool add_border=false);
    double max() const;
  };

}


#endif
