typedef struct far
	 {
	   byte x,y;
	 } CurXYPos;

typedef struct far
	 {
	   byte  VidModes[3];
	   dword Reserved1;
	   byte  AvlScanLns;
	   byte  AvlChrBlks;
	   byte  MaxActChrBlks;
	   word  MiscBIOSCpbl;
	   word  Reserved2;
	   byte  SaveAreaCpbl;
	   byte  Reserved3;
	 } DspAdptInf;

typedef struct far
	 {
	   DspAdptInf *V;
	   byte       CurVidMode;
	   word       NumChrClmns;
	   word       VidRefreshBufLen;
	   word       BufStrtAddr;
	   CurXYPos   Page[8];
	   byte       CurStrtScanLn;
	   byte       CurEndScanLn;
	   byte       ActDspPage;
	   word       AdptBasePortAddr; //byte
	   byte       Regs3B8or3D8;
	   byte       Regs3B9or3D9;
	   byte       NumChrRows;
	   word       ChrHtScanLns;
	   byte       ActDspCode;
	   byte       InActDspCode;
	   word       MaxCols;
	   byte       MaxPages;
	   byte       NumScanLns;
	   byte       PriChrBlk;
	   byte       SecChrBlk;
	   byte       MiscStateInf;
	   byte       Reserved1[3];
	   byte       AvlVidMem;
	   byte       SavePtrStateInf;
	   byte       Reserved2[13];
	 } VidAdptInf;
