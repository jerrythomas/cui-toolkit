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

class ScrX
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

     friend class Form;
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

     friend class Tag;
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

class Menu;            // Dummy declaration for reference by pad
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
word Menu::MenuID=0x100;
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>                   ScrX Module Source                    <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

ScrX::ScrX()
 {
   X = Y = W = H;
   swScr   =  NoAlloc;
   Buffer  = (char *)NULL;
   BufSize = 0;
 }
ScrX::~ScrX()
 {
   if (Buffer != (char *)NULL)
      delete Buffer;
 }

void ScrX::SetEffect(word Eff)
 {
   swScr |= Eff&0x00FF;
 }
void ScrX::Copy(byte DstPg,byte SrcPg,byte x,byte y,byte w,byte h)
 {
   word OffSet = (Screen.Width*y+x)*2;
   word Incr   = Screen.Width*2;
   xPrintf(20,20,"%d %d",Screen.Width,Screen.Delta);
   for(y=0;y<h;y++,OffSet+=Incr)
    {
     memcpy(Screen.BufAddr(DstPg)+OffSet,Screen.BufAddr(SrcPg)+OffSet,w*2);
     GetKey();
    }
 }
void ScrX::xCopy(byte DstPg,byte SrcPg,word DstOff,word SrcOff,byte w,byte h)
 {
   word Incr   = Screen.Width*2;
   for(byte y=0;y<h;y++,DstOff+=Incr,SrcOff+=Incr)
     memcpy(Screen.BufAddr(DstPg)+DstOff,Screen.BufAddr(SrcPg)+SrcOff,w*2);
 }

void ScrX::Capture(byte x,byte y,byte w,byte h)
 {
   if (Buffer != (byte*)NULL)
      delete Buffer;
   swScr |= (w==Screen.Width || h==Screen.Height) ? NoShadow:0;
   X = x;
   Y = y;
   W = (swScr&NoShadow)? w:w+1;
   H = (swScr&NoShadow)? h:h+1;
   swScr  &= MaskAlloc;
   BufSize = W*H*2;
   Buffer  = new char[BufSize];
   w = W*2;
   word Offset = (Screen.Width*y+x)*2;
   for (y=0;y<H;y++,Offset+=Screen.Width*2)
     memcpy(Buffer+y*w,(Screen.BufAddr(DrwPg)+Offset),w);
 }
void ScrX::Restore()
 {
  if (Buffer != (byte*)NULL)
   {
     byte w=W*2;
     byte y;
     word Offset = (Screen.Width*Y+X)*2;
     for (y=0;y<H;y++,Offset+=Screen.Width*2)
       memcpy(Screen.BufAddr(DrwPg)+Offset,Buffer+y*w,w);
   }
 }
void ScrX::Restore(byte x,byte y)
 {
  if (Buffer != (byte*)NULL)
   {
     byte w=W*2;
     X = x;
     Y = y;
     word Offset = (Screen.Width*Y+X)*2;
     for (y=0;y<H;y++,Offset+=Screen.Width*2)
       memcpy(Screen.BufAddr(DrwPg)+Offset,Buffer+y*w,w);
   }
 }
void ScrX::ShowEffect(byte x,byte y,byte w,byte h)
 {
   byte  n,wS,hS;
   if (swScr&NoShadow)
    { w++;h++;}
   if (!(X==x && Y==y && W==w && H==h) && Buffer != (char *)NULL)
    {
      Restore();
      if (swScr&NoShadow)
       {
         w--;h--;
         swScr^=NoShadow;
       }
      Capture(x,y,w,h);
    }
  wS = W;
  hS = H;
  W  = w;
  H  = h;


  byte  N  = max(W,H);
  byte  Style  = swScr&0x1F;
  word  SrcOff,DstOff;
  //word  Incr  = Screen.Width*2;

  if (Style == SlideRt)
     for(n=1;n<=W;n++)
      {
       DstOff = (Screen.Width*Y+X)*2;
       SrcOff = DstOff + (W-n)*2;
       xCopy(DrwPg,RufPg,DstOff,SrcOff,n,H);
       if (swScr&EffShadow) BoxShadow(X,Y,X+n-1,Y+H-1);
       delay(10);
      }
  else if (Style == SlideLt)
     for(n=1;n<=W;n++)
      {
       SrcOff = (Screen.Width*Y+X)*2;
       DstOff = SrcOff + (W-n)*2;
       xCopy(DrwPg,RufPg,DstOff,SrcOff,n,H);
       if (swScr&EffShadow) BoxShadow(X+W-n,Y,X+W-1,Y+H-1);
       delay(10);
      }
  else if (Style == SlideDn)
     for(n=1;n<=H;n++)
      {
       SrcOff = (Screen.Width*(Y+H-n)+X)*2;
       DstOff = (Screen.Width*Y + X)*2;
       xCopy(DrwPg,RufPg,DstOff,SrcOff,W,n);
       if (swScr&EffShadow) BoxShadow(X,Y,X+W-1,Y+n-1);
       delay(10);
      }
  else if (Style == SlideUp)
     for(n=1;n<=H;n++)
      {
       SrcOff = (Screen.Width*Y + X)*2;
       DstOff = (Screen.Width*(Y+H-n)+X)*2;
       xCopy(DrwPg,RufPg,DstOff,SrcOff,W,n);
       if (swScr&EffShadow) BoxShadow(X,Y+H-n,X+W-1,Y+H-1);
       delay(10);
      }
  else if (Style == SlideRtDn)
     for(n=1;n<=N;n++)
      {
       w  = W*n/N;
       h  = H*n/N;
       if (h>0 && w>0)
        {
         SrcOff = (Screen.Width*(Y+H-h)+X+W-w)*2;
         DstOff = (Screen.Width*Y+X)*2;
         xCopy(DrwPg,RufPg,DstOff,SrcOff,w,h);
	 if (swScr&EffShadow) BoxShadow(X,Y,X+w-1,Y+h-1);
         delay(10);
        }
      }
  else if (Style == SlideLtDn)
     for(n=1;n<=N;n++)
      {
       w      = W*n/N;
       h      = H*n/N;
       if (h>0 && w>0)
        {
         SrcOff = (Screen.Width*(Y+H-h)+X)*2;
	 DstOff = (Screen.Width*Y+X+W-w)*2;
         xCopy(DrwPg,RufPg,DstOff,SrcOff,w,h);
         if (swScr&EffShadow) BoxShadow(X+W-w,Y,X+W-1,Y+h-1);
         delay(10);
        }
      }
  else if (Style == SlideRtUp)
     for(n=1;n<=N;n++)
      {
       w      = W*n/N;
       h      = H*n/N;
       if (h>0 && w>0)
	{
         SrcOff = (Screen.Width*Y+X+W-w)*2;
         DstOff = (Screen.Width*(Y+H-h)+X)*2;
         xCopy(DrwPg,RufPg,DstOff,SrcOff,w,h);
	 if (swScr&EffShadow) BoxShadow(X,Y+H-h,X+w-1,Y+H-1);
         delay(10);
        }
      }
  else if (Style == SlideLtUp)
     for(n=1;n<=N;n++)
      {
       w      = W*n/N;
       h      = H*n/N;
       if (h>0 && w>0)
        {
          SrcOff = (Screen.Width*Y+X)*2;
          DstOff = (Screen.Width*(Y+H-h)+X+W-w)*2;
          xCopy(DrwPg,RufPg,DstOff,SrcOff,w,h);
          if (swScr&EffShadow) BoxShadow(X+W-w,Y+H-h,X+W-1,Y+H-1);
          delay(10);
        }
      }
  else
    Copy(DrwPg,RufPg,X,Y,W,H);
  W = wS;
  H = hS;
 }
