# Demo polyscope + python
#
# make sure to have `pip install polyscope numpy`
#

import polyscope
import numpy as np

pts = np.array([[0,0,0], [0,0,1], [0,1,0], [1,0,0], [1,1,0],[0,1,1],[1,0,1],[1,1,1]])
val = np.array([ 0.3, 3.4, 0.2, 0.4, 1.2, 4.0,3.6,5.0])


polyscope.init()

polyscope.register_point_cloud("My Points", pts)

polyscope.get_point_cloud("My Points").add_scalar_quantity("Some values",val)

polyscope.show()
