#ifndef __MENU_H
#define __MENU_H

// Cui.Cpp Version 3.0
// Total Hours  11 Hrs
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>              Character User Interface Tool              <<>>
// <<>>                                                         <<>>
// <<>>                 Menu Generator Class                    <<>>
// <<>>                  Version 3.0                            <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

#include <Events.H>
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

#define MainAppMenu    0x0400

#define MenuOpen       0x0800
#define Colorised      0x1000
#define FullMenu       0x2000
#define UpdateScr      0x4000
#define InternalAlloc  0x8000
#define MaskMenuFlags  0x07FF

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
   word   HotKey;
   App    PadApp;      // App to be taken on selection
   char   *Msg;        // Message string for guidance
   Menu   *SubMenu;    // Ptr to Sub-Menu
 };

class Menu : public Event
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
     Image   *Sav;
     static word MenuID;

   private :

     byte Search(word ID,Pad *Q);

     byte ScrollUp(byte *idx,byte n);
     byte ScrollDown(byte *idx,byte n);
     void ScrollPadPrv();
     void ScrollPadNxt();
     byte NextPad(byte XorY,byte i);

     void DrawPad(byte xL,byte y,byte xR,Pad *Q,byte Txt,byte Hot);
     void DrawMenu();

     byte MenuCtrl();

     byte ShutMenu(byte Flag);
     void Open();
     void XecPadApp(byte Flag);

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

     byte addHelp(word MenuID,char *Hlp);

     void addColor(Scheme *Sch);
     void addColor(byte Txt,byte TxtHi,byte Xec,byte XecHi,byte Lck,byte Box);

     void endMenu();

     void SetOrigin(int X,int Y);

     byte GetState(word ID,bool& State);
     byte SetState(word ID,bool  State);

     byte Activity(word ID,bool OnOff);
     byte Visibility(word ID,bool OnOff);



     bool KeyDown(word Key);
     bool MouseMove(int mx,int my);
     bool MouseLeftClick(int mx,int my);

     //bool Refresh();
     //bool Show();
     word XecMenu();
     word GetMenuID();
 };

extern Scheme Classic,CoolBlue,SoftGreen,RedAlert,StatusBar;
#endif

word   Menu::MenuID=0x100;
Scheme Classic,CoolBlue,SoftGreen,RedAlert,StatusBar;

byte LabelAllocSize(char *txt)
 {
  int siz=0;
  while (*txt)
   {
    for(;*txt && *txt != '&' && *txt != '\t';txt++,siz++);
    switch (*txt)
     {
      case '&'  : siz--;
		  break;
      case '\t' : for(txt++,siz++;*txt && txt;txt++,siz++);
		   if (*txt == '\t')
		       *txt = 32;
		  break;
     }
    if (*txt)
     {
      txt++;
      siz++;
     }
   }
  *txt = '\0';
  return ++siz;
 }

char *SetPrompt(char *Src, char *Dst, byte& Pos)
 {
  int  i=Pos=0;
  char *Addr=(char*)NULL;
  while(*Src)
   {
    for(;*Src && *Src != '&' && *Src != '\t'; Src++,i++)
	 Dst[i] = *Src;
    switch (*Src)
     {
      case '&'  : Dst[i] = *++Src;
		  if (*Src != '&')
		    Pos = i;
		  break;
      case '\t' : Dst[i]   = '\0';
		  Addr = (char*)(Dst+i+1);
		  break;
     }
    if (*Src)
     {
      Src++;
      i++;
     }
   }
   Dst[i] = '\0';
   return (Addr == (char*)NULL) ? (char*)(Dst+i):Addr;
 }

int Status(char *fmt,...)
 {
  char Hlp[255];
  va_list argptr;
  byte len;
  int  cnt;
  byte OffSet = 0;
  byte x = 1;

  va_start(argptr, fmt);
  cnt = vsprintf(Hlp, fmt, argptr);
  va_end(argptr);
  len = strlen(Hlp);

  HideMouseCursor();
  TxtAttr = StatusBar.Txt;
  FillChr(0,GetMaxY(),GetMaxX(),GetMaxY(),Blank);

  for (OffSet=0;OffSet < len;OffSet++)
   {
    switch(Hlp[OffSet])
     {
      case '/' :switch(Hlp[OffSet+1])
		{
		 case '+':TxtAttr=StatusBar.TxtHi;
			  OffSet++;
			  break;
		 case '-':TxtAttr=StatusBar.Txt;
			  OffSet++;
			  break;
		 case '/':SetVidAt(DrwPg,x++,GetMaxY(),Hlp[OffSet],TxtAttr);
			  OffSet++;
			  break;
		}
		break;
      case '\t':x += 4;
		break;
      default  :SetVidAt(DrwPg,x,GetMaxY(),Hlp[OffSet],TxtAttr);
		x++;
		break;
     }
  }
 ShowMouseCursor();
 return(cnt);
}


