#ifndef __MOUSE_H
#define __MOUSE_H

#include <BaseInc.H>

#define MouseActive    0x0001
#define MousePress     0x0002
#define MouseRelease   0x0004

#define MaskPressBit   0xFFFD
#define MaskReleaseBit 0xFFFB
#define MouseInt  0x33

typedef struct
         {
           int  MajVerNo,
                MinVerNo,
                MouseType,
                MouseIRQ,
                xMickeyCnt,
                yMickeyCnt;
         } MouseInf;


extern word     ms_x,
		ms_y;
extern word     ms_Clix,
		ms_Btn,
                ms_PressCnt,
                ms_ReleaseCnt;

extern MouseInf ms_Inf;


  void SetMousePixSize(byte xSz,byte ySz);
  void StartMouse();
  void CloseMouse();
  int  MouseExists();
  void SetMousePointerShape(int xHotSpotOff,int yHotSpotOff,void far *Buf);
  void HideMouseCursor();
  void ShowMouseCursor();
  void MouseClix();
  void FlushMouse();

  void SetMouseCurPos(int X,int Y);
  void GetMouseBtnPress(int WhichBtn);
  void GetMouseBtnRelease(int WhichBtn);
  void SetMouseCurWin(int Up_Lf_X,int Up_Lf_Y,int Dn_Rt_X,int Dn_Rt_Y);
  void SoftMouseCursor(Word AndMask,Word XorMask);
  void HardMouseCursor(Word StartLn,Word EndLn);
  void MouseMotionCounter();

  void SetLightPenEmulate(bool State);
  void SetMickeysToPixRatio(int xMickey,int yMickey);
  void SetMouseCurWinX(int Up_Lf_X,int Up_Lf_Y,int Dn_Rt_X,int Dn_Rt_Y);
  void SetDoubleSpeed(int Speed);

  int  GetMouseSavStateSiz();
  void SaveMouseDrvState(Word Segment,Word Offset);
  void RestoreMouseDrvState(Word Segment,Word Offset);

  void SetUserMouseEventHandler(word EvtMask,isr Handle);
  void SwapEventHandler(word EvtMask,isr NewEvt,Handler *Hndl);
  int  SetAlternateMouseHandler(word EvtMask,isr Hndl);
  int  GetAlternateMouseHandler(word SrcMask,Handler *Hndl);

  void SetMouseSensitivity(int xMic,int yMic,int DblSpeed);
  void GetMouseSensitivity(int *xMic,int *yMic,int *DblSpeed);
  void SetMouseIntrRate(int IntrFlag);
  void SetMouseCurPage(int PageNo);
  int  DisableMouseDriver(Handler *Hndl);
  void EnableMouseDriver();
  int  ResetMouseDriver();
  void GetMouseInfo();
//  void SoftMouseCur(Word aMask,Word xMask);

#endif


struct REGPACK EventHndl;
union REGS     MouseReg;
Word           swMouse;
Word     ms_x,
         ms_y;
Word     ms_Clix,
         ms_Btn,
         ms_PressCnt,
         ms_ReleaseCnt;
MouseInf ms_Inf;
Word     ms_xSiz=1,ms_ySiz=1;


void SetMousePixSize(byte xSz,byte ySz)
 {
  ms_xSiz = (xSz>0) ? xSz:1;
  ms_ySiz = (ySz>0) ? ySz:1;
 }

void StartMouse()
 {
  ms_xSiz = ms_ySiz = 1;

  asm mov ax,0x00;
  asm int MouseInt;
  asm mov [[swMouse]],ax;
  asm mov [[ms_Clix]],bx;
  swMouse = (swMouse) ? 1:0;
  if (swMouse&MouseActive)
   {
    asm mov ax,0x01;
    asm int MouseInt;
   }
 }

void CloseMouse()
 {
  asm mov ax,0x02;
  asm int MouseInt;
 }

int MouseExists()
 {
   return(swMouse&MouseActive);
 }

void ShowMouseCursor()
 {
  if (swMouse&MouseActive)
   {
    asm mov ax,0x01;
    asm int MouseInt;
   }
 }

void HideMouseCursor()
 {
  if (swMouse&MouseActive)
   {
    asm mov ax,0x02;
    asm int MouseInt;
   }
 }

void MouseClix(void)
 {
  if (swMouse&MouseActive)
   {
    asm mov ax,0x03;
    asm int MouseInt;
    asm mov [[ms_x]],cx;
    asm mov [[ms_y]],dx;
    asm mov [[ms_Clix]],bx;
    ms_x /= ms_xSiz;
    ms_y /= ms_ySiz;
   }
 }

void FlushMouse()
 {
  while (ms_Clix)
   MouseClix();
 }

