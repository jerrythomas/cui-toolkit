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

   void PadPos(int m,int *xL,int *Y,int *xR);

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

Scheme GrayScale,
       Classic;

byte GetLblWidth(char *Lbl)
 {
  int i,w,l=strlen(Lbl);
  for(i=0,w=0;i < l;i++,w++)
   {
    for(;i < l && Lbl[i] != '&' && Lbl[i] != '\t'; i++,w++);
    switch (Lbl[i])
    {
     case '&'  : w--;
                 break;
     case '\t' : for(i++,w++;Lbl[i] != '\0';i++,w++);
                  if (Lbl[i] == '\t')
                    Lbl[i] = 32;
                 break;
    }
   }
  return(w);
 }
char *SetLblStr(char *Src, char *Dst, byte& Pos)
 {
  int i,j,l = strlen(Src);
  char *Addr = (char*)NULL;

  for(i=0,Pos=0,j=0;i < l;i++,j++)
   {
    for(;i < l && Src[i] != '&' && Src[i] != '\t'; i++,j++)
         Dst[j] = Src[i];
    switch (Src[i])
     {
      case '&'  : Dst[j] = Src[++i];
                  if (Src[i] != '&')
                    Pos = j;
                  break;
      case '\t' : if (Addr == (char*)NULL)
                   {
                     Dst[j] = '\0';
                     Addr = (char*)(Dst+j+1);
                   }
                  else
                     Dst[j] = ' ';
                  break;
     }
   }
   Dst[--j] = '\0';
   return((Addr == (char *) NULL ) ?(char*)(Dst+j):Addr);
 }

Menu:: Menu()
 {
  Max = NumDef = 0;
  CurP = 0;
 }
Menu::~Menu()
 {
  delete M;
 }
void Menu::PadPos(int m,int *xL,int *Y,int *xR)
 {
  if (swMenu&MenuVt)
   {
    *Y  = t+Ht+m*(Height()+8);
    *xL = l+3;
    *xR = r-3;
   }
  else
   {
    *Y  = t+Ht;
    *xL = l;
    *xR = Width(M[0].Prompt)+*xL+4*Wd;
    for (int i=1;i<=m;i++)
     {
      *xL = *xR + Width("W")-2*Wd;
      *xR = Width(M[i].Prompt)+*xL+4*Wd;
     }
   }
 }

void Menu::DefineMenu(word Type,int L,int T,int R,int B,byte MaxPad,Scheme S)
 {
  TextSize(1,1);
  swMenu = Type;
  l = L;
  t = T;
  r = R;
  b = B;
  Max    = MaxPad;
  NumDef = 0;
  M = new Pad[Max];
  Sch = S;
  if (swMenu&MenuVt)
   {
    Wd  = (r-l-6)/2;
    Ht  = (b-t-6-Max*(Height()+8))/2;
   }
  else
   {
    Wd  = Width("w");
    Ht  = (b-t-6-Height())/2;
   }
 }
void Menu::DefinePad(char *Txt,word type,App PadApp)
 {
  if (NumDef < Max)
   {
    M[NumDef].swPad    = type;
    M[NumDef].PadApp   = PadApp;
    M[NumDef].Prompt   = new(char[1+GetLblWidth(Txt)]);
    M[NumDef].ShortCut = SetLblStr(Txt,M[NumDef].Prompt,M[NumDef].Pos);
    M[NumDef].Hlp      = new char[1];
    M[NumDef].Hlp[0]   = '\0';
    if (swMenu&MenuVt)
     {
      int W = Width(M[NumDef].Prompt)+Width(M[NumDef].ShortCut);
      Wd = min(Wd,(r-l-6-4*Width("W")-W)/2);
     }
    NumDef++;
   }
 }
void Menu::SetPadHelp(byte Which,char *Str)
 {
  if (Which < Max)
   {
    if (M[Which].Hlp) delete M[Which].Hlp;
    M[Which].Hlp = new char[strlen(Str)+1];
    strcpy(M[Which].Hlp,Str);
   }
 }

void Menu::DrawPad(int x,int y,byte i,byte Txt,byte TxtHi)
 {
  SetColor(Txt);
  gPrintf(x,y+4,M[i].Prompt);         //x+wd
  SetColor(TxtHi);
  gPrintf(x+Width("W")*M[i].Pos,y+4,"%c",M[i].Prompt[M[i].Pos]);//x+wd
 }
void Menu::DrawMenu()
 {
  int x=l,y=t,xR=r;
  int W = (swMenu&MenuVt) ? Width("Wd"):Wd;
  ViewPort(0,0,xMax(),yMax());
  Justify(LeftText,TopText);
  SetColor(Sch.Nrm+5);
  Box(l,t,r,b,Sch.Nrm+5);
  Tile(l,t,r,b,Sch.Nrm);
  if (swMenu&MenuVt)
   {
    x  += 3;
    xR -= 3;
   }
  y += Ht;
  for (int i=0;i<Max;i++)
   {
    if (!(swMenu&MenuVt))
     xR = Width(M[i].Prompt)+x+2*Wd;//4*Wd;
    if (i==CurP)
     {
      SetColor(Sch.Hot);
      Box(x,y,xR,y+Height()+7,Sch.Hot); //x+wd,xr-wd
      DrawPad(x+W,y,i,Sch.Xec,Sch.XecHi);
     }
    else if (M[i].swPad&LockedPad)
      DrawPad(x+W,y,i,Sch.Lck,Sch.Lck);
    else if (M[i].swPad&MenuBreak)
     {
      if (swMenu&MenuVt)
       {
        byte Col = Sch.Nrm;
        for (int j=0;j<3;j++,Col+=3)
         {
          SetColor(Col);
          Line(x+j,y+Height()/2+4-j,xR-j,y+Height()/2+4-j);
          Line(x+j,y+Height()/2+4+j,xR-j,y+Height()/2+4+j);
         }
       }
     }
    else if (M[i].swPad&ActivePad)
     DrawPad(x+W,y,i,Sch.Txt,Sch.TxtHi);

    if (swMenu&MenuVt)
     y += Height()+8;
    else
     x = xR + Width("W"); //-2*Wd;
   }
 }

