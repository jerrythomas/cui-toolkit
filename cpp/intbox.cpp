#include <kbd.h>
#include <vdu.h>
#include <Events.H>
Vector f;
word Key;
void interrupt far KeyCheck(...)
 {
   Key = _AX;
   TxtAttr = 0x05;
   xPrintf(20,20,"Intr Key %4X",Key);
   _AX = Key;
   f(...);
 }
main()
 {
   TxtAttr = 0x05;
   ModeSearch(Txt100x37x16x4);
   TxtAttr = 0x07;
   FillChr(0,0,Screen.Width-1,Screen.Height-1,CloseDot);
/*
   xPrintf(20,10,"Width    %d",Screen.Width);
   xPrintf(20,11,"Height   %d",Screen.Height);
   xPrintf(20,12,"MaxPages %d",Screen.Pages);
   xPrintf(20,13,"Colors   %d",Screen.Colors);
   for (int i=0;i<Screen.Pages;i++)
    xPrintf(20,14+i,"Address   %x:%x",FP_SEG(Screen.BufAddr(i)),FP_OFF(Screen.BufAddr(i)));
   GetKey();*/
   Vector f;
   f = getvect(0x9);
   setvect(0x9,KeyCheck);
   word K=GetKey();

   while (K != EscKy)
     {
      TxtAttr = 0x7E;
      xPrintf(20,30,"GetKey %4X",K);
      K = GetKey();
     }
   setvect(0x9,f);
   return 0;
 }

