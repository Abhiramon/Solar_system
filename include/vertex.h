#include <bits/stdc++.h>
#include "GL/freeglut.h"
#include "GL/gl.h"
#include <GL/glu.h>

using namespace std;

#pragma once

class Vertex {
	public:
		float x, y, z, r, s;
		float normal[3];
		Vertex() {
			x = y = z = r = s = 0;
			normal[0]=normal[1]=normal[2]=0;
		}
		Vertex(float a, float b, float c);
		~Vertex();
};