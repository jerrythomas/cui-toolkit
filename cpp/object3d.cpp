#include <XForm3d.h>
#include <Pixel.h>
#include <kbd.h>
#include <Bmp.h>
#include <Menu3D.h>

#define WireFrame      0x8000
#define Overlapped     0x4000
#define LoopBackInner  0x2000
#define LoopBackOuter  0x1000

#define InnerCurves    0x0800
#define OuterCurves    0x0400
#define ShowCtrlPts    0x0200
#define ShowEdges      0x0100
#define MaskObjOff     0xF1FF
#define ShowObject     0x0C00

#define CuboidIn3D     0xEC01
#define PyramidIn3D    0xEC02
#define ConeIn3D       0xEC03
#define CylinderIn3D   0xEC04
#define TorusIn3D      0xFC05
#define EllipsoidIn3D  0xFC06
#define ChessPawnIn3D  0xEC07
#define VaseIn3D       0xEC08

#define ObjType        0x00FF
#define Cuboid3D       0x0001
#define Pyramid3D      0x0002
#define Cone3D         0x0003
#define Cylinder3D     0x0004
#define Torus3D        0x0005
#define Ellipsoid3D    0x0006
#define ChessPawn3D    0x0007
#define Vase3D         0x0008

#define Trn3D  0
#define Scl3D  1
#define Rot3D  2
#define Arb3D  3
#define Apply  5
#define Clear  6
#define Poly   8
#define ObOnly 9
#define ObPoly 10

// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                  <<>>
// <<>>         Declaration of Class ObjectIn3D          <<>>
// <<>>                                                  <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>

class ObjectIn3D
 {
   protected :

    Vector Centre;          // Vector for centre of object
    Vector Normal;          // Vector for Normal for object

    int    M,N,             // For M x N Control Points
	   Size;            // For number of Total points = M*N
    int    Nu,Nv;           // Precision or Solidity of Object
    int    GrpM,GrpN;       // for Grouping

    word   swObjectIn3D;
    byte   cSurface,
	   cPolyNet,
	   cNetEdge;

    int    icCnt,ocCnt,SrfSiz;
    Vector *Srf;
   public :

    XForm  XF;             // Composite Transformation
    Vector *S;             // Ptr to vectors of object points


    ObjectIn3D();
    ObjectIn3D(int m,int n);
    ObjectIn3D(word Type);
    ~ObjectIn3D();

    void Create(int m,int n);
    void SetDisplayColours(byte cSrf,byte cNet,byte cEdg);
    void SetPrecision(int m,int n);
    void SetGroups(int m,int n);
    void ResetControls();

    void   SetNormal();
    void   GetObjectIn3D(char *s);
    void   CreateObject();
    void   ApplyTransform();
    Vector CentreOfObject();
    void   ZAxisToNormal();

    void RegularPoly(int About,int i,float x,float y,float z);
    void Elliptical(int About,int i,int Grp,float x,float y,float z);

    Vector Surface(float u,float v,int mOff,int nOff);
    void DisplayObject();
    void CreateObjectPoints();
    void DrawWireFrame();
    void DrawSolid();
    void PolygonNet(int mOff,int nOff);
    void GetTrans(byte Which);
 };


int        mn3D_z;
int        mx3D_z;
Vector     Cur3D;
int        Wd,H;
Menu       M,Tr;
ObjectIn3D *Obj;

// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                            <<>>
// <<>>           Mathematical Functions           <<>>
// <<>>                                            <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>

double fact(int n)
 {
   int i;
   double f=1;
   if (n>0)
    for (i=1;i <= n ; i++)
     f *= i;
   return(f);
 }

double ncr(int n,int k)
 {
  double v=0;
  v=fact(n) /(fact(k)*fact(n-k));

  return(v);
 }

double Bez(int n,float u,int k)
 {
   double B= ncr(n,k);

   B *= (double) (k==0) ? 1.0:pow(u,k);
   B *= (double) (k==n) ? 1.0:pow(1-u,n-k);
   return(B);
 }


// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                            <<>>
// <<>>            General 3D Functions            <<>>
// <<>>                                            <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>

void Init3D()
 {
   H = 30;
   Wd = yMax()-66;
   Map3D.Cavalier(Wd/2,(yMax()+H)/2,45);
   mn3D_z = -400;
   mx3D_z =  400;
 }

byte Color3D(byte Color,Vector V)
 {
  byte inten=min(35,max(0,Round(36*((V.z+mx3D_z)/(mx3D_z-mn3D_z)))));
  return Color+inten;
 }
byte Shade3D(Vector V)
 {
  byte inten=min(35,max(0,Round(36*((V.z+mx3D_z)/(mx3D_z-mn3D_z)))));
  return inten;
 }
void Facet(Vector V1,Vector V2,Vector V3,Vector V4,byte Col)
 {
  Vector V[4];
  int    l,t,w,h,idx,Shade,N1,N2;
  int    FacetBuf[10000];

  V[0] = V1*Map3D;
  V[1] = V2*Map3D;
  V[2] = V3*Map3D;
  V[3] = V4*Map3D;
  l = w = V[0].x;
  t = h = V[0].y;

  for (int i=1;i<4;i++)
   {
    l = min(l,V[i].x);
    w = max(w,V[i].x);
    t = min(t,V[i].y);
    h = max(h,V[i].y);
   }
  w = w-l+1;
  h = h-t+1;
  //FacetBuf = new int[w*h];
  N1 = max(V[0].Len(),V[1].Len());
  V[0] /= N1;
  V[1] /= N1;
  for (int j=0; j< N1;j++,V1+=V[0],V3+=V[1])
   {
    V[3]  = V3-V1;
    N2    = V[3].Len();
    V[3] /= N2;
    V2    = V1;
    for (i=0;i<N2;i++,V2+=V[3])
     {
      V4    = V2*Map3D;
      idx   = (V4.y-t)*w + V4.x-l;
      Shade = Shade3D(V2);
      if (Shade >= Intensity(FacetBuf[idx]))
	 FacetBuf[idx] = Col+Shade;
     }
   }
  ShowImage(l,t,w,h,FacetBuf,zBuffer);
//  delete FacetBuf;
 }
