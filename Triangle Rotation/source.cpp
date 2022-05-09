#include<windows.h>
#include<glut.h>
#include<iostream>

using namespace std;
GLfloat angle;

void triangle()
{
	glBegin(GL_LINE_LOOP);
	glVertex2i(100, 250);
	glVertex2i(175, 350);
	glVertex2i(250, 250);
	glEnd();
	glFlush();
}
void display()
{
	glClearColor(0.2, 1.0, 1.0, 0.0);		// set the window color to yellow
	glColor3f(0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	triangle();
	glRotatef(angle, 0.0, 0.0, 1.0);	//function computes a matrix that performs a counterclockwise rotation of angle degrees about the vector from the origin through the point (x, y, z).
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(100, 250, 0.0);
	glRotatef(angle,0.0,0.0,1.0);
	glTranslatef(-100, -250, 0.0);
	triangle();
}

void main(int argc, char** argv)
{
	cout << "Enter the angle of rotation: ";
	cin >> angle;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Trianle Rotation");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
	glutDisplayFunc(display);
	glutMainLoop();
}