void ScrX::UndoEffect()
 {
  byte n,w,h,eW,eH;
  eW = W;
  eH = H;
  if (!(swScr&NoShadow))
    { eW--;eH--;}
  byte  N  = max(eW,eH);
  byte  Style  = swScr&0x1F;
  word  SrcOff,DstOff;

  Copy(RufPg,DrwPg,X,Y,eW,eH);
  if (Style == SlideRt)
     for(n=eW;n>0;n--)
      {
       DstOff = (Screen.Width*Y+X)*2;
       SrcOff = DstOff + (eW-n)*2;
       Restore();
       xCopy(DrwPg,RufPg,DstOff,SrcOff,w,eH);
       if (swScr&EffShadow) BoxShadow(X,Y,X+n-1,Y+eH-1);
       delay(10);
      }
  else if (Style == SlideLt)
     for(n=eW;n>0;n--)
      {
       SrcOff = (Screen.Width*Y+X)*2;
       DstOff = SrcOff + (eW-n)*2;
       Restore();
       xCopy(DrwPg,RufPg,DstOff,SrcOff,w,eH);
       if (swScr&EffShadow) BoxShadow(X+eW-n+1,Y,X+eW,Y+eH-1);
       delay(10);
      }
  else if (Style == SlideDn)
     for(n=eH;n>0;n--)
      {
       SrcOff = (Screen.Width*(Y+eH-n)+X)*2;
       DstOff = (Screen.Width*Y + X)*2;
       Restore();
       xCopy(DrwPg,RufPg,DstOff,SrcOff,eW,n);
       if (swScr&EffShadow) BoxShadow(X,Y,X+eW-1,Y+n-1);
       delay(10);
      }
  else if (Style == SlideUp)
     for(n=eH;n>0;n--)
      {
       SrcOff = (Screen.Width*Y + X)*2;
       DstOff = (Screen.Width*(Y+eH-n)+X)*2;
       Restore();
       xCopy(DrwPg,RufPg,DstOff,SrcOff,eW,n);
       if (swScr&EffShadow) BoxShadow(X,Y+eH-n,X+eW-1,Y+eH-1);
       delay(10);
      }
  else if (Style == SlideRtDn)
     for(n=N;n>0;n--)
      {
       w  = eW*n/N;
       h  = eH*n/N;
       if (h>0 && w>0)
        {
	 SrcOff = (Screen.Width*(Y+eH-h)+X+eW-w)*2;
         DstOff = (Screen.Width*Y+X)*2;
         Restore();
         xCopy(DrwPg,RufPg,DstOff,SrcOff,w,h);
         if (swScr&EffShadow) BoxShadow(X,Y,X+w-1,Y+h-1);
         delay(10);
        }
      }
  else if (Style == SlideLtDn)
     for(n=N;n>0;n--)
      {
       w      = eW*n/N;
       h      = eH*n/N;
       if (h>0 && w>0)
        {
         SrcOff = (Screen.Width*(Y+eH-h)+X)*2;
         DstOff = (Screen.Width*Y+X+eW-w)*2;
         Restore();
         xCopy(DrwPg,RufPg,DstOff,SrcOff,w,h);
         if (swScr&EffShadow) BoxShadow(X+eW-w,Y,X+eW-1,Y+h-1);
	 delay(10);
        }
      }
  else if (Style == SlideRtUp)
     for(n=N;n>0;n--)
      {
       w      = eW*n/N;
       h      = eH*n/N;
       if (h>0 && w>0)
        {
         SrcOff = (Screen.Width*Y+X+eW-w)*2;
         DstOff = (Screen.Width*(Y+eH-h)+X)*2;
         Restore();
         xCopy(DrwPg,RufPg,DstOff,SrcOff,w,h);
	 if (swScr&EffShadow) BoxShadow(X,Y+eH-h,X+w-1,Y+eH-1);
         delay(10);
        }
      }
  else if (Style == SlideLtUp)
     for(n=N;n>0;n--)
      {
       w      = eW*n/N;
       h      = eH*n/N;
       if (h>0 && w>0)
        {
          SrcOff = (Screen.Width*Y+X)*2;
	  DstOff = (Screen.Width*(Y+eH-h)+X+eW-w)*2;
          Restore();
          xCopy(DrwPg,RufPg,DstOff,SrcOff,w,h);
          if (swScr&EffShadow) BoxShadow(X+eW-w,Y+eH-h,X+eW-1,Y+eH-1);
          delay(10);
        }
      }
    Restore();
 }
void ScrX::Delete()
 {
  if (Buffer != (char*)NULL)
      delete Buffer;
  Buffer = (char*)NULL;
 }

// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>                   Frame Module Source                   <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>


Frame::Frame(word inf)
 {
   SetEventID(EventFrame);
   swFrame = inf;
   Cap     = (Caption*)NULL;
   cs      = &Classic;
 }
Frame::Frame(byte x,byte y,byte w,byte h,word inf)
      :Tool(x,y,w,h)
 {
   SetEventID(EventFrame);
   swFrame = inf;
   Cap     = (Caption*)NULL;
   cs      = &CoolBlue;
 }
Frame::~Frame()
 {
   delete Cap;
 }
void Frame::SetEventLimit(byte Lim)
 {
  if (Hndl == (Despatch*)NULL)
      Hndl = new Despatch(this,Lim);
 }

byte Frame::AddEvent(Event *Evt)
 {
   return (Hndl != (Despatch*)NULL) ? Hndl->AddEvent(Evt):1;
 }
bool Frame::Show()
 {
   byte x = (swFrame&ToolJustify)>>JustShft;
   TxtAttr = cs->Box;
   DrawBox(Vp.X+X,Vp.Y+Y,Vp.X+X+W-1,Vp.Y+Y+H-1,swFrame&BoxStyle);
   if (Cap)
    {
      x = xJust(x,Vp.X+X,W,strlen(Cap->Txt));
      //TxtAttr = cs->Txt;
      //xPrintf(x,Vp.Y+Y,Cap->Txt);
      //TxtAttr = cs->TxtHi;
      //xPrintf(x+Cap->Hot,Y,"%c",Cap->Txt[Cap->Hot]);
      Cap->Parse(x+Cap->Hot,Vp.Y+Y,cs->Txt,cs->TxtHi);
    }
   Vp.Set(Vp.X+X,Vp.Y+Y,W,H);
   return true;
 }
