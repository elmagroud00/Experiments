package com.example.simpleactivity;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;


public class SimpleBroadcastReceiver extends BroadcastReceiver {

	@Override
	public void onReceive(Context context, Intent intent) {
		String action = intent.getAction();
		if(action.equals(Intent.ACTION_BATTERY_CHANGED)) {
			context.startService(new Intent(context, SimpleService2.class));
		}
	}

}
