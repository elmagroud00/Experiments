package com.example.physicalkeypress;

import android.os.Bundle;
import android.app.Activity;
import android.view.KeyEvent;
import android.view.Menu;
import android.widget.Toast;

public class PhysicalKeyPress extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_physical_key_press);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.physical_key_press, menu);
		return true;
	}

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		switch(keyCode) {
		case KeyEvent.KEYCODE_CAMERA:
			Toast.makeText(this, "Press Camera Button", Toast.LENGTH_SHORT).show();
			return true;
		case KeyEvent.KEYCODE_DPAD_LEFT:
			Toast.makeText(this, "Pressed DPAD Left Button", Toast.LENGTH_SHORT).show();
			return true;
		case KeyEvent.KEYCODE_VOLUME_UP:
			Toast.makeText(this, "Press Volume Up Button", Toast.LENGTH_SHORT).show();
			return false;
		case KeyEvent.KEYCODE_SEARCH:
			if(event.getRepeatCount() == 0)
				event.startTracking();
			return true;
		case KeyEvent.KEYCODE_BACK:
			if(android.os.Build.VERSION.SDK_INT < android.os.Build.VERSION_CODES.ECLAIR &&
				event.getRepeatCount() == 0) {
					onBackPressed();
				}
			return super.onKeyDown(keyCode, event);
		}
		
		return super.onKeyDown(keyCode, event);
	}
	
	public void onBackPressed() {
		Toast.makeText(this, "Pressed BACK KEY", Toast.LENGTH_SHORT).show();
	}
	
	@Override
	public boolean onKeyUp(int keyCode, KeyEvent event) {
		if(keyCode == KeyEvent.KEYCODE_SEARCH && event.isTracking() && !event.isCanceled()) {
			Toast.makeText(this, "Pressed SEARCH Key", Toast.LENGTH_SHORT).show();
			return true;
		}
		return super.onKeyUp(keyCode, event);
	}
}