void Frame::SetCaption(char *Src)
 {
   Cap    = new Caption(Src);
   HotKey = StrToKey(Cap->ShortCut);
 }

// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>                 Tag Sheet Module Source                 <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

TagSheet::TagSheet()
 {
   SetEventID(EventTagSheet);
   ToolID = 0x09;
   Hndl   = (Despatch*)NULL;
 }
TagSheet::~TagSheet()
 {
   if (Tgs != (Caption*)NULL)
       delete Tgs;
   if (Hndl != (Despatch*)NULL)
       delete Hndl;
 }

bool TagSheet::Show()
 {
   TxtAttr = cs->Txt;
   FillChr(X,Y,W,H,Blank);
   TxtAttr = cs->Box;
   DrawBox(X+1,Y,X+W-1,Y+H,ToolID&BoxStyle);
   return true;
 }
bool TagSheet::Refresh()
 {
   TxtAttr = cs->Txt;
   FillChr(X,Y,W,H,Blank);
   TxtAttr = cs->Box;
   DrawBox(X+1,Y,X+W-1,Y+H,ToolID&BoxStyle);
   return true;
 }
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>                    Tag Module Source                    <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>


Tag::Tag()
 {
   SetEventID(EventTag);
   Hndl      = (Despatch*)NULL;
   Tgs       = (TagSheet*)NULL;
   TgsIdx    = 0;
   AllocSize = 0;
   TgsCount   = 0;
 }
Tag::~Tag()
 {
   if (Hndl != (Despatch*)NULL)
       delete Hndl;
   if (Tgs != (TagSheet*)NULL)
       delete Tgs;
 }
void Tag::SetTagCount(byte Count)
 {
   if (AllocSize == 0)
    {
      AllocSize = Count;
      Tgs = new TagSheet[AllocSize];
    }
 }
void Tag::AddTag(char *Txt,byte EvtCount)
 {
   if (TgsCount < AllocSize)
    {
      Tgs[TgsCount].Tgs  = new Caption(Txt);
      Tgs[TgsCount].Hndl = new Despatch(&Tgs[TgsCount],EvtCount);
      TgsCount++;
    }
 }
byte Tag::AddEvent(byte Idx,Event *Evt)
 {
   if (Idx < TgsCount)
     return Tgs[Idx].Hndl->AddEvent(Evt);
   return 1;
 }
bool Tag::Show()
 {
  return true;
 }
bool Tag::Refresh()
 {
  return true;
 }
bool Tag::KeyDown(word Key)
 {
  bool rvHndl = true;
  if (Key==RtArr)
     ++TgsIdx %= TgsCount;
  else if (Key==LtArr)
    TgsIdx = (TgsIdx+TgsCount+1)%TgsCount;
  else
     rvHndl = false;
  if (rvHndl)
     Show();
  return rvHndl;
 }

// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>                   Menu Module Source                    <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

byte Menu::Search(word ID,Pad *Q)
 {
  byte found=0;
  int i;
  if (swMenu&FullMenu)
   {
     for (i=0;i<MaxPads && P[i].PadID != ID;i++);
      if (P[i].PadID==ID)
	{
	  found = 1;
	  Q     = &P[i];
	}
       else
	{
	 for (i=0;i<MaxPads && !found;i++)
	   if (P[i].SubMenu)
	     found  = P[i].SubMenu->Search(ID,Q);
	}
   }
  return found;
 }

byte Menu::ScrollUp(byte *idx,byte n)
 {
  for (;n>0;n--)
   do
    *idx = (*idx+MaxPads-1)%MaxPads;
   while (P[*idx].swItem&HiddenPad);
  return n;
 }
byte Menu::ScrollDown(byte *idx,byte n)
 {
  for (;n>0;n--)
   do
    ++(*idx)%=MaxPads;
   while (P[*idx].swItem&HiddenPad);
  return n;
 }
void Menu::ScrollPadPrv()
 {
  int n=0;
  P[Hot].swItem |= RefreshPad;
  do
   {
    n++;
    Hot=(Hot+MaxPads-1)%MaxPads;
   }
  while (!(P[Hot].swItem&ActivePad));
  if (visF > 0 || visL < MaxPads-1)
   {
     if (Hot > visL)
      {
       visL = Hot;
       ScrollDown(&visF,n);
      }
     else if (Hot < visF)
      {
       visF = Hot;
       ScrollUp(&visL,n);
      }
     swMenu ^= UpdateScr;
   }
  P[Hot].swItem |= RefreshPad;
 }
void Menu::ScrollPadNxt()
 {
  int n=0;
  P[Hot].swItem |= RefreshPad;
  do
   {
    n++;
    ++Hot%=MaxPads;
   }
  while (!(P[Hot].swItem&ActivePad));
  if (visF > 0 || visL < MaxPads-1)
   {
     if (Hot > visL)
      {
       visL = Hot;
       ScrollDown(&visF,n);
      }
     else if (Hot < visF)
      {
       visF = Hot;
       ScrollUp(&visL,n);
      }
     swMenu ^= UpdateScr;
   }
  P[Hot].swItem |= RefreshPad;
 }
byte Menu::NextPad(byte XorY,byte i)
 {
  if (!(P[i].swItem&HiddenPad))
   {
    if (swMenu&MenuVt)
     XorY++;
    else
     {
      if (P[i].swItem&MenuBreak)
       {
	byte w=0;
	byte j,R=(swMenu&Border) ? X+W-3:X+W-1;
	for (j=i+1;j <= visL && w+XorY < R;j++)
	if (!(P[j].swItem&HiddenPad))
	   w += 1+Spc+Spc+strlen(P[j].Cap->Txt);
	if (w+XorY > R)
	   w -= 1+Spc+Spc+strlen(P[j].Cap->Txt);
	XorY = R-w+1;
       }
      else
	XorY+= Spc+Spc+1+strlen(P[i].Cap->Txt);
     }
   }
  return(XorY);
 }

