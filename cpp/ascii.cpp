#include <cuibase.h>
#include <kbd.h>
#include <stdio.h>
main()
 {
   //ModeSearch(Txt80x25x16x8);
   Screen.Width =80;
   Screen.Height=25;
   for (int j=0;j<25;j++)
    for (int i=0;i<80;i++)
     {
       GetVidAt(0,i,j,VidAtr,VidChr);
       SetVidAt(1,i,j,VidAtr,VidChr);
     }


   TxtAttr = SetTxtCol(Green,Yellow);

   FillChr(5,1,68,1,Blank);
   xPrintf(30,1,"Ascii Chart");
   TxtAttr = SetTxtCol(LightGray,Blue);
   FillChr(5,2,68,22,Blank);
   DrawBox(5,2,72,23,HDVS);

   DrawBox(7,3,13,22,Single);
   DrawBox(13,3,18,22,Single);
   DrawBox(7,3,70,5,Single);
   TxtAttr = SetTxtCol(LightGray,Red);
   xPrintf(8,4," Dec");
   xPrintf(15,4,"Hex");
   for (i=0;i<16;i++)
    {
      xPrintf(21+i*3,4,"%X ",i);
      xPrintf(9,6+i,"%3d",i*16);
      xPrintf(16,6+i,"%X",i);
    }
   TxtAttr = SetTxtCol(LightGray,Black);
   for (j=0;j<16;j++)
    for (i=0;i<16;i++)
      xPrintf(21+i*3,6+j,"%c",j*16+i);
   GetKey();
   for (j=0;j<25;j++)
    for (i=0;i<80;i++)
     {
       GetVidAt(1,i,j,VidAtr,VidChr);
       SetVidAt(0,i,j,VidAtr,VidChr);
     }

   return 0;
 }