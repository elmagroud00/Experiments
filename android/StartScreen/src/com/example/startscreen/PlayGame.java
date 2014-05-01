package com.example.startscreen;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class PlayGame extends Activity {
	private TextView tv2;
	int answer;
	String author;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.game);
		
		tv2 = (TextView)findViewById(R.id.game_text);
		Intent i = getIntent();
		answer = i.getIntExtra("meaningOfLife", -1);
		author = i.getStringExtra("userName");
		
		tv2.setText(author + ":" + answer);
		
		answer = answer - 41;
		author = author + "Jr.";
		Button startButton = (Button)findViewById(R.id.end_game);
		startButton.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				Intent i = getIntent();
				i.putExtra("returnInt", answer);
				i.putExtra("returnStr", author);
				setResult(RESULT_OK, i);
				finish();
			}
		});
	}
}
