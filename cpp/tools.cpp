#ifndef __TOOL_H
#define __TOOL_H
#include <CuiBase.h>
#include <Events.h>


#define JustifyLeft   0x00
#define JustifyMid    0x01
#define JustifyRight  0x02

#define xJust(j,x,w,l)((j)==0) ? (x)+2:((j)==1) ? (x)+((w)-(l))/2:(x)+(w)-(l)-2;

#define ToolActive  0x01
#define ToolVisible 0x02
#define Colorised   0x0800
#define ToolState       0x04

// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>        Class Caption for maintaining Captions           <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

class Caption
 {
   public :
    char  *Txt;
    char  *ShortCut;
    byte  Hot;
    byte  Key;
    word  HotKey;

   Caption(char *Src);
   ~Caption();
   void Parse(byte x,byte y,byte coTxt,byte coTxtHi);
 };



// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>       Class Tool : ToolKit Base Class                   <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

class Tool //:public Event
 {
   protected :
     byte    X,Y,
             W,H;
     word    ToolID;
     Scheme  *cs;

   protected :
     void SetEventID(word ID);
   public :
     Tool();
     Tool(byte x,byte y,byte w,byte h);

     void SetOrigin (byte x,byte y);
     void SetSize   (byte w,byte h);
     void SetCaption(char *Cap);

     void Width (byte w);
     void Height(byte h);
     void AddColor(byte Txt,byte TxtHi,byte Xec,byte XecHi,byte Lck,byte Box);
     void AddColor(Scheme *Sch);
 };

class Label : public Tool
 {
   private :
     Caption *Cap;

   public :
     Label(word inf);
     Label(byte x,byte y,byte w,byte h,word inf);

     ~Label();

     void SetCaption(char *Src);
     bool ShowX();
     bool Show();
     //bool KeyDown(word Key);
 };
class  Check : public Tool
 {
   private :
     Caption *Cap;

   public :
     Check(word inf);
     Check(byte x,byte y,byte w,byte h,word inf);

     ~Check();

     void SetState(bool OnOff);
     void SetCaption(char *Src);
     bool Show();
     bool ShowX();
     //bool KeyDown(word Key);
 };
class  Radio : public Tool
 {
   private :
     Caption *Cap;

   public :
     Radio(word inf);
     Radio(byte x,byte y,byte w,byte h,word inf);

     ~Radio();

     void SetState(bool OnOff);
     void SetCaption(char *Src);
     bool Show();
     bool ShowX();
     //bool KeyDown(word Key);
 };
#define AllowNumeric   0x0010
#define AllowUpAlpha   0x0020
#define AllowLoAlpha   0x0040
#define AllowSpace     0x0080

class  TextBox: public Tool
 {
   private :
     char Text[256];
     byte Length;
     byte Cur;
     byte Strt;
     byte SelStart;
     byte SelLength;
   public :
     TextBox();
     TextBox(char *Src);

     bool KeyDown(word Key);
     void Draw();
     bool Show();
     bool Refresh  ();
     //bool GotFocus ();
     //bool LostFocus();
     virtual bool Change();
 };
class  IntBox : public Tool
 {
    private:
      int   Max,Min;
      char  Text[6];
      byte  Cur;
      byte  Length;
      byte SelStart;
      byte  SelLength;
    public :
      int   Value;

      IntBox();
      IntBox(int Val,int Mn,int Mx);

      void SetRange(int Mn,int Mx);
      bool KeyDown(word Key);
      void Draw();
      bool Show();
      bool Refresh  ();
      bool GotFocus ();
      bool LostFocus();
      virtual bool Change();
 };
class FloatBox : public Tool
 {
    private:
      float  Max,Min;
      char   Text[16];
      byte   Cur;
      byte   Length;
      byte SelStart;
      byte   SelLength;
      byte   DecN;
    public :
      float Value;

      FloatBox();
      FloatBox(float Val,float Mn,float Mx);

      void SetRange(float Mn,float Mx);
      bool KeyDown(word Key);
      void Draw();
      bool Show();
      bool Refresh  ();
      bool GotFocus ();
      bool LostFocus();
      virtual bool Change();
 };
extern Scheme CoolBlue,Classic,DarkNight,RedAlert,SoftGreen,SoftGray;
#endif

Scheme CoolBlue,Classic,DarkNight,RedAlert,SoftGreen,SoftGray;
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>          Caption :   Source Code                        <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

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
Caption::~Caption()
 {
   ShortCut = (char *)NULL;
   delete Txt;
 }
