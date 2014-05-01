package com.example.audioexampleraw;

import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioRecord;
import android.media.AudioTrack;
import android.media.MediaRecorder;
import android.os.Bundle;
import android.os.Handler;
import android.app.Activity;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class AudioExampleRaw extends Activity implements Runnable {
	
	private TextView statusText;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_audio_example_raw);
		
		statusText = (TextView)findViewById(R.id.status);
		
		Button actionButton = (Button)findViewById(R.id.record);
		actionButton.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				record_thread();
			}
		});
		
		Button replayButton = (Button)findViewById(R.id.play);
		replayButton.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				Thread thread = new Thread(AudioExampleRaw.this);
				thread.start();
			}
		});
	}

	String text_string;
	final Handler mHandler = new Handler();
	final Runnable mUpdateResults = new Runnable() {
		
		@Override
		public void run() {
			updateResultsInUi(text_string);
		}
	};
	
	private void updateResultsInUi(String update_txt) {
		statusText.setText(update_txt);
	}
	
	private void record_thread() {
		Thread thread = new Thread(new Runnable() {
			
			@Override
			public void run() {
				text_string = "Starting";
				mHandler.post(mUpdateResults);
				record();
				text_string = "Done";
				mHandler.post(mUpdateResults);
			}
		});
		thread.start();
	}
	
	private int audioEncoding = AudioFormat.ENCODING_PCM_16BIT;
	int frequency = 11025;
	int buffersize = 50 * AudioTrack.getMinBufferSize(frequency, AudioFormat.CHANNEL_OUT_MONO, audioEncoding);
	
	public AudioRecord audioRecord = new AudioRecord(MediaRecorder.AudioSource.MIC,
			frequency, AudioFormat.CHANNEL_IN_MONO,
			audioEncoding, buffersize);
	public AudioTrack audioTrack = new AudioTrack(AudioManager.STREAM_MUSIC, frequency,
			AudioFormat.CHANNEL_OUT_MONO,
			audioEncoding, 4096,
			AudioTrack.MODE_STREAM);
	short[] buffer = new short[buffersize];
	
	public void record() {
		try{
			audioRecord.startRecording();
			audioRecord.read(buffer, 0, buffersize);
			audioRecord.stop();
		}catch(Throwable t){
			Log.e("AudioExampleRaw", "Recording Failed");
		}
	}
	
	public void run() {
		audioTrack.play();
		int i = 0;
		while(i < buffersize) {
			audioTrack.write(buffer, i++, 1);
		}
		return;
	}
	
	@Override
	protected void onPause() {
		if(audioTrack != null) {
			if(audioTrack.getPlayState() == AudioTrack.PLAYSTATE_PLAYING) {
				audioTrack.pause();
			}
		}
		super.onPause();
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.audio_example_raw, menu);
		return true;
	}

}













