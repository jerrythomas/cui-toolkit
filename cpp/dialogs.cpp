#ifndef __DIALOGS_H
#define __DIALOGS_H

#ifndef __VDU_H
#include <vdu.h>
#endif
#include <string.h>
#include <kbd.h>

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

#define AllOptions    0xFFFF

#define ActiveTgs     0x0001
#define HiddenTgs     0x0002
#define LockedTgs     0x0004
#define UsrDefSch     0x8000

//
//  swDlg  Dialog Status Word
//  Bits 0-4 Dialog Buttons
//     Bit 0  >> Close        Bit 1  >> Help
//     Bit 2  >> Min/Max      Bit 3  >> Properties
//  Bits 5-6 Scroll bars
//     Bit 4  >> Horizontal   Bit 5  >> Vertical
//  Bits 8-11 Button Activity
//     Bit
6  >> Close        Bit 7  >> Help
//     Bit 8  >> Max/Min      Bit 9 >> Properties
//  Bit 10    Draw Header
//  Bit 11    Draw Border
//  Bit 12-13 Border Style
//  Bit 14    Draw Shadow
//  Bit 15    Fill dialog Interior
//  Bit 1 >> Show Close Dialog Option
//  Bit 2 >> Show Close Dialog Option
//  Bit 3 >> Show Close Dialog Option

//
// Scheme
// Txt   == cWrk
// Xec   == cHdr
// XecHi == cHot
// TxtHi == ??
// Lck   == cLock
// Box   == cBox

typedef struct
         {
           char  *Prompt;      // Contains the Prompt string
           char  *ShortCut;    // Address of ShortCut String
           byte  HotKeyPos;    // Position of Hot Character
           byte  HotKey;       // Short Cut Key Code
           word  ItemID;       // Item Identification code
           word  swItem;       // Item Status Word
         } ItemInf;

typedef struct Group
         {
           byte     L,T,R,B;
           ItemInf  GrpInf;
           Group    *Prv,*Nxt;
         };

typedef struct TagSheet
         {

           ItemInf      Inf;         // Pad Information
           Group        *GrpF,       // Ptr to first Group
                        *GrpH;       // Ptr to Current Group
           App          TgsApp;      // App to be taken on selection
           char         *Msg;        // Message string for guidance
           Scheme       *TgsColSch;  // Ptr Or Structure for ColourScheme
           TagSheet     *Prv,*Nxt;   // Ptr to next and previous items
         } ;

typedef struct Tag
         {
          byte     L,T;         // Top Left Coordinates of Tag
          byte     R,B;          // Right Bottom Coordinates
          word     swTag;       // Menu type & other flags
          TagSheet *F,          // Ptr to first Tag Sheet
                   *H,          // Ptr to Highlighted Tag Sheet
                   *VisF,       // Ptr to first Visible Tag Sheet
                   *VisL;       // Ptr to last Visible Tag Sheet
          Scheme   TMenuColSch; // Colour Scheme
          byte     MaxTags;
         } ;

typedef struct Dialog
         {
          byte      nrmL,nrmT,nrmR,nrmB;
          byte      maxL,maxT,maxR,maxB;

          Scheme    DlgSch;
          byte      DlgFill;
          App       DlgXec,DlgXit,DlgHlp;
          char      *DlgAppName;
          Tag       *DlgTag;     // Ptr To Tag Sheets
          Group     *GrpF,       // Ptr to first Group if !Tag
                    *GrpH;       // Ptr to Current Group

          Image     *DlgScr;

          word      swDlg;
          ItemInf  DlgInf;

         };
