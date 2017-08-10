#include "stdafx.h"
#include "com_cai_jnitest_JniMethod.h"
#include <Windows.h>
#include <string.h>

//JNI 访问非静态方法
JNIEXPORT void JNICALL Java_com_cai_jnitest_JniMethod_accessMethod
(JNIEnv * env, jobject jobj) {
	printf("Java_com_cai_jnitest_JniMethod_accessMethod \n");
	//jclass
	jclass jclz = (*env)->GetObjectClass(env, jobj);

	//jmethodId
	//方法的名字，方法的签名
	jmethodID mid = (*env)->GetMethodID(env, jclz, "getRandomInt", "(I)I");

	//调用
	jint random = (*env)->CallIntMethod(env, jobj, mid, 200);
	printf("C random: %d \n", random);
}

//JNI 访问Java 中的静态方法
JNIEXPORT void JNICALL Java_com_cai_jnitest_JniMethod_accessStaticMethod
(JNIEnv *env, jobject jobj) {
	printf("Java_com_cai_jnitest_JniMethod_accessStaticMethod \n");
	//jclass, 通过jobjcct 来搜索class，如果找到了，将这个class 转变成jclass，然后返回。
	jclass clz = (*env)->GetObjectClass(env, jobj);
	//jmethdId，GETStaticMethodID  方法的名字，方法的签名
	jmethodID jmid = (*env)->GetStaticMethodID(env, clz, "getRandeomUUId", "()Ljava/lang/String;");

	// 调用静态方法
	jstring uuid = (*env)->CallStaticObjectMethod(env, clz, jmid);

	//jstring -> char *
	char * uuid_c = (*env)->GetStringUTFChars(env, uuid, NULL);
	// uuid.txt
	char filename[100];
	sprintf(filename, "D://%s.txt", uuid_c);
	FILE *fp = fopen(filename, "w");
	fputs("I love Av", fp);
	fclose(fp);
	printf("文件写入成功\n");

}

//访问java构造方法
JNIEXPORT jobject JNICALL Java_com_cai_jnitest_JniMethod_acceessConstructor
(JNIEnv * env, jobject jobj) {
	printf("Java_com_cai_jnitest_JniMethod_acceessConstructor \n");
	//通过类的路径来从JVM 里面找到对应的类
	jclass jclz = (*env)->FindClass(env, "java/util/Date");
	//jmethodid
	jmethodID jmid = (*env)->GetMethodID(env, jclz, "<init>", "()V");

	//调用 newObject 实例化Date 对象，返回值是一个jobjcct
	jobject date_obj = (*env)->NewObject(env, jclz, jmid);

	//得到对应对象的方法，前提是，我们访问了相关对象的构造函数创建了这个对象
	jmethodID time_mid = (*env)->GetMethodID(env, jclz, "getTime", "()J");
	jlong time = (*env)->CallLongMethod(env, date_obj, time_mid);

	printf("time: %lld \n", time);
	return date_obj;
}


JNIEXPORT jstring JNICALL Java_com_cai_jnitest_JniMethod_chineseChars
(JNIEnv * env, jobject jobj, jstring in) {
	printf("Java_com_cai_jnitest_JniMethod_chineseChars \n");
	jboolean iscp;
	char * c_str = (*env)->GetStringChars(env, in, &iscp);
	if (iscp == JNI_TRUE)
	{
		printf("is copy: JNI_TRUE\n");
	}
	else if (iscp == JNI_FALSE)
	{
		printf("is copy: JNI_FALSE\n");
	}

	int length = (*env)->GetStringLength(env, in);
	const jchar * jcstr = (*env)->GetStringChars(env, in, NULL);
	if (jcstr == NULL) {
		return NULL;
	}
	//jchar -> char
	char * rtn = (char *)malloc(sizeof(char)* 2 * length + 3);
	memset(rtn, 0, sizeof(char)* 2 * length + 3);
	int size = 0;
	size = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)jcstr, length, rtn, sizeof(char)* 2 * length + 3, NULL, NULL);
	/*if (size <= 0)
	{
	printf("size: 0 \n", rtn);
	return NULL;
	}*/

	if (rtn != NULL) {
		free(rtn);
		rtn = NULL;
	}
	(*env)->ReleaseStringChars(env, in, c_str);// JVM 使用。通知JVM c_str 所指的空间可以释放了
	printf("string: %s\n", rtn);

	return NULL;

	//char *c_str = "马蓉与宝宝";
	//jclass str_cls = (*env)->FindClass(env, "java/lang/String");
	//jmethodID jmid = (*env)->GetMethodID(env, str_cls, "<init>", "([BLjava/lang/String;)V");
	//
	////jstring -> jbyteArray
	//jbyteArray bytes = (*env)->NewByteArray(env, strlen(c_str));
	//// 将Char * 赋值到 bytes
	//(*env)->SetByteArrayRegion(env, bytes, 0, strlen(c_str), c_str);
	//jstring charsetName = (*env)->NewStringUTF(env, "GB2312");

	//return (*env)->NewObject(env, str_cls, jmid, bytes, charsetName);

}