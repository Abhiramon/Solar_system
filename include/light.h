#include <bits/stdc++.h>
#include "GL/freeglut.h"
#include "GL/gl.h"
#include <GL/glu.h>

using namespace std;

#pragma once

class Light{

public:
	int n;
	vector<GLfloat> position;
	vector<GLfloat> direction;
	float cutoff;
	float exponent;
	Light(int );
	~Light();
	void set();

};