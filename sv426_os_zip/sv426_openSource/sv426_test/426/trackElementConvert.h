#ifndef TRACKELEMENTCONVERT_H
#define  TRACKELEMENTCONVERT_H

#include<rct1lib.h>
#include<rct2lib.h>

#define RCT_NUMTRACKELEMENTS 0x100

BYTE RCT1to2trackElementConversionTable[RCT_NUMTRACKELEMENTS]=
{
/*0x00*/ 0x00, /*flat */
/*0x01*/ 0x01, /*end station */
/*0x02*/ 0x02, /*begin station */
/*0x03*/ 0x03, /*middle station */
/*0x04*/ 0x04, /*25 /\ */
/*0x05*/ 0x05, /*60 /\ */
/*0x06*/ 0x06, /*flat to 25 /\ */
/*0x07*/ 0x07, /*25 /\ to 60 /\ */
/*0x08*/ 0x08, /*60 /\ to 25 /\ */
/*0x09*/ 0x09, /*25 /\ to flat */
/*0x0A*/ 0x0A, /*25 \/ */
/*0x0B*/ 0x0B, /*60 \/ */
/*0x0C*/ 0x0C, /*flat to 25 \/ */
/*0x0D*/ 0x0D, /*25 \/ to 60 \/ */
/*0x0E*/ 0x0E, /*60 \/ to 25 \/ */
/*0x0F*/ 0x0F, /*25 \/ to flat */
/*0x10*/ 0x10, /*L ¼ D5 */
/*0x11*/ 0x11, /*R ¼ D5 */
/*0x12*/ 0x12, /*flat to L bank */
/*0x13*/ 0x13, /*flat to R bank */
/*0x14*/ 0x14, /*L bank to flat */
/*0x15*/ 0x15, /*R bank to flat */
/*0x16*/ 0x16, /*L ¼ D5 bank */
/*0x17*/ 0x17, /*R ¼ D5 bank */
/*0x18*/ 0x18, /*L bank to 25 /\ */
/*0x19*/ 0x19, /*R bank to 25 /\ */
/*0x1A*/ 0x1A, /*25 /\ to L bank */
/*0x1B*/ 0x1B, /*25 /\ to R bank */
/*0x1C*/ 0x1C, /*L bank to 25 \/ */
/*0x1D*/ 0x1D, /*R bank to 25 \/ */
/*0x1E*/ 0x1E, /*25 \/ to L bank */
/*0x1F*/ 0x1F, /*25 \/ to R bank */
/*0x20*/ 0x20, /*L bank */
/*0x21*/ 0x21, /*R bank */
/*0x22*/ 0x22, /*L ¼ D5 25 /\ */
/*0x23*/ 0x23, /*R ¼ D5 25 /\ */
/*0x24*/ 0x24, /*L ¼ D5 25 \/ */
/*0x25*/ 0x25, /*R ¼ D5 25 \/ */
/*0x26*/ 0x26, /*L "S" bend */
/*0x27*/ 0x27, /*R "S" bend */
/*0x28*/ 0x28, /*L vertical loop */
/*0x29*/ 0x29, /*R vertical loop */
/*0x2A*/ 0x2A, /*L ¼ D3 */
/*0x2B*/ 0x2B, /*R ¼ D3 */
/*0x2C*/ 0x2C, /*L ¼ D3 bank */
/*0x2D*/ 0x2D, /*R ¼ D3 bank */
/*0x2E*/ 0x2E, /*L ¼ D3 25 /\ */
/*0x2F*/ 0x2F, /*R ¼ D3 25 /\ */
/*0x30*/ 0x30, /*L ¼ D3 25 \/ */
/*0x31*/ 0x31, /*R ¼ D3 25 \/ */
/*0x32*/ 0x32, /*L ¼ D1 */
/*0x33*/ 0x33, /*R ¼ D1 */
/*0x34*/ 0x34, /*L twist \/ to /\ */
/*0x35*/ 0x35, /*R twist \/ to /\ */
/*0x36*/ 0x36, /*L twist /\ to \/ */
/*0x37*/ 0x37, /*R twist /\ to \/ */
/*0x38*/ 0x38, /*½ loop /\ */
/*0x39*/ 0x39, /*½ loop \/ */
/*0x3A*/ 0x3A, /*L corkscrew /\ */
/*0x3B*/ 0x3B, /*R corkscrew /\ */
/*0x3C*/ 0x3C, /*L corkscrew \/ */
/*0x3D*/ 0x3D, /*R corkscrew \/ */
/*0x3E*/ 0x3E, /*flat to 60 /\ */
/*0x3F*/ 0x3F, /*60 /\ to flat */
/*0x40*/ 0x40, /*flat to 60 \/ */
/*0x41*/ 0x41, /*60 \/ to flat */
/*0x42*/ 0x42, /*tower base */
/*0x43*/ 0x43, /*tower section */
/*0x44*/ 0x44, /*flat covered */
/*0x45*/ 0x45, /*25 /\ covered */
/*0x46*/ 0x46, /*60 /\ covered */
/*0x47*/ 0x47, /*flat to 25 /\ covered */
/*0x48*/ 0x48, /*25 /\ to 60 /\ covered */
/*0x49*/ 0x49, /*60 /\ to 25 /\ covered */
/*0x4A*/ 0x4A, /*25 /\ to flat covered */
/*0x4B*/ 0x4B, /*25 \/ covered */
/*0x4C*/ 0x4C, /*60 \/ covered */
/*0x4D*/ 0x4D, /*flat to 25 \/ covered */
/*0x4E*/ 0x4E, /*25 \/ to 60 \/ covered */
/*0x4F*/ 0x4F, /*60 \/ to 25 \/ covered */
/*0x50*/ 0x50, /*25 \/ to flat covered */
/*0x51*/ 0x51, /*L ¼ D5 covered */
/*0x52*/ 0x52, /*R ¼ D5 covered */
/*0x53*/ 0x53, /*L "S" bend covered */
/*0x54*/ 0x54, /*R "S" bend covered */
/*0x55*/ 0x55, /*L ¼ D3 covered */
/*0x56*/ 0x56, /*R ¼ D3 covered */
/*0x57*/ 0x57, /*L ½ banked helix /\ small */
/*0x58*/ 0x58, /*R ½ banked helix /\ small */
/*0x59*/ 0x59, /*L ½ banked helix \/ small */
/*0x5A*/ 0x5A, /*R ½ banked helix \/ small */
/*0x5B*/ 0x5B, /*L ½ banked helix /\ large */
/*0x5C*/ 0x5C, /*R ½ banked helix /\ large */
/*0x5D*/ 0x5D, /*L ½ banked helix \/ large */
/*0x5E*/ 0x5E, /*R ½ banked helix \/ large */
/*0x5F*/ 0x5F, /*L ¼ D1 60 /\ */
/*0x60*/ 0x60, /*R ¼ D1 60 /\ */
/*0x61*/ 0x61, /*L ¼ D1 60 \/ */
/*0x62*/ 0x62, /*R ¼ D1 60 \/ */
/*0x63*/ 0x63, /*brakes */
/*0x64*/ 0x00, /*booster RCT2: Rotation control toggle (Spinning Wild Mouse)*/
/*0x65*/ 0xFF, /*{reserved}RCT2: inverted 90 /\ to flat quarter loop (multidim)*/
/*0x66*/ 0x66, /*L ¼ banked helix large /\ */
/*0x67*/ 0x67, /*R ¼ banked helix large /\ */
/*0x68*/ 0x68, /*L ¼ banked helix large \/ */
/*0x69*/ 0x69, /*R ¼ banked helix large \/ */
/*0x6A*/ 0x6A, /*L ¼ helix large /\ */
/*0x6B*/ 0x6B, /*R ¼ helix large /\ */
/*0x6C*/ 0x6C, /*L ¼ helix large \/ */
/*0x6D*/ 0x6D, /*R ¼ helix large \/ */
/*0x6E*/ 0x00, /*{ride base: 2 X 2} RCT2: 25 /\ L banked*/
/*0x6F*/ 0x6F, /*{ride base: 4 X 4} RCT2: 25 /\ R banked*/
/*0x70*/ 0x70, /*waterfall */
/*0x71*/ 0x71, /*rapids */
/*0x72*/ 0x72, /*on ride photo */
/*0x73*/ 0xFF, /*{reserved}RCT2: 25 \/ L banked*/
/*0x74*/ 0x74, /*{ride base: 1 X 5}RCT2: 25 \/ R banked*/
/*0x75*/ 0x75, /*watersplash */
/*0x76*/ 0x76, /*{shop/stall} RCT2: flat to 60 /\ - long base*/
/*0x77*/ 0x77, /*{ride base: 1 X 2} RCT2: 60 /\ to flat - long base*/
/*0x78*/ 0x78, /*whirlpool */
/*0x79*/ 0x79, /*{info kiosk}RCT2: 60 \/ to flat - long base*/
/*0x7A*/ 0x7A, /*{ride base: 1 X 4}RCT2: flat to 60 \/ - long base*/
/*0x7B*/ 0x7B, /*{ride base: 3 X 3}RCT2: Cable Lift Hill*/
/*0x7C*/ 0x7C, /*reverse whoa belly slope */
/*0x7D*/ 0x7D, /*reverse whoa belly vertical */
/*0x7E*/ 0x7E, /*90 /\ */
/*0x7F*/ 0x7F, /*90 \/ */
/*0x80*/ 0x80, /*60 /\ to 90 /\ */
/*0x81*/ 0x81, /*90 \/ to 60 \/ */
/*0x82*/ 0x82, /*90 /\ to 60 /\ */
/*0x83*/ 0x83, /*60 \/ to 90 \/ */
/*0x84*/ 0x84, /*brake for drop */
/*0x85*/ 0x85, /*L 1/8 OTD */
/*0x86*/ 0x86, /*R 1/8 OTD */
/*0x87*/ 0x87, /*L 1/8 DTO */
/*0x88*/ 0x88, /*R 1/8 DTO */
/*0x89*/ 0x89, /*L 1/8 bank OTD */
/*0x8A*/ 0x8A, /*R 1/8 bank OTD */
/*0x8B*/ 0x8B, /*L 1/8 bank DTO */
/*0x8C*/ 0x8C, /*R 1/8 bank DTO */
/*0x8D*/ 0x8D, /*Diag flat */
/*0x8E*/ 0x8E, /*Diag 25 /\ */
/*0x8F*/ 0x8F, /*Diag 60 /\ */
/*0x90*/ 0x90, /*Diag flat to 25 /\ */
/*0x91*/ 0x91, /*Diag 25 /\ to 60 /\ */
/*0x92*/ 0x92, /*Diag 60 /\ to 25 /\ */
/*0x93*/ 0x93, /*Diag 25 /\ to flat */
/*0x94*/ 0x94, /*Diag 25 \/ */
/*0x95*/ 0x95, /*Diag60 \/ */
/*0x96*/ 0x96, /*Diag flat to 25 \/ */
/*0x97*/ 0x97, /*Diag 25 \/ to 60 \/ */
/*0x98*/ 0x98, /*Diag 60 \/ to 25 \/ */
/*0x99*/ 0x99, /*Diag 25 \/ to flat */
/*0x9A*/ 0x9A, /*Diag flat to 60 /\ */
/*0x9B*/ 0x9B, /*Diag 60 /\ to flat */
/*0x9C*/ 0x9C, /*Diag flat to 60 \/ */
/*0x9D*/ 0x9D, /*Diag 60 \/ to flat */
/*0x9E*/ 0x9E, /*Diag flat to L bank */
/*0x9F*/ 0x9F, /*Diag flat to R bank */
/*0xA0*/ 0xA0, /*Diag L bank to flat */
/*0xA1*/ 0xA1, /*Diag R bank to flat */
/*0xA2*/ 0xA2, /*Diag L bank to 25 /\ */
/*0xA3*/ 0xA3, /*Diag R bank to 25 /\ */
/*0xA4*/ 0xA4, /*Diag 25 /\ to L bank */
/*0xA5*/ 0xA5, /*Diag 25 /\ to R bank */
/*0xA6*/ 0xA6, /*Diag L bank to 25 \/ */
/*0xA7*/ 0xA7, /*Diag R bank to 25 \/ */
/*0xA8*/ 0xA8, /*Diag 25 \/ to L bank */
/*0xA9*/ 0xA9, /*Diag 25 \/ to R bank */
/*0xAA*/ 0xAA, /*Diag L bank */
/*0xAB*/ 0xAB, /*Diag R bank */
/*0xAC*/ 0xAC, /*Log flume reverser*/
/*0xAD*/ 0xAD, /*spinning tunnel */
/*0xAE*/ 0xAE, /*L barrel roll /\ to \/ */
/*0xAF*/ 0xAF, /*R barrel roll /\ to \/ */
/*0xB0*/ 0xB0, /*L barrel roll \/ to /\ */
/*0xB1*/ 0xB1, /*R barrel roll \/ to /\ */
/*0xB2*/ 0xB2, /*L bank to L ¼ D3 25 /\ */
/*0xB3*/ 0xB3, /*R bank to R ¼ D3 25 /\*/
/*0xB4*/ 0xB4, /*L ¼ D3 25 \/ to L bank*/
/*0xB5*/ 0xB5, /*R ¼ D3 25 \/ to R bank*/
/*0xB6*/ 0xB6, /*powered lift */
/*0xB7*/ 0xB7, /*L large ½ loop /\ */
/*0xB8*/ 0xB8, /*R large ½ loop /\ */
/*0xB9*/ 0xB9, /*R large ½ loop \/ */
/*0xBA*/ 0xBA, /*L large ½ loop \/ */
/*0xBB*/ 0xBB, /*L flyer twist /\ to \/ */
/*0xBC*/ 0xBC, /*R flyer twist /\ to \/ */
/*0xBD*/ 0xBD, /*L flyer twist \/ to /\ */
/*0xBE*/ 0xBE, /*R flyer twist \/ to /\ */
/*0xBF*/ 0xBF, /*flyer ½ loop /\ */
/*0xC0*/ 0xC0, /*flyer ½ loop \/ */
/*0xC1*/ 0xC1, /*L fly corkscrw /\ to \/ */
/*0xC2*/ 0xC2, /*R fly corkscrw /\ to \/ */
/*0xC3*/ 0xC3, /*L fly corkscrw \/ to /\ */
/*0xC4*/ 0xC4, /*R fly corkscrew \/ to /\ */
/*0xC5*/ 0xC5, /*heartline transfer up */
/*0xC6*/ 0xC6, /*heartline transfer down */
/*0xC7*/ 0xC7, /*L heartline roll */
/*0xC8*/ 0xC8, /*R heartline roll */
/*0xC9*/ 0xC9, /*mini golf hole A */
/*0xCA*/ 0xCA, /*mini golf hole B */
/*0xCB*/ 0xCB, /*mini golf hole C */
/*0xCC*/ 0xCC, /*mini golf hole D */
/*0xCD*/ 0xFF, /*RCT2: mini golf hole E*/
/*0xCE*/ 0xFF, /*RCT2: inverted flat to 90 \/ quarter loop (multidim)*/
/*0xCF*/ 0xFF, /*RCT2: Quarter loop 90 /\ to invert*/
/*0xD0*/ 0xFF, /*RCT2: Quarter loop invert to 90 \/*/
/*0xD1*/ 0xFF, /*RCT2: L curved lift hill*/
/*0xD2*/ 0xFF, /*RCT2: R curved lift hill*/
/*0xD3*/ 0xD3, /*L reverser */
/*0xD4*/ 0xD4, /*R reverser */
/*0xD5*/ 0xD5, /*Air Thrust top cap*/
/*0xD6*/ 0xD6, /*Air Thrust Vertical down*/
/*0xD7*/ 0xD7, /*Air Thrust vertical down to level */
/*0xD8*/ 0xFF, /*Block Brakes*/
/*0xD9*/ 0xFF, /*L ¼ D3 25 /\ banked*/
/*0xDA*/ 0xFF, /*R ¼ D3 25 /\ banked*/
/*0xDB*/ 0xFF, /*L ¼ D3 25 \/ banked*/
/*0xDC*/ 0xFF, /*R ¼ D3 25 \/ banked*/
/*0xDD*/ 0xFF, /*L ¼ D5 25 /\ banked */
/*0xDE*/ 0xFF, /*R ¼ D5 25 /\ banked*/
/*0xDF*/ 0xFF, /*L ¼ D5 25 \/ banked*/
/*0xE0*/ 0xFF, /*R ¼ D5 25 \/ banked*/
/*0xE1*/ 0xFF, /*25 /\ to L bank 25 /\*/
/*0xE2*/ 0xFF, /*25 /\ to R bank 25 /\*/
/*0xE3*/ 0xFF, /*L bank 25 /\ to 25 /\*/
/*0xE4*/ 0xFF, /*R bank 25 /\ to 25 /\*/
/*0xE5*/ 0xFF, /*25 \/ to L bank 25 \/*/
/*0xE6*/ 0xFF, /*25 \/ to R bank 25 \/*/
/*0xE7*/ 0xFF, /*L bank 25 \/ to 25 \/*/
/*0xE8*/ 0xFF, /*R bank 25 \/ to 25 \/*/
/*0xE9*/ 0xFF, /*L bank to L bank 25 /\*/
/*0xEA*/ 0xFF, /*R bank to R bank 25 /\*/
/*0xEB*/ 0xFF, /*L bank 25 /\ to L bank flat */
/*0xEC*/ 0xFF, /*R bank 25 /\ to R bank flat */
/*0xED*/ 0xFF, /*L bank to L bank 25 \/*/
/*0xEE*/ 0xFF, /*R bank to R bank 25 \/*/
/*0xEF*/ 0xFF, /*L bank 25 \/ to L bank flat*/
/*0xF0*/ 0xFF, /*R bank 25 \/ to R bank flat*/
/*0xF1*/ 0xFF, /*flat to L bank 25 /\*/
/*0xF2*/ 0xFF, /*flat to R bank 25 /\*/
/*0xF3*/ 0xFF, /*L bank 25 /\ to flat*/
/*0xF4*/ 0xFF, /*R bank 25 /\ to flat*/
/*0xF5*/ 0xFF, /*flat to L bank 25 \/*/
/*0xF6*/ 0xFF, /*flat to R bank 25 \/*/
/*0xF7*/ 0xFF, /*L bank 25 \/ to flat*/
/*0xF8*/ 0xFF, /*R bank 25 \/ to flat*/
/*0xF9*/ 0xFF, /*L ¼ D1 90 /\*/
/*0xFA*/ 0xFF, /*R ¼ D1 90 /\*/
/*0xFB*/ 0xFF, /*L ¼ D1 90 \/*/
/*0xFC*/ 0xFF, /*R ¼ D1 90 \/*/
/*0xFD*/ 0xFF, /*90 /\ to inverted flat quarter loop (multidim)*/
/*0xFE*/ 0xFF, /*flat to 90 \/ quarter loop (multidim)*/
/*0xFF*/ 0xFF, /*End of track*/
};

#endif //TRACKELEMENTCONVERT_H