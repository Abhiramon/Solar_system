#include "../include/controller.h"
#include "../include/SOIL.h"
#include <stdlib.h>
#define pi 3.142857

using namespace std;

GLuint tex[] = {0, 0, 0, 0, 0, 0, 0};

Controller::Controller(){
	attach_to=0;
	timeSteps=300,animateSpeedChange=30;
	currentTime=0;
	currentX = currentY = mState=-1;
	headl = s1 = s2 = false;
	tex[0] = tex[1] = tex[2] = tex[3] = tex[4] = tex[5] = 0;
	addTexture=true;
	showBoundingBox=true;
	lightObjNum=-1;

	scaleX=scaleY=scaleZ=0.8;
	camSwitch=0;
	stopRotation=false;
	animating=false;
}

Controller::~Controller(){
}

void Controller::bindTextures() {
	for(int i=0; i<model->objects.size(); i++) 
		model->objects[i].computeTexSphere();
}

void Controller::setRotations(){
	if (!stopRotation){
		model->objects[1].rotY+=0.05;
		model->objects[1].spinY+=0.2;

		model->objects[2].rotY+=model->objects[2].speedY;
		model->objects[2].spinY+=0.1;

		model->objects[3].orbitZ+=0.2;

		model->objects[model->objects.size()-1].spinX=-90;
	}
	else {
		model->objects[1].rotY+=0;
		model->objects[1].spinY+=0;

		model->objects[2].rotY+=0;
		model->objects[2].spinY+=0;

		model->objects[3].orbitZ+=0;
	}
	glutPostRedisplay();

}

void Controller::controlSpeed(bool faster, int ind){
	if (ind==2){
		if (faster) model->objects[2].speedY+=0.01;
		else model->objects[2].speedY -=0.01;
	}
	if (ind==4){
		if (faster){
				if (timeSteps>=animateSpeedChange) timeSteps-=animateSpeedChange;
		} 
		else {
			timeSteps+=animateSpeedChange;
			}
	}
}

void Controller::assignTexture(char* image_file,int ind){
	int width, height;
	glGenTextures(1, &(tex[ind]));
	glBindTexture(GL_TEXTURE_2D, tex[ind]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* image = SOIL_load_image(image_file, &width, &height, 0, SOIL_LOAD_RGB);
	// const char* errX = SOIL_last_result();
	// cout<<errX<<controller->tex[4]<<endl;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

}

void Controller::enableLighting(){
	if (lightObjNum==-1){
		for (int i=0;i<model->lights.size();i++){
			glEnable(GL_LIGHT0+model->lights[i].n);
		}
	}
	else if (lightObjNum==-2){
		for (int i=0;i<model->lights.size();i++){
			glDisable(GL_LIGHT0+model->lights[i].n);
		}
	}
	else{for (int i=0;i<model->lights.size();i++){
			if (i!=lightObjNum)
				glDisable(GL_LIGHT0+model->lights[i].n);
			}
		glEnable(GL_LIGHT0+model->lights[lightObjNum].n);
	}

}


void Controller::setLights(){

	for (int i=0;i<model->lights.size()-2;i++){

		float top=model->objects[i].top;
		float bot=model->objects[i].bottom;

		model->lights[i].position[0]=model->objects[i].pos[0];
		model->lights[i].position[1]=model->objects[i].pos[1]+4;
		model->lights[i].position[2]=model->objects[i].pos[2];

		model->lights[i].set();
	}
	float x,y,z,length;
	int mov_light=model->lights.size()-1;
	x=model->objects[movable_object].pos[0] - Position[0];
	y=model->objects[movable_object].pos[1] - Position[1];
	z=model->objects[movable_object].pos[2] - Position[2];
	length=sqrt(x*x + y*y + z*z);

	model->lights[mov_light].direction[0]=x/length;
	model->lights[mov_light].direction[1]=y/length;
	model->lights[mov_light].direction[2]=z/length;

	model->lights[mov_light].position[0]=Position[0];
	model->lights[mov_light].position[1]=Position[1];	
	model->lights[mov_light].position[2]=Position[2];

	model->lights[mov_light].set();

	int head_light=model->lights.size()-2;	


	x=model->X - Position[0];
	y=model->Y - Position[1];
	z=model->Z - Position[2];
	length=sqrt(x*x + y*y + z*z);

	model->lights[head_light].direction[0]=x/length;
	model->lights[head_light].direction[1]=y/length;
	model->lights[head_light].direction[2]=z/length;

	model->lights[head_light].position[0]=Position[0];
	model->lights[head_light].position[1]=Position[1];	
	model->lights[head_light].position[2]=Position[2];

	model->lights[head_light].set();

	//display lights
	glPushMatrix();
	glColor3f(1,1,1);
	glPointSize(5);
	glBegin(GL_POINTS);
	for (int i=0;i<model->lights.size();i++){
		glVertex3f(model->lights[i].position[0], model->lights[i].position[1], model->lights[i].position[2]);
		
	}
	glEnd();
	glPopMatrix();
}

void Controller::lighting(){

	GLfloat light_ambient[] = {0.4f, 0.4f, 0.4f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);
	glShadeModel(GL_SMOOTH);


	GLfloat mat_specular[] = {1.0,1.0,1.0,1.0};
	GLfloat mat_shininess[] = {50.0};

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	setLights();

	enableLighting();
}

		

void Controller::renderScene() {
	if (addTexture == true)
		glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	model->addChild(3,2);
	if (animating) animate();
	glScalef(scaleX,scaleY,scaleZ);
	model->renderScene(tex);

	if (showBoundingBox){
		for (int i=0;i<model->objects.size();i++) model->objects[i].showBoundingBox=true;
		}
	else for (int i=0;i<model->objects.size();i++) model->objects[i].showBoundingBox=false;
	glDisable(GL_TEXTURE_2D);
}

void Controller::rotate(float oldx, float oldy, float x, float y)
{	
    float w = glutGet( GLUT_WINDOW_WIDTH );
	float h = glutGet( GLUT_WINDOW_HEIGHT );
    float p = (2.0*oldx - w)/(float)w;
    float q = (h - 2.0*oldy)/(float)h;
    float r = (2.0*x - w)/(float)w;
    float s = (h - 2.0*y)/(float)h;
    trackball.rotate(p,q,r,s);
}

void Controller::drawFloor() {	
	glPushMatrix();
	if (addTexture)
		glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, tex[5]);
	model->drawFloor();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
}