void Plot3D(Vector V,byte Color)
 {
   Color = Color3D(Color,V);

   V *= Map3D;
   if (GetPixel(V.x,V.y)%36 <= Color%36)
      Plot(V.x,V.y,Color);
   MoveTo(V.x,V.y);
 }

void Line3D(Vector A,Vector B,byte Col)
 {
  Vector Dv=(A > B) ? A-B:B-A;
  A = (A > B) ? B:A;
  float Max = Dv.Len();
  float i;
  Dv.UnitVector();

  for (i=0;i<=Max;i++,A += Dv)
    Plot3D(A,Col);
 }

void MoveTo3D(Vector V)
 {
  Cur3D = V;
  V *= Map3D;
  MoveTo(V.x,V.y);
 }

void LineTo3D(Vector V,byte Col)
 {
  Line3D(Cur3D,V,Col);
  MoveTo3D(V);
 }

void LineRel3D(Vector Dv,byte Col)
 {
  Line3D(Cur3D,Cur3D+Dv,Col);
  MoveTo3D(Cur3D+Dv);
 }

void Block3D(Vector V,byte Color)
 {
  Vector X(1,0,0),
         Y(0,1,0);

  MoveTo3D(V);
  for (int x=-2;x<=2;x++)
   for (int y=-2;y<=2;y++)
    Plot3D(V+X*x+Y*y,Color);
  MoveTo3D(V);
 }

void GetBlock(int x,int y,byte Blk[9][9])
 {
  for (int i=-4;i<=4;i++)
   for (int j=-4;j<=4;j++)
     Blk[j+4][i+4] = GetPixel(x+i,y+j);
 }

void SetBlock(int x,int y,byte Blk[9][9])
 {
  for (int i=-4;i<=4;i++)
   for (int j=-4;j<=4;j++)
     Plot(x+i,y+j,Blk[j+4][i+4]);
 }

Vector Cursor3D()
 {
  Vector V;
  Vector X(1,0,0),Y(0,1,0),Z(0,0,1);
  byte   Bmp[9][9];
  word Key;
  ViewPortType Vp;
  GetViewPort(Vp);

  ViewPort(0,0,xMax(),yMax());
  V = Cur3D;
  GetBlock(GetX(),GetY(),Bmp);
  Block3D(V,Cyan);
  SetColor(Red+7);
  Justify(LeftText,CenterText);
  gPrintf(Wd+2*Width("w"),yMax()-H/2,"Cursor At : ");
  V.VecStatus();
  do
   {
    Key = GetKey();
    switch(Key)
     {
      case LtArr     : V -= X; break;
      case RtArr     : V += X; break;
      case UpArr     : V += Y; break;
      case DnArr     : V -= Y; break;
      case PgUp      : V += Z; break;
      case PgDn      : V -= Z; break;
      case Alt_LtArr : V -= X*20; break;
      case Alt_RtArr : V += X*20; break;
      case Alt_UpArr : V += Y*20; break;
      case Alt_DnArr : V -= Y*20; break;
      case Alt_PgUp  : V += Z*20; break;
      case Alt_PgDn  : V -= Z*20; break;
      default    : Key = (Key != RetKy && Key != EscKy) ? 32:Key;
     }

    if (Key != 32 && Key != RetKy && Key != EscKy)
     {
      SetBlock(GetX(),GetY(),Bmp);
      MoveTo3D(V);
      GetBlock(GetX(),GetY(),Bmp);
      Block3D(V,Cyan);
      ViewPort(0,0,xMax(),yMax());
      V.VecStatus();
      ViewPort(Vp);
     }
   }
  while (Key != RetKy && Key != EscKy);
  SetBlock(GetX(),GetY(),Bmp);
  return V;
 }

void Draw3DAxis()
 {
  Vector Org(0,0,0);
  Vector Z_Ax(0,0,300);
  Vector X_Ax(300,0,0);
  Vector Y_Ax(0,300,0);

  ViewPort(3,2*H+5,Wd-3,yMax()-H-5);
  Line3D(Org,Z_Ax,Magenta);
  Justify(RightText,TopText);

  SetColor(GetPixel(GetX(),GetY())%36+Yellow);
  gPrintf(GetX(),GetY(),"Z-Axis");

  Line3D(Org,X_Ax,Magenta);
  Justify(LeftText,BottomText);
  SetColor(GetPixel(GetX(),GetY())%36+Yellow);
  gPrintf(GetX(),GetY(),"X-Axis");

  Line3D(Org,Y_Ax,Magenta);
  Justify(CenterText,BottomText);

  SetColor(GetPixel(GetX(),GetY())%36+Yellow);
  gPrintf(GetX(),GetY(),"Y-Axis");
  ViewPort(0,0,xMax(),yMax());
 }

void WorkArea()
 {
  ViewPort(0,0,xMax(),yMax());
  SetColor(0);
  Box(3,2*H+5,Wd-3,yMax()-H-5,0);
  Draw3DAxis();
  ViewPort(3,2*H+5,Wd-3,yMax()-H-5);
 }

// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                            <<>>
// <<>>         Functions specific to App          <<>>
// <<>>                                            <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>

