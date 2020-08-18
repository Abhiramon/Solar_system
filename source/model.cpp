#include <bits/stdc++.h>
#include "GL/freeglut.h"
#include "GL/gl.h"
#include <GL/glu.h>
#include "../include/model.h"
#include "../include/SOIL.h"
#define PI 3.1415926
using namespace std;

Model::Model() {
			X = Y = Z = 0.0;
			lighting = on = true;
		
		}

Model::~Model(){}

void Model::updatePositions(){
	
	for (int i=0;i<objects.size();i++){
		if (objects[i].parent==-1){
			objects[i].pos[0]=cos(objects[i].rotY*PI/180)*(objects[i].placeX+objects[i].moveX) + sin(objects[i].rotY*PI/180)*(objects[i].placeZ+objects[i].moveZ) ;
			objects[i].pos[1]=(objects[i].placeY+objects[i].moveY);
			objects[i].pos[2]=-sin(objects[i].rotY*PI/180)*(objects[i].placeX+objects[i].moveX) + cos(objects[i].rotY*PI/180)*(objects[i].placeZ+objects[i].moveZ) ;
		}
		else {
			float height = objects[objects[i].parent].top - objects[objects[i].parent].bottom;
			objects[i].pos[0]=objects[objects[i].parent].pos[0];
			objects[i].pos[1]=objects[objects[i].parent].pos[1]+height+0.5;
			objects[i].pos[2]=objects[objects[i].parent].pos[2];
		}
	}



}

void Model::setNormals(int ind) {
	float a[3], b[3], c[3], length;
	for(int i=0; i<objects[ind].faces.size(); i++) {
		a[0] = objects[ind].faces[i].vertices[1].x - objects[ind].faces[i].vertices[0].x;
		a[1] = objects[ind].faces[i].vertices[1].y - objects[ind].faces[i].vertices[0].y;
		a[2] = objects[ind].faces[i].vertices[1].z - objects[ind].faces[i].vertices[0].z;
		
		b[0] = objects[ind].faces[i].vertices[2].x - objects[ind].faces[i].vertices[0].x;
		b[1] = objects[ind].faces[i].vertices[2].y - objects[ind].faces[i].vertices[0].y;
		b[2] = objects[ind].faces[i].vertices[2].z - objects[ind].faces[i].vertices[0].z;
		
		c[0] = a[1] * b[2] - b[1] * a[2]; 
		c[1] = a[2] * b[0] - b[2] * a[0];
		c[2] = a[0] * b[1] - b[0] * a[1];
		
		length = sqrt((c[0] * c[0]) + (c[1] * c[1]) + (c[2] * c[2]));
		
		objects[ind].faces[i].normal[0] = c[0] / length;
		objects[ind].faces[i].normal[1] = c[1] / length;
		objects[ind].faces[i].normal[2] = c[2] / length;
		
	}

	//Setting vertex normals for smooth shading

	for (int i=0;i<objects[ind].faces.size();i++){
		for (int j=0;j<objects[ind].faces[i].vertices.size();j++){
			objects[ind].faces[i].vertices[j].normal[0]+=objects[ind].faces[i].normal[0];
			objects[ind].faces[i].vertices[j].normal[1]+=objects[ind].faces[i].normal[1];
			objects[ind].faces[i].vertices[j].normal[2]+=objects[ind].faces[i].normal[2];
		}
	}

	for (int i=0;i<objects[ind].faces.size();i++){
		for (int j=0;j<objects[ind].faces[i].vertices.size();j++){
			objects[ind].faces[i].vertices[j].normal[0]/=3;
			objects[ind].faces[i].vertices[j].normal[1]/=3;
			objects[ind].faces[i].vertices[j].normal[2]/=3;
		}
	}

}



void Model::renderScene(GLuint* tex){
	for (int i=0;i<objects.size();i++){
		objects[i].renderingFinished=false;
	}
	for (int ind=0;ind<objects.size();ind++){
		objects[ind].tex_val=tex[objects[ind].tex_id];
	}
	for (int ind=0;ind<objects.size();ind++){
		if (objects[ind].renderingFinished==false){
			glPushMatrix();
			objects[ind].render();
			glPopMatrix(); 
		}
	}
	updatePositions();
}

