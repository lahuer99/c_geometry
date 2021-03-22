#include<iostream>
#include<fstream>

#include<GL/freeglut.h>
#include<GL/gl.h>

using namespace std;

#define DIM 2
typedef GLfloat tPointi[DIM];
tPointi vertices[20];
int c;

void renderFunction(){
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.64,0.164,0.164);
	glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);

	glBegin(GL_LINE_STRIP);
		for(int i=0;i<c;i++){
			glVertex2f(vertices[i][0],vertices[i][1]);
		}
	glEnd();

	glFlush();
}



int main(int argc, char** argv)
{
	ifstream iFile("input.txt",ios::in);

	c=0;
	tPointi pd;
	while(iFile>>pd[0]>>pd[1]){
		vertices[c][0]=pd[0];
		vertices[c][1]=pd[1];
		c++;
	}

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(500,400);
	glutInitWindowPosition(200,100);
	glutCreateWindow("OpenGL_Q3");
	glutDisplayFunc(renderFunction);

	iFile.close();
	glutMainLoop();
	return 0;
}