class DialogClass
 {
  private:

   // Special Purpose Variables

   byte      nrmL,nrmT,nrmR,nrmB;
   byte      maxL,maxT,maxR,maxB;

   Scheme    DlgSch;
   Byte      DlgFill;
   App       DlgXec,DlgXit,DlgHlp;
   char      *DlgAppName;
   Tag       *DlgTag;     // Ptr To Tag Sheets
   Group     *GrpF,       // Ptr to first Group if !Tag
             *GrpH;       // Ptr to Current Group

   Image     *Scr;

   Word      swDlg;
   Bool      Quit;

   // General Purpose variables

   byte      L,T,R,B,X,Y;
   word      Key;
   Tag       *TagG;
   TagSheet  *TgsN,*TgsC;
   Group     *GrpN,*GrpC;
   byte      NumTags;

  public:

   DialogClass(void);
   ~DialogClass(void);

   void SetDialogClient(App Xec);
   void SetDialogClose (App Xit);
   void SetDialogHlp   (App Hlp);
   void SetDialogColors(Byte H,Byte W,Byte X,Byte L,Byte O,Byte F);
   void DialogSetUp    (Byte l,Byte t,Byte r,Byte b,Word Ops,char *DAN);
   void Frame(Byte L,Byte T,Byte R,Byte B,char *Title,Byte Style);
   void DialogDraw(void);
   void DialogMinimise (void);
   void DialogMaximise (void);
   void DialogMoveSize (void);
   void Dialog(Byte L,Byte T,Byte R,Byte B,char *Title,Byte Style,Bool Shad);

   byte TagKeys();
   void DrawTagSheet(byte L,byte T,byte Txt,byte TxtHi);
   void DrawTags();
   byte DefineTagSheet(char *Txt,word TgsType,App TgsApp,Scheme *ColSch);
   void DefineTags(byte L,byte T,byte R,byte B,word TagType,word Other,byte MaxItem);
   void InitTags();
 };

#endif

DialogClass::DialogClass()
 {
  L       = 0;
  T       = 1;
  R       = GetMaxX();
  B       = GetMaxY()-1;
  DlgFill = Blank;
  DlgHlp  = NoApp;
  DlgXec  = NoApp;
  DlgXit  = NoApp;
  Quit    = False;
  DlgSch.Xec   = SetTxtCol(Brown,LightGray);
  DlgSch.Txt   = SetTxtCol(Blue,Yellow);
  DlgSch.Box   = SetTxtCol(Blue,Yellow);
  DlgSch.Lck   = SetTxtCol(LightGray,Brown);
  DlgSch.XecHi = SetTxtCol(Brown,Red);
  Scr     = new(Image);
  SaveVidBlock(Scr,DrwPg,L,T,R,B);
 }
DialogClass::~DialogClass()
 {
  if (DlgXit != NoApp)
  DlgXit();
  DlgFill = Blank;
  DlgHlp  = NoApp;
  DlgXec  = NoApp;
  DlgXit  = NoApp;
  ShowVidBlock(Scr,DrwPg,True);
 }
void DialogClass::SetDialogClient(App Xec)
 {
  DlgXec = Xec;
 }
void DialogClass::SetDialogClose (App Xit)
 {
  DlgXit = Xit;
 }
void DialogClass::SetDialogHlp   (App Hlp)
 {
  DlgHlp = Hlp;
 }
void DialogClass::SetDialogColors(Byte H,Byte W,Byte X,Byte L,Byte O,Byte F)
 {
  DlgSch.Xec   = H;
  DlgSch.Txt   = W;
  DlgSch.Box   = X;
  DlgSch.Lck   = L;
  DlgSch.XecHi = O;
  DlgFill      = F;
 }
void DialogClass::DialogSetUp(Byte l,Byte t,Byte r,Byte b,Word Ops,char *DAN)
 {
  nrmL = l;
  nrmT = t;
  nrmR = r;
  nrmB = b;
  swDlg = Ops;
  DlgAppName = new(char[strlen(DAN)+1]);
  strcpy(DlgAppName,DAN);
 }
