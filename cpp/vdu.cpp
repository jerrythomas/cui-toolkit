#ifndef __VDU_H
#define __VDU_H

#include <Kbd.h>
#include <math.h>
#include <stdarg.h>
#include <string.h>
//#include <Control.h>

#define VidInt 0x10

#define max(v1,v2) ((v1) > (v2)) ? (v1):(v2)
#define min(v1,v2) ((v1) < (v2)) ? (v1):(v2)

#define SetTexAttr(Attr) TxtAttr = (Attr)
#define SetDrawPg(Pg) DrwPg = (Pg)

/*#define SlideRt       0x01
#define SlideLt       0x02
#define SlideDn       0x03
#define SlideUp       0x04

#define SlideRtDn     0x05
#define SlideLtDn     0x06
#define SlideRtUp     0x07
#define SlideLtUp     0x08

#define RollRt        0x09
#define RollLt        0x0A
#define RollDn        0x0B
#define RollUp        0x0C*/

/*#define Single        0
#define HDVS          1
#define HSVD          2
#define Double        3

// Arrow Symbols

#define uArrow        0x18
#define dArrow        0x19
#define rArrow        0x1A
#define lArrow        0x1B
#define DblArrow      0x12

// FillStyles
#define Blank         0x20
#define Solid         0xDB
#define CloseDot      0xB2
#define Dotted        0xB1
#define WideDot       0xB0
#define Lines         0xF0
#define Hashes        0x23
#define Stars         0x0F
#define BlackFace     0x01
#define WhiteFace     0x02
#define KillBtn       0x02
#define Hearts        0x03
#define Diamonds      0x04
#define Clubs         0x05
#define Spade         0x06
#define Notes         0x0E
#define LtTriAngl     0x11
#define RtTriAngl     0x10
#define UpTriAngl     0x1E
#define DnTriAngl     0x1F
#define SqBox         0xFE
#define Sphere        0x07
#define Tick          0xFB

// Greek  Symbols
#define Alpha         0xE0
#define Beta          0xE1
#define Gamma         0xE2
#define PiSym         0xE3
#define Zigma         0xE4
#define Sigma         0xE5
#define Nue           0xE6
#define Tou           0xE7
#define Phi           0xE8
#define Theta         0xE9
#define Omega         0xEA
#define DeltaSym      0xEB
#define Infinity      0xEC
#define Xi            0xED
#define Epsilon       0xEE
#define MinMax        0x12

#define Black         0x00
#define Blue          0x01
#define Green         0x02
#define Cyan          0x03
#define Red           0x04
#define Magenta       0x05
#define Brown         0x06
#define LightGray     0x07

#define DarkGray      0x08
#define LightBlue     0x09
#define LightGreen    0x0A
#define LightCyan     0x0B
#define LightRed      0x0C
#define LightMagenta  0x0D
#define Yellow        0x0E
#define White         0x0F */


#define Cursor01      0x0F0F
#define Cursor02      0x0F0E
#define Cursor03      0x0F0D
#define Cursor04      0x0F0C
#define Cursor05      0x0F0B
#define Cursor06      0x0F0A
#define Cursor07      0x0F09
#define Cursor08      0x0F08
#define Cursor09      0x0F07
#define Cursor10      0x0F06
#define Cursor11      0x0F05
#define Cursor12      0x0F04
#define Cursor13      0x0F03
#define Cursor14      0x0F02
#define Cursor15      0x0F01
#define FullBlkCur    0x000F

#define DnCur01       0x0000
#define DnCur02       0x0001
#define DnCur03       0x0002
#define DnCur04       0x0003
#define DnCur05       0x0004
#define DnCur06       0x0005
#define DnCur07       0x0006
#define DnCur08       0x0007
#define DnCur09       0x0008
#define DnCur10       0x0009
#define DnCur11       0x000A
#define DnCur12       0x000B
#define DnCur13       0x000C
#define DnCur14       0x000D
#define DnCur15       0x000E

