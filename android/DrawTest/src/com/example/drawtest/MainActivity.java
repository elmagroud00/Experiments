package com.example.drawtest;

import android.os.Bundle;
import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Path;
import android.graphics.Typeface;
import android.support.v4.widget.SlidingPaneLayout.PanelSlideListener;
import android.view.Display;
import android.view.Menu;
import android.view.Window;
import android.view.WindowManager;
import android.widget.ImageView;

public class MainActivity extends Activity {

	ImageView imageView;
	Bitmap bmp;
	Canvas canvas;
	Paint paint;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
				WindowManager.LayoutParams.FLAG_FULLSCREEN);
		setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
		
		setContentView(R.layout.activity_main);

		imageView = (ImageView) findViewById(R.id.imageView);

		Display display = getWindowManager().getDefaultDisplay();
		int dw = display.getWidth();
		int dh = display.getHeight();
		Bitmap bmp = Bitmap.createBitmap(dw, dh, Bitmap.Config.ARGB_8888);
		canvas = new Canvas(bmp);
		paint = new Paint();
		paint.setColor(Color.RED);
		paint.setStrokeWidth(5);
		paint.setTextSize(20);
		paint.setTypeface(Typeface.DEFAULT_BOLD);
		Path p = new Path();
		p.moveTo(20, 20);
		p.lineTo(100, 150);
		p.lineTo(200, 250);
		canvas.drawTextOnPath("hello, Android", p, 0, 0, paint);
		imageView.setImageBitmap(bmp);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
