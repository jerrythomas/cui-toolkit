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


byte TxtAttr;
byte ForeCol;
byte VidChr,VidAtr;

byte FillStyle;
byte FillColor;
union REGS reg;

#define Round(v) (int)((v)+0.5)

void SetColour(byte Colour)
 {
  ForeCol = Colour;
 }
byte SetTxtCol(byte AttrB,byte AttrF)
 {
  return ((AttrB<<4)^(AttrF));
 }
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
  return (xCur);
 }

byte GetY(byte Page)
 {
  byte yCur;
  asm mov ah,0x03;
  asm mov bh,[Page];
  asm int VidInt;
  asm mov [[yCur]],dh;
  return (yCur);
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

byte     SetScanLns(byte ScanLnCode)
 {
  reg.h.ah = 0x12;
  reg.h.al = ScanLnCode;
  reg.h.bl = 0x30;
  int86(0x10,&reg,&reg);
  return(( reg.h.al == 0x12) ? 1:0);
 }
