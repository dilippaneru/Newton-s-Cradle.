#include<iostream>
#include"mymath.h"
#include"transformation.h"
#include"scanraster.h"
#include<cmath>


float PI = 3.1416;
float timestep=0.5;
float gravity=-10.0;
void Drawline(int x1, int y1, int x2, int y2);
void Drawtriangle(int x1,int y1,int x2,int y2,int x3,int y3);
void DrawLTop()
{
    int y=400,x1=-100;
    float vdata[8][3]=
    {
        {15+x1,y, 200},{-15+x1, y, 200},{15+x1, y, -200},{-15+x1, y, -200},
        {15+x1,y+5, 200},{-15+x1, y+5, 200},{15+x1, y+5, -200},{-15+x1, y+5, -200},
     };
   int tindices[12][3]=
     {
       {5,1,0},{5,0,4},{4,0,2},{4,2,6},{6,2,3},{6,3,7},
       {5,4,6},{5,6,7},{1,5,7},{1,7,3},{1,2,0},{1,3,2},
       };

     for (int i = 0; i < 12; i++)
    {

        vec3 a=treeto(vec3(vdata[tindices[i][0]][0],vdata[tindices[i][0]][1],vdata[tindices[i][0]][2]));
        vec3 b=treeto(vec3(vdata[tindices[i][1]][0],vdata[tindices[i][1]][1],vdata[tindices[i][1]][2]));
        vec3 c=treeto(vec3(vdata[tindices[i][2]][0],vdata[tindices[i][2]][1],vdata[tindices[i][2]][2]));
        Drawtriangle(a.x,a.y,b.x,b.y,c.x,c.y);
        vec3 normal = cross((c-b),(a-b));
        Triangle(vec3(1.0,0.0,0.0),a.x,a.y, vec3(1.0,0.0,0.0), b.x,b.y, vec3(1.0,0.0,0.0),c.x,c.y,4,normal);
      }
}

void DrawRTop()
{
    int y=400,x1=+100;
    float vdata[8][3]=
    {
        {15+x1,y, 200},{-15+x1, y, 200},{15+x1, y, -200},{-15+x1, y, -200},
        {15+x1,y+5, 200},{-15+x1, y+5, 200},{15+x1, y+5, -200},{-15+x1, y+5, -200},
    };
    int tindices[12][3]=
    {
        {5,1,0},{5,0,4},{4,0,2},{4,2,6},{6,2,3},{6,3,7},
        {5,4,6},{5,6,7},{1,5,7},{1,7,3},{1,2,0},{1,3,2},
    };

    for (int i = 0; i < 12; i++)
    {

        vec3 a=treeto(vec3(vdata[tindices[i][0]][0],vdata[tindices[i][0]][1],vdata[tindices[i][0]][2]));
        vec3 b=treeto(vec3(vdata[tindices[i][1]][0],vdata[tindices[i][1]][1],vdata[tindices[i][1]][2]));
        vec3 c=treeto(vec3(vdata[tindices[i][2]][0],vdata[tindices[i][2]][1],vdata[tindices[i][2]][2]));
        Drawtriangle(a.x,a.y,b.x,b.y,c.x,c.y);
        vec3 normal = cross((c-b),(a-b));
        Triangle(vec3(1.0,0.0,0.0),a.x,a.y, vec3(1.0,0.0,0.0), b.x,b.y, vec3(1.0,0.0,0.0),c.x,c.y,4,normal);
    }
}

