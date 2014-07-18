package net.lnmcc.testfindview;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends Activity {

	TextView tv;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		tv = (TextView)findViewById(R.id.tv);
	}
	
	@Override
	protected void onResume() {
		super.onResume();
		tv.setText("Changed");
	}
}
