#include<windows.h>
#include<glut.h>
#include<stdio.h>

float x1=200, y1=200, x2=100, y2=300, x3=200, y3=400, x4=300, y4=300;
int value = 0;
void init()
{
	glClearColor(1, 1, 1, 1);
	glColor3f(1, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
}
void edge_detect(float x1, float y1, float x2, float y2,int* le,int* re)
{
	float mx,temp,x;
	int i;
	if ((y2 - y1) < 0)
	{
		temp = y1;
		y1 = y2;
		y2 = temp;
		temp = x1;
		x1 = x2;
		x2 = temp;
	}
	if ((y2 - y1) != 0)
	{
		mx = (x2 - x1) / (y2 - y1);
	}
	else
	{ 
		mx = x2 - x1;
	}
	x = x1;
	for (i = y1; i <= y2; i++)
	{
		if (x < le[i])
			le[i] = x;
		if (x > re[i])
			re[i] = x;
		x += mx;
	}
}
void drawpixel(int x, int y)
{
	glColor3f(1, 0, 1);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}
void scanfill(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	int le[500], re[500];
	int i,y;
	for (i = 0; i < 500; i++)
	{
		le[i] = 500;
		re[i] = 0;
	}
	edge_detect(x1,y1,x2,y2,le,re);
	edge_detect(x2, y2, x3, y3,le,re);
	edge_detect(x3, y3, x4, y4,le,re);
	edge_detect(x4,y4,x1,y1,le,re);
	for (y = 0; y < 500; y++)
	{
		if (le[y] <= re[y])
		{
			for(i=le[y];i<re[y];i++)
			{
				drawpixel(i, y);
				glFlush();
			}
		}
	}
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(x1,y1);
	glVertex2i(x2,y2);
	glVertex2i(x3,y3);
	glVertex2i(x4,y4);
	glEnd();
	if (value == 1)
	{
		scanfill(x1, y1, x2, y2, x3, y3, x4, y4);
	}
	glFlush();
}
void menu(int option)
{
	if (option == 1)
		value = 1;
	if(option==2)
		value = 2;
	display();
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("ScanLine Fill");
	init();
	glutDisplayFunc(display);
	glutCreateMenu(menu);
	glutAddMenuEntry("Polygon Fill", 1);
	glutAddMenuEntry("Clear", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}
