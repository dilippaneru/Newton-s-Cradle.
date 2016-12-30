#include<iostream>
#include"mymath.h"
#include"transformation.h"

class RigidBody
{
public:
    /*constant quantities*/
    double mass;
    mat3 Ibody,Ibodyinv;


    /*State variables*/
    vec3 cm;
    quaternion q;
    vec3 P,L;


    /*Derived quantities */
    mat3 Iinv,R;
    vec3 v,w;

    /*Computed quantities*/
    vec3 force,torque;
    void diffeuler();

};

void RigidBody::diffeuler()
{
    quaternion omega;   //convert vector angular velocity vector to quaternion
    omega.s=0.0;
    omega.v = w;

    cm = cm + v*(1/6000);

    quaternion q1 = (omega*q);
    q1.scale(1.0/3000);
    q = q1 + q;


    P=P+force*(1.0/6000);


    L=L+torque*(1.0/6000);

    q.normalize();
    R = q_to_m(q);


    v=P*(1/mass);


    Iinv=mulm3m3(mulm3m3(R,Ibodyinv),transpose(R));
    w=mulm3v3(Iinv,L);
}

class cube:public RigidBody
{
public:
    vec3 vertex[8];
    cube()
    {
        mass = 1200;
        mat3 b(2000000,0,0,
               0,2000000,0,
               0,0,2000000);
        Ibody=b;
        vec3 x(0,0,0);
        P=L=v=x;
        float k= 1/2000000;
        mat3 c(k,0,0,
               0,k,0,
               0,0,k);
        Ibodyinv=c;
        mat3 d(1,0,0,
               0,1,0,
               0,0,1);
        R=d;


        vec3 zet(50,50,50);
        cm = zet;
        float hello[8][3]= {{0,0,100},{0,100,100},{100,0,100},{0,0,0},{0,100,0},{100,100,100},{100,0,0},{100,100,0}};
        for(int i=0; i<8; i++)
        {
            vertex[i].x=hello[i][0];
            vertex[i].y=hello[i][1];
            vertex[i].z=hello[i][2];
        }
    }


    void calcforce(void)
    {
        vec3 a(0,9.8,0);
        vec3 b(0,0,0);
        force = a+b;
    }
    void calctorque(void)
    {
        vec3 a(0,0,1200);
        torque = a;
    }

    void draw()
    {
        vec3 a,b;
        for(int i=0; i<8; i++)
        {
            a = mulm3v3(R,vertex[i])+cm;
            vertex[i]=a;
        }

        a = treeto(vertex[0]);
        for(int i =1; i<=3; i++)
        {
            b = treeto(vertex[i]);
            Drawline(a.x,a.y,b.x,b.y);
        }

        a = treeto(vertex[7]);
        for(int i =7; i>=4; i--)
        {
            b = treeto(vertex[i]);
            Drawline(a.x,a.y,b.x,b.y);
        }

        a = treeto(vertex[4]);
        b = treeto(vertex[1]);
        Drawline(a.x,a.y,b.x,b.y);
        b = treeto(vertex[3]);
        Drawline(a.x,a.y,b.x,b.y);

        a = treeto(vertex[6]);
        b = treeto(vertex[3]);
        Drawline(a.x,a.y,b.x,b.y);
        b = treeto(vertex[2]);
        Drawline(a.x,a.y,b.x,b.y);

        a = treeto(vertex[5]);
        b = treeto(vertex[1]);
        Drawline(a.x,a.y,b.x,b.y);
        b = treeto(vertex[2]);
        Drawline(a.x,a.y,b.x,b.y);
    }

};




class Particle
{
    double mass;
    vec3 position;
 vec3 vel;
};








