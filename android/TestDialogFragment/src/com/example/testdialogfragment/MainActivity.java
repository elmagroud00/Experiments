package com.example.testdialogfragment;

import java.sql.Date;
import java.text.SimpleDateFormat;

import android.app.Activity;
import android.app.DialogFragment;
import android.os.Bundle;

public class MainActivity extends Activity {
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

	}

	@Override
	protected void onResume() {
		SimpleDateFormat sdf = new SimpleDateFormat("HH:mm:ss");
		Date currentTime = new Date(System.currentTimeMillis());
		String dateString = sdf.format(currentTime);
		String tag = "my_dialog";
		DialogFragment myFragment = MyDialogFragment.newInstance(dateString);
		myFragment.show(getFragmentManager(), tag);
		super.onResume();
	}
}