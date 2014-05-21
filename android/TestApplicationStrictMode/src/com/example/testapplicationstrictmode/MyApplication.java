package com.example.testapplicationstrictmode;

import android.app.Application;
import android.os.StrictMode;
import android.util.Log;

public class MyApplication extends Application {

	private static final String TAG = "MyApplication";
	public static final boolean DEV_MODE = true;
	
	@Override
	public void onCreate() {
		Log.v(TAG, "MyApplication::OnCreate()");
		super.onCreate();
		
		if(DEV_MODE) {
			StrictMode.enableDefaults();
		}
	}
	
	@Override
	public void onTerminate() {
		super.onTerminate();
	}
}