void JerryThomas()
 {
  ViewPort(0,0,xMax(),yMax());
  int x = (Wd+2+xMax())/2;
  int t = H+4+10*Height();
  int b = yMax()-8*H+2;
  int W = Width("W");
  Panel(Wd+2,t,xMax(),b,Gray+22,Gray+17);
  Justify(CenterText,CenterText);

  TextSize(1,3);
  SetColor(0);
  t+=W+3;
  Box(Wd+W+3,t,xMax()-W-3,t+3*H-2*W,Green+10);
  Box(Wd+W+3,t+3*H-W,xMax()-W-3,t+6*H+W,Green+10);
  Box(Wd+W+3,t+6*H+2*W,xMax()-W-3,t+10*H+2*W,Green+10);
  SetColor(Yellow+21);
  gPrintf(x,t+H-W,"3D Wireframe Objects");
  gPrintf(x,t+2*H-W,"Created using Bezier Surfaces");
  Justify(LeftText,CenterText);
  SetColor(Cyan+20);
  gPrintf(Wd+4*W,t+3*H+2*W,"Implemented By :");
  Justify(RightText,CenterText);
  gPrintf(xMax()-3*W,t+4*H+2*W," Jerry Thomas ");
  gPrintf(xMax()-3*W,t+5*H+2*W,"MCA IV 1998-99");
  Justify(CenterText,CenterText);
  SetColor(Green+22);

  Justify(LeftText,CenterText);
  gPrintf(Wd+3*W,t+8*H-15,"X-Resolution         : 1024 Pixels");
  gPrintf(Wd+3*W,t+9*H-15,"Y-Resolution         : 768  Pixels");
  gPrintf(Wd+3*W,t+10*H-15,"Colour Depth (8 Bit) : 256 Colours");
  TextSize(1,2);

  Panel(Wd+2,H+2,xMax(),6*H+12,Gray+22,Gray+17);
  Justify(CenterText,CenterText);
  Signature((3*Wd+6+xMax())/4,H+( 5*H+11)/4,Yellow+15);
  Signature((Wd+2+3*xMax())/4,H+( 5*H+11)/4,Blue  +15);
  Signature(  (Wd+2+xMax())/2,H+( 5*H+11)/2,Green +15);
  Signature((3*Wd+6+xMax())/4,H+(15*H+33)/4,Cyan  +15);
  Signature((Wd+2+3*xMax())/4,H+(15*H+33)/4,Red   +15);
  Justify(LeftText,CenterText);
  ViewPort(3,2*H+5,Wd-3,yMax()-H-5);
 }

void Screen()
 {
  Init3D();
  InitScheme();
  TextSize(1,1);
  SetColor(Yellow+30);
  Panel(0,0,xMax(),H,Gray+22,Gray+17);
  Panel(0,yMax()-H,xMax(),yMax(),Gray+22,Gray+17);
  Signature(100,3,Green+10);
  Signature(xMax()-140,3,Green+10);
  Frame(0,2*H+2,Wd,yMax()-H-2,Gray+17);

  M.DefineMenu(MenuHz,0,H+2,Wd,2*H,9,GrayScale);
    M.DefinePad("&Cuboid",ActivePad,NoApp);
    M.DefinePad("&Pyramid",ActivePad,NoApp);
    M.DefinePad("C&one",ActivePad,NoApp);
    M.DefinePad("C&ylinder",ActivePad,NoApp);
    M.DefinePad("&Torus",ActivePad,NoApp);
    M.DefinePad("&Ellipsoid",ActivePad,NoApp);
    M.DefinePad("P&awn",ActivePad,NoApp);
    M.DefinePad("&Vase",ActivePad,NoApp);
    M.DefinePad("E&xit",ActivePad,NoApp);

  M.SetPadHelp(0,"Create a Cuboid for transformations in 3D");
  M.SetPadHelp(1,"Create a Pyramid for transformations in 3D");
  M.SetPadHelp(2,"Create a Cone for transformations in 3D");
  M.SetPadHelp(3,"Create a Cylinder Surface for transformations in 3D");
  M.SetPadHelp(4,"Create a Torus Surface for transformations in 3D");
  M.SetPadHelp(5,"Create a Ellipsoid for transformations in 3D");
  M.SetPadHelp(6,"Create a Chess Pawn Surface for transformations in 3D");
  M.SetPadHelp(7,"Create a Vase Surface for transformations in 3D");
  M.SetPadHelp(8,"Exit the 3D Graphics Application");

  SetColor(Red+7);
  Justify(CenterText,CenterText);
  TextSize(1,2);
  gPrintf(xMax()/2,H/2,"Three Dimensional Graphics");

  M.DrawMenu();
  Map3D.Display("Cavalier Projection");


  JerryThomas();
  WorkArea();
 }

void ObjTrans()
 {
  do
   {
    Tr.Xecute();
    if (Tr.MenuID() != 0xFF)
	Obj->GetTrans(Tr.MenuID());
   }
  while (Tr.MenuID() != 0xFF);
  JerryThomas();
 }

// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                  <<>>
// <<>>       Member functions of Class ObjectIn3D       <<>>
// <<>>                                                  <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>  <<>>

ObjectIn3D::ObjectIn3D()
 {
  Create(20,20);
  S = new Vector[Size];
  SetDisplayColours(Green,Red,Cyan);
 }

ObjectIn3D::ObjectIn3D(int m,int n)
 {
  Create(m,n);
  S = new Vector[Size];
  SetDisplayColours(Green,Red,Cyan);
 }

