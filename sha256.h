/*********************************************************************
 * Filename:   sha256.h
 * Authors:    Brad Conte (brad AT bradconte.com), rimopa (rimopapomir AT gmail.com)
 * Copyright:
 * Disclaimer: This code is presented "as is" without any guarantees.
 * Details:    Defines the API for the corresponding SHA1 implementation.
 *********************************************************************/

#ifndef SHA256_H
#define SHA256_H

/*************************** HEADER FILES ***************************/
#include <stddef.h>

/****************************** MACROS ******************************/
#define SHA256_BLOCK_SIZE 32 // SHA256 outputs a 32 byte digest

/**************************** DATA TYPES ****************************/
typedef unsigned char BYTE; // 8-bit byte
typedef unsigned int WORD;	// 32-bit word, change to "long" for 16-bit machines

typedef struct
{
	BYTE data[64];
	WORD datalen;
	unsigned long long bitlen;
	WORD state[8];
} SHA256_CTX;

/*********************** FUNCTION DECLARATIONS **********************/
void sha256_init(SHA256_CTX *ctx);
void sha256_update(SHA256_CTX *ctx, const BYTE data[], size_t len);
void sha256_final(SHA256_CTX *ctx, BYTE hash[]);

/************************* HASH-DISTRIB CODE ************************/
#include "hash_api.h"

static const HashAPI api = {
	.name = "SHA256",

	.ctx_size = sizeof(SHA256_CTX),
	.out_size = 32,

	.init = init,
	.update = update,
	.final = final};

void init(void *ctx)
{
	sha256_init((SHA256_CTX *)ctx);
}
void update(void *ctx, const unsigned char *data, size_t len)
{
	sha256_update((SHA256_CTX *)ctx, (BYTE *)data, len);
}
void final(void *ctx, const unsigned char *out)
{
	sha256_final((SHA256_CTX *)ctx, (BYTE *)out);
}

HashAPI hash_api()
{
	return api;
}

#endif // SHA256_H
