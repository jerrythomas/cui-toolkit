// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>            ScrX  Screen Capture eXtensions              <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>


class ScrX
 {
    #define SlideRt             0x0001
    #define SlideLt             0x0002
    #define SlideDn             0x0003
    #define SlideUp             0x0004

    #define SlideRtDn           0x0005
    #define SlideLtDn           0x0006
    #define SlideRtUp           0x0007
    #define SlideLtUp           0x0008

    #define RollRt              0x0009
    #define RollLt              0x000A
    #define RollDn              0x000B
    #define RollUp              0x000C

    #define EffShadow           0x0020
    #define EffHalfShadow       0x0040
    #define NoShadow            0x0080
    #define NoAlloc             0x8000
    #define MaskAlloc           0x7FFF

   protected  :
     word   swScr;

   private :

     byte   X,Y,W,H;
     char   *Buffer;
     word   BufSize;

   public :

     ScrX();
     ~ScrX();

     void SetEffect(word Eff);

     void Copy(byte DstPg,byte SrcPg,byte x,byte y,byte w,byte h);
     void xCopy(byte DstPg,byte SrcPg,word DstOff,word SrcOff,byte w,byte h);
     void Capture(byte x,byte y,byte w,byte h);
     void Restore();
     void Restore(byte x,byte y);

     void ShowEffect(byte x,byte y,byte w,byte h);
     void UndoEffect();
     void Delete();

     friend class Form;
  };

// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>                   ScrX Module Source                    <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

ScrX::ScrX()
 {
   X = Y = W = H;
   swScr   =  NoAlloc;
   Buffer  = (char *)NULL;
   BufSize = 0;
 }
ScrX::~ScrX()
 {
   if (Buffer != (char *)NULL)
      delete Buffer;
 }

void ScrX::SetEffect(word Eff)
 {
   swScr |= Eff&0x00FF;
 }
void ScrX::Copy(byte DstPg,byte SrcPg,byte x,byte y,byte w,byte h)
 {
   word OffSet = (Screen.Width*y+x)*2;
//   word Incr   = Screen.Width*2;
  // xPrintf(20,20,"%d %d",Screen.Width,Screen.Delta);
   for(y=0;y<h;y++,OffSet+=Screen.Delta)
    {
     memcpy(Screen.BufAddr(DstPg)+OffSet,Screen.BufAddr(SrcPg)+OffSet,w*2);
     GetKey();
    }
 }
void ScrX::xCopy(byte DstPg,byte SrcPg,word DstOff,word SrcOff,byte w,byte h)
 {
//   word Incr   = Screen.Width*2;
   for(byte y=0;y<h;y++,DstOff+=Screen.Delta,SrcOff+=Screen.Delta)
     memcpy(Screen.BufAddr(DstPg)+DstOff,Screen.BufAddr(SrcPg)+SrcOff,w*2);
 }

void ScrX::Capture(byte x,byte y,byte w,byte h)
 {
   if (Buffer != (byte*)NULL)
      delete Buffer;
   swScr |= (w==Screen.Width || h==Screen.Height) ? NoShadow:0;
   X = x;
   Y = y;
   W = (swScr&NoShadow)? w:w+1;
   H = (swScr&NoShadow)? h:h+1;
   swScr  &= MaskAlloc;
   BufSize = W*H*2;
   Buffer  = new char[BufSize];
   w = W*2;
   word Offset = Screen.Delta*y+x*2;
   for (y=0;y<H;y++,Offset+=Screen.Delta)
     memcpy(Buffer+y*w,(Screen.BufAddr(DrwPg)+Offset),w);
 }
void ScrX::Restore()
 {
  if (Buffer != (byte*)NULL)
   {
     byte w=W*2;
     byte y;
     word Offset = Screen.Delta*Y+X*2;
     for (y=0;y<H;y++,Offset+=Screen.Delta)
       memcpy(Screen.BufAddr(DrwPg)+Offset,Buffer+y*w,w);
   }
 }
void ScrX::Restore(byte x,byte y)
 {
  if (Buffer != (byte*)NULL)
   {
     byte w=W*2;
     X = x;
     Y = y;
     word Offset = (Screen.Width*Y+X)*2;
     for (y=0;y<H;y++,Offset+=Screen.Delta)
       memcpy(Screen.BufAddr(DrwPg)+Offset,Buffer+y*w,w);
   }
 }
