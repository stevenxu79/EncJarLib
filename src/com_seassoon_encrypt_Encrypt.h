/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_seassoon_encrypt_Encrypt */

#ifndef _Included_com_seassoon_encrypt_Encrypt
#define _Included_com_seassoon_encrypt_Encrypt
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     com_seassoon_encrypt_Encrypt
 * Method:    genEncKey
 * Signature: ([B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_seassoon_encrypt_Encrypt_genEncKey
  (JNIEnv * _env, jobject _obj, jbyteArray _keyorg);


/*
 * Class:     com_seassoon_encrypt_Encrypt
 * Method:    encrypt
 * Signature: ([B[B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_seassoon_encrypt_Encrypt_encrypt
  (JNIEnv * _env, jobject _obj, jbyteArray _buf, jbyteArray _enckey,jbyteArray _keyorg);
//
//JNIEXPORT jbyteArray JNICALL Java_com_seassoon_encrypt_Encrypt_decrypt
//  (JNIEnv * _env, jobject _obj, jbyteArray _buf, jbyteArray _deckey, jbyteArray _keyorg);

#ifdef __cplusplus
}
#endif
#endif
