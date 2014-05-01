package com.example.pressandplay;

import android.media.MediaPlayer;
import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.View;
import android.widget.Button;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		Button startButton = (Button)findViewById(R.id.trigger);
		startButton.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				Thread initBkgdThread = new Thread(new Runnable() {
					
					@Override
					public void run() {
						play_music();
					}
				});
				initBkgdThread.start();
			}
		});
	}
	
	int[] notes = {R.raw.c5, R.raw.b4, R.raw.a4, R.raw.g4};
	int NOTE_DURATION = 400;
	MediaPlayer m_mediaPlayer;
	boolean paused = false;
	
	@Override
	protected void onPause() {	
		super.onPause();
		paused = true;
	}
	
	@Override
	protected void onResume() {
		super.onResume();
		paused = false;
	}
	
	private void play_music() {
		for(int ii = 0; ii < 12; ii++) {
			if(!paused) {
				if(m_mediaPlayer != null) m_mediaPlayer.release();
				m_mediaPlayer = MediaPlayer.create(this, notes[ii % 4]);
				m_mediaPlayer.start();
				try {
					Thread.sleep(NOTE_DURATION);
				} catch(InterruptedException e) {
					e.printStackTrace();
				}
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
