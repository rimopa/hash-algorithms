#include "hash_api.h"
#include <stdint.h>
#include <memory.h>

void init(void *ctx)
{
}
void update(void *ctx, const unsigned char *data, size_t len)
{
}
void final(void *ctx, unsigned char *out)
{
    uint8_t thirty_seven = 37;
    memcpy(out, &thirty_seven, sizeof(uint8_t));
}

const HashAPI hash_api = {
    .name = "I like 37",

    .ctx_size = 0,
    .out_size = sizeof(uint8_t),

    .init = init,
    .update = update,
    .final = final};