void Menu::DrawPad(byte xL,byte y,byte xR,Pad *Q,byte Txt,byte Hot)
 {
   byte x = xL;
   xL -= Spc;
   if (!(Q->swItem&NoShow) && (Q->swItem&RefreshPad))
    {
      TxtAttr = Txt;
      FillChr(xL,y,xR-xL+1,1,Blank);
      Q->Cap->Parse(x,y,Txt,Hot);
      if (swMenu&MenuVt)
       {
	xR -= Spc-1;
	if (Q->SubMenu != (Menu*)NULL)
	 {
	  xPrintf(xR-1,y,"%c",RtTriAngl);
	  xR -= 2;
	 }
	xPrintf(xR-strlen(Q->Cap->ShortCut),y,Q->Cap->ShortCut);
	TxtAttr = Txt;
	xL++;
	if (Q->swItem&RadioPad)
	 {
	  xPrintf(xL  ,y,"( )");
	  xPrintf(xL+1,y,"%c",(Q->swItem&PadState)? Sphere:Blank);
	 }
	if (Q->swItem&CheckPad)
	 {
	  xPrintf(xL  ,y,"[ ]");
	  xPrintf(xL+1,y,"%c",(Q->swItem&PadState)? Tick:Blank);
	 }
       }
    }
 }
void Menu::DrawMenu()
 {
  byte x,y,R,B;
  byte Flag=0x00;
  byte i;
  HideMouseCursor();
  y   = Y;
  x   = X+1+Spc;
  R   = X+W-3;
  B   = Y+H-1;

  if (swMenu&UpdateScr)
   {
    TxtAttr = cs->Txt;
    FillChr(X,Y,W,H,Blank);
    TxtAttr = cs->Box;
    if (swMenu&Border)
     {
      DrawBox(x-Spc,Y,R+1,B,(swMenu&MnuBoxStyle)>>MnuBoxShft);
      if (swMenu&Shadow)
	BoxShadow(X,Y,R+2,B);
     }
    if (swMenu&MenuVt)
     {
      if (visF >0 || visL < MaxPads-1)
       {
	xPrintf(R-3-(Spc/2),Y,"[%c]",uArrow);
	xPrintf(R-3-(Spc/2),B,"[%c]",dArrow);
       }
     }
    for (i=visF;i<=visL;i++)
       P[i].swItem |= (P[i].swItem&HiddenPad) ? 0:RefreshPad;
    swMenu ^= UpdateScr;
   }
  if (swMenu&Border)
   {
     x += (swMenu&MenuVt) ? 1:2;
     y++;
   }
  if (!(swMenu&MenuVt))
    R = NextPad(x,0)-2;

  for (i=visF;i<=visL;i++)
   {
    if (P[i].swItem&MenuBreak)
     {
       if ((swMenu&MenuVt) && (P[i].swItem&RefreshPad))
	{
	  TxtAttr = cs->Box;
	  DrawLineHz(x-Spc-1,y,R+1,((swMenu&MnuBoxStyle)>>MnuBoxShft)&0x01);
	}
       Flag = 0x10;
     }
    else if (i == Hot)
     {
       DrawPad(x,y,R,&P[i],cs->Xec,cs->XecHi);
       if (P[i].SubMenu != (Menu*)NULL)
	 if (Flag&0x10)
	   P[i].SubMenu->SetOrigin((swMenu&MenuVt) ? X+Spc+5:R-P[i].SubMenu->W,y+1);
	 else
	   P[i].SubMenu->SetOrigin((swMenu&MenuVt) ? X+Spc+5:x,y+1);
       //Status(P[i].Msg);
     }
    else if (P[i].swItem&ActivePad)
      DrawPad(x,y,R,&P[i],cs->Txt,cs->TxtHi);
    else
      DrawPad(x,y,R,&P[i],cs->Lck,cs->Lck);


    if (!(P[i].swItem&HiddenPad))
     {
      P[i].swItem ^= P[i].swItem&RefreshPad;
      if (swMenu&MenuVt)
       y = NextPad(y,i);
      else
       {
	 x = NextPad(x,i);
	 R = NextPad(x,i+1)-2;
       }
     }
   }
  ShowMouseCursor();
 }

void Menu::Open()
 {
   HideMouseCursor();
   Ptr->MnuX.Capture(Ptr->X,Ptr->Y,Ptr->W,Ptr->H);
   Ptr->swMenu |= UpdateScr;
   SetDrawPg(RufPg);
   Ptr->DrawMenu();
   SetDrawPg(ActPg);

   Ptr->MnuX.ShowEffect(Ptr->X,Ptr->Y,Ptr->W,Ptr->H);
   ShowMouseCursor();
 }
byte Menu::ShutMenu(byte Flag)
 {
   if (Ptr != this)
    {
      Ptr->MnuX.UndoEffect();
      //Ptr->MnuX.Restore();
      Ptr->MnuX.Delete();
      Ptr = Ptr->Ptr;        // Pop
    }
   else
    {
      Ptr->swMenu ^= MenuOpen;
      Ptr->P[Ptr->Hot].swItem |= RefreshPad;
      Ptr->Hot = Ptr->MaxPads;
      Ptr->DrawMenu();
    }
   Flag &= MaskClose;
   return Flag;
 }

// Public members of Class Menu

Menu::Menu()
 {
   SetEventID(EventMenu);
   X=Y=W=H=N=0;
   cs = &CoolBlue;
   Spc     = 1;
   Ptr     = this;
   P       = (Pad*)NULL;
   MaxPads = 0;
 }
Menu::Menu(word MenuType,byte MaxItem)
 {
   SetEventID(EventMenu);
   X=Y=W=H=N=Hot=0;
   swMenu     = MenuType&MaskMenuFlags;
   cs         = &CoolBlue;
   Ptr        = this;
   TxtAttr    = 0x0F;
   MaxPads    = MaxItem;
   visF       = 0;
   visL       = MaxPads-1;
   P          = new Pad[MaxPads];
   H          = (swMenu&MenuVt) ? MaxPads+2:(swMenu&Border) ? 3:1;
   Spc        = (swMenu&MenuVt) ? 2:0;
   W          = (swMenu&MenuVt) ? 0:Screen.Width;
   MnuX.SetEffect((MenuType&ShowEff)>>EffShft);
 }
Menu::~Menu()
 {
   Ptr = (Menu*)NULL;
   for (int i=0;i<MaxPads;i++)
    {
      if (P[i].SubMenu != (Menu*)NULL)
       if (P[i].SubMenu->swMenu&InternalAlloc)
	  delete P[i].SubMenu;
       else
	  P[i].SubMenu->Ptr = (Menu*)NULL;
      delete P[i].Cap->Txt;
      P[i].SubMenu  = (Menu*)NULL;
      P[i].PadApp   = NoApp;
      //P[i].ShortCut = (char*)NULL;
    }
   delete P;
 }

