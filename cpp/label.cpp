#include <Tool.h>
#define LbJustify  0xC0
#define LbJustShft 14
class Label : public Tool
 {
   private :
     word    swLabel;
     word    HotKey;
     Caption *Cap;

   public :
     Label(word inf);
     Label(byte x,byte y,byte w,byte h,word inf);

     ~Label();

     void SetCaption(char *Src);
     bool Show();
     //bool KeyDown(word Key);
 };

Label::Label(word inf)
 {
   ToolID  = Label_Tool;
   swLabel = inf;
   cs = &Classic;
 }
Label::Label(byte x,byte y,byte w,byte h,word inf)
        :Tool(x,y,w,h)
 {
   ToolID  = Label_Tool;
   swLabel = inf;
   cs = &CoolBlue;
 }
Label::~Label()
 {
   delete Cap;
 }
bool Label::Show()
 {
   byte x = (swLabel&0xC000)>>14;

   if (Cap)
    {
      x = xJust(x,X,W,min(strlen(Cap->Prompt),W-4));
      TxtAttr = cs->Txt;
      FillChr(X,Y,X+W-1,Y+H-1,Blank);
      xPrintf(x,Y,Cap->Prompt);
      TxtAttr = cs->TxtHi;
      xPrintf(x+Cap->Hot,Y,"%c",Cap->Prompt[Cap->Hot]);
    }
   return true;
 }
void Label::SetCaption(char *Src)
 {
   if (Cap != (Caption*)NULL)
      delete Cap;
   Cap    = new Caption(Src);
   HotKey = StrToKey(Cap->ShortCut);
 }
