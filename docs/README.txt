Compilation and Execution:
==========================
Use the following command to compile and run (from project directory):

make ARGS="data/filename data/filename data/filename data/filename data/filename" run

For example, 
make ARGS="data/sphere.ply data/sphere.ply data/sphere.ply data/sphere.ply data/airplane.ply" run


Note:
=====
The assignment is modelled after a solar system
The last object to be passed should be the movable object
'A' if the object with blue texture, 'D' is the airplane  
Object 'B' in green texture orbits around 'A'

Controls:
=========
'l' ->   switch between spotlights one at a time and back to all
't' ->   toggle texture for all objects
'+', '-' -> scale (zoom in,out)
'c' -> to change camera view from external point to D to A and back
'h', 'g' -> to increase and decrease speed of rotation of A
'k','j' -> to increase and decrease the speed of animation of D jumping
's' -> to stop/restart planet rotations
'b' -> toggle display of bounding boxes

click and drag left mouse key for rotation in external point mode

right click on static objects for the movable object to jump to


Some limitations:
================
1. Picking is based on pixel color, hence is dependent on texture
2. Lights and Camera are not in scenegraph


Libraries/APIs used:
===============
SOIL
GL
GLU
glut

