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
Event    *EvtMain;
Despatch *ActiveHndl;

// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>                   Event Class Modules                   <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

#pragma warn -par
Event::Event()
 {
   EventID = 0x0000;
   Hndl    = (Despatch*)NULL;
 }
bool Event:: KeyPress(word Key) {return false;}
bool Event:: KeyUp   (word Key) {return false;}
bool Event:: KeyDown (word Key) {return false;}

bool Event:: MouseMove       (int mx,int my) {return false;}
bool Event:: MouseLeftClick  (int mx,int my) {return false;}
bool Event:: MouseLeftBtnUp  (int mx,int my) {return false;}
bool Event:: MouseRightClick (int mx,int my) {return false;}
bool Event:: MouseRightBtnUp (int mx,int my) {return false;}
bool Event:: MouseMiddleClick(int mx,int my) {return false;}
bool Event:: MouseMiddleBtnUp(int mx,int my) {return false;}

bool Event:: MouseMoveWithShift      (int mx,int my) {return false;}
bool Event:: MouseLeftClickWithShift (int mx,int my) {return false;}
bool Event:: MouseLeftBtnUpWithShift (int mx,int my) {return false;}
bool Event:: MouseRightClickWithShift(int mx,int my) {return false;}
bool Event:: MouseRightBtnUpWithShift(int mx,int my) {return false;}

bool Event:: MouseMoveWithCtrl      (int mx,int my) {return false;}
bool Event:: MouseLeftClickWithCtrl (int mx,int my) {return false;}
bool Event:: MouseLeftBtnUpWithCtrl (int mx,int my) {return false;}
bool Event:: MouseRightClickWithCtrl(int mx,int my) {return false;}
bool Event:: MouseRightBtnUpWithCtrl(int mx,int my) {return false;}

bool Event:: MouseMoveWithAlt      (int mx,int my) {return false;}
bool Event:: MouseLeftClickWithAlt (int mx,int my) {return false;}
bool Event:: MouseLeftBtnUpWithAlt (int mx,int my) {return false;}
bool Event:: MouseRightClickWithAlt(int mx,int my) {return false;}
bool Event:: MouseRightBtnUpWithAlt(int mx,int my) {return false;}

bool Event:: ShowX()              {return false;}
bool Event:: Show()               {return false;}
bool Event:: Refresh()            {return false;}
bool Event:: Close()              {return false;}

bool Event:: SetFocus()
 {
  bool rvHndl = false;
  if (EvtMain != (Event*)NULL)
     if (EvtMain->Hndl != (Despatch*)NULL)
        rvHndl=EvtMain->Hndl->SetFocus(this);
  return rvHndl;
 }
bool Event:: SetFocus(Event *Evt) {return false;}
bool Event:: LostFocus()          {return false;}
bool Event:: GotFocus()           {return false;}
bool Event:: Change()             {return false;}


#pragma warn +par

// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>             Event Despatcher Class Modules              <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>


#pragma warn -par

Despatch::Despatch(Event *Par,byte Size):Event()
 {
   EvtMenu  = (Event*)NULL;
   ActEvt   = (Event*)NULL;
   Parent   = Par;
   GrpIdx   = 0;
   GrpSize  = 0;
   KeyAhead = TabKy;
   KeyBack  = Shft_TabKy;
   EventID  = Parent->EventID&0xC0FF;
   Parent->EventID |= AddedDespatch;

   Grp      = new EventGroup[Size];
   for(AllocSize=0;AllocSize<Size;AllocSize++)
     Grp[AllocSize].Evt = (Event*)NULL;
 }
Despatch::~Despatch()
 {
   Parent->EventID ^= AddedDespatch;
   Parent   = (Event*)NULL;
   EvtMenu  = (Event*)NULL;
   ActEvt   = (Event*)NULL;

   for(GrpIdx=0;GrpIdx < GrpSize;GrpIdx++)
       Grp[GrpIdx].Evt = (Event*)NULL;
   delete Grp;
 }
void Despatch::SetKeys(word Back,word Ahead)
 {
   KeyBack  = Back;
   KeyAhead = Ahead;
 }
byte Despatch::AddEvent(Event *Evt)
 {
   byte rvFlag = 0x01;
   if ((Evt->EventID&EventCode) > (EventID&EventCode))
   if (GrpSize < AllocSize)
    {
     Grp[GrpSize].Evt = Evt;
     GrpSize++;
     if (ActEvt == (Event*)NULL)
        ActEvt = Grp[0].Evt;
     rvFlag = 0x00;
    }
   return rvFlag;
 }
byte Despatch::AddMenu(Event *Evt)
 {
   byte rvFlag =0x00;
   if (EvtMenu==(Event*)NULL && Evt->EventID&EventCode == EventMenu)
    {
      EvtMenu  = Evt;
      EventID |= AddedMenu;
    }
   else
     rvFlag = 0x01;
   return rvFlag;

 }
byte Despatch::RemoveEvent(Event *Evt)
 {
   byte rvFlag = 0x00;
   if (GrpSize>0)
    {
     for(int i=0;i<GrpSize;i++)
       if (Evt == Grp[i].Evt)
        {
          //Grp[i].Evt->Terminate();
          Grp[i].Evt = (Event*)NULL; // possibly issue terminate
          for (i++;i<GrpSize;i++)
            Grp[i-1].Evt = Grp[i].Evt;
          Grp[GrpSize].Evt = (Event*)NULL;
          GrpSize--;
          rvFlag = 0x01;
        }
    }
   return rvFlag;
 }

// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>       Event Despatcher  : Keyboard Handler              <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

