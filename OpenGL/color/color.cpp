#include<iostream>
#include<fstream>

#include <GL/glut.h>
#include<GL/freeglut.h>
#include<GL/gl.h>
using namespace std;

void displayMe(void){
    ifstream iFile("input.txt",ios::in);

    GLfloat r,g,b,a;

    iFile>>r>>g>>b>>a;
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
    iFile.close();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL_q1");
    glutDisplayFunc(displayMe);
    glutMainLoop();
    return 0;
}