package com.example.testapplicationstrictmode;

import android.app.Application;
import android.util.Log;

public class MyApplication extends Application {

	private static final String TAG = "MyApplication";
	
	@Override
	public void onCreate() {
		Log.v(TAG, "MyApplication::OnCreate()");
		super.onCreate();
	}
}
