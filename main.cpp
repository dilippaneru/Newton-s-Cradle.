#include "GL/freeglut.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include "mymath.h"
#include "gfunction.h"
#include "physics.h"
#include "transformation.h"
#include "scanraster.h"
#define pi 3.14167

//float Depth[1300][700];//pixel[1300][700][3];
int phys=0;

Sphere sphere2(40,0.0,100.0,-50.0,1,60,2),sphere3(40,0.0,100.0,50.0,1,-60,3), sphere1(40,0.0,100,-150.0,1,-60,1),
       sphere4(40,0.0,100.00,+150.0,1,+60,4);
const int windows_width=1300, windows_height=700;

float b=800,t,c=0.0;
cube ddd;
vec3 x21(0.0,0.0,1.0);

/*void ClearDepthBuffer()
{
    for(int i=1;i<=1300;i++)
    {
        for(int j=0;j<=700;j++)
        {
         Depth[i][j]=-1;
         /*for(int k=0;k<=3;k++)
         {
          pixel[i][j][0]=0.3;
          pixel[i][j][1]=0.8;
          pixel[i][j][2]=0.9;
         }
        }
    }
}*/

using namespace shading;
using namespace std;
using namespace camera;

int Sphere::colison()
{
    float ca=0;
    float d1;
    //cout<<55;
    if(label==1)
    {
      d1 = pow((sphere1.ty - sphere2.ty),2) + pow((sphere1.tz - sphere2.tz),2);
      if(abs(d1-6400)<50)
      {
          ca=sphere1.omega;
          sphere1.omega = sphere2.omega;
          sphere2.omega=ca;
          cout<<55;
          return 1;
      }
      return 0;
    }

    if(label==2)
    {
        d1 = pow((sphere2.tx - sphere3.tx),2) + pow((sphere2.ty - sphere3.ty),2) + pow((sphere2.tz - sphere3.tz),2);
      if(abs(d1-6400)<50)
      {
          ca=sphere2.omega;
          sphere2.omega = sphere3.omega;
          sphere3.omega=ca;
           //cout<<55;
          return 1;
       }
       return 0;
    }

    if(label==3)
    {
       d1 = pow((sphere3.tx - sphere4.tx),2) + pow((sphere3.ty - sphere4.ty),2) + pow((sphere3.tz - sphere4.tz),2);
      if(abs(d1-6400)<50)
      {
          ca=sphere3.omega;
          sphere3.omega = sphere4.omega;
          sphere4.omega=ca;
          cout<<55;
          return 1;
        }
        return 0;
    }
    if(label==4)
    {
       d1 = pow((sphere3.tx - sphere4.tx),2) + pow((sphere3.ty - sphere4.ty),2) + pow((sphere3.tz - sphere4.tz),2);
      if(abs(d1-6400)<50)
      {
         ca=sphere3.omega;
          sphere3.omega = sphere4.omega;
          sphere4.omega=ca;
           cout<<55;
          return 1;
      }
      return 0;
    }
}


void physics(void)
{
    ddd.calcforce();
    ddd.calctorque();
    ddd.draw();
    ddd.diffeuler();
    glutPostRedisplay();
}
void keyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 27: // Escape key
        exit(0);
        break;
    case 'l':
        glutPostRedisplay();
    case 'r':
        //physics();
        c+=1;
        glutPostRedisplay();
        break;
     case 'e':
        //physics();
        c-=1;
        glutPostRedisplay();
        break;
    case 't':
        camera::ud+=0.1;
        glutPostRedisplay();
        break;
    case 'v':
        camera::ud-=0.1;
        glutPostRedisplay();
        break;

    case 'a':
        camera::lr+=0.05;
        glutPostRedisplay();
        break;

    case 'd':
        camera::lr-=0.05;
        glutPostRedisplay();
        break;
    case 's':
       shading::wireframe *= -1 ;
        glutPostRedisplay();
        break;
    case 'w':
        camera::dy+=25;
        glutPostRedisplay();
        break;
     case 'x':
        camera::dy-=25;
        glutPostRedisplay();
        break;
      case 'h':
        camera::dx+=10;
        camera::dy+=10;
        glutPostRedisplay();
        break;
    case 'p':
        phys=not(phys);
        glutPostRedisplay();
        break;

    default:
        cout << "Unhandled key press " << key << "." << endl;
    }

    glutPostRedisplay();
}




void display(void)
{

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //ClearDepthBuffer();
    glColor3f (0.0, 0.0, 0.0);
    c+=0;
    vec3 x2(0.0,1.0,0.0);
    for(int i=0; i<8; i++)
    {
        ddd.vertex[i] = rot_axis(ddd.vertex[i]-ddd.cm,x2,c);

    }
    //ddd.draw();
    Chessfloor a;

    sphere1.draw();
    sphere2.draw();
    sphere3.draw();
    sphere4.draw();
    if(phys==1)
   {
    sphere1.physics();
    sphere2.physics();
    sphere3.physics();
    sphere4.physics();
   }

    DrawLTop();
    DrawRTop();

    //courabcg.draw();




    //physics();
    glutPostRedisplay();
    glutSwapBuffers();
    glFlush ();
}





void init (void)
{
    glClearColor(0.3,0.8,0.9, 1.0);
    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
   // glLoadIdentity();
    gluOrtho2D(0.0,windows_width,0.0,windows_height);
    //glShadeModel(GL_SMOOTH);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);
    glutInitWindowSize (1300, 700);
    glutInitWindowPosition (25, 25);
    glutCreateWindow ("GraPhyX");
    init();
    glutKeyboardFunc(keyboardFunc);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