ObjectIn3D::ObjectIn3D(word Type)
 {
  swObjectIn3D = Type;
  switch(swObjectIn3D&ObjType)
   {
    case Cuboid3D   : Create(4,4);
                      SetGroups(2,2);
		      SetPrecision(20,20);
		      break;
    case Pyramid3D  : Create(3,4);
                      SetGroups(2,2);
		      SetPrecision(20,20);
		      break;
    case Cone3D     : Create(3,8);
                      SetGroups(2,3);
		      SetPrecision(20,30);
		      break;
    case Cylinder3D : Create(4,8);
		      SetGroups(2,3);
		      SetPrecision(10,20);
		      break;
    case Torus3D    : Create(8,8);
                      SetGroups(3,3);
		      SetPrecision(40,5);
		      break;
    case Ellipsoid3D: Create(5,8);
                      SetGroups(3,3);
		      SetPrecision(20,20);
		      break;
    case ChessPawn3D: Create(13,8);
                      SetGroups(3,3);
		      SetPrecision(10,10);
		      break;
    case Vase3D     : Create(11,8);
                      SetGroups(2,3);
		      SetPrecision(10,10);
		      break;
   }
  S = new Vector[Size];
  SetDisplayColours(Green,Red,Cyan);
 }

ObjectIn3D::~ObjectIn3D()
 {
  delete S;
 }

void ObjectIn3D::Create(int m,int n)
 {
  M= GrpM = m;
  N= GrpN = n;
  Size    = M*N;
  Nu      = 2;
  Nv      = 2;
 }
void ObjectIn3D::SetDisplayColours(byte cSrf,byte cNet,byte cEdg)
 {
  cSurface = cSrf;
  cPolyNet = cNet;
  cNetEdge = cEdg;
 }
void ObjectIn3D::SetPrecision(int m,int n)
 {
  Nu = abs(n);
  Nv = abs(m);
 }

void ObjectIn3D::SetGroups(int m,int n)
 {
  GrpM = (m >1 && m<= M)? m:M;
  GrpN = (n >1 && n<= N)? n:N;
 }

void ObjectIn3D::ResetControls()
 {
   for (int i=0;i<Size;i++)
    S[i].Vectorise(0,0,0);
 }

void ObjectIn3D::SetNormal()
 {
  Normal -= Centre;
  Normal.UnitVector();
 }
void ObjectIn3D::ApplyTransform()
 {
  for (int i=0;i<Size;i++)
   S[i] *= XF;
 }
Vector ObjectIn3D::CentreOfObject()
 {
  Vector Cntr;
  for (int i=0;i<Size;i++)
    Cntr += S[i]*XF;
  Cntr /= (Size>0) ? Size:1;
  return Cntr;
 }
void ObjectIn3D::ZAxisToNormal()
 {
  XF.Identity();
  XF.zAxisToNormal(Normal);
  XF.Translate3D(Centre);
  for (int i=0;i<Size;i++)
    S[i] *= XF;
  XF.Identity();
 }

void ObjectIn3D::RegularPoly(int About,int i,float x,float y,float z)
 {
  About %=3;
  int n=i*N;
  if (N==4)
   {
    switch(About)
     {
       case X_Axis : S[n  ].Vectorise(x,y,z);
                     S[n+1].Vectorise(x,-y,z);
		     S[n+2].Vectorise(x,-y,-z);
		     S[n+3].Vectorise(x,y,-z);
		     break;
       case Y_Axis : S[n  ].Vectorise(x,y,z);
                     S[n+1].Vectorise(x,y,-z);
		     S[n+2].Vectorise(-x,y,-z);
		     S[n+3].Vectorise(-x,y,z);
		     break;
       case Z_Axis : S[n  ].Vectorise(x,y,z);
                     S[n+1].Vectorise(x,-y,z);
		     S[n+2].Vectorise(-x,-y,z);
		     S[n+3].Vectorise(-x,y,z);
		     break;
     }
   }
  else
   {
    S[n].Vectorise(x,y,z);
    for (i=1;i<N;i++)
     {
      XF.Identity();
      XF.RotateAbout(About,i*360/(N-1));
      S[n+i] = S[n]*XF;
     }
    XF.Identity();
   }
 }

void ObjectIn3D::Elliptical(int About,int i,int Grp,float x,float y,float z)
 {
  About %= 3;
  int j,k,n=i,l;
  Vector V;
  int SgnA,SgnB;
  switch(About)
   {
     case X_Axis: if (swObjectIn3D&Overlapped)
		    for (i=0,k=2;i<8;i++,k=(k+1)%8)
		     {
		      SgnA = -((k%4+2)%6)/3*((k/4)*2-1);
		      SgnB = -((i%4+2)%6)/3*((i/4)*2-1);
		      V.Vectorise(x,SgnA*y,SgnB*z);
		      for (l=0;l<Grp;l++)
			S[n++] += V;
		     }
                  else
		   {
		    for (j=-1;j<=1;j+=2)
		     for (i=0,k=3;i<6;i++,k++)
                      {
                        V.Vectorise(x,(i/2-1)*j*y,((k%8)/4)*j*z);
		        for (l=0;l<Grp;l++)
		         S[n++] += V;
		      }
		   }
		  break;
     case Y_Axis: if (swObjectIn3D&Overlapped)
                    for (i=0,k=2;i<8;i++,k=(k+1)%8)
		      {
			SgnA = -((k%4+2)%6)/3*((k/4)*2-1);
			SgnB = -((i%4+2)%6)/3*((i/4)*2-1);
			V.Vectorise(SgnA*x,y,SgnB*z);
			for (l=0;l<Grp;l++)
			 S[n++] += V;
		      }
                  else
		   {
		    for (j=-1;j<=1;j+=2)
		     for (i=0,k=3;i<6;i++,k++)
		      {
			V.Vectorise((i/2-1)*j*x,y,((k%8)/4)*j*-z);
			for (l=0;l<Grp;l++)
			 S[n++] += V;
		      }
		     }
		    break;
     case Z_Axis: if (swObjectIn3D&Overlapped)
                     for (i=0,k=2;i<8;i++,k=(k+1)%8)
		      {
			SgnA = -(((k%4+2)%6)/3)*((k/4)*2-1);
			SgnB = -(((i%4+2)%6)/3)*((i/4)*2-1);
			V.Vectorise(SgnA*x,SgnB*y,z);
			for (l=0;l<Grp;l++)
			 S[n++] += V;
		      }
                  else
		   {
		    for (j=1;j>=-1;j-=2)
		     for (i=0,k=3;i<6;i++,k++)
		      {
			V.Vectorise((i/2-1)*j*-x,((k%8)/4)*j*y,z);
			for (l=0;l<Grp;l++)
			 S[n++] += V;
		      }
		   }
		  break;
	 }
 }