// Private members of class Menu

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
	byte j,R=(swMenu&Border) ? L+W-2:L+W;
	for (j=i+1;j <= visL && w+XorY < R;j++)
	if (!(P[j].swItem&HiddenPad))
	   w += 1+Spc+Spc+strlen(P[j].Prompt);
	if (w+XorY > R)
	   w -= 1+Spc+Spc+strlen(P[j].Prompt);
	XorY = R-w+1;
       }
      else
	XorY+= Spc+Spc+1+strlen(P[i].Prompt);
     }
   }
  return(XorY);
 }

void Menu::DrawPad(byte xL,byte y,byte xR,Pad *Q,byte Txt,byte Hot)
 {
   int x = xL;
   xL -= Spc;
   if (!(Q->swItem&NoShow) && (Q->swItem&RefreshPad))
    {
      TxtAttr = Txt;
      FillChr(xL,y,xR,y,Blank);
      xPrintf(x,y,Q->Prompt);

      TxtAttr = Hot;
      xPrintf(x+Q->Hot,y,"%c",Q->Prompt[Q->Hot]);
      if (swMenu&MenuVt)
       {
	xR -= Spc-1;
	if (Q->SubMenu != (Menu*)NULL)
	 {
	  xPrintf(xR-1,y,"%c",RtTriAngl);
	  xR -= 2;
	 }
	xPrintf(xR-strlen(Q->ShortCut),y,Q->ShortCut);
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
  y   = T;
  x   = L+1+Spc;
  R   = (swMenu&MenuVt) ? L+W-3:L+W-2;
  B   = T+H-1;

  if (swMenu&UpdateScr)
   {
    TxtAttr = MenuColSch->Txt;
    FillChr(L,T,R+2,B,Blank);
    TxtAttr = MenuColSch->Box;
    if (swMenu&Border)
     {
      DrawBox(x-Spc,T,R+1,B,(swMenu&BoxStyle)>>BoxShft);
      if (swMenu&Shadow)
	BoxShadow(L,T,R+2,B);
     }
    if (swMenu&MenuVt)
     {
      if (visF >0 || visL < MaxPads-1)
       {
	xPrintf(R-3-(Spc/2),T,"[%c]",uArrow);
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
	  TxtAttr = MenuColSch->Box;
	  DrawLineHz(x-Spc-1,y,R+1,((swMenu&BoxStyle)>>BoxShft)&0x01);
	}
       Flag = 0x10;
     }
    else if (i == Hot)
     {
       DrawPad(x,y,R,&P[i],MenuColSch->Xec,MenuColSch->XecHi);
       if (P[i].SubMenu != (Menu*)NULL)
	 if (Flag&0x10)
	   P[i].SubMenu->SetOrigin((swMenu&MenuVt) ? L+Spc+5:R-P[i].SubMenu->W,y+1);
	 else
	   P[i].SubMenu->SetOrigin((swMenu&MenuVt) ? L+Spc+5:x,y+1);
       Status(P[i].Msg);
     }
    else if (P[i].swItem&ActivePad)
      DrawPad(x,y,R,&P[i],MenuColSch->Txt,MenuColSch->TxtHi);
    else
      DrawPad(x,y,R,&P[i],MenuColSch->Lck,MenuColSch->Lck);


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
byte Menu::MenuCtrl()
 {
  byte Flag = 0x00;
  byte HotKey;
  word Key;
  byte p = Hot,n=0;
  if (KeyHit())
   {
    Key = GetKey();
    switch(Key)
     {
      case LtArr: if (!(swMenu&MenuVt))
		     ScrollPadPrv();
		  else if (Ptr != this && !(Ptr->swMenu&MenuVt))
		   {
		     Ptr->ScrollPadPrv();
		     Flag ^= (Ptr->P[Ptr->Hot].SubMenu) ? XecAndClose:Close;
		   }
		  else
		     Flag ^= (Ptr != this) ? Close:0;
		  break;
      case RtArr: if (!(swMenu&MenuVt))
		     ScrollPadNxt();
		  else if (Ptr != this && !(Ptr->swMenu&MenuVt))
		   {
		     Ptr->ScrollPadNxt();
		     Flag ^= (Ptr->P[Ptr->Hot].SubMenu) ? XecAndClose:Close;
		   }
		  else
		     Flag ^= XecPad;
		  break;
      case UpArr: if (swMenu&MenuVt)
		     ScrollPadPrv();
		  else if ((Ptr != this) && (Ptr->swMenu&MenuVt))
		   {
		     Ptr->ScrollPadPrv();
		     Flag ^= (Ptr->P[Ptr->Hot].SubMenu) ? XecAndClose:Close;
		   }
		  else
		     Flag ^= (Ptr != this) ? Close:0;
		  break;
      case DnArr: if (swMenu&MenuVt)
		     ScrollPadNxt();
		  else if ((Ptr != this) && (Ptr->swMenu&MenuVt))
		   {
		     Ptr->ScrollPadNxt();
		     Flag ^= (Ptr->P[Ptr->Hot].SubMenu) ? XecAndClose:Close;
		   }
		  else
		     Flag ^= XecPad;
		  break;
      case EscKy: Flag = Close;  break;
      case RetKy: Flag = XecPad; break;
      case SpcKy: Flag = XecPad; break;
      default   : Key = UpCase(Key&0x00FF);
		  n=visF;
		  for (n=visF;n <= visL && !(Flag&XecPad);n++)
		   {
		    if (P[n].swItem&ActivePad)
		     {
		      HotKey = UpCase(P[n].Prompt[P[n].Hot]);
		      Flag   = (Key == HotKey)?  XecPad:0;
		     }
		   }
		  if (Flag&XecPad) Hot = --n;
		  break;
     }
   }

  if (Hot != p)
   {
     P[Hot].swItem |= RefreshPad;
     P[p].swItem   |= RefreshPad;
     DrawMenu();
   }
  return(Flag);
 }
void Menu::Open()
 {
   byte r=Ptr->L+Ptr->W-1,
        b=Ptr->T+Ptr->H-1;
   SetDrawPg(RufPg);
   HideMouseCursor();
   Ptr->swMenu |= UpdateScr;
   Ptr->DrawMenu();
   SetDrawPg(0);
   SaveVidBlock(Ptr->Sav,DrwPg,Ptr->L,Ptr->T,r+1,b+1);
   DspRufArea(Ptr->L,Ptr->T,r,b,(swMenu&ShowEff)>>EffShft);
   ShowMouseCursor();
   swMenu |= MenuOpen;
 }
byte Menu::ShutMenu(byte Flag)
 {
   if (Ptr != this)
    {
      byte r=Ptr->L+Ptr->W-1,
           b=Ptr->T+Ptr->H-1;
      UndoEffect(Ptr->Sav,Ptr->L,Ptr->T,r,b,(Ptr->swMenu&ShowEff)>>EffShft);
      Ptr = Ptr->Ptr;        // Pop
    }
   else
      Ptr->swMenu ^= MenuOpen;
   Flag &= MaskClose;
   return Flag;
 }

// Public members of Class Menu

Menu::Menu()
 {
   L=T=W=H=N=0;
   MenuColSch = &CoolBlue;
   Spc     = 1;
   Ptr     = this;
   P       = (Pad*)NULL;
   MaxPads = 0;
 }
Menu::Menu(word MenuType,byte MaxItem)
 {
   L=T=W=H=N=Hot=0;
   MenuColSch = &CoolBlue;
   swMenu     = MenuType&MaskMenuFlags;
   Ptr        = this;
   TxtAttr    = 0x0F;
   MaxPads    = MaxItem;
   visF       = 0;
   visL       = MaxPads-1;
   P          = new Pad[MaxPads];
   H          = (swMenu&MenuVt) ? MaxPads+2:(swMenu&Border) ? 3:1;
   Spc        = (swMenu&MenuVt) ? 2:0;
   W          = (swMenu&MenuVt) ? 0:GetMaxX();
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
      delete P[i].Prompt;
      P[i].SubMenu  = (Menu*)NULL;
      P[i].PadApp   = NoApp;
      P[i].ShortCut = (char*)NULL;
    }
   delete P;
 }

byte Menu::addPad(char *Txt, word PadType)
 {
  byte   PadErr=0;
  //static word MenuID=0x100;
  //char S[20];
  Pad  *Q;
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
    Q->Prompt   = new char[1+LabelAllocSize(Txt)];
    Q->ShortCut = SetPrompt(Txt,Q->Prompt,Q->Hot);
    Q->HotKey   = StrToKey(Q->ShortCut);    //to be added to shortcuts
    Q->Msg      = new(char[1]);
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
      int Wd  = strlen(Q->Prompt)+strlen(Q->ShortCut);
      Wd     += (Wd > strlen(Q->Prompt)) ? 2:0;
      Ptr->W = max(Ptr->W,Wd+2*Ptr->Spc+4);
      Ptr->L = (Ptr->L+Ptr->W > GetMaxX()-1) ? GetMaxX()-2-Ptr->W:Ptr->L;
     }
    Ptr->N++;
   }
   return PadErr;
 }
byte Menu::addPad(char *Txt, word PadType,App PadApp)
 {
   byte PadErr = addPad(Txt,PadType);
   if (!PadErr)
      Ptr->P[Ptr->N-1].PadApp = PadApp;
   return PadErr;
 }
byte Menu::addPad(char *Txt, word PadType,Menu *Sub)
 {
   byte PadErr = addPad(Txt,PadType);
   if (!PadErr)
      Ptr->P[Ptr->N-1].SubMenu = Sub;
   return PadErr;
 }
byte Menu::addPad(char *Txt,word PadType,char *Hlp)
 {
   byte PadErr = addPad(Txt,PadType);
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
byte Menu::addPad(char *Txt,word PadType,App PadApp,char *Hlp)
 {
   byte PadErr = addPad(Txt,PadType);
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
byte Menu::addMenu(word MenuType,byte MaxItem)
 {
   byte err=0;
   Pad  *Q;
   if (Ptr->N > 0 && Ptr->P[Ptr->N-1].SubMenu == (Menu*)NULL)
    {
     Q = &Ptr->P[Ptr->N-1];
     Q->SubMenu             = new Menu(MenuType,MaxItem);
     Q->SubMenu->swMenu    ^= InternalAlloc;
     Q->SubMenu->Ptr        = Ptr;   // pop pointer;
     Q->SubMenu->MenuColSch = MenuColSch;
     if (Ptr->swMenu&MenuVt)
      {
       int Wd  = strlen(Q->Prompt)+strlen(Q->ShortCut);
       Wd     += (Wd > strlen(Q->Prompt)) ? 10:7;
       Wd     += 2*Ptr->Spc;
       Ptr->W  = max(Ptr->W,Wd);
      }
     Ptr = Q->SubMenu;  // as good as push

    /* if (Ptr->swMenu&MenuVt)
      {
       Ptr->H = min(1+Ptr->MaxPads,GetMaxY()-2);
       Ptr->W = 8;
      }
     else
      Ptr->W = GetMaxX();*/
    }
   else err = 1;
   return err;
 }
byte Menu::addMenu(Menu *M)
 {
   byte err=0;
   Pad  *Q; // no coordinate setup will be assigned by user
   if (Ptr->N > 0 && Ptr->P[Ptr->N-1].SubMenu == (Menu*)NULL)
    {
     Q = &Ptr->P[Ptr->N-1];
     Q->SubMenu          = M;
     Q->SubMenu->Ptr     = Ptr;   // pop pointer;
     if (!(Q->SubMenu->swMenu&Colorised))
       Q->SubMenu->MenuColSch = MenuColSch;
     Ptr = Q->SubMenu;  // as good as push
    }
   else err = 1;
   return err;
 }
byte Menu::addHelp(word MenuID,char *Hlp)
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
void Menu::addColor(byte Txt,byte TxtHi,byte Xec,byte XecHi,byte Lck,byte Box)
 {
   if (!(swMenu&Colorised))
    {
      MenuColSch = new Scheme;
      swMenu    ^= Colorised;
    }
   MenuColSch->Txt   = Txt;
   MenuColSch->TxtHi = TxtHi;
   MenuColSch->Xec   = Xec;
   MenuColSch->XecHi = XecHi;
   MenuColSch->Lck   = Lck;
   MenuColSch->Box   = Box;
 }
void Menu::addColor(Scheme *Sch)
 {
   if (swMenu&Colorised)
    {
      delete MenuColSch;
      swMenu ^= Colorised;
    }
   MenuColSch = Sch;
 }

void Menu::endMenu()
 {
   while (Ptr->MaxPads == Ptr->N && Ptr != this)
    {
     Ptr->swMenu ^= FullMenu;
     Ptr          = Ptr->Ptr;    // as good as pop
    }
   if (swMenu&MainAppMenu)
     swMenu ^= ((swMenu&MenuVt)) ? MainAppMenu:0;
 }
void Menu::SetOrigin(int X,int Y)
 {
   L = X;
   T = Y;
   //if (swMenu&MenuVt)
      L = (L+W > GetMaxX())  ? GetMaxX()-W-Spc-5:L;
  /* else
    {
      R = R-Spc-1;
      P[i].SubMenu->L  = x+strlen(P[i].Prompt)+strlen(P[i].ShortCut);//L + X - Spc - P[i].SubMenu->X-2;
    }
   P[i].SubMenu->L -= P[i].SubMenu->W+1;
   P[i].SubMenu->L  = (x+P[i].SubMenu->W>R) ? P[i].SubMenu->L:x;*/
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

word Menu::XecMenu()
 {
  byte rvFlag=0x00;
  Scheme SavStat=StatusBar;
  StatusBar = *MenuColSch;
  Image Sav;
  SetDrawPg(RufPg);
  swMenu |= UpdateScr;
  DrawMenu();
  HideMouseCursor();
  SetDrawPg(0);
  SaveVidBlock(&Sav,DrwPg,L,T,L+W,T+H);
  DspRufArea(L,T,L+W-1,T+H-1,(swMenu&ShowEff)>>EffShft);
  ShowMouseCursor();
  //swMenu|=UpdateScr;
  //DrawMenu();
  do
   {
      while (!(rvFlag&XecOrClose))
	 rvFlag=MenuCtrl();

      if (rvFlag&XecPad && !(rvFlag&CloseMenu))
       {
	if (P[Hot].SubMenu != (Menu*)NULL)
	  {
	   rvFlag = P[Hot].SubMenu->XecMenu();
	   DrawMenu();
	   rvFlag &= MaskClose;
	  }
	else if (P[Hot].PadApp != (App)NULL)
	  {
	   P[Hot].PadApp();
	   rvFlag ^= XecPad;
	  }
	else
	 {
	   if (P[Hot].swItem&CheckPad)
	     P[Hot].swItem ^= PadState;
	   if (P[Hot].swItem&RadioPad && !(P[Hot].swItem&PadState))
	    {
	     int i;
	     for (i=Hot-1;i >= visF && P[i].swItem&RadioPad;i--);
	     for (i++;i <= visL && P[i].swItem&RadioPad;i++)
	       P[i].swItem &= MaskPadState;
	     P[Hot].swItem ^= PadState;
	    }
	   rvFlag = Close;
	 }
       }
   }
  while (!(rvFlag&CloseMenu));
  if (Ptr != this) // main menu
    UndoEffect(&Sav,L,T,L+W-1,T+H-1,(swMenu&ShowEff)>>EffShft);
  //else
    //delete Sav;
  StatusBar = SavStat;
  return rvFlag;
 }


bool Menu::KeyDown(word Key)
 {
  byte Flag = 0x00;
  byte HotKey;
  byte p = Ptr->Hot,n=0;

  MenuID = 0xFFFF;
  if (!(swMenu&MenuOpen))
   {
     if (Ptr==this && (swMenu&MainAppMenu))
      {
       for (int i=0;i<MaxPads && !Flag;i++)
         Flag = ((P[i].swItem&ActivePad) && Key == P[i].HotKey) ? XecPad:0;
       if (Flag&XecPad)
        {
         Hot = i;
         Open();
        }
      }
    // else Scan for app xec no opening of submenu
   }
  else
   {
    Menu *Prv = Ptr->Ptr;
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
      case RtArr: if (!(swMenu&MenuVt))
		     Ptr->ScrollPadNxt();
		  else if (Ptr != this && !(Prv->swMenu&MenuVt))
		   {
		     Prv->ScrollPadNxt();
		     Flag ^= (Prv->P[Prv->Hot].SubMenu) ? XecAndClose:Close;
		   }
		  else
		     Flag ^= XecPad;
		  break;
      case UpArr: if (swMenu&MenuVt)
		     Ptr->ScrollPadPrv();
		  else if ((Prv != this) && (Prv->swMenu&MenuVt))
		   {
		     Prv->ScrollPadPrv();
		     Flag ^= (Prv->P[Prv->Hot].SubMenu) ? XecAndClose:Close;
		   }
		  else
		     Flag ^= (Ptr != this) ? Close:0;
		  break;
      case DnArr: if (swMenu&MenuVt)
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
      default   : Key = UpCase(Key&0x00FF);
		  n=visF;
		  for (n=visF;n <= visL && !(Flag&XecPad);n++)
		   {
		    if (Ptr->P[n].swItem&ActivePad)
		     {
		      HotKey = UpCase(Ptr->P[n].Prompt[Ptr->P[n].Hot]);
		      Flag   = (Key == HotKey)?  XecPad:0;
		     }
		   }
		  if (Flag&XecPad) Ptr->Hot = --n;
		  break;
     }
    if (Ptr->Hot != p)
    {
     Ptr->P[Hot].swItem |= RefreshPad;
     Ptr->P[p].swItem   |= RefreshPad;
     Ptr->DrawMenu();
     XecPadApp(Flag);
    }
   }
   return true;
 }
bool Menu::MouseMove(int mx,int my)
 {
  bool rvEvtProcessed=false;
  byte p = Ptr->visF;
  byte r = Ptr->L+Ptr->W-1;
  byte b = Ptr->T+Ptr->H-1;

  MenuID = 0xFFFF;
  if (!(mx < Ptr->L || mx > r || my < Ptr->T || my > b))
   {
    if (Ptr->swMenu&MenuVt)
     {
       byte y=Ptr->T+1;
       while (p != Ptr->visL && y < my)
         y=Ptr->NextPad(y,p++);
       rvEvtProcessed = (bool)(y==my && Ptr->P[--p].swItem&ActivePad);

     }
    else
     {
      byte x=Ptr->NextPad(Ptr->L+1,p);
      while (p != Ptr->visL && x-1 < mx)
	x = Ptr->NextPad(x,++p);
      rvEvtProcessed = (bool)(x-1 > mx && Ptr->L < mx && (Ptr->P[p].swItem&ActivePad));
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
  byte r = Ptr->L+Ptr->W-1;
  byte b = Ptr->T+Ptr->H-1;

  MenuID = 0xFFFF;
  if (!(mx < Ptr->L || mx > r || my < Ptr->T || my > b))
   {
    if (Ptr->swMenu&MenuVt)
     {
       if (Ptr->visF>0 || Ptr->visL<Ptr->MaxPads)
         if (mx == r-Spc)
          if (my==Ptr->T)
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
         byte y=Ptr->T+1;
         while (p != Ptr->visL && y < my)
           y=Ptr->NextPad(y,p++);
         Flag = (y==my && Ptr->P[--p].swItem&ActivePad) ? 0x11:0;
        }
     }
    else
     {
      byte x=Ptr->NextPad(Ptr->L+1,p);
      while (p != Ptr->visL && x-1 < mx)
	x = Ptr->NextPad(x,++p);
      if (Ptr->P[p].swItem&ActivePad)
      Flag = (x-1 > mx && Ptr->L < mx) ? 0x11:0;

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
  Scheme SavStat=StatusBar;
  StatusBar = *MenuColSch;
  byte x,y,r,b;
  Pad *Q=&Ptr->P[Ptr->Hot];
  if (Flag&CloseMenu)
   Flag = ShutMenu(Flag);
  if (Flag&XecPad && !(Flag&CloseMenu))
   {
    if (Q->SubMenu != (Menu*)NULL)
     {
       Ptr=Q->SubMenu; // Push
       Open();
       Flag   &= MaskClose;
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

  StatusBar = SavStat;
 }

word Menu::GetMenuID()
 {
   return MenuID;
 }