void DialogClass::DialogDraw()
 {
  if (Scr->Sav == (word*)NULL)
   SaveVidBlock(Scr,DrwPg,L,T,R,B);

  Y = T;
  if (swDlg&DrawHeader)
   {
    SetTexAttr(DlgSch.Xec);
    FillChr(L,T,R,T,Blank);
    Y = T+1;
   }
  TxtAttr=DlgSch.Txt;
  if (swDlg&FillDialog && T != B)
   FillChr(L,Y,R,B,DlgFill);
//	 else if (T != B)
//		CharBox(DrwPg,L,Y,R,B,DlgFill);
  if (swDlg&DrawBorder && T != B)
   DrawBox(L,Y,R,B,((swDlg&BorderStyle)>>StyleShft));

  if (swDlg&ShowSpecs)
   {
    TxtAttr = (swDlg&DrawHeader) ? DlgSch.Xec:DlgSch.Box;
    xPrintf(L+1,T,"[ ]");
    TxtAttr = (swDlg&ActiveSpecs) ? DlgSch.XecHi:DlgSch.Lck;
    xPrintf(L+2,T,"%c",SqBox);
   }
  X = R;
  if (swDlg&ShowClose)
   {
    X-=3;
    TxtAttr = (swDlg&DrawHeader) ? DlgSch.Xec:DlgSch.Box;
    xPrintf(X,T,"[ ]");
    TxtAttr = (swDlg&ActiveClose) ? DlgSch.XecHi:DlgSch.Lck;
    xPrintf(X+1,T,"X");
   }
  if (swDlg&ShowHelp)
   {
    X-=3;
    TxtAttr = (swDlg&DrawHeader) ? DlgSch.Xec:DlgSch.Box;
    xPrintf(X,T,"[ ]");
    TxtAttr = (swDlg&ActiveHelp) ? DlgSch.XecHi:DlgSch.Lck;
    xPrintf(X+1,T,"?");
   }
  if (swDlg&ShowMinMax)
   {
    X-=3;
    TxtAttr = (swDlg&DrawHeader) ? DlgSch.Xec:DlgSch.Box;
    xPrintf(X,T,"[ ]");
    TxtAttr = (swDlg&ActiveMinMax) ? DlgSch.XecHi:DlgSch.Lck;
    if (L==0 && R == GetMaxX() && T ==1 && B == GetMaxY()-1)
     xPrintf(X+1,T,"%c",dArrow);
    else if (T == B)
     xPrintf(X+1,T,"%c",uArrow);
    else
     xPrintf(X+1,T,"%c",DblArrow);
   }
  if (swDlg&DrawShadow)
   if (T != B && B != GetMaxY() && R != GetMaxX())
     BoxShadow(L,T,R,B);
   if (swDlg&HzScrollBar && T+6 < B && L+20 <R)
    {
     SetTexAttr(DlgSch.Box);
     FillChr(L+1,B,R-1,B,WideDot);
     xPrintf(L+1,B,"%c",LtTriAngl);
     xPrintf(R-1,B,"%c",RtTriAngl);
    }
   if (swDlg&VtScrollBar && T+6 < B && L+20 <R)
    {
     SetTexAttr(DlgSch.Box);
     FillChr(R,Y+1,R,B-1,WideDot);
     xPrintf(R,Y+1,"%c",UpTriAngl);
     xPrintf(R,B-1,"%c",DnTriAngl);
    }
   TxtAttr = (swDlg&DrawHeader) ? DlgSch.Xec:DlgSch.Box;
   (swDlg&ShowSpecs) ? Justify(L+3,T,X,DlaAppName):Justify(L+3,T,X,DlaAppName);
   /*switch(DlgAppName[0])
    {
     case '!':X = (swDlg&ShowSpecs) ? L+5: L+2;
       	      xPrintf(X,T,DlgAppName+1);
	      break;
     case '#':X -= strlen(DlgAppName);
	      xPrintf(X,T,DlgAppName+1);
	      break;
     case '%':X -= strlen(DlgAppName);
              X  = (swDlg&ShowSpecs) ? (X+L+4)/2:(X+L)/2;
	      xPrintf(X,T,DlgAppName+1);
	      break;
     default :X = (swDlg&ShowSpecs) ? L+5: L+2;
	      xPrintf(X,T,DlgAppName);
	      break;*/
    }
 }
