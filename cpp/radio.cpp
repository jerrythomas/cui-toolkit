#include <Tool.h>
#define LbJustify  0xC0
#define LbJustShft 14
#define State 0x0004

class Radio : public Tool
 {
   private :
     word    swRadio;
     word    HotKey;
     Caption *Cap;

   public :
     Radio(word inf);
     Radio(byte x,byte y,byte w,byte h,word inf);

     ~Radio();

     void SetState(bool OnOff);
     void SetCaption(char *Src);
     bool Show();
     //bool KeyDown(word Key);
 };

Radio::Radio(word inf)
 {
   ToolID  = Radio_Tool;
   swRadio = inf;
   cs = &Classic;
 }
Radio::Radio(byte x,byte y,byte w,byte h,word inf)
        :Tool(x,y,w,h)
 {
   ToolID  = Radio_Tool;
   swRadio = inf;
   cs = &CoolBlue;
 }
Radio::~Radio()
 {
   delete Cap;
 }
bool Radio::Show()
 {
   if (Cap)
    {
      TxtAttr = cs->Txt;
      FillChr(X,Y,X+W-1,Y+H-1,Blank);
      xPrintf(X,Y,"( ) %s",Cap->Prompt);
      TxtAttr = cs->TxtHi;
      xPrintf(X+4+Cap->Hot,Y,"%c",Cap->Prompt[Cap->Hot]);
      xPrintf(X+1,Y,"%c",(swRadio&State) ? Sphere:Blank);
    }
   return true;
 }
void Radio::SetCaption(char *Src)
 {
   if (Cap != (Caption*)NULL)
      delete Cap;
   Cap    = new Caption(Src);
   HotKey = StrToKey(Cap->ShortCut);
 }
void Radio::SetState(bool OnOff)
 {
   swRadio &= 0xFFFB;
   swRadio |= (OnOff) ? State:0x0000;
 }
main()
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

   Radio F(0,0,11,1,0x0000);
   Radio f1(12,0,10,1,0x4001);
   Radio f2(23,0,11,1,0x4002);
   Radio f3(35,0,10,1,0x4003);
   ModeSearch(Txt80x25x16x8);
   F.SetCaption("&Jerry\tAlt+J");
   f1.SetCaption("&is");
   f2.SetCaption("&testing");
   f3.SetCaption("Radios");
   F.Show();
   f1.SetState(On);
   f1.Show();
   f2.Show();
   f3.Show();

   GetKey();
   return 0;
 }