byte Menu::AddPad(char *Txt, word PadType)
 {
  byte   PadErr=0;
  Pad   *Q;
  while (Ptr->MaxPads == Ptr->N && Ptr != this)
   {
     //width,height,location setup -- optional
     Ptr->swMenu ^= FullMenu;
     Ptr          = Ptr->Ptr;    // as good as pop
   }
  PadErr       = (Ptr->MaxPads == Ptr->N);
  Ptr->swMenu ^= (PadErr) ? FullMenu:0x0000;
  if (!PadErr)
   {
    Q           = &Ptr->P[Ptr->N];
    Q->swItem   = PadType&MaskPadFlags;
    Q->PadID    = (Q->swItem&MenuBreak) ? 0xFFFF:MenuID++;
    Q->Cap      = new Caption(Txt);
    Q->Msg      = new char[1];
    Q->PadApp   = NoApp;
    Q->SubMenu  = (Menu*)NULL;
    Q->Msg[0]   = '\0';
    if (Ptr->swMenu&MenuVt) // Vertical Menu coord specs
     {
      if (Q->swItem&SetSpc)
       {
	Ptr->W  += (Spc < 5) ? (5-Spc):0;
	Ptr->Spc = max(5,Ptr->Spc);
       }
      int Wd  = strlen(Q->Cap->Txt)+strlen(Q->Cap->ShortCut);
      Wd     += (Wd > strlen(Q->Cap->Txt)) ? 2:0;
      Ptr->W = max(Ptr->W,Wd+2*Ptr->Spc+4);
      Ptr->X = (Ptr->X+Ptr->W > GetMaxX()-1) ? GetMaxX()-2-Ptr->W:Ptr->X;
     }
    Ptr->N++;
   }
   return PadErr;
 }
byte Menu::AddPad(char *Txt, word PadType,App PadApp)
 {
   byte PadErr = AddPad(Txt,PadType);
   if (!PadErr)
      Ptr->P[Ptr->N-1].PadApp = PadApp;
   return PadErr;
 }
byte Menu::AddPad(char *Txt, word PadType,Menu *Sub)
 {
   byte PadErr = AddPad(Txt,PadType);
   if (!PadErr)
      Ptr->P[Ptr->N-1].SubMenu = Sub;
   return PadErr;
 }
byte Menu::AddPad(char *Txt,word PadType,char *Hlp)
 {
   byte PadErr = AddPad(Txt,PadType);
   Pad  *Q;
   if (!PadErr)
    {
      Q = &Ptr->P[Ptr->N-1];
      delete Q->Msg;
      Q->Msg = new char[strlen(Hlp)+1];
      strcpy(Q->Msg,Hlp);
    }
   return PadErr;
 }
byte Menu::AddPad(char *Txt,word PadType,App PadApp,char *Hlp)
 {
   byte PadErr = AddPad(Txt,PadType);
   Pad  *Q;
   if (!PadErr)
    {
      Q = &Ptr->P[Ptr->N-1];
      delete Q->Msg;
      Q->Msg    = new char[strlen(Hlp)+1];
      Q->PadApp = PadApp;
      strcpy(Q->Msg,Hlp);
    }
   return PadErr;
 }
byte Menu::AddMenu(word MenuType,byte MaxItem)
 {
   byte err=0;
   Pad  *Q;
   if (Ptr->N > 0 && Ptr->P[Ptr->N-1].SubMenu == (Menu*)NULL)
    {
     Q = &Ptr->P[Ptr->N-1];
     Q->SubMenu             = new Menu(MenuType,MaxItem);
     Q->SubMenu->swMenu    ^= InternalAlloc;
     Q->SubMenu->Ptr        = Ptr;   // pop pointer;
     Q->SubMenu->cs = cs;
     if (Ptr->swMenu&MenuVt)
      {
       int Wd  = strlen(Q->Cap->Txt)+strlen(Q->Cap->ShortCut);
       Wd     += (Wd > strlen(Q->Cap->Txt)) ? 10:7;
       Wd     += 2*Ptr->Spc;
       Ptr->W  = max(Ptr->W,Wd);
      }
     Ptr = Q->SubMenu;  // as good as push
    }
   else err = 1;
   return err;
 }
byte Menu::AddMenu(Menu *M)
 {
   byte err=0;
   Pad  *Q; // no coordinate setup will be assigned by user
   if (Ptr->N > 0 && Ptr->P[Ptr->N-1].SubMenu == (Menu*)NULL)
    {
     Q = &Ptr->P[Ptr->N-1];
     Q->SubMenu          = M;
     Q->SubMenu->Ptr     = Ptr;   // pop pointer;
     if (!(Q->SubMenu->swMenu&Colorised))
       Q->SubMenu->cs = cs;
     Ptr = Q->SubMenu;  // as good as push
    }
   else err = 1;
   return err;
 }
byte Menu::AddHelp(word MenuID,char *Hlp)
 {
   Pad *Q;
   byte rvFlag=Search(MenuID,Q);
   if (rvFlag)
    {
     delete Q->Msg;
     Q->Msg    = new char[strlen(Hlp)+1];
    }
   return rvFlag;
 }


void Menu::EndMenu()
 {
   while (Ptr->MaxPads == Ptr->N && Ptr != this)
    {
     Ptr->swMenu ^= FullMenu;
     Ptr          = Ptr->Ptr;    // as good as pop
    }
   if (swMenu&MainAppMenu)
     swMenu ^= ((swMenu&MenuVt)) ? MainAppMenu:0;
 }
void Menu::SetOrigin(byte x,byte y)
 {
   X = x;
   Y = y;
   X = (X+W > GetMaxX())  ? GetMaxX()-W-Spc-5:X;
 }
byte Menu::SetState(word MenuID,bool State)
 {
   Pad *Q;
   byte rvFlag=Search(MenuID,Q);
   if (rvFlag)
    {
      if (State)
	Q->swItem |= PadState;
      else
	Q->swItem &= MaskPadState;
    }
   return rvFlag;
 }
byte Menu::GetState(word MenuID,bool& State)
 {
   Pad *Q;
   byte rvFlag=Search(MenuID,Q);
   if (rvFlag)
    {
      State = (bool)(Q->swItem&PadState);
    }
   return rvFlag;
 }
byte Menu::Activity(word MenuID,bool OnOff)
 {
   Pad *Q;
   byte rvFlag=Search(MenuID,Q);
   if (rvFlag)
    {
      if (OnOff)
	Q->swItem |= ActivePad;
      else
	Q->swItem &= MaskActivity;
    }
   return rvFlag;
 }
byte Menu::Visibility(word MenuID,bool OnOff)
 {
   Pad *Q;
   byte rvFlag=Search(MenuID,Q);
   if (rvFlag)
    {
      if (OnOff)
	Q->swItem &= MaskVisibility;
      else
	Q->swItem |= HiddenPad;
    }
   return rvFlag;
 }


