#ifndef __KBDFLAGS_H
#define __KBDFLAGS_H

// -------------- Keyboard Byte Flags --------------- \\

#define RhtShiftDn         0x01
#define LftShiftDn         0x02
#define CtrlKeyDn          0x04
#define AltKeyDn           0x08
#define ScrollLckOn        0x10
#define NumLckOn           0x20
#define CapsLckOn          0x40
#define InsertOn           0x80

// -------------- Keyboard Word Flags --------------- \\

#define AnyShftKyDn      0x0003
#define RhtShftKyDn      0x0001
#define LftShftKyDn      0x0002
#define AnyCtrlKeyDn     0x0004
#define AnyAltKeyDn      0x0008
#define ScrollLckTglOn   0x0010
#define NumLckTglOn      0x0020
#define CapsLckTglOn     0x0040
#define InsToggleOn      0x0080
#define LftCtrlDn        0x0100
#define LftAltDn         0x0200
#define RhtCtrlDn        0x0400
#define RhtAltDn         0x0800
#define ScrollKeyDn      0x1000
#define NumLckKeyDn      0x2000
#define CapsLckKeyDn     0x4000
#define SysReqKeyDn      0x8000

#endif
