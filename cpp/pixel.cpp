#include <Pixel.H>
#include <Vga.h>

int  ColorMonitor;
int  mx_x,mx_y,mx_col;
int  mx_Scan,xOff;
int  x_Siz,y_Siz;
int  vp_mn_x,vp_mx_x,vp_mn_y,vp_mx_y;
int  Cur2D_x,Cur2D_y;
int  Pix_Col;
int  xJust,yJust;
byte CurPg;

char far *ChBmpBufStart = (char far*) (0xFFA6000EL);
char far *GrBufStart    = (char far*) (0xA0000000L);
dword GrOffset[768];
PaletteRegister RGBHue;


int GetVidState(VidAdptInf *VAI)
 {
  struct REGPACK reg;
  reg.r_ax = 0x1B00;
  reg.r_bx = 0;
  reg.r_es = FP_SEG(VAI);
  reg.r_di = FP_OFF(VAI);
  intr(0x10,&reg);
  return(((reg.r_ax&0x00FF) == 0x1B) ? 1:0);
 }

//   <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>>
// 64 kb Refresh buffer Manipulators

int  OnBoundary(int y)
 {
  int  Pg = y/mx_Scan;
  int Off = Pg*xOff/mx_x;
  return ((y == Pg*mx_Scan+Off) ? 1:0);
 }
int ScanLines(int Pg)
 {
  int Off = Pg*xOff;
  return mx_Scan + (Off+xOff)/mx_x -Off/mx_x;
 }
char far *GrBufAddr(int x,int y)
 {
  return (char far *) (GrBufStart +(word)(GrOffset[y]+x));
 }
byte Vga64kPage(int x,int y)
 {
   return (byte)(((double)(GrOffset[y]+x))/65536.0);
 }
void SetVga64kPage(byte Pg)
 {
  outport(0x3CD,Pg);
 }
void SetVga64kPage(int x,int y)
 {
  if (ColorMonitor)
    SetVga64kPage(Vga64kPage(x,y));
  else
    SetPixel(x,y,GetPixel(x,y));
 }



// Memory Manipulators

void GrMemFill(char far *Buf,byte fill,int num)
 {
  for (int i=0;i<num;i++)
     *(Buf+i) = fill;
 }
void GrMemCopy(char far *Buf,int *img,int num)
 {
  for (int i=0;i<num;i++)
     *(Buf+i) = *(img+i);
 }
void GrMemXCopy(char far *Buf,int *img,int num)
 {
  for (int i=0;i<num;i++)
    if (*(img+i) != 0)
       *(Buf+i) = *(img+i);
 }
void GrMemAdd(char far *Buf,int *img,int num)
 {
  for (int i=0;i<num;i++)
      *(Buf+i) = *(img+i);
 }
void GrMemAND(char far *Buf,int *img,int num)
 {
   for (int i=0;i<num;i++)
      *(Buf+i) &= *(img+i);
 }
void GrMemXOR(char far *Buf,int *img,int num)
 {
   for (int i=0;i<num;i++)
      *(Buf+i) ^= *(img+i);
 }
void GrMemOR(char far *Buf,int *img,int num)
 {
   for (int i=0;i<num;i++)
      *(Buf+i) |= *(img+i);
 }
void GrMemZBuffer(char far *Buf,int *img,int num)
 {
  for (int i=0;i<num;i++)
    if (Intensity(*(img+i)) >= Intensity(*(Buf+i)))
       *(Buf+i) = *(img+i);
 }
void ExpandBits(int W,int H,char *bits,int *img)
 {
  int i,j,b,k;
  k = 0;
  b = 7;
  for (i=0;i<H;i++)
   for (j=0;j<W;j++)
    {
     img[i*W+j] = (bits[k]>>b)&0x01;
     b += 7;
     b %= 8;
     if (b == 7) k++;
    }
 }
void ExpandBits(int W,int H,int *bits,int *img)
 {
  int i,j,b,k;
  k = 0;
  b = 15;
  for (i=0;i<H;i++)
   for (j=0;j<W;j++)
    {
     img[i*W+j] = (bits[k]>>b)&0x0001;
     b += 15;
     b %= 16;
     if (b == 15) k++;
    }
 }

// Vga Mode Initializers & Controllers