bool Menu::KeyDown(word Key)
 {
  bool rvHndl = false;
  byte Flag = 0x00;
  byte HotKey;
  byte p=Ptr->Hot;
  byte n=0;

  MenuID = 0xFFFF;
  if (!(swMenu&MenuOpen))
   {
     if (Ptr==this && (swMenu&MainAppMenu))
      {
       for (n=0;n<MaxPads && !rvHndl;n++)
         rvHndl = (bool)((P[n].swItem&ActivePad) && Key == P[n].Cap->HotKey);
       if (rvHndl)
        {
         swMenu|=MenuOpen;
         Hot = n-1;
	 Open();
         XecPadApp(XecPad);
        }
       else rvHndl = false;
      }
    // else Scan for app xec no opening of submenu
   }
  else
   {
    Menu *Prv = Ptr->Ptr;
    byte pp = Prv->Hot;
    rvHndl  = true;
    switch(Key)
     {
      case LtArr: if (!(Ptr->swMenu&MenuVt))
		     Ptr->ScrollPadPrv();
		  else if (Ptr != this && !(Prv->swMenu&MenuVt))
		   {
		     Prv->ScrollPadPrv();
		     Flag ^= (Prv->P[Prv->Hot].SubMenu) ? XecAndClose:Close;
		   }
		  else
		     Flag ^= (Ptr != this) ? Close:0;
		  break;
      case RtArr: if (!(Ptr->swMenu&MenuVt))
		     Ptr->ScrollPadNxt();
		  else if (Ptr != this && !(Prv->swMenu&MenuVt))
		   {
		     Prv->ScrollPadNxt();
		     Flag ^= (Prv->P[Prv->Hot].SubMenu) ? XecAndClose:Close;
		   }
		  else
		     Flag ^= XecPad;
		  break;
      case UpArr: if (Ptr->swMenu&MenuVt)
		     Ptr->ScrollPadPrv();
		  else if ((Prv != this) && (Prv->swMenu&MenuVt))
		   {
		     Prv->ScrollPadPrv();
		     Flag ^= (Prv->P[Prv->Hot].SubMenu) ? XecAndClose:Close;
		   }
		  else
		     Flag ^= (Ptr != this) ? Close:0;
		  break;
      case DnArr: if (Ptr->swMenu&MenuVt)
		     Ptr->ScrollPadNxt();
		  else if ((Ptr != this) && (Prv->swMenu&MenuVt))
		   {
		     Prv->ScrollPadNxt();
		     Flag ^= (Prv->P[Prv->Hot].SubMenu) ? XecAndClose:Close;
		   }
		  else
		     Flag ^= XecPad;
		  break;
      case EscKy: Flag = Close;  break;
      case RetKy: Flag = XecPad; break;
      case SpcKy: Flag = XecPad; break;
      default   : Key = UpCase(Key);
                  for (n=visF;n <= visL && !(Flag&XecPad);n++)
		   {
		    if (Ptr->P[n].swItem&ActivePad)
		     {
		      HotKey = UpCase(Ptr->P[n].Cap->Txt[Ptr->P[n].Hot]);
		      Flag   = (Key == HotKey)?  XecPad:0;
		     }
		   }
		  if (Flag&XecPad)
                     Ptr->Hot = n-1;
		  break;
     }
    if (Prv->Hot != pp)
     {
       Prv->P[Prv->Hot].swItem |= RefreshPad;
       Prv->P[pp].swItem       |= RefreshPad;
       Prv->DrawMenu();
     }
    if (Ptr->Hot != p)
     {
       Ptr->P[Ptr->Hot].swItem |= RefreshPad;
       Ptr->P[p].swItem        |= RefreshPad;
       Ptr->DrawMenu();
     }
    XecPadApp(Flag);

   }
   return rvHndl;
 }
bool Menu::MouseMove(int mx,int my)
 {
  bool rvEvtProcessed=false;
  byte p = Ptr->visF;
  byte r = Ptr->X+Ptr->W-1;
  byte b = Ptr->Y+Ptr->H-1;

  MenuID = 0xFFFF;
  if (!(mx < Ptr->X || mx > r || my < Ptr->Y || my > b))
   {
    if (Ptr->swMenu&MenuVt)
     {
       byte y=Ptr->Y+1;
       while (p != Ptr->visL && y < my)
         y=Ptr->NextPad(y,p++);
       rvEvtProcessed = (bool)(y==my && Ptr->P[--p].swItem&ActivePad);

     }
    else
     {
      byte x=Ptr->NextPad(Ptr->X+1,p);
      while (p != Ptr->visL && x-1 < mx)
	x = Ptr->NextPad(x,++p);
      rvEvtProcessed = (bool)(x-1 > mx && Ptr->X < mx && (Ptr->P[p].swItem&ActivePad));
     }
    if (rvEvtProcessed)
    {
     Ptr->P[Hot].swItem |= RefreshPad;
     Ptr->P[p].swItem   |= RefreshPad;
     Ptr->DrawMenu();
     FlushMouse();
    }
   }
  return rvEvtProcessed;
 }

bool Menu::MouseLeftClick(int mx,int my)
 {
  bool rvEvtProcessed=false;
  byte Flag = 0x00;
  byte p = Ptr->visF;
  byte r = Ptr->X+Ptr->W-1;
  byte b = Ptr->Y+Ptr->H-1;

  MenuID = 0xFFFF;
  if (!(mx < Ptr->X || mx > r || my < Ptr->Y || my > b))
   {
    if (Ptr->swMenu&MenuVt)
     {
       if (Ptr->visF>0 || Ptr->visL<Ptr->MaxPads)
         if (mx == r-Spc)
          if (my==Ptr->Y)
           {
	     Ptr->ScrollPadPrv();
             Flag = 0x01;
           }
          else if (my==b)
           {
             Ptr->ScrollPadPrv();
             Flag = 0x01;
           }
       if (!rvEvtProcessed)
        {
         byte y=Ptr->Y+1;
         while (p != Ptr->visL && y < my)
           y=Ptr->NextPad(y,p++);
         Flag = (y==my && Ptr->P[--p].swItem&ActivePad) ? 0x11:0;
        }
     }
    else
     {
      byte x=Ptr->NextPad(Ptr->X+1,p);
      while (p != Ptr->visL && x-1 < mx)
	x = Ptr->NextPad(x,++p);
      if (Ptr->P[p].swItem&ActivePad)
      Flag = (x-1 > mx && Ptr->X < mx) ? 0x11:0;

     }
    if (Flag)
    {
     rvEvtProcessed = true;
     Ptr->P[Hot].swItem |= RefreshPad;
     Ptr->P[p].swItem   |= RefreshPad;
     Ptr->DrawMenu();
     FlushMouse();
     if (Flag&0x10)
       XecPadApp(XecPad);
    }
   }
  return rvEvtProcessed;
 }
