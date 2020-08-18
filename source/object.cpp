#include "../include/object.h"
#define PI 3.1415926

Object::Object(){
			parent=-1;
			moveX=moveY=moveZ=0;
			color[0]=color[1]=color[2]=0.5;
			placeX=placeY=placeZ=0;
			scaleX=scaleY=scaleZ=1;
			rotX=rotY=rotZ=spinY=spinX=spinZ=orbitZ=0;
			speedX=speedY=speedZ=0;
			renderingFinished=false;
			inherit_texture=false;
		}
Object::~Object(){
}

void Object::computeTexSphere() {
	for(int i=0; i<faces.size(); i++) {
		for(int j=0; j<faces[i].vertices.size(); j++) {
			faces[i].vertices[j].r = (atan2f(faces[i].vertices[j].z, faces[i].vertices[j].x)  + PI) / (2 * PI);
			faces[i].vertices[j].s = (atan2f(faces[i].vertices[j].z, faces[i].vertices[j].y * 
									  sin(2 * PI * faces[i].vertices[j].r))) / (2 * PI);
		}
	}
}


void Object::render(){

	//Modify updatePosition function if these transformations are changed
	glRotatef(rotX,1,0,0);
	glRotatef(rotY,0,1,0);
	glRotatef(rotZ,0,0,1);
	glTranslatef(moveX,moveY,moveZ);
	glTranslatef(placeX,placeY,placeZ);
	if (!inherit_texture)
		glBindTexture(GL_TEXTURE_2D, tex_val);
	glRotatef(spinX,1,0,0);
	glRotatef(spinY,0,1,0);
	glRotatef(spinZ,0,0,1);
	//Transforms specific to object
	glPushMatrix();
	glScalef(scaleX,scaleY,scaleZ);
	for(int n=0; n<faces.size(); n++) {	
			glBegin(GL_POLYGON);
				glColor3f(color[0], color[1], color[2]);		
			for(int i=0; i<faces[n].vertices.size(); i++) {	
				glNormal3f(faces[n].vertices[i].normal[0], faces[n].vertices[i].normal[1], faces[n].vertices[i].normal[2]);
				glTexCoord2f(faces[n].vertices[i].r, faces[n].vertices[i].s);		
				glVertex3f(faces[n].vertices[i].x,faces[n].vertices[i].y,faces[n].vertices[i].z); 
			}
			glEnd();
		}

	// glGetFloatv(GL_MODELVIEW_MATRIX,MVMatrix);
	// pos[0]=MVMatrix[12]; pos[1]=MVMatrix[13]; pos[2]=MVMatrix[14];
	if (showBoundingBox)
		boundingBox();
	glPopMatrix(); 
	//
	for (int i=0;i<children.size();i++){
		if (children[i]->renderingFinished==false){
			glPushMatrix();
			glRotatef(children[i]->orbitZ,0,0,1);
			glTranslatef(0,top-bottom+0.5,0);
			children[i]->render();
			glPopMatrix();
		}
	}

	renderingFinished=true;

}

void Object::boundingBox(){
	glPushMatrix();
	glColor3f(1,1,1);

	glBegin(GL_LINES);
	glVertex3f(left,bottom,near);
	glVertex3f(right,bottom,near);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(left,bottom,near);
	glVertex3f(left,top,near);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(left,bottom,near);
	glVertex3f(left,bottom,far);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(right,top,near);
	glVertex3f(left,top,near);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(right,top,near);
	glVertex3f(right,top,far);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(right,top,near);
	glVertex3f(right,bottom,near);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(left,top,far);
	glVertex3f(left,bottom,far);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(left,top,far);
	glVertex3f(right,top,far);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(left,top,far);
	glVertex3f(left,top,near);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(right,bottom,far);
	glVertex3f(right,top,far);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(right,bottom,far);
	glVertex3f(left,bottom,far);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(right,bottom,far);
	glVertex3f(right,bottom,near);
	glEnd();



	glPopMatrix();
}
	