void Controller::unsetTextures(){
	addTexture=false;

	model->objects[0].color[0]=1; model->objects[0].color[1]=0; model->objects[0].color[2]=0;
	model->objects[1].color[0]=1; model->objects[1].color[1]=0; model->objects[1].color[2]=1;
	model->objects[2].color[0]=0; model->objects[2].color[1]=0; model->objects[2].color[2]=1;
	model->objects[3].color[0]=0; model->objects[3].color[1]=1; model->objects[3].color[2]=0;
	model->objects[4].color[0]=1; model->objects[4].color[1]=1; model->objects[4].color[2]=1;

	lightObjNum=-2;
	glutPostRedisplay();
}

void Controller::setTextures(){
	addTexture=true;

	model->objects[0].color[0]=0.5; model->objects[0].color[1]=0.5; model->objects[0].color[2]=0.5;
	model->objects[1].color[0]=0.5; model->objects[1].color[1]=0.5; model->objects[1].color[2]=0.5;
	model->objects[2].color[0]=0.5; model->objects[2].color[1]=0.5; model->objects[2].color[2]=0.5;
	model->objects[3].color[0]=0.5; model->objects[3].color[1]=0.5; model->objects[3].color[2]=0.5;
	model->objects[4].color[0]=0.5; model->objects[4].color[1]=0.5; model->objects[4].color[2]=0.5;

	lightObjNum=-1;
	glutPostRedisplay();
}

void Controller::prepareObjects(){
	for (int i=0;i<model->objects.size();i++) model->objects[i].tex_id=5;

	if (model->objects.size()>=5){
		model->objects[0].tex_id = 0;  //sun
		
		model->objects[1].tex_id = 1;  //planet brown

		model->objects[2].tex_id = 2;  //planet blue

		model->objects[3].tex_id = 3;  //moon green

		model->objects[4].tex_id = 4;  //airplane
		
	}

	Light l(model->objects.size());
	model->lights.push_back(l);

	model->objects[2].speedY=0.05;
	model->objects[model->objects.size()-1].inherit_texture = true;
	model->arrangeObjects();
	movable_object=model->objects.size()-1;

	model->addChild(movable_object,0);

}


