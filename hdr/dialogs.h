#ifndef __DIALOGS_H
#define __DIALOGS_H

#ifndef __VIDEO_H
#include <video.h>
#endif

Class DialogClass
	{
	  private:

		Byte  L,T,R,B,X,Y;
		Byte  cHdr,cWrk,cBox,cLock,cHot;
		Byte  DlgFill;
		Fun   DlgXec,DlgXit,DlgHlp;
		Image *Scr;
		Word  Specs;

	  public:

		DialogClass(void);
		~DialogClass(void);

		void SetDialogClient(Fun Xec);
		void SetDialogClose (Fun Xit);
		void SetDialogHlp   (Fun Hlp);
		void SetDialogColors(Byte H,Byte W,Byte X,Byte L,Byte O,Byte F);
		void DialogSetUp    (Byte l,Byte t,Byte r,Byte b,Word Ops,char *DAN);

		void DialogDraw(void);
		void DialogMinimise (void);
		void DialogMaximise (void);
		void DialogMoveSize (void);
	};

#endif
