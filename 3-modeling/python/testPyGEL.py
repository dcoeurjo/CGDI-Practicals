import polyscope
import numpy as np
from pygel3d import hmesh

m = hmesh.load("../cube.obj")
print(m.positions())

faces = m.faces()

## Old school
allfaces=[]
for f in faces:
 face=[]
 for v in m.circulate_face(f):
     face.append(v)
 allfaces = allfaces + [face]

## Fancy version
allfaces2 = [[v for v in m.circulate_face(f)] for f in faces]

polyscope.init()

#Display the vertices as point cloud
polyscope.register_point_cloud("data", m.positions())

#Display the vertices as mesh
polyscope.register_surface_mesh("data mesh", m.positions(), allfaces)
#Display the vertices as mesh
polyscope.register_surface_mesh("data mesh2", m.positions(), allfaces2)

polyscope.show()