void Caption::Parse(byte x,byte y,byte coTxt,byte coTxtHi)
 {
   char *src;
   //byte pos=0;
   TxtAttr = coTxt;
   xPrintf(x,y,Txt);
   TxtAttr = coTxtHi;
   xPrintf(x+Hot,y,"%c",Txt[Hot]);
  /* for (src=Txt;*src != '\0';src++)
     if (pos > 0 && *(src-1) == '&')
        SetVidAt(++pos+X,Y,*src,coTxtHi);
     else if (src != '&')
        SetVidAt(++pos+X,Y,*src,coTxtHi);*/
 }

// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>         Tool  : Tool Source Code                        <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

void Tool::SetEventID(word ID)
 {
   word EventID; //temporary
   EventID  = ID&0x00FF;
   EventID |= (ID&0x00FF <  EventMenu ) ? HndlMenu :0;
   EventID |= (ID&0x00FF <= EventFrame) ? HndlEvent:0;
 }
Tool::Tool()
 {
  X=Y=W=H=0;
  cs = &DarkNight;
 }
Tool::Tool(byte x,byte y,byte w,byte h)
 {
   cs = &DarkNight;
   X = (x > GetMaxX()) ? 0:x;
   Y = (y > GetMaxY()) ? 0:y;
   W = (w+X > GetMaxX()) ? GetMaxX()-X:w;
   H = (h+Y > GetMaxY()) ? GetMaxY()-Y:h;
 }

void Tool::SetOrigin(byte x,byte y)
 {
   X = (x > GetMaxX()) ? 0:x;
   Y = (y > GetMaxY()) ? 0:y;
 }

void Tool::SetSize(byte w,byte h)
 {
   W = (w+X > GetMaxX()) ? GetMaxX()-X:w;
   H = (h+Y > GetMaxY()) ? GetMaxY()-Y:h;
 }
void Tool::Width(byte w)
 {
   H = (w+X > GetMaxX()) ? GetMaxX()-X:w;
 }
void Tool::Height(byte h)
 {
   H = (h+Y > GetMaxY()) ? GetMaxY()-X:h;
 }
void Tool::AddColor(byte Txt,byte TxtHi,byte Xec,byte XecHi,byte Lck,byte Box)
 {
   if (!(ToolID&Colorised))
    {
      cs      = new Scheme;
      ToolID ^= Colorised;
    }
   cs->Txt    = Txt;
   cs->TxtHi  = TxtHi;
   cs->Xec    = Xec;
   cs->XecHi  = XecHi;
   cs->Lck    = Lck;
   cs->Box    = Box;
 }
void Tool::AddColor(Scheme *Sch)
 {
   if (ToolID&Colorised)
    {
      delete cs;
      ToolID ^= Colorised;
    }
   cs = Sch;
 }


// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>               Class Label Source Code                   <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

Label::Label(word inf)
 {
   SetEventID(EventLabel);
   ToolID = inf;
 }
Label::Label(byte x,byte y,byte w,byte h,word inf)
        :Tool(x,y,w,h)
 {
   SetEventID(EventLabel);
   ToolID = inf;
 }
Label::~Label()
 {
   delete Cap;
 }
bool Label::ShowX()
 {
   byte x = (ToolID&0xC000)>>14;

   if (Cap)
    {
      x = xJust(x,Vp.X+X,W,min(strlen(Cap->Txt),W-4));
      TxtAttr = cs->Txt;
      FillChr(Vp.X+X,Vp.Y+Y,W,H,Blank);
      //xPrintf(x,Vp.Y+Y,Cap->Txt);
      //TxtAttr = cs->TxtHi;
      //xPrintf(x+Cap->Hot,Y,"%c",Cap->Txt[Cap->Hot]);
      Cap->Parse(x,Vp.Y+Y,cs->Txt,cs->TxtHi);
    }
   return true;
 }
bool Label::Show()
 {
  return ShowX();
 }
void Label::SetCaption(char *Src)
 {
   if (Cap != (Caption*)NULL)
      delete Cap;
   Cap    = new Caption(Src);
   //HotKey = StrToKey(Cap->ShortCut);
 }



Check::Check(word inf)
 {
   SetEventID(EventCheck);
   ToolID = inf;
 }
Check::Check(byte x,byte y,byte w,byte h,word inf)
        :Tool(x,y,w,h)
 {
   SetEventID(EventCheck);
   ToolID = inf;
 }
Check::~Check()
 {
   delete Cap;
 }
