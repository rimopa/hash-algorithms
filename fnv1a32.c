/*
Based on https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV-1a_hash
Written by Aleks Babkov Yatsenko
Adapted by rimopa

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
*/

#ifdef __cplusplus
#include <cstdint>
#include <string>
#else
#include <stdint.h>
#endif

#include "hash_api.h"

#define FNV1A32_BASIS 0x811c9dc5
#define FNV1A32_PRIME 0x01000193
#define OUT_SIZE 4

typedef struct
{
	uint32_t key;
} fnv1a64_CTX;

void fnv1a32_init(fnv1a64_CTX *ctx)
{
	ctx->key = FNV1A32_BASIS;
}

void fnv1a32_update(fnv1a64_CTX *ctx, const char *buf, size_t len)
{
	for (size_t i = 0; i < len; i++)
		ctx->key = (ctx->key ^ buf[i]) * FNV1A32_PRIME;
}

void fnv1a32_final(fnv1a64_CTX *ctx, uint32_t *out)
{
	*out = ctx->key;
}

void init(void *ctx)
{
	fnv1a32_init((fnv1a64_CTX *)ctx);
}
void update(void *ctx, const unsigned char *data, size_t len)
{
	fnv1a32_update((fnv1a64_CTX *)ctx, (char *)data, len);
}
void final(void *ctx, unsigned char *out)
{
	fnv1a32_final((fnv1a64_CTX *)ctx, (uint32_t *)out);
}

const HashAPI hash_api = {
	.name = "FNV1a 32 bits",

	.ctx_size = OUT_SIZE,
	.out_size = OUT_SIZE,

	.init = init,
	.update = update,
	.final = final};