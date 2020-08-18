#include <bits/stdc++.h>
#include "GL/freeglut.h"
#include "GL/gl.h"
#include <GL/glu.h>
#include "model.h"
#include "FastTrackball.h"

using namespace std;

#pragma once

class Controller {
	public:
		int currentX, currentY, mState; 
		int attach_to, movable_object, prev_attached;
		float scaleX,scaleY,scaleZ;
		int camSwitch;
		bool addTexture;
		bool animating;
		int lightObjNum;
		int animateSpeedChange;
		int timeSteps;
		int currentTime;
		float Position[3];
		float data[3];
		float jumpPosition[3];
		bool headl, s1, s2;
		GLuint tex[6];
		Trackball trackball;
		Model *model;
		bool stopRotation;
		bool showBoundingBox;
		void unsetTextures();
		void setTextures();
		void animate();
		void controlSpeed(bool faster,int);
		void setRotations();
		void setLights();
		void enableLighting();
		void bindTextures();
		void assignTexture(char* image_file,int ind);
		void pick(int x,int y);
		void prepareObjects();
		void display();
		void lighting();
		void renderScene();
		void drawFloor();
		void rotate(float, float, float, float);
		Controller();
		~Controller();
};
