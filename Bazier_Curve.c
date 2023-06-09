#include <stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
int input[2][4];
int i;
float q;

void BazierCurve(){
int bx,by;
for(q=0;q<=1;q+=0.001){

bx=(1-q)*(1-q)*(1-q)*input[0][0]+3*(1-q)*(1-q)*(q)*input[0][1]+3*(1-q)*(q)*(q)*input[0][2]+(q)*(q)*(q)*input[0][3];
by=(1-q)*(1-q)*(1-q)*input[1][0]+3*(1-q)*(1-q)*(q)*input[1][1]+3*(1-q)*(q)*(q)*input[1][2]+(q)*(q)*(q)*input[1][3];
glBegin(GL_POINTS);
glVertex2d(bx,by);
glEnd();
}

glFlush();
}

void display(){
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0,0.0,0.0);
glBegin(GL_POINTS);
for(i=0;i<4;i++){
glVertex2d(input[0][i],input[1][i]);
}

glEnd();
glColor3f(1.0,1.0,0.0);
BazierCurve();


glFlush();


}

int main(int argc,char**argv){
printf("Enter 4 point\n");
for(i=0;i<4;i++){
printf("%d) X:",i+1);
scanf("%d",&input[0][i]);
printf("%d) Y:",i+1);
scanf("%d",&input[1][i]);
}

glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB);
glutInitWindowSize(800,800);
glutInitWindowPosition(0,0);
glutCreateWindow("Bazier Curve");

glClearColor(0.0,0.0,0.0,0.0);
gluOrtho2D(0,800,0,800);
glutDisplayFunc(display);
glutMainLoop();




}