void Defaults()
 {
  x_Siz   = y_Siz   = 1;
  Cur2D_x = Cur2D_y = 0;
  xJust   = yJust   = 0;

  vp_mn_x = vp_mn_y = 0;
  vp_mx_x = mx_x;
  vp_mx_y = mx_y;

  Pix_Col = Blue+35;
  for (int i=0;i<mx_y;i++)
    GrOffset[i] = (dword)i*mx_x;

 }
/*void SetVidConstants(byte Mode)
 {

  switch(Mode)
   {
    case Vga640x350x256 : mx_x    = 640;
			  mx_y    = 350;
			  mx_col  = 256;
                          mx_Scan = 102;
			  xOff    = 256;
			  break;
    case Vga640x480x256 : mx_x    = 640;
			  mx_y    = 480;
			  mx_col  = 256;
			  mx_Scan = 102;
			  xOff    = 256;
			  break;
    case Vga800x600x256 : mx_x    = 800;
			  mx_y    = 600;
			  mx_col  = 256;
                          mx_Scan = 81;
                          xOff    = 736;
			  break;
    case Vga1024x768x256: mx_x    = 1024;
			  mx_y    = 768;
			  mx_col  = 256;
                          mx_Scan = 64;
			  xOff    = 0;
			  break;
   }
   mx_Scan = (int)(65536.0/mx_x);
   xOff    = (int)(65536.0-mx_x*mx_Scan);
   CurPg = 30;
 }*/

void SetVidMode(byte vid_Mode)
 {
  asm mov  ah,0x00;
  asm mov  al,[vid_Mode];
  asm int  VidInt;
 }

/*void SelectMode(byte VidMode)
 {
  SetVidConstants(VidMode);
  for (int i=0;i<mx_y;i++)
    GrOffset[i] = (dword)i*mx_x;
  Defaults();
  InitPalette7x36(RGBHue);
  int flag=0;         //96
   for (byte j=VidMode;j<100 && !flag;j++)
    {
      SetVidMode(j);
      SetPalette(RGBHue);
      CurPg = 30;
      SetPixel(xMax(),yMax(),25);
      flag = (GetPixel(xMax(),yMax())==25) ? 1:0;
    }
   if (!flag)
    SetVidMode(3);
   else
    {
     InitPalette7x36(RGBHue);
     SetPalette(RGBHue);
    }
 }*/
void ModeSearch(dword Mode)
 {
  VidAdptInf V;
  int Flag=0,MaxX,MaxY;
  byte m;

  mx_x    = (Mode>>xResShift)&xResMask;
  mx_y    = (Mode>>yResShift)&yResMask;
  mx_col  = (Mode&ColorMask) ? 256 :16;
  mx_Scan = (int)(65536.0/mx_x);
  xOff    = (int)(65536.0-mx_x*mx_Scan);
  CurPg   = 30;
  Defaults();

  InitPalette7x36(RGBHue);

  if (Mode&Graphics)
   {
    for(m=(int)(Mode&ModeMask);m < 150 && !Flag;m++)
     {
      SetVidMode(3);
      SetVidMode(m);
      GetVidState(&V);
      MaxX  = V.NumChrClmns*8;
      MaxY  = V.NumChrRows*V.ChrHtScanLns;
      MaxY += (MaxY==592) ? 8:0;
      if (MaxX == mx_x && MaxY == mx_y && V.MaxCols >= mx_col)
       {
	SetPalette(RGBHue);
	CurPg = 30;
	SetPixel(xMax(),yMax(),25);
	Flag = (GetPixel(xMax(),yMax())==25) ? 1:0;
	if (Flag)
	 {
	  SetPalette(RGBHue);
	  ColorMonitor = (int)(m == (int)(Mode&ModeMask));
	 }
       }
     }
   }
  else
    for(m=Mode&ModeMask;m < 100 && !Flag;m++)
      {
       SetVidMode(m);
       GetVidState(&V);
       MaxX = V.NumChrClmns;
       MaxY = V.NumChrRows;

       Flag = (MaxX == mx_x && MaxY == mx_y && V.MaxCols >= mx_col) ? 1:0;
     }
  if (!Flag)
   {
    SetVidMode(3);
    exit(1);
   }
 }
void CloseGraph()
 {
  SetVidMode(3);
  asm mov ah,0x01;
  asm mov cx,0x0d0f;
  asm int 0x10;

  asm mov ah,0x02;
  asm mov bh,0;
  asm mov dh,0;
  asm mov dl,0;
  asm int 0x10;
 }

