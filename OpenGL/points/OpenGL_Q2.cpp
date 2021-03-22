#include<iostream>
#include<fstream>

#include <GL/glut.h>
#include<GL/freeglut.h>
#include<GL/gl.h>
using namespace std;


void displayMe(void){
    ifstream iFile("input.txt",ios::in);

    GLfloat x,y;


    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,1.0);
    glPointSize(5);
    glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);

    glBegin(GL_POINTS);
    while(iFile>>x>>y){
        glVertex2f(x,y);
    }
    glEnd();
    glFlush();
    iFile.close();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL_q2");
    glutDisplayFunc(displayMe);
    glutMainLoop();
    return 0;
}