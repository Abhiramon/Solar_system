#include <bits/stdc++.h>
#include "GL/freeglut.h"
#include "GL/gl.h"
#include <GL/glu.h>
# include "../include/view.h"

using namespace std;

Model* View::model;
Controller* View::controller;

int main(int argc, char* argv[]) {
	View view;
	Model model;
	Controller controller;
	controller.model = &model;
	View::model = &model;
	View::controller = &controller;
	//Assumption : Last object passed is the movable object
	for(int i=1; i<argc; i++)
		model.read(i-1, argv[i]);
	controller.bindTextures();
	// model.createLights();
	View::init(argc, argv);
	delete &view;

	return 0;
}