void Menu::XecPadApp(byte Flag)
 {
//  Scheme SavStat=StatusBar;
//  StatusBar = *cs;
  byte x,y,r,b;

  if (Flag&Close)
     Flag = ShutMenu(Flag);
  Pad *Q=&Ptr->P[Ptr->Hot];
  if (Flag&XecPad && !(Flag&CloseAll))
   {
    if (Q->SubMenu != (Menu*)NULL)
     {
       Ptr=Q->SubMenu; // Push
       Open();
       Flag &= MaskClose;
     }
    else if (Q->PadApp != (App)NULL)
     {
       Q->PadApp();
       Flag ^= XecPad;
       MenuID = Q->PadID;
     }
    else
     {
       MenuID = Q->PadID;
       if (Q->swItem&CheckPad)
	   Q->swItem ^= PadState;
       if (Q->swItem&RadioPad && !(Q->swItem&PadState))
        {
	  int i;
	  for (i=Ptr->Hot-1;i >= Ptr->visF && Ptr->P[i].swItem&RadioPad;i--);
	  for (i++;i <= Ptr->visL && Ptr->P[i].swItem&RadioPad;i++)
	     Ptr->P[i].swItem &= MaskPadState;
	  Q->swItem ^= PadState;
	}
       Flag = Close;
     }
   }
  while(Flag&CloseMenu)
   {
    Flag |= Close;
    if (Ptr==this)
      Flag = 0x00;
    else
      Flag = ShutMenu(Flag);
   }

 // StatusBar = SavStat;
 }

word Menu::GetMenuID()
 {
   return MenuID;
 }
bool Menu::Show()
 {
   Hot=0xFF;
   swMenu |= UpdateScr;
   if (!(swMenu&MenuOpen))
       DrawMenu(); //Open();
   return true;
 }


Form::Form()
 {
  SetEventID(EventForm);
  X         = 0;
  Y         = 1;
  W         = GetMaxX();
  H         = GetMaxY()-1;
  WallPaper = Blank;
  cs        = &Classic;
  swForm    = 0xffff;
 }
Form::~Form()
 {
  WallPaper = Blank;
 }


void Form::SetEventLimit(byte Lim)
 {
  if (Hndl == (Despatch*)NULL)
      Hndl = new Despatch(this,Lim);
 }
byte Form::AddEvent(Event *Evt)
 {
   return (Hndl != (Despatch*)NULL) ? Hndl->AddEvent(Evt):1;
 }
byte Form::AddMenu(Event  *Evt)
 {
   return (Hndl != (Despatch*)NULL) ? Hndl->AddMenu(Evt):1;
 }
void Form::SetCaption(char *DAN)
 {
  DlgAppName = new char [strlen(DAN)+1];
  strcpy(DlgAppName,DAN);
  minW  = strlen(DlgAppName)+2;
  minW += (swForm&ShowClose)  ? 3:0;
  minW += (swForm&ShowHelp)   ? 3:0;
  minW += (swForm&ShowMinMax) ? 3:0;
  minW += (swForm&ShowSpecs)  ? 3:0;
 }
void Form::SetOrigin(byte x,byte y)
 {
   X = nrmX = x;
   Y = nrmY = y;
 }
void Form::SetSize(byte w,byte h)
 {
   W = nrmW = w;
   H = nrmH = h;
 }

void Form::Draw()
 {
  byte x,y;
  y = Y;
  if (swForm&DrawHeader)
   {
    SetTexAttr(cs->Xec);
    FillChr(X,Y,W,1,Blank);
    y = Y+1;
   }
  TxtAttr=cs->Txt;
  if (swForm&FillDialog && Y != Y+H)
   FillChr(X,y,W,H-(y-Y),WallPaper);
  if (swForm&DrawBorder && Y != Y+H)
   DrawBox(X+1,y,X+W-2,Y+H-1,((swForm&BorderStyle)>>StyleShft));

  if (swForm&ShowSpecs)
   {
    TxtAttr = (swForm&DrawHeader) ? cs->Xec:cs->Box;
    xPrintf(X+1,Y,"[ ]");
    TxtAttr = (swForm&ActiveSpecs) ? cs->XecHi:cs->Lck;
    xPrintf(X+2,Y,"%c",SqBox);
   }
  x = X+W-1;
  if (swForm&ShowClose)
   {
    x-=3;
    TxtAttr = (swForm&DrawHeader) ? cs->Xec:cs->Box;
    xPrintf(x,Y,"[ ]");
    TxtAttr = (swForm&ActiveClose) ? cs->XecHi:cs->Lck;
    xPrintf(x+1,Y,"%c",KillBtn);
   }
  if (swForm&ShowHelp)
   {
    x-=3;
    TxtAttr = (swForm&DrawHeader) ? cs->Xec:cs->Box;
    xPrintf(x,Y,"[ ]");
    TxtAttr = (swForm&ActiveHelp) ? cs->XecHi:cs->Lck;
    xPrintf(x+1,Y,"?");
   }
  if (swForm&ShowMinMax)
   {
    x-=3;
    TxtAttr = (swForm&DrawHeader) ? cs->Xec:cs->Box;
    xPrintf(x,Y,"[ ]");
    TxtAttr = (swForm&ActiveMinMax) ? cs->XecHi:cs->Lck;
    if (X==0 && X+W == GetMaxX() && Y ==1 && Y+H == GetMaxY()-1)
     xPrintf(x+1,Y,"%c",dArrow);
    else if (Y == Y+H)
     xPrintf(x+1,Y,"%c",uArrow);
    else
     xPrintf(x+1,Y,"%c",DblArrow);
   }
  if (swForm&DrawShadow)
   if (Y != Y+H && Y+H-1 != GetMaxY() && X+W-1 != GetMaxX())
     BoxShadow(X,Y,X+W-1,Y+H-1);
   if (swForm&HzScrollBar && Y+6 < Y+H && X+20 <X+W)
    {
     SetTexAttr(cs->Box);
     FillChr(X+2,Y+H-1,W-6,1,WideDot);
     xPrintf(X+2,Y+H-1,"%c",LtTriAngl);
     xPrintf(X+W-4,Y+H-1,"%c",RtTriAngl);
    }
   if (swForm&VtScrollBar && Y+6 < Y+H && X+20 <X+W)
    {
     SetTexAttr(cs->Box);
     FillChr(X+W-2,y+1,1,H-4,WideDot);
     xPrintf(X+W-2,y+1,"%c",UpTriAngl);
     xPrintf(X+W-2,Y+H-2,"%c",DnTriAngl);
    }
   TxtAttr = (swForm&DrawHeader) ? cs->Xec:cs->Box;
   x = xJust(0,X+3,x-X-3,strlen(DlgAppName));
   xPrintf(x,Y,DlgAppName);
   Vp.Set(X,Y,W,H);
 }

void Form::FormMinimise()
 {
  W  = strlen(DlgAppName)+3;
  W += (swForm&ShowClose)  ? 3:0;
  W += (swForm&ShowHelp)   ? 3:0;
  W += (swForm&ShowMinMax) ? 3:0;
  W += (swForm&ShowSpecs)  ? 3:0;
  Y  = GetMaxY()-1;
  H  = 0;
  Show();
 }
void Form::FormMaximise()
 {
  X  = maxX;
  W  = maxW;
  Y  = maxY;
  H  = maxH;
  Show();
 }
