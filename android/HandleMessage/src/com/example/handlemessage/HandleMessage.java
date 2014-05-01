package com.example.handlemessage;

import android.os.Bundle;
import android.os.Handler;
import android.app.Activity;
import android.view.Menu;

public class HandleMessage extends Activity implements Runnable{

	private Handler mHandler = new Handler() {
		public void handleMessage(android.os.Message msg) {
			setContentView(R.layout.activity_main);
		};
	};
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.loading);
		
		Thread thread = new Thread(this);
		thread.start();
	}

	@Override
	public void run() {
		initializeArrays();
		mHandler.sendEmptyMessage(0);
	}
	
	final static int NUM_SAMPS = 1000;
	static double[][] correlation;
	
	void initializeArrays() {
		if(correlation != null) return;
		correlation = new double[NUM_SAMPS][NUM_SAMPS];
		for(int k = 0; k < NUM_SAMPS; k++) {
			for(int m = 0; m < NUM_SAMPS; m++) {
				correlation[k][m] = Math.cos(2 * Math.PI * (k + m) / 1000);
			}
		}
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
