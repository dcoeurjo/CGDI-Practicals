#include <vector>
#include <array>
#include <polyscope/polyscope.h>
#include <polyscope/point_cloud.h>
#include <polyscope/surface_mesh.h>

int main(int argc, char **argv)
{
  // Initialize polyscope
  polyscope::init();

  //Some data
  std::vector<std::array<double, 3>> pts={{0,0,0}, {0,0,1}, {0,1,0}, {1,0,0}, {1,1,0},{0,1,1},{1,0,1},{1,1,1}};
  std::vector<double> values = {0.3, 3.4, 0.2, 0.4, 1.2, 4.0,3.6,5.0};
 
  auto pcl = polyscope::registerPointCloud("My Points", pts);
  pcl->addScalarQuantity("Some values", values);
 
  // Give control to the polyscope gui
  polyscope::show();

  return EXIT_SUCCESS;
}
