#define Xms 0x67
#include <stdio.h>
#include <dos.h>
#include <conio.h>

typedef unsigned char byte;
typedef unsigned int  word;
typedef unsigned long dword;

union REGS reg;

class Ems
 {
   public :
     static byte Error;
     static word EmsFree;
     static word EmsTotal;

   public :
     static byte Status();
     static byte Version();
     static word PageFrameAddress();
     static void TotalPages();
     static word AllocHandleAndPages(word ReqPg);
     static void MapPage(word Xms_Handle,word LogicPg,byte PhysPg);
     static void ReleaseHandleAndPage(word Xms_Handle);
     static void SavePageMap(word XmsHandle);
     static void RestorePageMap(word XmsHandle);
     static word HandleCount();
     static word HandlePages(word XmsHandle);
     static word PagesForAllHandles(dword *XmsHandleBuf);
     static void SavePageMapState(dword *XmsPageMapBuf);
     static void RestorePageMapState(dword *XmsPageMapBuf);
     static void SaveAndRestorePageMapState(dword *XmsPageMapBuf,dword *XmsPageMapInf);
     static byte PageMapInfSize();
     static void SavePartialPageMap(dword *XmsPageMapLstBuf,dword *XmsPageMapInf);
     static void RestorePartialPageMap(dword *XmsPageMapBuf);
     static byte PartialPageMapInfSize(word Pages);
     static void MapPagesByNumber(word Pages,word Handle,dword *Buffer);
     static void MapPagesByAddress(word Pages,word Handle,dword *Buffer);
     static byte ReallocPages(word NewPages,word Handle);
     static byte GetHandleAttribute(word Handle);
     static void SetHandleAttribute(word Handle,byte Attribute);
 };

byte Ems::Error=0x01;
word Ems::EmsFree=0x00;
word Ems::EmsTotal=0x00;
byte Ems::Status()
 {
   reg.h.ah = 0x40;
   int86(Xms,&reg,&reg);
   Error = reg.h.ah;
   return Error;
 }
byte Ems::Version()
 {
   reg.h.ah = 0x46;
   int86(Xms,&reg,&reg);
   Error = reg.h.ah;
   return  reg.h.al;
 }
word Ems::PageFrameAddress()
 {
   reg.h.ah=0x41;
   int86(Xms,&reg,&reg);
   Error   = reg.h.ah;
   return (Error) ? 0:reg.x.bx;
 }
void Ems::TotalPages()
 {
   reg.h.ah=0x42;
   int86(Xms,&reg,&reg);
   Error = reg.h.ah;
   if (!Error)
    {
      EmsFree  = reg.x.bx;
      EmsTotal = reg.x.dx;
    }
 }
word Ems::AllocHandleAndPages(word ReqPg)
 {
   reg.h.ah = 0x43;
   reg.x.bx = ReqPg;
   int86(Xms,&reg,&reg);
   Error = reg.h.ah;
   return (Error) ? 0:reg.x.dx;
 }
void Ems::MapPage(word Xms_Handle,word LogicPg,byte PhysPg)
 {
   reg.h.ah=0x44;
   reg.h.al=PhysPg;
   reg.x.dx=Xms_Handle;
   reg.x.bx=LogicPg;
   int86(Xms,&reg,&reg);
   Error = reg.h.ah;
 }
void Ems::ReleaseHandleAndPage(word Xms_Handle)
 {
   reg.h.ah=0x45;
   reg.x.dx=Xms_Handle;
   int86(Xms,&reg,&reg);
   Error = reg.h.ah;
 }
void Ems::SavePageMap(word XmsHandle)
 {
   reg.h.ah=0x47;
   reg.x.dx=XmsHandle;
   int86(Xms,&reg,&reg);
   Error = reg.h.ah;
 }
void Ems::RestorePageMap(word XmsHandle)
 {
   reg.h.ah = 0x48;
   reg.x.dx = XmsHandle;
   int86(Xms,&reg,&reg);
   Error = reg.h.ah;
 }
word Ems::HandleCount()
 {
   reg.h.ah = 0x4B;
   int86(Xms,&reg,&reg);
   Error = reg.h.ah;
   return (Error) ? 0:reg.x.bx;
 }

word Ems::HandlePages(word XmsHandle)
 {
   reg.h.ah=0x4C;
   reg.x.dx=XmsHandle;
   int86(Xms,&reg,&reg);
   Error = reg.h.ah;
   return (Error) ? 0 : reg.x.bx;
 }

word Ems::PagesForAllHandles(dword *XmsHandleBuf)
 {
   REGPACK reg;
   reg.r_ax = 0x4D00;
   reg.r_di = FP_OFF(XmsHandleBuf);
   reg.r_es = FP_SEG(XmsHandleBuf);
   intr(Xms,&reg);
   Error = reg.r_ax >> 8;
   return (Error) ? 0:reg.r_bx;
 }
void Ems::SavePageMapState(dword *XmsPageMapBuf)
 {
   REGPACK reg;
   reg.r_ax = 0x4E00;
   reg.r_di = FP_OFF(XmsPageMapBuf);
   reg.r_es = FP_SEG(XmsPageMapBuf);
   intr(Xms,&reg);
   Error = reg.r_ax >> 8;
 }
