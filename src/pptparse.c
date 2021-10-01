/**
 * @file   pptparse.c
 * @author Alex Ott <alexott@gmail.com>
 * @date   23 ‰≈À 2004
 * Version: $Id: pptparse.c,v 1.2 2006-10-17 19:11:29 vitus Exp $
 * Copyright: Alex Ott
 * 
 * @brief  .ppt parsing routines
 * 
 * 
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "ppt.h"
#include "catdoc.h"
#include "ppttypes.h"
#include "mstream.h"

void catdoc_output_chars(unsigned char* buffer, size_t bufferSz);
int catdoc_raise_error(const char* reason);

char *slide_separator = "\f"; 

static int process_item (int rectype, long reclen, FILE* input);

#if !defined(min)
#define min(x,y) ((x) < (y) ? (x) : (y))
#endif

static void start_text_out(void);

/** 
 * 
 * 
 * @param input 
 * @param filename 
 */

//enum {START_FILE,START_SLIDE,TEXTOUT,END_FILE} slide_state ;

//static void start_text_out(void) {
//	if (slide_state == START_SLIDE) {
//		catdoc_output_chars(" ", 1);// fputs(slide_separator, stdout);
//	}
//	slide_state = TEXTOUT;
//}	
int do_ppt(FILE *input) {
	int itemsread=1;
	int rectype;
	long reclen;
	int retcode = 0;
	unsigned char recbuf[8];
	//slide_state = START_FILE;
	//int skipState = EmptySkipState;
	while(itemsread) {
		itemsread = catdoc_read(recbuf, 1, 8, input);
/* 		fprintf(stderr,"itemsread=%d: ",itemsread); */
/* 		for(i=0; i<8; i++) */
/* 			fprintf(stderr,"%02x ",recbuf[i]); */
/* 		fprintf(stderr,"\n"); */
		
		if (catdoc_eof(input)) {
			return process_item(DOCUMENT_END,0,input);
		}
		if(itemsread < 8)
			break;
		rectype=getshort(recbuf,2);
		reclen=getulong(recbuf,4);
		if (reclen < 0) {
			return catdoc_raise_error("PPT wrong format, block size is negative");
		}	
		retcode = process_item(rectype, reclen, input);
		if (retcode != 0)
		{
			return retcode;
		}
	}
	return 0;
}

void printify(unsigned char* buf, int len)
{
	for (int i = 0; i < len; ++i)
		if (!isprint(buf[i]))
			buf[i] = ' ';
}
int  read_type_block(unsigned char* buf, size_t len, FILE* input)
{
	if (len > MAX_MS_RECSIZE)
		return catdoc_raise_error("Reclen isn't suite MAX_MS_RECSIZE buffer");
	size_t res = catdoc_read(buf, 1, len, input);
	if (res != len)
		return catdoc_raise_error("Can't read");
	return 0;
}
unsigned char* extract_client_textbox(unsigned char* buf, unsigned char* bufEnd)
{
	STREAM_FETCH_VAR_ERR(u0, uint32_t, getulong, 0);
	STREAM_FETCH_VAR_ERR(u4, uint32_t, getulong, 0);
	STREAM_FETCH_VAR_ERR(type, uint32_t, getulong, 0);
	//uint32_t type = getulong(buf, 8);
	STREAM_FETCH_IMPL(2);
	STREAM_FETCH_VAR_ERR(subtype, uint16_t, getshort, 0);
	//uint16_t subtype = getshort(buf, 14);
	STREAM_FETCH_VAR_ERR(len, uint32_t, getulong, 0);
	//uint32_t len = getulong(buf, 16);
	STREAM_FETCH_ERR(str, len, 0);
	//unsigned char* str = buf + 20;
	//printify(str, len);
	//printf("FRAME_D [0x%x - 0x%x] %d bytes => [%s]\n", type, subtype, reclen, str);
	if (PPDRAWING_FRAME_D_TYPE_STR == type || 4 == type)
	{
		switch (subtype)
		{
		case PPDRAWING_FRAME_D_SUBTYPE_CSTR:
			catdoc_output_chars(str, len);
			break;
		case PPDRAWING_FRAME_D_SUBTYPE_WSTR:
			catdoc_output_wchars(str, len / 2);
			break;
		default:
			break;
		}
	}
	return NULL;
}

