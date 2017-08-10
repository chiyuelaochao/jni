package com.cai.jnitest;

public class TestMain {
	static {
		System.loadLibrary("jniLibrary");
	}

	public static void main(String[] args) {
		System.out.println("==========================JniUtil================================");
		System.out.println(JniUtil.getStringFromJni());

		JniUtil jniUtil = new JniUtil();
		System.out.println(jniUtil.getStringFromJni2());

		System.out.println("change before key: " + jniUtil.key);
		jniUtil.accessField();
		System.out.println("after change, Key:  " + jniUtil.key);

		System.out.println("change before count: " + JniUtil.count);
		jniUtil.accessStaticField();
		System.out.println("change after count: " + JniUtil.count);

		System.out.println("==========================JniMethod================================");

		JniMethod jniMethod = new JniMethod();
		jniMethod.accessMethod();
		jniMethod.accessStaticMethod();
		jniMethod.acceessConstructor();

		System.out.println(jniMethod.chineseChars("宝宝"));

		
		System.out.println("============================JniThird==============================");
		JniThird jniThird = new JniThird();
		int[] array = { 3, 9, 2, 50, 6, 13 };
		jniThird.giveArray(array);
		for (int i = 0; i < array.length; i++) {
			System.out.println(array[i]);
		}

//		int[][] arr = jniThird.initInt2DArray(3);
//		for (int i = 0; i < 3; i++) {
//			for (int j = 0; j < 3; j++) {
//				System.out.format("arr[%d][%d] = %d\n", i, j, arr[i][j]);
//			}
//		}

		String[] strArr = jniThird.initStringArray(5);
		for (int i = 0; i < strArr.length; i++) {
			System.out.format("strArr[%d] = %s\n", i, strArr[i]);
		}

		jniThird.createGlobalRef();
		System.out.println(jniThird.getglobalRef());
		jniThird.delGlobalRef();
		System.out.println("globalRef is released");
		// System.out.println(jniMain.getglobalRef());
		try {
			// jniMain.exception();
		} catch (Exception e) {
			System.out.println(e.toString());
		}

		System.out.println("----------------异常发生后-------------");

		// for(int i = 0; i < 100; i++) {
		// jniMain.cached();
		// }

		// jniMain.AcessCacheNewString();
		jniThird.AcessCF();
		for (int i = 0; i < 100; i++) {
			jniThird.AcessCF();
			long[] ar = new long[1024 * 1024];
		}
	}

}
