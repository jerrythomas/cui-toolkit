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

// cui Drawing Routines
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
#define White           0x0F
#define ModeMask        0x3F
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

class far VDU
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
     void far SetScreen();
     char *BufAddr(byte Page);
 };

// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>                Mouse :  Mouse Information               <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

class far Mouse
  {
    private :
      int xSz,ySz;

    public  :
      int  x,y;
      word BtnState;
      word EvtFlags;

      Mouse();
      void far SetMouse(int mx,int my,word Btn,word Evt);
      void far SetScale(int x_Sz,int y_Sz);
  };
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>             ViewPort :  Screen ViewPorts                <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

class far ViewPort
  {
    public :
      byte X,Y,W,H;

      ViewPort();
      void far Set(byte x,byte y,byte w,byte h);
  };

  byte far GetAdapterInf(VgaInf *Vai);
  word far GetMaxX();
  word far GetMaxY();
  byte far GetMaxPg();
  byte far GetMaxCol();

  void far GetVidAt(byte Page, byte x ,byte y, byte& Chr, byte& Attr);
  void far SetVidAt(byte Page, byte x ,byte y, byte Chr, byte Attr);

  void far ModeSearch(dword Mode);
  void far ClrPage(byte Page, byte Attr);
  void far FillChr(byte L, byte T, byte R, byte B, byte Fill);
  void far ChrBox(byte L, byte T, byte R, byte B, byte Fill);

  void far DrawLineHz(byte xL, byte y, byte xR, byte Style);
  void far DrawLineVt(byte x, byte yT, byte yB, byte Style);
  void far DrawBox(byte L,byte T,byte R,byte B,byte Style);
  void far BoxShadow(byte L,byte T,byte R,byte B);

  int  far xPrintf(byte x, byte y, char *fmt,...);


extern byte     ActPg,DrwPg,RufPg;
extern VDU      Screen;
extern Mouse    Ms;
extern ViewPort Vp;

#endif