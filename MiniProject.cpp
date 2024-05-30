//#include <windows.h>
//#include <stdio.h>
//#include <iostream>
#include <GL/glut.h>
#include <math.h>


int boatStatus = 1;

float boatX = 0;
float boatY = 0;



void drawBoat(int);


float move, angle;



void scene()
{


	glBegin(GL_POLYGON); //Sky  
	glColor3f(0.4, 0.5, 1.0);
	glVertex2i(0, 800);
	glVertex2i(1200, 800);
	glColor3f(0.7, 0.7, 1.0);
	glVertex2i(1200, 0);
	glVertex2i(0, 0);
	glEnd();
	
	glEnd();


	glBegin(GL_POLYGON); // River
	glColor3f(0.2, 0.3, 1.1);
	glVertex2i(0, 150);
	glVertex2i(200, 150);
	glVertex2i(400, 150);
	glVertex2i(600, 150);
	//glColor3f(0.2, 0.3, 1.1);
	glVertex2i(800, 150);
	glVertex2i(1000, 150);
	glVertex2i(1200, 150);
	glVertex2i(1200, 0);
	glVertex2i(0, 0);
	glEnd();

}




void drawBoat(int i)
{
	glPushMatrix();

	glBegin(GL_POLYGON); // Boat Starts
	glColor3f(0.7, 0.8, 0.1);//upper part
	glVertex2i(230, 100);
	glVertex2i(230, 165);
	glVertex2i(480, 165);
	glVertex2i(480, 100);
	
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.9, 0.5, 0.1);
	glVertex2i(250, 20);
	glVertex2i(220, 100);
	glVertex2i(550, 100);
	glVertex2i(500, 20);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.9, 0.1, 0.1);
	glVertex2i(235, 135);
	glVertex2i(235, 160);
	glVertex2i(270, 160);
	glVertex2i(270, 135);
	glEnd();
	glFlush();
	glPopMatrix();
}



void myInit(void)
{
	glClearColor(0.0, 0.0, 1.0, 0.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1200.0, 0.0, 800.0);
}

void keyboard(unsigned char key, int x, int y)
{

	switch (key) {
	
	case 'b':		//boat start
	case 'B':
		boatStatus = 1;
		break;
	case 'n':		//boat stop
	case 'N':
		boatStatus = 0;
		break;
	
	default:
		break;
	}
}

void boat()
{
	if (boatStatus == 1)
	{
		boatX += .5;
	}
	if (boatX>1000)
	{
		boatX = -600;
	}
	glPushMatrix();
	glTranslatef(boatX, boatY, 0);
	drawBoat(1);
	glPopMatrix();
}



void myDisplay(void)
{
	scene();
	
	boat();
	
	glFlush();

	glutPostRedisplay();
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1250, 600);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Project");
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
}
