/*****************************************************************/
/* Substitution maps to replace some unicode characters with     */
/* multicharacter sequences                                      */
/*                                                               */
/* This file is part of catdoc project                           */
/* (c) Victor Wagner 1998-2003, (c) Alex Ott 2003	             */
/*****************************************************************/
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "catdoc.h"
SUBSTMAP spec_chars, replacements;
char *map_path=CHARSETPATH;
void map_insert(SUBSTMAP map, int uc, const char *s) ;
int longest_sequence=6;/* six is longest character sequence which can be
						  generated by catdoc internally*/

/******************************************************************/
/* checks for terminator of character sequence. If stop is something
 * like quote - check for same char. If it is \n, check for any space
 ********************************************************************/ 
//int isstop(char  c, char stop) {
//	if (stop=='\n') {
//		return isspace(c);
//	} else {
//		return c==stop;
//	}
//}
/************************************************************************/
/* Reads substitution map file.                                         */
/************************************************************************/
//SUBSTMAP read_substmap(char* filename) {
//	FILE *f;
//	SUBSTMAP map=calloc(sizeof(char **),256);
//	char *path, line[1024], *p, *q;
//	char s[256];
//	char stopchar;
//	int escaped, lineno=0, i;
//    int32_t uc;
//	path=find_file(filename,/*add_exe_path*/(map_path));
//	if (!path) {
//		free(map);
//		return(NULL);
//	}   
//	if (!map) {
//		fprintf(stderr,"Insufficient memory\n");
//		exit(1);
//	}
//	f=fopen(path,"rb");
//	if (!f) {
//		perror(path);
//		free(map);
//		return NULL;
//	}
//	if (input_buffer)
//		setvbuf(f,input_buffer,_IOFBF,FILE_BUFFER);
//
//	while (!feof(f)) {
//		if (!fgets(line,1024,f)) continue;
//		lineno++;
//		/* parse line */
//
//		/* skip leading space */
//		for(p=line;*p && isspace(*p);p++);
//		/* if #, it is comment */
//		if (!*p ||
//#ifdef  __MSDOS__
//				*p==0x1A || /* DOS have strange habit of using ^Z as eof */
//#endif
//				*p=='#') continue;
//		/* read hexadecimal code */
//		uc = strtol(p,&p,16);
//		if (!isspace(*p)|| uc<0 || uc>0xfffd) {
//			fprintf(stderr,"Error parsing %s(%d)\n",path,lineno);
//			continue;
//		}
//		/* skip space between  code and sequence */
//		for(;*p && isspace(*p);p++);
//		if (!*p) continue;
//		switch (*p) {
//			case '\'':
//			case '"':
//				stopchar=*p;
//				break;
//			case '(':
//				stopchar=')';
//				break;
//			case '[':
//				stopchar=']';
//				break;
//			case '{':
//				stopchar='}';
//				break;
//			default:
//				p--;
//				stopchar='\n';
//		}
//		p++;
//		q=p;
//		escaped=0;
//		while (*q && (!isstop(*q,stopchar) || escaped)) {
//			if (escaped) {
//				escaped=0;
//			} else {
//				escaped= (*q=='\\');
//			}
//			q++;
//		}
//		if (*q!=stopchar && !(isspace(*q) && stopchar=='\n')) {
//			fprintf(stderr,"Error parsing %s(%d): unterminated sequence\n",
//					path,lineno);
//			continue;
//		}
//		/* HERE SHOULD BE BACKSLASH ESCAPE PROCESSING !!!*/
//		*q=0;
//		for (q=s,i=0;*p && i<256;q++,i++) {
//			if (*p!='\\') {
//				*q=*p++;
//			} else {
//				switch (*(++p)) {
//					case 'n': *q='\n'; break;
//					case 'r': *q='\r'; break;
//					case 't': *q='\t'; break;
//					case 'b': *q='\b'; break;
//							  case '\"': *q='\"'; break;
//					case '\'': *q='\''; break;
//					case '0': *q=strtol(p,&p,8); p--; break;
//					case '\\':
//					default:
//							  *q=*p;
//				}
//				p++;
//			}
//		}
//		*q=0;
//		if (i>longest_sequence)
//			longest_sequence=i;
//		map_insert(map,uc,s);
//	}
//	fclose(f);
//	free(path);
//	return map;
//}

/*************************************************************************/
/* searches for string in the substituton map. Returns NULL if not found */
/*************************************************************************/
char * map_subst ( SUBSTMAP map, int uc) {
	//char **p=map[(unsigned)uc >>8];
	//if (!p) return NULL;
	//return p[uc & 0xff];
	static unsigned char buf[2] = "A";
	buf[0] = uc & 0xff;
	return (char*)buf;
}

/*************************************************************************/
/*  inserts string + unicode code into map                               */
/*************************************************************************/
//void map_insert(SUBSTMAP map, int uc, const char *s) {
//	SUBSTMAP p=map+((unsigned)uc>>8);
//
//	if (!*p) {
//		*p= calloc(sizeof(char*),256);
//		if (!*p) { 
//			fprintf(stderr,"Insufficient memory\n");
//			exit(1);
//		}
//	}
//	(*p)[uc & 0xff] = strdup(s);
//}
