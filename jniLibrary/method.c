#include "stdafx.h"
#include "com_cai_jnitest_JniMethod.h"
#include <Windows.h>
#include <string.h>

//JNI ���ʷǾ�̬����
JNIEXPORT void JNICALL Java_com_cai_jnitest_JniMethod_accessMethod
(JNIEnv * env, jobject jobj) {
	printf("Java_com_cai_jnitest_JniMethod_accessMethod \n");
	//jclass
	jclass jclz = (*env)->GetObjectClass(env, jobj);

	//jmethodId
	//���������֣�������ǩ��
	jmethodID mid = (*env)->GetMethodID(env, jclz, "getRandomInt", "(I)I");

	//����
	jint random = (*env)->CallIntMethod(env, jobj, mid, 200);
	printf("C random: %d \n", random);
}

//JNI ����Java �еľ�̬����
JNIEXPORT void JNICALL Java_com_cai_jnitest_JniMethod_accessStaticMethod
(JNIEnv *env, jobject jobj) {
	printf("Java_com_cai_jnitest_JniMethod_accessStaticMethod \n");
	//jclass, ͨ��jobjcct ������class������ҵ��ˣ������class ת���jclass��Ȼ�󷵻ء�
	jclass clz = (*env)->GetObjectClass(env, jobj);
	//jmethdId��GETStaticMethodID  ���������֣�������ǩ��
	jmethodID jmid = (*env)->GetStaticMethodID(env, clz, "getRandeomUUId", "()Ljava/lang/String;");

	// ���þ�̬����
	jstring uuid = (*env)->CallStaticObjectMethod(env, clz, jmid);

	//jstring -> char *
	char * uuid_c = (*env)->GetStringUTFChars(env, uuid, NULL);
	// uuid.txt
	char filename[100];
	sprintf(filename, "D://%s.txt", uuid_c);
	FILE *fp = fopen(filename, "w");
	fputs("I love Av", fp);
	fclose(fp);
	printf("�ļ�д��ɹ�\n");

}

//����java���췽��
JNIEXPORT jobject JNICALL Java_com_cai_jnitest_JniMethod_acceessConstructor
(JNIEnv * env, jobject jobj) {
	printf("Java_com_cai_jnitest_JniMethod_acceessConstructor \n");
	//ͨ�����·������JVM �����ҵ���Ӧ����
	jclass jclz = (*env)->FindClass(env, "java/util/Date");
	//jmethodid
	jmethodID jmid = (*env)->GetMethodID(env, jclz, "<init>", "()V");

	//���� newObject ʵ����Date ���󣬷���ֵ��һ��jobjcct
	jobject date_obj = (*env)->NewObject(env, jclz, jmid);

	//�õ���Ӧ����ķ�����ǰ���ǣ����Ƿ�������ض���Ĺ��캯���������������
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
	(*env)->ReleaseStringChars(env, in, c_str);// JVM ʹ�á�֪ͨJVM c_str ��ָ�Ŀռ�����ͷ���
	printf("string: %s\n", rtn);

	return NULL;

	//char *c_str = "�����뱦��";
	//jclass str_cls = (*env)->FindClass(env, "java/lang/String");
	//jmethodID jmid = (*env)->GetMethodID(env, str_cls, "<init>", "([BLjava/lang/String;)V");
	//
	////jstring -> jbyteArray
	//jbyteArray bytes = (*env)->NewByteArray(env, strlen(c_str));
	//// ��Char * ��ֵ�� bytes
	//(*env)->SetByteArrayRegion(env, bytes, 0, strlen(c_str), c_str);
	//jstring charsetName = (*env)->NewStringUTF(env, "GB2312");

	//return (*env)->NewObject(env, str_cls, jmid, bytes, charsetName);

}