void  SetMouseCurPos(int X,int Y)
 {
  if (swMouse&MouseActive)
   {
    X *= ms_xSiz;
    Y *= ms_ySiz;
    asm mov ax,0x04;
    asm mov cx,[X];
    asm mov dx,[Y];
    asm int MouseInt;
   }
 }

void GetMouseBtnPress(int WhichBtn)
 {
  if (swMouse&MouseActive)
   {
    WhichBtn %= 3;
    asm mov ax,0x05;
    asm mov bx,[WhichBtn];
    asm int MouseInt;
    asm mov [[ms_x]],cx;
    asm mov [[ms_y]],dx;
    asm mov [[ms_Clix]],ax;
    asm mov [[ms_PressCnt]],bx;
    ms_x   /= ms_xSiz;
    ms_y   /= ms_ySiz;
    swMouse = (swMouse&MaskPressBit)^MousePress;
  /*
	 MouseReg.x.ax = 0x05;
    MouseReg.x.bx = WhichBtn%3;

    int86( 0x33,&MouseReg,&MouseReg );
    ms_x        = MouseReg.x.cx/ms_xSiz;
    ms_y        = MouseReg.x.dx/ms_xSiz;
    ms_Clix     = MouseReg.x.ax;
    swMouse = (swMouse&MaskPressBit)^MousePress;
    ms_PressCnt = MouseReg.x.bx;*/
   }
  }

void GetMouseBtnRelease(int WhichBtn)
 {
  if (swMouse&MouseActive)
   {
    WhichBtn %= 3;
    asm mov ax,0x06;
    asm mov bx,[WhichBtn];
    asm int MouseInt;
    asm mov [[ms_x]],cx;
    asm mov [[ms_y]],dx;
    asm mov [[ms_Clix]],ax;
    asm mov [[ms_ReleaseCnt]],bx;
    ms_x   /= ms_xSiz;
    ms_y   /= ms_ySiz;
    swMouse = (swMouse&MaskReleaseBit)^MouseRelease;
    /*
	 MouseReg.x.ax = 0x06;
    MouseReg.x.bx = WhichBtn%3;

	 int86( 0x33,&MouseReg,&MouseReg );
    ms_x          = MouseReg.x.cx/ms_xSiz;
    ms_y          = MouseReg.x.dx/ms_xSiz;
    ms_Clix       = MouseReg.x.ax;
    swMouse     = (swMouse&MaskReleaseBit)^MouseRelease;
    ms_ReleaseCnt = MouseReg.x.bx;*/
   }
 }

void SetMouseCurWin(int Up_Lf_X,int Up_Lf_Y,
                                 int Dn_Rt_X,int Dn_Rt_Y)
 {
  if (swMouse&MouseActive)
   {
    Up_Lf_X *= ms_xSiz;
    Dn_Rt_X *= ms_xSiz;
    Up_Lf_Y *= ms_ySiz;
    Dn_Rt_Y *= ms_ySiz;

    asm mov ax,0x07;
    asm mov cx,[Up_Lf_X];
    asm mov dx,[Dn_Rt_X];
    asm int MouseInt;

    asm mov ax,0x08;
    asm mov cx,[Up_Lf_Y];
    asm mov dx,[Dn_Rt_Y];
    asm int MouseInt;
   }
 }
void SetMousePointerShape(int xHotSpotOff,int yHotSpotOff,void far *Buf)
 {
  int wSeg = FP_SEG(Buf);
  int wOff = FP_OFF(Buf);
  asm mov ax,0x09;
  asm mov bx,[xHotSpotOff];
  asm mov cx,[yHotSpotOff];
  asm mov dx,[wSeg];
  asm mov es,dx;
  asm mov dx,[wOff];
  asm int 0x33;
 }

void SoftMouseCursor(Word AndMask,Word XorMask)
 {
  if (swMouse&MouseActive)
   {
    asm mov ax,0x0A;
    asm mov bx,0;
    asm mov cx,[AndMask];
    asm mov dx,[XorMask];
    asm int MouseInt;
   }
 }

void HardMouseCursor(Word StartLn,Word EndLn)
 {
  if (swMouse&MouseActive)
   {
    asm mov ax,0x0A;
    asm mov bx,1;
    asm mov cx,[StartLn];
    asm mov dx,[EndLn];
    asm int MouseInt;
   }
 }

void MouseMotionCounter()
 {
  if (swMouse&MouseActive)
   {
    asm mov ax,0x0B;
    asm int MouseInt;
    asm mov word ptr [ms_Inf.xMickeyCnt],cx;
    asm mov word ptr [ms_Inf.yMickeyCnt],dx;
	 /*MouseReg.x.ax = 0x0B;

	 int86( 0x33,&MouseReg,&MouseReg );

    ms_Inf.xMickeyCnt = MouseReg.x.cx;
    ms_Inf.yMickeyCnt = MouseReg.x.dx;*/
   }
 }