void ObjectIn3D::GetObjectIn3D(char *s)
 {
  Cur3D.Vectorise(0,0,0);
  MoveTo3D(Cur3D);
  Status("Select the Centre Of %s",s);
  Centre = Cursor3D();
  Status("Select a point on the Normal thru Centre");
  Normal = Cursor3D();
  ViewPort(0,0,xMax(),yMax());
  SetNormal();
 }

void ObjectIn3D::CreateObject()
 {
  char *Cub[4] = {
		   "Dimensions of        ",
		   "Length     : ",
		   "Breadth    : ",
		   "Height     : ",
                 };
  char *Con[4] = {
		   "Dimensions of          ",
		   "Major Radius  : ",
		   "Minor Radius  : ",
		   "Height        : "
		 };
  char *Tor[4] = {
		   "Dimensions of Torus",
		   "Major Radius  : ",
		   "Tube Width    : ",
		   "Tube Height   : "
                 };
  int   i,j;
  float R;
  Vector D,vMin(10,10,10),
           vMax(300,300,300);

  Centre.Vectorise(0,0,0);
  Normal.Vectorise(0,0,1);
  ResetControls();
  WorkArea();

  switch(swObjectIn3D&ObjType)
   {
    case Cuboid3D  : GetObjectIn3D("Cuboid");
                     strcpy(Cub[0]+14,"Cuboid");
		     D.Get(Cub,vMin,vMax);
		     D /= 2;
		     RegularPoly(Z_Axis,0,0,0,D.z);
		     RegularPoly(Z_Axis,1,D.x,D.y,D.z);
		     RegularPoly(Z_Axis,2,D.x,D.y,-D.z);
		     RegularPoly(Z_Axis,3,0,0,-D.z);
		     break;
    case Pyramid3D : GetObjectIn3D("Pyramid");
		     strcpy(Cub[0]+14,"Pyramid");
		     D.Get(Cub,vMin,vMax);
		     RegularPoly(Z_Axis,0,  0,   0, D.z/2);
		     RegularPoly(Z_Axis,1,D.x, D.y,-D.z/2);
		     RegularPoly(Z_Axis,2,  0,   0,-D.z/2);
		     break;
    case Cone3D    : GetObjectIn3D("Cone");
                     strcpy(Con[0]+14,"Cone");
                     strcpy(Con[3],"Height        : ");
		     D.Get(Con,vMin,vMax);
		     Elliptical(Z_Axis,0  ,1,  0,  0, D.z/2);
		     Elliptical(Z_Axis,N  ,1,D.x,D.y,-D.z/2);
		     Elliptical(Z_Axis,2*N,1,  0,  0,-D.z/2);
		     break;
    case Cylinder3D: GetObjectIn3D("Cylinder");
		     strcpy(Con[0]+14,"Cylinder");
                     strcpy(Con[3],"Height        : ");
		     D.Get(Con,vMin,vMax);
		     Elliptical(Z_Axis,  0,1,  0,  0, D.z/2);
		     Elliptical(Z_Axis,  N,1,D.x,D.y, D.z/2);
		     Elliptical(Z_Axis,2*N,1,D.x,D.y,-D.z/2);
		     Elliptical(Z_Axis,3*N,1,  0,  0,-D.z/2);
		     break;
    case Torus3D   : GetObjectIn3D("Torus");
                     D.Get(Tor,vMin,vMax);
		     Elliptical(Y_Axis,0,1,D.y,0,D.z);
		     Elliptical(Y_Axis,N,1,sqrt(2)*D.y,0,D.z);
		     XF.Identity();
                     XF.RotateAbout(Z_Axis,45);
                     for (i=N;i<2*N;i++)
		       S[i] *= XF;
                     XF.Identity();
                     XF.RotateAbout(Z_Axis,90);
                     for (i=2;i<M;i++)
                      for (j=0;j<N;j++)
		       S[i*N+j] = S[(i-2)*N+j]*XF;
                     XF.Identity();
                     Elliptical(Z_Axis,0,N,D.x,D.x,0);
                     break;
    case Ellipsoid3D:GetObjectIn3D("Ellipsoid");
                     strcpy(Con[0]+14,"Ellipsoid");
                     strcpy(Con[3],"Depth Radius  : ");
                     D.Get(Con,vMin,vMax);
                     R = (float)sqrt(D.x*D.x+D.y*D.y);
                     Elliptical(Y_Axis,0  ,1,D.x,0,D.z);
                     Elliptical(Y_Axis,N  ,1,R  ,0,D.z);
                     Elliptical(Y_Axis,N+N,1,D.y,0,D.z);
                     XF.Identity();
                     XF.RotateAbout(Z_Axis,atan(D.y/D.x)*PiUnder180);
		     for (i=N;i<N+N;i++)
                       S[i] *= XF;
                     XF.Identity();
                     XF.RotateAbout(Z_Axis,90);
		     for (i=N+N;i<3*N;i++)
		       S[i] *= XF;
                     XF.Identity();
                     D.Vectorise(-1,1,1);
                     XF.Scale3D(D);

                     for (i=1;i<3;i++)
                      for (j=0;j<N;j++)
                       S[(i+2)*N+j] = S[(2-i)*N+j]*XF;
                     XF.Identity();
                     break;
    case ChessPawn3D: Elliptical(Y_Axis,   0,1,  0,-200,  0);
                      Elliptical(Y_Axis,   N,1, 40,-200, 40);
		      Elliptical(Y_Axis, 2*N,1, 80,-200, 80);
                      Elliptical(Y_Axis, 3*N,1,100,-150,100);
		      Elliptical(Y_Axis, 4*N,1, 40, -70, 40);
                      Elliptical(Y_Axis, 5*N,1, 60, -60, 60);
                      Elliptical(Y_Axis, 6*N,1, 40, -50, 40);
                      Elliptical(Y_Axis, 7*N,1, 60,   0, 60);
                      Elliptical(Y_Axis, 8*N,1, 20,  80, 20);
		      Elliptical(Y_Axis, 9*N,1, 50,  90, 50);
                      Elliptical(Y_Axis,10*N,1, 20, 100, 20);
                      Elliptical(Y_Axis,11*N,1, 30, 130, 30);
                      Elliptical(Y_Axis,12*N,1,  0, 200, 0);
                      break;
    case Vase3D     : Elliptical(Y_Axis,  0,1, 60,-150, 60);
                      Elliptical(Y_Axis,  N,1, 50,-150, 50);
                      Elliptical(Y_Axis,2*N,1, 30,-130, 30);
                      Elliptical(Y_Axis,3*N,1,  0,-130,  0);
                      Elliptical(Y_Axis,4*N,1, 30,-130, 30);
                      Elliptical(Y_Axis,5*N,1, 30,-110, 30);
                      Elliptical(Y_Axis,6*N,1,100, 130,100);
                      Elliptical(Y_Axis,7*N,1, 80, 180, 80);
                      Elliptical(Y_Axis,8*N,1, 20, 180, 20);
		      Elliptical(Y_Axis,9*N,1, 20, 200, 20);
                      Elliptical(Y_Axis,10*N,1, 40, 240, 40);
                      break;
   }
  ZAxisToNormal();
 }

