#include <conio.h>
#include <stdio.h>
#include <dos.h>
typedef unsigned int word;

#define TimerCh3   0x43
#define TimerCh2   0x42
#define Port8255   0x61
#define PortB      0x61
#define ProgTimer  0xB6

class Tone
 {
   public :
     Tone(word Frequency);
     ~Tone();
     void SetTone(word Frequency);
   };
Tone::Tone(word Frequency)
 {
   asm mov al, ProgTimer;
   asm out TimerCh3,al;
   asm in  al,Port8255;
   asm or  al,0x03;
   asm out Port8255,al;
   asm mov ax,[Frequency];
   asm out TimerCh2,al;
   asm mov al,ah;
   asm out TimerCh2,al;
 }
Tone::~Tone()
 {
   asm in  al,Port8255;
   asm and al,0xFC;
   asm out Port8255,al;
 }
void Tone::SetTone(word Frequency)
 {
   asm mov al, ProgTimer;
   asm out TimerCh3,al;
   asm in  al,Port8255;
   asm or  al,0x03;
   asm out Port8255,al;
   asm mov ax,[Frequency];
   asm out TimerCh2,al;
   asm mov al,ah;
   asm out TimerCh2,al;
 }

void Beep(word Frequency,word MilliSec)
 {
   asm mov al,ProgTimer;
   asm out TimerCh3,al;
   asm in  al,Port8255;
   asm or  al,0x03;
   asm out Port8255,al;
   asm mov ax,[Frequency];
   asm out TimerCh2,al;
   asm mov al,ah;
   asm out TimerCh2,al;
   delay(MilliSec);
   asm in  al,Port8255;
   asm and al,0xFC;
   asm out Port8255,al;
 }
main()
 {

   return 0;
 }