void Model::removeChild(int i,int j){
	for (int ind=0;ind<objects[j].children.size();ind++){
		if (objects[j].children[ind] == &objects[i])
			objects[j].children.erase(objects[j].children.begin()+ind);
	}
	objects[i].parent=-1;
}

void Model::addChild(int i,int j){
	if (objects[i].parent!=-1){
		removeChild(i,objects[i].parent);
	}
	objects[i].parent=j;
	objects[j].children.push_back(&objects[i]);

}

void Model::arrangeObjects(){
	if (objects.size()>=1){
		objects[0].placeX=0; objects[0].placeY=0; objects[0].placeZ=0;
		objects[0].scaleX=1.5; objects[0].scaleY=1.5; objects[0].scaleZ=1.5;
		}
	if (objects.size()>=2){
		objects[1].placeX=0; objects[1].placeY=0; objects[1].placeZ=-8;
		objects[1].scaleX=0.7; objects[1].scaleY=0.7; objects[1].scaleZ=0.7;
		}
	if (objects.size()>=3){
		objects[2].placeX=0; objects[2].placeY=0; objects[2].placeZ=-16;
		objects[2].scaleX=1; objects[2].scaleY=1; objects[2].scaleZ=1;
		}
	if (objects.size()>=4){
		objects[3].placeX=0; objects[3].placeY=0; objects[3].placeZ=0;
		objects[3].scaleX=0.4; objects[3].scaleY=0.4; objects[3].scaleZ=0.4;
		}
	if (objects.size()>=5){
		objects[4].placeX=0; objects[4].placeY=0; objects[4].placeZ=0;}
}

