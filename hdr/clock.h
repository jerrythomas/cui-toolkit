#ifndef __CLOCK_H
#define __CLOCK_H

#include <vdu.h>
#include <dos.h>

#define Fmt24Hrs        0x01
#define Fmt12Hrs        0x02
#define TicksPerHour   65520
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