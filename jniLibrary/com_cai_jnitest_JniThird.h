/* DO NOT EDIT THIS FILE - it is machine generated */
#include "jni.h"
/* Header for class com_cai_jnitest_JniThird */

#ifndef _Included_com_cai_jnitest_JniThird
#define _Included_com_cai_jnitest_JniThird
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     com_cai_jnitest_JniThird
 * Method:    giveArray
 * Signature: ([I)V
 */
JNIEXPORT void JNICALL Java_com_cai_jnitest_JniThird_giveArray
  (JNIEnv *, jobject, jintArray);

/*
 * Class:     com_cai_jnitest_JniThird
 * Method:    initInt2DArray
 * Signature: (I)[[I
 */
JNIEXPORT jobjectArray JNICALL Java_com_cai_jnitest_JniThird_initInt2DArray
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_cai_jnitest_JniThird
 * Method:    initStringArray
 * Signature: (I)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_com_cai_jnitest_JniThird_initStringArray
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_cai_jnitest_JniThird
 * Method:    localRef
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_cai_jnitest_JniThird_localRef
  (JNIEnv *, jobject);

/*
 * Class:     com_cai_jnitest_JniThird
 * Method:    createGlobalRef
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_cai_jnitest_JniThird_createGlobalRef
  (JNIEnv *, jobject);

/*
 * Class:     com_cai_jnitest_JniThird
 * Method:    getglobalRef
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_cai_jnitest_JniThird_getglobalRef
  (JNIEnv *, jobject);

/*
 * Class:     com_cai_jnitest_JniThird
 * Method:    delGlobalRef
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_cai_jnitest_JniThird_delGlobalRef
  (JNIEnv *, jobject);

/*
 * Class:     com_cai_jnitest_JniThird
 * Method:    exception
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_cai_jnitest_JniThird_exception
  (JNIEnv *, jobject);

/*
 * Class:     com_cai_jnitest_JniThird
 * Method:    cached
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_cai_jnitest_JniThird_cached
  (JNIEnv *, jobject);

/*
 * Class:     com_cai_jnitest_JniThird
 * Method:    initIDs
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_cai_jnitest_JniThird_initIDs
  (JNIEnv *, jclass);

/*
 * Class:     com_cai_jnitest_JniThird
 * Method:    AcessCacheNewString
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_cai_jnitest_JniThird_AcessCacheNewString
  (JNIEnv *, jobject);

/*
 * Class:     com_cai_jnitest_JniThird
 * Method:    AcessCF
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_cai_jnitest_JniThird_AcessCF
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