#define NullCursor    0x0F00

/*#define ModeMask        0x3F
#define xResShift         12
#define yResShift          6
#define xResMask        0xFF
#define yResMask        0x3F

#define Txt80x25x16x8   0x00050643
#define Txt80x30x16x8   0x00050792
#define Txt80x35x16x8   0x000508C3
#define Txt80x43x16x8   0x00050AC3
#define Txt80x50x16x8   0x00050C83
#define Txt80x60x16x2   0x00050F26

#define Txt100x37x16x4  0x0006496A

#define Txt132x25x16x4  0x00084663
#define Txt132x28x16x4  0x00084724
#define Txt132x30x16x4  0x000847A4
#define Txt132x35x16x8  0x000848C3
#define Txt132x43x16x8  0x00084AC3
#define Txt132x44x16x2  0x00084B22
#define Txt132x50x16x2  0x00084C83
#define Txt132x60x16x2  0x00084F03*/

#define VgaFnt8x14      0x01
#define VgaFnt8x8       0x02
#define VgaFnt8x16      0x04
#define MCgaFnt8x14     0x11
#define MCgaFnt8x8      0x12
#define MCgaFnt8x16     0x14

#define PixVgaFnt8x14   0x21
#define PixVgaFnt8x8    0x22
#define PixVgaFnt8x16   0x24
#define PixMCgaFnt8x14  0x21
#define PixMCgaFnt8x8   0x22
#define PixMCgaFnt8x16  0x24

#define FntUsrRows      0x00
#define Fnt14Rows       0x01
#define Fnt25Rows       0x01
#define Fnt43Rows       0x01

struct VGAConfig
	 {
	   byte DspType;
	   word VGAMem;
	   byte FeatureBits;
	   byte SwitchSettings;
	 };

 void SetColour(byte Colour);
 byte SetTxtCol(byte AttrB,byte AttrF);
 void SetShadAttr(byte Attr);
 void SetFillStyle(byte Style,byte Colour);

// word GetMaxX();
// word GetMaxY();
// byte GetMaxPg();
// byte GetMaxCol();
 void SetPixel(int x,int y,byte col);
 byte GetPixel(int x,int y);

 void SetVidMode(byte vid_Mode);
// void ModeSearch(dword Mode);

 void SetCurType(word Style);
 void SetCurPos(byte Page, byte x, byte y);
 word GetCurPos(byte Page, byte& x, byte& y);
 byte GetX(byte Page);
 byte GetY(byte Page);
 void SetActivePage(byte Page);

 void ScrollWinUp(byte L, byte T, byte R, byte B, byte NumOfLns, byte Attr);
 void ScrollWinDn(byte L, byte T, byte R, byte B, byte NumOfLns, byte Attr);

 //void GetVidAt(byte Page, byte x ,byte y, byte& Chr, byte& Attr);
 //void SetVidAt(byte Page, byte x ,byte y, byte Chr, byte Attr);
 void SetChrAtCur(byte Page, byte Chr, word Rept);
 void SetBackGround(byte Col);

 void TypeChrAtCur(byte Page, byte Chr);

 void GetVidMode(byte& NumCols, byte& VidMode, byte& ActPage);
 void SetPalletteReg(byte Colour,byte RegCod);
 void SetBorderCol(byte Colour);
 void TglBlink(byte OnOff);

 byte GetPalletteReg(byte RegCod);
 byte GetBorderCol();
 byte SetRegRGB(word RegCod,byte rgRed,byte rgGrn,byte rgBlu);
 void LoadRomFont(byte Font,byte Blk);
 void SetInt43H(byte Font,byte Rows);

 void GetVGACfg(VGAConfig& VGACfg);
 byte SetScanLns(byte ScanLnCode);
// int  GetVidState(VidAdptInf *VAI);

// void ClrPage(byte Page, byte Attr);
// void FillChr(byte L, byte T, byte R, byte B, byte Fill);
// void ChrBox(byte L, byte T, byte R, byte B, byte Fill);

