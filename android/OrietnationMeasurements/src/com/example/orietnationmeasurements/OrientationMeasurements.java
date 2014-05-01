package com.example.orietnationmeasurements;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.widget.TextView;

public class OrientationMeasurements extends Activity {

	private SensorManager myManager = null;
	TextView tv;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_orientation_measurements);
		tv = (TextView)findViewById(R.id.attitude);
		myManager = (SensorManager)getSystemService(SENSOR_SERVICE);
		myManager.registerListener(mySensorListener, myManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER),
				SensorManager.SENSOR_DELAY_GAME);
		myManager.registerListener(mySensorListener, myManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD),
				SensorManager.SENSOR_DELAY_GAME);
	}
	
	float[] mags = new float[3];
	float[] accels = new float[3];
	float[] RotationMat = new float[9];
	float[] InclinationMat = new float[9];
	float[] attitude = new float[3];
	final static double RAD2DEG = 180 / Math.PI;
	private final SensorEventListener mySensorListener = new SensorEventListener() {
		
		@Override
		public void onSensorChanged(SensorEvent event) {
			int type = event.sensor.getType();
			if(type == Sensor.TYPE_MAGNETIC_FIELD) {
				mags = event.values;
			}
			if(type == Sensor.TYPE_ACCELEROMETER) {
				accels = event.values;
			}
			if(type == Sensor.TYPE_TEMPERATURE) {
				
			}
			
			
			
			SensorManager.getRotationMatrix(RotationMat, InclinationMat, accels, mags);
			SensorManager.getOrientation(RotationMat, attitude);
			tv.setText("Azimuth, Pitch, Roll: \n" +
					attitude[0] * RAD2DEG + "\n"
					+ attitude[1] * RAD2DEG + "\n"
					+ attitude[2] * RAD2DEG);
		}
		
		
		@Override
		public void onAccuracyChanged(Sensor sensor, int accuracy) {
			// TODO Auto-generated method stub
			
		}
	};

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.orientation_measurements, menu);
		return true;
	}

}
