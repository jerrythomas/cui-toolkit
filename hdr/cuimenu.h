#ifndef __CUIMENU_H
#define __CUIMENU_H

// Cui.Cpp Version 3.0
// Total Hours  11 Hrs
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>              Character User Interface Tool              <<>>
// <<>>                                                         <<>>
// <<>>                 Menu Generator Class                    <<>>
// <<>>                                                         <<>>
// <<>>   Features :                                            <<>>
// <<>>                                                         <<>>
// <<>>        Multiple Levels                                  <<>>
// <<>>        Vertical/Horizontal Menus                        <<>>
// <<>>        Check / Radio Pads                               <<>>
// <<>>        Menubreaks                                       <<>>
// <<>>        Special Effects                                  <<>>
// <<>>        Direct Function Execution                        <<>>
// <<>>        Hidden & Scrollable Menu Items                   <<>>
// <<>>        Menu Activation/Deactivation                     <<>>
// <<>>        On Line Messages for menu items                  <<>>
// <<>>                                                         <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

#include <mouse.h>
#include <vdu.h>
#include <kbd.h>

#define RadioBtn       0x0010
#define RadioBtnOn     0x0050
#define CheckBtn       0x0020
#define CheckBtnOn     0x0060

#define ActiveRadio    0x0011
#define ActiveRadioOn  0x0051
#define ActiveCheck    0x0021
#define ActiveCheckOn  0x0061

#define HiddenRadio    0x0012
#define HiddenRadioOn  0x0052
#define HiddenCheck    0x0022
#define HiddenCheckOn  0x0062

#define LockedPad      0x0000
#define ActivePad      0x0001
#define HiddenPad      0x0002
#define MenuBreak      0x0004
#define Frozen         0x0008   // currently unused
#define RadioPad       0x0010
#define CheckPad       0x0020
#define PadState       0x0040
#define MaskPadFlags   0x007F
#define MaskPadState   0xFFBF

#define OptsResvd_P    0xFF80  // reserved bits

#define MenuHz         0x0000
#define MenuVt         0x0001
#define Effects        0x0006
#define EffectsDir     0x0018
#define Shadow         0x0040
#define Border         0x0080
#define BoxStyle       0x0300

#define ReservedM      0x3C00 // reserved bits

#define Colorised      0x1000
#define FullMenu       0x2000
#define UpdateScr      0x4000
#define InternalAlloc  0x8000
#define MaskMenuFlags  0x03FF

#define ShowEff        0x003E
#define SpcMask        0xFFF1
#define SetSpc         0x0070
#define StateShft        0x06
#define EffShft          0x01
#define BoxShft          0x08

#define XecPad           0x01
#define Close            0x02
#define MaskClose        0xFD
#define CloseAll         0x04
#define RefreshMenu      0x08
#define OpenMenu         0x10
#define CloseMenu        0x06
#define XecOrClose       0x03
#define RefAndClose      0x0A
#define XecAndClose      0x03
#define XecAndCloseAll   0x07
#define XecOrCloseAll    0x07
#define None             0x00

#define NoShow           0x0006
#define HSVSBoxShadow    0x00C0
#define HDVSBoxShadow    0x01C0
#define HSVDBoxShadow    0x02C0
#define HDVDBoxShadow    0x03C0

#define SlideRtMenuHz    0x0002
#define SlideLtMenuHz    0x0004
#define SlideDnMenuHz    0x0006
#define SlideUpMenuHz    0x0008
#define SlideRtDnMenuHz  0x000A
#define SlideLtDnMenuHz  0x000C
#define SlideRtUpMenuHz  0x000E
#define SlideLtUpMenuHz  0x0010
#define RollRtMenuHz     0x0012
#define RollLtMenuHz     0x0014
#define RollDnMenuHz     0x0016
#define RollUpMenuHz     0x0018

#define SlideRtMenuVt    0x0003
#define SlideLtMenuVt    0x0005
#define SlideDnMenuVt    0x0007
#define SlideUpMenuVt    0x0009
#define SlideRtDnMenuVt  0x000B
#define SlideLtDnMenuVt  0x000D
#define SlideRtUpMenuVt  0x000F
#define SlideLtUpMenuVt  0x0011
#define RollRtMenuVt     0x0013
#define RollLtMenuVt     0x0015
#define RollDnMenuVt     0x0017
#define RollUpMenuVt     0x0019

class Menu;            // Dummy declaration for reference by pad
struct Pad
 {
   word   swItem;      // Item Status Word
   word   PadID;       // Pad Identification code
   byte   Hot;         // Position of Hot Character
   char   *Prompt;     // Contains the Prompt string
   char   *ShortCut;   // Address of ShortCut String
   App    PadApp;      // App to be taken on selection
   char   *Msg;        // Message string for guidance
   Menu   *SubMenu;    // Ptr to Sub-Menu
 };

class Menu
 {
   private :
     Scheme  *MenuColSch;       // Colour Scheme
     byte    L,T;               // Top Left Coordinates of Menu
     byte    W,                 // Width  Of Menu
	     H;                 // Height Of Menu
     byte    Spc,N;             // Spacing & Index variable
     word    swMenu;            // Menu type & other flags
     Pad     *P;                // Ptr to first Pad
     byte    Hot,               // Index Of Highlighted Pad
	     visF,              // Index Of first Visible Pad
	     visL;              // Index Of last Visible Pad

     byte    MaxPads;           // Maximum number of pads in menu
     Menu    *Ptr;              // Pointer to a menu

   private :
     byte Search(word ID,Pad *Q);

     byte ScrollUp(byte *idx,byte n);
     byte ScrollDown(byte *idx,byte n);
     void ScrollPadPrv();
     void ScrollPadNxt();
     byte NextPad(byte XorY,byte i);

     void DrawPad(byte xL,byte y,byte xR,Pad *Q,byte Txt,byte Hot);
     void DrawMenu();

     byte MenuMouse();
     byte MenuCtrl();

   public :

     Menu();
     Menu(word MenuType,byte MaxItem);
     ~Menu();

     byte addPad(char *Txt, word PadType);
     byte addPad(char *Txt, word PadType,App  PadApp);
     byte addPad(char *Txt, word PadType,Menu *Sub);
     byte addPad(char *Txt, word PadType,char *Hlp);
     byte addPad(char *Txt, word PadType,App  PadApp,char *Hlp);

     byte addMenu(word MenuType,byte MaxItem);
     byte addMenu(Menu *M);

     void addColor(Scheme *Sch);
     void addColor(byte Txt,byte TxtHi,byte Xec,byte XecHi,byte Lck,byte Box);

     void endMenu();

     void SetOrigin(int X,int Y);

     byte GetState(word ID);
     byte SetState(word ID);

     byte Activate(word ID);
     byte Deactivate(word ID);

     word XecMenu();
   /*
     void RePaintMenu();
     void SetPadHlp(word PadID,char *PadHlp);
     void SetPadState(word PadID,word State);
     void SetRepaintDeskTop(App PaintDesk);
     void SetCloseDeskTop(App CloseDesk);*/
 };

extern Scheme Classic,CoolBlue,SoftGreen,RedAlert,StatusBar;
#endif