bool Check::ShowX()
 {
   if (Cap)
    {
      TxtAttr = cs->Txt;
      FillChr(Vp.X+X,Vp.Y+Y,W,H,Blank);
      xPrintf(Vp.X+X,Vp.Y+Y,"[ ]",Cap->Txt);
      //TxtAttr = cs->TxtHi;
      //xPrintf(X+5+Cap->Hot,Y,"%c",Cap->Txt[Cap->Hot]);
      Cap->Parse(Vp.X+X+4,Vp.Y+Y,cs->Txt,cs->TxtHi);
      xPrintf(Vp.X+X+1,Vp.Y+Y,"%c",(ToolID&ToolState) ? Tick:Blank);
    }
   return true;
 }
bool Check::Show()
 {
  return ShowX();
 }
void Check::SetCaption(char *Src)
 {
   if (Cap != (Caption*)NULL)
      delete Cap;
   Cap    = new Caption(Src);
//   HotKey = StrToKey(Cap->ShortCut);
 }
void Check::SetState(bool OnOff)
 {
   ToolID &= 0xFFFB;
   ToolID |= (OnOff) ? ToolState:0x0000;
 }
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>               Class Radio : Modules                   <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>


Radio::Radio(word inf)
 {
   SetEventID(EventRadio);
   ToolID = inf;
 }
Radio::Radio(byte x,byte y,byte w,byte h,word inf)
        :Tool(x,y,w,h)
 {
   SetEventID(EventRadio);
   ToolID = inf;
 }
Radio::~Radio()
 {
   delete Cap;
 }
bool Radio::ShowX()
 {
   if (Cap)
    {
      TxtAttr = cs->Txt;
      FillChr(Vp.X+X,Vp.Y+Y,W,H,Blank);
      xPrintf(Vp.X+X,Vp.Y+Y,"( )",Cap->Txt);
      Cap->Parse(Vp.X+X+4,Vp.Y+Y,cs->Txt,cs->TxtHi);
      //TxtAttr = cs->TxtHi;
      //xPrintf(X+4+Cap->Hot,Y,"%c",Cap->Txt[Cap->Hot]);
      xPrintf(Vp.X+X+1,Vp.Y+Y,"%c",(ToolID&ToolState) ? Sphere:Blank);
    }
   return true;
 }
bool Radio::Show()
 {
  return ShowX();
 }

void Radio::SetCaption(char *Src)
 {
   if (Cap != (Caption*)NULL)
      delete Cap;
   Cap    = new Caption(Src);
//   HotKey = StrToKey(Cap->ShortCut);
 }
void Radio::SetState(bool OnOff)
 {
   SetEventID(EventTxtBox);
   ToolID &= 0xFFFB;
   ToolID |= (OnOff) ? ToolState:0x0000;
 }

