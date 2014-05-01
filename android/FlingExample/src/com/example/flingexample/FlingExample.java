package com.example.flingexample;

import android.os.Bundle;
import android.app.Activity;
import android.view.GestureDetector;
import android.view.Menu;
import android.view.MotionEvent;
import android.widget.TextView;

public class FlingExample extends Activity {
	
	private static final int LARGE_MOVE = 60;
	private GestureDetector gestureDetector;
	TextView tv;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_fling_example);
		tv = (TextView)findViewById(R.id.text_result);
		gestureDetector = new GestureDetector(this, new GestureDetector.OnGestureListener() {
			
			@Override
			public boolean onSingleTapUp(MotionEvent e) {
				// TODO Auto-generated method stub
				return false;
			}
			
			@Override
			public void onShowPress(MotionEvent e) {
				// TODO Auto-generated method stub
				
			}
			
			@Override
			public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX,
					float distanceY) {
				// TODO Auto-generated method stub
				return false;
			}
			
			@Override
			public void onLongPress(MotionEvent e) {
				// TODO Auto-generated method stub
				
			}
			
			@Override
			public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX,
					float velocityY) {
				if(e1.getY() - e2.getY() > LARGE_MOVE) {
					tv.append("\nFling Up woth velocityY" + velocityY);
					return true;
				} else if(e2.getY() - e1.getY() > LARGE_MOVE) {
					tv.append("\nFling Down with velocity " + velocityY);
					return true;
				} else if(e1.getX() - e2.getX() > LARGE_MOVE) {
					tv.append("\nFling Left with velocityX" + velocityX);
					return true;
				} else if(e2.getX() - e1.getX() > LARGE_MOVE) {
					tv.append("\nFling Right with velocityX" + velocityX);
				}
				
				return false;
			}
			
			@Override
			public boolean onDown(MotionEvent e) {
				// TODO Auto-generated method stub
				return false;
			}
		} );
	}
	
	@Override
	public boolean onTouchEvent(MotionEvent event) {
		return gestureDetector.onTouchEvent(event);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.fling_example, menu);
		return true;
	}

}
