#ifndef __XFORM_H
#define __XFORM_H

#include <pixel.h>
#include <math.h>
#include <values.h>
#include <iostream.h>

#define Ln10        2.30358509299405E+000
#define OneOverLn10 0.43429448190325E+000
#define Pi          3.1415927
#define PiOver180   1.74532925199433E-002
#define PiUnder180  5.72957795130823E+001

#define Radians(Theta)  PiOver180*(Theta)
#define Cavalier_Alpha 0.7853981633974485E+000
#define Cabinet_Alpha  1.1065387457644051E+000

#define X_Axis     0x00
#define Y_Axis     0x01
#define Z_Axis     0x02

#define yz_Plane   0x00
#define zx_Plane   0x01
#define xy_Plane   0x02

typedef unsigned char byte;

class XForm;

// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                            <<>>
// <<>>          Vector Class Declaration          <<>>
// <<>>                                            <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>

class Vector
 {
   public :

    float x,y,z;

   public :

    Vector();
    Vector(float X,float Y,float Z);
    void  Vectorise(float X,float Y,float Z);

    float  Len();
    void   UnitVector();
    Vector cross(Vector V);
    float  dot(Vector V);
    int    IsZeroVector();
    void   Abs();
    Vector ProjectionOn(byte Plane);
    int    ClosestProjectionPlane(Vector A,Vector B);
    float  Angle(Vector V);
    void   VecStatus();
    void   Get(char **S,Vector vMin,Vector vMax);
    //void   Out(char **S);

    // Operators
    int    operator >(Vector V);
    Vector operator *(float i);
    Vector operator /(float i);

    Vector operator +(Vector V);
    Vector operator -(Vector V);

    Vector operator *=(float i);
    Vector operator /=(float i);

    Vector operator +=(Vector V);
    Vector operator -=(Vector V);

    Vector operator *(XForm M);
    Vector operator *=(XForm M);

    void   OutVector();
    friend class XForm;
    friend void Plot3D(Vector V,byte Color);
    friend byte Color3D(byte Color,Vector V);
 };

// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                            <<>>
// <<>>          XForm Class Declaration           <<>>
// <<>>                                            <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>

class XForm
 {
  protected :

   float Mat[4][4];

  private :

   void Assign(float f);

  public :

   XForm();
   XForm(float f);

   XForm Zero();
   XForm Identity();
   XForm Scale3D(Vector Scale);
   XForm Translate3D(Vector Tran);
   XForm RotateAbout(byte About, float Theta);
   XForm ShearAbout(byte About,float Shear);
   XForm Rotate3D(Vector SolidAngle);
   XForm Shear3D(Vector Shear);
   XForm NormalToAxisZ(Vector Normal);
   XForm zAxisToNormal(Vector Normal);
   XForm Perspective(int Cx,int Cy,Vector Eye);
   XForm Parallel(int Cx,int Cy,double Alpha,double Phi,byte Deg);
   XForm Cavalier(int Cx,int Cy,float Phi);
   XForm Cabinet(int Cx,int Cy,float Phi);
   void  Display(char *Lbl);

   XForm operator *(float f);
   XForm operator /(float f);

   XForm operator *(XForm M);

   XForm operator *=(float f);
   XForm operator /=(float f);

   XForm operator *=(XForm M);

   friend class Vector;
 };

 extern XForm Map3D;
#endif