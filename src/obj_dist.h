#ifndef __OBJ_DIST_H
#define __OBJ_DIST_H

#include <string>
#include <vector>
#include <exception>
#include <include/rect_grid.h>

using rg::v3d;
using std::string;
using std::exception;
using std::istream;
using std::ostream;

namespace img_sim {

  class obj_dist {
  private:
    class obj_dist_exception: public exception {
    private:
      string filename;
      string description;
      
    public:
      obj_dist_exception(const string &f, const string &d): filename(f),
							    description(d) {}
      virtual const char* what() const throw() {
	return (string("Error reading ") + filename + description).c_str();
      }
	  
    };

  private:
    vector<string> symbol_list;
    vector<v3d> obj_coord_list;
    string label_str;

  public:
    obj_dist();
    ~obj_dist();

    obj_dist(const obj_dist& obj_dist) {}; 
    const obj_dist& operator= (const obj_dist& obj_dist) {};

    void init(const string& conf);
    
    const vector<v3d>& get_obj_coord_list() const;
    const string& label() const;

    friend istream& operator>> (istream& os, obj_dist& obj);
    friend ostream& operator<< (ostream& os, const obj_dist& obj);
  };

}

#endif
