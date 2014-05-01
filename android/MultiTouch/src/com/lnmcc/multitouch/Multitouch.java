package com.lnmcc.multitouch;

import android.os.Bundle;
import android.app.Activity;
import android.graphics.Matrix;
import android.util.Log;
import android.view.Menu;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.ImageView;
import android.widget.Toast;

public class Multitouch extends Activity implements OnTouchListener{

	Matrix matrix = new Matrix();
	Matrix eventMatrix = new Matrix();
	
	final static int NONE = 0;
	final static int DRAG = 1;
	final static int ZOOM = 2;
	int touchState = NONE;
	
	final static int MIN_DIST = 50;
	static float eventDistance = 0;
	static float centerX = 0, centerY = 0;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_multitouch);
		
		ImageView view = (ImageView)findViewById(R.id.imageView);
		view.setOnTouchListener(this);
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.multitouch, menu);
		return true;
	}

	@Override
	public boolean onTouch(View arg0, MotionEvent arg1) {
		ImageView view = (ImageView)arg0;

		view.setImageMatrix(matrix);
		switch(arg1.getAction() & MotionEvent.ACTION_MASK) {
		case MotionEvent.ACTION_DOWN:
			touchState = DRAG;
			centerX = arg1.getX(0);
			centerY = arg1.getY(0);
			eventMatrix.set(matrix);
			break;
		case MotionEvent.ACTION_POINTER_DOWN:
			eventDistance = calcDistance(arg1);
			calcMidpoint(centerX, centerY, arg1);
			if(eventDistance > MIN_DIST) {
				eventMatrix.set(matrix);
				touchState = ZOOM;
			}
			break;
		case MotionEvent.ACTION_MOVE:
			if(touchState == DRAG) {
				matrix.set(eventMatrix);
				matrix.setTranslate(arg1.getX(0) - centerX, arg1.getY(0) - centerY);
			} else if(touchState == ZOOM) {
				float dist = calcDistance(arg1);
				if(dist > MIN_DIST) {
					matrix.set(eventMatrix);
					float scale = dist / eventDistance;
					matrix.postScale(scale, scale, centerX, centerY);
				}
			}
			view.setImageMatrix(matrix);

			break;
		case MotionEvent.ACTION_UP:
		case MotionEvent.ACTION_POINTER_UP:
			touchState = NONE;
			break;
		}

		return true;
	}
	
	private float calcDistance(MotionEvent event) {
		float x = event.getX(0) - event.getX(1);
		float y = event.getY(0) - event.getY(1);
		return (float) Math.sqrt(x * x + y * y);
	}
	
	private void calcMidpoint(float centerX, float centerY, MotionEvent event) {
		centerX = (event.getX(0) + event.getX(1)) / 2;
		centerY = (event.getY(0) + event.getY(1)) / 2;
	}
}






