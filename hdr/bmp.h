#ifndef __BMP_H
#define __BMP_H

#include <string.h>
#include <stdio.h>
#include <pixel.h>
#include <kbd.h>

struct ColorMap
 {
   byte blu;
   byte grn;
   byte red;
   byte gry;
 };
struct BmpHeader
 {
   char  Type[2];     //type of file ; must be ascii "BM"
   dword Size;        // Size of file
   word  Reserved1;   //reserved fiels must be 0
   word  Reserved2;   // ----------do------------
   dword OffBits;    //specifies offset in bytes fo start of bitmap data
 };
struct BmpInfo
 {
   dword  Size;           //Size of bitmapinfostructure 40 bytes
   dword  Width;          //Width of bitmap in pixels
   dword  Height;         //Height of Bitmap in pixels
   word   Planes;         //image planes( 1)
   word   BitCount;       //BitsPerPixel (1,4,8 or 24)
   dword  Compression;    //Compression used
   dword  SizeImage;      // Size of image in bytes
   dword  XPelsPerMeter;  // Horizontal resolution in pixels per meter
   dword  YPelsPerMeter;  // Vertical resolution in pixels per meter
   dword  ClrUsed;        // Number of color indexes in the color table
   dword  ClrImportant;   // Number of color indexes considered important for displaying bitmap
 };

class Bmp
 {
   private :
     BmpHeader   bf;
     BmpInfo     bi;
     ColorMap   *co;
     char       *BmpFile;
     word       swImage;

     int        ColMapSize;
     byte       xScl,yScl;
     word       X,Y;
     dword      Width,Height;
     byte       TotPix;
     byte       BitMask;

   public :
     Bmp(char *FileName);
     Bmp();
     ~Bmp();
   private :
     void ShowBW();
     void Show16();
     void Show256();

   public :
     void Capture(int x,int y,int w,int h);
     void SaveAs(char *F);
     void Show(int x,int y);
     void Scale(byte x,byte y);
     void Spec();
 };
#endif