/*
 * com_seassoon_encrypt_Encrypt.cpp
 *
 *  Created on: 2018年5月23日
 *      Author: steven
 */

#include "com_seassoon_encrypt_Encrypt.h"
#include <iostream>
#include <string.h>
using namespace std;

const char* argDecKey = "FECOI()*&<MNCXZPKL899"; //参数解密KEY
const char* contEncKey = "FECOI()*&<MNCXZPKL0909090"; //内容加密解密KEY

JNIEXPORT jbyteArray JNICALL Java_com_seassoon_encrypt_Encrypt_genEncKey(
		JNIEnv * _env, jobject _obj, jbyteArray _keyorg) {
	unsigned char* keyorgCharArray =
			(unsigned char*) _env->GetByteArrayElements(_keyorg, 0);
	jsize keyLen = _env->GetArrayLength(_keyorg);
	int desKeyLen = strlen(argDecKey);
	for (int i = 0; i < keyLen; i++) {
		for (int j = 0; j < desKeyLen; j++) {
			char keychar = argDecKey[j];
			keyorgCharArray[i] = keyorgCharArray[i] ^ keychar;
			keyorgCharArray[i] = keyorgCharArray[i] + keychar + 2;
		}
	}
	jbyteArray c_result = _env->NewByteArray(keyLen);
	_env->SetByteArrayRegion(c_result, 0, keyLen, (jbyte*) keyorgCharArray);
	return c_result;
}

JNIEXPORT jbyteArray JNICALL Java_com_seassoon_encrypt_Encrypt_encrypt(
		JNIEnv * _env, jobject _obj, jbyteArray _buf, jbyteArray _key,
		jbyteArray _keyorg) {
	cout << "Java_com_seassoon_encrypt_Encrypt_encrypt JNI(dll)" << endl;
	jsize len = _env->GetArrayLength(_buf);
	jsize keyLen = _env->GetArrayLength(_keyorg);
	char* keyDe = (char*) _env->GetByteArrayElements(_key, 0);
	char* keyorgCharArray = (char*) _env->GetByteArrayElements(_keyorg, 0);

	int desKeyLen = strlen(argDecKey);
//	cout << "KeyLen:" << desKeyLen << endl;
	bool flag = false;
	for (int i = 0; i < keyLen; i++) {

		for (int j = desKeyLen; j > 0; j--) {
			char keychar = argDecKey[j - 1];
			keyDe[i] = keyDe[i] - keychar - 2;
			keyDe[i] = keyDe[i] ^ keychar;
		}
//		cout << "2," << keyDe[i] << "," << keyorgCharArray[i] << endl;
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
		cout << "Key is right" << endl;
		char* dst = (char*) _env->GetByteArrayElements(_buf, 0);
//		char* encData = encode(dst);

		int encKeyLen = strlen(contEncKey);

		for (int i = 0; i < len; i++) {
			for (int j = 0; j < encKeyLen; j++) {
				char keychar = contEncKey[j];
				dst[i] = dst[i] - keychar + 9;//先改变内容
				dst[i] = dst[i] ^ keychar;

			}
		}

		jbyteArray c_result = _env->NewByteArray(len);
		_env->SetByteArrayRegion(c_result, 0, len, (jbyte *) dst);
		_env->ReleaseByteArrayElements(_buf, (jbyte *) dst, 0);
		return c_result;
	} else {
		cout << "Key is not right" << endl;
	}
	_env->ReleaseByteArrayElements(_key, (jbyte *) keyDe, 0);
	_env->ReleaseByteArrayElements(_keyorg, (jbyte *) keyorgCharArray, 0);
	return _buf;
}

JNIEXPORT jbyteArray JNICALL Java_com_seassoon_encrypt_Encrypt_decrypt(
		JNIEnv * _env, jobject _obj, jbyteArray _buf, jbyteArray _key,
		jbyteArray _keyorg) {

	cout << "Java_com_seassoon_encrypt_Encrypt_decrypt JNI(dll)" << endl;
	jsize len = _env->GetArrayLength(_buf);
	jsize keyLen = _env->GetArrayLength(_keyorg);
	char* keyDe = (char*) _env->GetByteArrayElements(_key, 0);
	char* keyorgCharArray = (char*) _env->GetByteArrayElements(_keyorg, 0);
	int desKeyLen = strlen(argDecKey);
//	cout << "desKeyLen:" << desKeyLen << endl;
	bool flag = false;
	for (int i = 0; i < keyLen; i++) {

		for (int j = desKeyLen; j > 0; j--) {
			char keychar = argDecKey[j - 1];
			keyDe[i] = keyDe[i] - keychar - 2;
			keyDe[i] = keyDe[i] ^ keychar;
		}
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
		cout << "Key is right" << endl;
		char* dst = (char*) _env->GetByteArrayElements(_buf, 0);
//		char* encData = encode(dst);
		int encKeyLen = strlen(contEncKey);
		for (int i = 0; i < len; i++) {
			for (int j = encKeyLen; j >0 ; j--) {
				char keychar = contEncKey[j-1];
				dst[i] = dst[i] ^ keychar;
				dst[i] = dst[i] + keychar - 9;//恢复内容
			}
		}

		jbyteArray c_result = _env->NewByteArray(len);
		_env->SetByteArrayRegion(c_result, 0, len, (jbyte *) dst);
		_env->ReleaseByteArrayElements(_buf, (jbyte *) dst, 0);
		return c_result;
	} else {
		cout << "Key is not right" << endl;
	}
	_env->ReleaseByteArrayElements(_key, (jbyte *) keyDe, 0);
	_env->ReleaseByteArrayElements(_keyorg, (jbyte *) keyorgCharArray, 0);
	return _buf;

}

