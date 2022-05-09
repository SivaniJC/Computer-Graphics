#include<glut.h>
#include<math.h>
#include<stdio.h>

GLint xOne, yOne, xTwo, yTwo;

void resize(int, int);
void setPixel(GLint, GLint);
void HLine(GLint, GLint, GLint);
void VLine(GLint, GLint, GLint);
void lineBres(GLint, GLint, GLint, GLint, GLfloat);
void display();


void resize(int w, int h)
{									//"projection matrix" is used to create your viewing volume
	glMatrixMode(GL_PROJECTION);	//function specifies which matrix is the current matrix.
	glLoadIdentity();				//function replaces the current matrix with the identity matrix
	gluOrtho2D(0.0, w, 0.0, h);		//function defines a 2-D orthographic projection matrix
	glViewport(0.0, 0.0, w, h);		//function sets the viewport.
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);	///Clear the window-set the color of pixels in buffer
	GLfloat m;
	GLint t;

	if (xOne == xTwo)
	{
		if (yOne > yTwo)
		{
			t = yOne;
			yOne = yTwo;
			yTwo = t;
		}

		VLine(xOne, yOne, yTwo);
	}
	else if (yOne == yTwo)
	{
		HLine(xOne, yOne, xTwo);
	}
	else
	{
		m = (float)(yTwo - yOne) / (xTwo - xOne);
		if (fabs(m) < 1)
			lineBres(xOne, yOne, xTwo, yTwo, m);
		else
			lineBres( yOne, xOne, yTwo, xTwo, m);
	}
}

void lineBres(GLint x0, GLint y0, GLint xEnd, GLint yEnd,GLfloat m)
{
	GLint dx = abs(xEnd - x0);
	GLint dy = abs(yEnd - y0);
	GLint p = (2 * dy) - dx;
	GLint twoDy = 2 * dy;
	GLint twodyMinusDx = 2 * (dy - dx);
	GLint x = x0, y = y0;

	if (x0 > xEnd)
	{
		x = xEnd;
		y = yEnd;
		xEnd = x0;
		yEnd = y0;
	}
	else
	{
		x = x0;
		y = y0;
	}
	setPixel(x, y);

	while (x < xEnd)
	{
		x++;
		if (p < 0)
			p += twoDy;
		else
		{
			if (m < 0)
				y--;
			else
				y++;
			p += twodyMinusDx;
		}
		setPixel(x, y);
	}
}

void VLine(GLint x1, GLint y1, GLint y2)
{
	GLint x, y;
	x = x1;
	glBegin(GL_POINTS);
	for (y = y1; y <= y2; y++)
		glVertex2d(x, y);
	glEnd();
	glFlush();
}
void HLine(GLint x1, GLint y1, GLint x2)
{
	GLint x, y;
	y = y1;
	glBegin(GL_POINTS);
	for (x = x1; x <= x2; x++)
		glVertex2d(x, y);
	glEnd();
	glFlush();
}
void setPixel(GLint xCoord, GLint yCoord)
{
	glBegin(GL_POINTS);
	glVertex2i(xCoord, yCoord);
	glEnd();
	glFlush();
}
void myinit()
{
	glClearColor(1.0, 1.0, 0.0, 1.0);		// set the window color to yellow
	glColor3f(1.0, 0.0, 0.0);			// set the point color to red (RGB)
	glPointSize(2.0);			// set the pixel size

}
void main(int argc, char** argv)
{
	printf("\nEnter starting vertex(x1,y1): ");
	scanf_s("%d%d", &xOne, &yOne);
	printf("\nEnter ending vertex(x2,y2): ");
	scanf_s("%d%d", &xTwo, &yTwo);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	// sets the initial display mode, GLUT single-default
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(800, 50);
	glutCreateWindow("Bresenhams Line Drawing Algorithm");
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	myinit();
	glutMainLoop();
}