byte Menu::MenuKeys()
 {
  byte NewP=CurP;
  byte Flag = 0x00;
  word Key;
  byte HotKey;
  int W = (swMenu&MenuVt) ? Width("Wd"):Width("W");
  if (KeyHit())
   {
    Key = GetKey();
    switch(Key)
     {
      case LtArr: if (!(swMenu&MenuVt))
		    do
                     NewP = (NewP+Max-1)%Max;
                    while (M[NewP].swPad&NoShow);
                  break;
      case RtArr: if (!(swMenu&MenuVt))
                    do
                     NewP = (NewP+1)%Max;
                    while (M[NewP].swPad&NoShow);
                  break;
      case UpArr: if (swMenu&MenuVt)
                    do
                     NewP = (NewP+Max-1)%Max;
		    while (M[NewP].swPad&NoShow);
                  break;
      case DnArr: if (swMenu&MenuVt)
                    do
		     NewP = (NewP+1)%Max;
                    while (M[NewP].swPad&NoShow);
                  break;
      case EscKy: Flag = Close;
                  break;
      case RetKy: Flag = XecPad;
                  break;
      default   : Key = UpCase(Key&0x00FF);
		  NewP = 0;
		  do
		   {
		     if (M[NewP].swPad&ActivePad)
		      {
		       HotKey = UpCase(M[NewP].Prompt[M[NewP].Pos]);
		       Flag = (HotKey==Key) ? XecPad:0;
		      }
 //		    Flag = (Flag &&  ? XecPad:0;
		    NewP++;
		   }
		  while (!(Flag&XecPad) && NewP < Max);
		  NewP--;
		  if (!(Flag&XecPad))
		    NewP = CurP;
		  break;
     }

    if (NewP != CurP)
     {
      int xL,y,xR;
      PadPos(CurP,&xL,&y,&xR);
      SetColor(Sch.Nrm+5);
      Box(xL+Wd,y,xR-Wd,y+Height()+7,Sch.Nrm+5);
      DrawPad(xL+W,y,CurP,Sch.Txt,Sch.TxtHi);
      CurP = NewP;
      //DrawMenu();
      PadPos(CurP,&xL,&y,&xR);
      SetColor(Sch.Hot);
      Box(xL+Wd,y,xR-Wd,y+Height()+7,Sch.Hot);
      DrawPad(xL+W,y,CurP,Sch.Xec,Sch.XecHi);
      Status(M[CurP].Hlp);
     }
   }
 return Flag;
}

void Menu::Xecute()
 {
  byte Flags = 0x00;
  DrawMenu();
  Status(M[CurP].Hlp);
  while (KeyHit())
   GetKey();
  do
   {
    UsrMenuID = 0xFF;
    while (!Flags)
      Flags = MenuKeys();
    if (Flags&XecPad)
     {
      UsrMenuID = CurP;

      if (M[CurP].PadApp != NoApp)
        M[CurP].PadApp();
      else
        Flags = CloseMenu;

      Flags = (!(Flags&CloseMenu)) ? 0:Flags;
     }
   }
  while (!(Flags&CloseMenu));
  //return((Flags&CloseAll) ? CloseMenu:Flags&MaskClose);
 }
word Menu::MenuID()
 {
  return UsrMenuID;
 }
void InitScheme()
 {
  Classic.Nrm   = Cyan+7;
  Classic.Hot   = 0;
  Classic.Txt   = Gray+17;
  Classic.TxtHi = Red+15;
  Classic.Lck   = Red+10;
  Classic.Xec   = Green +20;
  Classic.XecHi = Yellow+30;

  GrayScale.Nrm   = Gray+17;
  GrayScale.Hot   = 0;
  GrayScale.Txt   = Red+7;
  GrayScale.TxtHi = Cyan+18;
  GrayScale.Lck   = Gray+14;
  GrayScale.Xec   = Green +20;
  GrayScale.XecHi = Yellow+30;
}
/*
main()
 {
   Menu M;
   SetVidMode(Vga1024x768x256);
   InitScheme();
   TextSize(1,1);
   M.DefineMenu(MenuHz,20,100,300,128,4,Classic);
    M.DefinePad("&Translate",ActivePad,NoApp);
    M.DefinePad("&Rotate",ActivePad,NoApp);
    M.DefinePad("&Scale",ActivePad,NoApp);
    M.DefinePad("&Shear",ActivePad,NoApp);
   M.SetPadHelp(0,"Translate the Object in 3D");
   M.SetPadHelp(1,"Rotate the Object in 3D");
   M.SetPadHelp(2,"Scale the Object in 3D");
   M.SetPadHelp(3,"Shear the Object in 3D");
  // M.DrawMenu();
   M.Xecute();
   GetKey();
   return(0);
 }*/
