package com.example.countdowntimeexample;

import android.os.Bundle;
import android.os.CountDownTimer;
import android.app.Activity;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity {

	private int buttonPress = 0;
	TextView mButtonLabel;
	private TextView mTimeLabel;
	CountDownTimer myTimer;
	long myTime = 30000;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		mTimeLabel = (TextView) findViewById(R.id.text);
		mButtonLabel = (TextView) findViewById(R.id.trigger);

		Button startButton = (Button) findViewById(R.id.trigger);
		
		startButton.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View arg0) {
				mButtonLabel.setText("Pressed" + ++buttonPress + "times");
			}
		});
	}

	@Override
	protected void onResume() {
		
		myTimer = new CountDownTimer(myTime, 1000) {

			@Override
			public void onTick(long arg0) {
				mTimeLabel.setText("second remaining: " + arg0 / 1000);
				myTime = arg0;
			}

			@Override
			public void onFinish() {
				mTimeLabel.setText("done!");
				myTime = 0;
			}
		}.start();
		super.onResume();
	}
	
	@Override
	protected void onStop() {
		myTimer.cancel();
		super.onStop();
	}
	
	@Override
	protected void onSaveInstanceState(Bundle outState) {
		outState.putLong("time", myTime);
		super.onSaveInstanceState(outState);
	}

	@Override
	protected void onRestoreInstanceState(Bundle savedInstanceState) {
		myTime = savedInstanceState.getLong("time");
		super.onRestoreInstanceState(savedInstanceState);
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