static int process_item (int rectype, long reclen, FILE* input/*, int* skipState*/) {
	int i=0;
	int retcode = 0;
	unsigned char buf[MAX_MS_RECSIZE];

	//long offset = catdoc_tell(input);
	//fprintf(stdout,"[x%04X]"
	//	           " : Rectype [%s] reclen=x%04X\n",offset,
	//	CatDocPptTypesToStr(rectype), reclen);

	//switch (rectype)
	//{
	//case TEXT_BYTES_ATOM:
	//case TEXT_CHARS_ATOM:
	//case CSTRING:
	//case TEXT_HEADER_ATOM:
	//case DFF_msofbtClientTextbox:
	//	break;
	//default:
	//	*skipState = EmptySkipState;
	//	break;
	//}

	switch(rectype) {
	case DOCUMENT_END:
/* 		fprintf(stderr,"End of document, ended at %ld\n",catdoc_tell(input)); */
		catdoc_seek(input, reclen, SEEK_CUR);
		//if (slide_state == TEXTOUT) {
		//	catdoc_output_chars(" ", 1); //fputs(slide_separator,stdout);
		//	slide_state = END_FILE;
		//}	
		break;

	case DOCUMENT:
/* 		fprintf(stderr,"Start of document, reclen=%ld, started at %ld\n", reclen, */
/* 						catdoc_tell(input)); */
		break;

	case DOCUMENT_ATOM:
/* 		fprintf(stderr,"DocumentAtom, reclen=%ld\n", reclen); */
		catdoc_seek(input, reclen, SEEK_CUR);
		break;

	case SLIDE:
/* 		fprintf(stderr,"Slide, reclen=%ld\n", reclen); */
		break;

	case SLIDE_ATOM:
/* 		fprintf(stderr,"SlideAtom, reclen=%ld\n", reclen); */
		catdoc_seek(input, reclen, SEEK_CUR);
		break;
		
	case SLIDE_BASE:
/* 		fprintf(stderr,"SlideBase, reclen=%ld\n", reclen); */
		break;

	case SLIDE_BASE_ATOM:
/* 		fprintf(stderr,"SlideBaseAtom, reclen=%ld\n", reclen); */
		catdoc_seek(input, reclen, SEEK_CUR);
		break;
		
	case NOTES:
/* 		fprintf(stderr,"Notes, reclen=%ld\n", reclen); */
		break;

	case NOTES_ATOM:
/* 		fprintf(stderr,"NotesAtom, reclen=%ld\n", reclen); */
		catdoc_seek(input, reclen, SEEK_CUR);
		break;
		
	case HEADERS_FOOTERS:
/* 		fprintf(stderr,"HeadersFooters, reclen=%ld\n", reclen); */
		break;

	case HEADERS_FOOTERS_ATOM:
/* 		fprintf(stderr,"HeadersFootersAtom, reclen=%ld\n", reclen); */
		catdoc_seek(input, reclen, SEEK_CUR);
		break;
		
	case MAIN_MASTER:
/* 		fprintf(stderr,"MainMaster, reclen=%ld\n", reclen); */
		break;
		
	case TEXT_BYTES_ATOM: {
/* 			fprintf(stderr,"TextBytes, reclen=%ld\n", reclen); */
			//start_text_out();
			retcode = read_type_block(buf, reclen, input);
			if (retcode)
			{
				return retcode;
			}
			//if (*skipState != NeedSkipState)
			catdoc_output_chars(buf, reclen);
		}
		break;
		
	case TEXT_CHARS_ATOM: 
	case CSTRING: {
		retcode = read_type_block(buf, reclen, input);
		if (retcode)
		{
			return retcode;
		}
		//if(*skipState != NeedSkipState)
		catdoc_output_wchars(buf, reclen/2);
	}
		break;
		
	case USER_EDIT_ATOM:
/* 		fprintf(stderr,"UserEditAtom, reclen=%ld\n", reclen); */
		catdoc_seek(input, reclen, SEEK_CUR);
		break;

	case COLOR_SCHEME_ATOM:
/* 		fprintf(stderr,"ColorSchemeAtom, reclen=%ld\n", reclen); */
		catdoc_seek(input, reclen, SEEK_CUR);
		break;

	case PPDRAWING:
/* 		fprintf(stderr,"PPDrawing, reclen=%ld\n", reclen); */
		//catdoc_seek(input, reclen, SEEK_CUR);
		break;

	case ENVIRONMENT:
/* 		fprintf(stderr,"Environment, reclen=%ld\n", reclen); */
		catdoc_seek(input, reclen, SEEK_CUR);
		break;

	case SSDOC_INFO_ATOM:
/* 		fprintf(stderr,"SSDocInfoAtom, reclen=%ld\n", reclen); */
		catdoc_seek(input, reclen, SEEK_CUR);
		break;

	case SSSLIDE_INFO_ATOM:
/* 		fprintf(stderr,"SSSlideInfoAtom, reclen=%ld\n", reclen); */
		catdoc_seek(input, reclen, SEEK_CUR);
		break;

	case PROG_TAGS:
/* 		fprintf(stderr,"ProgTags, reclen=%ld\n", reclen); */
		catdoc_seek(input, reclen, SEEK_CUR);
		break;

	case PROG_STRING_TAG:
/* 		fprintf(stderr,"ProgStringTag, reclen=%ld\n", reclen); */
		catdoc_seek(input, reclen, SEEK_CUR);
		break;

	case PROG_BINARY_TAG:
/* 		fprintf(stderr,"ProgBinaryTag, reclen=%ld\n", reclen); */
		catdoc_seek(input, reclen, SEEK_CUR);
		break;

	case LIST:
/* 		fprintf(stderr,"List, reclen=%ld\n", reclen); */
		break;

	case SLIDE_LIST_WITH_TEXT:
/* 		fprintf(stderr,"SlideListWithText, reclen=%ld\n", reclen); */
/*  		fputs("---------------------------------------\n",stderr); */
		break;

	case PERSIST_PTR_INCREMENTAL_BLOCK:
/* 		fprintf(stderr,"PersistPtrIncrementalBlock, reclen=%ld\n", reclen); */
		catdoc_seek(input, reclen, SEEK_CUR);
		break;

	case EX_OLE_OBJ_STG:
/* 		fprintf(stderr,"ExOleObjStg, reclen=%ld\n", reclen); */
		catdoc_seek(input, reclen, SEEK_CUR);
		break;

	case PPDRAWING_GROUP:
/* 		fprintf(stderr,"PpdrawingGroup, reclen=%ld\n", reclen); */
		catdoc_seek(input, reclen, SEEK_CUR);
		break;

	case EX_OBJ_LIST:
/* 		fprintf(stderr,"ExObjList, reclen=%ld\n", reclen); */
		catdoc_seek(input, reclen, SEEK_CUR);
		break;

	case TX_MASTER_STYLE_ATOM:
/* 		fprintf(stderr,"TxMasterStyleAtom, reclen=%ld\n", reclen); */
		catdoc_seek(input, reclen, SEEK_CUR);
		break;

	case HANDOUT:
/* 		fprintf(stderr,"Handout, reclen=%ld\n", reclen); */
		catdoc_seek(input, reclen, SEEK_CUR);
		break;

	case SLIDE_PERSIST_ATOM:
		//if (slide_state != START_FILE) {
		//	slide_state = START_SLIDE;
		//}	
		catdoc_seek(input, reclen, SEEK_CUR);
		break;

	case TEXT_HEADER_ATOM: {
/* 		fprintf(stderr,"TextHeaderAtom, reclen=%ld\n", reclen); */
		catdoc_seek(input, reclen, SEEK_CUR);
		//read_type_block(buf, reclen, input);
		//uint32_t val = getulong(buf, 0);
		//if (*skipState == TextBoxSkipState && val != 4)
		//	*skipState = NeedSkipState;
		//fprintf(stderr, "TextHeaderAtom, value=%ld\n", val);
	}
	break;

	case TEXT_SPEC_INFO:
/* 		fprintf(stderr,"TextSpecInfo, reclen=%ld\n", reclen); */
		catdoc_seek(input, reclen, SEEK_CUR);
		break;

	case STYLE_TEXT_PROP_ATOM:
/* 		fprintf(stderr,"StyleTextPropAtom, reclen=%ld\n", reclen); */
		catdoc_seek(input, reclen, SEEK_CUR);
		break;

		/*	case :
		fprintf(stderr,", reclen=%ld\n", reclen);
		catdoc_seek(input, reclen, SEEK_CUR);
		break;*/

		/*	case :
		fprintf(stderr,", reclen=%ld\n", reclen);
		catdoc_seek(input, reclen, SEEK_CUR);
		break;*/

	case PPDRAWING_FRAME_2:
		break;
	case PPDRAWING_FRAME_3:
		break;
	case PPDRAWING_FRAME_4:
		break;
	case DFF_msofbtClientTextbox: {
		//*skipState = TextBoxSkipState;
	}
		break;

	default:
/* 		fprintf(stderr,"Default action for rectype=%d reclen=%ld\n", */
/* 						rectype, reclen); */
		catdoc_seek(input, reclen, SEEK_CUR);

	}
	return 0;
}
