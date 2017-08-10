#include "stdafx.h"

#include "com_cai_jnitest_JniThird.h"

//���ʻ���������������
JNIEXPORT void JNICALL Java_com_cai_jnitest_JniThird_giveArray
(JNIEnv * env, jobject jobj, jintArray arr) {
	int compare(jint * a, jint *b);
	//jintArray -> jint *
	jint *elemts = (*env)->GetIntArrayElements(env, arr, NULL);
	if (elemts == NULL)
	{
		return;
	}
	//���鳤��
	int len = (*env)->GetArrayLength(env, arr);
	qsort(elemts, len, sizeof(jint), compare);
	//�ͷſ��ܵ��ڴ�
	//��JNI  �޸ĵ���������д��ԭ�����ڴ�
	(*env)->ReleaseIntArrayElements(env, arr, elemts, JNI_COMMIT);
}

int compare(jint * a, jint *b) {
	return *a - *b;
}


JNIEXPORT jobjectArray JNICALL Java_com_cai_jnitest_JniThird_initInt2DArray
(JNIEnv *, jobject, jint);

// ���������������͵�����
JNIEXPORT jobjectArray JNICALL Java_com_cai_jnitest_JniThird_initStringArray
(JNIEnv * env, jobject jobj, jint size) {
	//����jobjectArray
	jobjectArray result;
	jclass jclz;
	int i;
	jclz = (*env)->FindClass(env, "java/lang/String");
	if (jclz == NULL) {
		return NULL;
	}
	result = (*env)->NewObjectArray(env, size, jclz, jobj);
	if (result == NULL) {
		return NULL;
	}
	// ��ֵ
	for (i = 0; i < size; i++) {
		//C �ַ���
		char * c_str = (char *)malloc(256);
		memset(c_str, 0, 256);
		//��int ת����Ϊchar
		sprintf(c_str, "hello num: %d\n", i);
		//C ->jstring
		jstring str = (*env)->NewStringUTF(env, c_str);
		if (str == NULL) {
			return NULL;
		}
		//��jstring ��ֵ������
		(*env)->SetObjectArrayElement(env, result, i, str);
		free(c_str);
		c_str = NULL;
		//(*env)->DeleteGlobalRef(env, str);
	}

	//����jobjectArray
	return result;
}

//JNI ����
//�ֲ�����
// ���巽ʽ������FindClass��NewObject,GetObjectClass,NewCharArray.... NewLocalRef()
//�ͷŷ�ʽ�� 1 ����������JVM ���Զ��ͷ� 2.DeleteLocalRef
// �����ڶ��߳�����ʹ��
JNIEXPORT void JNICALL Java_com_cai_jnitest_JniThird_localRef
(JNIEnv * env, jobject jobj) {
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		jclass cls = (*env)->FindClass(env, "java/util/Date");
		jmethodID jmid = (*env)->GetMethodID(env, cls, "<init>", "()V");
		//����һ��Date���͵ľֲ�����
		jobject obj = (*env)->NewObject(env, cls, jmid);
		//ʹ���������

		//�ͷ�����
		(*env)->DeleteLocalRef(env, cls);
		(*env)->DeleteLocalRef(env, obj);

	}
}


//ȫ������
//���̣߳��緽��ʹ�ã�NewGlobalRef �Ǵ���ȫ�����õ�Ψһ����
jstring global_str;
JNIEXPORT void JNICALL Java_com_cai_jnitest_JniThird_createGlobalRef
(JNIEnv * env, jobject jobj) {
	jobject obj = (*env)->NewStringUTF(env, "JNI is intersting");
	global_str = (*env)->NewGlobalRef(env, obj);
}


JNIEXPORT jstring JNICALL Java_com_cai_jnitest_JniThird_getglobalRef
(JNIEnv * env, jobject jobj) {
	return global_str;
}


JNIEXPORT void JNICALL Java_com_cai_jnitest_JniThird_delGlobalRef
(JNIEnv * env, jobject jobj) {
	(*env)->DeleteGlobalRef(env, global_str);

}

//��ȫ������
//��������ֹGC,/���̣߳��緽��ʹ��
jclass g_weak_cls;
JNIEXPORT jstring JNICALL Java_com_cai_jnitest_JniThird_createWeakRef
(JNIEnv * env, jobject jobj) {
	jclass cls_string = (*env)->FindClass(env, "java/lang/String");
	g_weak_cls = (*env)->NewWeakGlobalRef(env, cls_string);
	return g_weak_cls;
}


//JNI �쳣����
JNIEXPORT void JNICALL Java_com_cai_jnitest_JniThird_exception
(JNIEnv * env, jobject jobj) {
	jclass cls = (*env)->GetObjectClass(env, jobj);
	jfieldID fid = (*env)->GetFieldID(env, cls, "key", "Ljava/lang/String;");

	//����Ƿ����쳣
	jthrowable ex = (*env)->ExceptionOccurred(env);
	// �ж��쳣�Ƿ���
	if (ex != NULL) {
		jclass newExc;
		//���JNI �������쳣
		(*env)->ExceptionClear(env);
		//IllegalArgumentException
		newExc = (*env)->FindClass(env, "java/lang/IllegalArgumentException");
		if (newExc == NULL)
		{
			printf("exception\n");
			return;
		}
		(*env)->ThrowNew(env, newExc, "Throw exception from JNI: GetFieldID faild ");
	}

}

// �ֲ���̬�������л���
JNIEXPORT void JNICALL Java_com_cai_jnitest_JniThird_cached
(JNIEnv * env, jobject jobj) {
	jclass cls = (*env)->GetObjectClass(env, jobj);
	static jfieldID fid = NULL;
	if (fid == NULL) {
		fid = (*env)->GetFieldID(env, cls, "key", "Ljava/lang/String;");
		printf("GetFieldID\n");
	}
}


//ȫ�ֵı���
jfieldID fid_glb;
JNIEXPORT void JNICALL Java_com_cai_jnitest_JniThird_cachedGlobal
(JNIEnv * env, jclass cls) {
	if (fid_glb == NULL) {
		fid_glb = (*env)->GetFieldID(env, cls, "key", "Ljava/lang/String;");
	}
}

//������Ժ�����������ʹ�ô���������
JNIEXPORT jstring JNICALL Java_com_cai_jnitest_JniThird_AcessCacheNewString
(JNIEnv * env, jobject jobj) {
	//����һ����̬�ľֲ�����
	static jclass cls_string = NULL;
	if (cls_string == NULL)
	{
		printf("alvin in Java_com_cai_jnitest_JniThird_AcessCacheNewString out: \n");
		//���ֲ���̬������һ���ֲ�����
		cls_string = (*env)->FindClass(env, "com/cai/jnitest/Refrence");
	}
	//ʹ�������̬�ֲ����� 
	jmethodID jmid = (*env)->GetMethodID(env, cls_string, "getRef", "(I)I");
	jthrowable ex = (*env)->ExceptionOccurred(env);
	if (ex != NULL)
	{
		jclass newExc;
		// ��java ��������
		(*env)->ExceptionDescribe(env);//�����������쳣������
		(*env)->ExceptionClear(env);
		printf("C exceptions happend\n");
	}

	printf("alvin out Java_com_cai_jnitest_JniThird_AcessCacheNewString\n");
	return NULL;
}


JNIEXPORT jstring JNICALL Java_com_cai_jnitest_JniThird_AcessCF
(JNIEnv * env, jobject jobj) {
	//Sleep(100);
	return Java_com_cai_jnitest_JniThird_AcessCacheNewString(env, jobj);
}