int xMax()
 { return mx_x-1 ;}

int yMax()
 { return mx_y-1 ;}

int GetX()
 { return Cur2D_x ;}

int GetY()
 { return Cur2D_y ;}


int Height()
 {
  return Round(8*y_Siz);
 }

int Width(char *S)
 {
  return Round(8*x_Siz*strlen(S));
 }

void SetColor(byte Color)
 {
  Pix_Col = Color;
 }
byte Intensity(byte Col)
 {
  return Col%36;
 }
void Justify(int X_Just,int Y_Just)
 {
  xJust = X_Just%3;
  yJust = Y_Just%3;
 }

void TextSize(int XSize,int YSize)
 {
  x_Siz = (XSize > 0) ? XSize:1;
  y_Siz = (YSize > 0) ? YSize:1;
 }

void ViewPort(int x1,int y1,int x2,int y2)
 {
  vp_mn_x = max(0,min(x1,x2));
  vp_mx_x = min(xMax(),max(x1,x2));
  vp_mn_y = max(0,min(y1,y2));
  vp_mx_y = min(yMax(),max(y1,y2));
 }
void ViewPort(ViewPortType Vp)
 {
  ViewPort(Vp.x1,Vp.y1,Vp.x2,Vp.y2);
 }
void GetViewPort(ViewPortType& Vp)
 {
  Vp.x1 = vp_mn_x;
  Vp.x2 = vp_mx_x;
  Vp.y1 = vp_mn_y;
  Vp.y2 = vp_mx_y;
 }

// Pallette Setup Routines

void ClearPalette(PaletteRegister Hue)
 {
  word i;
  for(i=0;i<=255;i++)
   Hue[i].red = Hue[i].grn = Hue[i].blu = 0;
 }

void SetPalette(PaletteRegister Hue)
 {
  union REGS reg;
  SREGS inreg;
  reg.x.ax=0x1012;
  segread(&inreg);
  inreg.es=inreg.ds;
  reg.x.bx=0;
  reg.x.cx=256;
  reg.x.dx=(int)(&Hue[0]);
  int86x(0x10,&reg,&reg,&inreg);
 }

void InitPalette4x64(PaletteRegister Hue)
 {
  word i;
  ClearPalette(Hue);
  for(i=0;i<64;i++)
   {
    Hue[i+192].red = Hue[i+128].red = i;
    Hue[i+192].grn = Hue[i+ 64].grn = i;
    Hue[i+192].blu = Hue[i    ].blu = i;
   }
 }
void InitPaletteCMY(PaletteRegister Hue)
 {
  word i;
  ClearPalette(Hue);
  for(i=0;i<64;i++)
   {
    Hue[i+192].red = Hue[i    ].red = Hue[i    ].grn = i;
    Hue[i+192].grn = Hue[i+ 64].grn = Hue[i+ 64].blu = i;
    Hue[i+192].blu = Hue[i+128].blu = Hue[i+128].red = i;
   }
 }

void InitPalette7x36(PaletteRegister Hue)
 {
  word i;
  ClearPalette(Hue);
  for(i=0;i<36;i++)
   {
    Hue[i    ].blu = Round(1.8*i);
    Hue[i+ 36].grn = Hue[i].blu;
    Hue[i+ 72].blu = Hue[i+ 72].grn = Hue[i].blu;
    Hue[i+144].blu = Hue[i+144].red = Hue[i].blu;
    Hue[i+108].red = Hue[i].blu;
    Hue[i+180].grn = Hue[i+180].red = Hue[i].blu;
   }
  for (i=0;i<40;i++)
   Hue[i+216].red = Hue[i+216].grn = Hue[i+216].blu = Round(1.616*i);
 }

void CyclePalette(PaletteRegister Hue)
 {
  word i;
  RGB tmp;
  tmp=Hue[0];
  for(i=1;i<=255;i++)
	Hue[i-1]=Hue[i];
  Hue[255]=tmp;
  SetPalette(Hue);
 }


void PixelToRGB(int Pix,float& red,float& grn,float &blu)
 {
  float factor = (Pix < 216) ? (Pix%36)*1.8:(Pix-216)*1.616;
  Pix = (Pix<216) ? Pix/36+1:7;
  red = (Pix&0x04)*factor;
  grn = (Pix&0x02)*factor;
  blu = (Pix&0x01)*factor;
 }
