#ifndef __FONT_H
#define __FONT_H

typedef unsigned word;
typedef unsigned char byte;

#define PostScriptID  0x436
#define Psf256        0
#define Psf512        1

#define FileOpenErr   0x8000
#define FileReadErr   0x4000
#define FileCreateErr 0x2000

#define FontLoaded    0x0080

void LoadUserFont(byte H,word TotChr,byte *Buf)
 {
   word Sg = FP_SEG(Buf);
   word Of = FP_OFF(Buf);
   asm push es;
   asm push bp;
   asm mov  ax,0x1100;
   asm mov  bh,H;
   asm mov  bl,0;
   asm mov  cx,TotChr;
   asm mov  dx,Sg;
   asm mov  es,Sg;
   asm mov  bp,Of;
   asm mov  dx,0;
   asm int  0x10;
   asm pop  bp;
   asm pop  es;
 }
struct PsfHeader
 {
  word FileID;
  byte FileMode;
  byte FontHeight;
 };

class Font
 {
  public :

   byte  Buffer[4096];
   word  BufSize;
   byte  Height;
   word  swFont;
   char  *FontFile;

  public :

   Font();
   Font(Font& f);
   Font(char * FileName);

   void xCopy(Font& src,byte strt,byte stop);

   virtual void Load(char * FileName);
   virtual void Save();
   virtual void SaveAs(char * FileName);
   virtual void Activate();
   //void Edit();
 };

class PsfFont : public Font
 {
   private :
     PsfHeader Psf;

   public :

     PsfFont();
     PsfFont(Font& f);
     PsfFont(char * FileName);

     virtual void Load(char * FileName);
     virtual void Save();
     virtual void SaveAs(char * FileName);
 };

#endif

Font::Font()
 {
   swFont   = 0x0000;
   BufSize  = 4096;
   Height   = 16;
   FontFile = (char*)NULL;
   memset(Buffer,0,BufSize);
 }
Font::Font(Font& f)
 {
   memcpy(Buffer,f.Buffer,4096);
   BufSize=f.BufSize;
   Height=f.Height;
   swFont=f.swFont;
 }
Font::Font(char *FileName)
 {
   swFont   = 0x0000;
   BufSize  = 4096;
   Height   = 16;
   FontFile = (char*)NULL;
   memset(Buffer,0,BufSize);
   Load(FileName);
 }

void Font::xCopy(Font& src,byte strt,byte stop)
 {
   if (src.Height == Height)
    {
      int cpySiz = (stop-strt+1)*Height;
      memcpy(Buffer+strt*Height,src.Buffer+strt*src.Height,cpySiz);
    }
   else if (src.Height < Height)
    {
      for (int i = strt;i<stop;i++)
        memcpy(Buffer+i*Height,src.Buffer+i*src.Height,src.Height);
    }
 }

void Font::Load(char *FileName)
 {
   FILE *fp;

   if (FontFile != (char*)NULL)
       delete FontFile;

   FontFile = new char[strlen(FileName) + 1];
   strcpy(FontFile,FileName);

   swFont |= ((fp=fopen(FontFile,"rb")) == (FILE*)NULL) ? FileOpenErr:0;
   if (swFont != FileOpenErr)
    {
      BufSize=fread(Buffer,sizeof(char),BufSize,fp);
      //for (BufSize=0;BufSize<4096 && !feof(fp);BufSize++)
       // Buffer[BufSize] = getc(fp);
      BufSize = (BufSize > 4096) ? 4096:BufSize;
      Height = BufSize/256;
      swFont |= FontLoaded;
    }

   fclose(fp);
 }

void Font::Save()
 {
   FILE *fp;

   if ((swFont&FontLoaded) && FontFile != (char*)NULL)
    {
      swFont |= ((fp=fopen(FontFile,"wb")) == (FILE*)NULL) ? FileCreateErr:0;
      if (!(swFont&FileCreateErr))
	  fwrite(Buffer,sizeof(char),BufSize,fp);
      fclose(fp);
    }
 }

void Font::SaveAs(char *FileName)
 {
   FILE *fp;

   if (swFont&FontLoaded)
    {
      if (FontFile != (char*)NULL)
       delete FontFile;

      FontFile = new char[strlen(FileName) + 5];
      strcpy(FontFile,FileName);
      strcat(FontFile,".fnt");

      swFont |= ((fp=fopen(FontFile,"wb")) == (FILE*)NULL) ? FileCreateErr:0;
      if (!(swFont&FileCreateErr))
	  fwrite(Buffer,sizeof(char),BufSize,fp);

      fclose(fp);
    }
 }
void Font::Activate()
 {
   LoadUserFont(Height,256,Buffer);
 }

