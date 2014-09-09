package net.lnmcc.testclickprocess;

import android.app.Activity;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {

	LinearLayout mContainer;
	TextView mTextView;
	int mCount = 0;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		mContainer = (LinearLayout)findViewById(R.id.container);
		mTextView = (TextView)findViewById(R.id.child);
	}
	
	@Override
	protected void onStart() {
		super.onStart();
		mTextView.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				mCount = (++mCount) % 2;
				
				if(mCount == 0)
					mTextView.setText("Clicked !!!");
				else 
					mTextView.setText("Press Me !!!");
			}
		});
		
		mContainer.setOnTouchListener(new OnTouchListener() {
			
			@Override
			public boolean onTouch(View v, MotionEvent event) {
				Toast.makeText(MainActivity.this, "ViewGroup.onTouchEvent", Toast.LENGTH_SHORT).show();
				return false;
			}
		});
	}
	@Override
	public boolean dispatchTouchEvent(MotionEvent ev) {
		super.dispatchTouchEvent(ev);
		return true;
	}
	
	@Override
	public boolean onTouchEvent(MotionEvent event) {
		Toast.makeText(this, "Activity.onTouchEvent", Toast.LENGTH_SHORT).show();
		return true;
	}
	
}