bool Despatch::KeyDown(word Key)
 {
   bool rvHndl=false;
   int  i;

   /*if ((EventID&HandleMenu) && ActEvt == EvtMenu)
    {
      rvHndl = ActEvt->KeyDown(Key);
      if (!(ActEvt->EventID&EvtActive))
         ActEvt = Grp[GrpIdx].Evt;
    }
   else if (Key == KeyAhead && GrpSize>0)
    {
     if (Grp[GrpIdx].Evt->EventID&HandleEvent)
        rvHndl = Grp[GrpIdx].Evt->Hndl->KeyDown(Key);
     if (!rvHndl && GrpIdx < GrpSize-1)
      {
       if (Grp[GrpIdx+1].Evt != (Event*)NULL)
         for (i=GrpIdx;i<GrpSize && !rvHndl;i++)
          if (Grp[i].Evt->EventID&Responds)
	   {
            GrpIdx = i;
            ActEvt = Grp[GrpIdx].Evt;
            rvHndl = true;
           }
      }
     else if (!rvHndl && ((EventID&EventCode) < EventTagSheet))
       {
        //rvHndl = Parent->KeyDown(Key);
        for (i=0;i<GrpSize && !rvHndl;i++)
         if (Grp[i].Evt->EventID&Responds)
	   {
            GrpIdx = i;
            ActEvt = Grp[GrpIdx].Evt;
            rvHndl = true;
           }
       }
    }
   else if (Key == KeyBack && GrpSize>0)
    {
     if (Grp[GrpIdx].Evt->EventID&HandleEvent)
        rvHndl = Grp[GrpIdx].Evt->Hndl->KeyDown(Key);
     if (!rvHndl && GrpIdx > 0)
      {
        for (i=GrpIdx-1;i>=0 && !rvHndl;i--)
         if (Grp[i].Evt->EventID&Responds)
	  {
           GrpIdx = i;
           ActEvt = Grp[GrpIdx].Evt;
           rvHndl = true;
          }
      }
     else if (!rvHndl && ((EventID&EventCode) < EventTagSheet))
       {
        //rvHndl = Parent->Keydown(Key);
        for (i=GrpSize;i>0 && Grp[i].Evt == (Event*)NULL;i--)
        for ( ;i<0 && !rvHndl;i--)
         if (Grp[i].Evt->EventID&Responds)
	   {
            GrpIdx = i;
            ActEvt = Grp[GrpIdx].Evt;
            rvHndl = true;
           }
       }
    }
   else*/
   if (Key > 0xFF)   // Special Code
    {
     rvHndl = Parent->KeyDown(Key);
     if (rvHndl) xPrintf(20,18,"Handled by Parent Key %X ",Key);
     if (!rvHndl)
      {
       //if (EventID&HandleMenu)
       //  rvHndl = EvtMenu->KeyDown(Key);
       //if (rvHndl)
        // ActEvt = EvtMenu;
       //else
       // {
         xPrintf(20,19,"Not handled by parent %X ,Key");
         if (ActEvt != (Event*)NULL)
             rvHndl = ActEvt->KeyDown(Key);
         if (rvHndl) xPrintf(20,20,"Handled by Active Event Key %X ",Key);
       /*	 for (i=0;i<GrpSize && !rvHndl;i++)
            if (Grp[i].Evt->EventID&HandleEvent)
               rvHndl = Grp[i].Evt->Hndl->KeyDown(Key);
            else
               rvHndl = Grp[i].Evt->KeyDown(Key);
        */
         if (rvHndl)
          {
            GrpIdx = i;
            ActEvt = Grp[GrpIdx].Evt;
          }
       // }
      }
    }
   else if (ActEvt != (Event*)NULL)
     rvHndl = ActEvt->KeyDown(Key);

   return rvHndl;
 }


// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>       Event Despatcher  : Mouse Only Events             <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

bool Despatch::MouseMove(int mx,int my)
 {
  bool rvHndl=false;
  if ((EventID&HandleMenu) && ActEvt == EvtMenu)
   {
     rvHndl = ActEvt->MouseMove(mx,my);
     if (!(ActEvt->EventID&EvtActive))
        ActEvt = Grp[GrpIdx].Evt;
   }
  else
   {
     for (int i=0;!rvHndl && i<GrpSize;i++)
        if (Grp[i].Evt->EventID&Responds)
         {
	  if (Grp[i].Evt->EventID&HandleEvent)
             rvHndl = Grp[i].Evt->Hndl->MouseMove(mx,my);
          if (!rvHndl)
	     rvHndl = Grp[i].Evt->MouseMove(mx,my);
          if (rvHndl)
           {
            GrpIdx = i;
            ActEvt = Grp[GrpIdx].Evt;
           }
         }
     if (!rvHndl && EventID&HandleMenu)
      {
        rvHndl = EvtMenu->MouseMove(mx,my);
        if (EvtMenu->EventID&EvtActive)
          ActEvt = EvtMenu;
      }
     if (!rvHndl)
        rvHndl = Parent->MouseMove(mx,my);
   }
  return rvHndl;
 }
bool Despatch::MouseLeftClick(int mx,int my)
 {
  bool rvHndl=false;
  if ((EventID&HandleMenu) && ActEvt == EvtMenu)
   {
     rvHndl = ActEvt->MouseLeftClick(mx,my);
     if (!(ActEvt->EventID&EvtActive))
        ActEvt = Grp[GrpIdx].Evt;
   }
  else
   {
     for (int i=0;!rvHndl && i<GrpSize ;i++)
        if (Grp[i].Evt->EventID&Responds)
         {
	  if (Grp[i].Evt->EventID&HandleEvent)
            rvHndl = Grp[i].Evt->Hndl->MouseLeftClick(mx,my);
          if (!rvHndl)
	    rvHndl = Grp[i].Evt->MouseLeftClick(mx,my);
          if (rvHndl)
           {
            GrpIdx = i;
            ActEvt = Grp[GrpIdx].Evt;
           }
         }
     if (!rvHndl && EventID&HandleMenu)
      {
        rvHndl = EvtMenu->MouseLeftClick(mx,my);
        if (EvtMenu->EventID&EvtActive)
          ActEvt = EvtMenu;
      }
     if (!rvHndl)
        rvHndl = Parent->MouseLeftClick(mx,my);
   }
  return rvHndl;
 }
bool Despatch::MouseLeftBtnUp(int mx,int my)
 {
  bool rvHndl=false;
  if ((EventID&HandleMenu) && ActEvt == EvtMenu)
   {
     rvHndl = ActEvt->MouseLeftBtnUp(mx,my);
     if (!(ActEvt->EventID&EvtActive))
        ActEvt = Grp[GrpIdx].Evt;
   }
  else
   {
     for (int i=0;!rvHndl && i<GrpSize ;i++)
        if (Grp[i].Evt->EventID&Responds)
         {
	  if (Grp[i].Evt->EventID&HandleEvent)
            rvHndl = Grp[i].Evt->Hndl->MouseLeftBtnUp(mx,my);
          if (!rvHndl)
	    rvHndl = Grp[i].Evt->MouseLeftBtnUp(mx,my);
          if (rvHndl)
           {
            GrpIdx = i;
            ActEvt = Grp[GrpIdx].Evt;
           }
         }
     if (!rvHndl && EventID&HandleMenu)
      {
        rvHndl = EvtMenu->MouseLeftBtnUp(mx,my);
        if (EvtMenu->EventID&EvtActive)
          ActEvt = EvtMenu;
      }
     if (!rvHndl)
        rvHndl = Parent->MouseLeftBtnUp(mx,my);
   }
  return rvHndl;
 }
