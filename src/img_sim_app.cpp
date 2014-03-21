#include <src/img_sim_app.h>

#include "boost/filesystem.hpp"
#include "boost/program_options.hpp" 

#include <string>
#include <iostream>
#include <exception>

#include "CImg.h"

using namespace img_sim;
using namespace cimg_library;
namespace po = boost::program_options; 
namespace fs = boost::filesystem; 


img_sim_app::img_sim_app() {}
img_sim_app::~img_sim_app() {}

int img_sim_app::parse(int argc, char** argv) {
  string psf_conf_fname;
  string screen_conf_fname;
  vector<string> obj_dist_fname_list;

  po::variables_map vm; 

  try {
    po::options_description desc("Options"); 
    desc.add_options() 
      ("help", "Print help messages")
      ("psf,p", po::value<string>(&psf_conf_fname)->required(), 
       "Point spread function")
      ("screen,s", po::value<string>(&screen_conf_fname)->required(), "Screen conf")
      ("obj,o", po::value< vector<string> >(&obj_dist_fname_list)->multitoken(), 
       "Object xyz file list")
      ("display,d", "Display image")
      ("verbose,v", "Verbose");


    try { 
      po::store(po::parse_command_line(argc, argv, desc), vm); // can throw 
 
      if ( vm.count("help")  ) {
        std::cout << "Basic Command Line Parameter App" << std::endl 
                  << desc << std::endl; 
        return success; 
      } 
 
      po::notify(vm); // throws on error, so do after help in case 
                      // there are any problems 
    } 
    catch(po::error& e) { 
      std::cerr << "ERROR: " << e.what() << std::endl << std::endl; 
      std::cerr << desc << std::endl; 
      return error_in_cmd_line; 
    } 

    catch(std::exception& e) { 
      std::cerr << "Unhandled Exception reached the top of main: " 
		<< e.what() << ", application will now exit" << std::endl; 
      return error_unhandled_exception; 
 
    }
  } 
  catch(std::exception& e) { 
    std::cerr << "Unhandled Exception reached the top of main: " 
              << e.what() << ", application will now exit" << std::endl; 
    return error_unhandled_exception; 
  } 

  p.reset(new psf(psf_conf_fname));
  s.reset(new screen(screen_conf_fname));
  obj_dist_list.resize(obj_dist_fname_list.size());

  for (int i=0; i<obj_dist_list.size(); i++)
    obj_dist_list[i].init(obj_dist_fname_list[i]);

  display = static_cast<bool>(vm.count("display"));
  return success;
}


int img_sim_app::run() {
  vector<double> val;

  for (auto &obj_dist: obj_dist_list) {
    p->simulate(obj_dist, (*s));
    s->save_img(obj_dist.label() + ".pgm", s->max(), true);
  }
  
  return success;
}
