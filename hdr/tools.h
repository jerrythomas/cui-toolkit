#ifndef __TOOL_H
#define __TOOL_H
#include <cuibase.h>
#include <events.h>


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

class Tool :public Event
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