bool Form::Show()
 {

   if (FrmX.swScr&NoAlloc)
     FrmX.Capture(X,Y,W,H);
   //FrmX.SetEffect(SlideRtUp|EffShadow);
   DrwPg=RufPg;
   Draw();
   Hndl->Show();
   DrwPg=ActPg;
   FrmX.ShowEffect(X,Y,W,H);
   return true;
 }
bool Form::Refresh()
 {
   X = nrmX;
   Y = nrmY;
   W = nrmW;
   H = nrmH;
   DrwPg=RufPg;
   Draw();
   DrwPg=ActPg;
   xPrintf(10,24,"hello");
   FrmX.Restore();
   GetKey();
   FrmX.Capture(X,Y,W+1,H+1);
   FrmX.Copy(RufPg,DrwPg,X,Y,W,H);
   if (swForm&DrawShadow)
   if (Y != Y+H && Y+H-1 != GetMaxY() && X+W-1 != GetMaxX())
     BoxShadow(X,Y,X+W-1,Y+H-1);

   return true;
 }
bool Form::KeyDown(word Key)
 {
   bool rvHndl=true;

   if (Key == Ctrl_F5)
      ToolID ^= FrmMoveSize;
   else if (ToolID&FrmMoveSize)
    {
     if (Key==LtArr)
        nrmX = (nrmX > 0) ? nrmX-1:nrmX;
     else if (Key==RtArr)
        nrmX = (nrmX+nrmW < GetMaxX()) ? nrmX+1:nrmX;
     else if (Key==UpArr)
        nrmY = (nrmY > 0) ? nrmY-1:nrmY;
     else if (Key==DnArr)
        nrmY = (nrmY+nrmH < GetMaxY()) ? nrmY+1:nrmY;
     else if (Key==Ctrl_LtArr)
        nrmW = (nrmW > minW) ? nrmW-1:nrmW;
     else if (Key==Ctrl_RtArr)
        nrmW = (nrmX+nrmW < GetMaxX()) ? nrmW+1:nrmW;
     else if (Key==Ctrl_UpArr)
        nrmH = (nrmH == 0) ? nrmH: (nrmH==3) ? 0:nrmH-1;
     else if (Key==Ctrl_DnArr)
        nrmH = (nrmY+nrmH < GetMaxY()) ? (nrmH==0) ? 3:nrmH+1:nrmH;
     else rvHndl = false;
     if (rvHndl)
      {
        //if (Hndl != (Despatch*)NULL)
        //  Hndl->Refresh();
        //else
          Refresh();
      }
    }
   else rvHndl = false;
   //xPrintf(10,23,"Handled %X %s ",Key, (rvHndl) ? "True":"False");
   return rvHndl;
 }





void SetUpColors()
 {
  Classic.Txt   = SetTxtCol(Brown,Black);
  Classic.TxtHi = SetTxtCol(Brown,LightCyan);
  Classic.Xec   = SetTxtCol(DarkGray,LightGreen);
  Classic.XecHi = SetTxtCol(DarkGray,LightMagenta);
  Classic.Lck   = SetTxtCol(Brown,LightRed);
  Classic.Box   = SetTxtCol(Brown,LightGray);
  CoolBlue.Txt   = SetTxtCol(Cyan,DarkGray);
  CoolBlue.TxtHi = SetTxtCol(Cyan,White);
  CoolBlue.Xec   = SetTxtCol(LightGray,Yellow);
  CoolBlue.XecHi = SetTxtCol(LightGray,Green);
  CoolBlue.Lck   = SetTxtCol(Cyan,LightGray);
  CoolBlue.Box   = SetTxtCol(Cyan,DarkGray);

  RedAlert.Txt   = SetTxtCol(Red,LightMagenta);
  RedAlert.TxtHi = SetTxtCol(Red,Magenta);
  RedAlert.Xec   = SetTxtCol(Green,LightBlue);
  RedAlert.XecHi = SetTxtCol(Green,Red);
  RedAlert.Lck   = SetTxtCol(Red,LightRed);
  RedAlert.Box   = SetTxtCol(Red,Yellow);

  SoftGreen.Txt   = SetTxtCol(LightGray,LightBlue);
  SoftGreen.TxtHi = SetTxtCol(LightGray,Cyan);
  SoftGreen.Xec   = SetTxtCol(Black,Cyan);
  SoftGreen.XecHi = SetTxtCol(Black,Yellow);
  SoftGreen.Lck   = SetTxtCol(LightGray,LightGreen);
  SoftGreen.Box   = SetTxtCol(LightGray,LightCyan);

  SoftGray.Txt   = SetTxtCol(LightGray,LightCyan);
  SoftGray.TxtHi = SetTxtCol(LightGray,Yellow);
  SoftGray.Xec   = SetTxtCol(DarkGray,LightMagenta);
  SoftGray.XecHi = SetTxtCol(DarkGray,LightGreen);
  SoftGray.Lck   = SetTxtCol(LightGray,Cyan);
  SoftGray.Box   = SetTxtCol(LightGray,Brown);

  DarkNight.Txt   = SetTxtCol(Black,Cyan);
  DarkNight.TxtHi = SetTxtCol(Black,Yellow);
  DarkNight.Xec   = SetTxtCol(LightMagenta,White);
  DarkNight.XecHi = SetTxtCol(LightMagenta,LightGreen);
  DarkNight.Lck   = SetTxtCol(Black,DarkGray);
  DarkNight.Box   = SetTxtCol(Black,White);
 }
/*main()
 {
   ModeSearch(Txt80x25x16x8);
//   FillChr(0,0,Screen.Width,Screen.Height,CloseDot);

   TglBlink(Off);
   Form D;
   TextBox T;
   T.SetOrigin(10,5);
   T.SetSize(20,1);
   T.AddColor(&SoftGray);

   D.SetOrigin(3,1);
   D.SetSize(40,10);
   D.SetCaption("Jerry Thomas");
   TxtAttr = 0x0f;
   FillChr(0,0,80,25,CloseDot);
   D.SetEventLimit(5);
   D.AddColor(&DarkNight);

//   D.AddEvent(&T);

   D.Show();


  // T.Show();
   word Key =0x00;
   //xPrintf(10,10,"Changing allocation with sbrk()");
   //xPrintf(10,11,"Before sbrk() call: %lu bytes free",
   //    (unsigned long) coreleft());
   //sbrk(4096*4);
   //xPrintf(10,12," After sbrk() call: %lu bytes free",
   //     (unsigned long) coreleft());
   xPrintf(20,22,"%d %d %d ",Screen.Width,Screen.Height,Screen.Delta);
   do
    {
      Key = GetKey();
      if (Key != EscKy)
         D.Hndl->KeyDown(Key);
    }
   while (Key != EscKy);
   ChrBox(0,0,79,24,Blank);
   GetKey();
   return(0);
 }*/
