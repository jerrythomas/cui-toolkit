#ifndef __CUIBASE_H
#define __CUIBASE_H

#ifndef __STDIO_H
#include <stdio.h>
#endif

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
   public:
     word     Delta;
     byte     Width,Height;
     byte     Pages,Colors;

   private :
     char     *PgBuf[8];

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

byte   GetAdapterInf(VgaInf *Vai);


  word GetMaxX();
  word GetMaxY();
  byte GetMaxPg();
  byte GetMaxCol();
   void GetVidAt(byte Page, byte x ,byte y, byte& Chr, byte& Attr);
   void SetVidAt(byte Page, byte x ,byte y, byte Chr, byte Attr);
   void ClrPage(byte Page, byte Attr);
   void FillChr(byte L, byte T, byte R, byte B, byte Fill);
   void ChrBox(byte L, byte T, byte R, byte B, byte Fill);

   void DrawLineHz(byte xL, byte y, byte xR, byte Style);
   void DrawLineVt(byte x, byte yT, byte yB, byte Style);
   void DrawBox(byte L,byte T,byte R,byte B,byte Style);
   void BoxShadow(byte L,byte T,byte R,byte B);

   int  xPrintf(byte x, byte y, char *fmt,...);


extern byte  ActPg,DrwPg,RufPg;
extern VDU   Screen;
extern Mouse Ms;
extern ViewPort Vp;
#endif