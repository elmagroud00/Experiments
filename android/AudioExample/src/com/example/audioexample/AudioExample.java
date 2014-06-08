package com.example.audioexample;

import android.media.MediaPlayer;
import android.os.Bundle;
import android.os.Environment;
import android.app.Activity;
import android.content.Intent;
import android.view.Menu;
import android.view.View;
import android.widget.Button;

public class AudioExample extends Activity {

	static final String MUSIC_DIR = "/Music";
	Button playPauseButton;
	private MediaPlayer m_mediaPlayer;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_audio_example);
		
		playPauseButton = (Button)findViewById(R.id.play_pause);
		m_mediaPlayer = new MediaPlayer();
		
		String MusicDir = Environment.getExternalStorageDirectory().getAbsolutePath() + MUSIC_DIR;
		Intent i = new Intent(this, ListFiles.class);
		i.putExtra("directory", MusicDir);
		startActivityForResult(i, 0);
		
		playPauseButton.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				if(m_mediaPlayer.isPlaying()) {
					pauseMP();
				} else {
					startMP();
				}
			}
		});
	}
	
	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);
		if(requestCode == 0 && resultCode == RESULT_OK) {
			String tmp = data.getExtras().getString("clickedFile");
			
			try{
				m_mediaPlayer.setDataSource(tmp);
				m_mediaPlayer.prepare();
			}catch(Exception e) {
				e.printStackTrace();
			}
			startMP();
		}
	}
	
	void pauseMP() {
		playPauseButton.setText("Play");
		m_mediaPlayer.pause();
	}
	
	void startMP() {
		playPauseButton.setText("Pause");
		m_mediaPlayer.start();
	}

	boolean needToResume = false;
	
	@Override
	protected void onPause() {
		if(m_mediaPlayer != null && m_mediaPlayer.isPlaying()) {
			needToResume = true;
			pauseMP();
		}
		super.onPause();
	}
	
	@Override
	protected void onResume() {
		super.onResume();
		if(needToResume && m_mediaPlayer != null) {
			startMP();
		}
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.audio_example, menu);
		return true;
	}

}














