#ifndef __SET_H
 #define __SET_H
 
typedef unsigned char byte;
typedef unsigned int  word;

#define EmptySet   0x01
#define FullSet    0x02
#define OutOfScope 0x04

template <class T>
 class Set
  {
    private :

      T    *Member;
      word *Priori;
      word Max,
           Top;
      byte Flag;

    public :

     Set();
     Set(word N);
     ~Set();

     byte Status();

     byte Add(T Val);
     byte Add(T Val,word Pri);
     byte Delete(T Val);
     byte Peek(int i,T& Val);
     byte Peek(int i,T& Val,word& Pri);

     byte isMember(T Val);
     byte Priority(T Val,word& Pri);
   };
#endif
