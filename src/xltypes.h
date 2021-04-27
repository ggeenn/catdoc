/*
  Copyright 1998 David Rysdam
  Copyright 1998-2003 Victor Wagner
  Copyright 2003 Alex Ott
  This file is released under the GPL.  Details can be
  found in the file COPYING accompanying this distribution.
*/

#define MAX_MS_RECSIZE 18000

#define MS_UNIX_DATE_DIFF (70*365.2422+1)

#define DATE_FORMAT              14

#define CATDOC_XL_TYPES_FOREACH(F)                                                                    \
F( MS1904  		 , 0x22                             ) \
F( ADDIN 		         , 0x87                     ) \
F( ADDMENU 		 , 0xC2                             ) \
F( ARRAY 		         , 0x221                    ) \
F( AUTOFILTER 		 , 0x9E                         ) \
F( AUTOFILTERINFO 		 , 0x9D                     ) \
F( BACKUP 		         , 0x40                     ) \
F( BLANK 		         , 0x201                    ) \
F( BOF 		         , 0x809                        ) \
F( BOOKBOOL 		 , 0xDA                         ) \
F( BOOLERR 		 , 0x205                            ) \
F( BOTTOMMARGIN 		 , 0x29                     ) \
F( BOUNDSHEET 		 , 0x85                         ) \
F( CALCCOUNT 		 , 0x0C                         ) \
F( CALCMODE 		 , 0x0D                         ) \
F( CODEPAGE 		 , 0x42                         ) \
F( COLINFO 		 , 0x7D                             ) \
F( CONTINUE 		 , 0x3C                         ) \
F( COORDLIST 		 , 0xA9                         ) \
F( COUNTRY 		 , 0x8C                             ) \
F( CRN 		         , 0x5A                         ) \
F( DBCELL 		         , 0xD7                     ) \
F( DCON 		         , 0x50                     ) \
F( DCONNAME 		 , 0x52                         ) \
F( DCONREF 		 , 0x51                             ) \
F( DEFAULTROWHEIGHT 	 , 0x225                    ) \
F( DEFCOLWIDTH 		 , 0x55                         ) \
F( DELMENU 		 , 0xC3                             ) \
F( DELTA 		         , 0x10                     ) \
F( DIMENSIONS 		 , 0x200                        ) \
F( DOCROUTE 		 , 0xB8                         ) \
F( EDG 		         , 0x88                         ) \
F( MSEOF 		         , 0x0A                     ) \
F( EXTERNCOUNT 		 , 0x16                         ) \
F( EXTERNNAME 		 , 0x223                        ) \
F( EXTERNSHEET 		 , 0x17                         ) \
F( FILEPASS 		 , 0x2F                         ) \
F( FILESHARING 		 , 0x5B                         ) \
F( FILESHARING2 		 , 0x1A5                    ) \
F( FILTERMODE 		 , 0x9B                         ) \
F( FNGROUPCOUNT 		 , 0x9C                     ) \
F( FNGROUPNAME 		 , 0x9A                         ) \
F( FONT 		         , 0x231                    ) \
F( FONT2 		         , 0x31                     ) \
F( FOOTER 		         , 0x15                     ) \
F( FORMAT 		         , 0x41E                    ) \
F( FORMULA_RELATED		 , 0x4BC                    ) \
F( DOUBLE_STREAM_FILE	 , 0x161                    ) \
F( FORMULA 		 , 0x06                             ) \
F( GCW 		         , 0xAB                         ) \
F( GRIDSET 		 , 0x82                             ) \
F( PROT4REVPASS             , 0x1BC                 ) \
F( GUTS 		         , 0x80                     ) \
F( HCENTER 		 , 0x83                             ) \
F( HEADER 		         , 0x14                     ) \
F( HIDEOBJ 		 , 0x8D                             ) \
F( HORIZONTALPAGEBREAKS, 0x1B                       ) \
F( IMDATA 		         , 0x7F                     ) \
F( INDEX 		         , 0x20B                    ) \
F( INTERFACEEND 		 , 0xE2                     ) \
F( INTERFACEHDR 		 , 0xE1                     ) \
F( ITERATION 		 , 0x11                         ) \
F( LABEL 		         , 0x204                    ) \
F( LEFTMARGIN 		 , 0x26                         ) \
F( LHNGRAPH 		 , 0x95                         ) \
F( LHRECORD 		 , 0x94                         ) \
F( LPR 		         , 0x98                         ) \
F( MMS 		         , 0xC1                         ) \
F( MULBLANK 		 , 0xBE                         ) \
F( MULRK 		         , 0xBD                     ) \
F( NAME 		         , 0x218                    ) \
F( NOTE 		         , 0x1C                     ) \
F( NUMBER 		         , 0x203                    ) \
F( OBJ 		         , 0x5D                         ) \
F( OBJPROTECT 		 , 0x63                         ) \
F( OBPROJ 		         , 0xD3                     ) \
F( OLESIZE 		 , 0xDE                             ) \
F( PALETTE 		 , 0x92                             ) \
F( PANE 		         , 0x41                     ) \
F( PASSWORD 		 , 0x13                         ) \
F( PLS 		         , 0x4D                         ) \
F( PRECISION 		 , 0x0E                         ) \
F( PRINTGRIDLINES 		 , 0x2B                     ) \
F( PRINTHEADERS 		 , 0x2A                     ) \
F( PROTECT 		 , 0x12                             ) \
F( PUB 		         , 0x89                         ) \
F( RECIPNAME 		 , 0xB9                         ) \
F( REFMODE 		 , 0x0F                             ) \
F( RIGHTMARGIN 		 , 0x27                         ) \
F( RK 		         , 0x27E                        ) \
F( ROW 		         , 0x208                        ) \
F( RSTRING 		 , 0xD6                             ) \
F( SAVERECALC 		 , 0x5F                         ) \
F( SCENARIO 		 , 0xAF                         ) \
F( SCENMAN 		 , 0xAE                             ) \
F( SCENPROTECT 		 , 0xDD                         ) \
F( SCL 		         , 0xA0                         ) \
F( SELECTION 		 , 0x1D                         ) \
F( SETUP 		         , 0xA1                     ) \
F( SHRFMLA 		 , 0xBC                             ) \
F( SORT 		         , 0x90                     ) \
F( SOUND 		         , 0x96                     ) \
F( STANDARDWIDTH 		 , 0x99                     ) \
F( STRING 		         , 0x207                    ) \
F( STYLE 		         , 0x293                    ) \
F( SUB 		         , 0x91                         ) \
F( SXDI 		         , 0xC5                     ) \
F( SXEXT 		         , 0xDC                     ) \
F( SXIDSTM 		 , 0xD5                             ) \
F( SXIVD 		         , 0xB4                     ) \
F( SXLI 		         , 0xB5                     ) \
F( SXPI 		         , 0xB6                     ) \
F( SXSTRING 		 , 0xCD                         ) \
F( SXTBL 		         , 0xD0                     ) \
F( SXTBPG 		         , 0xD2                     ) \
F( SXTBRGIITM 		 , 0xD1                         ) \
F( SXVD 		         , 0xB1                     ) \
F( SXVI 		         , 0xB2                     ) \
F( SXVIEW 		         , 0xB0                     ) \
F( SXVS 		         , 0xE3                     ) \
F( TABID 		         , 0x13D                    ) \
F( TABIDCONF 		 , 0xEA                         ) \
F( TABLE 		         , 0x236                    ) \
F( TEMPLATE 		 , 0x60                         ) \
F( TOPMARGIN 		 , 0x28                         ) \
F( UDDESC 		         , 0xDF                     ) \
F( UNCALCED 		 , 0x5E                         ) \
F( VCENTER 		 , 0x84                             ) \
F( VERTICALPAGEBREAKS 	 , 0x1A                     ) \
F( WINDOW1 		 , 0x3D                             ) \
F( WINDOW2 		 , 0x23E                            ) \
F( WINDOWPROTECT 		 , 0x19                     ) \
F( WRITEACCESS 		 , 0x5C                         ) \
F( WRITEPROT 		 , 0x86                         ) \
F( WSBOOL 		         , 0x81                     ) \
F( XCT 		         , 0x59                         ) \
F( XF 		         , 0xE0                         ) \
F( SST			 , 0xFC                             ) \
F( CONSTANT_STRING	         , 0xFD                 ) \
F( REFRESHALL		 , 0x1B7                        ) \
F( USESELFS		 , 0x160                            ) \
F( EXTSST		         , 0xFF                     ) \
F( INTEGER_CELL 	 , 0x202                        )

#define CATDOC_XL_TYPES_ENUM(NAME, NUM) NAME = NUM,

enum CatDocXlTypes
{
    CATDOC_XL_TYPES_FOREACH(CATDOC_XL_TYPES_ENUM)
};

#define CATDOC_XL_TYPES_STR_CASE(NAME, NUM) case NUM: return #NAME;
inline char* CatDocXlTypesToStr(int type)
{
    switch (type)
    {
        CATDOC_XL_TYPES_FOREACH(CATDOC_XL_TYPES_STR_CASE)
    }
    static char buf[50];
    sprintf(buf, "0x%x", type);
    return buf;
}