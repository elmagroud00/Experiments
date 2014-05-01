package com.example.serviceexample;

import android.app.Service;
import android.content.Intent;
import android.os.Bundle;
import android.os.IBinder;
import android.widget.Toast;

public class MyService extends Service {
	
	static final String TAG = "MyService";
	
	@Override
	public IBinder onBind(Intent arg0) {
		// TODO Auto-generated method stub
		return null;
	}
	
	@Override
	public void onCreate() {
		super.onCreate();
		Toast.makeText(this, "MyService: start", Toast.LENGTH_SHORT).show();
	}
	
	@Override
	public int onStartCommand(Intent intent, int flags, int startId) {
		 super.onStartCommand(intent, flags, startId);
		 Toast.makeText(this, "MyService: onStartCommand", Toast.LENGTH_SHORT).show();
		 return 0;
	}
    
	@Override
	public void onDestroy() {
		super.onDestroy();
		Toast.makeText(this, "MyService: onDestroy", Toast.LENGTH_SHORT).show();
	}
}
