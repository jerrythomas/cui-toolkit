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