#ifndef __CUIMENU_H
#define __CUIMENU_H

// Cui.Cpp Version 3.0
// Total Hours  11 Hrs
// <<>> <<>> <<>> <<>> <<>> <<>> <<-:->> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>>
// <<>>                                                                     <<>>
// <<>>              Character User Interface Tool                          <<>>
// <<>>                                                                     <<>>
// <<>>                 Menu Generator Class                                <<>>
// <<>>                                                                     <<>>
// <<>>   Features :                                                        <<>>
// <<>>                                                                     <<>>
// <<>>        Multiple Levels                                              <<>>
// <<>>        Vertical/Horizontal Menus                                    <<>>
// <<>>        Check / Radio Pads                                           <<>>
// <<>>        Menubreaks                                                   <<>>
// <<>>        Special Effects                                              <<>>
// <<>>        Direct Function Execution                                    <<>>
// <<>>        Hidden & Scrollable Menu Items                               <<>>
// <<>>        Menu Activation/Deactivation                                 <<>>
// <<>>        On Line Messages for menu items                              <<>>
// <<>>                                                                     <<>>
// <<>>                                                                     <<>>
// <<>> <<>> <<>> <<>> <<>> <<>> <<-:->> <<>> <<>> <<>> <<>> <<>> <<>> <<>> <<>>

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
#define RefreshPad     0x8000

#define MaskPadFlags   0x007F
#define MaskPadState   0xFFBF
#define MaskActivity   0xFFF7
#define MaskVisibility 0xFFFD

#define OptsResvd_P    0x7F80  // reserved bits

#define MenuHz         0x0000
#define MenuVt         0x0001
#define Effects        0x0006
#define EffectsDir     0x0018
#define Shadow         0x0040
#define Border         0x0080
#define BoxStyle       0x0300

#define ReservedM      0x0400 // reserved bits

#define MenuOpen       0x0800
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
#define HSVSBox          0x0080
#define HDVSBox          0x0180
#define HSVDBox          0x0280
#define HDVDBox          0x0380

#define SlideRtMenuHz    0x0002
#define SlideLtMenuHz    0x0004
#define SlideDnMenuHz    0x0006
#define SlideUpMenuHz    0x0008
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
   Caption *Cap;        // Caption
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







