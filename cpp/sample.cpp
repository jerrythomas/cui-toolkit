#include <Form.h>
Scheme *S;
//,SoftGray,DarkNight;

byte WhichColor(int i,int j)
 {
  word Key=0;

  SetVidAt(0,50+i,7+j,'x',(i<<4)^j);
  do
   {
     Key = GetKey();
     SetVidAt(0,50+i,7+j,' ',(i<<4)^j);
     switch(Key)
      {
       case LtArr : i = (i+15)%16;break;
       case RtArr : i = (i+1)%16;break;
       case UpArr : j = (j+15)%16;break;
       case DnArr : j = (j+1)%16;break;
      }
     SetVidAt(0,50+i,7+j,'x',(i<<4)^j);
   }
  while (Key != RetKy && Key != SpcKy && Key != EscKy);
  SetVidAt(0,50+i,7+j,' ',(i<<4)^j);
  return (i<<4)^j;
 }
void SetTxt()
 {
   S->Txt = WhichColor(S->Txt>>4,S->Txt&0x0F);
 }
void SetTxtHi()
 {
   S->TxtHi = WhichColor(S->TxtHi>>4,S->TxtHi&0x0F);
 }
void SetXec()
 {
   S->Xec = WhichColor(S->Xec>>4,S->Xec&0x0F);
 }
void SetXecHi()
 {
   S->XecHi = WhichColor(S->XecHi>>4,S->XecHi&0x0F);
 }
void SetLck()
 {
   S->Lck = WhichColor(S->Lck>>4,S->Lck&0x0F);
 }
void SetBox()
 {
   S->Box = WhichColor(S->Box>>4,S->Box&0x0F);
 }

main()
 {
  //ModeSearch(Txt80x25x16x8);
  Menu M(MenuHz|MainAppMenu,7),
       K(SlideRtDnMenuVt^HSVDBoxShadow,9);
  StartMouse();
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
  DarkNight.Xec   = SetTxtCol(Brown,White);
  DarkNight.XecHi = SetTxtCol(Brown,LightGreen);
  DarkNight.Lck   = SetTxtCol(Black,DarkGray);
  DarkNight.Box   = SetTxtCol(Black,White);

  SetCurType(NullCursor);
//  SetBorderCol(White);
  S = &DarkNight;
  TglBlink(Off);
  M.AddColor(&DarkNight);
	//M.AddMenu(MenuVt,3);
     K.AddPad("Locked",ActiveRadio);
     K.AddPad("Break",ActiveRadio);
     K.AddPad("Active",ActiveRadioOn);
     K.AddPad(" ",MenuBreak);
     K.AddPad("Break",ActiveRadio);
     K.AddPad("Active",ActiveRadioOn);
     K.AddPad("",MenuBreak);
     K.AddPad("Break",ActiveRadioOn);
     K.AddPad("Active",ActiveRadio);

  M.AddPad("&File\tAlt F",ActivePad,"Opens File Options SubMenu");
    M.AddMenu(SlideDnMenuVt|HSVDBoxShadow,8);
      M.AddPad("&New"      ,ActivePad,"Creates a new file");
      M.AddPad("&Open \tF3",ActivePad,"Opens an existing file");
	M.AddMenu(SlideDnMenuVt^HSVDBoxShadow,3);
	  M.AddPad("Locked",ActivePad);
	  M.AddPad("Break",ActivePad);
	  M.AddPad("Active",ActiveCheckOn);
      M.AddPad(" "        ,MenuBreak);
      M.AddPad("&Save"    ,ActivePad);
      M.AddPad("&Copy"    ,LockedPad);
      M.AddPad("&Print"   ,ActivePad);
      M.AddPad(" "        ,MenuBreak);
      M.AddPad("E&xit \tAlt X",ActivePad);

  M.AddPad("&Sort\tAlt S",ActivePad);
    M.AddMenu(&K);

  M.AddPad("&Options\tAlt O",ActivePad);
    M.AddMenu(SlideRtDnMenuVt|HSVDBoxShadow,5);
      M.AddPad("&Mode",ActivePad);
      M.AddPad("&Colors",ActivePad);
      M.AddPad("&Environment",ActivePad);
      M.AddPad("",MenuBreak);
      M.AddPad("&Save Settings",ActivePad);
  M.AddPad("&Color\tAlt C",ActivePad);
    M.AddMenu(SlideRtDnMenuVt|HSVDBoxShadow,6);
      M.AddPad("&Txt",ActivePad,SetTxt);
      M.AddPad("&TxtHi",ActivePad,SetTxtHi);
      M.AddPad("&Xec",ActivePad,SetXec);
      M.AddPad("XecHi",ActivePad,SetXecHi);
      M.AddPad("&Lck",ActivePad,SetLck);
      M.AddPad("&Box",ActivePad,SetBox);
      M.AddPad("",MenuBreak);
  M.AddPad("&Window\tAlt W",ActivePad);
    M.AddMenu(SlideLtDnMenuVt|HSVDBoxShadow,10);
      M.AddPad("&Next\tF6"           ,ActivePad,
				  "Switches to next active window");
      M.AddPad("&Size/Move \tCtrl F5",ActivePad,
				  "Resize or move current window");
      M.AddPad("&Zoom\tF5"           ,ActivePad,
				  "Maximises the current window");
      M.AddPad("&Iconify"            ,ActivePad,
				  "Iconifies the current window");
      M.AddPad("",MenuBreak);
      M.AddPad("C&lose",ActivePad);
      M.AddPad("Close &All",ActivePad);
      M.AddPad("",MenuBreak);
      M.AddPad("&Dock",ActivePad);
      M.AddPad("&Cascade",ActivePad);

      M.AddPad("&Help\tAlt H",ActivePad);
	M.AddMenu(SlideLtDnMenuVt|HSVDBoxShadow,4);
	  M.AddPad("&Contents",ActivePad);
	    M.AddPad("&Index",ActivePad);
	    M.AddPad(" "      ,MenuBreak);
	    M.AddPad("&About",ActivePad);

  M.EndMenu();

      TxtAttr=SetTxtCol(DarkGray,LightGray);
      FillChr(0,0,GetMaxX(),GetMaxY(),CloseDot);
        for (int i=0;i<16;i++)
         for (int j=0;j<16;j++)
           SetVidAt(0,50+i,7+j,' ',(i<<4)^j);

  M.Show();
  word Key=0;
  do
   {
    Key = GetKey();
    M.KeyDown(Key);
   }
  while (Key != Alt_X);
  FillChr(0,0,Screen.Width,Screen.Height,Blank);
  SetCurPos(0,0,0);
  SetCurType(Cursor01);
  CloseMouse();
  return 0;
 }