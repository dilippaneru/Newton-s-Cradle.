#ifndef SCANRASTER_H
#define SCANRASTER_H
#include"mymath.h"

namespace shading
{
int wireframe=1;
}

class Edge
{
public:
    vec3 Color1, Color2;
    int X1, Y1, X2, Y2;
    Edge(const vec3 &color1, int x1, int y1, const vec3 &color2, int x2, int y2);
};

class Span
{
public:
    vec3 Color1, Color2;
    int X1, X2;
    Span(const vec3 &color1, int x1, const vec3 &color2, int x2);
};


void DrawSpan( Span &span, int y);
void DrawSpansBetweenEdges( Edge &e1,  Edge &e2);
void Triangle( vec3 &color1, int x1, int y1,
               vec3 &color2, int x2, int y2,
               vec3 &color3, int x3, int y3,int scolor);


void DrawBetweenEdges(Edge, Edge);

Span::Span(const vec3 &color1, int x1, const vec3 &color2, int x2)
{
    if(x1 < x2)
    {
        Color1 = color1;
        X1 = x1;
        Color2 = color2;
        X2 = x2;
    }
    else
    {
        Color1 = color2;
        X1 = x2;
        Color2 = color1;
        X2 = x1;
    }
}

Edge::Edge( const vec3 &color1, int x1, int y1,
            const vec3 &color2, int x2, int y2)
{
    vec3 Color1,Color2;
    if(y1 < y2)
    {
        Color1 = color1;
        X1 = x1;
        Y1 = y1;
        Color2 = color2;
        X2 = x2;
        Y2 = y2;
    }
    else
    {
        Color1 = color2;
        X1 = x2;
        Y1 = y2;
        Color2 = color1;
        X2 = x1;
        Y2 = y1;
    }
}


void Triangle( const vec3 &color1, int x1, int y1,
               const vec3 &color2, int x2, int y2,
               const vec3 &color3, int x3, int y3,int scolor,vec3 normal)
{
    int lightcolor;
    float lc;
    if (shading::wireframe==-1)return;

    normal.normalize();
    vec3 L(0.0,300.0,00);
    vec3 V(camera::ca,camera::cb,camera::cc);
    //vec3 H = (L + V);
    //H.normalize();
    L.normalize();
    V.normalize();
    lightcolor = 1.0*100+0.4*200*dot(L,normal)+1*200*pow(dot(normal,V),50);
    lc = 0.25*pow(4,(float)lightcolor/256);

    if (scolor==3)
    {
        glColor3f(lc*240/255,lc*240/255,lc*240/255);
    }
    else if (scolor==2)
    {
        glColor3f(lc*00/255,lc*00/255,lc*00/255);
    }
    else if (scolor==4)
    {
        glColor3f(lc*135/255,lc*196/255,lc*250/255);
    }
    else
    {
        glColor3f(lc*158/255,lc*182/255,lc*250/255);
    }
    Edge tempa(color1, x1, y1, color2, x2, y2);
    Edge tempb(color2, x2, y2, color3, x3, y3);
    Edge tempc(color3, x3, y3, color1, x1, y1);
    Edge edges[3]= {tempa,tempb,tempc};
    int maxLength = 0;
    int longEdge = 0;
    for(int i = 0; i < 3; i++)
    {
        int length = edges[i].Y2 - edges[i].Y1;
        if(length > maxLength)
        {
            maxLength = length;
            longEdge = i;
        }
    }
    int shortEdge1 = (longEdge + 1) % 3;
    int shortEdge2 = (longEdge + 2) % 3;
    // draw spans between edges; the long edge can be drawn
    // with the shorter edges to draw the full triangle
    DrawSpansBetweenEdges(edges[longEdge], edges[shortEdge1]);
    DrawSpansBetweenEdges(edges[longEdge], edges[shortEdge2]);
}

void DrawSpansBetweenEdges( Edge &e1,  Edge &e2)
{
    // calculate difference between the y coordinates
    // of the first edge and return if 0
    float e1ydiff = (float)(e1.Y2 - e1.Y1);
    if(e1ydiff == 0.0f)
        return;

    // calculate difference between the y coordinates
    // of the second edge and return if 0
    float e2ydiff = (float)(e2.Y2 - e2.Y1);
    if(e2ydiff == 0.0f)
        return;
    // calculate differences between the x coordinates
    // and colors of the points of the edges
    float e1xdiff = (float)(e1.X2 - e1.X1);
    float e2xdiff = (float)(e2.X2 - e2.X1);

    vec3 e1colordiff = (e1.Color2 - e1.Color1);
    vec3 e2colordiff = (e2.Color2 - e2.Color1);
    // calculate factors to use for interpolation
    // with the edges and the step values to increase
    // them by after drawing each span
    float factor1 = (float)(e2.Y1 - e1.Y1) / e1ydiff;
    float factorStep1 = 1.0f / e1ydiff;
    float factor2 = 0.0f;
    float factorStep2 = 1.0f / e2ydiff;
    // loop through the lines between the edges and draw spans
    for(int y = e2.Y1; y < e2.Y2; y++)
    {
        // create and draw span
        Span span(e1.Color1 + (e1colordiff * factor1),
                  e1.X1 + (int)(e1xdiff * factor1),
                  e2.Color1 + (e2colordiff * factor2),
                  e2.X1 + (int)(e2xdiff * factor2));
        DrawSpan(span, y);

        // increase factors
        factor1 += factorStep1;
        factor2 += factorStep2;
    }
}
void DrawSpan( Span &span, int y)
{
    int xdiff = span.X2 - span.X1;
    if(xdiff == 0)
        return;

    vec3 colordiff = span.Color2 - span.Color1;
    float factor = 0.0f;
    float factorStep = 1.0f / (float)xdiff;
    // draw each pixel in the span
    vec3 acdc;
    glBegin(GL_POINTS);
    for(int x = span.X1; x < span.X2; x++)
    {

        acdc=span.Color1 + (colordiff * factor);
        //glColor3f(acdc.x,acdc.y,acdc.z);
        glVertex2i(x, y);
        factor += factorStep;
    }
    glEnd();
}





#endif // SCANRASTER_H

