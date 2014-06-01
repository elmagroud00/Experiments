package com.example.testtoast;

import android.app.Activity;
import android.content.Context;
import android.graphics.drawable.GradientDrawable;
import android.os.Bundle;
import android.os.Handler;
import android.view.Gravity;
import android.widget.Toast;

public class MainActivity extends Activity {

	Handler handler = new Handler();

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		setContentView(R.layout.activity_main);
	}

	@Override
	protected void onResume() {
		super.onResume();
		mainProcessing();
	}

	private void mainProcessing() {
		Thread thread = new Thread(null, doBackgroundThreadProcessing,
				"Background");
		thread.start();
	}

	private Runnable doBackgroundThreadProcessing = new Runnable() {

		@Override
		public void run() {
			try {
				Thread.sleep(5 * 1000);
			} catch (Exception e) {
				// TODO: handle exception
			}

			backgroundThreadProcessing();
		}
	};

	private void backgroundThreadProcessing() {
		handler.post(doUpdateGUI);
	}

	private Runnable doUpdateGUI = new Runnable() {

		@Override
		public void run() {
			Context context = getApplicationContext();
			String msg = "To open mobile development";
			int duration = Toast.LENGTH_LONG;
			Toast toast = Toast.makeText(context, msg, duration);
			toast.setGravity(Gravity.TOP, 100, 0);
			toast.show();
		}
	};
}
