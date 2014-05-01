package com.example.backgroundtimer;

import android.os.Bundle;
import android.os.Handler;
import android.os.SystemClock;
import android.app.Activity;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class BackgroundTimer extends Activity {

	private int buttonPress = 0;
	TextView mButtonLabel;
	private long mStartTime = 0L;
	private TextView mTimeLabel;
	private Handler mHandler = new Handler();
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_background_timer);
		
		if(mStartTime == 0L) {
			mStartTime = SystemClock.uptimeMillis();
			mHandler.removeCallbacks(mUpdateTimeTask);
			mHandler.postDelayed(mUpdateTimeTask, 1000);
		}
		
		mTimeLabel = (TextView)findViewById(R.id.text);
		mButtonLabel = (TextView)findViewById(R.id.trigger);
		
		Button startButton = (Button)findViewById(R.id.trigger);
		startButton.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				mButtonLabel.setText("Pressed " +  ++buttonPress + " times");
			}
		});
	}
	
	private Runnable mUpdateTimeTask = new Runnable() {
		
		@Override
		public void run() {
			final long start = mStartTime;
			long millis = SystemClock.uptimeMillis() - start;
			int seconds = (int)(millis / 1000);
			int minutes = seconds / 60;
			seconds = seconds % 60;
			mTimeLabel.setText(" " + minutes + ":" + String.format("%02d", seconds));
			mHandler.postDelayed(this, 200);
		}
	};

	@Override
	protected void onPause() {
		mHandler.removeCallbacks(mUpdateTimeTask);
		super.onPause();
	};
	
	@Override
	protected void onResume() {
		super.onResume();
		mHandler.postDelayed(mUpdateTimeTask, 100);
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.background_timer, menu);
		return true;
	}

}
