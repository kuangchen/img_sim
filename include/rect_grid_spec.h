#ifndef __RECT_GRID_SPEC_H
#define __RECT_GRID_SPEC_H

#include <cstddef>
#include <string>


using std::size_t;
using std::string;

namespace rg {
  
  extern const size_t outside_spec;

  typedef struct rect_grid_spec {
  public:
    double orig;
    double delta;
    size_t size;
    
  public:
    rect_grid_spec(double orig=0, double delta=0, size_t size=0, bool center=false);
    size_t nearest_neighbor(double x) const;

  } rect_grid_spec;

  rect_grid_spec extract_spec(const string& fname, const string &prefix);
  
}

#endif
