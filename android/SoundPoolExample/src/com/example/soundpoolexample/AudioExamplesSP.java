package com.example.soundpoolexample;

import android.media.AudioManager;
import android.media.SoundPool;
import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.View;
import android.widget.Button;

public class AudioExamplesSP extends Activity {

	static float rate = 2f;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		Button playButton = (Button) findViewById(R.id.play_pause);
		final SoundPool mySP = new SoundPool(10, AudioManager.STREAM_MUSIC, 0);
		final int soundId = mySP.load(this, R.raw.hh, 1);

		mySP.setOnLoadCompleteListener(new SoundPool.OnLoadCompleteListener() {
			
			@Override
			public void onLoadComplete(SoundPool arg0, int arg1, int arg2) {
				mySP.play(soundId, 1f, 1f, 1, 5, rate);
			}
		});
		
		playButton.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View arg0) {
				int sid = 0;
				for(int i = 0; i < 1000; i++) {
					if(sid == 0) {
						try {
							rate = rate / 2;
							sid = mySP.play(soundId, 1f, 1f, 1, 5, rate);
							Thread.sleep(1);
						} catch(InterruptedException e) {
							e.printStackTrace();
						}
					} else {
						break;
					}
				}
			}
		});
	}
	
	
}