void DialogClass::DialogMinimise()
 {
  R  = L + strlen(DlgAppName)+3;
  R += (swDlg&ShowClose)  ? 3:0;
  R += (swDlg&ShowHelp)   ? 3:0;
  R += (swDlg&ShowMinMax) ? 3:0;
  R += (swDlg&ShowSpecs)  ? 3:0;
  T  = B = GetMaxY()-1;
  ShowVidBlock(Scr,DrwPg,True);
  Scr = (Image*)NULL;
  DialogDraw();
 }
void DialogClass::DialogMaximise()
 {
  L  = maxL;
  R  = maxR;
  T  = maxT;
  B  = maxB;
  ShowVidBlock(Scr,DrwPg,True);
  Scr = (Image*)NULL;
  DialogDraw();
 }
void DialogClass::DialogMoveSize()
 {
  byte ReDraw=0;
  X  = strlen(DlgAppName)+2;
  X += (swDlg&ShowClose)  ? 3:0;
  X += (swDlg&ShowHelp)   ? 3:0;
  X += (swDlg&ShowMinMax) ? 3:0;
  X += (swDlg&ShowSpecs)  ? 3:0;
  do
   {
    Key = GetKey();
    switch(Key)
     {
      case LtArr     : if (L > 0)
     			{
			 L=--nrmL;
			 R=--nrmR;
                         ReDraw=1;
			}
		       break;
      case RtArr     : if (R < GetMaxX())
			{
			 L=++nrmL;
			 R=++nrmR;
                         ReDraw=1;
			}
		       break;
      case UpArr     : if (T > 1)
			{
			 T=--nrmT;
			 B=--nrmB;
                         ReDraw=1;
			}
		       break;
      case DnArr     : if (B < GetMaxY()-1)
			{
			 T=++nrmT;
			 B=++nrmB;
                         ReDraw=1;
			}
			break;
      case Ctrl_LtArr : if (R > L+X)
			 {
                          R=--nrmR;
                          ReDraw=1;
                         }
			break;
      case Ctrl_RtArr : if (R < GetMaxX())
			 {
                           R=++nrmR;
                           ReDraw=1;
                         }
			break;
      case Ctrl_UpArr : if (B > T)
			 {
                          B=--nrmB;
                          ReDraw=1;
                         }
			break;
      case Ctrl_DnArr : if (B < GetMaxY()-1)
			 {
                          B=++nrmB;
                          ReDraw=1;
                         }
			break;
     }
    if (ReDraw)
     {
      ShowVidBlock(Scr,DrwPg,True);
     //Scr = (Image*)NULL;
      DialogDraw();
      ReDraw=0;
     }
    }
   while (Key != EscKy && Key != RetKy);
  }

void DialogClass::Frame(Byte L,Byte T,Byte R,Byte B,char *Title,Byte Style)
 {
  /*L %= 80;
  R %= 80;
  T %= 25;
  B %= 25;
  if (L>R) Swap(&L,&R);
  if (T>B) Swap(&T,&B);*/
  DrawBox(L,T,R,B,Style);
  Justify(L,T,R,Title);
 /* X = strlen(Title);
  if (X < R-L)
   {
    switch(Title[0])
     {
       case '!' : xPrintf(L+2,T,Title+1);
		  break;
       case '#' : xPrintf(R-X,T,Title+1);
                  break;
       case '%' : xPrintf((R+L-X)/2+1,T,Title+1);
		  break;
       default  : xPrintf(L+1,T,Title);
		  break;
     }
   }    */
 }


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