Vector ObjectIn3D::Surface(float u,float v,int mOff,int nOff)
 {
  Vector rvVec(0,0,0);
  int    m,n;

  for (m=0;m<GrpM;m++,++mOff%=M)
  for (n=0;n<GrpN;n++)
   rvVec = rvVec + S[mOff*N + (nOff+n)%N]*(Bez(GrpN-1,u,n)*Bez(GrpM-1,v,m));

  return rvVec ;
 }

void ObjectIn3D::GetTrans(byte Which)
 {
  Vector T;
  char *Trn[4] = {
	           "Translation Vector",
		   "Translation in X : ",
		   "Translation in Y : ",
		   "Translation in Z : "
		 };
  char *Scl[4] = {
                   "Scale Vector",
		   "X Scale Factor : ",
		   "Y Scale Factor : ",
		   "Z Scale Factor : "
		 };
  char *Rot[4] = {
                   "Rotation Vector",
		   "About X Axis : ",
		   "About Y Axis : ",
		   "About Z Axis : "
		 };
  float theta;
  Vector vMin(-300,-300,-300),
         vMax(300,300,300);

  ViewPortType V;
  GetViewPort(V);

  Cur3D = CentreOfObject();
  MoveTo3D(Cur3D);

  switch(Which)
   {
    case Trn3D : T.Get(Trn,vMin,vMax);
		 XF.Translate3D(T);
		 break;
    case Scl3D : Status("Select the reference point");
		 Centre = Cursor3D();
		 XF.Translate3D(Centre*(-1));
                 vMin.Vectorise(-10,-10,-10);
                 vMax.Vectorise(10,10,10);
                 T.Get(Scl,vMin,vMax);
		 T.x = (T.x < 0) ? -1:T.x;
		 T.y = (T.y < 0) ? -1:T.y;
		 T.z = (T.z < 0) ? -1:T.z;
		 XF.Scale3D(T);
		 XF.Translate3D(Centre);
		 break;
    case Rot3D : Status("Select the reference point");
                 Centre = Cursor3D();
                 vMin.Vectorise(-360,-360,-360);
		 vMax.Vectorise(360,360,360);
		 XF.Translate3D(Centre*(-1));
                 T.Get(Rot,vMin,vMax);
		 XF.Rotate3D(T);
		 XF.Translate3D(Centre);
		 break;
    case Arb3D : ViewPort(0,0,xMax(),yMax());
                 Status("Select the reference point");
                 Centre = Cursor3D();
		 Status("Select a point on the normal thru reference point");
		 Normal = Cursor3D();
		 Panel(Wd+2,H+2,xMax(),5*H+10,Gray+12,Gray+12);
		 Label(Wd+2,5*H+12,xMax(),6*H+12,"Rotation Angle",Gray+7,Green+7);
                 SetColor(Green+7);
                 Justify(LeftText,CenterText);
		 gPrintf(Wd+2+3*Width("W"),3*H+5,"Rotation Angle : ");
                 SetColor(Red+17);
		 gScanf(Wd+2+21*Width("W"),3*H-3,"%6.2f",&theta,-360,360,Gray+17);
		 XF.Translate3D(Centre*(-1));
		 SetNormal();
		 XF.NormalToAxisZ(Normal);
		 XF.RotateAbout(Z_Axis,theta);
		 XF.zAxisToNormal(Normal);
		 XF.Translate3D(Centre);
                 ViewPort(V);
		 break;
    case Apply:  ApplyTransform();
                 DisplayObject();
		 XF.Identity();
		 break;
    case Clear : XF.Identity();
		 break;
    case Poly  : swObjectIn3D = (swObjectIn3D&MaskObjOff)^ShowCtrlPts;
		 DisplayObject();
                 break;
    case ObOnly: swObjectIn3D = (swObjectIn3D&MaskObjOff)^ShowObject;
		 DisplayObject();
                 break;
    case ObPoly: swObjectIn3D  = (swObjectIn3D&MaskObjOff);
                 swObjectIn3D ^= (ShowCtrlPts|ShowObject);
		 DisplayObject();
                 break;
   }

  XF.Display("Composite Transformation");
 }

