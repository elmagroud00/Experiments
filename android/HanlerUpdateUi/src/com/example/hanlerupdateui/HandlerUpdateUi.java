package com.example.hanlerupdateui;

import android.os.Bundle;
import android.os.Handler;
import android.app.Activity;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.ProgressBar;

public class HandlerUpdateUi extends Activity {

	private static ProgressBar m_progressBar;
	int percent_done = 0;
	final Handler mHandler = new Handler();
	final Runnable mUpdateResults = new Runnable() {
		
		@Override
		public void run() {
			m_progressBar.setProgress(percent_done);
		}
	};
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_handler_update_ui);
		
		m_progressBar = (ProgressBar)findViewById(R.id.ex_progress_bar);
		Button actionButton = (Button)findViewById(R.id.action);
		actionButton.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				do_work();
			}
		});
	}

	private void do_work() {
		Thread thread = new Thread(new Runnable() {
			
			@Override
			public void run() {
				percent_done = 0;
				mHandler.post(mUpdateResults);
				
				computation(1);
				percent_done = 10;
				mHandler.post(mUpdateResults);
				
				computation(2);
				percent_done = 20;
				mHandler.post(mUpdateResults);
				
				computation(3);
				percent_done = 30;
				mHandler.post(mUpdateResults);
				
				computation(4);
				percent_done = 50;
				mHandler.post(mUpdateResults);
				
				computation(5);
				percent_done = 70;
				mHandler.post(mUpdateResults);
				
				computation(6);
				percent_done = 100;
				mHandler.post(mUpdateResults);
			}
		});
		thread.start();
	}
	
	private static int SIZE = 1000;
	double tmp;
	private void computation(int val) {
		for(int ii = 0; ii < SIZE; ii++)
			for(int jj = 0; jj < SIZE; jj++)
				tmp = val * Math.log(ii + 1) / Math.log1p(jj + 1);
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.handler_update_ui, menu);
		return true;
	}

}
