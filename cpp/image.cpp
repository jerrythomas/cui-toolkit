#include <stdio.h>
#include <string.h>\

#include <kbd.h>
#include <Pix2d.h>

#define FloydSteinBerg 1
#define Stucki         2
#define Burke          3
#define Sierra         4
#define Ninke          5
#define StevensonArce  6

class Filter
 {
  private :
   float F[4][7],
         D[4][7];
   int   W,H,w;

  public :
    void InitStandardFilter();
    void InitDither();
    void SetFilter(int Which);
    Filter();
    Filter(int which);
    void Dither(int x,int y,int Pix);
  };
class Images
  {
   private :
    int    xStrt,yStrt,xOff,yOff;
    char   *title;
    Filter F;

   public :
    Images();
    Images(int l,int t,int w,int h);
    void Resize(int w,int h);
    void SetTitle(char *lbl);
    void RGBPallette();
    void ToGrayScale();
    void Dither(int Which);
    void Show();
  };

void  Filter::InitStandardFilter()
 {
  for (int i=0;i<4;i++)
   for (int j=0;j<7;j++)
     F[i][j] = 0.0;
 }
void  Filter::InitDither()
 {
  for (int i=0;i<4;i++)
   for (int j=0;j<7;j++)
     D[i][j] = 0.0;
 }
void  Filter::SetFilter(int Which)
 {
  InitStandardFilter();
   switch(Which)
    {
     case FloydSteinBerg :
            W=3;H=2;w=1;
            F[0][2] = 7;
            F[1][0] = 3;
            F[1][1] = 5;
            F[1][2] = 1;
          break;
     case Stucki :
            W=5;H=3;w=2;
            F[0][3] = F[1][2] = 8;
            F[0][4] = F[1][1] = F[1][3] = F[2][2] = 4;
            F[1][0] = F[1][4] = F[2][1] = F[2][3] = 2;
            F[2][0] = F[2][4] = 1;
          break;
     case Burke :
            W=5;H=2;w=2;
            F[0][3] = F[1][2] = 8;
            F[0][4] = F[1][1] = F[1][3] = 4;
            F[1][0] = F[1][4] = 2;
          break;
     case Sierra :
            W=5;H=3;w=2;
            F[0][3] = F[1][2] = 5;
            F[0][4] = F[2][2] = 3;
            F[1][1] = F[1][3] = 4;
            F[1][0] = F[1][4] = F[2][1] = F[2][3] = 2;
           break;
     case Ninke :
            W=5;H=3;w=2;
            F[0][3] = F[1][2] = 7;
            F[0][4] = F[1][1] = F[1][3] = F[2][2] = 5;
            F[1][0] = F[1][4] = F[2][1] = F[2][3] = 3;
            F[2][0] = F[2][4] = 1;
          break;
     case StevensonArce :
            W=7;H=4;w=3;
            F[0][6] = 32;
            F[1][0] = F[2][1] = F[2][5] = 12;
            F[3][2] = F[3][4] = 12;
            F[1][2] = F[2][3] = 26;
            F[1][4] = 30;
            F[1][6] = 16;
            F[3][0] = F[3][6] = 5;
          break;
    }
  int Sum =0;
  for (int i=0;i<H;i++)
    for (int j=0;j<W;j++)
      Sum += F[i][j];
   for (i=0;i<H;i++)
    for (j=0;j<W;j++)
      F[i][j] /= Sum;
 }
  Filter::Filter()
  {
   InitStandardFilter();
   InitDither();
  }
 Filter:: Filter(int which)
  {
   SetFilter(which);
  }
 void Filter::Dither(int x,int y,int Pix)
  {
   int d;
   for (int i=0;i<H;i++)
    for (int j=0;j<W;j++)
      D[i][j] = F[i][j]*Pix;
   int xP,yP;
   for (i=0;i<H;i++,y++)
    for (j=0,xP=x-w;j<W;j++,xP++)
     {
      Pix = GetPixel(xP,y);
      d   = (Pix < 216) ? Pix%36:Pix-216;
      d   = max(0,d+D[i][j]);
      d   = (Pix < 216) ? min(d,35):min(d,39);
      Pix = (Pix < 216) ? Pix/36:6;
      Plot(xP,y,Pix*36+d);
     }
  }


