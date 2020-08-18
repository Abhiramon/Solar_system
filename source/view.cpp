#include <bits/stdc++.h>
#include "GL/freeglut.h"
#include "GL/gl.h"
#include <GL/glu.h>
#include "../include/SOIL.h"
#include "../include/view.h"

using namespace std;

bool click_released=false;

View::View(){}

View::~View(){ delete model; }

void View::initialize() {
	GLsizei winX = glutGet(GLUT_WINDOW_WIDTH);
	GLsizei winY = glutGet(GLUT_WINDOW_HEIGHT);	
	glViewport(0, 0, winX, winY);
	glClearColor(0.0,0.0,0.0,1.0);
	glColor3f(1.0,0.0,0.0);

	controller->prepareObjects();

	//Modify Controller::pick function, if these are changed
	controller->assignTexture("data/sun.jpg",0);  
	controller->assignTexture("data/brown.jpeg",1);
	controller->assignTexture("data/blue.jpeg",2);
	controller->assignTexture("data/green.jpeg",3);
	controller->assignTexture("data/silver.jpeg",4);
	// controller->assignTexture("data/table_wood.jpg",5);
	//

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_PROGRAM_POINT_SIZE); 
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	// controller->enableLighting();
	glMatrixMode(GL_PROJECTION);						
	glLoadIdentity();							
	gluPerspective(90.0, (float)winX /(float)winY, .01, 100.0);		
	glMatrixMode(GL_MODELVIEW);						
	glLoadIdentity();	
}


void View::drawAxis() {
	glPushMatrix();
	glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-250.0, 0.0, -1.0f);
		glVertex3f(250.0, 0.0, -1.0f);		
	glEnd();
	glBegin( GL_LINES);
		glColor3f( 0.0, 0.0, 1.0);
		glVertex3f(0.0, -250.0, -1.0f);
		glVertex3f(0.0, 250.0, -1.0f);		
	glEnd();
	glPopMatrix();
}

void View::display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	drawAxis();
	controller->display();
}

void View::reshape(GLsizei wt, GLsizei ht) {  
	if (ht == 0)
		ht = 1;								
	glViewport(0,0, wt, ht);						
	glMatrixMode(GL_PROJECTION); 						
	glLoadIdentity(); 							
	gluPerspective(90.0, (float)wt / (float)ht, .1, 20.0);		
	glMatrixMode(GL_MODELVIEW);						
	glLoadIdentity();							
}

void View::keyboard(unsigned char key, int x, int y) {
	
   	switch (key) {
   			case '+':
   				controller->scaleX+=0.2;
   				controller->scaleY+=0.2;
   				controller->scaleZ+=0.2;
   				glutPostRedisplay();
   				break;	
   			case '-':
   				controller->scaleX-=0.2;
   				controller->scaleY-=0.2;
   				controller->scaleZ-=0.2;
   				glutPostRedisplay();
   				break;
   			case 'c':
   				if (controller->camSwitch==2) controller->camSwitch=0;
   				else controller->camSwitch+=1;
   				glutPostRedisplay();
   				break;
   			case 't':
   				if (controller->addTexture==true) controller->addTexture=false;
   				else controller->addTexture=true;
   				glutPostRedisplay();
   				break;
   			case 'l':
   				if (controller->lightObjNum==-1) controller->lightObjNum =0;
   				else if (controller->lightObjNum ==6) controller->lightObjNum=-1;
   				else controller->lightObjNum+=1;
   				glutPostRedisplay();
   				break;
   			case 's':
   				if (controller->stopRotation) controller->stopRotation=false;
   				else controller->stopRotation=true;
   				glutPostRedisplay();
   				break;
   			case 'g':
   				controller->controlSpeed(false,2);
   				glutPostRedisplay();
   				break;
   			case 'h':
   				controller->controlSpeed(true,2);
   				glutPostRedisplay();
   				break;
   			case 'j':
   				controller->controlSpeed(false,4);
   				glutPostRedisplay();
   				break;
   			case 'k':
   				controller->controlSpeed(true,4);
   				glutPostRedisplay();
   				break;
   			case 'b':
   				if (controller->showBoundingBox) controller->showBoundingBox=false;
   				else controller->showBoundingBox=true;
   				glutPostRedisplay();
   				break;
      		case 27:     
        	 	exit(0);
        	 	break;
        	default:
        		break;       
   	}
}

void View::setRotations(void){
	controller->setRotations();
}

void View::mouseMotion(int x, int y) {
	if (View::controller->mState == 0) {
		View::controller->rotate(View::controller->currentX, View::controller->currentY, x, y);
		glutPostRedisplay();
    }
  	View::controller->currentX = x;
    View::controller->currentY = y;
}


void View::mouse(int button, int state, int x, int y) {
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			View::controller->mState = 0;				// Update Mouse State when Left Button pressed
            View::controller->currentX = x;
            View::controller->currentY = y;
            glutIdleFunc(View::setRotations);
        }	
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        View::controller->mState = 1;				
		View::controller->rotate(0, 0, 0, 0);		      
       	glutIdleFunc(View::setRotations);
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		controller->pick(x,y);
		glutIdleFunc(View::setRotations);	
	}
	else{
		glutIdleFunc(View::setRotations);	
	}
}

void View::init(int argc, char** argv) {
	glutInit(&argc,argv);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700,700);
	glutCreateWindow("Texture");
	View::initialize();
	glutDisplayFunc(View::display); 
	glutReshapeFunc(View::reshape);       
	glutKeyboardFunc(View::keyboard);
	glutMotionFunc(View::mouseMotion); 
	glutMouseFunc(View::mouse);
	glutMainLoop();
}
