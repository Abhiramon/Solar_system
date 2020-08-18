#include "../include/light.h"

Light::Light(int num){
	position.push_back(1);
	position.push_back(1);
	position.push_back(1);
	position.push_back(1);
	
	direction.push_back(0);
	direction.push_back(-1);
	direction.push_back(0);

	cutoff=45;
	exponent=1;
	n=num;
}

Light::~Light(){}

void Light::set(){
	GLfloat pos[]={position[0],position[1],position[2],position[3]};
	GLfloat dir[]={direction[0],direction[1],direction[2]};
	GLfloat dif[]={0.6,0.6,0.6,1};
	GLfloat spec[]{1,1,1,1};
	glLightfv(GL_LIGHT0+n,GL_DIFFUSE, dif);
	glLightfv(GL_LIGHT0+n,GL_SPECULAR, spec);
	glLightfv(GL_LIGHT0+n, GL_POSITION, pos);
	glLightf(GL_LIGHT0+n, GL_SPOT_CUTOFF, cutoff);	
	glLightfv(GL_LIGHT0+n, GL_SPOT_DIRECTION, dir);
	glLightf(GL_LIGHT0+n, GL_SPOT_EXPONENT, exponent);
}