void Controller::animate(){
	float t=timeSteps;
	float i=currentTime;
	float p1[3];
	float p2[3];
	float height=model->objects[attach_to].top - model->objects[attach_to].bottom;
		p1[0]=jumpPosition[0];
		p1[1]=jumpPosition[1];
		p1[2]=jumpPosition[2];
	
		
		p2[0]=model->objects[attach_to].pos[0];
		p2[1]=model->objects[attach_to].pos[1]+height;
		p2[2]=model->objects[attach_to].pos[2];
		model->objects[movable_object].moveX=((t-i)*p1[0]+i*p2[0])/t;
		model->objects[movable_object].moveY=((t-i)*p1[1]+i*p2[1])/t+3*(1-pow((1-(2*i/t)),2));
		model->objects[movable_object].moveZ=((t-i)*p1[2]+i*p2[2])/t;
		// cout<<model->objects[movable_object].moveX<<" "<<model->objects[movable_object].moveY<<" "<<model->objects[movable_object].moveZ<<endl;
		// cout<<"i is "<<i<<endl;
		if (currentTime>=timeSteps){
			currentTime=0;
			animating=false;
			model->objects[movable_object].moveX=0;
			model->objects[movable_object].moveY=0;
			model->objects[movable_object].moveZ=0;
			model->objects[movable_object].inherit_texture=true;
			model->addChild(movable_object,attach_to);
		}

		else{
				currentTime+=1;
			}
		glutPostRedisplay();



}

void Controller::pick(int x,int y){
	// unsetTextures();
	float h = glutGet( GLUT_WINDOW_HEIGHT );
	GLubyte * data = (GLubyte*)malloc(3);
	y=h-y;
	glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,data);

	int r,g,b;
	r=data[0]; g=data[1]; b=data[2];

	prev_attached=attach_to;

	// setTextures();

	if (g>3*b && g>r) attach_to=3;
	else if (b>3*r && b>g) attach_to=2;
	else if (r>3*b && r>g) attach_to=0;
	else if (r<2*g && r<2.5*b) attach_to=1;
	if (prev_attached!=attach_to){
		float height=model->objects[prev_attached].top - model->objects[prev_attached].bottom;
		jumpPosition[0]=model->objects[prev_attached].pos[0];
		jumpPosition[1]=model->objects[prev_attached].pos[1]+height+0.5;
		jumpPosition[2]=model->objects[prev_attached].pos[2];

		model->removeChild(movable_object,prev_attached);
		model->objects[movable_object].inherit_texture=false;
		model->objects[movable_object].tex_id=model->objects[prev_attached].tex_id;
		animating = true;
	}

}

void Controller::display() {
	glLoadIdentity();
	glPushMatrix();
		float x,y,z;								
		static float rotation_transform[4][4];					
		trackball.rotationMatrix(rotation_transform);	
		Position[0] = 0 + model->X;
		Position[1] = 5 + model->Y;
		Position[2] = 6.0 + model->Z;			
				
		x = Position[0] * rotation_transform[0][0] + Position[1] * rotation_transform[0][1] + Position[2] * rotation_transform[0][2] 
		+ rotation_transform[0][3];
		
		y = Position[0] * rotation_transform[1][0] + Position[1] * rotation_transform[1][1] + Position[2] * rotation_transform[1][2] 
		+ rotation_transform[1][3];
		
		z = Position[0] * rotation_transform[2][0] +Position[1] * rotation_transform[2][1] + Position[2] * rotation_transform[2][2] 
		+ rotation_transform[2][3];

		
		Position[0] = x;
		Position[1] = y;
		Position[2] = z;
		
		float eye[3];
		if (camSwitch==0){
			eye[0]=Position[0]; eye[1]=Position[1]; eye[2]=Position[2];
			gluLookAt(eye[0], eye[1], eye[2], model->X, model->Y, model->Z, 0, 1, 0);
			}
		else if (camSwitch==1){
			eye[0]=model->objects[4].pos[0]+0.2; eye[1]=model->objects[4].pos[1]+0.2;
			eye[2]=model->objects[4].pos[2]+0.2;
			gluLookAt(eye[0], eye[1], eye[2], model->X, eye[1], model->Z, 0, 1, 0);
			}
		else if (camSwitch==2){
			eye[0]=model->objects[2].pos[0]+0.2; eye[1]=model->objects[2].pos[1]+0.2;
			eye[2]=model->objects[2].pos[2]+0.2;
			gluLookAt(eye[0], eye[1]+1.25, eye[2], model->X, eye[1], model->Z, 0, 1, 0);
			}
	
		
		// drawFloor();
		renderScene();
		lighting();	
	glPopMatrix();
	glutSwapBuffers();
}
