#include <geometrycentral/surface/manifold_surface_mesh.h>
#include <geometrycentral/surface/meshio.h>
#include <geometrycentral/surface/vertex_position_geometry.h>

#include <polyscope/polyscope.h>
#include <polyscope/surface_mesh.h>

using namespace geometrycentral;
using namespace geometrycentral::surface;

// == Geometry-central data
std::unique_ptr<ManifoldSurfaceMesh> mesh;
std::unique_ptr<VertexPositionGeometry> geometry;

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
  
  // Give control to the polyscope gui
  polyscope::show();

  return EXIT_SUCCESS;
}
