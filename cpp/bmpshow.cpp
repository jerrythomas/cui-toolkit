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

Bmp::Bmp()
 {
  bf.Type[0]   = 'B';
  bf.Type[1]   = 'M';
  bf.Size      = 56;
  bf.Reserved1 = 0;
  bf.Reserved2 = 0;
  bf.OffBits   = 56;

  swImage = 0;
  bi.Size      = 40;
  BmpFile = (char*)NULL;
  xScl =yScl = 1;
 }
Bmp::Bmp(char *FileName)
 {
   FILE *f;
   swImage = 0x00;
   xScl = yScl = 1;
   f = fopen(FileName,"r");
   if (f != (FILE*)NULL)
    {
     fread((char*)&bf,sizeof(bf),1,f);
     if (bf.Type[0] == 'B' && bf.Type[1] == 'M')
      {
	fread((char*)&bi,sizeof(bi),1,f);
	BmpFile = new char[strlen(FileName)+1];
	strcpy(BmpFile,FileName);
	swImage = 0x10;
	BitMask = 0;
	for(TotPix=0;TotPix<bi.BitCount;TotPix++)
	   BitMask |= (1<<TotPix);
	TotPix  = 8/bi.BitCount;
        Width   = bi.Width;
	Width  +=  (bi.BitCount==1) ? (32-bi.Width%32)%32:(8-bi.Width%8)%8;
        ColMapSize=(bf.OffBits-54)/4;
        co = new ColorMap[ColMapSize];
        fread((char*)co,sizeof(ColorMap),ColMapSize,f);
      }
    }
   fclose(f);
 }
Bmp::~Bmp()
 {
   if (BmpFile != (char*)NULL)
      delete BmpFile;
   if (co != (ColorMap*)NULL)
      delete co;
 }


void Bmp::Show16()
 {
  int   x,y,Pix;
  char  dummy;
  FILE *f=fopen(BmpFile,"rb");
  for (x=0;x<bf.OffBits;x++)
    fread(&dummy,sizeof(char),1,f);
  x=y=0;
  byte scl=1;
  if (bi.BitCount==1)
   {
     scl=15; //loadcolormap
   }
  if (swImage==0x10)
  do
   {
     fread(&dummy,sizeof(char),1,f);
     for (int k=0;k<TotPix;k++)
      {
       Pix = scl*((dummy>>((TotPix-1-k)*bi.BitCount))&BitMask);
       if (x<bi.Width)
	for(int i=0;i<xScl;i++)
	 for (int j=0;j<yScl;j++)
	  SetPixel(X+x*xScl+i,Y+(bi.Height-y)*yScl+j,Pix);
       x++;
       if (x==Width)
	{ x=0;y++;}
      }
   }
  while((y<bi.Height) && !feof(f));
  fclose(f);
 }

void Bmp::Show(int x,int y)
 {
   X = x;
   Y = y;
   for (int i=0 ; i< ColMapSize;i++)
    {
      RGBHue[i].red = co[i].red>>2;
      RGBHue[i].blu = co[i].blu>>2;
      RGBHue[i].grn = co[i].grn>>2;
    }
   SetPalette(RGBHue);

   Show16();
 }
void Bmp::Capture(int x,int y,int w,int h)
 {
  bf.Type[0]   = 'B';
  bf.Type[1]   = 'M';
  bf.Size      = 56;
  bf.Reserved1 = 0;
  bf.Reserved2 = 0;
  bf.OffBits   = 56;

  swImage = 0;
  bi.Size = 40;
  bi.Width  = w;
  bi.Height = h;
  bi.BitCount = 8;
  bi.Planes = 1;
  bi.Compression = 0;
  bi.SizeImage = w*h;
  ColMapSize = 256;
  if (co) delete co;
  co = new ColorMap[256];
  for (int i=0 ; i< ColMapSize;i++)
    {
      co[i].red = RGBHue[i].red<<2;
      co[i].blu = RGBHue[i].blu<<2;
      co[i].grn = RGBHue[i].grn<<2;
    }
  xScl =yScl = 1;
  X = x;
  Y = y;
 }
void Bmp::SaveAs(char *F)
 {
  byte Pix;
  int x,y;
  char  dummy;

  if (BmpFile != (char*)NULL)
     delete BmpFile;
  BmpFile = new char [strlen(F)+1];
  strcpy(BmpFile,F);

  FILE *f=fopen(BmpFile,"wb");

  fwrite(&bf,sizeof(bf),1,f);
  fwrite((char*)&bi,sizeof(bi),1,f);
  fwrite((char*)co,sizeof(ColorMap),ColMapSize,f);


  BitMask = 0;
  for(TotPix=0;TotPix<bi.BitCount;TotPix++)
      BitMask |= (1<<TotPix);
  TotPix  = 8/bi.BitCount;
  Width   = bi.Width;
  Width  +=  (bi.BitCount==1) ? (32-bi.Width%32)%32:(8-bi.Width%8)%8;
  y=0;
  byte buffer[1024];
  do
   {
     for (x=0;x<bi.Width;x++)
        buffer[x] = GetPixel(X+x,Y+bi.Height-y);
     fwrite(buffer,sizeof(char),bi.Width,f);
     y++;
   }
  while(y<bi.Height);
  fclose(f);
 }
void Bmp::Scale(byte x,byte y)
 {
   xScl = (x>0) ? x:1;
   yScl = (y>0) ? y:1;
 }
void Bmp::Spec()
 {
  gPrintf(600,510,"\n File Name    %s",BmpFile);
  gPrintf(600,520,"\nbfType          %c%c ",bf.Type[0],bf.Type[1]);
  gPrintf(600,530,"\nbfSize          %u ",bf.Size);
  gPrintf(600,540,"\nbfReserved1     %d ",bf.Reserved1);
  gPrintf(600,550,"\nbfReserved2     %d ",bf.Reserved2);
  gPrintf(600,560,"\nbfOffBits       %u ",bf.OffBits);
  gPrintf(600,570,"\n head Size       %u %u %u",sizeof(bf),sizeof(bi),sizeof(BmpHeader));
  gPrintf(600,580,"\nColMapSize      %d ",ColMapSize);
  gPrintf(600,590,"\n\nBMP InfoStructure\n");
  gPrintf(600,600,"\nbiSize          %u",bi.Size);
  gPrintf(600,610,"\nbiWidth         %u",bi.Width);
  gPrintf(600,620,"\nbiHeight        %u",bi.Height);
  gPrintf(600,630,"\nbiPlanes        %u",bi.Planes);
  gPrintf(600,640,"\nbiBitCount      %u",bi.BitCount);
  gPrintf(600,650,"\nbiCompression   %u",bi.Compression);
  gPrintf(600,660,"\nbiSizeImage     %u",bi.SizeImage);
  gPrintf(600,670,"\nbiXPelsPerMeter %u",bi.XPelsPerMeter);
  gPrintf(600,680,"\nbiYPelsPerMeter %u",bi.YPelsPerMeter);
  gPrintf(600,690,"\nbiClrUsed       %u",bi.ClrUsed);
  gPrintf(600,700,"\nbiClrImportant  %u\n",bi.ClrImportant);
 }
/*main()//int argc,char **argv)
 {
   Bmp A("C:\\windows\\setup.bmp");
   Bmp B;

   ModeSearch(VgaCo1024x768x256);

   A.Spec();
   A.Show(10,10);
   GetKey();

   CloseGraph();
   return 0;
 }*/
