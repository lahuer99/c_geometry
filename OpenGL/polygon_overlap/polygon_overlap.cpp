#include<iostream>
#include<fstream>

#include<GL/freeglut.h>
#include<GL/gl.h>

using namespace std;

#define DIM 3
typedef GLfloat tPointi[DIM];
tPointi vertices[20];
int c;

void renderFunction(){
	glClearColor(0.0,0.0,0.0,0.0);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);



	glBegin(GL_QUADS);
	for(int i=0;i<c;){
		if(i==0){
			glColor3f(1.0,0.0,0.0);
		}
		else if(i==4){
			glColor3f(0.0,1.0,0.0);
		}
		else{
			glColor3f(0.0,0.0,1.0);	
		}
		glVertex3f(vertices[i][0],vertices[i][1],vertices[i][2]);
		glVertex3f(vertices[i+1][0],vertices[i+1][1],vertices[i+1][2]);
		glVertex3f(vertices[i+2][0],vertices[i+2][1],vertices[i+2][2]);
		glVertex3f(vertices[i+3][0],vertices[i+3][1],vertices[i+3][2]);
		i+=4;
	}
	glEnd();

	glFlush();
}

int main(int argc,char** argv){

	ifstream iFile("input.txt",ios::in);
	c=0;
	tPointi pd;
	while(iFile>>pd[0]>>pd[1]>>pd[2]){
		vertices[c][0]=pd[0];
		vertices[c][1]=pd[1];
		vertices[c][2]=pd[2];
		c++;
	}

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowSize(500,400);
	glutInitWindowPosition(10,10);
	glutCreateWindow("OpenGL_Q5");
	glutDisplayFunc(renderFunction);


	iFile.close();

	glutMainLoop();
	return 0;
}