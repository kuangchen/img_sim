#ifndef __RECT_GRID_H
#define __RECT_GRID_H

#include <memory>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <include/rect_grid_spec.h>
#include <boost/multi_array.hpp>
#include <iostream>

using std::shared_ptr;
using std::array;
using boost::multi_array;
using boost::extents;
using std::vector;
using std::numeric_limits;
using std::cout;
using rg::outside_spec;

namespace rg {
  typedef array<size_t, 2> v2i;
  typedef array<double, 3> v3d;
  typedef array<double, 2> v2d;
  
  template <class T> 
  class rect_grid: public multi_array<T, 2> {
  public:
    static const v2i outside_boundary;

  private:
    rect_grid_spec row;
    rect_grid_spec col;
    std::shared_ptr<multi_array<T, 2> > raw_data;
    vector<v2d> coord_list;
    vector<v2i> index_list;

  private:

  public:
    // Empty grid
    rect_grid() : row(), col(), raw_data() {}

    rect_grid(const rect_grid_spec &row, const rect_grid_spec &col):
      row(row), col(col), 
      raw_data(new multi_array<T, 2>(extents[row.size][col.size]))
      {
	for (size_t i=0; i<row.size; i++)
	  for (size_t j=0; j<col.size; j++) {
	    coord_list.push_back({col.orig+col.delta*j, row.orig+row.delta*i});
	    index_list.push_back({i, j});
	  }
      };

    bool empty() const { return col.size==0 && col.size==0; };

    inline const T* cbegin() const { return raw_data->origin(); };

    inline const T* cend() const { return raw_data->origin() + raw_data->num_elements(); }

    template <class K> void assign(const K& begin, const K& end) {
      raw_data->assign(begin, end);
    }

    const T& operator[] (const v2i &index) const {
      return (*raw_data)(index);
      //return (*raw_data)[index[1]][index[0]];
    };
    
    T& operator[] (const v2i &index) {
      return (*raw_data)(index);
//      return (*raw_data)[index[1]][index[0]];
    };
    
    const vector<v2d>& get_coord_list() const {
      return coord_list;
    }

    const vector<v2i>& get_index_list() const {
      return index_list;
    }

    inline size_t num_row() const { return row.size; };
    inline size_t num_col() const { return col.size; };
    
    inline double delta_row() const { return row.delta; }
    inline double delta_col() const { return col.delta; }

    const std::shared_ptr<multi_array<T, 2> >& data() const { 
      return raw_data; 
    }

    std::array<size_t, 2> nearest_neighbor(const v2d& coord) const {
      if (raw_data==false) 
	return outside_boundary;

      v2i nn = { row.nearest_neighbor(coord[1]), 
		 col.nearest_neighbor(coord[0]) };

      if (nn[0] == outside_spec || nn[1] == outside_spec)
	return outside_boundary;
      else
	return nn;
      // int n[2];
      
      // n[0] = static_cast<int>(floor((coord[0] - col.orig)/col.delta));
      // n[1] = static_cast<int>(floor((coord[1] - row.orig)/row.delta));

      // //cout << n[0] << "\t" << n[1] << "\n";
      // for (int i=0; i<2; i++)
      // 	if (n[i] < 0 || n[i] >= raw_data->shape()[1-i] - 1) 
      // 	  return outside_boundary;
       
      // return v2i({static_cast<size_t>(n[0]), 
      // 	    static_cast<size_t>(n[1])});
    }
    
    T eval_nearest_neighbor(const v2d& coord) const {
      if (raw_data==false)
	return T();

      v2i nn_idx = nearest_neighbor(coord);
      if (nn_idx == outside_boundary) 
	return T(0);
      
      else 
	return (*this)[nearest_neighbor(coord)];
    }

    
  };
    
  template <class T> const v2i rect_grid<T>::outside_boundary = { 
    numeric_limits<size_t>::max(), 
    numeric_limits<size_t>::max()
  };
  
}

#endif