PsfFont::PsfFont():Font()
 {
   Psf.FileID     = 0x436;
   Psf.FileMode   = 0;
   Psf.FontHeight = 16;
 }
PsfFont::PsfFont(Font& f) :Font(f)
 {
   Psf.FileID     = 0x436;
   Psf.FileMode   = 0;
   Psf.FontHeight = Height;
   FontFile  = (char*)NULL;
 }
PsfFont::PsfFont(char *FileName) :Font()
 {
   Psf.FileID     = 0x436;
   Psf.FileMode   = 0;
   Psf.FontHeight = 16;
   Load(FileName);
 }
void PsfFont::Load(char *FileName)
 {
   FILE *fp;

   if (FontFile != (char*)NULL)
       delete FontFile;

   FontFile = new char[strlen(FileName) + 5];
   strcpy(FontFile,FileName);
   strcat(FontFile,".psf");

   swFont |= ((fp=fopen(FontFile,"rb")) == (FILE*)NULL) ? FileOpenErr:0;
   if (swFont != FileOpenErr)
    {
      if (fread((char*)&Psf,sizeof(Psf),1,fp) != 1)
          swFont |= FileReadErr;
      else
       {
        Height = Psf.FontHeight;
        if (Height && Psf.FileID==PostScriptID)
	  BufSize=fread(Buffer,sizeof(char),BufSize,fp);

        swFont |= FontLoaded;
       }
    }
   fclose(fp);
 }
void PsfFont::Save()
 {
   FILE *fp;

   Psf.FontHeight = Height;
   if ((swFont&FontLoaded) && FontFile != (char*)NULL)
    {
      swFont |= ((fp=fopen(FontFile,"wb")) == (FILE*)NULL) ? FileCreateErr:0;
      if (!(swFont&FileCreateErr))
       {
	fwrite((char*)&Psf,sizeof(Psf),1,fp);
        fwrite(Buffer,sizeof(char),BufSize,fp);
       }
      fclose(fp);
    }
 }

void PsfFont::SaveAs(char *FileName)
 {
   FILE *fp;
   printf("\n %x",swFont);
   if (swFont&FontLoaded)
    {
      if (FontFile != (char*)NULL)
       delete FontFile;

      FontFile = new char[strlen(FileName) + 5];
      strcpy(FontFile,FileName);
      strcat(FontFile,".psf");
      printf("\n%s",FontFile);
      //Psf.FontHeight = Height;
      swFont |= ((fp=fopen(FontFile,"wb")) == (FILE*)NULL) ? FileCreateErr:0;

      if (!(swFont&FileCreateErr))
       {
        fwrite((char*)&Psf,sizeof(Psf),1,fp);
        fwrite(Buffer,sizeof(char),BufSize,fp);
       }
      fclose(fp);
    }
 }
struct FontRef
  {
    byte  State;
    byte  BackCol;
    byte  ForeCol;
  }

class Font
 {
   private :
     byte    *Buffer;
     word    BufSize;
     byte    Height;

     word    swFont;

     byte    BackCol,ForeCol;
     byte    FntState;

   private :
     void xPutc(word x,word y,byte Ascii);

   public :

     Font();
     ~Font();

     Load(char *Fnt);

     void ForeColor(byte Col);
     byte ForeColor();
     void BackColor(byte Col);
     byte BackColor();
     void DrawMode(byte DrwMode);
     byte DrawMode();

     void Transparency(bool OnOff);
     bool Transparency();
     void Italic(bool OnOff);
     bool Italic();
     void Bold(bool OnOff);
     bool Bold();

     void SetAll();
     void ClearAll();

     void Print(word x,word y,char *fmt,...);
  }


class FontMgr
 {
   private :
     Font  *Fnt[10];    // to collect fonts
     byte  Count;       // count of fonts in memory
     char  **AllFonts;   // list of all available fonts

   public :
     FontMgr();
     ~FontMgr();

     Font *GetFont(char *FntName);
     bool Remove(Font *FntName);
 }

void Font::Load(char *FontFile)
 {
   FILE      *fp;
   PsfHeader Psf;

   swFont |= ((fp=fopen(FontFile,"rb")) == (FILE*)NULL) ? FileOpenErr:0;
   if (swFont != FileOpenErr)
    {
      if (fread((char*)&Psf,sizeof(Psf),1,fp) != 1)
          swFont |= FileReadErr;
      else if (Psf.FontHeight && Psf.FileID==PostScriptID)
       {
         BufSize = Psf.FontHeight * 256 (1+Psf.FileMode);
         if (Buffer != (byte*)NULL) delete Buffer;
         Buffer = new byte[BufSize];
         fread(Buffer,sizeof(byte),BufSize,fp);
         swFont |= FontLoaded;
       }
    }
   fclose(fp);
 }
