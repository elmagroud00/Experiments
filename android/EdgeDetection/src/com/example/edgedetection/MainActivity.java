package com.example.edgedetection;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity implements Runnable {

	int numberOfTimesPressd = 0;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		final TextView tv = (TextView)findViewById(R.id.text);
		Thread thread = new Thread(MainActivity.this);
		thread.start();
		
		Button startButton = (Button)findViewById(R.id.trigger);
		startButton.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				tv.setText("Pressed Button" + ++numberOfTimesPressd + " times\nAnd compution loop at "
						+"(" + xi + ", " + yi  + ") pixels");
			}
		});
		
	}

	@Override
	public void run() {
		detectEdge();
	}
	
	int xi;
	int yi;
	
	private double detectEdge() {
		int x_pixels = 4000;
		int y_pixels = 3000;
		double image_transfor = 0;
		for(xi = 0; xi < x_pixels; xi++) {
			for(yi = 0; yi < y_pixels; yi++) {
				image_transfor = Math.cosh(xi * yi / x_pixels / y_pixels);
			}
		}
		return image_transfor;
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
