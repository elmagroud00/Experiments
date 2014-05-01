package com.example.alertdialog;

import android.os.Bundle;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.view.Menu;

public class MainActivity extends Activity {

	private int mScroe = 0;
	private int mLevel = 0;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		AlertDialog dialog = new AlertDialog.Builder(this).create();
		dialog.setButton(DialogInterface.BUTTON_POSITIVE, "Try this level again", new DialogInterface.OnClickListener() {
			
			@Override
			public void onClick(DialogInterface dialog, int which) {
				mScroe = 0;
				start_level();
			}
		});
		
		dialog.setButton(DialogInterface.BUTTON_NEGATIVE, "Advence to next level", new DialogInterface.OnClickListener() {
			
			@Override
			public void onClick(DialogInterface dialog, int which) {
				mLevel++;
				start_level();
			}
		});
		
		dialog.setButton(DialogInterface.BUTTON_NEUTRAL, "Back to the main menu", new DialogInterface.OnClickListener() {
			
			@Override
			public void onClick(DialogInterface dialog, int which) {
			
				mLevel = 0;
				finish();
			}
		});
		dialog.show();
	}
	
	public void start_level() {
		
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
