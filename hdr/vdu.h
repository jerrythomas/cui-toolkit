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

#define SlideRt       0x01
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
#define RollUp        0x0C

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
#define White         0x0F


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
 //word GetMaxY();
 //byte GetMaxPg();
 //byte GetMaxCol();
 void SetPixel(int x,int y,byte col);
 byte GetPixel(int x,int y);

 void SetVidMode(byte vid_Mode);
 void ModeSearch(dword Mode);

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

 void ClrPage(byte Page, byte Attr);
 void FillChr(byte L, byte T, byte R, byte B, byte Fill);
 void ChrBox(byte L, byte T, byte R, byte B, byte Fill);

 void DrawLineHz(byte xL, byte y, byte xR, byte Style);
 void DrawLineVt(byte x, byte yT, byte yB, byte Style);
 void DrawBox(byte L,byte T,byte R,byte B,byte Style);
 void BoxShadow(byte L,byte T,byte R,byte B);

 void SaveVidBlock(Image *Scr,byte Pg,byte L,byte T,byte R,byte B);
 void ShowVidBlock(Image *Scr,byte Pg,byte Del);

 int  xPrintf(byte x, byte y, char *fmt,...);
 void Justify(byte L,byte y,byte R,char *fmt, ...);


 extern byte TxtAttr,VidChr,VidAtr;
 extern byte ForeCol,FillStyle,FillColor;

#endif