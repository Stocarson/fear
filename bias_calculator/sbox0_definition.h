#define SBOX_INPUT_BITS 16
#define SBOX_OUTPUT_BITS 8
#define SBOX_INPUT_SIZE 1<<(SBOX_INPUT_BITS)
#define SBOX_OUTPUT_SIZE 1<<(SBOX_OUTPUT_BITS)
#define UPPERMASK ((1 << 8) - 1) << 8
#define LOWERMASK ((1 << 8) - 1)

// Left rotation
static inline int rol(int arg, int howmuch) {
    int tosave = arg >> (SBOX_OUTPUT_BITS - howmuch);
    return (arg << howmuch) + tosave;
}

static inline int sbox(int arg) {
    // Feal cipher sbox 0
    return rol((((arg & UPPERMASK) + (arg & LOWERMASK)) % 256), 2);
}
