#ifndef MYMATH_H
#define MYMATH_H
#include<iostream>
#include<cmath>

class vec3
{
public:
    float x;
    float y;
    float z;
    vec3();
    vec3(float ,float ,float );
    vec3 operator +(const vec3 &x1)
    {
        vec3 c;
        c.x = x+x1.x;
        c.y = y+x1.y;
        c.z = z+x1.z;
        return c;

    }
    vec3 operator -(const vec3 &x1)
    {
        vec3 c;
        c.x = x-x1.x;
        c.y = y-x1.y;
        c.z = z-x1.z;
        return c;

    }

    vec3 operator *(const float &x)
    {
        vec3 a;
        a.x*=x;
        a.y*=x;
        a.z*=x;
        return a;
    }

    void normalize()
    {
        float d = x*x + y*y+ z*z;
           d=(1.0/(sqrt(d)));
           x=x*d;
           y=y*d;
           z=z*d;

    }

    float norm()
    {
        float d = x*x + y*y+ z*z;
        return(sqrt(d));
    }
};



vec3::vec3()
    {
        x=0;
        y=0;
        z=0;
    }

vec3::vec3(float a,float b,float c)
    {
        x=a;
        y=b;
        z=c;
    }

vec3 cross(vec3 a,vec3 b)
{
    vec3 c;
    c.x = a.y*b.z-a.z*b.y;
    c.y = a.z*b.x - a.x*b.z;
    c.z = a.x*b.y - a.y*b.x;
    return c;
}

float dot(vec3 a,vec3 b)
    {
        return(a.x*b.x+a.y*b.y+a.z*b.z);
    }

class vec4
{
public:
    float x;
    float y;
    float z;
    float w;
    vec4()
    {
        x=0;
        y=0;
        z=0;
        w=0;
    }
    vec4(float a,float b,float c,float d)
    {
        x=a;
        y=b;
        z=c;
        w=d;
    }
    vec4 add(vec4 ,vec4 );
    vec4 sub(vec4,vec4);
};

vec4 add(vec4 a,vec4 b)
{
    vec4 c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    c.z = a.z + b.z;
    c.w = a.w + b.w;
    return c;
}

vec4 sub(vec4 a,vec4 b)
{
    vec4 c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    c.z = a.z - b.z;
    c.w = a.w - b.w;
    return c;
}

class mat3
{
public:
    float a[3][3];
    mat3()
    {
        for(int i=0; i<3; i++)
            for(int j=0; j<3; j++)
                a[i][j]=0.0;
    }
    mat3(float a11,float a12,float a13,
         float a21,float a22,float a23,
         float a31,float a32,float a33)
    {
        a[0][0]=a11;
        a[0][1]=a12;
        a[0][2]=a13;
        a[1][0]=a21;
        a[1][1]=a22;
        a[1][2]=a23;
        a[2][0]=a31;
        a[2][1]=a32;
        a[2][2]=a33;
    }
};

class mat4
{
public:
    float a[4][4];
    mat4()
    {
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                a[i][j]=0.0;
    }
    mat4(float a11,float a12,float a13,float a14,
         float a21,float a22,float a23,float a24,
         float a31,float a32,float a33,float a34,
         float a41,float a42,float a43,float a44)
    {
        a[0][0]=a11;
        a[0][1]=a12;
        a[0][2]=a13;
        a[0][3]=a14;
        a[1][0]=a21;
        a[1][1]=a22;
        a[1][2]=a23;
        a[1][3]=a24;
        a[2][0]=a31;
        a[2][1]=a32;
        a[2][2]=a33;
        a[2][3]=a34;
        a[3][0]=a41;
        a[3][1]=a42;
        a[3][2]=a43;
        a[3][3]=a44;
    }
};

vec3 mulm3v3(mat3 a,vec3 b)
{
    vec3 c;
    c.x = a.a[0][0]*b.x+a.a[0][1]*b.y+a.a[0][2]*b.z;
    c.y = a.a[1][0]*b.x+a.a[1][1]*b.y+a.a[1][2]*b.z;
    c.z = a.a[2][0]*b.x+a.a[2][1]*b.y+a.a[2][2]*b.z;
    return c;
}

