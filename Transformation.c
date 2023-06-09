//TRANSFORMATION//

#include <stdio.h>
#include <stdlib.h>
#include<GL/glut.h>
#include<math.h>

float input[3][10];
float output[3][10];
float trans[3][3];
float scale[3][3];
float rotate[3][3];
float ref[3][3];
float shear[3][3];
int i,j,v,ch;
float x,y;
const float pie=3.14159;


int Round(float a)
{
  return (int)(a + 0.5);
}

void dda(float xa,float ya,float xb,float yb)
{
  float dx,dy;
  int steps;
  dx = xb - xa;
  dy = yb - ya;
  
  if(abs(dx) > abs(dy))
  {
    steps = abs(dx);
  }
  else
  {
    steps = abs(dy);
  }
  
  float xincrement,yincrement;
  
  xincrement = dx/(float)(steps);
  yincrement = dy/(float)(steps);
  
  float x,y;
  
  x = xa;
  y = ya;
  
  glVertex2d(Round(x),Round(y));
  int k;
  for(k = 0; k < steps; k++)
  {
    x = x + xincrement;
    y = y + yincrement;
    glVertex2d(Round(x),Round(y));
  }
}


void translation()
{
	float tx,ty;
	printf("Enter vales of tx,ty: ");
	scanf("%f%f",&tx,&ty);
	
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
			if (i==j)
				trans[i][j]=1;
			else
				trans[i][j]=0;
		}
		
	}
	trans[0][2]=tx;
	trans[1][2]=ty;	
}


void scaling()
{
	float xf,yf;
	float sx,sy;
	printf("Enter vales of sx,sy: ");
	scanf("%f%f",&sx,&sy);
	printf("Enter vales of xf,yf: ");
	scanf("%f%f",&xf,&yf);
	
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
		
			scale[i][j]=0;
		}
		
	}
	scale[0][0]=sx;
	scale[1][1]=sy;
	scale[0][2]=xf*(1-sx);
	scale[1][2]=yf*(1-sy);	
	scale[2][2]=1;
}


void rotation()
{
	int xf,yf;
	double degree,r;
	printf("enter angle in degrees: ");
	scanf("%lf",&degree);
	r=pie*(degree/180);
	printf("enter fixed point: ");
	scanf("%d%d",&xf,&yf);
	
	rotate[0][0]=cos(r);
	rotate[0][1]=-sin(r);
	rotate[0][2]=xf*(1-cos(r))+(yf*sin(r));
	rotate[1][0]=sin(r);	
	rotate[1][1]=cos(r);
	rotate[1][2]=yf*(1-cos(r))-(xf*sin(r));
	rotate[2][0]=0;
	rotate[2][1]=0;
	rotate[2][2]=1;
	
}


void reflection()
{
//	int ch;
	printf("enter reflection along which axis:\n1.X AXIS\n2.Y AXIS\n3.line perpendicular to XY PLANE\n4.X=Y LINE\n5.X=-Y LINE");
	scanf("%d",&ch);
	
	
	
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			ref[i][j]=0;
		}
	}
	
	if(ch==1)
	{
		ref[0][0]=1;
		ref[1][1]=-1;
		ref[2][2]=1;
		
	}
	
	if(ch==2)
	{
		ref[0][0]=-1;
		ref[1][1]=1;
		ref[2][2]=1;
		
	}
	if(ch==3)
	{
		ref[0][0]=-1;
		ref[1][1]=-1;
		ref[2][2]=1;
		
	}
	
	if(ch==4)
	{
		ref[0][1]=1;
		ref[1][0]=1;
		ref[2][2]=1;
		
	}
	
	if(ch==5)
	{
		ref[0][1]=-1;
		ref[1][0]=-1;
		ref[2][2]=1;
		
	}
	
	
}


void shearing()
{
	int ch;
	float shx,shy;
	for ( i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
			shear[i][j]=0;
			if(i==j)
			{
				shear[i][j]=1;
			}
		}
	}
	
	printf("enter your choice:\n1.x direction\n2.y direction\n3.general shear\n");
	scanf("%d",&ch);
	
	if(ch==1)
	{
		printf("Enter shearing force in x-direction: ");
		scanf("%f",&shx);
		shear[0][1]=shx;
	}
	
	if(ch==2)
	{
		printf("Enter shearing force in y-direction: ");
		scanf("%f",&shy);
		shear[1][0]=shy;
	}
	
	if(ch==3)
	{
		printf("Enter shearing force in x-direction: ");
		scanf("%f",&shx);
		printf("Enter shearing force in y-direction: ");
		scanf("%f",&shy);
		shear[1][0]=shy;
		shear[0][1]=shx;
	}
}




