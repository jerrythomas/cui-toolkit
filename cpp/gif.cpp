#include <Pixel.h>
#include <Kbd.h>

struct GifHeader
 {
  char  Sig[6];
  word  ScreenWidth,ScreenDepth;
  byte  Flags,Background,Aspect;
 };
struct ImageBlock
 {
  word  Left,Top,Wide,Depth;
  byte  Flags;
 };
struct BinaryHeader
 {
  char Sign[8];
  int width,depth,bits;
  PaletteRegister Hue;
 };

 word Wide,Depth,L,T;
 int  cptIdx;
 char cpt[12] = "dump";

#define largest_code  4095
#define table_size  5003
#define GIFSIG "GIF87a"

char code_buffer[259];
int oldcode[table_size];
int current_code[table_size];
char newcode[table_size];

int code_size;
int clear_code;
int eof_code;
int bit_offset;
int byte_offset;
int bits_left;
int max_code;
int free_code;
int BackCol;

void strmfe(char *New,char *old,char *ext)
 {
  while(*old != 0 && *old != '.')
      *New++ = *old++;
  while(*ext)
      *New++ = *ext++;
  *New = 0;
 }
void init_table(int min_code_size)
 {
  int i;
  code_size = min_code_size+1;
  clear_code = (1<<min_code_size);
  eof_code = clear_code+1;
  free_code = clear_code+2;
  max_code = (1<<code_size);
  for(i=0;i<table_size;i++)
   current_code[i] = BackCol;
 }
void flush(FILE *fp,int n)
 {
  fputc(n,fp);
  fwrite(code_buffer,1,n,fp);
 }
void write_code(FILE *fp,int code)
 {
  long temp;
  byte_offset = bit_offset >> 3;
  bits_left = bit_offset&7;
  if (byte_offset >= 254)
   {
    flush(fp,byte_offset);
    code_buffer[0] = code_buffer[byte_offset];
    bit_offset = bits_left;
    byte_offset = 0;
   }
  if (bits_left > 0)
   {
    temp = ((long)  code <<bits_left)|code_buffer[byte_offset];
    code_buffer[byte_offset] = temp;
    code_buffer[byte_offset+1] = (temp>>8);
    code_buffer[byte_offset+2] = (temp>>16);
   }
  else
   {
    code_buffer[byte_offset] = code;
    code_buffer[byte_offset+1] = (code>>8);
   }
  bit_offset += code_size;
 }
int LZWCompressImage(FILE *fp,word min_code_size)
 {
   int prefix_code;
   int suffix_char;
   int hx,d;
   int x,y;

   // make sure the initial code size is legal
   if (min_code_size < 2 || min_code_size > 9)
    {
     //monochrome images have two bits in LZW compression
     if (min_code_size ==1) min_code_size = 2;
     else return(EOF);
    }

   //write initial code size
   fputc(min_code_size,fp);
   //initialize the encoder
   bit_offset = 0;
   init_table(min_code_size);
   write_code(fp,clear_code);
   // initialise the prefix;
   prefix_code = suffix_char = GetPixel(L,T);
   for (y=0;y<Depth;y++)
   for (x=0;x<Wide;x++)

   //while (x <= Wide && y <= Depth)
    {
     suffix_char = GetPixel(L+x,T+y);
     // derive an index to toe code table
     hx = (prefix_code^(suffix_char << 5))%table_size;
     d = 1;
     for (;;)
      {
       // see if code is in the table
       if (current_code[hx]==BackCol)
        {
         write_code(fp,prefix_code);
         d = free_code;
         // find next free code
         if (free_code <= largest_code)
          {
           oldcode[hx] = prefix_code;
           newcode[hx] = suffix_char;
           current_code[hx] = free_code;
           free_code++;
          }
         // expand the code size or scrap the table
         if (d== max_code)
          {
           if (code_size < 12)
            {
             code_size++;
             max_code <<=1;
            }
           else
            {
             write_code(fp,clear_code);
             init_table(min_code_size);
            }
          }
         prefix_code = suffix_char;
         break;
        }
       if (oldcode[hx] == prefix_code &&
           newcode[hx] == suffix_char)
        {
         prefix_code = current_code[hx];
         break;
        }
       hx += d;
       d+= 2;
        if(hx >= table_size) hx -= table_size;
      }
    }
   // write the prefix_code
   write_code(fp,prefix_code);
   write_code(fp,eof_code);
   // flush buffer
   if (bit_offset > 0) flush(fp,(bit_offset+7)/8);
   //write zero length block;
   flush(fp,0);
   return(ferror(fp));
 }
