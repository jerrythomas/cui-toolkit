#ifndef __ZSTRING_H
 #define __ZSTRING_H
 
#include <string.h>
#include <iostream.h>
#include <stdio.h>

typedef unsigned int word;
typedef char far fchar;

#define VarLengthString    0x01
#define FixedLengthString  0x02

#define min(a,b) ((a) < (b)) ? (a):(b)

class far String
 {
  int  length;
  word swString;

  public :
    char *str;


  void AllocateAndInitialise();

  public :

   ~String();
   String();
   String(int N);
   String(char *S);

   String& operator = (String S);
   String& operator = (char *S);

   String& operator + (String S);
   String& operator + (char *S);

   String& operator +=(String S);
   String& operator +=(char *S);

   String& SubString(int start,int len);
   String& LTrim();
   String& RTrim();
   String& AllTrim();
   String& Reverse();
   String& FillWith(char c,int Num);

   int    IsNumeric();
   float  ToFloat();
   int    ToInt();
   void   out();
 };
#endif