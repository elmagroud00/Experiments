package com.example.testtts;

import java.util.Locale;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.speech.tts.TextToSpeech;
import android.speech.tts.TextToSpeech.Engine;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class MainActivity extends Activity implements
		android.view.View.OnClickListener {

	Button testBtn;
	private static int TTS_DATA_CHECK = 1;
	private TextToSpeech tts = null;
	private boolean ttsIsInit = false;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		testBtn = (Button) findViewById(R.id.test);
		testBtn.setOnClickListener(this);
	}

	@Override
	public void onClick(View v) {
		switch (v.getId()) {
		case R.id.test:
			Toast.makeText(this, "Speak", Toast.LENGTH_LONG).show();
			initTextToSpeech();
			break;
		default:
			break;
		}
	}

	private void initTextToSpeech() {
		Intent intent = new Intent(Engine.ACTION_INSTALL_TTS_DATA);
		startActivityForResult(intent, TTS_DATA_CHECK);
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		if (requestCode == TTS_DATA_CHECK) {
			if (resultCode == Engine.CHECK_VOICE_DATA_PASS) {
				tts = new TextToSpeech(this, new TextToSpeech.OnInitListener() {

					@Override
					public void onInit(int status) {
						if (status == TextToSpeech.SUCCESS) {
							ttsIsInit = true;
							if (tts.isLanguageAvailable(Locale.US) >= 0)
								tts.setLanguage(Locale.US);
							tts.setPitch(0.8f);
							tts.setSpeechRate(1.1f);
							speak();
						}
					}
				});
			}
		}

	}

	private void speak() {
		if (tts != null && ttsIsInit) {
			tts.speak("Hello, Android", TextToSpeech.QUEUE_ADD, null);
		}
	}

	@Override
	protected void onDestroy() {
		if(tts != null) {
			tts.stop();
			tts.shutdown();
		}
		super.onDestroy();
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