void RGBToGray(char far *buf,int len)
 {
  float red,grn,blu;
  for (int i=0;i<len;i++)
   {
    PixelToRGB(*(buf+i),red,grn,blu);
    *(buf+i) = RGBToPixel(red*0.3,grn*0.59,blu*0.11);
   }
  /*
  red *= 0.3;
  grn *= 0.59;
  blu *= 0.11;*/
 }
int RGBToPixel(float red,float grn,float blu)
 {
   int rgb  = (red > 0) ? 1:0;
       rgb |= (grn > 0) ? 2:0;
       rgb |= (blu > 0) ? 4:0;
   int pix=(rgb-1)*36;
   float offset = (red+grn+blu)/3;
   offset /= (rgb<7) ? 1.8:1.616;
   offset = max(offset,0);
   pix += (rgb < 7) ? min(35,Round(offset)):min(39,Round(offset));
   return pix;
 }



// Simple Drawing functions

void MoveTo(int x,int y)
 {
  Cur2D_x = x;
  Cur2D_y = y;
 }
byte GetPixel(int x,int y)
 {
  byte rvCol;
  asm mov  ah,0x0D;
  asm mov  bh,[0];
  asm mov  cx,[x];
  asm mov  dx,[y];
  asm int  VidInt;
  asm mov  [[rvCol]],al;
  return(rvCol);
 }

void Plot(int x,int y,int col)
 {
  if (!(vp_mn_x > x || vp_mx_x < x || vp_mn_y > y || vp_mx_y < y))
   {
     byte Pg = Vga64kPage(x,y);
     if (CurPg != Pg)
      {
       CurPg = Pg;
       SetVga64kPage(x,y);
       /*byte pcol = col&0x00ff;
       asm mov ah,0x0C;
       asm mov bh,0;
       asm mov cx,[x];
       asm mov dx,[y];
       asm mov al,[pcol];
       asm int VidInt;*/
      }
//     else
  //    {
     //byte Pg =(byte)(((double)(GrOffset[y]+x))/65536.0);
      //outport(0x3CD,Pg);
      char far *GrBuf = GrBufAddr(x,y);//(char far *)(0xA0000000L + (word)(GrOffset[y]+x));
      *GrBuf  = col;
    //  }
   }
 }
void SetPixel(int x,int y,byte col)
 {
  if (!(vp_mn_x > x || vp_mx_x < x || vp_mn_y > y || vp_mx_y < y))
   {
    CurPg = Vga64kPage(x,y);
    byte pcol = col&0x00ff;
    asm mov ah,0x0C;
    asm mov bh,0;
    asm mov cx,[x];
    asm mov dx,[y];
    asm mov al,[pcol];
    asm int VidInt;
   /*
    byte Pg = (byte)(((double)(GrOffset[y]+x))/65536.0);
    char far *GrBuf = (char far *)(0xA0000000L + (word)(GrOffset[y]+x));
    outport(0x3CD,Pg);
    *GrBuf  = col;*/
   }
 }
void ChBmpOut(int x,int y,byte ch)
 {
  int i,j,l,m;
  char far *Buf=(char far *)(ChBmpBufStart+ch*8);
  for (i=0;i<8;i++,Buf++)
   for (j=0;j<8;j++)
    if (*Buf&(1<<(7-j)))
      for (m=j*x_Siz;m<j*x_Siz+x_Siz;m++)
	for (l=i*y_Siz;l<i*y_Siz+y_Siz;l++)
	 Plot(x+m,y+l,Pix_Col);
 }
void HzBoundLine(int l,int t,int w,byte Col)
 {
  int x = ((t/mx_Scan)*xOff)%mx_x;
  int r = w+l-1;
  char far *GrBuf;
  if (l<x)
   {
    x = min(x,min(r+1,vp_mx_x));
    GrBuf = GrBufAddr(l,t);
    //(char far*)(0xA0000000L + (word)(GrOffset[t]+l));
    Plot(l,t,Col);
    GrMemFill(GrBuf,Col,x-l);
    l = x;
   }
  if (l < r)
   {
    GrBuf = GrBufAddr(l,t);//(char far*)(0xA0000000L + (word)(GrOffset[t]+l));
    Plot(l,t,Col);
    GrMemFill(GrBuf,Col,r-l+1);
   }
 }