bool Despatch:: MouseRightClick(int mx,int my)
 {
  bool rvHndl=false;
  if ((EventID&HandleMenu) && ActEvt == EvtMenu)
   {
     rvHndl = ActEvt->MouseRightClick(mx,my);
     if (!(ActEvt->EventID&EvtActive))
        ActEvt = Grp[GrpIdx].Evt;
   }
  else
   {
     for (int i=0;!rvHndl && i<GrpSize ;i++)
        if (Grp[i].Evt->EventID&Responds)
         {
	  if (Grp[i].Evt->EventID&HandleEvent)
            rvHndl = Grp[i].Evt->Hndl->MouseRightClick(mx,my);
          if (!rvHndl)
	    rvHndl = Grp[i].Evt->MouseRightClick(mx,my);
          if (rvHndl)
           {
            GrpIdx = i;
            ActEvt = Grp[GrpIdx].Evt;
           }
         }
     if (!rvHndl && EventID&HandleMenu)
      {
        rvHndl = EvtMenu->MouseRightClick(mx,my);
        if (EvtMenu->EventID&EvtActive)
          ActEvt = EvtMenu;
      }
     if (!rvHndl)
        rvHndl = Parent->MouseRightClick(mx,my);
   }
  return rvHndl;
 }
bool Despatch:: MouseRightBtnUp(int mx,int my)
 {
  bool rvHndl=false;
  if ((EventID&HandleMenu) && ActEvt == EvtMenu)
   {
     rvHndl = ActEvt->MouseRightBtnUp(mx,my);
     if (!(ActEvt->EventID&EvtActive))
        ActEvt = Grp[GrpIdx].Evt;
   }
  else
   {
     for (int i=0;!rvHndl && i<GrpSize ;i++)
        if (Grp[i].Evt->EventID&Responds)
         {
	  if (Grp[i].Evt->EventID&HandleEvent)
             rvHndl = Grp[i].Evt->Hndl->MouseRightBtnUp(mx,my);
          if (!rvHndl)
	    rvHndl = Grp[i].Evt->MouseRightBtnUp(mx,my);
          if (rvHndl)
           {
            GrpIdx = i;
            ActEvt = Grp[GrpIdx].Evt;
           }
         }
     if (!rvHndl && EventID&HandleMenu)
      {
        rvHndl = EvtMenu->MouseRightBtnUp(mx,my);
        if (EvtMenu->EventID&EvtActive)
          ActEvt = EvtMenu;
      }
     if (!rvHndl)
        rvHndl = Parent->MouseRightBtnUp(mx,my);
   }
  return rvHndl;
 }
bool Despatch:: MouseMiddleClick(int mx,int my)
 {
  bool rvHndl=false;
  if ((EventID&HandleMenu) && ActEvt == EvtMenu)
   {
     rvHndl = ActEvt->MouseMiddleClick(mx,my);
     if (!(ActEvt->EventID&EvtActive))
        ActEvt = Grp[GrpIdx].Evt;
   }
  else
   {
     for (int i=0;!rvHndl && i<GrpSize ;i++)
        if (Grp[i].Evt->EventID&Responds)
         {
	  if (Grp[i].Evt->EventID&HandleEvent)
            rvHndl = Grp[i].Evt->Hndl->MouseMiddleClick(mx,my);
          if (!rvHndl)
	    rvHndl = Grp[i].Evt->MouseMiddleClick(mx,my);
          if (rvHndl)
           {
            GrpIdx = i;
            ActEvt = Grp[GrpIdx].Evt;
           }
         }
     if (!rvHndl && EventID&HandleMenu)
      {
        rvHndl = EvtMenu->MouseMiddleClick(mx,my);
        if (EvtMenu->EventID&EvtActive)
          ActEvt = EvtMenu;
      }
     if (!rvHndl)
        rvHndl = Parent->MouseMiddleClick(mx,my);
   }
  return rvHndl;
 }
bool Despatch:: MouseMiddleBtnUp(int mx,int my)
 {
  bool rvHndl=false;
  if ((EventID&HandleMenu) && ActEvt == EvtMenu)
   {
     rvHndl = ActEvt->MouseMiddleBtnUp(mx,my);
     if (!(ActEvt->EventID&EvtActive))
        ActEvt = Grp[GrpIdx].Evt;
   }
  else
   {
     for (int i=0;!rvHndl && i<GrpSize ;i++)
        if (Grp[i].Evt->EventID&Responds)
         {
	  if (Grp[i].Evt->EventID&HandleEvent)
            rvHndl = Grp[i].Evt->Hndl->MouseMiddleBtnUp(mx,my);
          if (!rvHndl)
	    rvHndl = Grp[i].Evt->MouseMiddleBtnUp(mx,my);
          if (rvHndl)
           {
            GrpIdx = i;
            ActEvt = Grp[GrpIdx].Evt;
           }
         }
     if (!rvHndl && EventID&HandleMenu)
      {
        rvHndl = EvtMenu->MouseMiddleBtnUp(mx,my);
        if (EvtMenu->EventID&EvtActive)
          ActEvt = EvtMenu;
      }
     if (!rvHndl)
        rvHndl = Parent->MouseMiddleBtnUp(mx,my);
   }
  return rvHndl;
 }

// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>                    Shift Key & Mouse                    <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

bool Despatch:: MouseMoveWithShift(int mx,int my)
 {
  bool rvHndl=false;
  if ((EventID&HandleMenu) && ActEvt == EvtMenu)
   {
     rvHndl = ActEvt->MouseMoveWithShift(mx,my);
     if (!(ActEvt->EventID&EvtActive))
        ActEvt = Grp[GrpIdx].Evt;
   }
  else
   {
     for (int i=0;!rvHndl && i<GrpSize ;i++)
        if (Grp[i].Evt->EventID&Responds)
         {
	  if (Grp[i].Evt->EventID&HandleEvent)
            rvHndl = Grp[i].Evt->Hndl->MouseMoveWithShift(mx,my);
          if (!rvHndl)
	    rvHndl = Grp[i].Evt->MouseMoveWithShift(mx,my);
          if (rvHndl)
           {
            GrpIdx = i;
            ActEvt = Grp[GrpIdx].Evt;
           }
         }
     if (!rvHndl && EventID&HandleMenu)
      {
        rvHndl = EvtMenu->MouseMoveWithShift(mx,my);
        if (EvtMenu->EventID&EvtActive)
          ActEvt = EvtMenu;
      }
     if (!rvHndl)
        rvHndl = Parent->MouseMoveWithShift(mx,my);
   }
  return rvHndl;
 }
