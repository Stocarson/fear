#define SBOX_SIZE 16
#define SBOX_INPUT_BITS 4
#define SBOX_OUTPUT_BITS 4
#define SBOX_INPUT_SIZE 1<<(SBOX_INPUT_BITS)
#define SBOX_OUTPUT_SIZE 1<<(SBOX_OUTPUT_BITS)

static inline int sbox(int arg) {
    /* Small AES sbox */
    /* int small_AES_sbox[16]={}; */
    /* Simple cipher SBox (reduced DES) */
    int small_DES_sbox[16]= {0x0e,0x04,0x0d,0x01,0x02,0x0f,0x0b,0x08,0x03,0x0a,0x06,0x0c,0x05,0x09,0x00,0x07};
    return small_DES_sbox[arg];
}

