#include <CuiBase.H>
main()
 {
   ModeSearch(Txt132x25x16x4);
   //for (int i =33 ;i<40;i++)
//    SetVidMode(i);
  // Screen.SetScreen();
   TxtAttr = 0x0F;
   FillChr(0,0,Screen.Width,Screen.Height,CloseDot);
   DrawBox(10,2,30,8,Single);
   DrawBox(60,2,80,8,Single);
   DrawBox(10,14,30,20,Single);
   DrawBox(60,14,80,20,Single);
   DrawBox(25,6,65,16,Single);
   DrawBox(30,8,60,14,Single);
   xPrintf(20,20,"%d %d %d",Screen.Width,Screen.Height,Screen.Delta);
   GetKey();

   return(0);
 }