/**
\brief Definitions for crypto engine initialization

\author Malisa Vucinic <malishav@gmail.com>, March 2015.
\author Marcelo Barros de Almeida <marcelobarrosalmeida@gmail.com>, March 2015.
*/
#ifndef __CRYPTO_ENGINE_H__
#define __CRYPTO_ENGINE_H__

#ifdef  __cplusplus
extern "C" {
#endif

#include "opendefs.h"

//=========================== define ==========================================
#define CBC_MAX_MAC_SIZE  16

#ifdef CRYPTO_ENGINE_SCONS
#define CRYPTO_ENGINE CRYPTO_ENGINE_SCONS
#else /* CRYPTO_ENGINE_SCONS */
#define CRYPTO_ENGINE dummy_crypto_engine
#endif /* CRYPTO_ENGINE_SCONS */

//=========================== module variables ================================

struct crypto_engine {

   /**
   \brief CCM* forward transformation (i.e. encryption + authentication).
   \param[in] a Pointer to the authentication only data.
   \param[in] len_a Length of authentication only data.
   \param[in,out] m Pointer to the data that is both authenticated and encrypted. Overwritten by
      ciphertext and the trailing authentication tag. Buffer must hold len_m + len_mac.
   \param[in,out] len_m Length of data that is both authenticated and encrypted. Accounts for
      the added authentication tag of len_mac octets on return.
   \param[in] nonce Buffer containing nonce (max 13 octets).
   \param[in] l CCM parameter L that allows selection of different nonce length which is (15 - L).
      For example, l = 2 selects 13-octet long nonce which is used for IEEE 802.15.4 security. 
   \param[in] key Buffer containing the secret key (16 octets).
   \param[in] len_mac Length of the authentication tag.
   */
   owerror_t (* aes_ccms_enc)(uint8_t* a,
      uint8_t len_a,
      uint8_t* m,
      uint8_t* len_m,
      uint8_t* nonce,
      uint8_t l,
      uint8_t key[16],
      uint8_t len_mac);

   /**
   \brief CCM* inverse transformation (i.e. decryption + tag verification).
   \param[in] a Pointer to the authentication only data.
   \param[in] len_a Length of authentication only data.
   \param[in,out] m Pointer to the data that is both authenticated and encrypted. Overwritten by
      plaintext.
   \param[in,out] len_m Length of data that is both authenticated and encrypted, including the
      trailing authentication tag. On return it is reduced for len_mac octets to account for the
      removed authentication tag.
   \param[in] nonce Buffer containing nonce (max 13 octets).
   \param[in] l CCM parameter L that allows selection of different nonce length which is (15 - L).
      For example, l = 2 selects 13-octet long nonce which is used for IEEE 802.15.4 security.
   \param[in] key Buffer containing the secret key (16 octets).
   \param[in] len_mac Length of the authentication tag.
   */
   owerror_t (* aes_ccms_dec)(uint8_t* a,
      uint8_t len_a,
      uint8_t* m,
      uint8_t* len_m,
      uint8_t* nonce,
      uint8_t l,
      uint8_t key[16],
      uint8_t len_mac);  

   /**
   \brief Raw AES-CBC encryption.
   \param[in,out] buffer Message to be encrypted. Will be overwritten by ciphertext.
   \param[in] len Message length. 
   \param[in] key Buffer containing the secret key (16 octets).
   \param[in] iv Buffer containing the Initialization Vector (16 octets).
   */  
   owerror_t (* aes_cbc_enc_raw)(uint8_t* buffer,
      uint8_t len,
      uint8_t key[16],
      uint8_t iv[16]);

   /**
   \brief Raw AES-CTR encryption.
   \param[in,out] buffer Message to be encrypted. Will be overwritten by ciphertext.
   \param[in] len Message length.
   \param[in] key Buffer containing the secret key (16 octets).
   \param[in] iv Buffer containing the Initialization Vector (16 octets).
   */
   owerror_t (* aes_ctr_enc_raw)(uint8_t* buffer,
      uint8_t len,
      uint8_t key[16],
      uint8_t iv[16]);

   /**
   \brief Basic AES encryption of a single 16-octet block.
   \param[in,out] buffer Single block plaintext (16 octets). Will be overwritten by ciphertext.
   \param[in] key Buffer containing the secret key (16 octets).
   */
   owerror_t (* aes_ecb_enc)(uint8_t buffer[16],
      uint8_t key[16]);
    
   /**
   \brief Initialization of the crypto_engine driver.
   */
   owerror_t (* init)(void);
}; // struct crypto_engine

extern const struct crypto_engine CRYPTO_ENGINE;

#ifdef  __cplusplus
}
#endif

#endif /* __CRYPTO_ENGINE_H__ */
