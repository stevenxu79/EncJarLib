#include "com_seassoon_encrypt_EncryptJar.h"
#include <iostream>
#include <string.h>
using namespace std;

const char argDecKey[] = "FECOI()*&<MNCXZPKL899"; //参数解密KEY
JNIEXPORT jbyteArray JNICALL Java_com_seassoon_encrypt_EncryptJar_genEncKey(
		JNIEnv * _env, jobject _obj, jbyteArray _keyorg) {
	unsigned char* keyorgCharArray =
			(unsigned char*) _env->GetByteArrayElements(_keyorg, 0);
	jsize keyLen = _env->GetArrayLength(_keyorg);
	int desKeyLen = strlen(argDecKey);
	for (int i = 0; i < keyLen; i++) {
		for (int j = 0; j < desKeyLen; j++) {
			char keychar = argDecKey[j];
			keyorgCharArray[i] = keyorgCharArray[i] ^ keychar;
			keyorgCharArray[i] = keyorgCharArray[i] + keychar + 2; //改变内容
		}
	}
	jbyteArray c_result = _env->NewByteArray(keyLen);
	_env->SetByteArrayRegion(c_result, 0, keyLen, (jbyte*) keyorgCharArray);
	_env->ReleaseByteArrayElements(_keyorg, (jbyte *) keyorgCharArray, 0);
	return c_result;
}

JNIEXPORT jbyteArray JNICALL Java_com_seassoon_encrypt_EncryptJar_encrypt(
		JNIEnv * _env, jobject _obj, jbyteArray _buf, jbyteArray _enckey,
		jbyteArray _keyorg) {
//	cout << "Java_com_seassoon_encrypt_Encrypt_encrypt JNI(dll)" << endl;
	jsize len = _env->GetArrayLength(_buf);
	jsize keyLen = _env->GetArrayLength(_enckey);
	unsigned char* encKey = (unsigned char*) _env->GetByteArrayElements(_enckey,
			0);
	unsigned char* keyorgCharArray =
			(unsigned char*) _env->GetByteArrayElements(_keyorg, 0);
	unsigned char* dst = (unsigned char*) _env->GetByteArrayElements(_buf, 0);

	int desKeyLen = strlen(argDecKey);
//	cout << "KeyLen:" << desKeyLen << endl;
	jbyteArray e_result = _env->NewByteArray(len);
	bool flag = false;
	unsigned char encKeyCopy[keyLen];
	for (int i = 0; i < keyLen; i++) {
		encKeyCopy[i] = encKey[i];
		for (int j = desKeyLen; j > 0; j--) {
			char keychar = argDecKey[j - 1];
			encKey[i] = encKey[i] - keychar - 2; //恢复内容
			encKey[i] = encKey[i] ^ keychar;
		}
//		cout << "2," << encKey[i] << "," << keyorgCharArray[i] << endl;
		if (encKey[i] == keyorgCharArray[i]) {
			flag = true;
			continue;
		} else {
			flag = false;
			break;
		}
	}

//	if (strcmp(keyDe, keyorgCharArray) == 0) {
	if (flag) {

		//2.使用传入密钥加密或者从数据库获取密钥加密;
		int keyDeLen = _env->GetArrayLength(_enckey);
		for (int i = 0; i < len; i++) {
			for (int j = 0; j < keyDeLen; j++) {
				unsigned char keychar = encKeyCopy[j];
				dst[i] = dst[i] - keychar + 9;		//先改变内容
				dst[i] = dst[i] ^ keychar;

			}
		}

		_env->SetByteArrayRegion(e_result, 0, len, (jbyte *) dst);

	} else {
		cout << "Key is not right" << endl;
	}

	_env->ReleaseByteArrayElements(_keyorg, (jbyte *) keyorgCharArray, JNI_ABORT);
	_env->ReleaseByteArrayElements(_enckey, (jbyte *) encKey, JNI_ABORT);
	_env->ReleaseByteArrayElements(_buf, (jbyte *) dst, JNI_ABORT);
	return e_result;
}

JNIEXPORT jbyteArray JNICALL Java_com_seassoon_encrypt_EncryptJar_decrypt(
		JNIEnv * _env, jobject _obj, jbyteArray _buf, jbyteArray _deckey,
		jbyteArray _keyorg) {

//	cout << "Java_com_seassoon_encrypt_Encrypt_decrypt JNI(dll)" << endl;
	jsize len = _env->GetArrayLength(_buf);
	jsize keyLen = _env->GetArrayLength(_deckey);
	unsigned char* keyDe = (unsigned char*) _env->GetByteArrayElements(_deckey,
			0);
	unsigned char* keyorgCharArray =
			(unsigned char*) _env->GetByteArrayElements(_keyorg, 0);
	int desKeyLen = strlen(argDecKey);
//	cout << "desKeyLen:" << desKeyLen << endl;
	unsigned char* dst = (unsigned char*) _env->GetByteArrayElements(_buf, 0);
	jbyteArray c_result = _env->NewByteArray(len);
	bool flag = false;
	unsigned char decKeyCopy[keyLen];
	for (int i = 0; i < keyLen; i++) {
		decKeyCopy[i] = keyDe[i];
		for (int j = desKeyLen; j > 0; j--) {
			char keychar = argDecKey[j - 1];
			keyDe[i] = keyDe[i] - 2 - keychar;
			keyDe[i] = keyDe[i] ^ keychar;
		}
//		cout << "3," << keyDe[i] << "," << keyorgCharArray[i] << endl;
		if (keyDe[i] == keyorgCharArray[i]) {
			flag = true;
			continue;
		} else {
			flag = false;
			break;
		}
	}
//	if (strcmp(keyDe, keyorgCharArray) == 0) {
	if (flag) {
//		cout << "Key is right" << endl;

		//1.使用固定密钥加密
//		int encKeyLen = strlen(contEncKey);
//		for (int i = 0; i < len; i++) {
//			for (int j = encKeyLen; j > 0; j--) {
//				char keychar = contEncKey[j - 1];
//				dst[i] = dst[i] ^ keychar;
//				dst[i] = dst[i] + keychar - 9;		//恢复内容
//			}
//		}
		//2.使用传入密钥加密或者从数据库获取密钥加密;
		int keyDeLen = _env->GetArrayLength(_deckey);
		for (int i = 0; i < len; i++) {
			for (int j = keyDeLen; j > 0; j--) {
				unsigned char keychar = decKeyCopy[j - 1];
				dst[i] = dst[i] ^ keychar;
				dst[i] = dst[i] - 9 + keychar;		//恢复内容
			}
//			cout << "2," << dst[i] << endl;
		}

		_env->SetByteArrayRegion(c_result, 0, len, (jbyte *) dst);

		return c_result;
	} else {
		cout << "Key is not right" << endl;
	}
	_env->ReleaseByteArrayElements(_buf, (jbyte *) dst, JNI_ABORT);
	_env->ReleaseByteArrayElements(_deckey, (jbyte *) keyDe, JNI_ABORT);
	_env->ReleaseByteArrayElements(_keyorg, (jbyte *) keyorgCharArray, JNI_ABORT);

	return c_result;

}