// void DrawLineHz(byte xL, byte y, byte xR, byte Style);
// void DrawLineVt(byte x, byte yT, byte yB, byte Style);
// void DrawBox(byte L,byte T,byte R,byte B,byte Style);
// void BoxShadow(byte L,byte T,byte R,byte B);


// int  xPrintf(byte x, byte y, char *fmt,...);


 extern byte TxtAttr,VidChr,VidAtr;
 extern byte ForeCol,FillStyle,FillColor;

#endif


byte  TxtAttr;
byte  ForeCol;
byte  VidChr,VidAtr;

byte  FillStyle;
byte  FillColor;
union REGS reg;

#define Round(v) (int)((v)+0.5)

/*byte BoxS[5][8] = {
                    { 0xDA,0xC2,0xBF,0xB4,0xD9,0xC1,0xC0,0xC3 },
                    { 0xD5,0xD1,0xB8,0xB5,0xBE,0xCF,0xD4,0xC6 },
		    { 0xD6,0xD2,0xB7,0xB6,0xBD,0xD0,0xD3,0xC7 },
                    { 0xC9,0xCB,0xBB,0xB9,0xBC,0xCA,0xC8,0xCC },
                    { 0xC4,0xCD,0xB3,0xBA,0xC5,0xD8,0xD7,0xCE }
		  };*/

void SetColour(byte Colour)
 {
  ForeCol = Colour;
 }
byte SetTxtCol(byte AttrB,byte AttrF)
 {
  return((AttrB<<4)^(AttrF));
 }
/*void SetShadAttr(byte Attr)
 {
  TxtAttr  = ((Attr&0x70-0x10)&0x70);
  TxtAttr |= ((Attr&0x07-0x01)&0x07);
 }*/
void SetFillStyle(byte Style,byte Colour)
 {
  FillStyle = Style;
  FillColor = Colour;
 }

void SetVidMode(byte vid_Mode)
 {
  asm mov  ah,0x00;
  asm mov  al,[vid_Mode];
  asm int  VidInt;

 }
/*void ModeSearch(dword Mode)
 {
  VgaInf V;
  byte Flag=0x00;
  byte MaxX,MaxY;
  byte m    = (Mode&ModeMask);
  byte mx_X = (Mode>>xResShift)&xResMask;
  byte mx_Y = (Mode>>yResShift)&yResMask;
  TxtAttr=0x0F;
  SetVidMode(3);
  for(;m != 3 && m < 100 && !Flag;m++)
   {
    SetVidMode(m);
    GetAdapterInf(&V);

    MaxX = V.NumChrClmns;
    MaxY = V.NumChrRows;
    SetPixel(0,0,15);
    Flag = (mx_X == 80 && mx_Y == 25) ? 1:(GetPixel(0,0)!=15);
    Flag = (Flag && (MaxX==mx_X && MaxY==mx_Y));
   }
  if (!Flag) SetVidMode(3);
  Screen.SetScreen();
  Ms.SetScale(8,V.ChrHtScanLns);
 }*/

byte GetPixel(int x,int y)
 {
  byte rvCol;
  asm mov  ah,0x0D;
  asm mov  bh,[0];
  asm mov  cx,[x];
  asm mov  dx,[y];
  asm int  VidInt;
  asm mov  [[rvCol]],al;
  return rvCol;
 }

void SetPixel(int x,int y,byte col)
 {
   asm mov ah,0x0C;
   asm mov bh,0;
   asm mov cx,[x];
   asm mov dx,[y];
   asm mov al,[col];
   asm int VidInt;
 }


void SetCurType(word Style)
 {
  asm mov ah,0x01;
  asm mov cx,[Style];
  asm int VidInt
 }

void SetCurPos(byte Page,byte x,byte y)
 {
  asm mov ah,0x02;
  asm mov bh,[Page];
  asm mov dh,[y];
  asm mov dl,[x];
  asm int VidInt;
 }

