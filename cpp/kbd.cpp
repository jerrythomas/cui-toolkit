#include <Kbd.h>
#define KbdInt 0x16

word KeyMap(word Key)
 {
   byte KeyNo,KeyAscii;
   asm mov ax,Key;
   asm mov KeyNo,ah;
   asm mov KeyAscii,al;

   if (KeyNo == 1)
      Key |= (KbdFlagWord()&0x03) ? 0x2000:(KbdFlagWord()&0x04) ? 0x4000:0;
   else if (KbdFlagWord()&0x000C)
    {
      if (KeyNo == 0x39 && KeyAscii == 0x20)
	 Key |= (KbdFlagWord()&AnyAltKeyDn) ? 0x8000:0x4000;
    }
   else
    {
     if (KeyNo < 0x3B)
       Key = (KeyAscii==0) ? Key:KeyAscii;
     else  if (KeyNo==0x4A || KeyNo==0x4E || KeyNo==0xE0)
       Key = KeyAscii;
     else if (KeyNo > 0x46 && KeyNo < 0x54)
       if ((KeyAscii >= '0' && KeyAscii <= '9')||KeyAscii=='.')
	  Key = KeyAscii;
       else if (KbdFlagWord()&AnyShftKyDn)
	  Key |= 0x07;
    }
   return Key;
 }

/*word ShftNavKeys(word Key)
 {
  switch(Key)
   {
    case LtArr: case RtArr:
    case UpArr: case DnArr:
    case PgUp : case PgDn :
    case Home : case End  :
    case InsKy:
    case DelKy: Key+=0x0034;break;
   }
  return(Key);
 } */
byte KbdFlagByte()
 {
  byte rvFlag;
  asm mov ah,0x02;
  asm int KbdInt;
  asm mov [[rvFlag]],al;
  return(rvFlag);
 }
void SetKbdRepeatRate(byte Dly,byte Cps)
 {
  asm mov ah,0x03;
  asm mov al,0x05;
  asm mov bh,[Dly];
  asm mov bl,[Cps];
  asm int KbdInt;
 }
void SetKeyClick(byte State)
 {
  asm mov ah,0x04;
  asm mov al,[State];
  asm int KbdInt;
 }

int OutKey(word Key)
 {
  byte rvDone;
  asm mov ah,0x05;
  asm mov cx,[Key];
  asm int KbdInt;
  asm mov [[rvDone]],al;
  return(rvDone);
 }
word GetKey()
 {
  word rvKey;
  asm mov ah,0x10;
  asm int KbdInt;
  asm mov [[rvKey]],ax;
  return KeyMap(rvKey);
 }
word KeyHit()
 {
  word rvKey;
      asm mov  ah,0x11;
      asm int  KbdInt;
      asm jnz  Hit;
      asm mov  ax,0;
  Hit:asm mov [[rvKey]],ax;

  return KeyMap(rvKey);
 }
word KbdFlagWord()
 {
  word rvWord;
  asm mov ah,0x12;
  asm int KbdInt;
  asm mov [[rvWord]],ax;
  return(rvWord);
 }

word FnKey(int Num)
 {
  word rvWord = 0x3A00;
  if (Num > 0 && Num < 11)
     rvWord += Num<<8 ;
  else
    rvWord = (Num == 11)? 0x8500:(Num == 12)?0x8600:0;
  return(rvWord);
 }

word ShiftF(int Num)
 {
  word rvWord=0x5300;
  if (Num > 0 && Num < 11)
    rvWord += Num<<8 ;
  else
    rvWord = (Num == 11)? 0x8700:(Num == 12)?0x8800:0;
  return((rvWord==0x5300) ? 0:rvWord);
 }

word CtrlF(int Num)
 {
  word rvWord=0x5D00;
  if (Num > 0 && Num < 11)
    rvWord += Num<<8 ;
  else
    rvWord = (Num == 11)? 0x8900:(Num == 12)?0x8A00:0;
  return((rvWord==0x5D00) ? 0:rvWord);
 }

word AltF(int Num)
 {
  word rvWord=0x6700;
  if (Num > 0 && Num < 11)
    rvWord += Num<<8 ;
  else
    rvWord = (Num == 11)? 0x8B00:(Num == 12)?0x8C00:0;
  return((rvWord==0x6700) ? 0:rvWord);
 }

word Alt(char Alph)
 {
  switch(UpCase(Alph))
   {
    case 'A' : return(Alt_A);
	 case 'B' : return(Alt_B);
	 case 'C' : return(Alt_C);
	 case 'D' : return(Alt_D);
	 case 'E' : return(Alt_E);
    case 'F' : return(Alt_F);
	 case 'G' : return(Alt_G);
	 case 'H' : return(Alt_H);
	 case 'I' : return(Alt_I);
	 case 'J' : return(Alt_J);
	 case 'K' : return(Alt_K);
	 case 'L' : return(Alt_L);
	 case 'M' : return(Alt_M);
	 case 'N' : return(Alt_N);
	 case 'O' : return(Alt_O);
	 case 'P' : return(Alt_P);
	 case 'Q' : return(Alt_Q);
	 case 'R' : return(Alt_R);
	 case 'S' : return(Alt_S);
	 case 'T' : return(Alt_T);
	 case 'U' : return(Alt_U);
	 case 'V' : return(Alt_V);
	 case 'W' : return(Alt_W);
	 case 'X' : return(Alt_X);
	 case 'Y' : return(Alt_Y);
	 case 'Z' : return(Alt_Z);
	 default  : return(0);
   }
 }

word Ctrl(char Alph)
 {
  switch(UpCase(Alph))
   {
	 case 'A' : return(Ctrl_A);
	 case 'B' : return(Ctrl_B);
	 case 'C' : return(Ctrl_C);
	 case 'D' : return(Ctrl_D);
	 case 'E' : return(Ctrl_E);
    case 'F' : return(Ctrl_F);
	 case 'G' : return(Ctrl_G);
	 case 'H' : return(Ctrl_H);
	 case 'I' : return(Ctrl_I);
	 case 'J' : return(Ctrl_J);
	 case 'K' : return(Ctrl_K);
	 case 'L' : return(Ctrl_L);
	 case 'M' : return(Ctrl_M);
	 case 'N' : return(Ctrl_N);
	 case 'O' : return(Ctrl_O);
	 case 'P' : return(Ctrl_P);
	 case 'Q' : return(Ctrl_Q);
	 case 'R' : return(Ctrl_R);
	 case 'S' : return(Ctrl_S);
	 case 'T' : return(Ctrl_T);
	 case 'U' : return(Ctrl_U);
	 case 'V' : return(Ctrl_V);
	 case 'W' : return(Ctrl_W);
	 case 'X' : return(Ctrl_X);
	 case 'Y' : return(Ctrl_Y);
	 case 'Z' : return(Ctrl_Z);
	 default  : return(0);
   }
 }