void Ems::RestorePageMapState(dword *XmsPageMapBuf)
 {
   REGPACK reg;
   reg.r_ax = 0x4E01;
   reg.r_di = FP_OFF(XmsPageMapBuf);
   reg.r_es = FP_SEG(XmsPageMapBuf);
   intr(Xms,&reg);
   Error = reg.r_ax >> 8;
 }
void Ems::SaveAndRestorePageMapState(dword *XmsPageMapBuf,dword *XmsPageMapInf)
 {
   REGPACK reg;
   reg.r_ax = 0x4E02;
   reg.r_di = FP_OFF(XmsPageMapBuf);
   reg.r_es = FP_SEG(XmsPageMapBuf);
   reg.r_si = FP_OFF(XmsPageMapInf);
   reg.r_ds = FP_SEG(XmsPageMapInf);
   intr(Xms,&reg);
   Error = reg.r_ax>>8;
 }
byte Ems::PageMapInfSize()
 {
   reg.x.ax = 0x4E03;
   int86(Xms,&reg,&reg);
   Error        = reg.h.ah;
   return (Error) ? 0:reg.h.al;
 }
void Ems::SavePartialPageMap(dword *XmsPageMapLstBuf,dword *XmsPageMapInf)
 {
   REGPACK reg;
   reg.r_ax = 0x4F00;
   reg.r_si = FP_OFF(XmsPageMapLstBuf);
   reg.r_ds = FP_SEG(XmsPageMapLstBuf);
   reg.r_di = FP_OFF(XmsPageMapInf);
   reg.r_es = FP_SEG(XmsPageMapInf);
   intr(Xms,&reg);
   Error = reg.r_ax >> 8;
 }
void Ems::RestorePartialPageMap(dword *XmsPageMapBuf)
 {
   REGPACK reg;
   reg.r_ax = 0x4F01;
   reg.r_si = FP_OFF(XmsPageMapBuf);
   reg.r_ds = FP_SEG(XmsPageMapBuf);
   intr(Xms,&reg);
   Error = reg.r_ax >> 8;
 }
byte Ems::PartialPageMapInfSize(word Pages)
 {
   reg.x.ax = 0x4F02;
   reg.x.bx = Pages;
   int86(Xms,&reg,&reg);
   Error = reg.h.ah;
   return (Error) ? 0:reg.h.al;
 }
void Ems::MapPagesByNumber(word Pages,word Handle,dword *Buffer)
 {
   REGPACK reg;
   reg.r_ax = 0x5000;
   reg.r_si = FP_OFF(Buffer);
   reg.r_ds = FP_SEG(Buffer);
   reg.r_cx = Pages;
   reg.r_dx = Handle;
   intr(Xms,&reg);
   Error = reg.r_ax >> 8;
 }
void Ems::MapPagesByAddress(word Pages,word Handle,dword *Buffer)
 {
   REGPACK reg;
   reg.r_ax = 0x5001;
   reg.r_si = FP_OFF(Buffer);
   reg.r_ds = FP_SEG(Buffer);
   reg.r_cx = Pages;
   reg.r_dx = Handle;
   intr(Xms,&reg);
   Error = reg.r_ax >> 8;
 }
byte Ems::ReallocPages(word NewPages,word Handle)
 {
   reg.h.ah = 0x51;
   reg.x.bx = NewPages;
   reg.x.dx = Handle;
   int86(Xms,&reg,&reg);
   Error = reg.h.ah;
   return (Error) ? 0:reg.x.bx;
 }
#define Volatile 0
#define NonVolatile 1

byte Ems::GetHandleAttribute(word Handle)
 {
   reg.x.ax = 0x5200;
   reg.x.dx = Handle;
   int86(Xms,&reg,&reg);
   Error = reg.h.ah;
   return (Error) ? 0:reg.h.al;
 }
void Ems::SetHandleAttribute(word Handle,byte Attribute)
 {
   reg.x.ax = 0x5201;
   reg.x.dx = Handle;
   reg.h.bl = Attribute;
   int86(Xms,&reg,&reg);
   Error = reg.h.ah;
 }

main()
 {
   clrscr();
   printf ("\nEmm Status %X",Ems::Status());
   if (!Ems::Status())
    {
     printf ("\nError  %x ",Ems::Error);
   printf ("\nEmm Version %d",Ems::Version());
   printf ("\nError  %x ",Ems::Error);
   printf ("\nPFA %X",Ems::PageFrameAddress());
   printf ("\nError  %x ",Ems::Error);
   Ems::TotalPages();
   printf ("\nFree Pages %d \nTotal Pages %d",Ems::EmsFree,Ems::EmsTotal);
   printf ("\nError  %x ",Ems::Error);
   printf ("\n Handle Count %d ",Ems::HandleCount());
   printf ("\nError  %x ",Ems::Error);
   printf ("\n PageMapInf size  %d ",Ems::PageMapInfSize());
   printf ("\nError  %x ",Ems::Error);
   }
   return 0;
 }