void ObjectIn3D::DisplayObject()
 {
  WorkArea();
  if (swObjectIn3D&WireFrame)
   {
    float v,u;
    int   Offset=0,i,j;
    float Dv = (float)1.0/Nv;
    float Du = (float)1.0/Nu;
    int MaxM,MaxN,mOff,nOff;
    if (swObjectIn3D&Overlapped)
     {

      MaxM   = (M==GrpM) ? 1:(GrpM==2) ? M-1:M/(GrpM-1);
      mOff   = (M==GrpM) ? 1:(GrpM-1);
      MaxN   = (N==GrpN) ? 1:(GrpN==2) ? N-1:N/(GrpN-1);
      nOff   = (N==GrpN) ? GrpN:GrpN-1;
      if (swObjectIn3D&LoopBackOuter)
         MaxM = (M!=GrpM && GrpM==2) ? M:MaxM;
      if (swObjectIn3D&LoopBackInner)
         MaxN = (N!=GrpN && GrpN==2) ? N:MaxN;

     }
    else
     {
      MaxM   = M/GrpM;
      MaxN   = N/GrpN;
      mOff   = GrpM;
      nOff   = GrpN;
     }
    if (swObjectIn3D&ShowCtrlPts)
     {
      for (i=0,Offset=0;i<MaxM;i++,Offset+=mOff)
       for(j=0;j<MaxN;j++)
	PolygonNet(Offset,j*nOff);
     }
    if (swObjectIn3D&InnerCurves)
     {
      for (i=0,Offset=0;i<MaxM;i++,Offset+=mOff)
       for (v=0.0; v < 1.0+Dv ;v += Dv)
	{
	 for(j=0;j<MaxN;j++)
	  {
	   MoveTo3D(Surface(0.0,v,Offset,j*nOff));
	   for (u=Du;u < 1.0+Du;u+=Du)
	    LineTo3D(Surface(u,v,Offset,j*nOff),cSurface);//Green);
	   }
	}
     }
    if (swObjectIn3D&OuterCurves)
     {
      for(j=0;j<MaxN;j++)
       for (u=0.0;u< 1.0+Du;u +=Du)
	{
	 for (i=0,Offset=0;i<MaxM;i++,Offset+=mOff)
	  {
	   MoveTo3D(Surface(u,0.0,Offset,j*nOff));
	   for (v=Dv;v < 1+Dv;v+=Dv)
	    LineTo3D(Surface(u,v,Offset,j*nOff),cSurface);//Green);
	  }
	}
     }
   }
 }

void ObjectIn3D::PolygonNet(int mOff,int nOff)
 {
  int i,j,Offset;
  for (i=0,Offset=mOff*N;i<GrpM;i++,Offset=((mOff+i)%M)*N)
   {
    MoveTo3D(S[Offset+nOff%N]);
    Block3D (S[Offset+nOff%N],cNetEdge);//Cyan);
    for (j=1;j<GrpN;j++)
     {
      LineTo3D(S[Offset+(nOff+j)%N],cPolyNet);//Cyan);
      Block3D (S[Offset+(nOff+j)%N],cNetEdge);//Cyan);
     }
   }
  for (i=0,nOff%=N;i<GrpN;i++,++nOff%=N)
   {
    Offset = N*(mOff%M);
    MoveTo3D(S[Offset+nOff]);
    Block3D (S[Offset+nOff],cNetEdge);//Cyan);
    for (j=1,Offset=((mOff+1)%M)*N;j<GrpM;j++,Offset=((mOff+j)%M)*N)
     {
      LineTo3D(S[Offset+nOff],cPolyNet);//,Cyan);
      Block3D (S[Offset+nOff],cNetEdge);//,Cyan);
     }
   }
 }
