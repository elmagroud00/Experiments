package com.example.simpleserviceexample;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class MainActivity extends Activity implements OnClickListener {

	Button startServiceButton;
	Button stopServiceButton;
	Intent serviceIntent;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		startServiceButton = (Button)findViewById(R.id.StartServiceButton);
		stopServiceButton = (Button)findViewById(R.id.StopServiceButton);
		startServiceButton.setOnClickListener(this);
		stopServiceButton.setOnClickListener(this);
		
		serviceIntent = new Intent(this, SimpleServiceService.class);
	}

	@Override
	public void onClick(View v) {
		
		if(v == startServiceButton) {
			startService(serviceIntent);
		} else if(v == stopServiceButton) {
			stopService(serviceIntent);
		}
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
