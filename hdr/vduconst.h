#ifndef __VDUCONST_H
#define __VDUCONST_H

#define max(v1,v2) ((v1) > (v2)) ? (v1):(v2)
#define min(v1,v2) ((v1) < (v2)) ? (v1):(v2)

#define SetTexAttr(Attr) TxtAttr = (Attr)
#define SetDrawPg(Pg) DrwPg = (Pg)

#define SlideRt 0x01 //0x00
#define SlideLt 0x02 //0x04
#define SlideDn 0x03 //0x08
#define SlideUp 0x04 //0x0C

#define SlideRtDn 0x05 //0x10
#define SlideLtDn 0x06 //0x14
#define SlideRtUp 0x07 //0x18
#define SlideLtUp 0x08 //0x1C

#define RollRt 0x09
#define RollLt 0x0A
#define RollDn 0x0B
#define RollUp 0x0C

#define Single 0
#define HDVS   1
#define HSVD   2
#define Double 3

// Arrow Symbols

#define uArrow    0x18
#define dArrow    0x19
#define rArrow    0x1A
#define lArrow    0x1B
#define DblArrow  0x12

// FillStyles
#define Blank     0x20
#define Solid     0xDB
#define CloseDot  0xB2
#define Dotted    0xB1
#define WideDot   0xB0
#define Lines     0xF0
#define Hashes    0x23
#define Stars     0x0F
#define BlackFace 0x01
#define WhiteFace 0x02
#define KillBtn   0x02
#define Hearts    0x03
#define Diamonds  0x04
#define Clubs     0x05
#define Spade     0x06
#define Notes     0x0E
#define LtTriAngl 0x11
#define RtTriAngl 0x10
#define UpTriAngl 0x1E
#define DnTriAngl 0x1F
#define SqBox     0xFE
#define Sphere    0x07
#define Tick      0xFB
// Greek  Symbols
#define Alpha     0xE0
#define Beta      0xE1
#define Gamma     0xE2
#define PiSym     0xE3
#define Zigma     0xE4
#define Sigma     0xE5
#define Nue       0xE6
#define Tou       0xE7
#define Phi       0xE8
#define Theta     0xE9
#define Omega     0xEA
#define Delta     0xEB
#define Infinity  0xEC
#define Xi        0xED
#define Epsilon   0xEE
#define MinMax    0x12

#define Black     0x00
#define Blue      0x01
#define Green     0x02
#define Cyan      0x03
#define Red       0x04
#define Magenta   0x05
#define Brown     0x06
#define LightGray 0x07

#define DarkGray      0x08
#define LightBlue     0x09
#define LightGreen    0x0A
#define LightCyan     0x0B
#define LightRed      0x0C
#define LightMagenta  0x0D
#define Yellow        0x0E
#define White         0x0F

#define SingleLnCur   0x0D0D
#define DoubleLnCur   0x0D0E
#define TripleLnCur   0x0D0F
#define HalfBlkCur    0x0D10
#define FiveLnCur     0x0D11
#define SixLnCur      0x0D12
#define SevenLnCur    0x0D13
#define EightLnCur    0x0D14
#define NineLnCur     0x0D15
#define TenLnCur      0x0D16
#define ElevenLnCur   0x0D17
#define TwelveLnCur   0x0D18
#define ThirteenLnCur 0x0D19
#define FullBlkCur    0x0D0f

#define DnSingleLnCur   0x0020
#define DnDoubleLnCur   0x0021
#define DnTripleLnCur   0x0022
#define DnHalfBlkCur    0x0023
#define DnFiveLnCur     0x0024
#define DnSixLnCur      0x0025
#define DnSevenLnCur    0x0026
#define DnEightLnCur    0x0027
#define DnNineLnCur     0x0028
#define DnTenLnCur      0x0029
#define DnElevenLnCur   0x002A
#define DnTwelveLnCur   0x002B
#define DnThirteenLnCur 0x002C

#define DnFullBlkCur    0x002F
#define NullCursor    0x103F

#define ModeMask        0x3F
#define xResShift         12
#define yResShift          6
#define xResMask        0x7F
#define yResMask        0x3F

/*#define Txt80x25x16x8    0x03
#define Txt132x25x16x4   0x14
#define Txt80x25x16x8B   0x15
#define Txt132x44x16x2   0x54
#define XResShift   12
#define YResShift    6
#define XResMask  0xFF
#define ModeMask2 0x3F
#define YResMask  0x3F*/

#define Txt80x25x16x8    0x00050643
#define Txt80x30x16x8    0x00050792
#define Txt80x35x16x8    0x000508C3
#define Txt80x43x16x8    0x00050AC3
#define Txt80x50x16x8    0x00050C83
#define Txt80x60x16x8    0x00050F03

#define Txt100x37x16x4    0x0006496A

#define Txt132x25x16x4    0x00084663
#define Txt132x28x16x4    0x00084724
#define Txt132x30x16x4    0x000847A4
#define Txt132x35x16x8    0x000848C3
#define Txt132x43x16x8    0x00084AC3
#define Txt132x44x16x2    0x00084B22
#define Txt132x50x16x2    0x00084C83
#define Txt132x60x16x2    0x00084F03


/*
#define Vga320x200x16A   0x04
#define Vga320x200x16B   0x05
#define Vga640x200x2     0x06
#define Vga640x400x16A   0x08
#define Vga640x200x16    0x0E
#define Vga640x350x2B    0x0F
#define Vga640x350x16    0x10
#define Vga640x480x2     0x11
#define Vga640x480x16    0x12
#define Vga320x200x16C   0x13

#define Vga640x350x256   0x2D
#define Vga640x480x256   0x2E
#define Vga800x600x256   0x30
#define Vga1024x768x256  0x38*/

#define VgaFnt8x14       0x01
#define VgaFnt8x8        0x02
#define VgaFnt8x16       0x04
#define MCgaFnt8x14      0x11
#define MCgaFnt8x8       0x12
#define MCgaFnt8x16      0x14

#define PixVgaFnt8x14  0x21
#define PixVgaFnt8x8   0x22
#define PixVgaFnt8x16  0x24
#define PixMCgaFnt8x14 0x21
#define PixMCgaFnt8x8  0x22
#define PixMCgaFnt8x16 0x24

#define FntUsrRows     0x00
#define Fnt14Rows      0x01
#define Fnt25Rows      0x01
#define Fnt43Rows      0x01


#endif