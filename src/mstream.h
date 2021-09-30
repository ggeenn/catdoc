#ifndef _MSTREAM_H
#define _MSTREAM_H

#define STREAM_SUCCESS      0
#define STREAM_FETCH_ERROR -1
#define STREAM_FATAL_ERROR -2

#define STREAM_FETCH_IMPL(X) buf += X;
#define STREAM_FETCH_ERR(PTR, X, ERR) if (buf + X > bufEnd) return ERR;unsigned char* PTR = buf;STREAM_FETCH_IMPL(X)
#define STREAM_FETCH_VAR_ERR(VAR, TYPE, FUNC, ERR) if (buf + sizeof(TYPE) > bufEnd) return ERR;TYPE VAR = FUNC(buf, 0);STREAM_FETCH_IMPL(sizeof(TYPE));VAR
#define STREAM_PUT_BACK(X) buf -= X;

#define STREAM_FETCH(PTR, X) STREAM_FETCH_ERR(PTR, X, STREAM_FETCH_ERROR)
#define STREAM_FETCH_VAR(VAR, TYPE, FUNC) STREAM_FETCH_VAR_ERR(VAR, TYPE, FUNC, STREAM_FETCH_ERROR)

#define FSTREAM_FETCH_VAR(VAR, TYPE, FUNC) read_type_block(buf, sizeof(TYPE), input); TYPE VAR = FUNC(buf, 0);

#endif