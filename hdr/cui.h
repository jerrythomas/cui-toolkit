#include <mouse.h>
#include <vdu.h>
#include <kbd.h>

#define RadioBtn      0x0020
#define RadioBtnOn    0x00A0
#define CheckBtn      0x0040
#define CheckBtnOn    0x00C0

#define ActiveRadio   0x0021
#define ActiveRadioOn 0x00A1
#define ActiveCheck   0x0041
#define ActiveCheckOn 0x00C1

#define HiddenRadio   0x0022
#define HiddenRadioOn 0x00A2
#define HiddenCheck   0x0042
#define HiddenCheckOn 0x00C2

#define LockedPad     0x0000
#define ActivePad     0x0001
#define HiddenPad     0x0002
#define MenuBreak     0x0004
#define ExitProgram   0x0008
#define ColourPad     0x0010
#define RadioPad      0x0020
#define CheckPad      0x0040
#define PadState      0x0080
#define PadColour     0x0F00
#define AppXec        0x1000
#define RetPad        0x2000
#define CloseMenus    0x4000
#define ReservedP     0x8000
#define SpcCorrection 0x0070

#define MenuHz        0x0000
#define MenuVt        0x0001
#define PadSpc        0x000E
#define Effects       0x0030
#define EffectsDir    0x01C0
#define Shadow        0x0200
#define Border        0x0400
#define BoxStyle      0x1800
#define ReservedM     0x2000
#define UpdateScr     0x4000
#define MenuOpen      0x8000

#define ShowEff       0x03F0
#define SpcMask       0xFFF1
#define SetSpc        0x0070
#define SpcShft       0x01
#define StateShft     0x07
#define ColourShft    0x08
#define EffShft       0x04
#define BoxShft       0x0B

#define XecPad         0x01
#define Close          0x02
#define MaskClose      0xFD
#define CloseAll       0x04
#define RefreshMenu    0x08
#define OpenMenu       0x10
#define CloseMenu      0x06
#define XecOrClose     0x03
#define RefAndClose    0x0A
#define XecAndClose    0x03
#define XecAndCloseAll 0x07
#define None           0x00

#define NoShow           0x0006
#define HSVSBoxShadow    0x0600
#define HDVSBoxShadow    0x0E00
#define HSVDBoxShadow    0x1600
#define HDVDBoxShadow    0x1E00

#define BlackPad         0x0010
#define BluePad          0x0110
#define GreenPad         0x0210
#define CyanPad          0x0310
#define RedPad           0x0410
#define MagentaPad       0x0510
#define BrownPad         0x0610
#define LightGrayPad     0x0710

#define DarkGrayPad      0x0810
#define LightBluePad     0x0910
#define LightGreenPad    0x0A10
#define LightCyanPad     0x0B10
#define LightRedPad      0x0C10
#define LightMagentaPad  0x0D10
#define YellowPad        0x0E10
#define WhitePad         0x0F10

#define SlideRtMenuHz    0x0000
#define SlideLtMenuHz    0x0040
#define SlideDnMenuHz    0x0080
#define SlideUpMenuHz    0x00C0
#define SlideRtDnMenuHz  0x0100
#define SlideLtDnMenuHz  0x0140
#define SlideRtUpMenuHz  0x0180
#define SlideLtUpMenuHz  0x01C0

#define SlideRtMenuVt    0x0001
#define SlideLtMenuVt    0x0041
#define SlideDnMenuVt    0x0081
#define SlideUpMenuVt    0x00C1
#define SlideRtDnMenuVt  0x0101
#define SlideLtDnMenuVt  0x0141
#define SlideRtUpMenuVt  0x0181
#define SlideLtUpMenuVt  0x01C1


#define M_File     0x100
#define MF_New     0x101
#define MF_Open    0x102
#define MF_Save    0x103
#define MF_Copy    0x104
#define MF_Exit    0x105

#define M_Edit     0x106
#define ME_Cut     0x107
#define ME_Copy    0x108
#define ME_Paste   0x109
#define ME_Del     0x10A
#define ME_ViewClp 0x10B
#define ME_Clip    0x10C

#define M_Print    0x10D
#define MP_Block   0x10E
#define MP_Print   0x10F
#define MP_Delete  0x110
#define MP_View    0x111
#define MP_Edit    0x112

typedef struct
         {
           char  *Prompt;      // Contains the Prompt string
           char  *ShortCut;    // Address of ShortCut String
           byte  HotKeyPos;    // Position of Hot Character
           byte  HotKey;       // Short Cut Key Code
           word  ItemID;       // Item Identification code
           word  swItem;       // Item Status Word
         } ItemInf;

typedef struct Pad
         {
           ItemInf      Inf;        // Pad Information
           App          PadApp;     // App to be taken on selection
           char         *Msg;       // Message string for guidance
           Pad          *Prv,*Nxt;  // Ptr to next and previous items
           struct Menu  *SubMenu;   // Ptr to Sub-Menu
         } ;

typedef struct Menu
         {
          byte    L,T;         // Top Left Coordinates of Menu
          byte    X,           // Width  Of Menu
                  Y;           // Height Of Menu
          word    swMenu;      // Menu type & other flags
          Pad     *F,          // Ptr to first Pad
                  *H,          // Ptr to Highlighted Pad
                  *VisF,       // Ptr to first Visible Pad
                  *VisL;       // Ptr to last Visible Pad
//          Scheme  MenuColSch;  // Colour Scheme
          byte    MaxPads;
         } ;

typedef struct Stack
         {
           Menu   *MenuPtr;    // Stores Current Menu pointer
           byte   NoOfPads;    //
	        Stack  *Link;       // Link To next Element in Stack
         } ;


class MenuDef
 { 
   public :
   Menu    MainMenu,*MnuG,*PrvM;   // Global Menu Pointer
   Pad     *PadC,*PadN;              // Current,Next & Previous Bar Items
   Scheme  HzSch,                // Hz Menu Colour Scheme
           VtSch;                // Vt Menu Colour Scheme
   Stack   *S;                   // Global Stack Pointer
   Word    MaxID;
   Word    Key;                  // Stores key value for use in menu
   Word    UsrMenuID,
           UsrFlags;
   Byte    Spc,
           NumPads,
           MenuLev;

   Byte    X,Y,R,B;

   MenuDef();

   void PushMenuStack();
   byte PopMenuStack();
   byte NextPad(byte XorY,Menu *M,Pad *P) ;
   byte HzMenuBreak(byte X,byte Spc);
   void SetMainMenuPos(byte L,byte T,byte R,byte B);
   byte FirstVisPad(Menu *M);
   byte LastVisPad(Menu *M);
   byte VisiblePads(Menu *M) ;
   void ScrollPadPrv(Menu *M);
   void ScrollPadNxt(Menu *M);
   void DrawPad(byte x,byte y,Menu *M,Pad *P,byte Txt,byte Hot);
   void DrawMenu();
   void RePaintMenu();
   byte MenuMouse(Menu *M);
   byte MenuCtrl();
   byte DefinePad(char *Txt, word PadType, App PadApp);
   void DefineMenu(word MenuType, word Other ,byte MaxItem) ;
   byte XecMenu();
   byte SearchPad(word ID,Menu *M);
   void SetPadHlp(word PadID,char *PadHlp);
   void SetPadState(word PadID,word State);
   
 }; 
