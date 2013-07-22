/*
 * Copyright (c) 2013, Alexey Degtyarev. 
 * All rights reserved.
 *
 * $Id: gost3411-2012-core.h 526 2013-05-26 18:24:29Z alexey $
 */

#include <string.h>


#if defined _MSC_VER
#define ALIGN(x) __declspec(align(x))
#else
#define ALIGN(x) __attribute__ ((__aligned__(x)))
#endif


#include "gost3411-2012-ref.h"

ALIGN(16) union uint512_u
{
    unsigned long long QWORD[8];
} uint512_u;

#include "gost3411-2012-const.h"
#include "gost3411-2012-precalc.h"

ALIGN(16) typedef struct GOST34112012Context
{
    ALIGN(16) unsigned char buffer[64];
    ALIGN(16) union uint512_u hash;
    ALIGN(16) union uint512_u h;
    ALIGN(16) union uint512_u N;
    ALIGN(16) union uint512_u Sigma;
    size_t bufsize;
    unsigned int digest_size;
} GOST34112012Context;

void GOST34112012Init(GOST34112012Context *CTX,
        const unsigned int digest_size);

void GOST34112012Update(GOST34112012Context *CTX, const unsigned char *data,
        size_t len); 

void GOST34112012Final(GOST34112012Context *CTX, unsigned char *digest); 

void GOST34112012Cleanup(GOST34112012Context *CTX);
