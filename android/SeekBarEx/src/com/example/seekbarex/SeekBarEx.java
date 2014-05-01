package com.example.seekbarex;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.widget.SeekBar;

public class SeekBarEx extends Activity {

	private SeekBar m_seekBar;
	boolean advancing = true;
	int count  = 0;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_seek_bar_ex);
		
		m_seekBar = (SeekBar)findViewById(R.id.seekBar);
		m_seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
			
			@Override
			public void onStopTrackingTouch(SeekBar seekBar) {
				// TODO Auto-generated method stub
				
			}
			
			@Override
			public void onStartTrackingTouch(SeekBar seekBar) {
				// TODO Auto-generated method stub
				
			}
			
			@Override
			public void onProgressChanged(SeekBar seekBar, int progress,
					boolean fromUser) {
				if(fromUser)
					count = progress;
			}
		});
		Thread initThread = new Thread(new Runnable() {
			
			@Override
			public void run() {
				show_time();
			}
		});
		initThread.start();
	}

	private void show_time() {
		for(count = 0; count < 100; count++){
			m_seekBar.setProgress(count);
			try {
				Thread.sleep(100);
			}catch(InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.seek_bar_ex, menu);
		return true;
	}

}
