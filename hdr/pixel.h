#ifndef __PIX2D_H
#define __PIX2D_H

 #include <kbd.h>

 #ifndef __STDARG_H
  #include <stdarg.h>
 #endif

 #ifndef __STDIO_H
  #include <stdio.h>
 #endif

 #ifndef __DOS_H
  #include <dos.h>
 #endif

 #ifndef __STRING_H
  #include <string.h>
 #endif

 #ifndef __MATH_H
  #include <math.h>
 #endif



  #define LeftText   0
  #define CenterText 1
  #define RightText  2
  #define TopText    0
  #define BottomText 2

  #define Blue      0
  #define Green    36
  #define Cyan     72
  #define Red     108
  #define Magenta 144
  #define Yellow  180
  #define Gray    216

  #define ColorMask   0x20000000
  #define CoMonitor   0x40000000
  #define VgaOrTxt    0x80000000
  #define Graphics    0x80000000

  #define xResMask    0x7FF
  #define yResMask    0x3FF
  #define xResShift   18
  #define yResShift   8

  #define ModeMask    0x000000FF

  #define VgaCo1024x768x256 0xF0030038
  #define VgaCo800x600x256  0xEC825830
  #define VgaCo640x480x256  0xEA01E02E
  #define VgaCo640x400x256  0xEA019000
  #define VgaCo640x350x256  0xEA015E2D

  #define VgaBW1024x768x256 0xC0030038
  #define VgaBW800x600x256  0xCC825830
  #define VgaBW640x480x256  0xCA01E02E
  #define VgaBW640x400x256  0xCA019000
  #define VgaBW640x350x256  0xCA015E2D

  #define Vga1024x768x256 93 //98
  #define Vga800x600x256  92 //95
  #define Vga640x480x256  91 //94
  #define Vga640x400x256  90 //93
  #define Vga640x350x256  89 //92

  #define max(v1,v2) ((v1) > (v2)) ? (v1):(v2)
  #define min(v1,v2) ((v1) < (v2)) ? (v1):(v2)

  #define VidInt 0x10
  #define Ln10         2.30358509299405E+000
  #define OneOverLn10  0.43429448190325E+000
  #define Pi           3.1415927
  #define PiOver180    1.74532925199433E-002
  #define PiUnder180   5.72957795130823E+001
  #define Round(fval) (int)((fval)+(0.5))

  #define CopyPut   0x01
  #define Additive  0x02
  #define AndPut    0x03
  #define XorPut    0x04
  #define OrPut     0x05
  #define xCopyPut  0x06
  #define zBuffer   0x07

  struct ViewPortType
	  {
	   int x1,y1,x2,y2;
	  };
  struct RGB
	  {
	    byte red;
	    byte grn;
	    byte blu;
	  };

  typedef RGB PaletteRegister[256];


  //   <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>>
  //   <<>>                                              <<>>
  //   <<>>      Vga Memory Manipulation functions       <<>>
  //   <<>>                                              <<>>
  //   <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>>

  void GrMemFill (char far *Buf,byte fill,int num);
  void GrMemCopy (char far *Buf,int *img ,int num);
  void GrMemXCopy(char far *Buf,int *img ,int num);
  void GrMemAdd  (char far *Buf,int *img ,int num);
  void GrMemAND  (char far *Buf,int *img ,int num);
  void GrMemXOR  (char far *Buf,int *img ,int num);
  void GrMemOR   (char far *Buf,int *img ,int num);
  void GrMemZBuffer(char far *Buf,int *img,int num);
  void ExpandBits(int W,int H,char *bits,int *img);
  void ExpandBits(int W,int H,int  *bits,int *img);

  //   <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>>
  //   <<>>                                              <<>>
  //   <<>>     Vga 64k Refresh Buffer Manipulators      <<>>
  //   <<>>                                              <<>>
  //   <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>>

  byte     Vga64kPage(int x,int y);
  int      OnBoundary(int y);
  int      ScanLines (int Pg);
  char far *GrBufAddr(int x,int y);
  void     SetVga64kPage(byte Pg);
  void     SetVga64kPage(int x,int y);

  //   <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>>
  //   <<>>                                              <<>>
  //   <<>>           Vga Mode Setup & Control           <<>>
  //   <<>>                                              <<>>
  //   <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>>

  void Defaults();
  void SetVidMode(byte vid_Mode);
  void SelectMode(byte VidMode);
  void ModeSearch(dword Mode);
  void CloseGraph();

  int  xMax();
  int  yMax();
  int  GetX();
  int  GetY();
  int  Height();
  int  Width(char *S);
  byte Intensity(byte Col);
  void SetColor(byte Color);
  void ViewPort(int x1,int y1,int x2,int y2);
  void ViewPort(ViewPortType Vp);
  void GetViewPort(ViewPortType& Vp);

  void Justify(int X_Just,int Y_Just);
  void TextSize(int XSize,int YSize);

  //   <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>>
  //   <<>>                                              <<>>
  //   <<>>           Palette Setup functions            <<>>
  //   <<>>                                              <<>>
  //   <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>>

  void ClearPalette(PaletteRegister Hue);
  void SetPalette(PaletteRegister Hue);
  void InitPaletteCMY(PaletteRegister Hue);
  void InitPalette4x64(PaletteRegister Hue);
  void InitPalette7x36(PaletteRegister Hue);
  void CyclePalette(PaletteRegister Hue);

  void PixelToRGB(int Pix,float& red,float& grn,float &blu);
  void RGBToGray(char *buf,int len);
  int  RGBToPixel(float red,float grn,float blu);

  //   <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>>
  //   <<>>                                              <<>>
  //   <<>>           Simple Drawing Routines            <<>>
  //   <<>>                                              <<>>
  //   <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>>

  void MoveTo(int x,int y);
  byte GetPixel(int x,int y);
  void SetPixel(int x,int y,byte col);
  void Plot(int x,int y,int col);

  //   <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>>
  //   <<>>                                              <<>>
  //   <<>>    Advanced character & drawing routines     <<>>
  //   <<>>                                              <<>>
  //   <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>>

  void ChBmpOut(int x,int y,byte ch);

  void HzBoundLine(int x,int y,int w,byte Col);
  void HzLine(int x,int y,int w,byte Col);
  void VtLine(int x,int y,int w,int Col);
  void Line(int Xa,int Ya,int Xb,int Yb);
  void LineTo(int x,int y);
  void LineRel(int Dx,int Dy);
  void Circle(word x, word y, word Radius);
  void Rectangle(int l,int t,int r,int b);
  void Box(int x1,int y1,int x2,int y2,int fill);

  //   <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>>
  //   <<>>                                              <<>>
  //   <<>>    Advanced character & drawing routines     <<>>
  //   <<>>                                              <<>>
  //   <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>>
  // String Output routines

  int  gPrintf(int x,int y,char *fmt,...);
  int  Status(char *fmt,...);

  //   <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>>
  //   <<>>                                              <<>>
  //   <<>>             Block Mode Routines              <<>>
  //   <<>>                                              <<>>
  //   <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>>

  void ShowImage(int x,int y,int iW,int iH,int *img,int style);
  void Signature(int x,int y,int color);

  //   <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>>
  //   <<>>                                              <<>>
  //   <<>>                Input Routines                <<>>
  //   <<>>                                              <<>>
  //   <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>>

  void gScanf(int x,int y,char *Fs,float *N,int BkCol);
  void gScanf(int x,int y,char *Fs,float *N,float Mnf,float MxF,int BkCol);
  void gScanf(int x,int y,char *Fs,int *N,int BkCol);
  void gScanf(int x,int y,char *Fs,int *N,int Mnf,int MxF,int BkCol);

  //   <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>>
  //   <<>>                                              <<>>
  //   <<>>                GUI Primitives                <<>>
  //   <<>>                                              <<>>
  //   <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>>

  void Frame(int x1,int y1,int x2,int y2,byte Color);
  void Panel(int x1,int y1,int x2,int y2,byte Fill,byte Border);

  void Tile(int x1,int y1,int x2,int y2,byte Color);
  void Button(int x1,int y1,int x2,int y2,byte fill);
  void Label(int x1,int y1,int x2,int y2,char *lbl,byte fill,byte txt);

  void ShowPalette7x36(int x,int y);
  void ShowPalette4x64(int x,int y);
  extern PaletteRegister RGBHue;
#endif
