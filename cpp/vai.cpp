//#include <kbd.h>
//#include <Vdu.h>
#include <Mouse.h>
#include <CuiBase.h>
#include <stdlib.h>
#include <dos.h>

VgaInf va;
//void interrupt far *OldKbdVec(...);
#define NoOfScanLn(N)  ((N)==0)? 200:((N)==1)?350:((N)==2)?400:((N)==3)?480:0
#define AvlblScanLns(N) ((N)&4)? 400:((N)&2) ?350:((N)&1) ?200:0
#define VidMem(M) ((M)+1)*64

void MiscBIOSInf(byte X,byte Y)
 {
  TxtAttr=SetTxtCol(Cyan,Green);
  FillChr(X+1,Y+1,41,12,Blank);
  DrawBox(X,Y,X+42,Y+13,1);
  xPrintf(X+10,Y," ");
  xPrintf(X+10,Y,"[Misc BIOS Capability]");

  TxtAttr=SetTxtCol(Cyan,LightGreen);
  xPrintf(X+3,Y+ 1,"[ ] All Modes Active");
  xPrintf(X+3,Y+ 2,"[ ] Gray Scale Summing");
  xPrintf(X+3,Y+ 3,"[ ] Character Font Loading");
  xPrintf(X+3,Y+ 4,"[ ] Mode Set Default Pallette Load");
  xPrintf(X+3,Y+ 5,"[ ] Cursor Emulation");
  xPrintf(X+3,Y+ 6,"[ ] EGA (64 Colour) Pallette");
  xPrintf(X+3,Y+ 7,"[ ] Color Register Load");
  xPrintf(X+3,Y+ 8,"[ ] Color Register Paging Mode Select");
  xPrintf(X+3,Y+ 9,"[ ] Light Pen");
  xPrintf(X+3,Y+10,"[ ] Save/Restore Video State");
  xPrintf(X+3,Y+11,"[ ] Intensity/Blink Control");
  xPrintf(X+3,Y+12,"[ ] Get/Set Display Combination Code");

  TxtAttr = SetTxtCol(Cyan,Red);
  for (int i=1;i< 13;i++)
   xPrintf(X+4,Y+i,"%c",(va.V->MiscBIOSCpbl&(1<<i)) ? Tick:'X');
 }
void SaveAreaInf(byte X,byte Y)
 {
  TxtAttr=SetTxtCol(Cyan,Green);
  FillChr(X+1,Y+1,38,6,Blank);
  DrawBox(X,Y,X+39,Y+7,1);
  xPrintf(X+10,Y,"Save area Capabilities]");

  TxtAttr=SetTxtCol(Cyan,LightGreen);
  xPrintf(X+3,Y+ 1,"[ ] Supports 512 Character Sets");
  xPrintf(X+3,Y+ 2,"[ ] Dynamic Save Area");
  xPrintf(X+3,Y+ 3,"[ ] Alpha Font Override");
  xPrintf(X+3,Y+ 4,"[ ] Graphics Font Override");
  xPrintf(X+3,Y+ 5,"[ ] Pallette Override");
  xPrintf(X+3,Y+ 6,"[ ] DCC Extension");

  TxtAttr = SetTxtCol(Cyan,Red);
  for (int i=1;i< 7;i++)
   xPrintf(X+4,Y+i,"%c",(va.V->SaveAreaCpbl&(1<<i)) ? Tick:'X');
 }
void SavePtrState(byte X,byte Y)
 {
  TxtAttr=SetTxtCol(Cyan,Green);
  FillChr(X+1,Y+1,38,6,Blank);
  DrawBox(X,Y,X+39,Y+7,1);
  xPrintf(X+11,Y,"[Save Ptr State Info]");

  TxtAttr=SetTxtCol(Cyan,LightGreen);
  xPrintf(X+3,Y+ 1,"[ ] Supports 512 Character Sets");
  xPrintf(X+3,Y+ 2,"[ ] Dynamic Save Area");
  xPrintf(X+3,Y+ 3,"[ ] Alpha Font Override");
  xPrintf(X+3,Y+ 4,"[ ] Graphics Font Override");
  xPrintf(X+3,Y+ 5,"[ ] Pallette Override");
  xPrintf(X+3,Y+ 6,"[ ] DCC Extension");

  TxtAttr = SetTxtCol(Cyan,Red);
  for (int i=1;i< 7;i++)
   xPrintf(X+4,Y+i,"%c",(va.SavePtrStateInf&(1<<i)) ? Tick:'X');
 }
void OthStateInf(byte X,byte Y)
 {
  TxtAttr=SetTxtCol(Cyan,Green);
  FillChr(X+1,Y+1,38,6,Blank);
  DrawBox(X,Y,X+39,Y+7,1);
  xPrintf(X+9,Y,"[Misc State Information]");

  TxtAttr=SetTxtCol(Cyan,LightGreen);
  xPrintf(X+3,Y+ 1,"[ ] Modes on All Displays Active");
  xPrintf(X+3,Y+ 2,"[ ] Gray Scale Summing");
  xPrintf(X+3,Y+ 3,"[ ] MonoChrome Display");
  xPrintf(X+3,Y+ 4,"[ ] Mode Set Default Pallette Load");
  xPrintf(X+3,Y+ 5,"[ ] Cursor Emulation");
  xPrintf(X+3,Y+ 6,"[ ] Intensity/Blink Control");

  TxtAttr = SetTxtCol(Cyan,Red);
  for (int i=1;i< 7;i++)
   xPrintf(X+4,Y+i,"%c",(va.MiscStateInf&(1<<i)) ? Tick:'X');
 }