void ScrX::ShowEffect(byte x,byte y,byte w,byte h)
 {
   byte  n,wS,hS;
   if (swScr&NoShadow)
    { w++;h++;}
   if (!(X==x && Y==y && W==w && H==h) && Buffer != (char *)NULL)
    {
      Restore();
      if (swScr&NoShadow)
       {
         w--;h--;
         swScr^=NoShadow;
       }
      Capture(x,y,w,h);
    }
  wS = W;
  hS = H;
  W  = w;
  H  = h;


  byte  N  = max(W,H);
  byte  Style  = swScr&0x1F;
  word  SrcOff,DstOff;
  //word  Incr  = Screen.Width*2;

  if (Style == SlideRt)
     for(n=1;n<=W;n++)
      {
       DstOff = (Screen.Width*Y+X)*2;
       SrcOff = DstOff + (W-n)*2;
       xCopy(DrwPg,RufPg,DstOff,SrcOff,n,H);
       if (swScr&EffShadow) BoxShadow(X,Y,X+n-1,Y+H-1);
       delay(10);
      }
  else if (Style == SlideLt)
     for(n=1;n<=W;n++)
      {
       SrcOff = (Screen.Width*Y+X)*2;
       DstOff = SrcOff + (W-n)*2;
       xCopy(DrwPg,RufPg,DstOff,SrcOff,n,H);
       if (swScr&EffShadow) BoxShadow(X+W-n,Y,X+W-1,Y+H-1);
       delay(10);
      }
  else if (Style == SlideDn)
     for(n=1;n<=H;n++)
      {
       SrcOff = (Screen.Width*(Y+H-n)+X)*2;
       DstOff = (Screen.Width*Y + X)*2;
       xCopy(DrwPg,RufPg,DstOff,SrcOff,W,n);
       if (swScr&EffShadow) BoxShadow(X,Y,X+W-1,Y+n-1);
       delay(10);
      }
  else if (Style == SlideUp)
     for(n=1;n<=H;n++)
      {
       SrcOff = (Screen.Width*Y + X)*2;
       DstOff = (Screen.Width*(Y+H-n)+X)*2;
       xCopy(DrwPg,RufPg,DstOff,SrcOff,W,n);
       if (swScr&EffShadow) BoxShadow(X,Y+H-n,X+W-1,Y+H-1);
       delay(10);
      }
  else if (Style == SlideRtDn)
     for(n=1;n<=N;n++)
      {
       w  = W*n/N;
       h  = H*n/N;
       if (h>0 && w>0)
        {
         SrcOff = (Screen.Width*(Y+H-h)+X+W-w)*2;
         DstOff = (Screen.Width*Y+X)*2;
         xCopy(DrwPg,RufPg,DstOff,SrcOff,w,h);
         if (swScr&EffShadow) BoxShadow(X,Y,X+w-1,Y+h-1);
         delay(10);
        }
      }
  else if (Style == SlideLtDn)
     for(n=1;n<=N;n++)
      {
       w      = W*n/N;
       h      = H*n/N;
       if (h>0 && w>0)
        {
         SrcOff = (Screen.Width*(Y+H-h)+X)*2;
         DstOff = (Screen.Width*Y+X+W-w)*2;
         xCopy(DrwPg,RufPg,DstOff,SrcOff,w,h);
         if (swScr&EffShadow) BoxShadow(X+W-w,Y,X+W-1,Y+h-1);
         delay(10);
        }
      }
  else if (Style == SlideRtUp)
     for(n=1;n<=N;n++)
      {
       w      = W*n/N;
       h      = H*n/N;
       if (h>0 && w>0)
        {
         SrcOff = (Screen.Width*Y+X+W-w)*2;
         DstOff = (Screen.Width*(Y+H-h)+X)*2;
         xCopy(DrwPg,RufPg,DstOff,SrcOff,w,h);
         if (swScr&EffShadow) BoxShadow(X,Y+H-h,X+w-1,Y+H-1);
         delay(10);
        }
      }
  else if (Style == SlideLtUp)
     for(n=1;n<=N;n++)
      {
       w      = W*n/N;
       h      = H*n/N;
       if (h>0 && w>0)
        {
          SrcOff = (Screen.Width*Y+X)*2;
          DstOff = (Screen.Width*(Y+H-h)+X+W-w)*2;
          xCopy(DrwPg,RufPg,DstOff,SrcOff,w,h);
          if (swScr&EffShadow) BoxShadow(X+W-w,Y+H-h,X+W-1,Y+H-1);
          delay(10);
        }
      }
  else
    Copy(DrwPg,RufPg,X,Y,W,H);
  W = wS;
  H = hS;
 }
