#include <algorithm>
#include <src/psf.h>
#include <src/screen.h>


using namespace std;
using namespace img_sim;

const double psf::epsilon = 1e-18;

psf::psf(const string &conf): img_array(conf) {}

void psf::simulate(const obj_dist &o, screen &s) {
  vector<double> vv;

  for (auto &img_coord: s.get_coord_list() ) {
    vector<double> v;

    for (auto &obj_coord: o.get_obj_coord_list()) 
      v.push_back(eval(obj_coord, img_coord));

    vv.push_back(accumulate(v.begin(), v.end(), 0.0));
  }

  s.assign(vv.begin(), vv.end());
}


void psf::rotate(const v3d &obj, const v2d &img, v3d &new_obj, v2d &new_img) {
  double len = sqrt(obj[0] * obj[0] + obj[1] * obj[1]);

  new_obj[0] = len;
  new_obj[1] = 0;
  new_obj[2] = obj[2];

  if (len < epsilon) new_img = img;
  
  else {
    double c = obj[0] / len;
    double s = obj[1] / len;
    double cc = img[0];
    double ss = img[1];
    new_img[0] = cc * c + ss * s;
    new_img[1] = ss * c - cc * s;
  }

}

double psf::eval(const v3d& obj_coord, const v2d& img_coord) {
  v3d new_obj_coord_;
  v2d new_img_coord;

  rotate(obj_coord, img_coord, new_obj_coord_, new_img_coord);
  v2d new_obj_coord;
  
  new_obj_coord[0] = new_obj_coord_[0];
  new_obj_coord[1] = new_obj_coord_[2];

  shared_ptr<zemax_psf_image> p = img_array.eval_nearest_neighbor(new_obj_coord);
  if (p==NULL) 
    return 0;
  else 
    return p->eval_nearest_neighbor(new_img_coord);


  // vector<double> wgt;
  // vector<zemax_psf_image**> nn_sites;
  // std::array<size_t, 2> nn_sites = image_array->nearest_neighbor(new_obj_coord);
  // //image_array->nn(new_obj_coord, nn_sites, wgt);

  // vector<double> vv;
  // vector<double> wgt2;
  // vector<double*> nn_sites2;

  // for (auto &site: nn_sites) {
  //   wgt2.clear();
  //   nn_sites2.clear();
    
  //   (*site)->nn(new_img_coord, nn_sites2, wgt2);
  //   double sum = 0;
  //   for (int i=0; i<nn_sites2.size(); i++)
  //     sum += (*nn_sites2[i] * wgt2[i]);

  //   vv.push_back(sum);
  // }

  // return inner_product(vv.begin(), vv.end(), wgt.begin(), 0.0);
}  