class Chessfloor
{
  private:
      float x=500,y=0,z=500;
  public:
      Chessfloor();
};

 Chessfloor::Chessfloor()
 {

    float vdata[9][3]=
    {
        {x, -100, z},{x, -100, 0},{x, -100, -z},
        {0, -100, z},{0, -100, 0},{0, -100, -z},
        {-x, -100, z},{-x,-100, 0},{-x,-100, -z},
    };
    int tindices[8][3]=
    {
       {0,1,4},{0,4,3},{1,2,4},{4,2,5},
       {6,3,4},{6,4,7},{4,5,8},{4,8,7},
    };
    for (int i = 0; i < 8; i++)
    {

        vec3 a=treeto(vec3(vdata[tindices[i][0]][0],vdata[tindices[i][0]][1],vdata[tindices[i][0]][2]));
        vec3 b=treeto(vec3(vdata[tindices[i][1]][0],vdata[tindices[i][1]][1],vdata[tindices[i][1]][2]));
        vec3 c=treeto(vec3(vdata[tindices[i][2]][0],vdata[tindices[i][2]][1],vdata[tindices[i][2]][2]));
        Drawtriangle(a.x,a.y,b.x,b.y,c.x,c.y);
        vec3 normal = cross((c-b),(a-b));
        if((i==0)||(i==1)||(i==6)||(i==7))
         {
             Triangle(vec3(1.0,0.0,0.0),a.x,a.y, vec3(1.0,0.0,0.0), b.x,b.y, vec3(1.0,0.0,0.0),c.x,c.y,2,normal);
         }
          else
           {
            Triangle( vec3(1.0,0.0,0.0),a.x,a.y, vec3(1.0,0.0,0.0), b.x,b.y, vec3(1.0,0.0,0.0),c.x,c.y,3,normal);
           }
      }
}


class Sphere
{
    private:

    float theta,omega,alpha;
    int radius,label;
    float mass;
    float X,Z;
    float tx,ty,tz,x,y,z;
    float vy,vz;
    int scolor;
    float time;
    static GLfloat vdata[12][3];
    static GLuint tindices[20][3];

    public:

    Sphere(int r,int x,int y, int z,int w,float angle,int l);
    void draw(void);
    void subdivide(float *v1, float *v2, float *v3,long depth);
    void normalise(float v[3]);
    void physics();
     int colison();
};


void Sphere::physics()
{
   /*if(colison()==1)
    {
      return;
     }*/
    time += timestep;
    alpha = (gravity*sin(theta)/300);


    omega += alpha*timestep;
    theta += omega*timestep;

    ty = y + (300-300*cos(theta));
    tz = z + 300*sin(theta);


    vy += 200*omega*cos(theta);
    vz += 200*omega*sin(theta);

}



Sphere::Sphere(int r,int a,int b,int c,int w,float angle,int l)
{
    label=l;
    scolor=w;
    theta = angle*3.1416/180,omega=00;
    radius = r;
    X = 0.525731112119133606*radius;
    Z = 0.850650808352039932*radius;
    tx=a;
    ty=b;
    tz=c;
    x=a;
    y=b;
    z=c;
    mass=100;
}

void Sphere::draw()
{

    Drawline(treeto(vec3(tx,ty,tz)).x,treeto(vec3(tx,ty,tz)).y,treeto(vec3(x+100,y+300,z)).x,treeto(vec3(x+100,y+300,z)).y);
    Drawline(treeto(vec3(tx,ty,tz)).x,treeto(vec3(tx,ty,tz)).y,treeto(vec3(x-100,y+300,z)).x,treeto(vec3(x-100,y+300,z)).y);
    static GLfloat vdata[12][3] =
    {
        {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},
        {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},
        {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0}
    };

     static GLint tindices[20][3] =
    {
        {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},
        {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},
        {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6},
        {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11}
    };

    for (int i = 0; i < 20; i++)
    {
        for (i = 0; i < 20; i++)
        {
            subdivide(&vdata[tindices[i][0]][0],&vdata[tindices[i][1]][0],&vdata[tindices[i][2]][0],3);
        }

    }

}