word GetCurPos(byte Page,byte& x,byte& y)
 {
  reg.h.ah = 0x03;
  reg.h.bh = Page;
  int86(0x10,&reg,&reg);
  y = reg.h.dh;
  x = reg.h.dl;
  return(reg.x.cx);
 }

byte GetX(byte Page)
 {
  byte xCur;
  asm mov ah,0x03;
  asm mov bh,[Page];
  asm int VidInt;
  asm mov [[xCur]],dl;
  return(xCur);
 }

byte GetY(byte Page)
 {
  byte yCur;
  asm mov ah,0x03;
  asm mov bh,[Page];
  asm int VidInt;
  asm mov [[yCur]],dh;
  return(yCur);
 }

void SetActivePage(byte Page)
 {
  asm mov ah,0x05;
  asm mov al,[Page];
  asm int VidInt;
 }

void ScrollWinUp(byte L, byte T, byte R, byte B, byte NumOfLns, byte Attr)
 {
  asm mov ah,0x06;
  asm mov al,[NumOfLns];
  asm mov bh,[Attr];
  asm mov ch,[T];
  asm mov cl,[L];
  asm mov dh,[B];
  asm mov dl,[R];
  asm int VidInt;
 }

void ScrollWinDn(byte L, byte T, byte R, byte B, byte NumOfLns, byte Attr)
 {
  asm mov ah,0x07;
  asm mov al,[NumOfLns];
  asm mov bh,[Attr];
  asm mov ch,[T];
  asm mov cl,[L];
  asm mov dh,[B];
  asm mov dl,[R];
  asm int VidInt;
 }


void SetChrAtCur(byte Page, byte Chr, word Rept)
 {
  asm mov ah,0x0A;
  asm mov bh,[Page];
  asm mov al,[Chr];
  asm mov cx,[Rept];
  int86(0x10,&reg,&reg);
 }

void SetBackGround(byte Col)
 {
  asm mov ah,0x0B;
  asm mov bh,0x00;
  asm mov bl,[Col];
  asm int VidInt;
 }

void TypeChrAtCur(byte Page, byte Chr)
 {
  asm mov ah,0x0E;
  asm mov bh,[Page];
  asm mov al,[Chr];
  asm int VidInt;
 }

void GetVidMode(byte& NumCols, byte& VidMode, byte& ActPage)
 {
  reg.h.ah = 0x0F;
  int86(0x10,&reg,&reg);
  NumCols = reg.h.ah;
  VidMode = reg.h.al;
  ActPage = reg.h.bh;
 }

void SetPalletteReg(byte Colour,byte RegCod)
 {
  asm mov ah,0x10;
  asm mov al,0x00;
  asm mov bh,[Colour];
  asm mov bl,[RegCod];
  asm int VidInt;
 }
void SetBorderCol(byte Colour)
 {
  asm mov ah,0x10;
  asm mov al,0x01;
  asm mov bh,[Colour];
  asm int VidInt;
 }

void TglBlink(byte OnOff)
 {
  asm mov ah,0x10;
  asm mov al,0x03;
  asm mov bl,[OnOff];
  asm int VidInt;
/*  reg.h.ah = 0x10;
  reg.h.al = 0x03;
  reg.h.bl = OnOff;
  int86(0x10,&reg,&reg);*/
 }
byte GetPalletteReg(byte RegCod)
 {
  byte rvbyte;
  asm mov ah,0x10;
  asm mov al,0x07;
  asm mov bl,[RegCod];
  asm int VidInt;
  asm mov [[rvbyte]],bl;
  return(rvbyte);
 }
byte GetBorderCol()
 {
  byte rvCol;
  asm mov ah,0x10;
  asm mov al,0x08;
  asm int VidInt;
  asm mov [[rvCol]],bh;
  return(rvCol);
 }
