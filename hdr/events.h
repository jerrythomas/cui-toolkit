#ifndef __EVENTS_H
#define __EVENTS_H

#include <CuiBase.h>

#define cwMouseMove                0x0001
#define cwMouseLeftClick           0x0002
#define cwMouseLeftBtnUp           0x0004
#define cwMouseRightClick          0x0008
#define cwMouseRightBtnUp          0x0010
#define cwMouseMiddleClick         0x0020
#define cwMouseMiddleBtnUp         0x0040

#define cwMouseMoveWithShift       0x0021
#define cwMouseLeftClickWithShift  0x0022
#define cwMouseLeftBtnUpWithShift  0x0024
#define cwMouseRightClickWithShift 0x0028
#define cwMouseRightBtnUpWithShift 0x0030

#define cwMouseMoveWithCtrl        0x0041
#define cwMouseLeftClickWithCtrl   0x0042
#define cwMouseLeftBtnUpWithCtrl   0x0044
#define cwMouseRightClickWithCtrl  0x0048
#define cwMouseRightBtnUpWithCtrl  0x0050

#define cwMouseMoveWithAlt         0x0081
#define cwMouseLeftClickWithAlt    0x0082
#define cwMouseLeftBtnUpWithAlt    0x0084
#define cwMouseRightClickWithAlt   0x0088
#define cwMouseRightBtnUpWithAlt   0x0090

#define cwAllUserMouseEvents       0x007F
#define cwAllMouseEventsWithShift  0x003F
#define cwAllMouseEventsWithCtrl   0x005F
#define cwAllMouseEventsWithAlt    0x009F


const isr BiosKbd=(isr)MK_FP(0x22F3,0x10A3);


class Event;     // dummy declaration
class Despatch;  // dummy declaration
struct EventGroup
 {
   Event   *Evt;   // Pointer to event
 };

// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>                 Event Definition Class                  <<>>
// <<>>                     Version   1.0                       <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>        Mouse Control Events                             <<>>
// <<>>        Keyboard Events                                  <<>>
// <<>>        Generic Events                                   <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

#define EventAppMain    0x00
#define EventForm       0x01

#define EventMenu       0x07
#define EventTag        0x08
#define EventTagSheet   0x09
#define EventFrame      0x0A

#define EventLabel      0x0B
#define EventGauge      0x0C
#define EventButton     0x0D
#define EventHScroll    0x0E
#define EventVScroll    0x0F

#define EventTxtBox     0x10
#define EventIntBox     0x11
#define EventFloatBox   0x12

#define EventCheck      0x13
#define EventRadio      0x14
#define EventComboBox   0x15


class Event
 {
   protected :
     word       EventID;

   public    :
     Despatch  *Hndl;

   public :

    Event();

    virtual bool KeyPress(word Key) ;
    virtual bool KeyUp   (word Key) ;
    virtual bool KeyDown (word Key) ;

    virtual bool MouseMove       (int mx,int my) ;
    virtual bool MouseLeftClick  (int mx,int my) ;
    virtual bool MouseLeftBtnUp  (int mx,int my) ;
    virtual bool MouseRightClick (int mx,int my) ;
    virtual bool MouseRightBtnUp (int mx,int my) ;
    virtual bool MouseMiddleClick(int mx,int my) ;
    virtual bool MouseMiddleBtnUp(int mx,int my) ;

    virtual bool MouseMoveWithShift      (int mx,int my) ;
    virtual bool MouseLeftClickWithShift (int mx,int my) ;
    virtual bool MouseLeftBtnUpWithShift (int mx,int my) ;
    virtual bool MouseRightClickWithShift(int mx,int my) ;
    virtual bool MouseRightBtnUpWithShift(int mx,int my) ;

    virtual bool MouseMoveWithCtrl      (int mx,int my) ;
    virtual bool MouseLeftClickWithCtrl (int mx,int my) ;
    virtual bool MouseLeftBtnUpWithCtrl (int mx,int my) ;
    virtual bool MouseRightClickWithCtrl(int mx,int my) ;
    virtual bool MouseRightBtnUpWithCtrl(int mx,int my) ;

    virtual bool MouseMoveWithAlt      (int mx,int my) ;
    virtual bool MouseLeftClickWithAlt (int mx,int my) ;
    virtual bool MouseLeftBtnUpWithAlt (int mx,int my) ;
    virtual bool MouseRightClickWithAlt(int mx,int my) ;
    virtual bool MouseRightBtnUpWithAlt(int mx,int my) ;

    virtual bool ShowX();
    virtual bool Show();
    virtual bool Refresh();
    virtual bool Close();

    virtual bool SetFocus();
    virtual bool SetFocus(Event *Evt);
    virtual bool LostFocus();
    virtual bool GotFocus();
    virtual bool Change();

    friend class Despatch;
  };

// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>                 Event Despatcher Class                  <<>>
// <<>>                     Version   1.0                       <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