bool Despatch:: MouseLeftClickWithShift(int mx,int my)
 {
  bool rvHndl=false;
  if ((EventID&HandleMenu) && ActEvt == EvtMenu)
   {
     rvHndl = ActEvt->MouseLeftClickWithShift(mx,my);
     if (!(ActEvt->EventID&EvtActive))
        ActEvt = Grp[GrpIdx].Evt;
   }
  else
   {
     for (int i=0;!rvHndl && i<GrpSize ;i++)
        if (Grp[i].Evt->EventID&Responds)
         {
	  if (Grp[i].Evt->EventID&HandleEvent)
            rvHndl = Grp[i].Evt->Hndl->MouseLeftClickWithShift(mx,my);
          if (!rvHndl)
	    rvHndl = Grp[i].Evt->MouseLeftClickWithShift(mx,my);
          if (rvHndl)
           {
            GrpIdx = i;
            ActEvt = Grp[GrpIdx].Evt;
           }
         }
     if (!rvHndl && EventID&HandleMenu)
      {
        rvHndl = EvtMenu->MouseLeftClickWithShift(mx,my);
        if (EvtMenu->EventID&EvtActive)
          ActEvt = EvtMenu;
      }
     if (!rvHndl)
        rvHndl = Parent->MouseLeftClickWithShift(mx,my);
   }
  return rvHndl;
 }
bool Despatch:: MouseLeftBtnUpWithShift(int mx,int my)
 {
  bool rvHndl=false;
  if ((EventID&HandleMenu) && ActEvt == EvtMenu)
   {
     rvHndl = ActEvt->MouseLeftBtnUpWithShift(mx,my);
     if (!(ActEvt->EventID&EvtActive))
        ActEvt = Grp[GrpIdx].Evt;
   }
  else
   {
     for (int i=0;!rvHndl && i<GrpSize ;i++)
        if (Grp[i].Evt->EventID&Responds)
         {
	  if (Grp[i].Evt->EventID&HandleEvent)
            rvHndl = Grp[i].Evt->Hndl->MouseLeftBtnUpWithShift(mx,my);
          if (!rvHndl)
	    rvHndl = Grp[i].Evt->MouseLeftBtnUpWithShift(mx,my);
          if (rvHndl)
           {
            GrpIdx = i;
            ActEvt = Grp[GrpIdx].Evt;
           }
         }
     if (!rvHndl && EventID&HandleMenu)
      {
        rvHndl = EvtMenu->MouseLeftBtnUpWithShift(mx,my);
        if (EvtMenu->EventID&EvtActive)
          ActEvt = EvtMenu;
      }
     if (!rvHndl)
        rvHndl = Parent->MouseLeftBtnUpWithShift(mx,my);
   }
  return rvHndl;
 }
bool Despatch:: MouseRightClickWithShift(int mx,int my)
 {
  bool rvHndl=false;
  if ((EventID&HandleMenu) && ActEvt == EvtMenu)
   {
     rvHndl = ActEvt->MouseRightClickWithShift(mx,my);
     if (!(ActEvt->EventID&EvtActive))
        ActEvt = Grp[GrpIdx].Evt;
   }
  else
   {
     for (int i=0;!rvHndl && i<GrpSize ;i++)
        if (Grp[i].Evt->EventID&Responds)
         {
	  if (Grp[i].Evt->EventID&HandleEvent)
            rvHndl = Grp[i].Evt->Hndl->MouseRightClickWithShift(mx,my);
          if (!rvHndl)
	    rvHndl = Grp[i].Evt->MouseRightClickWithShift(mx,my);
          if (rvHndl)
           {
            GrpIdx = i;
            ActEvt = Grp[GrpIdx].Evt;
           }
         }
     if (!rvHndl && EventID&HandleMenu)
      {
        rvHndl = EvtMenu->MouseRightClickWithShift(mx,my);
        if (EvtMenu->EventID&EvtActive)
          ActEvt = EvtMenu;
      }
     if (!rvHndl)
        rvHndl = Parent->MouseRightClickWithShift(mx,my);
   }
  return rvHndl;
 }
bool Despatch:: MouseRightBtnUpWithShift(int mx,int my)
 {
  bool rvHndl=false;
  if ((EventID&HandleMenu) && ActEvt == EvtMenu)
   {
     rvHndl = ActEvt->MouseRightBtnUpWithShift(mx,my);
     if (!(ActEvt->EventID&EvtActive))
        ActEvt = Grp[GrpIdx].Evt;
   }
  else
   {
     for (int i=0;!rvHndl && i<GrpSize ;i++)
        if (Grp[i].Evt->EventID&Responds)
         {
	  if (Grp[i].Evt->EventID&HandleEvent)
            rvHndl = Grp[i].Evt->Hndl->MouseRightBtnUpWithShift(mx,my);
          if (!rvHndl)
	    rvHndl = Grp[i].Evt->MouseRightBtnUpWithShift(mx,my);
          if (rvHndl)
           {
            GrpIdx = i;
            ActEvt = Grp[GrpIdx].Evt;
           }
         }
     if (!rvHndl && EventID&HandleMenu)
      {
        rvHndl = EvtMenu->MouseRightBtnUpWithShift(mx,my);
        if (EvtMenu->EventID&EvtActive)
          ActEvt = EvtMenu;
      }
     if (!rvHndl)
        rvHndl = Parent->MouseRightBtnUpWithShift(mx,my);
   }
  return rvHndl;
 }

// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>                    Ctrl Key & Mouse                    <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

bool Despatch:: MouseMoveWithCtrl(int mx,int my)
 {
  bool rvHndl=false;
  if ((EventID&HandleMenu) && ActEvt == EvtMenu)
   {
     rvHndl = ActEvt->MouseMoveWithCtrl(mx,my);
     if (!(ActEvt->EventID&EvtActive))
        ActEvt = Grp[GrpIdx].Evt;
   }
  else
   {
     for (int i=0;!rvHndl && i<GrpSize ;i++)
        if (Grp[i].Evt->EventID&Responds)
         {
	  if (Grp[i].Evt->EventID&HandleEvent)
            rvHndl = Grp[i].Evt->Hndl->MouseMoveWithCtrl(mx,my);
          if (!rvHndl)
	    rvHndl = Grp[i].Evt->MouseMoveWithCtrl(mx,my);
          if (rvHndl)
           {
            GrpIdx = i;
            ActEvt = Grp[GrpIdx].Evt;
           }
         }
     if (!rvHndl && EventID&HandleMenu)
      {
        rvHndl = EvtMenu->MouseMoveWithCtrl(mx,my);
        if (EvtMenu->EventID&EvtActive)
          ActEvt = EvtMenu;
      }
     if (!rvHndl)
        rvHndl = Parent->MouseMoveWithCtrl(mx,my);
   }
  return rvHndl;
 }