bool TextEdit(word Key,char *Txt,byte& Cur,byte&SelStart,byte& SelLength)
 {
   bool rvHndl = true;
   byte Len = strlen(Txt);

   if (Key==InsKy)
    {
     if (KbdFlagWord()&InsertOn)
        SetCurType(Cursor02);
     else
        SetCurType(FullBlkCur);
    }
   else if (Len > 0)
    {
      if (Key == DelKy)
        if (SelLength == 0)
	   memcpy(Txt+Cur,Txt+Cur+1,Len-Cur);
        else
         {
           memcpy(Txt+SelStart,Txt+SelStart+SelLength,Len-SelStart-SelLength+1);
           Cur = SelStart;
           SelLength = 0;
         }
      else if (Key == BackSp)
       {
        if (Cur > 0 )
         {
          if (Cur == Len)
	    Txt[Cur-1] = '\0';
          else
	    memcpy(Txt+Cur-1,Txt+Cur,Len-Cur+1);
            Cur--;
         }
       }
      else if (Key == Ctrl_T)
       {
         Len=Cur;
         while(Txt[Len] != ' ' && Txt[Len] != '\t' && Txt[Len] != '\0')  Len++;
         while(Txt[Len] == ' ' || Txt[Len] == '\t' && Txt[Len] != '\0')  Len++;
         memcpy(Txt+Cur,Txt+Len,strlen(Txt)-Len+Cur);
       }
      else if (Key == LtArr)
        Cur = (Cur > 0  ) ? Cur-1:0  ;
      else if (Key == RtArr)
        Cur = (Cur < Len) ? Cur+1:Cur;
      else if (Key == HomeKey)
        Cur = 0  ;
      else if (Key == EndKey)
        Cur = Len;
      else if (Key == Ctrl_RtArr || Key == Ctrl_F)
       {
        while(Txt[Cur] != ' ' && Txt[Cur] != '\t' && Txt[Cur] != '\0')  Cur++;
        while(Txt[Cur] == ' ' || Txt[Cur] == '\t' && Txt[Cur] != '\0')  Cur++;
       }
      else if (Key == Ctrl_LtArr || Key == Ctrl_A)
       {
        if (Cur > 0 && (Txt[Cur-1] == ' ' || Txt[Cur-1] == '\t'))  Cur--;
        if (Txt[Cur] == ' ' || Txt[Cur] == '\t')
       	  while(Txt[Cur] == ' ' || Txt[Cur] == '\t' && Cur > 0)  Cur--;
        while(Txt[Cur] != ' ' && Txt[Cur] != '\t' && Cur > 0)  Cur--;
        if (Txt[Cur] == ' ' || Txt[Cur] == '\t' && Cur < strlen(Txt))  Cur++;
       }
      else if (Key == Shft_RtArr)
       {
        if (Cur < Len)
         {
          if (SelLength > 0 && SelStart==Cur)
           {
            --SelLength;
            ++SelStart;
           }
          else
           {
            if (Cur < SelStart || Cur-SelStart > SelLength)
               SelLength = 0;
            else if (SelLength > 0)
               SelLength = Cur-SelStart;
            SelLength = SelLength+1;
            SelStart  = Cur-SelLength+1;
           }
          Cur++;
         }
       }
      else if (Key == Shft_LtArr)
       {
        if (Cur > 0)
         {
          if (SelLength > 0 && Cur == SelStart+SelLength)
             SelLength = SelLength -1;
          else
           {
            if (Cur < SelStart || Cur-SelStart > SelLength)
               SelLength = 0;
            else
               SelLength = SelStart+SelLength - Cur;
            SelLength = SelLength + 1;
            SelStart = Cur-1;
           }
          Cur = Cur-1;
         }
       }
      else if (Key == Shft_Home)
       {
         SelStart = 0;
         SelLength = Cur-SelStart;
         Cur = 0;
       }
      else if (Key == Shft_End)
       {
         SelStart = Cur;
         Cur = Len;
         SelLength = Cur-SelStart;
       }
      else rvHndl = false;
    }

   return rvHndl;
 }
TextBox::TextBox()
 {
   SetEventID(EventTxtBox);
   Text[0]   = '\0';
   Length    = 0;
   Strt      = 0;
   Cur       = 0;
   SelStart  = 0;
   SelLength = 0;
 }
TextBox::TextBox(char *Src)
 {
   SetEventID(EventIntBox);
   strcpy(Text,Src);
   Length  = strlen(Src);
   Strt    = 0;
   Cur     = 0;
   SelStart = 0;
   SelLength = 0;
 }
bool TextBox::KeyDown(word Key)
 {
   bool rvHndl;
   byte i;
   rvHndl = true;
   if (Key < 0xFF && Key != BackSp && Key != TabKy && Key != RetKy)
    {
      //rvHndl = (bool)           (ToolID&AllowNumeric && !(Key < '0' || Key > '9'));
      //rvHndl = (bool)(rvHndl && (ToolID&AllowUpAlpha && !(Key < 'A' || Key > 'Z')));
      //rvHndl = (bool)(rvHndl && (ToolID&AllowLoAlpha && !(Key < 'a' || Key > 'z')));
      //rvHndl = (bool)(rvHndl && (ToolID&AllowSpace  && Key == ' '));
      if (rvHndl)
       {
	/*if (SelLength > 0)
	{
	 memcpy(Text+Cur,Text+Cur+SelLength,strlen(Text)-SelLength-Cur);
	 SelLength = 0;
	} */
	if (KbdFlagWord()&InsertOn)
	 {
          if (Cur < strlen(Text))
           {
             Length = strlen(Text);
	     for (i=Length+1;i > Cur;i--)
	      Text[i] = Text[i-1];
	     Text[Cur] = Key;
             Cur++;
           }
          else
           {
            Text[Cur] = Key;
            Text[++Cur] = '\0';
           }
          }
         else if (Cur < strlen(Text))
           Text[Cur++] = Key;
        //Cur++;
//	Change();
       }
    }
   else
     rvHndl = TextEdit(Key,Text,Cur,SelStart,SelLength);

   if (rvHndl) Draw();
   return rvHndl;
 }
