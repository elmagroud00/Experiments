package com.example.recognizerintentexample;

import java.util.ArrayList;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.speech.RecognizerIntent;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity {

	private static final int RECOGNIZER_EXAMPLE = 1001;
	private TextView tv;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		tv = (TextView)findViewById(R.id.text_result);
		Button startButton = (Button)findViewById(R.id.trigger);
		
		startButton.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View arg0) {

				Intent intent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
				intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL, RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);
				intent.putExtra(RecognizerIntent.EXTRA_PROMPT, "Say a word");
				startActivityForResult(intent, RECOGNIZER_EXAMPLE);
				
			}
		}); 
	}

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
    	
    	if(requestCode == RECOGNIZER_EXAMPLE && resultCode == RESULT_OK) {
    		ArrayList<String> result = data.getStringArrayListExtra(RecognizerIntent.EXTRA_RESULTS);
    		tv.setText(result.toString());
    	}
    	
    	super.onActivityResult(requestCode, resultCode, data);
    }
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
