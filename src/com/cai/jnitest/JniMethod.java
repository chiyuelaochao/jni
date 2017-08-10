package com.cai.jnitest;

import java.util.Date;
import java.util.Random;
import java.util.UUID;

public class JniMethod {
	public native void accessMethod();

	public native void accessStaticMethod();

	// ���ʹ��췽��
	public native Date acceessConstructor();

	public native String chineseChars(String str);
	
	int getRandomInt(int max) {
    	return new Random().nextInt(max);
    }
    
    static String getRandeomUUId() {
    	return UUID.randomUUID().toString();
    }
}