void HzLine(int x,int y,int w,byte Col)
 {
  char far *GrBuf;

  x = max(vp_mn_x,x);
  w = min(vp_mx_x-x+1,w);
  if (y >= vp_mn_y && y<= vp_mx_y)
   {
    if (OnBoundary(y))
       HzBoundLine(x,y,w,Col);
    else
     {
      GrBuf = GrBufAddr(x,y);//(char far*)(0xA0000000L + (word)(GrOffset[y]+x));
      Plot(x,y,Col);
      GrMemFill(GrBuf,Col,w);
     }
   }
 }
void VtLine(int x,int y,int w,int Col)
 {
  char far *GrBuf;
  int Pg;//,Max;
  y = max(vp_mn_y,y);
  w = min(vp_mx_y,w+y-1);

  if (x >= vp_mn_x && x<= vp_mx_x)
   for (Pg=y/mx_Scan;y<=w;Pg++)//Pg<=w/mx_Scan;Pg++)
    {
     if (OnBoundary(y))
       Plot(x,y++,Col);
     if (y<=w)
       Plot(x,y,Col);
     GrBuf = GrBufAddr(x,y);
     // (char far*)(0xA0000000L + (word)(GrOffset[y]+x));
     for (;!OnBoundary(y) && y <= w ;y++,GrBuf+=mx_x)
	*GrBuf=Col;
    }
 }
void Line(int Xa,int Ya,int Xb,int Yb)
 {
   float p;
   int   Dx,Dy,x,y,xEnd,yEnd,S;

   if (Xa==Xb && Ya==Yb)
    Plot(Xa,Ya,Pix_Col);
   else
    {
     Dx = abs(Xb-Xa);
     Dy = abs(Yb-Ya);
     S  = (Dx == 0) ? 1:(Xb-Xa)/Dx;
     S *= (Dy == 0) ? 1:(Yb-Ya)/Dy;
     if (Dx > Dy)
      {
       p  = 2*Dy-Dx;
       if (Xa > Xb)
	{
	 x    = Xb;
	 y    = Yb;
	 xEnd = Xa;
	}
       else
	{
	 x    = Xa;
	 y    = Ya;
	 xEnd = Xb;
	}
       Plot(x,y,Pix_Col);
       while(x <xEnd)
       {
	y += (p<0) ? 0:S;
	p += (p<0) ? Dy+Dy:Dy+Dy-Dx-Dx;
	Plot(++x,y,Pix_Col);
       }
      }
     else
      {
       p = 2*Dx-Dy;
       if (Ya > Yb)
	{
	 x    = Xb;
	 y    = Yb;
	 yEnd = Ya;
	}
       else
	{
	 x    = Xa;
	 y    = Ya;
	 yEnd = Yb;
	}
       Plot(x,y,Pix_Col);
       while(y < yEnd)
	{
	 x += (p<0) ? 0:S;
	 p += (p<0) ? Dx+Dx:Dx+Dx-Dy-Dy;
	 Plot(x,++y,Pix_Col);
	}
      }
    }
  }
void LineTo(int x,int y)
 {
  Line(Cur2D_x,Cur2D_y,x,y);
  MoveTo(x,y);
 }

void LineRel(int Dx,int Dy)
 {
  Line(Cur2D_x,Cur2D_y,Cur2D_x+Dx,Cur2D_y+Dy);
  Cur2D_x += Dx;
  Cur2D_y += Dy;
 }
void Circle(word x, word y, word Radius)
 {
  word a,b,c;
  a=Radius;
  b=0;
  do
   {
    c=Round(sqrt(Radius*Radius-a*a));
    while(b<=c)
     {
      Plot(x+a,y+b,Pix_Col);
      Plot(x+a,y-b,Pix_Col);
      Plot(x-a,y+b,Pix_Col);
      Plot(x-a,y-b,Pix_Col);
      Plot(x+b,y+a,Pix_Col);
      Plot(x+b,y-a,Pix_Col);
      Plot(x-b,y+a,Pix_Col);
      Plot(x-b,y-a,Pix_Col);
      b=b+1;
     }
    a=a-1;
   }
  while(b<=a);
 }

