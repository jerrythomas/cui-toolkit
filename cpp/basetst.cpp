#include <CuiBase.H>
main()
 {
   ModeSearch(Txt132x25x16x4);
   TxtAttr = 0x0F;
   FillChr(0,0,Screen.Width,Screen.Height,CloseDot);
   xPrintf(20,20,"%d %d %d",Screen.Width,Screen.Height,Screen.Delta);
   GetKey();
   return(0);
 }