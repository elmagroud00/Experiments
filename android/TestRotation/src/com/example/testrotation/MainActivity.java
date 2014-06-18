package com.example.testrotation;

import android.os.Bundle;
import android.app.Activity;
import android.content.Context;
import android.view.Display;
import android.view.Menu;
import android.view.Surface;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity {

	Button btn;
	TextView tv;
	
	WindowManager wm;
	Display display;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		wm = (WindowManager)getSystemService(Context.WINDOW_SERVICE);
		display = wm.getDefaultDisplay();
		
		btn = (Button)findViewById(R.id.btn);
		tv = (TextView)findViewById(R.id.tv);
		
		btn.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				int rotation = display.getRotation();
				switch(rotation) {
				case (Surface.ROTATION_0):
					tv.setText("0");
					break;
				case (Surface.ROTATION_90):
					tv.setText("90");
					break;
				case (Surface.ROTATION_180):
					tv.setText("180");
					break;
				case (Surface.ROTATION_270):
					tv.setText("270");
					break;
				default:
					tv.setText("ERROR");
					break;
				}
			}
		});
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
