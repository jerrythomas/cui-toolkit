Class BTree
 {
   1 for HotKey's & 1 for Key
 }

class Nodes{};
class Node
 {
   protected:
     word   swItem;      // Item Status Word
     word   PadID;       // Pad Identification code
     byte   Hot;         // Position of Hot Character
     char   *Prompt;     // Contains the Prompt string
     char   *ShortCut;   // Address of ShortCut String
     word   HotKey;
     App    PadApp;      // App to be taken on selection
     char   *Msg;        // Message string for guidance
     Nodes  *SubNodes;    // Ptr to Sub-Nodes
     Nodes  *Parent;
     Node   *Next;
     Node   *Previous

     friend class Nodes;
 };

Caption::Caption(char *Src)
 {
  int  siz=0;

  Txt      = Src;
  ShortCut = (char*)NULL;
  Hot      = 0;
  HotKey   = 0;
  Key      = 0;
  while (*Src)
   {
    for(;*Src && *Src != '&' && *Src != '\t';Src++,siz++);
    if (*Src == '&')
       siz--;
    else if (*Src == '\t')
      for(Src++,siz++;*Src && Src;Src++,siz++);
        if (*Src == '\t')
            *Src = 32;
    if (*Src)
     { Src++; siz++; }
   }
  Src = Txt;
  Txt = (char*)NULL;
  Txt = new char [siz+1];
  siz    = 0;
  while(*Src)
   {
    for(;*Src && *Src != '&' && *Src != '\t'; Src++,siz++)
         Txt[siz] = *Src;
    if(*Src == '&')
     {
       Txt[siz] = *++Src;
       if (*Src != '&')
          Hot = siz;
     }
    else if (*Src == '\t')
     {
       Txt[siz] = '\0';
       ShortCut    = (char*)(Txt+siz+1);
     }
    if (*Src)
     {
      Src++;
      siz++;
     }
   }
   Txt[siz] = '\0';
   if (ShortCut ==(char*)NULL)
      ShortCut = (char*)Txt+siz;
   HotKey = StrToKey(ShortCut);
   Key    = UpCase(Txt[Hot]);
 }

class Nodes : public Event
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

   events ? (virtual)
     KeyDown
     MouseClick
     MouseMove
     Draw

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