void Rectangle(int l,int t,int r,int b)
 {
  int x = min(l,r),
  y = min(t,b);

  r = max(l,r);
  b = max(t,b);
  l = x;
  t = y;

  x     = max(vp_mn_x,x);
  int w = min(vp_mx_x,r)-x+1;
  if (t >= vp_mn_y && t<= vp_mx_y)
     HzLine(x,t,w,Pix_Col);
  if (b >= vp_mn_y && b<= vp_mx_y)
     HzLine(x,b,w,Pix_Col);
  y   = max(vp_mn_y,y);
  w   = min(vp_mx_y,b)-y+1;
  if (l >= vp_mn_x && l<= vp_mx_x)
     VtLine(l,y,w,Pix_Col);
  if (r >= vp_mn_x && r<= vp_mx_x)
     VtLine(r,y,w,Pix_Col);
 }

void Box(int l,int t,int r,int b,int fill)
 {
  char far *GrBuf;
  int Pg;
  int x = max(vp_mn_x,min(l,r)),
      y = max(vp_mn_y,min(t,b));
  r = min(vp_mx_x,max(l,r));
  b = min(vp_mx_y,max(t,b));
  l = x;
  t = y;
  for (Pg=t/mx_Scan;y<=b;Pg++)
   {
    if (OnBoundary(y))
       HzBoundLine(l,y++,r-l+1,fill);
    GrBuf = GrBufAddr(x,y);
    //(char far*)(0xA0000000L + (word)(GrOffset[y]+x));
    if (y <= b)
       SetVga64kPage(x,y);//Plot(x,y,fill);
    for (;!OnBoundary(y) && y<=b;y++,GrBuf+=mx_x)
       GrMemFill(GrBuf,fill,r-l+1);
   }
  Rectangle(l,t,r,b);
 }


// Block Mode Drawing Routines

void ShowImage(int x,int y,int iW,int iH,int *img,int style)
 {
  char far *GrBuf;
  void (*GrSetMem)(char far *,int *,int);
  int *buf,ib=0;
  int Pg;
  int W,H,dx,dy;

  dx = max(vp_mn_x,x);
  dy = max(vp_mn_y,y);
  dx -= x;
  dy -= y;
  x += dx;
  y += dy;

  W  = min(vp_mx_x-x,iW-dx);
  H  = min(vp_mx_y-y,iH-dy);

  if (W >0 && H > 0)
   {
    switch (style)
     {
      case CopyPut  : GrSetMem = GrMemCopy   ;break;
      case Additive : GrSetMem = GrMemAdd    ;break;
      case AndPut   : GrSetMem = GrMemAND    ;break;
      case XorPut   : GrSetMem = GrMemXOR    ;break;
      case OrPut    : GrSetMem = GrMemOR     ;break;
      case xCopyPut : GrSetMem = GrMemXCopy  ;break;
      case zBuffer  : GrSetMem = GrMemZBuffer;break;
      default       : GrSetMem = GrMemCopy;
     }
    buf = new int[W*H];
    for (int i=0;i<H;i++)
     for (int j=0;j<W;j++)
       buf[i*W+j] = img[(dy+i)*iW+dx+j];

    iH = y+H-1;

    for (Pg=y/mx_Scan;y<=iH;Pg++)
     {
      if (OnBoundary(y))
       {
	 Plot(x,y,GetPixel(x,y));
	 iW = max(((y/mx_Scan)*xOff)%mx_x,x);
	 iW = min(iW-x,W);
	 GrBuf = GrBufAddr(x,y);
	 //(char far*)(0xA0000000L + (word)(GrOffset[y]+x));
	 GrSetMem(GrBuf,buf+ib,iW);
	 ib += iW;
	 if (iW < W)
	  {
	   SetVga64kPage(x,y);//Plot(x,y,GetPixel(x,y));
	   GrBuf = GrBufAddr(x+iW,y);
	   //(char far*)(0xA0000000L + (word)(GrOffset[y]+x+iW));
	   GrSetMem(GrBuf,buf+ib,W-iW);
	   ib += (W-iW);
	  }
	 y++;
       }
      GrBuf = GrBufAddr(x,y);//(char far*)(0xA0000000L + (word)(GrOffset[y]+x));
      if (y <= iH)
	SetVga64kPage(x,y);//Plot(x,y,GetPixel(x,y));
      for (;!OnBoundary(y) && y<=iH;y++,GrBuf+=mx_x,ib+=W)
	GrSetMem(GrBuf,buf+ib,W);
     }
    delete buf;
   }
 }
