#ifndef __CUIBASE_H
#define __CUIBASE_H

#ifndef __KBD_H
#include <kbd.h>
#endif

#ifndef __VDU_H
#include <vdu.h>
#endif

#ifndef __MOUSE_H
#include <mouse.h>
#endif


#define max(v1,v2) ((v1) > (v2)) ? (v1):(v2)
#define min(v1,v2) ((v1) < (v2)) ? (v1):(v2)

// Box Style Codes
#define Single        0
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

//Colour Codes : Dark
#define Black         0x00
#define Blue          0x01
#define Green         0x02
#define Cyan          0x03
#define Red           0x04
#define Magenta       0x05
#define Brown         0x06
#define LightGray     0x07
//Colour Codes : Light
#define DarkGray      0x08
#define LightBlue     0x09
#define LightGreen    0x0A
#define LightCyan     0x0B
#define LightRed      0x0C
#define LightMagenta  0x0D
#define Yellow        0x0E
#define White         0x0F

//Mode Information Extractors
#define ModeMask        0x3F
#define xResShift         12
#define yResShift          6
#define xResMask        0xFF
#define yResMask        0x3F

//Mode Constants
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
#define Txt132x60x16x2  0x00084F03

struct far CurXYPos
 {
   byte x,y;
 };

struct far DspAdptInf
 {
   byte  VidModes[3];
   dword Reserved1;
   byte  AvlScanLns;
   byte  AvlChrBlks;
   byte  MaxActChrBlks;
   word  MiscBIOSCpbl;
   word  Reserved2;
   byte  SaveAreaCpbl;
   byte  Reserved3;
 };

struct far VgaInf
  {
    DspAdptInf *V;
    byte       CurVidMode;
    word       NumChrClmns;
    word       VidRefreshBufLen;
    word       BufStrtAddr;
    CurXYPos   Page[8];
    byte       CurStrtScanLn;
    byte       CurEndScanLn;
    byte       ActDspPage;
    word       AdptBasePortAddr;
    byte       Regs3B8or3D8;
    byte       Regs3B9or3D9;
    byte       NumChrRows;
    word       ChrHtScanLns;
    byte       ActDspCode;
    byte       InActDspCode;
    word       MaxCols;
    byte       MaxPages;
    byte       NumScanLns;
    byte       PriChrBlk;
    byte       SecChrBlk;
    byte       MiscStateInf;
    byte       Reserved1[3];
    byte       AvlVidMem;
    byte       SavePtrStateInf;
    byte       Reserved2[13];
 };

// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>                VDU :  Screen Information                <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

class VDU
 {
   public:
     word    Delta;
     byte    Width,Height;
     byte    Pages,Colors;

   private :
     char    *PgBuf[8];

   public :
     VgaInf  Vai;

     VDU();
     void SetScreen();
     char *BufAddr(byte Page);
 };

// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>                Mouse :  Mouse Information               <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

class Mouse
  {
    private :
      int xSz,ySz;

    public  :
      int  x,y;
      word BtnState;
      word EvtFlags;

      Mouse();
      void SetMouse(int mx,int my,word Btn,word Evt);
      void SetScale(int x_Sz,int y_Sz);
  };
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>             ViewPort :  Screen ViewPorts                <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

class ViewPort
  {
    public :
      byte X,Y,W,H;

      ViewPort();
      void Set(byte x,byte y,byte w,byte h);
  };

  byte GetAdapterInf(VgaInf *Vai);
  word GetMaxX();
  word GetMaxY();
  byte GetMaxPg();
  byte GetMaxCol();

  void GetVidAt(byte Page, byte x ,byte y, byte& Chr, byte& Attr);
  void SetVidAt(byte Page, byte x ,byte y, byte Chr, byte Attr);

  void ModeSearch(dword Mode);
  void ClrPage(byte Page, byte Attr);
  void FillChr(byte L, byte T, byte R, byte B, byte Fill);
  void ChrBox(byte L, byte T, byte R, byte B, byte Fill);

  void DrawLineHz(byte xL, byte y, byte xR, byte Style);
  void DrawLineVt(byte x, byte yT, byte yB, byte Style);
  void DrawBox(byte L,byte T,byte R,byte B,byte Style);
  void BoxShadow(byte L,byte T,byte R,byte B);

  int  xPrintf(byte x, byte y, char *fmt,...);

  void SubStr(char *Src,char *Dst,int Strt,int Len);
  word StrToKey(char *src);