byte DialogClass::TagKeys()
 {
  word TgKey;
  byte TgCode=0x00;
  if (KeyHit())
   {
     TgKey = GetKey();
     switch(TgKey)
      {
       case Alt_LtArr : for (TgsN=TagG->H->Prv;!(TgsN->Inf.swItem&ActiveTgs);TgsN = TgsN->Prv);
                        TagG->H = TgsN;
                        TgCode = 0x01;
                        break;
       case Alt_RtArr : for (TgsN=TagG->H->Nxt;!(TgsN->Inf.swItem&ActiveTgs);TgsN = TgsN->Nxt);
                        TagG->H = TgsN;
                        TgCode = 0x01;
                        break;
       case EscKy     : TgCode = 0x02;
                        break;
       default        : byte ChKey = UpCase(TgKey&0x00FF);
                        TgsN = TagG->F;
                        do
                         {
                          if (ChKey == TgsN->Inf.Prompt[TgsN->Inf.HotKeyPos])
                             TgCode = 0x01;
                          if (!(TgCode&0x01))
                             TgsN = TgsN->Nxt;
                         }
                        while (!(TgCode&0x01) && TgsN != TagG->F);
                        if (TgsN == TagG->H)
                            TgCode = 0x00;
                        TagG->H = TgsN;
                        break;
      }
   }
  return(TgCode);
 }
void DialogClass::DrawTagSheet(byte L,byte T,/*,byte W,*/byte Txt,byte TxtHi)
 {
  TxtAttr = Txt;
  xPrintf(L,T,"[ %s ]",TgsN->Inf.Prompt);
  TxtAttr = TxtHi;
  xPrintf(L+TgsN->Inf.HotKeyPos+2,T,"%c",TgsN->Inf.Prompt[TgsN->Inf.HotKeyPos]);
 }

void DialogClass::DrawTags()
 {
  byte X = TagG->L;
  TgsN=TagG->F;
  do
   {
    if (!(TgsN->Inf.swItem&HiddenTgs))
     {
      if (TgsN->Inf.swItem&LockedTgs)
        DrawTagSheet(X,TagG->T,TgsN->TgsColSch->Lck,TgsN->TgsColSch->Lck);
      else if (TgsN == TagG->H)
       {
        DrawTagSheet(X,TagG->T,TgsN->TgsColSch->Xec,TgsN->TgsColSch->XecHi);
        TxtAttr = TgsN->TgsColSch->Xec;
        FillChr(TagG->L,TagG->T+1,TagG->R,TagG->B,Blank);
        //TxtAttr=TgsN->TgsColSch.Xec;
        DrawBox(TagG->L,TagG->T+1,TagG->R,TagG->B,0);
       }
      else
        DrawTagSheet(X,TagG->T,TgsN->TgsColSch->Txt,TgsN->TgsColSch->TxtHi);

      X += 5+strlen(TgsN->Inf.Prompt);
     }
     TgsN = TgsN->Nxt;
   }
  while (TgsN != TagG->F);
 }
byte DialogClass::DefineTagSheet(char *Txt,word TgsType,App TgsApp,Scheme *ColSch)
 {
  byte TgsErr=0;
  TgsN = (TagSheet*)NULL;
  NumTags++;
  TgsN = new(TagSheet);
  //TgsN->Inf.ItemID   = (TgsType&TagBreak) ? 0x0000:MaxID++;
  TgsN->Inf.swItem   = TgsType;
  TgsN->Inf.Prompt   = new(char[1+GetLblWidth(Txt)]);
  TgsN->Inf.ShortCut = SetLblStr(Txt,TgsN->Inf.Prompt,TgsN->Inf.HotKeyPos);
  TgsN->Inf.HotKey   = StrToKey(TgsN->Inf.ShortCut);
  TgsN->Msg          = new(char[1]);
  TgsN->Msg[0]       = '\0';
  TgsN->TgsApp       = TgsApp;
  if (TgsType&UsrDefSch)
   {
    TgsN->TgsColSch  = new(Scheme);
    *TgsN->TgsColSch  = *ColSch;
   }
  else
    TgsN->TgsColSch  = ColSch;
  if (TagG->F == (TagSheet*)NULL)
   {
    TagG->H    = TagG->F    = TgsN;
    TagG->VisF = TagG->VisL = TgsN;
    TgsN->Prv  = TgsN->Nxt  = TgsN;
   }
  else
   {
    TgsN->Prv      = TagG->F->Prv;
    TgsN->Nxt      = TagG->F;
    TgsN->Prv->Nxt = TgsN;
    TgsN->Nxt->Prv = TgsN;
   }
  TgsN = (TagSheet*)NULL;
  return(TgsErr);
 }

