typedef unsigned int word;
typedef enum { false,true} bool;
class Object
 {
   public :
     int xOff,yOff,W,H;

   public :
     virtual word Xecute()    { return 0; }
     virtual bool KeyPress()  { return false; }
     virtual bool MouseMove() { return false; }
     virtual void Resize(int Wd,int Ht)
      {
	W = Wd;
	H = Ht;
      }
     virtual void Origin(int x,int y)
      {
	xOff = x;
	yOff = y;
      };
 };