void TextBox::Draw()
 {
   char *tmp;
   tmp = new char[SelLength+1];
   TxtAttr = cs->Txt;
   FillChr(X,Y,W,H,Blank);
   xPrintf(X,Y,Text);
   xPrintf(20,20,Text);
   memcpy(tmp,Text+SelStart,SelLength);
   tmp[SelLength] = '\0';
   TxtAttr = cs->Xec;
   //FillChr(X+Cur,Y,SelLength,H,Blank);
   xPrintf(X+SelStart,Y,tmp);
   SetCurPos(DrwPg,X+Cur,Y);
 }
bool TextBox::Show()
 {
  Draw();
  return true;
 }
bool TextBox::Refresh()
 {
  Draw();
  return true;
 }
bool TextBox::Change() { return false;}

IntBox::IntBox()
 {
   SetEventID(EventIntBox);
   Min    = -32768;
   Max    = +32767;
   Value  = 0;
   Cur    = 5;
   Length = 6;
   SelStart = 0;
   SelLength = 0;
   itoa(Value,Text,10);
 }
IntBox::IntBox(int Val,int Mn,int Mx)
 {
   SetEventID(EventIntBox);
   Min    = min(Mn,Mx);
   Max    = max(Mn,Mx);
   Value  = (Val >=Min && Val <= Max) ? Val :Min;
   Cur    = 5;
   Length = strlen(itoa(Max,Text,10));
   Length = max(Length,strlen(itoa(Min,Text,10)));
   SelStart = 0;
   SelLength = 0;
   itoa(Value,Text,10);
 }
void IntBox::SetRange(int Mn,int Mx)
 {
   Min    = min(Mn,Mx);
   Max    = max(Mn,Mx);
   Value  = (Value >=Min && Value <= Max) ? Value:Min;
   Length = strlen(itoa(Max,Text,10));
   Length = max(Length,strlen(itoa(Min,Text,10)));
   SelStart = 0;
   SelLength = 0;
   itoa(Value,Text,10);
 }
void IntBox::Draw()
 {
   xPrintf(X,Y+W-strlen(Text),Text);
 }

bool IntBox::KeyDown(word Key)
 {
   bool rvHndl;
   char Txt[6];
   byte i;
   strcpy(Txt,Text);
   rvHndl = true;
   if (Key >= '0' && Key <= '9')
    {
     if (Key > '0' || ((Cur > 0) || (Cur>1 && Txt[0] == '-')))
      {
       if (SelLength > 0)
	{
         memcpy(Txt+Cur,Txt+Cur+SelLength,strlen(Txt)-SelLength-Cur);
         SelLength = 0;
        }
       if (KbdFlagWord()&InsertOn)
        {
         for (i=Cur;i < Length+1;i++)
            Txt[i+1] = Txt[i];
         Txt[Cur] = Key;
         Change();
        }
      else
        Txt[Cur] = Key;
     }
    }
   else if (Key == '+' && Value < 0)
     itoa(-Value,Txt,10);
   else if (Key == '-' && Value > 0)
     itoa(-Value,Txt,10);
   else
     rvHndl = TextEdit(Key,Txt,Cur,SelStart,SelLength);
/*   else if (Key == Shft_RtArr && SelLength+Cur < strlen(Text))
      SelLength++;
   else if (Key == Shft_LtArr && Cur > 0)
    {
     Cur = Cur -1;
     SelLength = SelLength + 1;
     Draw();
    }
   else if (Key == DelKy)
    {
     if (SelLength == 0) SelLength = 1;
     memcpy(Txt+Cur,Txt+Cur+SelLength,strlen(Txt)-SelLength-Cur);
     SelLength = 0;
    }
   else if (Key == BackSp && Cur > 0)
     memcpy(Txt+Cur-1,Txt+Cur,Length-Cur);
   else if (Key == LtArr)
     Cur = (Cur > 0) ? Cur-1:Cur;
   else if (Key == RtArr)
     Cur = (Cur < Length) ? Cur+1:Cur;
   else
     rvHndl = false;*/
   if (rvHndl)
    {
      Value = atoi(Txt);
      if (!(Value < Min || Value > Max))
	 strcpy(Text,Txt);
      Value = atoi(Text);
      xPrintf(X,Y+W-strlen(Text),Text);
      SetCurPos(DrwPg,X+Cur,Y);
    }
   return rvHndl;
 }
bool IntBox::GotFocus()
 {
   SetCurType((KbdFlagWord()&InsertOn) ? Cursor02:FullBlkCur);
   return true;
 }