void Model::drawFloor() {
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-25.0f, -1.0f, -25.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(25.0f, -1.0f, -25.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(25.0f, -1.0f, 25.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-25.0f, -1.0f, 25.0f);
	glEnd();
}

void Model::read_ply(int argc, char *argv) {
	Object o;
	vector<Vertex> v;
	float minx, maxx, miny, maxy, minz, maxz;
	minx = miny = minz = INT_MAX;
	maxx = maxy = maxz = INT_MIN;
	FILE *file = fopen(argv,"r");
	int noOfv, noOfFaces;
	char buffer[100];
	if(file) {
		fgets(buffer, 100, file);
		while(strncmp("element vertex", buffer, strlen("element vertex")) != 0) {
			fgets(buffer, 100, file);
		}
		strcpy(buffer, buffer+strlen("element vertex"));
		sscanf(buffer, "%d", &noOfv);
					
		while(strncmp("element face", buffer, strlen("element face")) != 0) {
			fgets(buffer, 100, file);
		}
		strcpy(buffer, buffer+strlen("element face"));
		sscanf(buffer, "%d", &noOfFaces);
		
		while(strncmp("end_header", buffer, strlen("end_header")) != 0  ) {
			fgets(buffer, 100, file);			
		}
		
		for(int i=0; i<noOfv; i++) {
			fgets(buffer, 100, file);
			float a, b, c;
			sscanf(buffer, "%f %f %f", &a, &b, &c);
			minx = min(minx, a);
			miny = min(miny, b);
			minz = min(minz, c);
			maxx = max(maxx, a);
			maxy = max(maxy, b);
			maxz = max(maxz, c);
			Vertex newV(a,b,c);
			v.push_back(newV);
		}
		o.size = 0.0;
		
		if(o.size < maxx-minx)
		    	o.size = maxx-minx;
		if(o.size < maxy-miny)
			o.size = maxy-miny;
		if(o.size < maxz-minz)
		    	o.size = maxz-minz;
		o.scale = 2.0 / o.size;
		
		for (int i=0; i<noOfv; i++) {
		    	v[i].x = o.scale * (v[i].x - minx) - 1.0;
		    	v[i].y = o.scale * (v[i].y - miny) - 1.0;
			v[i].z = o.scale * (v[i].z - minz) - 1.0;
		}
		minx = miny = minz = 10000;
		maxx = maxy = maxz = -10000;
		for (int i=0; i<noOfv; i++) {
		    	minx = min(minx, v[i].x);
		    	maxx = max(maxx, v[i].x);
		    	miny = min(miny, v[i].y);
		    	maxy = max(maxy, v[i].y);
		    	minz = min(minz, v[i].z);
				maxz = max(maxz, v[i].z);
		}
		o.left = minx; o.right = maxx;
		o.top = maxy; o.bottom = miny;
		o.near = minz; o.far = maxz;
		
		for(int i=0; i<noOfFaces; i++) {
			int listSize;
			fscanf(file, "%d", &listSize);
			Face newf;
			for(int j=0; j<listSize; j++) {
				int a;
				fscanf(file, "%d", &a);
				newf.vertices.push_back(v[a]);
			}
			o.faces.push_back(newf);
		}
		fclose(file);
		o.mx = -(maxx+minx) / 2;
		o.my = -(maxy+miny) / 2;
		o.mx = -(maxz+minz) / 2;
		if(objects.size() == 2) {
			o.mx = -2.5;
			o.mz = 2.5;
		}
		objects.push_back(o);
		setNormals(objects.size()-1);	

		Light l(argc);
		lights.push_back(l);

	}
	else {
		printf("File cannot be opened\n");
	}
}

void Model::read(int argc,char* argv){
	int len=strlen(argv);
	if (argv[len-3]=='o' && argv[len-2]=='b' && argv[len-1]=='j')
			read_obj(argc,argv);
	else if (argv[len-3]=='p' && argv[len-2]=='l' && argv[len-1]=='y')
			read_ply(argc,argv);
}




vector<int> Model::face_info(string s){
	int pos1,pos2,v,t,n;
	string vs,ts,ns;
	vector<int> res;
	pos1=s.find("/");
	pos2=s.substr(pos1+1,s.length()).find("/");
	vs=s.substr(0,pos1);
	stringstream sstream1(vs);
	sstream1>>v;
	ts=s.substr(pos1+1,pos2);
	stringstream sstream2(ts);
	sstream2>>t;
	ns=s.substr(pos2+1,s.length());
	stringstream sstream3(ns);
	sstream3>>n;
	res.push_back(v);
	res.push_back(t);
	res.push_back(n);
	return res;
}

void Model::read_obj(int argc, char *argv) {
	Object o;
	vector<Vertex> v;
	vector<float> tex_r;
	vector<float> tex_s;
	vector<float> norm_x;
	vector<float> norm_y;
	vector<float> norm_z;
	
	float minx, maxx, miny, maxy, minz, maxz;
	minx = miny = minz = INT_MAX;
	maxx = maxy = maxz = INT_MIN;
	int noOfv=0, noOfFaces=0;

	ifstream file(argv);

	string s;

	if(file) {
		while(file>>s){
			// cout<<"running 1: "<<s<<endl;
			if (s=="v"){
				float a, b, c;
				file>>a>>b>>c;
				minx = min(minx, a);
				miny = min(miny, b);
				minz = min(minz, c);
				maxx = max(maxx, a);
				maxy = max(maxy, b);
				maxz = max(maxz, c);
				Vertex newV(a,b,c);
				v.push_back(newV);
				noOfv+=1;
			}
			else if (s=="vt"){
				float tr,ts;
				file>>tr>>ts;
				tex_r.push_back(tr);
				tex_s.push_back(ts);
			}
			else if (s=="vn"){
				float x,y,z;
				file>>x>>y>>z;
				norm_x.push_back(x);
				norm_y.push_back(y);
				norm_z.push_back(z);
			}
			else if (s=="f"){
				break;
			}

		}
		

		
		o.size = 0.0;
		
		if(o.size < maxx-minx)
		    	o.size = maxx-minx;
		if(o.size < maxy-miny)
			o.size = maxy-miny;
		if(o.size < maxz-minz)
		    	o.size = maxz-minz;
		o.scale = 2.0 / o.size;
		
		for (int i=0; i<noOfv; i++) {
		    	v[i].x = o.scale * (v[i].x - minx) - 1.0;
		    	v[i].y = o.scale * (v[i].y - miny) - 1.0;
			v[i].z = o.scale * (v[i].z - minz) - 1.0;
		}
		minx = miny = minz = 10000;
		maxx = maxy = maxz = -10000;
		for (int i=0; i<noOfv; i++) {
		    	minx = min(minx, v[i].x);
		    	maxx = max(maxx, v[i].x);
		    	miny = min(miny, v[i].y);
		    	maxy = max(maxy, v[i].y);
		    	minz = min(minz, v[i].z);
				maxz = max(maxz, v[i].z);
		}
		o.left = minx; o.right = maxx;
		o.top = maxy; o.bottom = miny;
		o.near = minz; o.far = maxz;

		//first face extraction
		string sa,sb,sc;
				Face newf;
				file>>sa>>sb>>sc;
				vector<int> a=face_info(sa);
				newf.vertices.push_back(v[a[0]-1]);
				v[a[0]-1].r=tex_r[a[1]-1];
				v[a[0]-1].s=tex_s[a[1]-1];
				v[a[0]-1].normal[0]=norm_x[a[2]-1];
				v[a[0]-1].normal[1]=norm_y[a[2]-1];
				v[a[0]-1].normal[2]=norm_z[a[2]-1];
				vector<int> b=face_info(sb);
				newf.vertices.push_back(v[b[0]-1]);
				v[b[0]-1].r=tex_r[b[1]-1];
				v[b[0]-1].s=tex_s[b[1]-1];
				v[b[0]-1].normal[0]=norm_x[b[2]-1];
				v[b[0]-1].normal[1]=norm_y[b[2]-1];
				v[b[0]-1].normal[2]=norm_z[b[2]-1];
				vector<int> c=face_info(sc);
				newf.vertices.push_back(v[c[0]-1]);
				v[c[0]-1].r=tex_r[c[1]-1];
				v[c[0]-1].s=tex_s[c[1]-1];
				v[c[0]-1].normal[0]=norm_x[c[2]-1];
				v[c[0]-1].normal[1]=norm_y[c[2]-1];
				v[c[0]-1].normal[2]=norm_z[c[2]-1];

				o.faces.push_back(newf);
		//remaining faces
		while(file>>s){
			if (s=="f"){
				Face newf;
				file>>sa>>sb>>sc;
				a=face_info(sa);
				newf.vertices.push_back(v[a[0]-1]);
				v[a[0]-1].r=tex_r[a[1]-1];
				v[a[0]-1].s=tex_s[a[1]-1];
				v[a[0]-1].normal[0]=norm_x[a[2]-1];
				v[a[0]-1].normal[1]=norm_y[a[2]-1];
				v[a[0]-1].normal[2]=norm_z[a[2]-1];
				b=face_info(sb);
				newf.vertices.push_back(v[b[0]-1]);
				v[b[0]-1].r=tex_r[b[1]-1];
				v[b[0]-1].s=tex_s[b[1]-1];
				v[b[0]-1].normal[0]=norm_x[b[2]-1];
				v[b[0]-1].normal[1]=norm_y[b[2]-1];
				v[b[0]-1].normal[2]=norm_z[b[2]-1];
				c=face_info(sc);
				newf.vertices.push_back(v[c[0]-1]);
				v[c[0]-1].r=tex_r[c[1]-1];
				v[c[0]-1].s=tex_s[c[1]-1];
				v[c[0]-1].normal[0]=norm_x[c[2]-1];
				v[c[0]-1].normal[1]=norm_y[c[2]-1];
				v[c[0]-1].normal[2]=norm_z[c[2]-1];

				o.faces.push_back(newf);
			}
		}
		
		file.close();
		o.mx = -(maxx+minx) / 2;
		o.my = -(maxy+miny) / 2;
		o.mx = -(maxz+minz) / 2;
		if(objects.size() == 2) {
			o.mx = -2.5;
			o.mz = 2.5;
		}
		objects.push_back(o);
		Light l(argc);
		lights.push_back(l);
	}
	else {
		printf("File cannot be opened\n");
	}
}



