#ifndef __MENU3D_H
#define __MENU3D_H

#include <Pixel.h>
#include <Kbd.h>

typedef void (*App)();
#define NoApp (App) NULL

#define LockedPad     0x0000
#define ActivePad     0x0001
#define HiddenPad     0x0002
#define MenuBreak     0x0004
#define ExitProgram   0x0008
#define ColourPad     0x0010
#define RadioPad      0x0020
#define CheckPad      0x0040
#define PadState      0x0080
#define PadColour     0x0F00
#define AppXec        0x1000
#define RetPad        0x2000
#define CloseMenus    0x4000
#define ReservedP     0x8000
#define SpcCorrection 0x0070

#define MenuHz        0x0000
#define MenuVt        0x0001
#define PadSpc        0x000E
#define Effects       0x0030
#define EffectsDir    0x01C0
#define Shadow        0x0200
#define Border        0x0400
#define BoxStyle      0x1800
#define ReservedM     0x2000
#define UpdateScr     0x4000
#define MenuOpen      0x8000

#define ShowEff       0x03F0
#define SpcMask       0xFFF1
#define SetSpc        0x0070
#define SpcShft       0x01
#define StateShft     0x07
#define ColourShft    0x08
#define EffShft       0x04
#define BoxShft       0x0B

#define XecPad         0x01
#define Close          0x02
#define MaskClose      0xFD
#define CloseAll       0x04
#define RefreshMenu    0x08
#define OpenMenu       0x10
#define CloseMenu      0x06
#define XecOrClose     0x03
#define RefAndClose    0x0A
#define XecAndClose    0x03
#define XecAndCloseAll 0x07
#define None           0x00

#define NoShow         0x0006

struct Pad
 {
   char *Prompt;
   char *ShortCut;
   byte Pos;
   word swPad;
   App  PadApp;
   char *Hlp;
 };
struct Scheme
 {
  byte Nrm;
  byte Hot;
  byte Txt;
  byte TxtHi;
  byte Xec;
  byte XecHi;
  byte Lck;
 };

class Menu
 {
  private :

   int    l,t,r,b,Wd,Ht;
   byte   Max,NumDef;
   word   swMenu;
   Pad    *M;
   byte   CurP;
   Scheme Sch;
   byte UsrMenuID;
  public :
   Menu();
   ~Menu();
   void DefineMenu(word MenuType,int L,int T,int R,int B,byte MaxPad,Scheme S);
   void DefinePad(char *Lbl,word type,App PadApp);
   void SetPadHelp(byte Which,char *Str);

   void DrawPad(int x,int y,byte i,byte Txt,byte TxtHi);
   void DrawMenu();

   byte MenuKeys();
   void Xecute();
   word MenuID();
 };

void InitScheme();
extern Scheme GrayScale,Classic;
#endif