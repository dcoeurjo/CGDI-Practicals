
#include "geometrycentral/surface/manifold_surface_mesh.h"
#include "geometrycentral/surface/meshio.h"
#include "geometrycentral/surface/vertex_position_geometry.h"

#include "polyscope/polyscope.h"
#include "polyscope/surface_mesh.h"
#include "polyscope/point_cloud.h"

using namespace geometrycentral;
using namespace geometrycentral::surface;

// == Geometry-central data
std::unique_ptr<ManifoldSurfaceMesh> mesh;
std::unique_ptr<VertexPositionGeometry> geometry;

int counter=0;

void oneStep()
{
  for(size_t i = 0; i < mesh->nVertices(); ++i)
    geometry->vertexPositions[i] = geometry->vertexPositions[i] + Vector3::constant(0.01*sin(i*counter/(2.0*M_PI)));
}

bool go=false;

void myCallback()
{
  if (ImGui::Button("Go!"))
    go= !go;
  
  if (go)
  {
    oneStep();
    polyscope::getSurfaceMesh("Input obj")->updateVertexPositions(geometry->vertexPositions);
   // polyscope::screenshot();
  }
  counter++;
}



int main(int argc, char **argv) {

  // Initialize polyscope
  polyscope::init();

  // Load mesh
  std::tie(mesh, geometry) = readManifoldSurfaceMesh(argv[1]);

  // Register the mesh with polyscope
  polyscope::registerSurfaceMesh("Input obj",
                                 geometry->inputVertexPositions,
                                 mesh->getFaceVertexList(),
                                 polyscopePermutations(*mesh));
  
  
  geometry->requireVertexPositions();
 
  // Specify the callback
  polyscope::state::userCallback = myCallback;
  
  // Give control to the polyscope gui
  polyscope::show();
  return EXIT_SUCCESS;
}
