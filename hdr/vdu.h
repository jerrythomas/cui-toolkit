#ifndef __VDU_H
#define __VDU_H

#include <BaseInc.H>

#define VidInt 0x10

// Cursor Styles
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

//Font Styles
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

#define SetTexAttr(Attr) TxtAttr = (Attr)
#define SetDrawPg(Pg) DrwPg = (Pg)

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

 void SetPixel(int x,int y,byte col);
 byte GetPixel(int x,int y);

 void SetVidMode(byte vid_Mode);
 void SetCurType(word Style);
 void SetCurPos(byte Page, byte x, byte y);
 word GetCurPos(byte Page, byte& x, byte& y);
 byte GetX(byte Page);
 byte GetY(byte Page);
 void SetActivePage(byte Page);

 void ScrollWinUp(byte L, byte T, byte R, byte B, byte NumOfLns, byte Attr);
 void ScrollWinDn(byte L, byte T, byte R, byte B, byte NumOfLns, byte Attr);

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

 extern byte TxtAttr;
 extern byte VidChr,VidAtr;
 extern byte ForeCol,FillStyle,FillColor;

#endif