bool IntBox::LostFocus()
 {
   SetCurType(NullCursor);
   return true;
 }

bool IntBox::Show()
 {
   Draw();
   return true;
 }
bool IntBox::Refresh()
 {
   Draw();
   return true;
 }

bool IntBox::Change() {return false;}
FloatBox::FloatBox()
 {
   SetEventID(EventFloatBox);
   Min    = -32768;
   Max    = +32767;
   Value  = 0;
   Cur    = 5;
   SelStart = 0;
   SelLength = 0;
   Length = strlen(gcvt(Max,DecN,Text));
   Length = max(Length,strlen(gcvt(Min,DecN,Text)));
   gcvt(Value,DecN,Text);
 }
FloatBox::FloatBox(float Val,float Mn,float Mx)
 {
   SetEventID(EventFloatBox);
   Min    = min(Mn,Mx);
   Max    = max(Mn,Mx);
   Value  = (Val >=Min && Val <= Max) ? Val :Min;
   Cur    = 5;
   SelStart = 0;
   SelLength = 0;
   Length = strlen(gcvt(Max,DecN,Text));
   Length = max(Length,strlen(gcvt(Min,DecN,Text)));
   gcvt(Value,DecN,Text);
 }
void FloatBox::SetRange(float Mn,float Mx)
 {
   Min    = min(Mn,Mx);
   Max    = max(Mn,Mx);
   Value  = (Value >=Min && Value <= Max) ? Value:Min;
   SelStart = 0;
   SelLength = 0;
   Length = strlen(gcvt(Max,DecN,Text));
   Length = max(Length,strlen(gcvt(Min,DecN,Text)));
   gcvt(Value,DecN,Text);
 }
void FloatBox::Draw()
 {
   xPrintf(X,Y+W-strlen(Text),Text);
 }

bool FloatBox::KeyDown(word Key)
 {
   bool rvHndl;
   char Txt[6];
   byte i;
   strcpy(Txt,Text);
   rvHndl = true;
   if (Key >= '0' && Key <= '9')
    {
     if (Key > '0' || ((Cur > 0) || (Cur==1 && Txt[0] == '-')))
      {
       if (SelLength > 0)
        {
         memcpy(Txt+Cur,Txt+Cur+SelLength,strlen(Txt)-SelLength-Cur);
         SelLength = 0;
        }
       if (KbdFlagWord()&InsertOn)
        {
         for (i=Cur;i < Length+1;i++)
            Txt[i+1] = Txt[i];
         Txt[Cur] = Key;
         Change();
        }
       else
        Txt[Cur] = Key;
      }
    }
   else if (Key == '+' && Value < 0)
     gcvt(-Value,DecN,Text);
   else if (Key == '-' && Value > 0)
     gcvt(-Value,DecN,Text);
   else
     rvHndl = TextEdit(Key,Txt,Cur,SelStart,SelLength);
/*   else if (Key == Shft_RtArr && SelLength+Cur < strlen(Text))
      SelLength++;
   else if (Key == Shft_LtArr && Cur > 0)
    {
     Cur = Cur -1;
     SelLength = SelLength + 1;
     Draw();
    }
   else if (Key == DelKy)
    {
     if (SelLength == 0) SelLength = 1;
     memcpy(Txt+Cur,Txt+Cur+SelLength,strlen(Txt)-SelLength-Cur);
     SelLength = 0;
    }
   else if (Key == BackSp && Cur > 0)
     memcpy(Txt+Cur-1,Txt+Cur,Length-Cur);
   else if (Key == LtArr)
     Cur = (Cur > 0) ? Cur-1:Cur;
   else if (Key == RtArr)
     Cur = (Cur < Length) ? Cur+1:Cur;

   else
     rvHndl = false;*/
   if (rvHndl)
    {
      Value = atof(Txt);
      if (!(Value < Min || Value > Max))
         strcpy(Text,Txt);
      Value = atof(Text);
      xPrintf(X,Y+W-strlen(Text),Text);
      SetCurPos(DrwPg,X+Cur,Y);
    }
   return rvHndl;
 }
bool FloatBox::GotFocus()
 {
   SetCurType((KbdFlagWord()&InsertOn) ? Cursor02:FullBlkCur);
   return true;
 }
bool FloatBox::LostFocus()
 {
   SetCurType(NullCursor);
   return true;
 }

bool FloatBox::Show()
 {
   Draw();
   return true;
 }
bool FloatBox::Refresh()
 {
   Draw();
   return true;
 }

bool FloatBox::Change() {return false;}