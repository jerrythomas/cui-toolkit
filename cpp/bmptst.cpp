#include <graphics.h>
#include <stdio.h>


typedef unsigned int     word;
typedef unsigned char    byte;
typedef unsigned long    dword;


/*BMP BitMapHeader structure
file contains
  file header ,
  bmp header ,
  bitmap data ,
  and color map unless image uses 24 bit color

File Header
bfType //type of file ; must be ascii "BM" ?? 2B
bfSize  // Size of file                    ?? 2B
bfReserved1  //reserved fiels must be 0    ?? 1B
bfReserved2 // ----------do------------    ?? 1B
bf OffBits  //specifies offset in bytes fo start of bitmap data ?? 1B

BMP bitmap infostructure
biSize           //Size of bitmapinfostructure 40 bytes
biWidth          //Width of bitmap in pixels   ? 2 bytes ?
biHeight         //Height of Bitmap in pixels  ? 2 bytes ?
biPlanes         //image planes( 1)            ?  1 b ?
biBitCount       //BitsPerPixel (1,4,8 or 24)  ? 1 b ?
biCompression    //Compressionused             ?     ?
biSizeImage      // Size of image in bytes     ? 4 bytes ?
biXPelsPerMeter  // Horizontal resolution in pixels per meter   ? 1b?
biYPelsPerMeter  // Vertical resolution in pixels per meter     ? 1 b?
biClrUsed        // Number of color inedxes in the color table  ? 2 b?
biClrImportant   // Number of color indexes considered important for displaying bitmap  ? 2 b?


biCompression specifies type of compression
 BI_RGB   => no compression
 BI_RLE4  => RLE 4 bit color
 BI_RLE8 => RLE 8  bit color
 if biClrUsed is 0
    the bmp uses 24 bit color
 else
    the value is the actual number of colors bmp uses
 if biClrImportant = 0
    all colors are important
 Color data entries in Color map occupy 4 bytes
   1 byte each for blue green & red values 1byte left as 0
*/
//File Header
struct bmpHeader
 {
   char  bfType[2];     //type of file ; must be ascii "BM" ?? 2B
   dword bfSize;        // Size of file                    ?? 2B
   word  bfReserved1;   //reserved fiels must be 0    ?? 1B
   word  bfReserved2;   // ----------do------------    ?? 1B
   dword bfOffBits;    //specifies offset in bytes fo start of bitmap data ?? 1B
 };
struct bmpInfo
 {
   dword  biSize;           //Size of bitmapinfostructure 40 bytes
   dword  biWidth;          //Width of bitmap in pixels
   dword  biHeight;         //Height of Bitmap in pixels
   word   biPlanes;         //image planes( 1)
   word   biBitCount;       //BitsPerPixel (1,4,8 or 24)
   word   biCompression;    //Compression used             ?     ?
   dword   biSizeImage;      // Size of image in bytes     ? 4 bytes ?
   dword  biXPelsPerMeter;  // Horizontal resolution in pixels per meter   ? 1b?
   dword  biYPelsPerMeter;  // Vertical resolution in pixels per meter     ? 1 b?
   dword  biClrUsed;        // Number of color inedxes in the color table  ? 2 b?
   dword  biClrImportant;   // Number of color indexes considered important for displaying bitmap  ? 2 b?
 };
