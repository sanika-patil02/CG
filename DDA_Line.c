#include<stdio.h>
#include<GL/glut.h>

int lineType;
int xa, ya, xb, yb;

int Round(float a)
{
    return(int)(a + 0.5);
}

void ddaline(int xa, int ya, int xb, int yb, int lineType)
{
    int dx, dy, steps;
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
    
    float xincrement, yincrement;
    xincrement = dx / (float)(steps);      //type cast
    yincrement = dy / (float)(steps);
   
    float x, y;
    x = xa;
    y = ya;
   
    glBegin(GL_POINTS);
    glVertex2i(Round(x), Round(y));
   
    int k;
    for(k = 0; k < steps; k++)
    {    
       
        if(lineType==4){
            glPointSize(5);
            x = x + xincrement;
            y = y + yincrement;
            glVertex2i(Round(x), Round(y));
        }
        
        else if(lineType==3){
            if(k%4!=0){
                glVertex2i(Round(x), Round(y));
            }
            x = x + xincrement;
            y = y + yincrement;
        }
        
        else if(lineType==2){
            if(k % 2== 0)
            {
                glVertex2i(Round(x), Round(y));
            }
            x = x + xincrement;
            y = y + yincrement;
        }
        
        else{
            x = x + xincrement;
            y = y + yincrement;
            glVertex2i(Round(x), Round(y));
        }
       
    }
   
    glEnd();
    glFlush();
}

void mouse1(int button, int state, int x, int y) {
     y = 480-y;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
       xa=x;
       ya=y;
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        xb=x;
        yb=y;
      
    }
}

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,1.0,0.0);
    ddaline(0,240,640,240,1);
    ddaline(320,0,320,480,1);
    glColor3f(1.0,0.0,0.0);
    ddaline(xa, ya, xb, yb, lineType);
	glFlush(); 
   
}

int main(int argc, char **argv)
{
   
    printf("Enter what type of line to draw (1. Simple 2. Dotted 3. Dashed 4. Solid) ");
    scanf("%d",&lineType);
    printf("Drag a line across the screen");
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);
    glutCreateWindow("DDA Line");
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(0, 640, 0, 480);
   
    glutDisplayFunc(Draw);
    glutMouseFunc(mouse1);
    glutMainLoop();
   
    return 0;
}
