package com.example.telephoneapp;

import android.os.Bundle;
import android.app.Activity;
import android.telephony.TelephonyManager;
import android.view.Menu;
import android.widget.TextView;

public class TelephoneApp extends Activity {

	TextView tv1;
	TelephonyManager telManager;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_telephone_app);
		
		tv1 = (TextView)findViewById(R.id.tv1);
		telManager = (TelephonyManager)getSystemService(TELEPHONY_SERVICE);
		StringBuilder sb = new StringBuilder();
		sb.append("device: ").append(telManager.getDeviceId()).append("\n");
		sb.append("device software Ver: ").append(telManager.getDeviceSoftwareVersion()).append("\n");
		sb.append("Line number: ").append(telManager.getLine1Number()).append("\n");
		tv1.setText(sb.toString());
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.telephone_app, menu);
		return true;
	}

}
