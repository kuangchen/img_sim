#include <src/img_sim_app.h>

using namespace img_sim;

int main(int argc, char** argv) {
  img_sim_app app;
  app.parse(argc, argv);
  return app.run(); 
}
