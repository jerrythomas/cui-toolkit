#ifndef __CONTROL_H
#define __CONTROL_H

#include <stdio.h>
#include <kbd.h>

#define max(v1,v2) ((v1) > (v2)) ? (v1):(v2)
#define min(v1,v2) ((v1) < (v2)) ? (v1):(v2)

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

struct VgaInf
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
   private :
     char         *PgBuf[8];
   public :
     VgaInf  Vai;

   public:
     word     DwScr;
     byte     Width,Height;
     byte     Pages,Colors;


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

byte   GetAdapterInf(VgaInf *Vai);
extern byte  ActPg,DrwPg,RufPg;
extern VDU   Screen;
extern Mouse Ms;
extern ViewPort Vp;
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
  DwScr  = 160;
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
  DwScr  = Vai.NumChrClmns*2;
  ActPg  = Vai.ActDspPage;
  DrwPg  = ActPg;
  RufPg  = 1;
  PgBuf[0] = (char *)MK_FP(0xB800,Vai.BufStrtAddr);
  for (Pages=1;Pages<Vai.MaxPages;Pages++)
    PgBuf[Pages] = (char *)PgBuf[Pages-1]+Vai.VidRefreshBufLen;
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
