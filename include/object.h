#include "face.h"

#pragma once

class Object {
	public:
		vector<Face> faces;
		vector<Object*> children;
		float max[3];					
		float min[3];
		float pos[3];	
		float color[3];		
		float left, right, top, bottom, near, far, size, scale;
		float mx, my, mz;
		int width, height;
		int tex_id;
		bool inherit_texture;
		GLuint tex_val;
		bool renderingFinished;
		float moveX,moveY,moveZ;
		float placeX,placeY,placeZ;
		float scaleX,scaleY,scaleZ;
		float rotX,rotY,rotZ,orbitZ;
		float spinX,spinY,spinZ;
		float speedX,speedY,speedZ;
		bool showBoundingBox;
		int parent;
		unsigned char *image;
		void render();
		void computeTexSphere();
		void readTexture(char*, GLuint*);
		void boundingBox();
		Object();
		~Object();
};