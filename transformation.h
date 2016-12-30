
#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#ifndef MYMATH_H
#include"mymath.h"
#endif

#include<iostream>
#include<cmath>
#define pi 3.1416

namespace camera
{
 float ud,lr,dx=700,dy=700,dz=500,ca,cb,cc;
}


vec3 rot_axis(vec3 point,vec3 axis,float theta);
vec3 translate(vec3 a,float tx,float ty,float tz);
vec3 treeto(vec3 p);



vec3 rot_axis(vec3 point,vec3 axis,float theta)           //x = point/vector , y = axis
{
    float a=(theta)*3.14169/180;
    quaternion p,q,qinv;
    p.s=0;
    p.v=point;
    q.s=cos(a/2);
    q.v.x=axis.x*sin(a/2);
    q.v.y=axis.y*sin(a/2);
    q.v.z=axis.z*sin(a/2);

    qinv.s=q.s;

    qinv.v.x=-q.v.x;
    qinv.v.y=-q.v.y;
    qinv.v.z=-q.v.z;

    quaternion z1= (q*(p*qinv));
    point=z1.v;
    return point;

}

vec3 translate(vec3 a,float tx,float ty,float tz)
{
    vec3 b(a.x+tx,a.y+ty,a.z+tz);
    return b;
}

/*
vec3 treeto(vec3 p)
{
    p.x = 50*p.x/p.z;
    p.y = 50*p.y/p.z;
    return p;

}
*/

vec3 treeto(vec3 p)
{
    float f=1000,n=0.1;
    float nx = 1300, ny=700;
    vec3 Lookat(0.0,0.0,0.0);
    vec3 up(0.0,1.0,0.0);
    camera::ca=camera::dx*cos(pi/4+camera::lr);
    camera::cb=camera::dy*sin(pi/4+camera::ud);
    camera::cc=camera::dz*sin(pi/4+camera::lr);
    vec3 cam(camera::ca,camera::cb,camera::cc);

    vec3 z = (cam-Lookat);
    z.normalize();

    vec3 x=cross(up,z);
    x.normalize();

    vec3 y=cross(z,x);

    p=translate(p,-cam.x,-cam.y,-cam.z);
    mat4 view(x.x, x.y, x.z,0.0,
              y.x, y.y, y.z,0.0,
              z.x, z.y, z.z,0.0,
              0.0, 0.0, 0.0,1.0);

   mat4 projection(1.0,0.0,0.0,0.0,
                    0.0,1.0,0,0.0,
                    0.0,0.0,-(f+n)/(f-n),-2*(f*n)/(f-n),
                    0.0,0.0,-1.0,0.0);



    vec4 a(p.x,p.y,p.z,1);
    mat4 T=mulm4m4(projection,view);
    a = mulm4v4(T,a);
    p.x = 0.5*((a.x/a.w+1.0)*nx+1);
    p.y = 0.5*((a.y/a.w+1.0)*ny+1);
    p.z = a.z/a.w;
    return p;


}




#endif
