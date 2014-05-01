package com.example.datastoragetester;

import android.net.Uri;
import android.os.Bundle;
import android.app.Activity;
import android.content.ContentResolver;
import android.database.Cursor;
import android.view.Menu;
import android.widget.TextView;

public class MainActivity extends Activity {

	TextView tv;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		tv = (TextView)findViewById(R.id.output);
		String myUri = "content://net.lnmcc.data/diaries";
		Uri CONTENT_URI = Uri.parse(myUri);
		ContentResolver crInstance = getContentResolver();
		Cursor c = crInstance.query(CONTENT_URI, null, null, null, null);
		startManagingCursor(c);
		StringBuilder sb = new StringBuilder();
		if(c.moveToFirst()) {
			do{
				sb.append(c.getString(1)).append("\n");
			} while(c.moveToNext());
		}
		tv.setText(sb.toString());
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
