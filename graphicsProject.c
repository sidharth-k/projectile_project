#include<GL/glut.h>
#include<stdlib.h>
#include<GL/freeglut.h>
#include<GL/gl.h>
#include<math.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#define pi 3.141592654
#define g 9.81
float x_0 =0 , y_0=0,x=0,y=0  ,  xl ,yl ,xt,yt;
float tmp;
float theta;
float v_0; //meters per second
float tof ;
float del_t;
int draw_endpoint = 0;
int n_points = 100;
float X[100],Y[100];
void mouse(int button, int state , int x1,int y1)
{
printf("%d %d\n",x1,y1);
xl = x1/2; //depends on the scaling that needs to be done after checking the values of glortho2D and the size of our window.!!
yl = 300-y1/2;
tmp = yl/xl;
if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
theta = atan(tmp);
}
void idle(void)
{
  draw_endpoint = (draw_endpoint + 1) % n_points;
  glutPostRedisplay();
  usleep(del_t*100000);//check
}
void calc(void)
{
int i;
tof = 2*v_0*sin(theta)/g;
  del_t = tof/100;
  float temp=0;
for(i=0;i<100;i++)
  {
  x = v_0*cos(theta)*temp;
  y = v_0*sin(theta)*temp - ((g*temp*temp)/2);
  X[i]=x;
  Y[i]=y;
  temp += del_t;
  }
}
void display(void)
{
  char *ar = "angle of throw is ";
  int n;
  float eta = (theta*180)/pi;
  n = eta;
  char str[15];
  sprintf(str, "%d", n);
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0.7f,0.9f,1.0f,0.0f);
  glRasterPos2i(xl, yl);
  glutBitmapString(GLUT_BITMAP_HELVETICA_18, ar);
  glutBitmapString(GLUT_BITMAP_HELVETICA_18, str);
  glBegin(GL_LINES);
  glVertex2f(x_0,y_0);
  glVertex2f(xl,yl);
  glEnd();
  glPointSize(50.0);
  glBegin(GL_POINTS);
  glColor3f(1.0,0.0,0.0);
  glVertex2f(xt,yt);
  glEnd();
  glPointSize(2.0);
  glBegin(GL_POINTS);
  glColor3f(0.0,0.0,0.0);
  calc();
  int i;
  for(i=0;i<draw_endpoint;i++)
  glVertex2f(X[i],Y[i]);
  glEnd();
  glFlush();
}

int main(int argc, char**argv)
{
float v;
printf("enter the value of initial velocity\n"); //Enter speed more than 30 for some substantial output
scanf("%f",&v_0);
glutInit(&argc, argv);
xt = (rand()%100)+100;
yt = (rand()%100)+100;
 printf("%d,%d \n",xt,yt);
 glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
 glutInitWindowSize (800, 600);
 glutInitWindowPosition (0,0);
 glutCreateWindow ("Projectile Motion");
 glClearColor(0.0,0.0,0.0,0.0);
 glMatrixMode(GL_PROJECTION);
 gluOrtho2D(0.0,400.0,0.0,300.0);
 glutDisplayFunc(display);
 glutMouseFunc(mouse);
 glutIdleFunc(idle);
 glutMainLoop();

 return 0;
}