void ScrX::UndoEffect()
 {
  byte n,w,h,eW,eH;
  eW = W;
  eH = H;
  if (!(swScr&NoShadow))
    { eW--;eH--;}
  byte  N  = max(eW,eH);
  byte  Style  = swScr&0x1F;
  word  SrcOff,DstOff;

  Copy(RufPg,DrwPg,X,Y,eW,eH);
  if (Style == SlideRt)
     for(n=eW;n>0;n--)
      {
       DstOff = (Screen.Width*Y+X)*2;
       SrcOff = DstOff + (eW-n)*2;
       Restore();
       xCopy(DrwPg,RufPg,DstOff,SrcOff,w,eH);
       if (swScr&EffShadow) BoxShadow(X,Y,X+n-1,Y+eH-1);
       delay(10);
      }
  else if (Style == SlideLt)
     for(n=eW;n>0;n--)
      {
       SrcOff = (Screen.Width*Y+X)*2;
       DstOff = SrcOff + (eW-n)*2;
       Restore();
       xCopy(DrwPg,RufPg,DstOff,SrcOff,w,eH);
       if (swScr&EffShadow) BoxShadow(X+eW-n+1,Y,X+eW,Y+eH-1);
       delay(10);
      }
  else if (Style == SlideDn)
     for(n=eH;n>0;n--)
      {
       SrcOff = (Screen.Width*(Y+eH-n)+X)*2;
       DstOff = (Screen.Width*Y + X)*2;
       Restore();
       xCopy(DrwPg,RufPg,DstOff,SrcOff,eW,n);
       if (swScr&EffShadow) BoxShadow(X,Y,X+eW-1,Y+n-1);
       delay(10);
      }
  else if (Style == SlideUp)
     for(n=eH;n>0;n--)
      {
       SrcOff = (Screen.Width*Y + X)*2;
       DstOff = (Screen.Width*(Y+eH-n)+X)*2;
       Restore();
       xCopy(DrwPg,RufPg,DstOff,SrcOff,eW,n);
       if (swScr&EffShadow) BoxShadow(X,Y+eH-n,X+eW-1,Y+eH-1);
       delay(10);
      }
  else if (Style == SlideRtDn)
     for(n=N;n>0;n--)
      {
       w  = eW*n/N;
       h  = eH*n/N;
       if (h>0 && w>0)
        {
         SrcOff = (Screen.Width*(Y+eH-h)+X+eW-w)*2;
         DstOff = (Screen.Width*Y+X)*2;
         Restore();
         xCopy(DrwPg,RufPg,DstOff,SrcOff,w,h);
         if (swScr&EffShadow) BoxShadow(X,Y,X+w-1,Y+h-1);
         delay(10);
        }
      }
  else if (Style == SlideLtDn)
     for(n=N;n>0;n--)
      {
       w      = eW*n/N;
       h      = eH*n/N;
       if (h>0 && w>0)
        {
         SrcOff = (Screen.Width*(Y+eH-h)+X)*2;
         DstOff = (Screen.Width*Y+X+eW-w)*2;
         Restore();
         xCopy(DrwPg,RufPg,DstOff,SrcOff,w,h);
         if (swScr&EffShadow) BoxShadow(X+eW-w,Y,X+eW-1,Y+h-1);
         delay(10);
        }
      }
  else if (Style == SlideRtUp)
     for(n=N;n>0;n--)
      {
       w      = eW*n/N;
       h      = eH*n/N;
       if (h>0 && w>0)
        {
         SrcOff = (Screen.Width*Y+X+eW-w)*2;
         DstOff = (Screen.Width*(Y+eH-h)+X)*2;
         Restore();
         xCopy(DrwPg,RufPg,DstOff,SrcOff,w,h);
         if (swScr&EffShadow) BoxShadow(X,Y+eH-h,X+w-1,Y+eH-1);
         delay(10);
        }
      }
  else if (Style == SlideLtUp)
     for(n=N;n>0;n--)
      {
       w      = eW*n/N;
       h      = eH*n/N;
       if (h>0 && w>0)
        {
          SrcOff = (Screen.Width*Y+X)*2;
          DstOff = (Screen.Width*(Y+eH-h)+X+eW-w)*2;
          Restore();
          xCopy(DrwPg,RufPg,DstOff,SrcOff,w,h);
          if (swScr&EffShadow) BoxShadow(X+eW-w,Y+eH-h,X+eW-1,Y+eH-1);
          delay(10);
        }
      }
    Restore();
 }
void ScrX::Delete()
 {
  if (Buffer != (char*)NULL)
      delete Buffer;
  Buffer = (char*)NULL;
 }

