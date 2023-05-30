#include <GL/glut.h>
#include<stdio.h>
#include<math.h>

bool mousepressedbefore=false;
double X,Y;
double radius;
int xMouse,yMouse,x;
double y;


int WindowWidth,WindowHeight;

void DrawPoint(double m,double n){
	glBegin(GL_POINTS);
	glVertex2d(m,n);
	glEnd();
}

void DrawCircleInAllQuadrants(double xc,double yc,double x,double y){
	DrawPoint(x+xc,y+yc);
	DrawPoint(y+xc,x+yc);
	
	DrawPoint(-x+xc,y+yc);
	DrawPoint(-y+xc,x+yc);
	
	DrawPoint(-x+xc,-y+yc);
	DrawPoint(-y+xc,-x+yc);
	
	DrawPoint(x+xc,-y+yc);
	DrawPoint(y+xc,-x+yc);
}

void bresenhamcircle(double xc,double yc,double r){
	
	 x=0;
	 y=r;
	double pk=3-2*(r);
	
	while(x<=y){
		if(pk<0){
			x++;
			pk=pk+4*(x)+6;
		}
		
		else{
			x++;
			y--;
			pk=pk+4*(x-y)+10;
		}
		DrawCircleInAllQuadrants(xc,yc,x,y);
	}
	
	glFlush();
}

int MouseYToWindowY(int y){
	return WindowHeight/2 - y;
}

double distancebetween2points(int dx,int dy,int bx,int by){
	return sqrt(pow(dx-bx,2)+pow(dy-by,2));
}

void mouseI(int button,int action,int x,int y){
	if(button==GLUT_LEFT_BUTTON && action==GLUT_DOWN){
		if(mousepressedbefore==false){
	    		xMouse=x;
	    		//y1=y;
		 	yMouse=MouseYToWindowY(y);
			mousepressedbefore=true;
		}
		
		else{
		mousepressedbefore=false;
			
			radius=distancebetween2points(xMouse,yMouse,x,y);
			bresenhamcircle(xMouse,yMouse,radius);
			
		}
		
	}
}

void axes(){
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINES);
	glVertex2i(0,-WindowWidth/2);
	glVertex2i(0,WindowWidth/2);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex2i(-WindowHeight/2,0);
	glVertex2i(WindowHeight/2,0);
	glEnd();
	glFlush();
}


void display(){
	axes();
	glColor3f(1.0,0.0,0.0);
	bresenhamcircle(X,Y,radius);
	glFlush();
	}


void Init(){

	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	//glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-WindowWidth/2,WindowWidth/2,-WindowHeight/2,WindowHeight/2);
}

int main(int argc, char *argv[]) {

	WindowWidth=800;
	WindowHeight=800;
	/*printf("Coordinates of centre:");
	scanf("%lf %lf",&X,&Y);
	
	
	
	printf("Radius of circle:");
	scanf("%lf",&radius);*/
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WindowWidth,WindowHeight);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Bresenham's Circle");
	
	/*glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	//glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-WindowWidth/2,WindowWidth/2,-WindowHeight/2,WindowHeight/2);*/
	Init();
	
	glutDisplayFunc(display);
	
	glutMouseFunc(mouseI);
	glutMainLoop();
	return 0;
}
