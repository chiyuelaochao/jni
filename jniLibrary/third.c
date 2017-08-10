#include "stdafx.h"

#include "com_cai_jnitest_JniThird.h"

//访问基本类型数据数组
JNIEXPORT void JNICALL Java_com_cai_jnitest_JniThird_giveArray
(JNIEnv * env, jobject jobj, jintArray arr) {
	int compare(jint * a, jint *b);
	//jintArray -> jint *
	jint *elemts = (*env)->GetIntArrayElements(env, arr, NULL);
	if (elemts == NULL)
	{
		return;
	}
	//数组长度
	int len = (*env)->GetArrayLength(env, arr);
	qsort(elemts, len, sizeof(jint), compare);
	//释放可能的内存
	//将JNI  修改的数据重新写回原来的内存
	(*env)->ReleaseIntArrayElements(env, arr, elemts, JNI_COMMIT);
}

int compare(jint * a, jint *b) {
	return *a - *b;
}


JNIEXPORT jobjectArray JNICALL Java_com_cai_jnitest_JniThird_initInt2DArray
(JNIEnv *, jobject, jint);

// 访问引用数据类型的数组
JNIEXPORT jobjectArray JNICALL Java_com_cai_jnitest_JniThird_initStringArray
(JNIEnv * env, jobject jobj, jint size) {
	//创建jobjectArray
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
	// 赋值
	for (i = 0; i < size; i++) {
		//C 字符串
		char * c_str = (char *)malloc(256);
		memset(c_str, 0, 256);
		//将int 转换成为char
		sprintf(c_str, "hello num: %d\n", i);
		//C ->jstring
		jstring str = (*env)->NewStringUTF(env, c_str);
		if (str == NULL) {
			return NULL;
		}
		//将jstring 赋值给数组
		(*env)->SetObjectArrayElement(env, result, i, str);
		free(c_str);
		c_str = NULL;
		//(*env)->DeleteGlobalRef(env, str);
	}

	//返回jobjectArray
	return result;
}

//JNI 引用
//局部引用
// 定义方式多样：FindClass，NewObject,GetObjectClass,NewCharArray.... NewLocalRef()
//释放方式： 1 方法调用完JVM 会自动释放 2.DeleteLocalRef
// 不能在多线程里面使用
JNIEXPORT void JNICALL Java_com_cai_jnitest_JniThird_localRef
(JNIEnv * env, jobject jobj) {
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		jclass cls = (*env)->FindClass(env, "java/util/Date");
		jmethodID jmid = (*env)->GetMethodID(env, cls, "<init>", "()V");
		//创建一个Date类型的局部引用
		jobject obj = (*env)->NewObject(env, cls, jmid);
		//使用这个引用

		//释放引用
		(*env)->DeleteLocalRef(env, cls);
		(*env)->DeleteLocalRef(env, obj);

	}
}


//全局引用
//跨线程，跨方法使用，NewGlobalRef 是创建全局引用的唯一方法
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

//弱全局引用
//它不会阻止GC,/跨线程，跨方法使用
jclass g_weak_cls;
JNIEXPORT jstring JNICALL Java_com_cai_jnitest_JniThird_createWeakRef
(JNIEnv * env, jobject jobj) {
	jclass cls_string = (*env)->FindClass(env, "java/lang/String");
	g_weak_cls = (*env)->NewWeakGlobalRef(env, cls_string);
	return g_weak_cls;
}


//JNI 异常处理
JNIEXPORT void JNICALL Java_com_cai_jnitest_JniThird_exception
(JNIEnv * env, jobject jobj) {
	jclass cls = (*env)->GetObjectClass(env, jobj);
	jfieldID fid = (*env)->GetFieldID(env, cls, "key", "Ljava/lang/String;");

	//检查是否发送异常
	jthrowable ex = (*env)->ExceptionOccurred(env);
	// 判断异常是否发送
	if (ex != NULL) {
		jclass newExc;
		//清空JNI 产生的异常
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

// 局部静态变量进行缓存
JNIEXPORT void JNICALL Java_com_cai_jnitest_JniThird_cached
(JNIEnv * env, jobject jobj) {
	jclass cls = (*env)->GetObjectClass(env, jobj);
	static jfieldID fid = NULL;
	if (fid == NULL) {
		fid = (*env)->GetFieldID(env, cls, "key", "Ljava/lang/String;");
		printf("GetFieldID\n");
	}
}


//全局的变量
jfieldID fid_glb;
JNIEXPORT void JNICALL Java_com_cai_jnitest_JniThird_cachedGlobal
(JNIEnv * env, jclass cls) {
	if (fid_glb == NULL) {
		fid_glb = (*env)->GetFieldID(env, cls, "key", "Ljava/lang/String;");
	}
}

//缓存策略和弱引用联合使用带来的问题
JNIEXPORT jstring JNICALL Java_com_cai_jnitest_JniThird_AcessCacheNewString
(JNIEnv * env, jobject jobj) {
	//定义一个静态的局部变量
	static jclass cls_string = NULL;
	if (cls_string == NULL)
	{
		printf("alvin in Java_com_cai_jnitest_JniThird_AcessCacheNewString out: \n");
		//给局部静态变量赋一个局部引用
		cls_string = (*env)->FindClass(env, "com/cai/jnitest/Refrence");
	}
	//使用这个静态局部变量 
	jmethodID jmid = (*env)->GetMethodID(env, cls_string, "getRef", "(I)I");
	jthrowable ex = (*env)->ExceptionOccurred(env);
	if (ex != NULL)
	{
		jclass newExc;
		// 让java 继续运行
		(*env)->ExceptionDescribe(env);//输出关于这个异常的描述
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
