#include <stdint.h>
#include "hash_api.h"
#define OUT_SIZE 8
#define djb2_BASIS 5381

typedef struct
{
    uint64_t key;
} djb2_CTX;

void djb2_init(djb2_CTX *ctx)
{
    ctx->key = djb2_BASIS;
}

void djb2_update(djb2_CTX *ctx, const char *buf, size_t len)
{
    for (size_t i = 0; i < len; i++)
        ctx->key = (ctx->key << 5) + ctx->key + buf[i];
}

void djb2_final(djb2_CTX *ctx, uint64_t *out)
{
    *out = ctx->key;
}

void init(void *ctx)
{
    djb2_init((djb2_CTX *)ctx);
}
void update(void *ctx, const unsigned char *data, size_t len)
{
    djb2_update((djb2_CTX *)ctx, (char *)data, len);
}
void final(void *ctx, unsigned char *out)
{
    djb2_final((djb2_CTX *)ctx, (uint64_t *)out);
}

static const HashAPI api = {
    .name = "djb2",

    .ctx_size = OUT_SIZE,
    .out_size = OUT_SIZE,

    .init = init,
    .update = update,
    .final = final};

HashAPI hash_api(void)
{
    return api;
}