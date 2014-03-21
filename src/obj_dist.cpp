#include <src/obj_dist.h>

#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>

#include "boost/filesystem.hpp"

using namespace std;
using namespace img_sim;

namespace fs = boost::filesystem;

obj_dist::obj_dist():
  symbol_list(0),
  obj_coord_list(0),
  label_str()
{}

obj_dist::~obj_dist() {}

const vector<v3d>& obj_dist::get_obj_coord_list() const { 
  return obj_coord_list; 
};

const string& obj_dist::label() const { 
  return label_str; 
};

void obj_dist::init(const string &conf) {
  fs::path p(conf);
  label_str = fs::basename(p);

  ifstream is(conf.c_str());
  while (is >> (*this)) {}
}

namespace img_sim {

  ostream& operator<< (ostream& os, const obj_dist& obj) {
   for (int i=0; i<obj.symbol_list.size(); i++) {
      os << obj.symbol_list[i] << "\t";
      for (int j=0; j<3; j++)
	os << obj.obj_coord_list[i][j] << "\t";
      os << endl;
    }
    return os;
  }

  istream& operator>> (istream& is, obj_dist& obj) {
    is.exceptions(istream::badbit | istream::failbit);
    
    size_t size;
    string comment;

    // need to eat the newline character
    try {
      is >> size >> ws >> comment >> ws;
      
      string l;
      stringstream ss;
      ss.exceptions(stringstream::badbit);

      string symbol;
      v3d obj_coord;

      for (int i=0; i<size; i++) {
	getline(is, l);
	ss.str(l);

	ss >> symbol;

	copy(istream_iterator<double>(ss), 
	     istream_iterator<double>(), 
	     obj_coord.begin());

	obj.symbol_list.push_back(symbol);
	obj.obj_coord_list.push_back(obj_coord);
    
	ss.clear();
      }
    }
//    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    catch (const ifstream::failure &e) {
      return is;
    }
    
    return is;

  }
}