void Signature(int x,int y,int color)
 {
  char bits[125] =
	  {
	    0x00,0x3E,0x00,0x00,0x00, 0x00,0xFF,0xC0,0x00,0x00,
	    0x01,0xE0,0xF0,0x00,0x00, 0x03,0x80,0x18,0x00,0x00,
	    0x07,0x08,0x04,0x00,0x00, 0x06,0x1C,0x02,0x00,0x00,
	    0x06,0x18,0x00,0x00,0x00, 0x06,0x38,0x00,0x00,0x00,
	    0x02,0x33,0x80,0x00,0x00, 0x02,0x67,0xD0,0x46,0x0C,

	    0x01,0x6C,0xD8,0x66,0x1E, 0x08,0xC8,0x98,0xE3,0x3E,
	    0x1D,0xBF,0x2C,0xB3,0x78, 0x3F,0x08,0x4D,0x33,0xE0,
	    0x06,0x07,0x86,0x1F,0x80, 0x00,0x00,0x00,0x03,0x00,
	    0x00,0x3F,0x80,0x02,0x00, 0x00,0x78,0x60,0x04,0x00,
	    0x00,0xF0,0x18,0x08,0x00, 0x00,0xE0,0x06,0x10,0x40,
	    0x00,0xE0,0x01,0x20,0xE0, 0x00,0xF0,0x00,0xC0,0xE0,
	    0x00,0x70,0x00,0xC1,0x80, 0x00,0x1D,0x03,0x23,0x00,
	    0x00,0x06,0xFC,0x1C,0x00
	  };
  int *img;
  img = new int [1000];
  ExpandBits(40,25,bits,img);
  for (int i=0;i<1000;i++)
    img[i] *= color;
  x -= (xJust == CenterText) ? 20:(xJust == RightText)  ? 40:0;
  y -= (yJust == CenterText) ? 13:(yJust == BottomText) ? 25:0;

  ShowImage(x,y,40,25,img,0x06);
  delete img;
 }
 // String Output functions

int gPrintf(int x,int y,char *fmt,...)
 {
  char buf[255];
  va_list argptr;
  int len;
  int cnt;

  va_start(argptr, fmt);
  cnt = vsprintf(buf, fmt, argptr);
  va_end(argptr);
  len = strlen(buf);

  if (xJust != LeftText)
	 x -= (xJust==CenterText)? Width(buf)/2-1:Width(buf);
  if (yJust != TopText)
   y -= (yJust==CenterText)? Height()/2-1: Height();

  for (int i=0;i<len;i++,x+=Width("W"))
    ChBmpOut(x,y,buf[i]);
  return cnt;
 }

int Status(char *fmt,...)
 {
  ViewPortType Sav;

  char buf[255];
  va_list argptr;
  int len;
  int cnt;

  GetViewPort(Sav);
  ViewPort(0,0,xMax(),yMax());

  va_start(argptr, fmt);
  cnt = vsprintf(buf, fmt, argptr);
  va_end(argptr);
  len = strlen(buf);

  TextSize(1,1);

  int x=4*Width("W");
  int y=yMax()-22;
  SetColor(Red+7);
  Box(3,yMax()-27,3+87*Width("w"),yMax()-3,Gray+22);
  //Panel(0,yMax()-30,xMax(),yMax(),Gray+17,Gray+12);
  for (int i=0;i<len;i++,x+=Width("W"))
    ChBmpOut(x,y,buf[i]);

  ViewPort(Sav);
  return cnt;
 }

// Input routines

