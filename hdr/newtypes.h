#ifndef __NEWTYPES_H
#define __NEWTYPES_H

#ifndef __DOS_H
#include <dos.h>
#endif

#include <stdlib.h>

typedef enum             bool { false = 0,true = 1 };
typedef unsigned int     word;
typedef unsigned char    byte;
typedef unsigned long    dword;

typedef unsigned int     Word;
typedef unsigned char    Byte;
typedef unsigned long    DWord;

typedef char             *Str;
typedef char far         *MemAddr;
typedef void far          Bitmap;

typedef void               (*App)();
typedef void interrupt far (*isr)(...);


typedef struct Handler
  {
    word  EvtMask;
    isr   EvtHndl;
  };

typedef struct
 {
  Bitmap  *Cursor;
  Word    xHotSpot,
	  yHotSpot;
  } gMouseCur;

typedef struct
  {
  byte   XorMask;
  Word    swCrypt;
  Str     Password;
  } CryptKey;

typedef struct far
  {
    Word *Sav;
    int  L,T,R,B;
    int  Size;
  } Image;

typedef struct
  {
    byte Txt,      // Item Normal Mode Attributes
	 TxtHi,
	 Xec,      // Item Selected Mode Attributes
	 XecHi,
	 Lck,      // Item Deactivated Mode Attributes
	 Box;      // Border Attributes
  } Scheme;


#define On    true
#define Off   false
#define NoApp (App)NULL

#endif
