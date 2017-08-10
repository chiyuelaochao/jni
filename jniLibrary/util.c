#include "stdafx.h"

#include "com_cai_jnitest_jniUtil.h"
#include <string.h>
#include <stdio.h>


JNIEXPORT jstring JNICALL Java_com_cai_jnitest_JniUtil_getStringFromJni
(JNIEnv * env, jclass jclz){
	printf("Java_com_cai_jnitest_JniUtil_getStringFromJni \n");
	return (*env)->NewStringUTF(env, "jstring from Java_com_cai_jnitest_JniUtil_getStringFromJni.");
}

JNIEXPORT jstring JNICALL Java_com_cai_jnitest_JniUtil_getStringFromJni2
(JNIEnv * env, jobject jobj){
	printf("Java_com_cai_jnitest_JniUtil_getStringFromJni2 \n");
	return (*env)->NewStringUTF(env, "jstring from Java_com_cai_jnitest_JniUtil_getStringFromJni2.");
}


JNIEXPORT jstring JNICALL Java_com_cai_jnitest_JniUtil_accessField
(JNIEnv * env, jobject jobj){
	printf("Java_com_cai_jnitest_JniUtil_accessField \n");
	// jclass
	jclass jclz = (*env)->GetObjectClass(env, jobj);

	// fieldId 属性名称，属性签名
	jfieldID fid = (*env)->GetFieldID(env, jclz, "key", "Ljava/lang/String;");
	// key -> dongNao key

	// 得到key 对应的值
	// GetXXXField
	jstring jstr = (*env)->GetObjectField(env, jobj, fid);

	// jni -> c
	char * c_str = (*env)->GetStringUTFChars(env, jstr, NULL);

	char text[30] = "key changed by Jni";
	// 生成新的字符串 dongNao key
	strcat(text, c_str);

	// C -> jni
	jstring new_str = (*env)->NewStringUTF(env, text);

	//setXXXField
	(*env)->SetObjectField(env, jobj, fid, new_str);

	(*env)->ReleaseStringChars(env, new_str, c_str);

	return new_str;
}

JNIEXPORT void JNICALL Java_com_cai_jnitest_JniUtil_accessStaticField
(JNIEnv * env, jobject jobj){
	printf("Java_com_cai_jnitest_JniUtil_accessStaticField \n");
	// jclass
	jclass jclz = (*env)->GetObjectClass(env, jobj);

	// fieldId 属性名称，属性签名
	jfieldID fid = (*env)->GetStaticFieldID(env, jclz, "count", "I");

	if (fid == NULL)
	{
		printf("fid is null");
	}
	jint count = (*env)->GetStaticIntField(env, jclz, fid);
	count++;

	(*env)->SetStaticIntField(env, jclz, fid, count);
}