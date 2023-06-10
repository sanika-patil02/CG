/*Implement DDA and Bresenham's line drawing algorithm to draw: 
i) Simple Line
ii) Dotted Line
iii) Dashed Line 
iv) Solid line 
using mouse interface. Divide the screen in four quadrants with center as (0, 0). The line should work for all the slopes positive as well as negative.*/

#include <stdio.h>
#include <stdlib.h>
#include<GL/glut.h>

int xa,ya,xb,yb,linetype;

void bresnline(int xa,int ya,int xb,int yb,int ch)
{
	int dx,dy,d;
	int c,r,f;
		
	dx=xb-xa;
	dy=yb-ya;

	if(abs(dx)>abs(dy))
	{
		d=2*abs(dy)-abs(dx);
		
		if(dx>=0)
		{
			c=xa;
			r=ya;
			f=xb;
		}
		else
		{
			c=xb;
			r=yb;
			f=xa;
		}
	
		while(c<=f)
		{
			if(d<0)
			{
				c=c+1;
				d=d+2*abs(dy);
			}
			else
			{
				c=c+1;
				d=d+(2*abs(dy))-(2*abs(dx));
				if(dx>0 && dy>=0||dy<=0&&dx<0)
				{
					r=r+1;
				}
				else
				{
					r=r-1;
				}
		
			}
			glBegin(GL_POINTS);
			if(ch==1)
			{
				glVertex2i(c,r);
			}
			if(ch==2)
			{
				if(c%2==0)
				{
					glVertex2i(c,r);
				}
			}
			if(ch==3)
			{
				if(c%4!=0)
				{
					glVertex2i(c,r);
				}
			}
			if(ch==4)
			{
				glPointSize(5);
				glVertex2i(c,r);
			}
		        glEnd();
		}
	}
	
	else
	{
		
		d=2*abs(dx)-abs(dy);
		
		if(dy>=0)
		{
			c=xa;
			r=ya;
			f=yb;
		}
		else
		{
			c=xb;
			r=yb;
			f=ya;
		}
		
		while(r<=f)
		{
			if(d<0)
			{
				r=r+1;
				d=d+2*abs(dx);
			}
			else
			{
				r=r+1;
				d=d+2*abs(dx)-2*abs(dy);
					
				if(dy>=0 && dx>0||dy<=0 && dx<0)
				{
					c=c+1;
				}
				else
				{
					c=c-1;
				}
				
			}
			
			glBegin(GL_POINTS);
			if(ch==1)
			{
				glVertex2i(c,r);
			}
			if(ch==2)
			{
				if(c%2==0)
				{
					glVertex2i(c,r);
				}
			}
			if(ch==3)
			{
				if(c%4!=0)
				{
					glVertex2i(c,r);
				}
			}
			if(ch==4)
			{
				glPointSize(5);
				glVertex2i(c,r);
			}
			
				glEnd();
			
		}
	}
	
}


void mouse(int button,int state,int x,int y)
{
	y=480-y;
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		xa=x;
		ya=y;
	}
	if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
	{
		xb=x;
		yb=y;	
	}
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,1.0,0.0);
	bresnline(0,240,640,240,1);
	bresnline(320,0,320,480,1);
	glColor3f(1.0,0.0,0.0);
	bresnline(xa,ya,xb,yb,linetype);
	glFlush();
}

int main(int argc, char *argv[]) {
	
/*	printf("enter first vertex: ");
	scanf("%d%d", &xa,&ya);
	printf("enter second vertex: ");
	scanf("%d%d", &xb,&yb);*/

    printf("Enter the type of line:");
	printf("enter choice:1.simple\n2.dotted\n3.dashed 4.Soid");
	scanf("%d", &linetype);

	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Bresenham's Line");
	
	glClearColor(0.0,0.0,0.0,0.0);
	gluOrtho2D(0,640,0,480);

	glutDisplayFunc(draw);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}