char *FileName = "C:\\Work\\Tom\\max2icon.bmp";
main()
 {
  FILE *f;
  bmpHeader bf;
  bmpInfo   bi;
  f = fopen(FileName,"r");
  fread((char*)&bf,sizeof(bf),1,f);
  fread((char*)&bi,sizeof(bi),1,f);
//  fread((char*)&cm,sizeof(cm),1,f);

  printf("\nbfType          %c%c ",bf.bfType[0],bf.bfType[1]);
  printf("\nbfSize          %u ",bf.bfSize);
  printf("\nbfReserved1     %d ",bf.bfReserved1);
  printf("\nbfReserved2     %d ",bf.bfReserved2);
  printf("\nbfOffBits       %u ",bf.bfOffBits);
  printf("\n\nBMP InfoStructure\n");
  printf("\nbiSize          %u",bi.biSize);
  printf("\nbiWidth         %u",bi.biWidth);
  printf("\nbiHeight        %u",bi.biHeight);
  printf("\nbiPlanes        %u",bi.biPlanes);
  printf("\nbiBitCount      %u",bi.biBitCount);
  printf("\nbiCompression   %u",bi.biCompression);
  printf("\nbiSizeImage     %u",bi.biSizeImage);
  printf("\nbiXPelsPerMeter %u",bi.biXPelsPerMeter);
  printf("\nbiYPelsPerMeter %u",bi.biYPelsPerMeter);
  printf("\nbiClrUsed       %u",bi.biClrUsed);
  printf("\nbiClrImportant  %u\n",bi.biClrImportant);


  char dummy;

  int  cnt=8/bi.biBitCount;
  byte bitmask=0;
  for(int i=0;i<bi.biBitCount;i++)
    bitmask |= (1<<i);
  printf("\n\n %d %X ",cnt,bitmask);
  int gd,gm;
  getchar();
  detectgraph(&gd,&gm);
  initgraph(&gd,&gm,"c:\\Cpp\\Bgi");

  word y=0,x=0;
  word bytes =0;
  fclose(f);
  f=fopen(FileName,"r");
  for (;bytes<bf.bfOffBits;bytes++)
    fread(&dummy,sizeof(char),1,f);

  int scl=(bi.biBitCount==1) ? 15:1;
  char dummy2;
 do
 {
   fread(&dummy,sizeof(dummy),1,f);
//     fread(&dummy2,sizeof(char),1,f);
     bytes++;
     int X ;
     int Y ;
    for (int k=0;k<cnt;k++)
    {
     int Pix,Pix2;
     Pix = (dummy>>((cnt-k-1)*bi.biBitCount))&bitmask;

     X = x;
     Y = bi.biHeight-y;
       for(int i=0;i<4;i++)
	for (int j=0;j<4;j++)
	 {
	  putpixel(100+X*4+i,20+Y*4+j,Pix*scl);
	 // putpixel(4*bi.biWidth/2+100+X*4+i,20+Y*4+j,Pix2*scl);
	 }
       putpixel(x,y,Pix*scl);
       //putpixel(bi.biWidth/2+x,y,Pix2*scl);
     x++;
     if (x==bi.biWidth+1)
      { x=0;y++;}
    }
   }
  while((y<bi.biHeight) && !feof(f));

  getchar();
  return 0;
 }




/*void bmpInterleaveBit1()
 {
  char dummy,dummy2;

  do
   {
     fread(&dummy,sizeof(dummy),1,f);
     fread(&dummy2,sizeof(char),1,f);
     bytes++;
     int X ;
     int Y ;
     for (int k=0;k<cnt;k++)
      {
       int Pix,Pix2;
       Pix = (dummy>>((cnt-k-1)*bi.biBitCount))&bitmask;
       Pix2 = (dummy2>>((cnt-k-1)*bi.biBitCount))&bitmask;

       X = x;
       Y = y;
       if (X <bi.biWidth/2)
	{
       for(int i=0;i<4;i++)
	for (int j=0;j<4;j++)
	 {
	  putpixel(100+X*4+i,20+Y*4+j,Pix*scl);
	  putpixel(4*bi.biWidth/2+100+X*4+i,20+Y*4+j,Pix2*scl);
	 }
       putpixel(x,y,Pix*scl);
       putpixel(bi.biWidth/2+x,y,Pix2*scl);
      }
       x++;
       if (x==bi.biWidth)
	{ x=0;y++;}
      }
   }
  while((y<bi.biHeight) && !feof(f));
 } */