extern byte      ActPg,DrwPg,RufPg;
extern VDU       Screen;
extern Mouse     Ms;
extern ViewPort  Vp;

#endif

byte     ActPg,DrwPg,RufPg;
VDU      Screen;
Mouse    Ms;
ViewPort Vp;

// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>                Obtain Video Adapter Info                <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

byte GetAdapterInf(VgaInf *Vai)
 {
/*  byte rv=0;
  word wSeg = FP_SEG(Vai);
  word wOff = FP_OFF(Vai);
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
  struct REGPACK reg;
  reg.r_ax = 0x1B00;
  reg.r_bx = 0;
  reg.r_es = FP_SEG(Vai);
  reg.r_di = FP_OFF(Vai);
  intr(0x10,&reg);
  return(((reg.r_ax&0x00FF) == 0x1B) ? 1:0);
 }

// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>                 VDU : Module Source Code                <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

void VDU::VDU()
 {
  Width  = 0;
  Height = 0;
  Colors = 16;
  Delta  = 160;
  ActPg  = 0;
  DrwPg  = ActPg;
  RufPg  = 1;
  SetScreen();
 }

void VDU::SetScreen()
 {
  GetAdapterInf(&Vai);
  Width  = Vai.NumChrClmns;
  Height = Vai.NumChrRows;
  Colors = Vai.MaxCols;
  Delta  = Vai.NumChrClmns*2;
  ActPg  = Vai.ActDspPage;
  DrwPg  = ActPg;
  RufPg  = 1;
  PgBuf[0] = (char *)MK_FP(0xB800,Vai.BufStrtAddr);
  for (Pages=1;Pages<Vai.MaxPages;Pages++)
    PgBuf[Pages] = (char *)PgBuf[Pages-1]+Vai.VidRefreshBufLen;
  Ms.SetScale(8,Vai.ChrHtScanLns);
 }

char *VDU::BufAddr(byte Page)
 {
  Page = (Page<Pages) ? Page:0;
  return PgBuf[Page];
 }

// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>                Mouse : Module Source Code               <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

Mouse::Mouse()
 {
  xSz = ySz = 1;
 }
void Mouse::SetMouse(int mx,int my,word Btn,word Evt)
 {
  x        = mx / xSz;
  y        = my / ySz;
  EvtFlags = Evt;
  BtnState = Btn;
 }
void Mouse::SetScale(int x_Sz,int y_Sz)
 {
  xSz = (x_Sz > 0) ? x_Sz:1;
  ySz = (y_Sz > 0) ? y_Sz:1;
 }

// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>               ViewPort : Module Source Code             <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

ViewPort::ViewPort()
 {
  X = 0;
  Y = 0;
  W = Screen.Width;
  H = Screen.Height;
 }
void ViewPort::Set(byte x,byte y,byte w,byte h)
 {
  X = x;
  Y = y;
  W = min(w,Screen.Width);
  H = min(h,Screen.Height);
 }

byte far BoxS[5][8] = {
		       { 0xDA,0xC2,0xBF,0xB4,0xD9,0xC1,0xC0,0xC3 },
		       { 0xD5,0xD1,0xB8,0xB5,0xBE,0xCF,0xD4,0xC6 },
		       { 0xD6,0xD2,0xB7,0xB6,0xBD,0xD0,0xD3,0xC7 },
		       { 0xC9,0xCB,0xBB,0xB9,0xBC,0xCA,0xC8,0xCC },
		       { 0xC4,0xCD,0xB3,0xBA,0xC5,0xD8,0xD7,0xCE }
		      };

word GetMaxX()
 {
   return(Screen.Width-1);
 }
word GetMaxY()
 {
   return(Screen.Height-1);
 }
byte GetMaxPg()
 {
   return(Screen.Pages);
 }
byte GetMaxCol()
 {
   return(Screen.Colors);
 }

void GetVidAt(byte Page, byte x,byte y, byte& Chr, byte& Attr)
 {
  char *VgaBuf;
  VgaBuf = Screen.BufAddr(Page) + Screen.Delta * y + x*2;
  Chr  = *VgaBuf;
  Attr = *++VgaBuf;
 }

void SetVidAt(byte Page, byte x ,byte y, byte Chr, byte Attr)
 {
  char *VgaBuf;
  VgaBuf = Screen.BufAddr(Page) + Screen.Delta * y + x*2;
  *VgaBuf = Chr;
  *++VgaBuf = Attr;
 }

void ModeSearch(dword Mode)
 {
  byte Flag=0x00;
  byte m    = (Mode&ModeMask);
  byte mx_X = (Mode>>xResShift)&xResMask;
  byte mx_Y = (Mode>>yResShift)&yResMask;

  TxtAttr=0x0F;
  RufPg=1;
  DrwPg=0;
  SetVidMode(3);
  Screen.SetScreen();
  for(;m != 3 && m < 100 && !Flag;m++)
   {
    SetVidMode(m);
    Screen.SetScreen();
    SetPixel(0,0,15);
    Flag = (mx_X == 80 && mx_Y == 25);
    if (GetPixel(0,0) != 15) Flag = 1;
    Flag = (Flag && (Screen.Width==mx_X && Screen.Height==mx_Y));
   }
  if (!Flag) SetVidMode(3);
  Screen.SetScreen();
 }
void ClrPage(byte Page,byte Attr)
 {
  char Pattern[2];
  byte X,Y;
  word DstOff=0;

  Pattern[1] = Attr;
  Pattern[0] = ' ';

  for (Y=0;Y<Screen.Height;Y++,DstOff+=Screen.Delta)
    for (X=0;X<Screen.Width;X++)
      memcpy(Screen.BufAddr(Page)+DstOff+X*2,Pattern,2);
 /* for (byte x=0;x<Screen.Width;x++)
   for (byte y=0;y<Screen.Height;y++)
      SetVidAt(Page,x,y,' ',Attr);*/
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

   for (Y=0;Y<H;Y++,DstOff+=Screen.Delta)
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
     memcpy(Screen.BufAddr(DrwPg)+DstOff+X*2+(H-1)*Screen.Delta,Pattern,2);
    }
   for (Y=0;Y<H;Y++,DstOff+=Screen.Delta)
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
}

