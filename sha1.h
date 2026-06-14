/*********************************************************************
 * Filename:   sha1.h
 * Author:     Brad Conte (brad AT bradconte.com), rimopa (rimopapomir AT gmail.com)
 * Copyright:
 * Disclaimer: This code is presented "as is" without any guarantees.
 * Details:    Defines the API for the corresponding SHA1 implementation.
 *********************************************************************/

#ifndef SHA1_H
#define SHA1_H

/*************************** HEADER FILES ***************************/
#include <stddef.h>

/****************************** MACROS ******************************/
#define SHA1_BLOCK_SIZE 20              // SHA1 outputs a 20 byte digest

/**************************** DATA TYPES ****************************/
typedef unsigned char BYTE;             // 8-bit byte
typedef unsigned int  WORD;             // 32-bit word, change to "long" for 16-bit machines

typedef struct {
	BYTE data[64];
	WORD datalen;
	unsigned long long bitlen;
	WORD state[5];
	WORD k[4];
} SHA1_CTX;

/*********************** FUNCTION DECLARATIONS **********************/
void sha1_init(SHA1_CTX *ctx);
void sha1_update(SHA1_CTX *ctx, const BYTE data[], size_t len);
void sha1_final(SHA1_CTX *ctx, BYTE hash[]);

/************************* HASH-DISTRIB CODE ************************/
#include "hash_api.h"

static const HashAPI api = {
	.name = "SHA1",

	.ctx_size = sizeof(SHA1_CTX),
	.out_size = 20,

	.init = init,
	.update = update,
	.final = final};

void init(void *ctx)
{
	sha1_init((SHA1_CTX *)ctx);
}
void update(void *ctx, const unsigned char *data, size_t len)
{
	sha1_update((SHA1_CTX *)ctx, (BYTE *)data, len);
}
void final(void *ctx, const unsigned char *out)
{
	sha1_final((SHA1_CTX *)ctx, (BYTE *)out);
}

HashAPI hash_api(void)
{
	return api;
}

#endif   // SHA1_H
