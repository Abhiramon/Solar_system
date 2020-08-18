#include <bits/stdc++.h>
#include "GL/freeglut.h"
#include "GL/gl.h"
#include <GL/glu.h>
#include "controller.h"

using namespace std;

#pragma once

class View {
	public:
		static Model * model;
		static Controller * controller;
		static void setRotations(void);
		static void init(int, char**);
		static void initialize();
		static void drawAxis();
		static void display();
		static void keyboard(unsigned char, int, int);
		static void mouse(int, int, int, int);
		static void mouseMotion (int, int);
		static void reshape(GLsizei, GLsizei);
		View();
		~View();
};
	
