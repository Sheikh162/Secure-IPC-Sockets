#ifndef AES_UTILS_H
#define AES_UTILS_H

#include <openssl/evp.h>
#include <openssl/rand.h>
#include <cstring>
#include <iostream>

// AES Key and IV size
constexpr int AES_KEY_SIZE = 16;  // 128-bit key
constexpr int MY_AES_BLOCK_SIZE = 16; // AES block size
constexpr int AES_IV_SIZE = 16;    // 128-bit IV

void generateAESKey(unsigned char *key, unsigned char *iv) {
    RAND_bytes(key, AES_KEY_SIZE);
    RAND_bytes(iv, AES_IV_SIZE);
}

bool encryptAES(const unsigned char *plaintext, int plaintext_len, 
                const unsigned char *key, const unsigned char *iv, 
                unsigned char *ciphertext, int &ciphertext_len) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) return false;

    if (EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv) != 1)
        return false;

    int len;
    if (EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len) != 1)
        return false;
    
    ciphertext_len = len;

    if (EVP_EncryptFinal_ex(ctx, ciphertext + len, &len) != 1)
        return false;
    
    ciphertext_len += len;
    EVP_CIPHER_CTX_free(ctx);
    return true;
}

bool decryptAES(const unsigned char *ciphertext, int ciphertext_len,
                const unsigned char *key, const unsigned char *iv,
                unsigned char *plaintext, int &plaintext_len) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) return false;

    if (EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv) != 1)
        return false;

    int len;
    if (EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len) != 1)
        return false;

    plaintext_len = len;

    if (EVP_DecryptFinal_ex(ctx, plaintext + len, &len) != 1)
        return false;

    plaintext_len += len;
    EVP_CIPHER_CTX_free(ctx);
    return true;
}

#endif
