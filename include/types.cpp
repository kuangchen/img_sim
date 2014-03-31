#include <include/types.h>
#include <iostream>

namespace rg {

  using std::istream;
  using std::ostream;

  istream& operator>> (istream &is, v3d &v) {
    is >> v[0] >> v[1] >> v[2];
    return is;
  }

  ostream& operator<< (ostream &os, const v3d &v) {
    os << v[0] << v[1] << v[2];
    return os;
  }

}
