package com.example.startscreen;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity {

	private static final int PLAY_GAME = 1010;
	private TextView tv;
	private int meaningOfLife = 42;
	private String userName = "Douglas Adams";
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		tv = (TextView)findViewById(R.id.startscreen_text);
		tv.setText(userName + ":" + meaningOfLife);
		
		Button startButton=(Button)findViewById(R.id.play_game);
		startButton.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				startGame();
			}
		});
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		if(requestCode == PLAY_GAME && resultCode == RESULT_OK) {
			meaningOfLife = data.getExtras().getInt("returnInt");
			userName = data.getExtras().getString("userName");
			
			tv.setText(userName + ":" + meaningOfLife);
		}
		super.onActivityResult(requestCode, resultCode, data);
	}
	
	private void startGame() {
		Intent launchGame = new Intent(this, PlayGame.class);
		launchGame.putExtra("meaningOfLife", meaningOfLife);
		launchGame.putExtra("userName", userName);
		startActivityForResult(launchGame, PLAY_GAME);
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
