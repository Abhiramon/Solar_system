#include <bits/stdc++.h>
#include "GL/freeglut.h"
#include "GL/gl.h"
#include "light.h"
#include <GL/glu.h>
#include "object.h"
using namespace std;

#pragma once
	
class Model {
	public:
		vector<Object> objects;
		vector<Light> lights;  //Assuming the last but one light is headlight and last is spotlight on moving obj
		bool on, lighting;
		float X, Y, Z;
		Model();
		~Model();
		void arrangeObjects();
		void read_ply(int, char *);
		void setNormals(int);
		void renderScene(GLuint*);
		void drawFloor();
		void addChild(int i,int j);
		void removeChild(int i,int j);
		void read_obj(int argc,char* argv);
		vector<int> face_info(string );
		void read(int argc,char* argv);
		void updatePositions();

};
	
