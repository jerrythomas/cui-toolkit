#include <Tool.h>
#define LbJustify  0xC0
#define LbJustShft 14
#define State 0x0004

class Check : public Tool
 {
   private :
     word    swCheck;
     word    HotKey;
     Caption *Cap;

   public :
     Check(word inf);
     Check(byte x,byte y,byte w,byte h,word inf);

     ~Check();

     void SetState(bool OnOff);
     void SetCaption(char *Src);
     bool Show();
     //bool KeyDown(word Key);
 };

Check::Check(word inf)
 {
   ToolID  = Check_Tool;
   swCheck = inf;
   cs = &Classic;
 }
Check::Check(byte x,byte y,byte w,byte h,word inf)
        :Tool(x,y,w,h)
 {
   ToolID  = Check_Tool;
   swCheck = inf;
   cs = &CoolBlue;
 }
Check::~Check()
 {
   delete Cap;
 }
bool Check::Show()
 {
   if (Cap)
    {
      TxtAttr = cs->Txt;
      FillChr(X,Y,X+W-1,Y+H-1,Blank);
      xPrintf(X,Y,"[ ] %s",Cap->Prompt);
      TxtAttr = cs->TxtHi;
      xPrintf(X+5+Cap->Hot,Y,"%c",Cap->Prompt[Cap->Hot]);
      xPrintf(X+1,Y,"%c",(swCheck&State) ? Tick:Blank);
    }
   return true;
 }
void Check::SetCaption(char *Src)
 {
   if (Cap != (Caption*)NULL)
      delete Cap;
   Cap    = new Caption(Src);
   HotKey = StrToKey(Cap->ShortCut);
 }
void Check::SetState(bool OnOff)
 {
   swCheck &= 0xFFFB;
   swCheck |= (OnOff) ? State:0x0000;
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

   Check F(0,0,11,1,0x0000);
   Check f1(12,0,10,1,0x4001);
   Check f2(23,0,11,1,0x4002);
   Check f3(35,0,10,1,0x4003);
   ModeSearch(Txt80x25x16x8);
   F.SetCaption("&Jerry\tAlt+J");
   f1.SetCaption("&is");
   f2.SetCaption("&testing");
   f3.SetCaption("Checks");
   F.Show();
   f1.SetState(On);
   f1.Show();
   f2.Show();
   f3.Show();

   GetKey();
   return 0;
 }