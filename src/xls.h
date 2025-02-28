/*****************************************************************/
/* Definition specific for Excel file handling                   */
/*                                                               */
/* This file is part of catdoc project                           */
/* (c) Victor Wagner 2003, (c) Alex Ott 2003	                 */
/*****************************************************************/

#ifndef XLS_H
#define XLS_H

#include <stdio.h>
#include <math.h>
/* types of quoting */
#define QUOTE_NEVER 0
#define QUOTE_SPACES_ONLY 1
#define QUOTE_ALL_STRINGS 2
#define QUOTE_EVERYTHING 3

struct rowdescr {
	int last, end;
	unsigned char **cells;
};	
/* structure to hold parsed table */
extern struct rowdescr *rowptr;
extern int startrow;
/* xls2csv-specific configuration */
extern char cell_separator;
extern int quote_mode;
void print_sheet(void);
void free_sheet(void);
void catdoc_output_chars(unsigned char *buffer, size_t bufferSz);
void format_double(unsigned char *rec, int offset, int format_code, char* buff, int buff_sz);
//char *format_int(int value,int format_code);
void format_rk(unsigned char *rec,short int format_code, char* buff, int buff_sz);
char *gettypename(long rectype);
//void parse_sst(unsigned char *sstbuf,int bufsize);
int process_xl_item (int rectype, int prev_rectype, int reclen, unsigned char *rec, int* unparsedSz);
//unsigned char **allocate(int row,int col);
//unsigned char *copy_unicode_string(unsigned char **src);
char convert8to8(char *src,int count);
char *convert16to8(char *src,int count);
int do_table(FILE *input);
char *mark_string(char *instr);

/* ---- added by Igor ---- */
void SetFormatIdxUsed(int format_code);
/* -- end added by Igor -- */


#ifdef __TURBOC__
#define rint(x) floor((x+0.5))
#endif
#endif
