package com.cai.jnitest;

public class JniUtil {
	public String key= "key";
	public static int count = 9;
	
	public native static String getStringFromJni();
	public native String getStringFromJni2();
	public native String accessField();
	public native void accessStaticField();
}