#define HndlEvent       0x8000
#define HndlMenu        0x4000

#define HandleEvent     0x2000
#define HandleMenu      0x1000

#define AddedDespatch   0x2000
#define AddedMenu       0x1000

#define Responds        0x0200
#define EvtActive       0x0100

#define EventCode       0x00FF

class Despatch : public Event
 {
   private :
     Event       *Parent;
     Event       *EvtMenu;
     Event       *ActEvt;

     EventGroup  *Grp;
     byte         AllocSize;
     byte         GrpIdx;
     byte         GrpSize;
     word         KeyAhead,
                  KeyBack;

   public :

    Despatch(Event *Par,byte Size);
    ~Despatch();

    void    SetKeys(word Back,word Ahead);

    byte    AddEvent   (Event *Evt);
    byte    AddMenu    (Event *Evt);
    byte    RemoveEvent(Event *Evt);

    virtual bool KeyPress(word Key) ;
    virtual bool KeyUp   (word Key) ;
    virtual bool KeyDown (word Key) ;


    virtual bool MouseMove       (int mx,int my) ;
    virtual bool MouseLeftClick  (int mx,int my) ;
    virtual bool MouseLeftBtnUp  (int mx,int my) ;
    virtual bool MouseRightClick (int mx,int my) ;
    virtual bool MouseRightBtnUp (int mx,int my) ;
    virtual bool MouseMiddleClick(int mx,int my) ;
    virtual bool MouseMiddleBtnUp(int mx,int my) ;

    virtual bool MouseMoveWithShift      (int mx,int my) ;
    virtual bool MouseLeftClickWithShift (int mx,int my) ;
    virtual bool MouseLeftBtnUpWithShift (int mx,int my) ;
    virtual bool MouseRightClickWithShift(int mx,int my) ;
    virtual bool MouseRightBtnUpWithShift(int mx,int my) ;

    virtual bool MouseMoveWithCtrl      (int mx,int my) ;
    virtual bool MouseLeftClickWithCtrl (int mx,int my) ;
    virtual bool MouseLeftBtnUpWithCtrl (int mx,int my) ;
    virtual bool MouseRightClickWithCtrl(int mx,int my) ;
    virtual bool MouseRightBtnUpWithCtrl(int mx,int my) ;

    virtual bool MouseMoveWithAlt      (int mx,int my) ;
    virtual bool MouseLeftClickWithAlt (int mx,int my) ;
    virtual bool MouseLeftBtnUpWithAlt (int mx,int my) ;
    virtual bool MouseRightClickWithAlt(int mx,int my) ;
    virtual bool MouseRightBtnUpWithAlt(int mx,int my) ;

    virtual bool ShowX();
    virtual bool Show();
    virtual bool Refresh();
    virtual bool Close();

    virtual bool SetFocus();
    virtual bool SetFocus(Event *Evt);
    virtual bool LostFocus();
    virtual bool GotFocus();
    virtual bool Change();

  };

// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>                 Interrupt Vector Setup                  <<>>
// <<>>                     Version   1.0                       <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

class IVT
 {
   protected :
    isr       OldKbVec;
    Handler   MouseEvt[4];

   public  :
    IVT();
    ~IVT();

 };

// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>               Interrupt Service Routines                <<>>
// <<>>                     Version   1.0                       <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
void interrupt far KeyPress(...) ;
void interrupt far KeyUp   (...) ;
void interrupt far KeyDown (...) ;


void interrupt far AllMouseEvents   (...);
void interrupt far EvtMouseWithShift(...);
void interrupt far EvtMouseWithCtrl (...);
void interrupt far EvtMouseWithAlt  (...);
/*
void interrupt far MouseMove       (...);
void interrupt far MouseLeftClick  (...);
void interrupt far MouseUp         (...);
void interrupt far MouseRightClick (...);
void interrupt far MouseRightBtnUp (...);
void interrupt far MouseMiddleClick(...);
void interrupt far MouseMiddleBtnUp(...);

void interrupt far MouseMoveWithShift      (...);
void interrupt far MouseLeftClickWithShift (...);
void interrupt far MouseLeftBtnUpWithShift (...);
void interrupt far MouseRightClickWithShift(...);
void interrupt far MouseRightBtnUpWithShift(...);

void interrupt far MouseMoveWithCtrl      (...);
void interrupt far MouseLeftClickWithCtrl (...);
void interrupt far MouseLeftBtnUpWithCtrl (...);
void interrupt far MouseRightClickWithCtrl(...);
void interrupt far MouseRightBtnUpWithCtrl(...);

void interrupt far MouseMoveWithAlt      (...);
void interrupt far MouseLeftClickWithAlt (...);
void interrupt far MouseLeftBtnUpWithAlt (...);
void interrupt far MouseRightClickWithAlt(...);
void interrupt far MouseRightBtnUpWithAlt(...);
  */
extern Event *EvtMain;

#endif