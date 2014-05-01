package com.example.handlerupdateui;

import android.os.Bundle;
import android.os.Handler;
import android.app.Activity;
import android.graphics.Color;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class HandlerUpdateUi extends Activity {
	
	TextView av;
	int text_string = R.string.start;
	int background_color = Color.DKGRAY;
	final Handler mHandler = new Handler();
	final Runnable mUpdateResults = new Runnable() {
		
		@Override
		public void run() {
			av.setText(text_string);
			av.setBackgroundColor(background_color);
		}
	};

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		av = (TextView)findViewById(R.id.computation_status);
		Button actionButton = (Button)findViewById(R.id.action);
		actionButton.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				do_work();
			}
		});
	}

	private void do_work() {
		Thread thread = new Thread(new Runnable() {
			
			@Override
			public void run() {
				text_string = R.string.start;
				background_color = Color.DKGRAY;
				mHandler.post(mUpdateResults);
				
				computation(1);
				text_string = R.string.first;
				background_color = Color.BLUE;
				mHandler.post(mUpdateResults);
				
				computation(2);
				text_string = R.string.second;
				background_color = Color.GREEN;
				mHandler.post(mUpdateResults);
			}
		});
		thread.start();
	}
	
	final static int SIZE = 1000;
	double tmp;
	
	private void computation(int val) {
		for(int ii = 0; ii < SIZE; ii++)
			for(int jj = 0; jj < SIZE; jj++)
				tmp = val * Math.log(ii + 1) / Math.log1p(jj + 1);
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