void ObjectIn3D::CreateObjectPoints()
 {
  WorkArea();
  if (swObjectIn3D&WireFrame)
   {
    float v,u;
    int   Offset=0,i,j;
    float Dv = (float)1.0/Nv;
    float Du = (float)1.0/Nu;
    int MaxM,MaxN,mOff,nOff;
    if (swObjectIn3D&Overlapped)
     {
      MaxM   = (M==GrpM) ? 1:(GrpM==2) ? M-1:M/(GrpM-1);
      mOff   = (M==GrpM) ? 1:(GrpM-1);
      MaxN   = (N==GrpN) ? 1:(GrpN==2) ? N-1:N/(GrpN-1);
      nOff   = (N==GrpN) ? GrpN:GrpN-1;
      if (swObjectIn3D&LoopBackOuter)
	 MaxM = (M!=GrpM && GrpM==2) ? M:MaxM;
      if (swObjectIn3D&LoopBackInner)
	 MaxN = (N!=GrpN && GrpN==2) ? N:MaxN;
     }
    else
     {
      MaxM   = M/GrpM;
      MaxN   = N/GrpN;
      mOff   = GrpM;
      nOff   = GrpN;

     }
  /*  if (swObjectIn3D&ShowCtrlPts)
     {
      for (i=0,Offset=0;i<MaxM;i++,Offset+=mOff)
       for(j=0;j<MaxN;j++)
	PolygonNet(Offset,j*nOff);
     }
    if (swObjectIn3D&InnerCurves)
     { */
      icCnt = MaxN*(Nu+1);
      ocCnt = MaxM*(Nv+1);
      SrfSiz = icCnt*ocCnt;
      Srf = new Vector[SrfSiz];
      int idx;
      for (idx=0,i=0,Offset=0;i<MaxM;i++,Offset+=mOff)
       for (v=0.0; v < 1.0+Dv ;v += Dv)
	 for(j=0;j<MaxN;j++)
	   for (u=0.0;u < 1.0+Du;u+=Du)
	     Srf[idx++] = Surface(u,v,Offset,j*nOff);//Green);
/*      for(j=0;j<MaxN;j++)
       for (u=0.0;u< 1.0+Du;u +=Du)
	 for (i=0,Offset=0;i<MaxM;i++,Offset+=mOff)
	   for (v=0.0;v < 1+Dv;v+=Dv)
	    Srf[idx++]=Surface(u,v,Offset,j*nOff);//,cSurface);//Green);*/
   }
 }
void ObjectIn3D::DrawWireFrame()
 {
  int i,j,offset;

  for (i=0;i<icCnt;i++)
   for (j=1,offset = icCnt;j<ocCnt;j++,offset+= icCnt)
    Line3D(Srf[offset+i-icCnt],Srf[offset+i],cSurface);
  for (i=0,offset = 0;i<ocCnt;j++,offset+=icCnt)
   for (j=1;j<icCnt;j++)
    Line3D(Srf[offset+j],Srf[offset+j-1],cSurface);
 }
void ObjectIn3D::DrawSolid()
 {
  int i,j,mnOff=0,mxOff=icCnt;
  for (j=1;j<icCnt;j++)
  for (i=1;i<ocCnt;i++,mnOff+=icCnt,mxOff+=icCnt)
     Facet(Srf[mnOff+i-1],Srf[mnOff+i],Srf[mxOff+i-1],Srf[mxOff+i],cSurface);
 }
main()
 {
  ObjectIn3D Cub3D(CuboidIn3D),
	     Pyr3D(PyramidIn3D),
	     Con3D(ConeIn3D),
	     Cyl3D(CylinderIn3D),
	     Tor3D(TorusIn3D);
  ObjectIn3D Ell3D(EllipsoidIn3D),
	     Pwn3D(ChessPawnIn3D),
	     Vas3D(VaseIn3D);

  Bmp CapS;
  ModeSearch(VgaCo1024x768x256);
  Screen();

  Tr.DefineMenu(MenuVt,Wd+2,6*H+14,xMax(),yMax()-8*H+2,11,GrayScale);
     Tr.DefinePad("&Translate Object",ActivePad,NoApp);
     Tr.DefinePad("&Scale Object",ActivePad,NoApp);
     Tr.DefinePad("&Rotate Object",ActivePad,NoApp);
     Tr.DefinePad("R&otate About Arbitrary Axis",ActivePad,NoApp);
     Tr.DefinePad("",MenuBreak,NoApp);
     Tr.DefinePad("&Apply Transformations",ActivePad,NoApp);
     Tr.DefinePad("&Clear Transformations",ActivePad,NoApp);
     Tr.DefinePad("",MenuBreak,NoApp);
     Tr.DefinePad("Polygon &Net Only",ActivePad,NoApp);
     Tr.DefinePad("O&bject Only",ActivePad,NoApp);
     Tr.DefinePad("Object && &Polygon Net",ActivePad,NoApp);

  Tr.SetPadHelp(0,"Append 3D Translation to transformation matrix");
  Tr.SetPadHelp(1,"Append 3D Scale to transformation matrix");
  Tr.SetPadHelp(2,"Append 3D Rotation to transformation matrix");
  Tr.SetPadHelp(3,"Append Arbitrary axis rotation to transformation matrix");
  Tr.SetPadHelp(5,"Apply the composite transformation to object in 3D");
  Tr.SetPadHelp(6,"Clear the composite transformation matrix");
  Tr.SetPadHelp(8,"Display defining Polygon net only");
  Tr.SetPadHelp(9,"Display Object only");
  Tr.SetPadHelp(10,"Display Object and Polygon net");


  while (M.MenuID() != 8 && M.MenuID() != 0xFF)
   {
     M.Xecute();
     switch(M.MenuID())
      {
       case 0: Obj = &Cub3D; break;
       case 1: Obj = &Pyr3D; break;
       case 2: Obj = &Con3D; break;
       case 3: Obj = &Cyl3D; break;
       case 4: Obj = &Tor3D; break;
       case 5: Obj = &Ell3D; break;
       case 6: Obj = &Pwn3D; break;
       case 7: Obj = &Vas3D; break;
      }
     if (M.MenuID() != 8 && M.MenuID() != 0xFF)
      {
       Obj->CreateObject();
       Obj->DisplayObject();
       //Obj->CreateObjectPoints();
       //Obj->DrawWireFrame();
       //GetKey();
       //if (GetKey() == Alt_S)
	// Obj->DrawSolid();
       ObjTrans();
       //Status("Create a Torus Surface for transformations in 3D");
       //CapS.Capture(0,0,1024,768);
       //CapS.SaveAs("Capture.Bmp");

      }
   }
  CloseGraph();
  return(0);
 }
