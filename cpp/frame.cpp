#ifndef __FRAME_H
#define __FRAME_H

#include <Tool.h>
#define FrBoxStyle 0x03
#define FrJustify  0xC000
#define FrJustShft 14

class Frame : public Tool
 {
   private :
     word    swFrame;
     word    HotKey;
     Caption *Cap;

   public :
     Frame(word inf);
     Frame(byte x,byte y,byte w,byte h,word inf);

     ~Frame();

     void SetCaption(char *Src);
     bool Show();
    // bool KeyDown(word Key);
 };

#endif


Frame::Frame(word inf)
 {
   ToolID  = Frame_Tool;
   swFrame = inf;
   Cap     = (Caption*)NULL;
   cs      = &Classic;
 }
Frame::Frame(byte x,byte y,byte w,byte h,word inf)
      :Tool(x,y,w,h)
 {
   ToolID  = Frame_Tool;
   swFrame = inf;
   Cap     = (Caption*)NULL;
   cs      = &CoolBlue;
 }
Frame::~Frame()
 {
   delete Cap;
 }
bool Frame::Show()
 {
   byte x = (swFrame&FrJustify)>>FrJustShft;
   TxtAttr = cs->Box;
   DrawBox(X,Y,X+W-1,Y+H-1,swFrame&FrBoxStyle);
   if (Cap)
    {
      x = xJust(x,X,W,strlen(Cap->Prompt));
      TxtAttr = cs->Txt;
      xPrintf(x,Y,Cap->Prompt);
      TxtAttr = cs->TxtHi;
      xPrintf(x+Cap->Hot,Y,"%c",Cap->Prompt[Cap->Hot]);
    }
   return true;
 }
void Frame::SetCaption(char *Src)
 {
   Cap    = new Caption(Src);
   HotKey = StrToKey(Cap->ShortCut);
 }

