//Block Select Codes
#define BlockBlinkOff  0x13
#define BlockBlinkOn   0x2C

void LoadUserFont(byte H,word TotChr,byte *Buf)
 {
   word Sg = FP_SEG(Buf);
   word Of = FP_OFF(Buf);
   asm push es;
   asm push bp;
   asm mov ah,0x11;
   asm mov al,0x00; //0x11 for recalc  & page 0
   asm mov bh,H;
   asm mov bl,0;          //block
   asm mov cx,TotChr;
   asm mov dx,Sg;
   asm mov es,Sg;
   asm mov bp,Of;
   asm mov dx,0;
   asm int 0x10;
   asm pop bp;
   asm pop es;
 }
void LoadRom8x14Font()
 {
   asm mov ah,0x11;
   asm mov al,0x01; //0x11 for recalc & page 0
   asm mov bl,0;    // block
   asm int 0x10;
 }
void LoadRom8x8Font()
 {
   asm mov ah,0x11;
   asm mov al,0x02; //0x12 for recalc & page 0
   asm mov bl,0;    //Block
   asm int 0x10;
 }
void SetBlockSpecifier(byte BlockSelect)
 {
   asm mov ah,0x11;
   asm mov al,0x03;
   asm mov bl,BlockSelect;
   asm int 0x10;
 }
