#ifndef __FORM_H
#define __FORM_H

#include <Tools.h>
#include <string.h>
#include <kbd.h>
#include <alloc.h>

#define ToolJustify   0x0300
#define JustShft      8
#define BoxStyle      0x00C0
#define BoxShft       6
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>            ScrX  Screen Capture eXtensions              <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

#define SlideRt        0x01
#define SlideLt        0x02
#define SlideDn        0x03
#define SlideUp        0x04

#define SlideRtDn      0x05
#define SlideLtDn      0x06
#define SlideRtUp      0x07
#define SlideLtUp      0x08

#define RollRt         0x09
#define RollLt         0x0A
#define RollDn         0x0B
#define RollUp         0x0C

#define EffShadow      0x20
#define EffHalfShadow  0x40
#define NoShadow       0x80
#define NoAlloc        0x8000
#define MaskAlloc      0x7FFF

class far ScrX
 {
   protected  :
     word   swScr;

   private :

     byte   X,Y,W,H;
     char   *Buffer;
     word   BufSize;

   public :

     ScrX();
     ~ScrX();

     void SetEffect(word Eff);

     void Copy(byte DstPg,byte SrcPg,byte x,byte y,byte w,byte h);
     void xCopy(byte DstPg,byte SrcPg,word DstOff,word SrcOff,byte w,byte h);
     void Capture(byte x,byte y,byte w,byte h);
     void Restore();
     void Restore(byte x,byte y);

     void ShowEffect(byte x,byte y,byte w,byte h);
     void UndoEffect();
     void Delete();

     friend class far Form;
  };


// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>               Class Frame  : Declarations               <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

class Frame : public Tool
 {
   private :
     word      swFrame;
     word      HotKey;
     Caption   *Cap;

   public :
     Frame(word inf);
     Frame(byte x,byte y,byte w,byte h,word inf);

     ~Frame();

     void SetEventLimit(byte Lim);
     byte AddEvent(Event *Evt);


     void SetCaption(char *Src);
     bool Show();
    // bool KeyDown(word Key);
 };

// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>            Class TagSheet :  Declarations               <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

class TagSheet : public Tool
 {
   protected :
     word     swSheet;
     Caption  *Tgs;
   public  :

     TagSheet();
     ~TagSheet();

     bool Show();
     bool Refresh();

     friend class far Tag;
 };

// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>                Class Tag :  Declarations                <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

class Tag : public Tool
 {
   protected :
     TagSheet  *Tgs;
     byte      AllocSize;
     byte      TgsCount;
     byte      TgsIdx;
     word      swTag;

   public :
     Tag();
     ~Tag();

     void SetTagCount(byte Count);
     void AddTag(char *Txt,byte EvtCount);
     byte AddEvent(byte Idx,Event *Evt);

     bool Show();
     bool Refresh();

     bool KeyDown(word Key);
 };
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>              Character User Interface Tool              <<>>
// <<>>                                                         <<>>
// <<>>                 Menu Generator Class                    <<>>
// <<>>                      Version 3.0                        <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

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
#define RefreshPad     0x8000

#define MaskPadFlags   0x007F
#define MaskPadState   0xFFBF
#define MaskActivity   0xFFF7
#define MaskVisibility 0xFFFD

#define OptsResvd_P    0x7F80  // reserved bits

#define MenuHz         0x0000
#define MenuVt         0x0001
#define Effects        0x0006
//#define EffectsDir     0x0018
#define Shadow         0x0040
#define Border         0x0080
#define MnuBoxStyle    0x0300

#define MainAppMenu    0x0400

#define MenuOpen       0x0800
//#define Colorised      0x1000
#define FullMenu       0x2000
#define UpdateScr      0x4000
#define InternalAlloc  0x8000
#define MaskMenuFlags  0x07FF

#define ShowEff        0x007E
#define SpcMask        0xFFF1
#define SetSpc         0x0070
#define StateShft        0x06
#define EffShft          0x01
#define MnuBoxShft       0x08

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
#define HSVSBox          0x0080
#define HDVSBox          0x0180
#define HSVDBox          0x0280
#define HDVDBox          0x0380

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