void CursorInf(byte X,byte Y)
 {
  TxtAttr=SetTxtCol(Cyan,Green);
  FillChr(X+1,Y+1,41,7,Blank);
  DrawBox(X,Y,X+42,Y+8,1);
  DrawLineHz(X,Y+3,X+42,1);
  xPrintf(X+11,Y,"[Cursor Information]");

  TxtAttr=SetTxtCol(Cyan,LightGreen);
  xPrintf(X+3,Y+ 1,"Start Scan Line  [   ]");
  xPrintf(X+3,Y+ 2,"End Scan Line    [   ]");
  xPrintf(X+12,Y+ 3,"[Cursor Positions]");
  for (int i=0;i< 8;i++)
    xPrintf(X+(i%2)*20+3,Y+4+i/2,"Page %1d  [   ][  ]",i);

  TxtAttr = SetTxtCol(Cyan,Red);
  xPrintf(X+22,Y+1,"%2d",va.CurStrtScanLn);
  xPrintf(X+22,Y+2,"%2d",va.CurEndScanLn);
  for (i=0;i< 8;i++)
   {
    xPrintf(X+(i%2)*20+12,Y+i/2+4,"%3d",va.Page[i].x);
    xPrintf(X+(i%2)*20+17,Y+i/2+4,"%2d",va.Page[i].y);
   }
 }
void VideoInf(byte X,byte Y)
 {
  TxtAttr=SetTxtCol(DarkGray,White);
  FillChr(X+1,Y+1,39,23,Blank);
  DrawBox(X,Y,X+40,Y+22,1);
  xPrintf(X+10,Y,"[Video Information]");

  TxtAttr=SetTxtCol(DarkGray,White);
  xPrintf(X+3,Y+ 1,"Current Video Mode             [  ]");
  xPrintf(X+3,Y+ 2,"Number Of Pages                [  ]");
  xPrintf(X+3,Y+ 3,"Number Of Rows                 [  ]");
  xPrintf(X+3,Y+ 4,"Number Of Columns             [   ]");
  xPrintf(X+3,Y+ 5,"Number Of Colours          [      ]");
  xPrintf(X+3,Y+ 6,"Active Display Page            [  ]");
  xPrintf(X+3,Y+ 7,"Refresh Buffer Length      [      ]");
  xPrintf(X+3,Y+ 8,"Number Of Scan Lines         [    ]");
  xPrintf(X+3,Y+ 9,"Scan Lines Available         [    ]");
  xPrintf(X+3,Y+10,"Character Height             [    ]");
  xPrintf(X+3,Y+11,"Adapter Base Port Address    [    ]");
  xPrintf(X+3,Y+12,"Settings Of Register %4X8     [  ]",va.AdptBasePortAddr);
  xPrintf(X+3,Y+13,"Settings Of Register %4X9     [  ]",va.AdptBasePortAddr);
  xPrintf(X+3,Y+14,"Video Memory Available   [        ]");
  xPrintf(X+3,Y+15,"Primary Character Block        [  ]");
  xPrintf(X+3,Y+16,"Secondary Character Block      [  ]");
  xPrintf(X+3,Y+17,"Activity Display Code          [  ]");
  xPrintf(X+3,Y+18,"Inactivity Display Code        [  ]");
  xPrintf(X+3,Y+19,"Character Blocks Available     [  ]");
  xPrintf(X+3,Y+20,"Max Active Character Blocks    [  ]");
  xPrintf(X+3,Y+21,"Offset Of Refresh Buffer     [    ]");

  TxtAttr = SetTxtCol(Cyan,Yellow);
  xPrintf(X+35,Y+ 1,"%2d",va.CurVidMode);
  xPrintf(X+35,Y+ 2,"%2d",va.MaxPages);
  xPrintf(X+35,Y+ 3,"%2d",va.NumChrRows);
  xPrintf(X+34,Y+ 4,"%3d",va.NumChrClmns);
  xPrintf(X+32,Y+ 5,"%5u",va.MaxCols);
  xPrintf(X+35,Y+ 6,"%2d",va.ActDspPage);
  xPrintf(X+32,Y+ 7,"%5u",va.VidRefreshBufLen);
  xPrintf(X+33,Y+ 8,"%4d",NoOfScanLn(va.NumScanLns));
  xPrintf(X+34,Y+ 9,"%3d",AvlblScanLns(va.V->AvlScanLns));
  xPrintf(X+35,Y+10,"%2d",va.ChrHtScanLns);
  xPrintf(X+33,Y+11,"%4X",va.AdptBasePortAddr);
  xPrintf(X+35,Y+12,"%2X",va.Regs3B8or3D8);
  xPrintf(X+35,Y+13,"%2X",va.Regs3B9or3D9);
  xPrintf(X+30,Y+14,"%4d Kb",(va.AvlVidMem+1)*64);
  xPrintf(X+35,Y+15,"%2d",va.PriChrBlk);
  xPrintf(X+35,Y+16,"%2d",va.SecChrBlk);
  xPrintf(X+35,Y+17,"%2X",va.ActDspCode);
  xPrintf(X+35,Y+18,"%2X",va.InActDspCode);
  xPrintf(X+35,Y+19,"%2X",va.V->AvlChrBlks);
  xPrintf(X+35,Y+20,"%2X",va.V->MaxActChrBlks);
  xPrintf(X+33,Y+21,"%4X",va.BufStrtAddr);
 }
