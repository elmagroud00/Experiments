package com.example.testpolytopoly;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		//setContentView(R.layout.test_poly_to_poly);

		
		/*
		Intent i = new Intent();
		i.setAction(Intent.ACTION_VIEW);
		i.setClassName("com.example.testpolytopoly",
				"com.example.testpolytopoly.MatrixPolyToPolyActivity");
	    startActivity(i);
		*/
		Intent i2 = new Intent();
		i2.setAction(Intent.ACTION_VIEW);
		i2.setClassName(getApplicationContext(),
				"com.example.testpolytopoly.MatrixPolyToPolyWithShadowActivity");
	    startActivity(i2);
	    /*
		Intent i3 = new Intent();
		i3.setClass(getApplicationContext(), SimpleUseActivity.class);
		startActivity(i3);
		*/
	}
}
