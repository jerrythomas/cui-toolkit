#ifndef __CLOCK_H
#define __CLOCK_H

#include <vdu.h>
#include <dos.h>

#define Fmt24Hrs        0x01
#define Fmt12Hrs        0x02
#define TicksPerHour    0xFFF0
#define TicksPerMin     1092
#define TicksPerSec     18.2

class Clock
 {
   public:

   Clock();
   ~Clock();
   void LoadClock();
   void DropClock();
   void MoveTo(byte X,byte Y);
   void SetColour(byte Colour);
   void SetFormat(byte Style);
 };

#endif

#define TimerIntr 0x1C

extern unsigned _heaplen = 1024;
extern unsigned _stklen  = 512;

typedef void interrupt far (*vec)(...);
vec OldTimerVec;
long far *Time=(long far*)MK_FP(0x000,0x046C);

byte Clk_X,Clk_Y;
byte Clk_TxtCol;
byte Clk_Style;
byte Clk_W;

char AmPm[3] = {"Am"};

void interrupt far ShowClock(...)
 {
  byte Hrs,Min,Sec;
  byte x=GetX(DrwPg);
  byte y=GetY(DrwPg);
  byte SavCol=TxtAttr;

  Hrs  = (byte)( *Time/TicksPerHour);
  Min  = (byte)((*Time%TicksPerHour) / TicksPerMin);
  Sec  = (byte)((*Time%TicksPerMin ) / TicksPerSec);

  TxtAttr=Clk_TxtCol;

  switch(Clk_Style)
   {
    case Fmt24Hrs: Hrs %= 24;
                   xPrintf(Clk_X,Clk_Y,"[%02d:%02d:%02d]",Hrs,Min,Sec);
                   break;
    case Fmt12Hrs: AmPm[0] = (Hrs > 12) ? 'P':'A';
                   Hrs     = (Hrs%12==0) ? 12:Hrs%12;
                   xPrintf(Clk_X,Clk_Y,"[%02d:%02d:%02d %s]",Hrs,Min,Sec,AmPm);
                   break;
   }
  SetCurPos(DrwPg,x,y);
  TxtAttr=SavCol;
  OldTimerVec(...);
 }

Clock::Clock()
 {
  SetFormat(Fmt24Hrs);
  MoveTo(GetMaxX()-10,GetMaxY());
  SetColour(SetTxtCol(Cyan,Black));
  OldTimerVec=(vec)getvect(TimerIntr);
  setvect(TimerIntr,ShowClock);
 }

Clock::~Clock()
 {
  setvect(TimerIntr,OldTimerVec);
 }

void Clock::LoadClock()
 {
  OldTimerVec=(Vector)getvect(TimerIntr);
  setvect(TimerIntr,ShowClock);
 }

void Clock::DropClock()
 {
  setvect(TimerIntr,OldTimerVec);
 }

void Clock::MoveTo(byte X,byte Y)
 {
  Clk_X = (X > GetMaxX()-Clk_W) ? GetMaxX()-Clk_W:X;
  Clk_Y = Y % (GetMaxY()+1);
 }

void Clock::SetColour(byte Colour)
 {
  Clk_TxtCol = Colour;
 }

void Clock::SetFormat(byte Style)
 {
  switch(Style)
   {
    case Fmt24Hrs:Clk_W = 10;
                  break;
    case Fmt12Hrs:Clk_W = 13;
                  break;
   }
  Clk_Style =Style;
  MoveTo(Clk_X,Clk_Y);
 }
/*main()
 {
  Clock C;
  C.SetFormat(Fmt24Hrs);
  C.SetColour(SetTxtCol(Brown,LightGray));
  keep(0, (_SS + (_SP/16) - _psp));
  return(0);
 } */
