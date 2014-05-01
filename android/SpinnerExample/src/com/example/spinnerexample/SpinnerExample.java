package com.example.spinnerexample;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.widget.ArrayAdapter;
import android.widget.Spinner;

public class SpinnerExample extends Activity {

	private static final String[] oceans = {
		"pacific", "Atlantic", "Indian", "Arctic", "Southern"
	};
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.spinner);
		
		Spinner favoriateOcean = (Spinner)findViewById(R.id.spinner);
		ArrayAdapter<String> mAdapter = new ArrayAdapter<String>(this, R.layout.spinner_entry,  oceans);
		mAdapter.setDropDownViewResource(R.layout.spinner_entry);
		favoriateOcean.setAdapter(mAdapter);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.spinner_example, menu);
		return true;
	}

}