void Vga()
 {
  GetAdapterInf(&va);
  //SetVidMode(Txt132x25x16x4);
  //GetVidState(&va);
  TglBlink(Off);
  DrwPg=0;
 // SetActivePage(0);
//  SetBorderCol(Green);
  ClrPage(0,SetTxtCol(Green,Cyan));
  TxtAttr=SetTxtCol(Cyan,Yellow);
  FillChr(1,1,GetMaxX()-1,GetMaxY()-1,Blank);
  TxtAttr=SetTxtCol(Cyan,Yellow);
 // SetActivePage(0);
//  DrawBox(0,1,GetMaxX(),GetMaxY()-1,1);

  TxtAttr=SetTxtCol(Green,Yellow);
 /* FillChr(0,0,GetMaxX(),0,Blank);
  FillChr(0,GetMaxY(),GetMaxX(),GetMaxY(),Blank);
  FillChr(0,0,0,GetMaxY(),Blank);
  FillChr(GetMaxX(),0,GetMaxX(),GetMaxY(),Blank);*/

  xPrintf(GetMaxX()/2-12,0,"Current Video Information");
  xPrintf(1,0,"[%c]",SqBox);
  xPrintf(GetMaxX()-10,0,"[%c][?][X]",DblArrow);

  xPrintf(12,GetMaxY(),"Write");
  xPrintf(29,GetMaxY(),"Monitor");
  xPrintf(50,GetMaxY(),"View");
  xPrintf(68,GetMaxY(),"Unload");

  TxtAttr=SetTxtCol(Green,Yellow);
  xPrintf(3,GetMaxY(),"[Alt+W]");
  xPrintf(20,GetMaxY(),"[Alt+M]");
  xPrintf(39,GetMaxY(),"[Alt+F11]");
  xPrintf(57,GetMaxY(),"[Alt+F12]");

  if (GetMaxX() < 80)
   {
     VideoInf(5,1);
     GetKey();
     SaveAreaInf(5 ,2);
     SavePtrState(5,10);
     OthStateInf(5,10);
     GetKey();
     MiscBIOSInf(5,2);
   }
  else
   {
     VideoInf(3,1);
     SaveAreaInf(45,1);
     SavePtrState(45,8);
     OthStateInf(45,15);
     MiscBIOSInf(45,22);
     CursorInf(3,25);
   }
  GetKey();
 }
/*void interrupt far KbdVgaInf(...)
 {
  word Key=KeyHit();
  if (Key == Alt_V)
    Vga();
  OldKbdVec(...);
 }*/
main()
 {
  //getvact(0x09,OldKbdVec);
  //setvect(0x09,KbdVgaInf);
  //keep(800);
 /*
  TxtAttr = 0x0f;
  xPrintf(0,0," VAI Address %p",&va);
  xPrintf(0,1," VAI->V      %p",va.V);
  xPrintf(0,2," Vidmod      %p",&va.CurVidMode);
  xPrintf(0,3," NoChrCol    %p",&va.NumChrClmns);
  xPrintf(0,4," VidRef      %p",&va.VidRefreshBufLen);
  xPrintf(0,5," BufStrtAddr %p",&va.BufStrtAddr);
  xPrintf(0,6," CurPage     %p",va.Page);
  xPrintf(0,7," CurStrtScan %p",&va.CurStrtScanLn);
  */


  word key=0x00;
  for (int i=60;i<80 && key != EscKy;i++)
   {
    SetVidMode(i);
    Screen.SetScreen();
    Vga();
    key = GetKey();
    SetVidMode(i);
   }
  //ModeSearch(Txt80x60x16x8);
//  Vga();
  //SetVidMode(56);
  //Screen.SetScreen();
  dword Mode = Txt132x30x16x4;
 // ModeSearch(Mode);
 // Vga();
  ClrPage(0,Cyan<<4);
  TxtAttr = 0x0f;
  xPrintf(10,10,"X Resolution %d",(Mode>>xResShift)&xResMask);
  xPrintf(10,11,"Y Resolution %d",(Mode>>yResShift)&yResMask);
  xPrintf(10,12,"Video Mode   %d",(Mode&ModeMask));
  GetKey();
//  ClrPage(0,0x4F);
 // TxtAttr=0x7C;
 // FillChr(0,0,Screen.Width,Screen.Height,CloseDot);
  return(0);
 }
