/*********************************************************************
* Filename:   hash_api.h
* Author:     rimopa (rimopapomir AT gmail.com)
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Header file for communicating information
              related to hash functions confidently and efficiently.
*********************************************************************/

#ifndef HASH_DISTRIB_HASH_API_TYPE
#define HASH_DISTRIB_HASH_API_TYPE

#include <stddef.h>

typedef struct
{
    const char *name; // Name of your hash algorithm
    size_t ctx_size;  // Size you need for your context in bytes
    size_t out_size;  // Size of your returned key in bytes. Must be >= 2 and <= 256
    void (*init)(void *ctx);
    void (*update)(void *ctx, const unsigned char *data, size_t len);
    void (*final)(void *ctx, unsigned char *out);
} HashAPI;

#endif