void DialogClass::DefineTags(byte L,byte T,byte R,byte B,word TagType,word Other,byte MaxItem)
 {
  TagG->swTag   = (TagType^Other);
  TagG->MaxTags = MaxItem;
  NumTags       = 0;
  TagG->F       = TagG->H    = (TagSheet*)NULL;
  TagG->VisF    = TagG->VisL = (TagSheet*)NULL;
  TagG->L       = L;
  TagG->T       = T;
  TagG->R       = R;
  TagG->B       = B;
 }

void DialogClass::InitTags()
 {
  TagG = new(Tag);
  TagG->H    = TagG->F    =(TagSheet*)NULL;
  TagG->VisF = TagG->VisL =(TagSheet*)NULL;

  NumTags = 0;
 }
byte DialogClass::DefineGroup(byte L,byte T,byte R,byte B,char *Txt,word Type)
 {
  byte GrpErr=0;
  if (TagG != (Tags*)Null)
   {
    TgsN = TagG->F->Prv;
    if (TgsN->GrpF != (Group*)NULL)
     {
      TgsN->GrpF = new(Group);
      TgsN->GrpH = TgsN->GrpF;
      GrpN       = GrpG      = TgsN->GrpF;
      GrpG->Prv  = GrpG->Nxt = TgsN->GrpF;
     }
    else
     {
      GrpN  = new(Group);
      GrpG->Prv->Nxt = GrpN;
      GrpN->Prv      = GrpG->Prv;
      GrpN->Nxt      = GrpG;
      GrpG->Prv      = GrpN;
     }
   }
  NumTags++;
  //GrpN->Inf.ItemID   = (GrpType&TagBreak) ? 0x0000:MaxID++;
  GrpN->Inf.swItem   = Type;
  GrpN->Inf.Prompt   = new(char[1+GetLblWidth(Txt)]);
  GrpN->Inf.ShortCut = SetLblStr(Txt,GrpN->Inf.Prompt,GrpN->Inf.HotKeyPos);
  GrpN->Inf.HotKey   = StrToKey(GrpN->Inf.ShortCut);

  if (TagG->F == (TagSheet*)NULL)
   {
    TagG->H    = TagG->F    = GrpN;
    TagG->VisF = TagG->VisL = GrpN;
    GrpN->Prv  = GrpN->Nxt  = GrpN;
   }
  else
   {
    GrpN->Prv      = TagG->F->Prv;
    GrpN->Nxt      = TagG->F;
    GrpN->Prv->Nxt = GrpN;
    GrpN->Nxt->Prv = GrpN;
   }
  GrpN = (TagSheet*)NULL;
  return(GrpErr);
 }
main()
 {
   SetVidMode(Txt132x25x16x4);
   DialogClass D;

   D.DialogSetUp(10,5,50,20,0xFFFF,"Dialog by Jerry Thomas");

   DrwPg=0;
   D.DialogDraw();
   //D.DialogMoveSize();
   GetKey();
   D.DialogMinimise();
   GetKey();
   D.DialogMaximise();
   GetKey();
   return(0);
 }
