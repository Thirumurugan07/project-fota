#include <stdint.h>

void pal_crypt_tls_prf_sha256(const uint8_t* secret, uint16_t secret_length,
                               const uint8_t* label, uint16_t label_length,
                               const uint8_t* seed, uint16_t seed_length,
                               uint8_t* derived_key, uint16_t* derived_key_length)
{
    if (derived_key && derived_key_length)
    {
        for (uint16_t i = 0; i < *derived_key_length; i++)
        {
            derived_key[i] = 0x00;  // Dummy output
        }
    }
}

int pal_crypt_encrypt_aes128_ccm(const uint8_t* key, const uint8_t* nonce, uint16_t nonce_length,
                                  const uint8_t* input, uint16_t input_length,
                                  const uint8_t* aad, uint16_t aad_length,
                                  uint8_t* output, uint8_t* tag, uint16_t tag_length)
{
    for (uint16_t i = 0; i < input_length; i++)
    {
        output[i] = input[i];  // No real encryption
    }
    return 0;  // Success
}

int pal_crypt_decrypt_aes128_ccm(const uint8_t* key, const uint8_t* nonce, uint16_t nonce_length,
                                  const uint8_t* input, uint16_t input_length,
                                  const uint8_t* aad, uint16_t aad_length,
                                  const uint8_t* tag, uint16_t tag_length,
                                  uint8_t* output)
{
    for (uint16_t i = 0; i < input_length; i++)
    {
        output[i] = input[i];  // No real decryption
    }
    return 0;  // Success
}