bool Despatch:: MouseLeftClickWithCtrl(int mx,int my)
 {
  bool rvHndl=false;
  if ((EventID&HandleMenu) && ActEvt == EvtMenu)
   {
     rvHndl = ActEvt->MouseLeftClickWithCtrl(mx,my);
     if (!(ActEvt->EventID&EvtActive))
        ActEvt = Grp[GrpIdx].Evt;
   }
  else
   {
     for (int i=0;!rvHndl && i<GrpSize ;i++)
        if (Grp[i].Evt->EventID&Responds)
         {
	  if (Grp[i].Evt->EventID&HandleEvent)
            rvHndl = Grp[i].Evt->Hndl->MouseLeftClickWithCtrl(mx,my);
          if (!rvHndl)
	    rvHndl = Grp[i].Evt->MouseLeftClickWithCtrl(mx,my);
          if (rvHndl)
           {
            GrpIdx = i;
            ActEvt = Grp[GrpIdx].Evt;
           }
         }
     if (!rvHndl && EventID&HandleMenu)
      {
        rvHndl = EvtMenu->MouseLeftClickWithCtrl(mx,my);
        if (EvtMenu->EventID&EvtActive)
          ActEvt = EvtMenu;
      }
     if (!rvHndl)
        rvHndl = Parent->MouseLeftClickWithCtrl(mx,my);
   }
  return rvHndl;
 }
bool Despatch:: MouseLeftBtnUpWithCtrl (int mx,int my)
 {
  bool rvHndl=false;
  if ((EventID&HandleMenu) && ActEvt == EvtMenu)
   {
     rvHndl = ActEvt->MouseLeftBtnUpWithCtrl(mx,my);
     if (!(ActEvt->EventID&EvtActive))
        ActEvt = Grp[GrpIdx].Evt;
   }
  else
   {
     for (int i=0;!rvHndl && i<GrpSize ;i++)
        if (Grp[i].Evt->EventID&Responds)
         {
	  if (Grp[i].Evt->EventID&HandleEvent)
            rvHndl = Grp[i].Evt->Hndl->MouseLeftBtnUpWithCtrl(mx,my);
          if (!rvHndl)
	    rvHndl = Grp[i].Evt->MouseLeftBtnUpWithCtrl(mx,my);
          if (rvHndl)
           {
            GrpIdx = i;
            ActEvt = Grp[GrpIdx].Evt;
           }
         }
     if (!rvHndl && EventID&HandleMenu)
      {
        rvHndl = EvtMenu->MouseLeftBtnUpWithCtrl(mx,my);
        if (EvtMenu->EventID&EvtActive)
          ActEvt = EvtMenu;
      }
     if (!rvHndl)
        rvHndl = Parent->MouseLeftBtnUpWithCtrl(mx,my);
   }
  return rvHndl;
 }
bool Despatch:: MouseRightClickWithCtrl(int mx,int my)
 {
  bool rvHndl=false;
  if ((EventID&HandleMenu) && ActEvt == EvtMenu)
   {
     rvHndl = ActEvt->MouseRightClickWithCtrl(mx,my);
     if (!(ActEvt->EventID&EvtActive))
        ActEvt = Grp[GrpIdx].Evt;
   }
  else
   {
     for (int i=0;!rvHndl && i<GrpSize ;i++)
        if (Grp[i].Evt->EventID&Responds)
         {
	  if (Grp[i].Evt->EventID&HandleEvent)
            rvHndl = Grp[i].Evt->Hndl->MouseRightClickWithCtrl(mx,my);
          if (!rvHndl)
	    rvHndl = Grp[i].Evt->MouseRightClickWithCtrl(mx,my);
          if (rvHndl)
           {
            GrpIdx = i;
            ActEvt = Grp[GrpIdx].Evt;
           }
         }
     if (!rvHndl && EventID&HandleMenu)
      {
        rvHndl = EvtMenu->MouseRightClickWithCtrl(mx,my);
        if (EvtMenu->EventID&EvtActive)
          ActEvt = EvtMenu;
      }
     if (!rvHndl)
        rvHndl = Parent->MouseRightClickWithCtrl(mx,my);
   }
  return rvHndl;
 }
bool Despatch:: MouseRightBtnUpWithCtrl(int mx,int my)
 {
  bool rvHndl=false;
  if ((EventID&HandleMenu) && ActEvt == EvtMenu)
   {
     rvHndl = ActEvt->MouseRightBtnUpWithCtrl(mx,my);
     if (!(ActEvt->EventID&EvtActive))
        ActEvt = Grp[GrpIdx].Evt;
   }
  else
   {
     for (int i=0;!rvHndl && i<GrpSize ;i++)
        if (Grp[i].Evt->EventID&Responds)
         {
	  if (Grp[i].Evt->EventID&HandleEvent)
            rvHndl = Grp[i].Evt->Hndl->MouseRightBtnUpWithCtrl(mx,my);
          if (!rvHndl)
	    rvHndl = Grp[i].Evt->MouseRightBtnUpWithCtrl(mx,my);
          if (rvHndl)
           {
            GrpIdx = i;
            ActEvt = Grp[GrpIdx].Evt;
           }
         }
     if (!rvHndl && EventID&HandleMenu)
      {
        rvHndl = EvtMenu->MouseRightBtnUpWithCtrl(mx,my);
        if (EvtMenu->EventID&EvtActive)
          ActEvt = EvtMenu;
      }
     if (!rvHndl)
        rvHndl = Parent->MouseRightBtnUpWithCtrl(mx,my);
   }
  return rvHndl;
 }

// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>                    Alt Key & Mouse                    <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

bool Despatch:: MouseMoveWithAlt(int mx,int my)
 {
  bool rvHndl=false;
  if ((EventID&HandleMenu) && ActEvt == EvtMenu)
   {
     rvHndl = ActEvt->MouseMoveWithAlt(mx,my);
     if (!(ActEvt->EventID&EvtActive))
        ActEvt = Grp[GrpIdx].Evt;
   }
  else
   {
     for (int i=0;!rvHndl && i<GrpSize ;i++)
        if (Grp[i].Evt->EventID&Responds)
         {
	  if (Grp[i].Evt->EventID&HandleEvent)
            rvHndl = Grp[i].Evt->Hndl->MouseMoveWithAlt(mx,my);
          if (!rvHndl)
	    rvHndl = Grp[i].Evt->MouseMoveWithAlt(mx,my);
          if (rvHndl)
           {
            GrpIdx = i;
            ActEvt = Grp[GrpIdx].Evt;
           }
         }
     if (!rvHndl && EventID&HandleMenu)
      {
        rvHndl = EvtMenu->MouseMoveWithAlt(mx,my);
        if (EvtMenu->EventID&EvtActive)
          ActEvt = EvtMenu;
      }
     if (!rvHndl)
        rvHndl = Parent->MouseMoveWithAlt(mx,my);
   }
  return rvHndl;
 }
