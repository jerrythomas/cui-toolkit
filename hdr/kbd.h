#ifndef __KBD_H
#define __KBD_H

#include <KbdFlags.h>
#include <NumKeyPd.h>
#include <AltCodes.h>
#include <CtrlCode.h>
#include <FuNCodes.h>
#include <HotKeys.h>
#include <newtypes.h>

#define UpCase(C) ((C) >= 'a' && (C) <= 'z') ? (C)-32:(C)
#define LoCase(C) ((C) >= 'A' && (C) <= 'Z') ? (C)+32:(C)

word KeyMap(word Key);
byte KbdFlagByte();
void SetKbdRepeatRate(byte Dly,byte Cps);
void SetKeyClick(byte State);
int  OutKey(word Key);
word GetKey();
word KeyHit();
word KbdFlagWord();

word FnKey (int Num);
word AltF  (int Num);
word CtrlF (int Num);
word ShiftF(int Num);
word Alt   (char Alph);
word Ctrl  (char Alph);

word StrToKey(char *src);
#endif