void SetUserMouseEventHandler(word EvtMask,isr Handle)
 {
    EventHndl.r_ax = 0x0C;
    EventHndl.r_cx = EvtMask;
    EventHndl.r_es = FP_SEG(Handle);
    EventHndl.r_dx = FP_OFF(Handle);

    intr( 0x33,&EventHndl);
    /*
    word wSeg = FP_SEG(Handle);
    word wOff = FP_OFF(Handle);
    asm push es;
    asm mov  ax,0x000C;
    asm mov  cx,EvtMask;
    asm mov  dx,wSeg;
    asm mov  es,dx;
    asm mov  dx,wOff;
    asm int  MouseInt;
    asm pop  es;               */
 }
void SetLightPenEmulate(bool State)
 {
  if (swMouse&MouseActive)
   {
    /*if (State)
     asm mov ax,0x0D;
    else
     asm mov ax,0x0E;
    asm int MouseInt;*/

    MouseReg.x.ax = (State) ? 0x0D:0x0E;
    int86( 0x33,&MouseReg,&MouseReg );
   }
 }


void SetMickeysToPixRatio(int xMickey,int yMickey)
 {
  if (swMouse&MouseActive)
   {
    asm mov ax,0x0F;
    asm mov cx,[xMickey];
    asm mov dx,[yMickey];
    asm int MouseInt;
   }
 }

void SetMouseCurWinX(int Up_Lf_X,int Up_Lf_Y,
                                  int Dn_Rt_X,int Dn_Rt_Y)
 {
  if (swMouse&MouseActive)
   {
    Up_Lf_X *= ms_xSiz;
    Up_Lf_Y *= ms_ySiz;
    Dn_Rt_X *= ms_xSiz;
    Dn_Rt_Y *= ms_ySiz;
    asm mov ax,0x10;
    asm mov cx,[Up_Lf_X];
    asm mov dx,[Up_Lf_Y];
    asm mov si,[Dn_Rt_X];
    asm mov di,[Dn_Rt_Y];
    asm int MouseInt;
    /*MouseReg.x.ax = 0x10;
    MouseReg.x.cx = Up_Lf_X*ms_xSiz;
    MouseReg.x.dx = Up_Lf_Y*ms_ySiz;
    MouseReg.x.si = Dn_Rt_X*ms_xSiz;
    MouseReg.x.di = Dn_Rt_Y*ms_ySiz;

    int86( 0x33,&MouseReg,&MouseReg );*/
   }
 }

void SetDoubleSpeed(int Speed)
 {
  if (swMouse&MouseActive)
   {
    asm mov ax,0x13;
    asm mov dx,[Speed];
    asm int MouseInt;
	/* MouseReg.x.ax = 0x13;
    MouseReg.x.dx = Speed;

	 int86( 0x33,&MouseReg,&MouseReg );*/
   }
 }

void SwapEventHandler(word EvtMask,isr NewEvt,Handler *Hndl)
 {
  /*  word wSeg = FP_SEG(NewEvt);
    word wOff = FP_OFF(NewEvt);
    word wMask;
    asm push es;
    asm mov  ax,0x14;
    asm mov  cx,[EvtMask];
    asm mov  dx,[wSeg];
    asm mov  es,dx;
    asm mov  dx,[wOff];
    asm int  MouseInt;
    asm mov  [[wMask]],cx;
    asm mov  [[wSeg]],es;
    asm mov  [[wOff]],dx;
    asm pop  es;
    Hndl->EvtMask = wMask;
    Hndl->EvtHndl = (isr)MK_FP(wSeg,wOff);*/

    EventHndl.r_ax = 0x14;
    EventHndl.r_cx = EvtMask;
    EventHndl.r_es = FP_SEG(NewEvt);
    EventHndl.r_dx = FP_OFF(NewEvt);

    intr( 0x33,&EventHndl);
    Hndl->EvtMask = EventHndl.r_cx;
    Hndl->EvtHndl = (isr)MK_FP(EventHndl.r_es,EventHndl.r_dx);
 }
int GetMouseSavStateSiz()
 {
  int rvSavStateSiz=0;
  if (swMouse&MouseActive)
   {
    asm mov ax,0x15;
    asm int MouseInt;
    asm mov [[rvSavStateSiz]],bx;
/*  MouseReg.x.ax = 0x15;

    int86( 0x33,&MouseReg,&MouseReg );
    return(MouseReg.x.bx);*/
   }
  return(rvSavStateSiz);
 }