class  Menu;            // Dummy declaration for reference by pad
struct Pad
 {
   word    swItem;      // Item Status Word
   word    PadID;       // Pad Identification code
   byte    Hot;         // Position of Hot Character
   Caption *Cap;
   App     PadApp;      // App to be taken on selection
   char    *Msg;        // Message string for guidance
   Menu    *SubMenu;    // Ptr to Sub-Menu
 };

class Menu : public Tool
 {
   private :
     byte    Spc,N;             // Spacing & Index variable
     word    swMenu;            // Menu type & other flags
     Pad     *P;                // Ptr to first Pad
     byte    Hot,               // Index Of Highlighted Pad
	     visF,              // Index Of first Visible Pad
	     visL;              // Index Of last Visible Pad

     byte    MaxPads;           // Maximum number of pads in menu
     Menu    *Ptr;              // Pointer to a menu
     ScrX    MnuX;
     static  word    MenuID;

   private :

     byte Search(word ID,Pad *Q);

     byte ScrollUp(byte *idx,byte n);
     byte ScrollDown(byte *idx,byte n);
     void ScrollPadPrv();
     void ScrollPadNxt();
     byte NextPad(byte XorY,byte i);

     void DrawPad(byte xL,byte y,byte xR,Pad *Q,byte Txt,byte Hot);
     void DrawMenu();

     byte ShutMenu(byte Flag);
     void Open();
     void XecPadApp(byte Flag);

   public :

     Menu();
     Menu(word MenuType,byte MaxItem);
     ~Menu();

     byte AddPad(char *Txt, word PadType);
     byte AddPad(char *Txt, word PadType,App  PadApp);
     byte AddPad(char *Txt, word PadType,Menu *Sub);
     byte AddPad(char *Txt, word PadType,char *Hlp);
     byte AddPad(char *Txt, word PadType,App  PadApp,char *Hlp);

     byte AddMenu(word MenuType,byte MaxItem);
     byte AddMenu(Menu *M);

     byte AddHelp(word ID,char *Hlp);

     void EndMenu();

     void SetOrigin(byte x,byte y);

     byte GetState(word ID,bool& State);
     byte SetState(word ID,bool  State);

     byte Activity(word ID,bool OnOff);
     byte Visibility(word ID,bool OnOff);

     bool KeyDown(word Key);
     bool MouseMove(int mx,int my);
     bool MouseLeftClick(int mx,int my);

     //bool Refresh();
     bool Show();
     word GetMenuID();
 };

// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>               Class Form  : Declarations                <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

#define ShowClose     0x0001
#define ShowHelp      0x0002
#define ShowMinMax    0x0004
#define ShowSpecs     0x0008
#define HzScrollBar   0x0010
#define VtScrollBar   0x0020
#define ActiveClose   0x0040
#define ActiveHelp    0x0080
#define ActiveMinMax  0x0100
#define ActiveSpecs   0x0200
#define DrawHeader    0x0400
#define DrawBorder    0x0800
#define BorderStyle   0x3000
#define DrawShadow    0x4000
#define FillDialog    0x8000
#define StyleShft     12

#define FrmMoveSize   0x0080

#define AllOptions    0xFFFF

#define ActiveTgs     0x0001
#define HiddenTgs     0x0002
#define LockedTgs     0x0004
#define UsrDefSch     0x8000


class Form : public Tool
 {
  private:
   byte      nrmX,nrmY,nrmW,nrmH;
   byte      maxX,maxY,maxW,maxH;
   byte      minW;

   word      swForm;
   byte      WallPaper;
   char      *DlgAppName;
   ScrX      FrmX;

  public:

   Form(void);
   ~Form(void);

   void SetOrigin(byte x,byte y);
   void SetSize(byte x,byte y);

   void SetEventLimit(byte Lim);
   byte AddEvent(Event *Evt);
   byte AddMenu (Event *Evt);

  private :

   void Draw();

  public :
   bool KeyDown(word Key);
   //bool MouseMove(int mx,int my);
   //bool MouseLeftClick(int mx,int my);

   bool Show();
   bool Refresh();

   void SetCaption(char *DAN);
   void FormMinimise (void);
   void FormMaximise (void);

 };
#endif