void gScanf(int x,int y,char *Fs,float *N,int BkCol)
 {
  char *Num,Ch;
  word Key;
  byte Dig=0,Dec=0,Flag=0x00;

  for (int i=0;i<strlen(Fs);i++)
   {
    if (Fs[i++] == '%')
     {
      Dig=0;
      while (Fs[i] >= '0' && Fs[i] <= '9')
	Dig += Dig*10+Fs[i++]-'0';
      if (Fs[i++] == '.')
       {
	Dec=0;
	while (Fs[i] >= '0' && Fs[i] <= '9')
	 Dec += Dec*10+Fs[i++]-'0';
       }
     }
   }
  int L = Dig+1;
  Num = new char[L+2];
  if (Dec)
   Dig -= Dec+1;

  i = 0;
  Justify(RightText,TopText);
  Box(x,y-4,x+Width("w")*(L+2),y+Height()+4,BkCol);
  Num[0]='\0';
  do
   {
    Key = GetKey();
    Ch=Key;
    if ((Ch >= '0' && Ch <= '9' && i<L) || (Ch == '-' && i == 0))
     {
      if ((i<Dig)||(Num[0]=='-' && i==Dig)||(Flag&0x01))
	  Num[i++] = Ch;
     }
    else if (Ch=='.' && Dec > 0)
     {
      if (!(Flag&0x01))
       {
	Num[i++] = Ch;
	Flag    ^= 0x01;
       }
     }
    else if (Key == EscKy)
     {
      Num[0] = '0';
      i = 1;
     }
    else if (Key == BackSp)
     {
      if (i > 0)
        if (Num[--i] == '.')
          Flag = 0x00;
     }
    Num[i]   = '\0';
    Box(x,y-4,x+Width("w")*(L+2),y+Height()+4,BkCol);
    gPrintf(x+Width("w")*(L+1),y,Num);
   }
  while (Key != EscKy && Key != RetKy && i<L && Key != ' ');
  *N = atof(Num);
  Justify(LeftText,TopText);
  delete Num;
 }

void gScanf(int x,int y,char *Fs,float *N,float MnF,float MxF,int BkCol)
 {
  Status("Number Should lie between %7.3f & %7.3f ",MnF,MxF);
  do
   gScanf(x,y,Fs,N,BkCol);
  while (*N < MnF || *N > MxF);
 }

void gScanf(int x,int y,char *Fs,int *N,int BkCol)
 {
  float nF;
   gScanf(x,y,Fs,&nF,BkCol);
  *N = (int)nF;
 }

void gScanf(int x,int y,char *Fs,int *N,int MnF,int MxF,int BkCol)
 {
  Status("Truncated Number Should lie between %d & %d ",MnF,MxF);
  do
   gScanf(x,y,Fs,N,BkCol);
  while (*N < MnF || *N > MxF);
 }


 // GUI Primitives


void Frame(int x1,int y1,int x2,int y2,byte Color)
 {
  for (int i=0;i<3;i++)
   {
    SetColor(Color+i*4);
    Rectangle(x1+i,y1+i,x2-i,y2-i);
   }
 }
void Panel(int x1,int y1,int x2,int y2,byte Fill,byte Border)
 {
   Box(x1,y1,x2,y2,Fill);
   Frame(x1,y1,x2,y2,Border);
 }
void Tile(int x1,int y1,int x2,int y2,byte Color)
 {
  for (int i=0;i<3;i++)
   {
    SetColor(Color+i*4);
    Rectangle(x1+i,y1+i,x2-i,y2-i);
   }
 }
void Button(int x1,int y1,int x2,int y2,byte fill)
 {
  Box(x1,y1,x2,y2,fill+7);
  Tile(x1,y1,x2,y2,fill);
 }
void Label(int x1,int y1,int x2,int y2,char *lbl,byte fill,byte txt)
 {
  Box(x1,y1,x2,y2,fill+7);
  Tile(x1,y1,x2,y2,fill);
  SetColor(txt);
  Justify(CenterText,CenterText);
  gPrintf((x1+x2)/2,(y1+y2)/2,lbl);
 }

void ShowPalette7x36(int x,int y)
 {
  Label(x-3,y-30,x+36*12+5,y-5,"7 x 36 Palette",Gray+10,Red+7);
  Tile(x-3,y-3,x+36*12+5,y+7*12+5,Gray+10);
  x += 2;
  int i,j;
  for (i=0,y+=2; i< 7;i++,y+=12)
   for (j=0;j < 36;j++)
    Box(x+j*12,y,x+j*12+10,y+10,i*36+j);
 }
void ShowPalette4x64(int x,int y)
 {
  Label(x-3,y-30,x+64*12+5,y-5,"4 x 64 Palette",Gray+10,Red+7);
  Tile(x-3,y-3,x+64*12+5,y+4*12+5,Gray+10);
  x += 2;
  int i,j;
  for (i=0,y+=2; i< 4;i++,y+=12)
   for (j=0;j < 64;j++)
    Box(x+j*12,y,x+j*12+10,y+10,i*64+j);
 }


