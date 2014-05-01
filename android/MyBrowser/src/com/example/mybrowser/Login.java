package com.example.mybrowser;

import com.example.mybroswer.R;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.graphics.drawable.AnimationDrawable;
import android.view.Menu;
import android.view.MotionEvent;
import android.view.Window;
import android.view.WindowManager;
import android.widget.ImageView;

public class Login extends Activity implements Runnable {

	private ImageView imageView = null;
	private AnimationDrawable animationDrawable = null;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
				WindowManager.LayoutParams.FLAG_FULLSCREEN);
		setContentView(R.layout.login);

		imageView = (ImageView) findViewById(R.id.frameView);
		animationDrawable = (AnimationDrawable) imageView.getBackground();

		new Thread(this).start();
	}

	@Override
	public void run() {
		
		try {
			Thread.sleep(10 * 1000);
			animationDrawable.stop();
			Intent i = new Intent(this, Browser.class);
			startActivity(i);
			
		} catch(InterruptedException e) {
			e.printStackTrace();
		}
		this.finish();
	}
	
	@Override
	public void onWindowFocusChanged(boolean hasFocus) {
		super.onWindowFocusChanged(hasFocus);
		animationDrawable.start();
	}

	@Override
	public boolean onTouchEvent(MotionEvent event) {

		if (event.getAction() == MotionEvent.ACTION_UP) {
			animationDrawable.stop();
			Intent i = new Intent(this, Browser.class);
			startActivity(i);
		}
		return true;
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
