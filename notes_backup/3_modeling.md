[CGDI] 3d modeling and geometry processing (1)
===

> [name="David Coeurjolly"] 

ENS [CGDI](https://perso.liris.cnrs.fr/vincent.nivoliers/cgdi/) Version

[TOC]

---

The objective of the practical is to play with elementary 3D structures and 3d modeling of objects. 

# Setting up your project with [polyscope](https://polyscope.run)

In order to focus on the geometrical algorithms (rather than technical details that may be important but slightly out-of-context here), we would like you to consider [polyscope](https://polyscope.run) for the visualization of 3d structures with attached data.

![](http://polyscope.run/media/teaser.svg)


[Polyscope](https://polyscope.run) is available in `python` or `c++` with a very similar API. The main design is that you have **structures** (point cloud, meshes, curves...) and **quantities** (scalars or vectors) attached to geometrical elements (points, vertices, edges, faces,...).

1. Update the `clone` of the repository: [https://github.com/dcoeurjo/CGDI-Practicals](https://github.com/dcoeurjo/CGDI-Practicals) (`git pull`). 

    * If you are using `python`: `pip install polyscope numpy`, and run the demo: `python demo.py`
    * If you are using `c++`: get polyscope and its dependencies as submodules using `git submodule update --init --recursive`. Use cmake to build the project and you should get a `demo` executable.

`Python` code snippet:

``` python
import polyscope
import numpy as np

pts = np.array([[0,0,0], [0,0,1], [0,1,0], [1,0,0], [1,1,0],[0,1,1],[1,0,1],[1,1,1]])
val = np.array([ 0.3, 3.4, 0.2, 0.4, 1.2, 4.0,3.6,5.0])

polyscope.init()
polyscope.register_point_cloud("My Points", pts)
polyscope.get_point_cloud("My Points").add_scalar_quantity("Some values",val)
polyscope.show()
```

`C++` code snippet:

``` c++
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
````

2. Have a look to the [polyscope.run](https://polyscope.run) webpage, and more precisely the [structures vs. quantities](https://polyscope.run/structures/structure_management) approach.

A key ingredient of this viewer is that you can easily debug geometrical quantities attached to 3d elements with a very [generic way](https://polyscope.run/data_adaptors/) to describe those elements. For instance (in `c++`), a scalar quantity could either be a `std::vector<double>`, a `double*`, a `std::array<double>`, an `Eigen::VectorXd`... The program uses template metaprogramming and type inference to make the life of the dev easier.

The same holds for geometrical quantities, a point cloud (collection of points in $\mathbb{R}^3$) could be represented as a `std::vector< std::array<double,3> >` or as a $n\times 3$ [Eigen](https://eigen.tuxfamily.org) matrix on real numbers. 


3. Create a simple program that uniformly sample the unit ball with points. Add quantities to visualize, for each sample the distance to the ball center, and the direction to its closest point. Play a bit with the various color maps and the parameters that controls the visualization.

:::info
To generate uniform numbers in $[0,1)$ you can consider `numpy.random.random()` in python or `std::uniform_real_distribution<double> distribution(0.0,1.0);` in c++.
:::

4. Generate another point set with points sampling **uniformly** the unit sphere (aka, constant density all over the domain). (*Hint*: have a look to the first practical)

# Modeling 101

As described in the lecture, the simplest way to describe a polygonal surface is to consider an structure for the vertex coordinates (*e.g.* $|V|\times 3$ `numpy` array or `std::vector<std::array<double,3>>`):
```
v1: x1 y1 z1
v2: x2 y2 z2
v3: x3 y3 z3
...
```
and an array for faces (*e.g* vector of vectors) where each face is described by a sequence of vertex indices:
```
f1: id1 id2 id3 id4
f2: id3 id4 id5
...
```
(in this example, the first face has four vertices and share an edge with the second triangular one). So 


5. Create a new [Surface Mesh](https://polyscope.run/structures/surface_mesh/basics/) structure in polyscope representing a unit cube.
6. For each face, compute the normal vector (unitary vector perpendicular to the face) and visualize it as a [vector quantity](https://polyscope.run/structures/surface_mesh/vector_quantities/). 
7. For each face again, do the math and create a per face orthogonal frame (two additional vectors to encode the tangent plane at the face): ![](https://raw.githubusercontent.com/dcoeurjo/CGDI-Practicals/main/3-modeling/Capture%20d’écran%202021-02-02%20à%2012.43.32.png =200x)
8. Attach a quantity to each vertex that corresponds to the abscissa of that vertex.

::: info
Internally, the 3d viewer uses the same linear blending scheme on the faces as  the one you have implemented in the previous practical. 
:::


9. Generate an object made of randomly shifted, scaled and rotated cubes (cf the lecture for the transformation matrices).


# Catmull-Clark Subdivision Scheme

The idea now is to implement a basic yet widely used [subdivision surface](https://en.wikipedia.org/wiki/Subdivision_surface) scheme: the [Catmull-Clark](https://en.wikipedia.org/wiki/Catmull–Clark_subdivision_surface) scheme.

:::success
Ed Catmull = co-funder of Pixar ;). Nice [paper](https://graphics.pixar.com/library/Geri/paper.pdf) about subdivision surfaces in character animation from Pixar.
:::

![](https://upload.wikimedia.org/wikipedia/commons/3/33/Catmull-Clark_subdivision_of_a_cube.svg =200x)

Starting from a quadrilateral mesh, the limit surface is a bicubic [B-spline](https://en.wikipedia.org/wiki/B-spline) surface. The implicit limit surface is widely used in rendering with for instance very efficient ray/surface intersections without explicitly computing the high-resolution surface.

10. Starting from a unit cube, create a single [Catmull-Clark step](https://en.wikipedia.org/wiki/Catmull–Clark_subdivision_surface). To do so, you would need to implement several traversal/topological functions: iterate through the vertices of a face, to retrieve the two faces associated with an edge...


::: info
For the data structure and polyscope side, just keep it simple at this point: to subdivide a mesh, just create a new face-vertex structure (and `register` it in polyscope) and delete the previous one (instead of doing smart updates in the structures).
:::

11. Perform several subdivision steps to converge to a smooth object (be careful about the combinatorics...).


12. Have a look to the various [alternative schemes](https://en.wikipedia.org/w/index.php?title=Subdivision_surface&section=3) that have been proposed for the triangular or quadrangular cases.


# Additional Stuff: loading OBJ 3d model

We just detail here few hints in `python` or `c++` to visualize [Wavefront OBJ file](https://en.wikipedia.org/wiki/Wavefront_.obj_file) (simple ascii file easy to parse).

In `python`, you can have a look to [pygel3d](http://www2.compute.dtu.dk/projects/GEL/PyGEL/) (package that Vincent is using for the lecture, `pip install pygel3D`). The package comes with an visualization toolkit but have a look to the `testpyGEL.py` for an OBJ loading example with visualization using polyscope. The package also contains a manifold mesh API (to iterate of the mesh elements for instance) that we may be using for the next practicals.


In `c++`, there are various alternatives ([CGAL](http://cgal.org), [libIGL](https://libigl.github.io), [openmesh](https://www.openmesh.org)...). At this point, I will showcase the [geometry-central](https://geometry-central.net) lib that fits well with polyscope. Have a look to the practicals repository for a demo (geomtry-central has been added as `git submodule`, just do the update as mentioned at the very beginning of the note). Just have a look to the `displayOBJ.cpp` file.


![](https://raw.githubusercontent.com/dcoeurjo/CGDI-Practicals/main/3-modeling/bimba.png)