bool Despatch:: MouseLeftClickWithAlt(int mx,int my)
 {
  bool rvHndl=false;
  if ((EventID&HandleMenu) && ActEvt == EvtMenu)
   {
     rvHndl = ActEvt->MouseLeftClickWithAlt(mx,my);
     if (!(ActEvt->EventID&EvtActive))
        ActEvt = Grp[GrpIdx].Evt;
   }
  else
   {
     for (int i=0;!rvHndl && i<GrpSize ;i++)
        if (Grp[i].Evt->EventID&Responds)
         {
	  if (Grp[i].Evt->EventID&HandleEvent)
            rvHndl = Grp[i].Evt->Hndl->MouseLeftClickWithAlt(mx,my);
          if (!rvHndl)
	    rvHndl = Grp[i].Evt->MouseLeftClickWithAlt(mx,my);
          if (rvHndl)
           {
            GrpIdx = i;
            ActEvt = Grp[GrpIdx].Evt;
           }
         }
     if (!rvHndl && EventID&HandleMenu)
      {
        rvHndl = EvtMenu->MouseLeftClickWithAlt(mx,my);
        if (EvtMenu->EventID&EvtActive)
          ActEvt = EvtMenu;
      }
     if (!rvHndl)
        rvHndl = Parent->MouseLeftClickWithAlt(mx,my);
   }
  return rvHndl;
 }
bool Despatch:: MouseLeftBtnUpWithAlt(int mx,int my)
 {
  bool rvHndl=false;
  if ((EventID&HandleMenu) && ActEvt == EvtMenu)
   {
     rvHndl = ActEvt->MouseLeftBtnUpWithAlt(mx,my);
     if (!(ActEvt->EventID&EvtActive))
        ActEvt = Grp[GrpIdx].Evt;
   }
  else
   {
     for (int i=0;!rvHndl && i<GrpSize ;i++)
        if (Grp[i].Evt->EventID&Responds)
         {
	  if (Grp[i].Evt->EventID&HandleEvent)
            rvHndl = Grp[i].Evt->Hndl->MouseLeftBtnUpWithAlt(mx,my);
          if (!rvHndl)
	    rvHndl = Grp[i].Evt->MouseLeftBtnUpWithAlt(mx,my);
          if (rvHndl)
           {
            GrpIdx = i;
            ActEvt = Grp[GrpIdx].Evt;
           }
         }
     if (!rvHndl && EventID&HandleMenu)
      {
        rvHndl = EvtMenu->MouseLeftBtnUpWithAlt(mx,my);
        if (EvtMenu->EventID&EvtActive)
          ActEvt = EvtMenu;
      }
     if (!rvHndl)
        rvHndl = Parent->MouseLeftBtnUpWithAlt(mx,my);
   }
  return rvHndl;
 }
bool Despatch:: MouseRightClickWithAlt(int mx,int my)
 {
  bool rvHndl=false;
  if ((EventID&HandleMenu) && ActEvt == EvtMenu)
   {
     rvHndl = ActEvt->MouseRightClickWithAlt(mx,my);
     if (!(ActEvt->EventID&EvtActive))
        ActEvt = Grp[GrpIdx].Evt;
   }
  else
   {
     for (int i=0;!rvHndl && i<GrpSize ;i++)
        if (Grp[i].Evt->EventID&Responds)
         {
	  if (Grp[i].Evt->EventID&HandleEvent)
            rvHndl = Grp[i].Evt->Hndl->MouseRightClickWithAlt(mx,my);
          if (!rvHndl)
	    rvHndl = Grp[i].Evt->MouseRightClickWithAlt(mx,my);
          if (rvHndl)
           {
            GrpIdx = i;
            ActEvt = Grp[GrpIdx].Evt;
           }
         }
     if (!rvHndl && EventID&HandleMenu)
      {
        rvHndl = EvtMenu->MouseRightClickWithAlt(mx,my);
        if (EvtMenu->EventID&EvtActive)
          ActEvt = EvtMenu;
      }
     if (!rvHndl)
        rvHndl = Parent->MouseRightClickWithAlt(mx,my);
   }
  return rvHndl;
 }
bool Despatch:: MouseRightBtnUpWithAlt(int mx,int my)
 {
  bool rvHndl=false;
  if ((EventID&HandleMenu) && ActEvt == EvtMenu)
   {
     rvHndl = ActEvt->MouseRightBtnUpWithAlt(mx,my);
     if (!(ActEvt->EventID&EvtActive))
        ActEvt = Grp[GrpIdx].Evt;
   }
  else
   {
     for (int i=0;!rvHndl && i<GrpSize;i++)
        if (Grp[i].Evt->EventID&Responds)
         {
	  if (Grp[i].Evt->EventID&HandleEvent)
            rvHndl = Grp[i].Evt->Hndl->MouseRightBtnUpWithAlt(mx,my);
          if (!rvHndl)
	    rvHndl = Grp[i].Evt->MouseRightBtnUpWithAlt(mx,my);
          if (rvHndl)
           {
            GrpIdx = i;
            ActEvt = Grp[GrpIdx].Evt;
           }
         }
     if (!rvHndl && EventID&HandleMenu)
      {
        rvHndl = EvtMenu->MouseRightBtnUpWithAlt(mx,my);
        if (EvtMenu->EventID&EvtActive)
          ActEvt = EvtMenu;
      }
     if (!rvHndl)
        rvHndl = Parent->MouseRightBtnUpWithAlt(mx,my);
   }
  return rvHndl;
 }

bool Despatch:: KeyPress(word Key) {return false;}
bool Despatch:: KeyUp   (word Key) {return false;}

// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>                Generic Event Despatchers                <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

bool Despatch::Show()
 {
  ViewPort SavVp=Vp;
//  Parent->ShowX();
  for (int i=0;i<GrpSize;i++)
   //if (!(Grp[i].Evt->EventID&HandleEvent))
      Grp[i].Evt->Show();
   //else
    //  Grp[i].Evt->Hndl->Show();
  Vp = SavVp;
  return true;
 }

bool Despatch::ShowX()
 {
  //Parent->Show();
  //for (int i=0;i<GrpSize;i++)
  //     Grp[i].Evt->Show();
//  ShowX();
  return true;
 }
