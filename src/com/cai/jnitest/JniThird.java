package com.cai.jnitest;

public class JniThird {
	public String key = "key";

	public static int count = 9;

	public native void accessNonVirtualMethod();

	public native void giveArray(int[] inArray);

	public native int[][] initInt2DArray(int size);

	public native String[] initStringArray(int size);

	public native void localRef();

	public native void createGlobalRef();

	public native String getglobalRef();

	public native void delGlobalRef();

	public native void exception();

	public native void cached();

	public native static void initIDs();

	public native String AcessCacheNewString();

	public native String AcessCF();
}