void SaveMouseDrvState(Word DrvSegment,Word DrvOffset)
 {
  if (swMouse&MouseActive)
   {
    asm mov ax,0x16;
    asm mov dx,[DrvSegment];
    asm mov es,dx;
    asm mov dx,[DrvOffset];
    asm int MouseInt;
  /*EventHndl.r_ax = 0x16;
    EventHndl.r_es = Segment;
    EventHndl.r_dx = Offset;

    intr( 0x33,&EventHndl);*/
   }
 }

void RestoreMouseDrvState(Word DrvSegment,Word DrvOffset)
 {
  if (swMouse&MouseActive)
   {
    asm mov ax,0x17;
    asm mov dx,[DrvSegment];
    asm mov es,dx;
    asm mov dx,[DrvOffset];
    asm int MouseInt;
/*  EventHndl.r_ax = 0x17;
    EventHndl.r_es = Segment;
    EventHndl.r_dx = Offset;

    intr( 0x33,&EventHndl);*/
   }
 }

int SetAlternateMouseHandler(word EvtMask,isr Hndl)
 {
    EventHndl.r_ax = 0x18;
    EventHndl.r_cx = EvtMask;
    EventHndl.r_es = FP_SEG(Hndl);
    EventHndl.r_dx = FP_OFF(Hndl);

    intr( 0x33,&EventHndl);
    return((EventHndl.r_ax == 0x18));
 }

int GetAlternateMouseHandler(word EvtMask,Handler *Hndl)
 {
    EventHndl.r_ax = 0x19;
    EventHndl.r_cx = EvtMask;
    intr( 0x33,&EventHndl);
    Hndl->EvtMask = EventHndl.r_cx;
    Hndl->EvtHndl = (isr)MK_FP(EventHndl.r_es,EventHndl.r_dx);
    return((EventHndl.r_cx == 0));
 }

void SetMouseSensitivity(int xMic,int yMic,int DblSpeed)
 {
  if (swMouse&MouseActive)
   {
    asm mov ax,0x1A;
    asm mov bx,[xMic];
    asm mov cx,[yMic];
    asm mov dx,[DblSpeed];
    asm int MouseInt;
   }
 }

void GetMouseSensitivity(int *xMic,int *yMic,int *DblSpeed)
 {
  if (swMouse&MouseActive)
   {
    /*asm mov ax,0x1B;
    asm int MouseInt;
    asm mov word ptr xMic,bx;
    asm mov [yMic],cx;
    asm mov [DblSpeed],dx;*/

    MouseReg.x.ax = 0x1B;

    int86( 0x33,&MouseReg,&MouseReg );
    *xMic     = MouseReg.x.bx;
    *yMic     = MouseReg.x.cx;
    *DblSpeed = MouseReg.x.dx;
   }
 }

void SetMouseIntrRate(int IntrFlag)
 {
  if (swMouse&MouseActive)
   {
    asm mov ax,0x1C;
    asm mov ax,[IntrFlag];
    asm int MouseInt;
   }
 }

void SetMouseCurPage(int PageNo)
 {
  if (swMouse&MouseActive)
   {
    asm mov ax,0x1D;
    asm mov ax,[PageNo];
    asm int MouseInt;
   }
 }

int DisableMouseDriver(Handler *Hndl)
 {
  Hndl->EvtHndl = (isr)NULL;
  if (swMouse&MouseActive)
   {
     EventHndl.r_ax = 0x1F;

     intr( 0x33,&EventHndl);

    if (EventHndl.r_ax == 0x1F)
     {
       Hndl->EvtHndl = (isr)MK_FP(EventHndl.r_es,EventHndl.r_dx);
       return(1);
     }
   }
  return(0);
 }

void EnableMouseDriver()
 {
  if (swMouse&MouseActive)
   {
    asm mov ax,0x20;
    asm int MouseInt;
   }
 }

int ResetMouseDriver()
 {
  MouseReg.x.ax = 0x21;
  int86( 0x33,&MouseReg,&MouseReg );

  if (MouseReg.x.ax == 0xFFFF)
   {
     swMouse = 1;
     ms_Clix = MouseReg.x.bx;
//     swMouse ^= (MouseReg.x.bx <<1);
     return(1);
   }
  else
    return(0);
 }

void GetMouseInfo()
 {
  if (swMouse&MouseActive)
   {
     MouseReg.x.ax = 0x24;

     int86( 0x33,&MouseReg,&MouseReg );
     ms_Inf.MajVerNo  = MouseReg.h.bh;
     ms_Inf.MinVerNo  = MouseReg.h.bl;
     ms_Inf.MouseType = MouseReg.h.ch;
     ms_Inf.MouseIRQ  = MouseReg.h.cl;
   }
 }