bool Despatch::Refresh()
 {
  /*Parent->Refresh();
  for (int i=0;i<GrpSize;i++)
   if (!(Grp[i].Evt->EventID&HandleEvent))
      Grp[i].Evt->Refresh();
   else
      Grp[i].Evt->Hndl->Refresh();
  */
  ShowX();
  return true;
 }
bool Despatch:: SetFocus(Event *Evt)
 {
  bool rvHndl = false;
  for (int i=0;i<GrpSize && !rvHndl;i++)
    if (Grp[i].Evt == Evt && GrpIdx != i)
     {
       if (ActEvt==Grp[GrpIdx].Evt)
        {
         GrpIdx = i;
         ActEvt = Grp[GrpIdx].Evt;
         ActEvt->GotFocus();
         rvHndl = true;
        }
     }
    else if (Grp[i].Evt->EventID&HandleEvent)
        rvHndl = Grp[i].Evt->Hndl->SetFocus(Evt);
  return true;
 }
bool Despatch:: SetFocus() {return false;};
bool Despatch:: LostFocus(){return false;}
bool Despatch:: GotFocus() {return false;};
bool Despatch:: Change()   {return false;}
bool Despatch:: Close()    {return false;}

#pragma warn +par


// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>                      IVT Modules                        <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

IVT::IVT()
 {
   OldKbVec = getvect(0x9);

   SwapEventHandler(cwAllUserMouseEvents,AllMouseEvents,&MouseEvt[0]);

   GetAlternateMouseHandler(cwAllMouseEventsWithShift  ,&MouseEvt[1]);
   GetAlternateMouseHandler(cwAllMouseEventsWithCtrl   ,&MouseEvt[2]);
   GetAlternateMouseHandler(cwAllMouseEventsWithAlt    ,&MouseEvt[3]);

   setvect(0x9,KeyDown);
   SetAlternateMouseHandler(cwAllMouseEventsWithShift,EvtMouseWithShift);
   SetAlternateMouseHandler(cwAllMouseEventsWithCtrl ,EvtMouseWithCtrl);
   SetAlternateMouseHandler(cwAllMouseEventsWithAlt  ,EvtMouseWithAlt);
 }

IVT::~IVT()
 {
   setvect(0x9,OldKbVec);
   SetUserMouseEventHandler(MouseEvt[0].EvtMask,MouseEvt[0].EvtHndl);
   SetAlternateMouseHandler(MouseEvt[1].EvtMask,MouseEvt[1].EvtHndl);
   SetAlternateMouseHandler(MouseEvt[2].EvtMask,MouseEvt[2].EvtHndl);
   SetAlternateMouseHandler(MouseEvt[3].EvtMask,MouseEvt[3].EvtHndl);
   MouseEvt[0].EvtHndl = (isr)NULL;
   MouseEvt[1].EvtHndl = (isr)NULL;
   MouseEvt[2].EvtHndl = (isr)NULL;
   MouseEvt[3].EvtHndl = (isr)NULL;
   OldKbVec = (isr)NULL;
 }


// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>
// <<>>                                                         <<>>
// <<>>                        ISR Code                         <<>>
// <<>>                                                         <<>>
// <<>>  <<>>  <<>>  <<>>  <<>>  <<*>>  <<>>  <<>>  <<>>  <<>>  <<>>

void interrupt far KeyPress(...)
  {
    EvtMain->KeyPress(_AX);
  }
void interrupt far KeyUp   (...)
  {
    EvtMain->KeyUp(_AX);
  }
void interrupt far KeyDown (...)
  {
    Word Key;
    BiosKbd(...);
    Key=KeyHit();
    if (Key!=0)
      Key=GetKey();
    if (EvtMain != (Event*)NULL && EvtMain->Hndl != (Despatch*)NULL)
	  EvtMain->Hndl->KeyDown(Key);
  }
void interrupt far AllMouseEvents(...)
 {
   Ms.SetMouse(_CX,_DX,_BX,_AX);
   if (EvtMain != (Event*)NULL && EvtMain->Hndl != (Despatch*)NULL)
    {
     if (Ms.EvtFlags&cwMouseMove)
        EvtMain->Hndl->MouseMove(Ms.x,Ms.y);
     if (Ms.EvtFlags&cwMouseLeftClick)
        EvtMain->Hndl->MouseLeftClick(Ms.x,Ms.y);
     if (Ms.EvtFlags&cwMouseLeftBtnUp)
        EvtMain->Hndl->MouseLeftBtnUp(Ms.x,Ms.y);
     if (Ms.EvtFlags&cwMouseRightClick)
        EvtMain->Hndl->MouseRightClick(Ms.x,Ms.y);
     if (Ms.EvtFlags&cwMouseRightBtnUp)
        EvtMain->Hndl->MouseRightBtnUp(Ms.x,Ms.y);
     if (Ms.EvtFlags&cwMouseMiddleClick)
        EvtMain->Hndl->MouseMiddleClick(Ms.x,Ms.y);
     if (Ms.EvtFlags&cwMouseMiddleBtnUp)
        EvtMain->Hndl->MouseMiddleBtnUp(Ms.x,Ms.y);
    }
 }
void interrupt far EvtMouseWithShift(...)
 {
   Ms.SetMouse(_CX,_DX,_BX,_AX);
   if (EvtMain != (Event*)NULL && EvtMain->Hndl != (Despatch*)NULL)
    {
     if (Ms.EvtFlags&cwMouseMoveWithShift)
        EvtMain->Hndl->MouseMoveWithShift(Ms.x,Ms.y);
     if (Ms.EvtFlags&cwMouseLeftClickWithShift)
        EvtMain->Hndl->MouseLeftClickWithShift(Ms.x,Ms.y);
     if (Ms.EvtFlags&cwMouseLeftBtnUpWithShift)
        EvtMain->Hndl->MouseLeftBtnUpWithShift(Ms.x,Ms.y);
     if (Ms.EvtFlags&cwMouseRightClickWithShift)
        EvtMain->Hndl->MouseRightClickWithShift(Ms.x,Ms.y);
     if (Ms.EvtFlags&cwMouseRightBtnUpWithShift)
        EvtMain->Hndl->MouseRightBtnUpWithShift(Ms.x,Ms.y);
    }
 }