void Sphere::subdivide(float *v1, float *v2, float *v3,long depth)
{
    GLfloat v12[3], v23[3], v31[3];
    GLint i;
    if (depth == 0)
    {
        vec3 a11=treeto(vec3(v1[0]+tx,v1[1]+ty,v1[2]+tz));
        vec3 a21=treeto(vec3(v2[0]+tx,v2[1]+ty,v2[2]+tz));
        vec3 a31=treeto(vec3(v3[0]+tx,v3[1]+ty,v3[2]+tz));
        vec3 normal= vec3((v1[0]+v2[0]+v3[0])/3,(v1[1]+v2[1]+v3[1])/3,(v1[2]+v2[2]+v3[2])/3);
        vec3 Visible(camera::ca-normal.x,camera::cb-normal.y,camera::cc-normal.z);
        Visible.normalize();
        normal.normalize();
        if(dot(normal,Visible)>0)
        {
         Drawtriangle(a11.x,a11.y, a21.x,a21.y,a31.x,a31.y);
         Triangle( vec3(1.0,0.0,0.0),a11.x,a11.y, vec3(1.0,0.0,0.0), a21.x,a21.y, vec3(1.0,0.0,0.0),a31.x,a31.y,scolor,normal);
        }
        return;
    }

    for (i = 0; i < 3; i++)
    {
        v12[i] = v1[i]+v2[i];
        v23[i] = v2[i]+v3[i];
        v31[i] = v3[i]+v1[i];
    }
    normalise(v12);
    normalise(v23);
    normalise(v31);
    subdivide(v1, v12, v31, depth-1);
    subdivide(v2, v23, v12, depth-1);
    subdivide(v3, v31, v23, depth-1);
    subdivide(v12, v23, v31, depth-1);
}
void Sphere::normalise(float v[3])
{
    GLfloat d = sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
    if (d == 0.0)
    {
        return;
    }
    v[0] /= d/radius;
    v[1] /= d/radius;
    v[2] /= d/radius;
}

void bezier (void)
{
    float f=0;
    float x,y;
    //float a[4][4]={{1,-3,3,-1},{0,3,-6,3},{0,0,3,-3},{0,0,0,1}};
    glPointSize(1.0);
    glBegin(GL_POINTS);
    for(int i=1; i<=1000; i++)
    {
        float d[4]= {1,f,f*f,f*f*f};
        x =150*(1-3*d[1]+3*d[2]-d[3])+200*(3*d[1]-6*d[2]+3*d[3])+300*(3*d[2]-3*d[3])+500*d[3];
        y =150*(1-3*d[1]+3*d[2]-d[3])+500*(3*d[1]-6*d[2]+3*d[3])+50*(3*d[2]-3*d[3])+500*d[3];
        glVertex3f(x,y,0.0);
        f+=0.001;
    }
    glEnd();
}

void Drawline(int x1, int y1, int x2, int y2)
{
    GLint x,y,s,p;
    if(x1>x2)
    {
        x=x1,y=y1;
        x1=x2,y1=y2;
        x2=x,y2=y;
    }
    int dx=x2-x1,dy=y2-y1;
    //glColor3f(1,0,0);
    glBegin(GL_POINTS);
    glVertex2i(x1,y1);

    if(dy>=0)
        s=1;
    else
        s=-1;


    if(abs(dy)<=abs(dx))
    {
        p=2*s*dy-dx;
        for(int k=x1; k<x2; k++)
        {
            x1++;
            if(p<0)
                p+=2*s*dy;
            else
            {
                y1+=s;
                p+=2*(s*dy-dx);
            }
            glVertex2i(x1,y1);
        }
    }

    else if(abs(dy)>abs(dx))
    {
        p=2*s*dx-dy;
        while (y1!=y2)
        {
            y1+=s;
            if (dy>=0)
            {
                if (p<=0)
                    p+=2*s*dx;
                else
                {
                    x1=x1+1;
                    p+=2*(s*dx-dy);
                }
            }
            else
            {
                if(p<=0)
                {
                    x1++;
                    p=p+2*(s*dx-dy);
                }
                else
                    p=p+2*s*dx;
            }
            glVertex2i(x1,y1);
        }
    }
    glEnd();
}





void Drawtriangle(int x1,int y1,int x2,int y2,int x3,int y3)
{
    Drawline(x1,y1,x2,y2);
    Drawline(x2,y2,x3,y3);
    Drawline(x1,y1,x3,y3);
}

