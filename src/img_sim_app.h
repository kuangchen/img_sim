#ifndef _IMG_SIM_APP_H
#define _IMG_SIM_APP_H

#include <memory>
#include <vector>
#include <string>
#include <src/psf.h>
#include <src/screen.h>
#include <src/obj_dist.h>

using std::shared_ptr;

namespace img_sim {

  class img_sim_app {
  private:
    enum status { 
      success = 0, 
      error_in_cmd_line = 1,
      error_unhandled_exception = 2
    };

  private:
    bool display;
    std::shared_ptr<psf> p;
    std::shared_ptr<screen> s;
    vector<obj_dist> obj_dist_list;

  public:
    img_sim_app();
    ~img_sim_app();

    int parse(int argc, char** argv);
    int run();

  private:
    img_sim_app(const img_sim_app& app);
    img_sim_app& operator=(const img_sim_app& app);
  };

}

#endif