int writeImageDesc(FILE *fp,word L,word T,word W,word D,int bits,char *pal)
 {
  ImageBlock ib;
  memset((char*)&ib,0,sizeof(ImageBlock));
  // fill image block
  fputc(',',fp);
  ib.Left = L;
  ib.Top = T;
  ib.Wide = W;
  ib.Depth = D;
  if (pal == NULL)
   ib.Flags=bits-1;
  else
   ib.Flags = ((bits-1)&0x07)|0x80;

  fwrite((char*)&ib,1,sizeof(ImageBlock),fp);
  if (pal != NULL)
    fwrite(pal,1,3*(1<<bits),fp);
  return ferror(fp);
 }
int writeScreenDesc(FILE *fp,word W,word D,word bits,word background,char *pal)
 {
  GifHeader gh;
  memset((char*)&gh,0,sizeof(GifHeader));
  memcpy(gh.Sig,GIFSIG,6);
  gh.ScreenWidth = W;
  gh.ScreenDepth = D;
  gh.Background  = background;
  gh.Aspect = 0;
  if (pal ==NULL)
   gh.Flags = ((bits-1)&0x07)<<4;
  else
   gh.Flags = (0x80|((bits-1)<<4)|((bits-1)&0x07));
  fwrite((char*)&gh,1,sizeof(GifHeader),fp);
  if(pal != NULL)
   fwrite(pal,1,3*(1<<bits),fp);
  return ferror(fp);
 }

int writeGif(FILE *fp,word W,word D,word bits,char *pal)
 {
  if (writeScreenDesc(fp,W,D,bits,BackCol,pal)) return 1;

  if (writeImageDesc(fp,0,0,W,D,bits,NULL)) return 2;

  if (LZWCompressImage(fp,bits)) return 3;

  fputc(';',fp);
  return ferror (fp);
 }

void capture(int l,int t,int r,int b,int  back)
 {
   int bits=8;
   FILE *out;
   L= l;
   T= t;
   Wide  = r-l+1;//xMax();//+1;
   Depth = b-t+1;//10;//yMax()+1;
   BackCol = back;
   itoa(cptIdx++,cpt+4,10);
   strcat(cpt,".Gif");
   out = fopen(cpt,"wb");
   InitPalette7x36(RGBHue);
   for (int i=0;i<256;i++)
   {
    RGBHue[i].red = (RGBHue[i].red<< 2)|0x03;
    RGBHue[i].grn = (RGBHue[i].grn<< 2)|0x03;
    RGBHue[i].blu = (RGBHue[i].blu<< 2)|0x03;
   }
   //RGBHue[0].red = RGBHue[0].blu = RGBHue[0].grn =255;
   int  n = writeGif(out,Wide,Depth,bits,(char*)&RGBHue);
   fclose(out);
 }
void main(int argc,char **argv)
 {
  GifHeader gh;
  FILE *ip,*op;
  int bits = 8;
  if (argc>=2)
   {
    ip = fopen(argv[1],"rb");
    op = fopen(argv[2],"wb");
    fread((char*)&gh,1,sizeof(GifHeader),ip);
    fread((char*)&RGBHue,1,3*(1<<bits),ip);
    InitPalette7x36(RGBHue);
    for (int i=0;i<256;i++)
    {
     RGBHue[i].red = (RGBHue[i].red<<2)|0x03;
     RGBHue[i].grn = (RGBHue[i].grn<<2)|0x03;
     RGBHue[i].blu = (RGBHue[i].blu<<2)|0x03;
    }
   //RGBHue[0].red = RGBHue[0].blu = RGBHue[0].grn =255;
   fwrite((char*)&gh,1,sizeof(GifHeader),op);
   fwrite((char*)&RGBHue,1,3*(1<<bits),op);
   while (!feof(ip))
    fputc(fgetc(ip),op);
   fclose(ip);
   fclose(op);
  }
 }