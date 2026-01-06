#include <geometrycentral/surface/manifold_surface_mesh.h>
#include <geometrycentral/surface/meshio.h>
#include <geometrycentral/surface/vertex_position_geometry.h>

#include <polyscope/polyscope.h>
#include <polyscope/surface_mesh.h>

#include <CLI11.hpp>
#include <cstdlib>
#include <iostream>

using namespace geometrycentral;
using namespace geometrycentral::surface;

// == Geometry-central data
std::unique_ptr<ManifoldSurfaceMesh> mesh;
std::unique_ptr<VertexPositionGeometry> geometry;

int main(int argc, char **argv) {

  // Parse command line with CLI11
  CLI::App app{"Display an OBJ/mesh using Polyscope"};
  std::string meshPath;
  app.add_option("-m,--mesh", meshPath, "Path to mesh file (OBJ, etc.)")->required() ;
  try {
    app.parse(argc, argv);
  } catch (const CLI::ParseError &e) {
    return app.exit(e);
  }
   
  
  // Initialize polyscope
  polyscope::init();

  // Load mesh
  std::tie(mesh, geometry) = readManifoldSurfaceMesh(meshPath);

  // Register the mesh with polyscope
  polyscope::registerSurfaceMesh("Input mesh",
                                 geometry->inputVertexPositions,
                                 mesh->getFaceVertexList(),
                                 polyscopePermutations(*mesh));
  
  // Give control to the polyscope gui
  polyscope::show();

  return EXIT_SUCCESS;
}
