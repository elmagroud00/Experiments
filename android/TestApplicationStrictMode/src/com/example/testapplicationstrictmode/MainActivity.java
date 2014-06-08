package com.example.testapplicationstrictmode;

import android.os.Bundle;
import android.os.StrictMode;
import android.app.Activity;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.Button;

public class MainActivity extends Activity {

	private static final String TAG = "MainActivity";
	private Button btn = null;
	
	
	private long calFib(int fact) {
		StrictMode.noteSlowCall("Fib");
		if(fact > 2) {
			return calFib(fact - 2) + calFib(fact - 1);
		}
		return 0;
	}
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		
		if (MyApplication.DEV_MODE) {
			StrictMode.setThreadPolicy(new StrictMode.ThreadPolicy.Builder()
					.detectAll().penaltyLog().penaltyDialog().detectCustomSlowCalls().penaltyFlashScreen().build());
			
			StrictMode.setVmPolicy(new StrictMode.VmPolicy.Builder()
					.detectAll().penaltyLog().build());

		}
		
		btn = (Button)findViewById(R.id.btn);
		btn.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				calFib(100);
			}
		});

	}

	@Override
	protected void onResume() {
		super.onResume();
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
