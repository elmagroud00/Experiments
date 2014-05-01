package net.lnmcc.usejni;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.widget.TextView;

public class MainActivity extends Activity {

	static {
		System.loadLibrary("useJNI");
	}
	
	public native String getStringFromNative();
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		String strResult = getStringFromNative();
		
		TextView tv = (TextView)findViewById(R.id.tvResult);
		tv.setText(strResult);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
