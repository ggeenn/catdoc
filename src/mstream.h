#ifndef _MSTREAM_H
#define _MSTREAM_H

#define STREAM_FETCH_IMPL(X) buf += X;
#define STREAM_FETCH(PTR, X) if (buf + X > bufEnd) return 0;unsigned char* PTR = buf;STREAM_FETCH_IMPL(X)
#define STREAM_FETCH_VAR(VAR, TYPE, FUNC) if (buf + sizeof(TYPE) > bufEnd) return 0;TYPE VAR = FUNC(buf, 0);STREAM_FETCH_IMPL(sizeof(TYPE));VAR
#define STREAM_PUT_BACK(X) buf -= X;

#define FSTREAM_FETCH_VAR(VAR, TYPE, FUNC) read_type_block(buf, sizeof(TYPE), input); TYPE VAR = FUNC(buf, 0);

#endif