Images::Images()
 {
  xStrt = yStrt =0;
  xOff = yOff = 0;
 }
Images::Images(int l,int t,int w,int h)
 {
  xStrt = l;
  yStrt = t;
  xOff  = w;
  yOff  = h;
 }
void Images::Resize(int w,int h)
 {
  xOff = w;
  yOff = h;
 }
void Images::SetTitle(char *lbl)
 {
  title = new char[strlen(lbl)+1];
  strcpy (title,lbl);
 }
void Images::Show()
 {
  ViewPort(0,0,xMax(),yMax());
  SetColor(Gray+10);
  Box(xStrt,yStrt,xStrt+xOff+6,yStrt+30,Gray+12);
  Tile(xStrt,yStrt,xStrt+xOff+6,yStrt+30,Gray+12);
  TextSize(1,2);
  Justify(LeftText,CenterText);
  SetColor(Green+10);
  gPrintf(xStrt+10,yStrt+15,"%c",0x05);
  Rectangle(xStrt+3,yStrt+3,xStrt+22,yStrt+27);
  gPrintf(xStrt+26,yStrt+15,title);
  Tile(xStrt,yStrt+32,xStrt+xOff+6,yStrt+yOff+38,Gray+12);
  SetColor(0);
  Box(xStrt+3,yStrt+35,xStrt+xOff+3,yStrt+yOff+35,0);
  ViewPort(xStrt+3,yStrt+35,xStrt+xOff+3,yStrt+yOff+35);
 }
void Images::RGBPallette()
 {
  ViewPort(xStrt+3,yStrt+35,xStrt+xOff+3,yStrt+yOff+35);
  int W = xOff/16;
  int H = yOff/16;
  SetColor(0);
  int x=xStrt+3;
  int y=yStrt+35;
  for (int i=0;i<16;i++)
   for (int j=0;j<16;j++)
     Box(x+j*W,y+i*H,x+j*W+W,y+i*H+H,i*16+j);
 }
void Images::ToGrayScale()
 {
  ViewPort(xStrt+3,yStrt+35,xStrt+xOff+2,yStrt+yOff+34);
  char far *GrBuf;
  int Pg,i;
  int x=xStrt+3;
  int y=yStrt+35;
  int b=yStrt+35+yOff;


  for (Pg=y/64;Pg<=(yStrt+yOff+35)/64;Pg++)
   {
    i = y%64;
    GetKey();
    Plot(x,y,GetPixel(x,y));
    GrBuf = GrBufAddr(x,y);
    for (;i<64 && y<=b;i++,y++,GrBuf+=1024)
       RGBToGray(GrBuf,xOff);
   }
 }
void Images::Dither(int Which)
 {
  F.SetFilter(Which);
  int i,j,x,y,Pix,d;
  ViewPort(xStrt+3,yStrt+35,xStrt+xOff+2,yStrt+yOff+34);
  for (i=0,y=yStrt+35;i<yOff;i++,y++)
   for (j=0,x=xStrt+3;j<xOff;j++,x++)
    {
     Pix = GetPixel(x,y);
     d   = (Pix<216) ? Pix%36:Pix-216;
     d   = d - (20);
     Plot(x,y,(d >=0) ? 255:0);
     F.Dither(x,y,d);
    }
 }
main()
 {
  SelectMode(Vga1024x768x256);
  Images A(40,0,320,320);
  A.SetTitle("Dithered : Stevenson & Arce");
  A.Show();
/*  Images B(400,0,320,320);
  B.SetTitle("Dithered : Sierra");
  B.Show();
  Images C(40,380,320,320);
  C.SetTitle("Dithered : Judi Jarvis Ninke");
  C.Show();
  Images D(400,380,320,320);
  D.SetTitle("Dithered : Stucki");
  D.Show();*/
  A.RGBPallette();
/*  B.RGBPallette();
  C.RGBPallette();
  D.RGBPallette();*/
  if (GetKey() != EscKy)
   {
    //A.ToGrayScale();
    //C.Dither(Ninke);
//    D.Dither(Stucki);
    A.Dither(Sierra);
   }
  GetKey();
  return(0);
 }