vec4 mulm4v4(mat4 a,vec4 b)
{
    vec4 c;
    c.x = a.a[0][0]*b.x+a.a[0][1]*b.y+a.a[0][2]*b.z+a.a[0][3]*b.w;
    c.y = a.a[1][0]*b.x+a.a[1][1]*b.y+a.a[1][2]*b.z+a.a[1][3]*b.w;
    c.z = a.a[2][0]*b.x+a.a[2][1]*b.y+a.a[2][2]*b.z+a.a[2][3]*b.w;
    c.w = a.a[3][0]*b.x+a.a[3][1]*b.y+a.a[3][2]*b.z+a.a[3][3]*b.w;
    return c;
}

mat3 mulm3m3(mat3 a,mat3 b)
{
    mat3 c;
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            for(int k=0; k<3; k++)
                c.a[i][j]+= a.a[i][k]*b.a[k][j];
        }

    }
    return c;
}

mat4 mulm4m4(mat4 a,mat4 b)
{
    mat4 c(0,0,0,0,
           0,0,0,0,
           0,0,0,0,
           0,0,0,0);
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            for(int k=0; k<4; k++)
                c.a[i][j]+= a.a[i][k]*b.a[k][j];
        }

    }
    return c;
}

class quaternion
{
public:
    float s;
    vec3 v;

    quaternion()               //constructor to set no rotation condition quaternion (1,0,0,0)
    {
        s=1;
        v.x=0;
        v.y=0;
        v.z=0;
    }


    void normalize()
    {
        float d = s*s + v.x*v.x + v.y*v.y+ v.z*v.z;
        if(d==0)
        {
            s=1;
        }
         else{
           d=(1/(sqrt(d)));
           s=s*d;
           v.x=v.x*d;
           v.y=v.y*d;
           v.z=v.z*d;
         }
    }

      quaternion operator +(const quaternion &A)
    {
        quaternion q=*this;
        s = q.s + A.s;
        v.x = q.v.x + A.v.x;
        v.y = q.v.y + A.v.x;
        v.z = q.v.z + A.v.z;
        return *this;
    }

    void scale(float k)
    {
        s=k*s;
        v.x=k*v.x;
        v.y=k*v.y;
        v.z=k*v.z;
    }


    quaternion operator*(const quaternion &A)
    {
        quaternion q =*this;
        s= q.s*A.s - q.v.x*A.v.x - q.v.y*A.v.y - q.v.z*A.v.z;
        v.x= q.s*A.v.x + q.v.x*A.s + q.v.y*A.v.z - q.v.z*A.v.y;
        v.y= q.s*A.v.y +q.v.y*A.s +q.v.z*A.v.x - q.v.x*A.v.z;
        v.z= q.s*A.v.z + q.v.z*A.s +q.v.x*A.v.y - q.v.y*A.v.x;
        return *this;
    }

};

mat3 q_to_m(quaternion &orientation)
{
    mat3 rot;
    rot.a[0][0]=1-2*orientation.v.y*orientation.v.y-2*orientation.v.z*orientation.s;
    rot.a[0][1]=2*(orientation.v.x*orientation.v.y+orientation.v.z*orientation.s);
    rot.a[0][2]=2*(orientation.v.x*orientation.v.z+orientation.v.y*orientation.s);
    rot.a[1][0]=2*(orientation.v.x*orientation.v.y-orientation.v.z*orientation.s);
    rot.a[1][1]=1-2*(orientation.v.x*orientation.v.x+orientation.v.z*orientation.v.z);
    rot.a[1][2]=2*(orientation.v.y*orientation.v.z+orientation.v.x*orientation.s);
    rot.a[2][0]=2*(orientation.v.x*orientation.v.z+orientation.v.y*orientation.s);
    rot.a[2][1]=2*(orientation.v.y*orientation.v.z-orientation.v.x*orientation.s);
    rot.a[2][2]=1-2*(orientation.v.x*orientation.v.x+orientation.v.y*orientation.v.y);
    return rot;
}

mat3 transpose(mat3 m)
{
    for(int i =0;i<3;i++)
        for(int j=i+1;j<3;j++)
         {
             float c=m.a[i][j];
             m.a[i][j]=m.a[j][i];
             m.a[j][i]=c;
         }
         return m;
}

#endif