void interrupt far EvtMouseWithCtrl(...)
 {
   Ms.SetMouse(_CX,_DX,_BX,_AX);
   if (EvtMain != (Event*)NULL && EvtMain->Hndl != (Despatch*)NULL)
    {
     if (Ms.EvtFlags&cwMouseMoveWithCtrl)
        EvtMain->Hndl->MouseMoveWithCtrl(Ms.x,Ms.y);
     if (Ms.EvtFlags&cwMouseLeftClickWithCtrl)
        EvtMain->Hndl->MouseLeftClickWithCtrl(Ms.x,Ms.y);
     if (Ms.EvtFlags&cwMouseLeftBtnUpWithCtrl)
        EvtMain->Hndl->MouseLeftBtnUpWithCtrl(Ms.x,Ms.y);
     if (Ms.EvtFlags&cwMouseRightClickWithCtrl)
        EvtMain->Hndl->MouseRightClickWithCtrl(Ms.x,Ms.y);
     if (Ms.EvtFlags&cwMouseRightBtnUpWithCtrl)
        EvtMain->Hndl->MouseRightBtnUpWithCtrl(Ms.x,Ms.y);
    }
 }

void interrupt far EvtMouseWithAlt(...)
 {
   Ms.SetMouse(_CX,_DX,_BX,_AX);
   if (EvtMain != (Event*)NULL && EvtMain->Hndl != (Despatch*)NULL)
    {
     if (Ms.EvtFlags&cwMouseMoveWithAlt)
        EvtMain->Hndl->MouseMoveWithAlt(Ms.x,Ms.y);
     if (Ms.EvtFlags&cwMouseLeftClickWithAlt)
        EvtMain->Hndl->MouseLeftClickWithAlt(Ms.x,Ms.y);
     if (Ms.EvtFlags&cwMouseLeftBtnUpWithAlt)
        EvtMain->Hndl->MouseLeftBtnUpWithAlt(Ms.x,Ms.y);
     if (Ms.EvtFlags&cwMouseRightClickWithAlt)
        EvtMain->Hndl->MouseRightClickWithAlt(Ms.x,Ms.y);
     if (Ms.EvtFlags&cwMouseRightBtnUpWithAlt)
        EvtMain->Hndl->MouseRightBtnUpWithAlt(Ms.x,Ms.y);
    }
 }
/*void interrupt far MouseMove(...)
  {
    Ms.SetMouse(_CX,_DX,_BX,_AX);
    EvtMain->MouseMove(Ms.x,Ms.y);
  }
void interrupt far MouseLeftClick(...)
  {
    Ms.SetMouse(_CX,_DX,_BX,_AX);
    EvtMain->MouseLeftClick(Ms.x,Ms.y);
  }
void interrupt far MouseLeftBtnUp(...)
  {
    Ms.SetMouse(_CX,_DX,_BX,_AX);
    EvtMain->MouseLeftBtnUp(Ms.x,Ms.y);
  }
void interrupt far MouseRightClick(...)
  {
    Ms.SetMouse(_CX,_DX,_BX,_AX);
    EvtMain->MouseRightClick(Ms.x,Ms.y);
  }
void interrupt far MouseRightBtnUp(...)
  { 
    Ms.SetMouse(_CX,_DX,_BX,_AX);
    EvtMain->MouseRightBtnUp(Ms.x,Ms.y);
  }
void interrupt far MouseMiddleClick(...)
  {
    Ms.SetMouse(_CX,_DX,_BX,_AX);
    EvtMain->MouseMiddleClick(Ms.x,Ms.y);
  }
void interrupt far MouseMiddleBtnUp(...)
  { 
    Ms.SetMouse(_CX,_DX,_BX,_AX);
    EvtMain->MouseMiddleBtnUp(Ms.x,Ms.y);
  }

void interrupt far MouseMoveWithShift(...)
  { 
    Ms.SetMouse(_CX,_DX,_BX,_AX);
    EvtMain->MouseMoveWithShift(Ms.x,Ms.y);
  }
void interrupt far MouseLeftClickWithShift(...)
  { 
    Ms.SetMouse(_CX,_DX,_BX,_AX);
    EvtMain->MouseLeftClickWithShift(Ms.x,Ms.y);
  }
void interrupt far MouseLeftBtnUpWithShift(...)
  { 
    Ms.SetMouse(_CX,_DX,_BX,_AX);
    EvtMain->MouseLeftBtnUpWithShift(Ms.x,Ms.y);
  }
void interrupt far MouseRightClickWithShift(...)
  {
    Ms.SetMouse(_CX,_DX,_BX,_AX);
    EvtMain->MouseRightClickWithShift(Ms.x,Ms.y);
  }
void interrupt far MouseRightBtnUpWithShift(...)
  { 
    Ms.SetMouse(_CX,_DX,_BX,_AX);
    EvtMain->MouseRightBtnUpWithShift(Ms.x,Ms.y);
  }

void interrupt far MouseMoveWithCtrl(...)
  { 
    Ms.SetMouse(_CX,_DX,_BX,_AX);
    EvtMain->MouseMoveWithCtrl(Ms.x,Ms.y);
  }
void interrupt far MouseLeftClickWithCtrl(...)
  {
    Ms.SetMouse(_CX,_DX,_BX,_AX);
    EvtMain->MouseLeftClickWithCtrl(Ms.x,Ms.y);
  }
void interrupt far MouseLeftBtnUpWithCtrl(...)
  { 
    Ms.SetMouse(_CX,_DX,_BX,_AX);
    EvtMain->MouseLeftBtnUpWithCtrl(Ms.x,Ms.y);
  }
void interrupt far MouseRightClickWithCtrl(...)
  {
    Ms.SetMouse(_CX,_DX,_BX,_AX);
    EvtMain->MouseRightClickWithCtrl(Ms.x,Ms.y);
  }
void interrupt far MouseRightBtnUpWithCtrl(...)
  { 
    Ms.SetMouse(_CX,_DX,_BX,_AX);
    EvtMain->MouseRightBtnUpWithCtrl(Ms.x,Ms.y);
  }

void interrupt far MouseMoveWithAlt(...)
  {
    Ms.SetMouse(_CX,_DX,_BX,_AX);
    EvtMain->MouseMoveWithAlt(Ms.x,Ms.y);
  }
void interrupt far MouseLeftClickWithAlt(...)
  {
    Ms.SetMouse(_CX,_DX,_BX,_AX);
    EvtMain->MouseLeftClickWithAlt(Ms.x,Ms.y);
  }
void interrupt far MouseLeftBtnUpWithAlt(...)
  {
    Ms.SetMouse(_CX,_DX,_BX,_AX);
    EvtMain->MouseLeftBtnUpWithAlt(Ms.x,Ms.y);
  }
void interrupt far MouseRightClickWithAlt(...)
  {
    Ms.SetMouse(_CX,_DX,_BX,_AX);
    EvtMain->MouseRightClickWithAlt(Ms.x,Ms.y);
  }
void interrupt far MouseRightBtnUpWithAlt(...)
  { 
    Ms.SetMouse(_CX,_DX,_BX,_AX);
    EvtMain->MouseRightBtnUpWithAlt(Ms.x,Ms.y);
  }*/