void SubStr(char *Src,char *Dst,int Strt,int Len)
 {
  int i,l=strlen(Src);
  for (i=0;i<Len && i<l-Strt;i++)
     Dst[i] = Src[Strt+i];
  Dst[i] = '\0';
 }

word StrToKey(char *src)
 {
  word rvKey=0,i=0,l;
  char *tmp,dst[6],Cmp[7];
  tmp = new(char[strlen(src)+1]);

  strcpy(tmp,src);
  strupr(tmp);
  for (i=0;tmp[i]!='\0' && (tmp[i]<'A' || tmp[i]>'Z');i++);
  switch(tmp[i])
   {
    case 'A':l=3;
             strcpy(Cmp,"Alt");
             break;
    case 'C':l=4;
             strcpy(Cmp,"Ctrl");
             break;
    case 'S':l=5;
             strcpy(Cmp,"Shift");
             break;
    default :l=6;
             strcpy(Cmp,"\0");
             break;
   }
  if (l<6)
   {
    SubStr(tmp,dst,i,l);
    if (!strcmpi(dst,Cmp))
     {
      for(i+=l;tmp[i]!='\0' && (tmp[i]<'A' || tmp[i]>'Z');i++);
       if (tmp[i]=='F')
        if (tmp[i+1] >= '0' && tmp[i+1] <='9')
         {
          SubStr(tmp,dst,i+1,2);
          l -= 3;
         }
     }
    switch(l)
     {
      case 0 : rvKey = AltF(atoi(dst));break;
      case 1 : rvKey = CtrlF(atoi(dst));break;
      case 2 : rvKey = ShiftF(atoi(dst));break;
      case 3 : rvKey = Alt(tmp[i]);break;
      case 4 : rvKey = Ctrl(tmp[i]);break;
      //case 5 : rvKey = Shft(tmp[i]);break;
     }
   }
   return(rvKey);
  }