void multi(float matrix[3][3],float input[3][10],float output [3][10])
{
	int k;
	for(i=0;i<3;i++)
	{
		for(j=0;j<v;j++)
		{
			output[i][j]=0;
			for(k=0;k<3;k++)
			{
				output[i][j]+=matrix[i][k]*input[k][j];
			}
		}
	}
}


void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	
		dda(0,-500,0,500);
		dda(-500,0,500,0);
	
	glEnd();
	glBegin(GL_POINTS);
	
	glColor3f(0,0,1);
	int l;
	for(l=0;l<v-1;l++)
	{
	
		dda(input[0][l],input[1][l],input[0][l+1],input[1][l+1]);
	}
	dda(input[0][l],input[1][l],input[0][0],input[1][0]);
	
	glEnd();
	glBegin(GL_POINTS);
	
	int n;
	glColor3f(1,1,0);
	for(n=0;n<v-1;n++)
	{
	
		dda(output[0][n],output[1][n],output[0][n+1],output[1][n+1]);
	}
	dda(output[0][n],output[1][n],output[0][0],output[1][0]);
	glEnd();
	glFlush();
}



int main(int argc, char *argv[]) 
{
	int c,b;
	printf("Enter no of vertices: ");
	scanf("%d",&v);
	
	
	
	for (j=0;j<v;j++)
	{
		printf("Enter coordinates: ");
		scanf("%f%f",&input[0][j],&input[1][j]);

		input[2][j]=1;
	}
	
	
		printf("enter your choice:\n1.Translation\n2.Scaling\n3.Rotation\n4.Reflection\n5.Shearing");
		scanf("%d",&c);
		
		if(c==1)
		{
				
				translation();
				multi(trans,input,output);
				glutInit(&argc, argv);  
				glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
				glutInitWindowPosition(0,0);
				glutInitWindowSize(1000,1000);
				glutCreateWindow("TRANSLATION");
				glClearColor(0.0,0.0,0.0,0);  
				gluOrtho2D(-500,500,-500,500);
				glutDisplayFunc(draw);
			  	glutMainLoop();
			  	
		}
			  	
		if(c==2)
		{
				
				scaling();
				multi(scale,input,output);
				glutInit(&argc, argv);  
				glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
				glutInitWindowPosition(0,0);
				glutInitWindowSize(1000,1000);
				glutCreateWindow("SCALING");
				glClearColor(0.0,0.0,0.0,0);  
				gluOrtho2D(-500,500,-500,500);
				glutDisplayFunc(draw);
			  	glutMainLoop();
			
		}
				  
		if(c==3)
		{
				
				rotation();
				multi(rotate,input,output);
				glutInit(&argc, argv);  
				glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
				glutInitWindowPosition(0,0);
				glutInitWindowSize(1000,1000);
				glutCreateWindow("ROTATION");
				glClearColor(0.0,0.0,0.0,0);  
				gluOrtho2D(-500,500,-500,500);
				glutDisplayFunc(draw);
			  	glutMainLoop(); 
				
		}
				  
		if(c==4)
		{
				
				reflection();
				multi(ref,input,output);
				glutInit(&argc, argv);  
				glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
				glutInitWindowPosition(0,0);
				glutInitWindowSize(1000,1000);
				glutCreateWindow("REFLECTION");
				glClearColor(0.0,0.0,0.0,0);  
				gluOrtho2D(-500,500,-500,500);
				glutDisplayFunc(draw);
			  	glutMainLoop(); 
			
		}
			  	
		if(c==5)
		{
		
				shearing();
				multi(shear,input,output);
				glutInit(&argc, argv);  
				glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
				glutInitWindowPosition(0,0);
				glutInitWindowSize(1000,1000);
				glutCreateWindow("SHEARING");
				glClearColor(0.0,0.0,0.0,0);  
				gluOrtho2D(-500,500,-500,500);
				glutDisplayFunc(draw);
			  	glutMainLoop();   
		}
				
		
	
	
	
	/* 
		glutInit(&argc, argv);  
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowPosition(0,0);
		glutInitWindowSize(1000,1000);
		glutCreateWindow("2dTransformation");
		glClearColor(0.0,0.0,0.0,0);  
		gluOrtho2D(-500,500,-500,500);
		glutDisplayFunc(draw);
	  	glutMainLoop();     */
	
	return 0;
}