byte SetRegRGB(word RegCod,byte rgRed,byte rgGrn,byte rgBlu)
 {
  byte rvbyte;
  asm mov ah,0x10;
  asm mov al,0x10;
  asm mov bx,[RegCod];
  asm mov ch,[rgGrn];
  asm mov cl,[rgBlu];
  asm mov dh,[rgRed];
  asm int VidInt;
  asm mov [[rvbyte]],bh;
  return(rvbyte);
 }

void LoadRomFont(byte Font,byte Blk)
 {
  asm mov ah,0x11;
  asm mov al,[Font];
  asm mov bl,[Blk];
  asm int VidInt;
 }
void SetInt43H(byte Font,byte Rows)
 {
  byte NumRows=0;
  if (Rows > 3)
   {
     NumRows = Rows;
     Rows = FntUsrRows;
   }
  asm mov ah,0x11;
  asm mov al,[Font];
  asm mov bl,[Rows];
  asm mov dl,[NumRows];
  asm int VidInt;
 }

void GetVGACfg(VGAConfig& VGACfg)
 {
  reg.h.ah = 0x12;
  reg.h.bl = 0x10;
  int86(0x10,&reg,&reg);
  VGACfg.DspType        = reg.h.bh;
  VGACfg.VGAMem         = (reg.h.bl+1)*64;
  VGACfg.FeatureBits    = reg.h.ch;
  VGACfg.SwitchSettings = reg.h.cl;
 }

byte SetScanLns(byte ScanLnCode)
 {
  reg.h.ah = 0x12;
  reg.h.al = ScanLnCode;
  reg.h.bl = 0x30;
  int86(0x10,&reg,&reg);
  return(( reg.h.al == 0x12) ? 1:0);
 }

//int GetVidState(VidAdptInf *VAI)
// {
/*    byte rv=0;
  word wSeg = FP_SEG(VAI);
  word wOff = FP_OFF(VAI);
  asm push es;
  asm push di;
  asm mov  ax,0x1B00;
  asm mov  bx,0;
  asm mov  dx,wSeg;
  asm mov  es,dx;
  asm mov  di,wOff;
  asm int  0x10;
  asm pop  di;
  asm pop  es;
  asm cmp  al,0x1B;
  asm jz   RET;
  asm mov rv,1;
  RET : return rv;*/

/*  struct REGPACK reg;
  reg.r_ax = 0x1B00;
  reg.r_bx = 0;
  reg.r_es = FP_SEG(VAI);
  reg.r_di = FP_OFF(VAI);
  intr(0x10,&reg);
  return(((reg.r_ax&0x00FF) == 0x1B) ? 1:0);
 }*/
