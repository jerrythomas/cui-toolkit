class IntBox : public Tool
 {
    private:
      int   Max,Min;
      char  Text[6];
      byte  Cur;
    public :
      int   Value;

      IntBox();
      IntBox(int Val,int Mn,int Mx);

      void SetRange(int Mn,int Mx);
      bool KeyDown(word Key);
      void Draw();
      bool Show();
      bool Refresh();
 };

IntBox::IntBox()
 {
   ToolID = Event_IntBox;
   Min    = -32768;
   Max    = +32767;
   Value  = 0;
   Cur    = 5;
   memcpy(Text,0,6);
 }
IntBox::IntBox(int Val,int Mn,int Mx);
 {
   ToolID = Event_IntBox;
   Min    = min(Mn,Mx);
   Max    = max(Mn,Mx);
   Value  = (Val >=Min && Val <= Max) ? Val :Min;
   Cur    = 5;
   memcpy(Text,0,6);

 }
void IntBox::SetRange(int Mn,int Mx)
 {
   Min    = min(Mn,Mx);
   Max    = max(Mn,Mx);
   Value  = (Value >=Min && Value <= Max) ? Value:Min;
 }
void IntBox::Draw()
 {
 }
bool IntBox::KeyDown()
 {
   char Txt[6];
   byte i;
   strcpy(Txt,Text);
   if (Key >= '0' && Key <= '9')
    {
      if (ShiftStatus()&InsOn)
       {
         for (i=1;i< Cur;i++)
            Txt[i-1] = Txt[i];
         Txt[Cur] = Key;
       }
      else
        Txt[Cur] = Key;
    }
   else if (Key == DelKy)
    {
     for (i=Cur;i>0;i--)
      Txt[i] = Txt[i-1];
     Txt[0] = ' ';
    }
   else if (Key == BakSp)
    {
      for (i=Cur;i<5;i++)
       Txt[i] = Txt[i+1];
      for (i=5;i>0;i++)
       Txt[i] = Txt[i-1];
      Txt[0] = ' ';
    }

 }

bool IntBox::Show()
 {
   Draw();
 }
bool IntBox::Refresh();
 {
   Draw();
 }