/*

void ClrPage(byte Page,byte Attr)
 {
  char Pattern[2];
  byte X,Y;
  word DstOff=0;

  Pattern[1] = Attr;
  Pattern[0] = ' ';

  for (Y=0;Y<Screen.Height;Y++,DstOff+=Screen.DwScr)
    for (X=0;X<Screen.Width;X++)
      memcpy(Screen.BufAddr(Page)+DstOff+X*2,Pattern,2);
 }

bool BoxSym(byte X,byte Y,byte& R,byte& C)
 {
  bool RetVal = false;
  GetVidAt(DrwPg,X,Y,VidChr,VidAtr);
  if (VidChr > 0xB2 || VidChr < 0xDB)
   {
    for (Y=0;Y<5 && !RetVal;Y++)
     for  (X=0;X<8 && !RetVal;X++)
      RetVal = (BoxS[Y][X] == VidChr) ? true:false;
    R = Y-1;
    C = X-1;
   }
  return(RetVal);
 }

void BoxCorner(byte X,byte Y,byte R,byte C)
 {
  byte NewR,NewC,Va,Vb;
  NewR = R;
  NewC = C;

  if (BoxSym(X,Y,R,C))
   {
    if (R == NewR)
     {
      switch(NewC)
       {
	case 0 : C = (C+2)%8;
		 NewC = (C<2)? 7:(C==2)? NewC:(C<5)? 1:NewR+4;
		 break;
	case 2 : NewC = (C<2)? 1:(C==2)? NewC:(C<5)? 3:NewR+4;
		 break;
	case 4 : C = (C+6)%8;
		 NewC = (C<2)? 3:(C==2)? NewC:(C<5)? 5:NewR+4;
		 break;
	case 6 : C = (C+4)%8;
		 NewC = (C<2)? 5:(C==2)? NewC:(C<5)? 7:NewR+4;
		 break;
       }
      NewR = (C<5)? NewR:4;
     }
    else if (R==4)
     {
      if (C>3)
       {
	NewC = (C==NewR+4)? NewR+4:NewC;
	NewR = (C==NewR+4)? 4:NewR;
       }
      else
       {
	Va = (NewR == Single || NewR == HSVD) ? 0:1;
	Vb = (NewR == Single || NewR == HDVS) ? 2:3;
	NewC =(C==Va)? (NewC<4)? 1:5:NewC;
	NewC =(C==Vb)? (NewC==0 || NewC==6)? 7:3:NewC;
       }
     }
    }
  SetVidAt(DrwPg,X,Y,BoxS[NewR][NewC],TxtAttr);
 }
void DrawLineHz(byte xL, byte y, byte xR, byte Style)
 {
  byte NewR,NewC,R,C;
  byte Cx,Rx,V,Vc,x;

  for(x=xL;x <= xR;x++)
   {
    NewR = 4;
    NewC = Style;
    if (x==xL || x==xR)
     {
       if (BoxSym(x,y,R,C))
	{
	 Rx = Style + 2*(int)(R/2);
	 if (R==4)
	  {
	   Cx = C%4;
	   V  = (x==xL) ? 3:7;
	   NewR = (C==2)? Style:(C==3)? 2+Style:4;
	   NewC = (C<2) ? Style:(C<4)? 10-V:((C+Style)%2)? Style:Cx+4;
	  }
	 else
	  {
	   Cx = (x==xL)? (C+2)%8 : (C+6)%8;
	   V  = (R+Style)%2;
	   Vc = (x==xL);
	   NewR= ((Cx==5)||(Cx/3 && V))? 4:Rx;
	   Rx  = 4+R;
	   NewC=(Cx<3)? C:(V)? Style:(Cx==5)? Rx:(Cx>5)? (Vc)? 5:1:(Vc)? 1:5;
	  }
	}
     }
    else
     {
      if (BoxSym(x,y,R,C))
       {
	Cx = C%4;
	if (R==4)
	  NewC = (C<2)? Style:(C>3)? (Cx<2)? 4+Style:6+Style :2*C+Style;
	else
	 {
	  NewR = (Cx==3) ? 4:(R<2)? Style:Style+2;
	  NewC = (Cx==3) ? (R<2) ? 4+Style:6+Style:(C<3) ? 1:5;
	 }
       }
     }
    SetVidAt(DrwPg,x,y,BoxS[NewR][NewC],TxtAttr);
   }
 }
void DrawLineVt(byte x, byte yT, byte yB, byte Style)
 {
  byte NewR,NewC,R,C;
  byte Cx,Rx,Vc,y;

  for(y=yT;y <= yB;y++)
   {
    NewR = 4;
    NewC = Style+2;
    if (y==yT || y==yB)
     {
       if (BoxSym(x,y,R,C))
	{
	 if (R==4)
	  {
	   Cx = (C%4 +2*Style)%4;
	   Vc = (y==yT) ? 1:5;
	   NewR = (C<2)? C+2*Style:4;
	   NewC = (C<4) ? (C<2)? Vc:2+Style:(Cx<2)? C:2+Style;
	  }
	 else
	  {
	   Rx = ((R+2*Style)%4)/2;
	   Cx = (y==yT) ? C:(C+4)%8;
	   Vc = (y==yT) ? 7:3;
	   NewR = ((Cx==5)||(Cx/3 && Rx))? 4:R%2+2*Style;
	   NewC = (Cx<3)? C:(Rx)? 2+Style:(Cx==5)? 4+R:(Cx/3==2)? Vc:10-Vc;
	  }
	}
     }
    else
     {
      if (BoxSym(x,y,R,C))
       {
	Rx = Style*2;
	C  = (C+6)%8;
	Cx = C%4;
	if (R==4)
	  NewC = (C<2)? Style+2:(Cx%2)? Rx+5:Rx+4;
	else
	 {
	  NewR = (Cx==3) ? 4:(R%2)? Rx+1:Rx;
	  NewC = (Cx==3) ? (R%2) ? Rx+5:Rx+4:(C<3) ? 3:7;
	 }
       }
     }
    SetVidAt(DrwPg,x,y,BoxS[NewR][NewC],TxtAttr);
   }
 }

void DrawBox(byte L,byte T,byte R,byte B,byte Style)
 {
//	  if (L>R) Swap(&L,&R);
//	  if (T>B) Swap(&T,&B);
   BoxCorner(L,T,Style,0);
   BoxCorner(R,T,Style,2);
   BoxCorner(R,B,Style,4);
   BoxCorner(L,B,Style,6);
   DrawLineHz(L,T,R,Style&0x01);
   DrawLineHz(L,B,R,Style&0x01);
   DrawLineVt(R,T,B,(Style&0x02)>>1);
   DrawLineVt(L,T,B,(Style&0x02)>>1);
 }
void BoxShadow(byte L,byte T,byte R,byte B)
 {
  byte SaveAttr = TxtAttr;
  byte X,Y;
  TxtAttr=SetTxtCol(Black,DarkGray);
  for (X=L+1;X<=R+1;X++)
   {
    GetVidAt(DrwPg,X,B+1,VidChr,VidAtr);
    SetVidAt(DrwPg,X,B+1,VidChr,TxtAttr);
   }
  for (Y=T+1;Y<B+1;Y++)
   {
    GetVidAt(DrwPg,R+1,Y,VidChr,VidAtr);
    SetVidAt(DrwPg,R+1,Y,VidChr,TxtAttr);
   }
  SetTexAttr(SaveAttr);
 }

void FillChr(byte X,byte Y,byte W,byte H,byte FillPtn)
 {
   word DstOff = (Screen.Width*Y+X)*2;
   char Pattern[2];
   Pattern[1] = TxtAttr;
   Pattern[0] = FillPtn;

   for (Y=0;Y<H;Y++,DstOff+=Screen.DwScr)
    for (X=0;X<W;X++)
      memcpy(Screen.BufAddr(DrwPg)+DstOff+X*2,Pattern,2);
 }
void ChrBox(byte X,byte Y,byte W,byte H,byte FillPtn)
 {
   word DstOff = (Screen.Width*Y+X)*2;
   char Pattern[2];
   Pattern[1] = TxtAttr;
   Pattern[0] = FillPtn;

   for(X=0;X<W;X++)
    {
     memcpy(Screen.BufAddr(DrwPg)+DstOff+X*2           ,Pattern,2);
     memcpy(Screen.BufAddr(DrwPg)+DstOff+X*2+(H-1)*Screen.DwScr,Pattern,2);
    }
   for (Y=0;Y<H;Y++,DstOff+=Screen.DwScr)
    {
      memcpy(Screen.BufAddr(DrwPg)+DstOff      ,Pattern,2);
      memcpy(Screen.BufAddr(DrwPg)+DstOff+W*2-2,Pattern,2);
    }
 }

int xPrintf(byte x,byte y,char *fmt, ...)
{
  char buf[255];
  va_list argptr;
  byte len;
  int cnt;

  va_start(argptr, fmt);
  cnt = vsprintf(buf, fmt, argptr);
  va_end(argptr);
  len = strlen(buf);
  for (byte i=0; i < len;i++,x++)
   SetVidAt(DrwPg,x,y,buf[i],TxtAttr);
  return(cnt);
} */
