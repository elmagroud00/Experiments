package com.example.mylocation;

import java.io.IOException;
import java.util.List;
import java.util.Locale;

import android.location.Address;
import android.location.Criteria;
import android.location.Geocoder;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.app.Activity;
import android.content.Context;
import android.view.Menu;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity implements LocationListener {

	LocationManager mLocationManager;
	Location mLocation;
	TextView tv;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		tv = (TextView) findViewById(R.id.tv1);
		mLocationManager = (LocationManager) getSystemService(Context.LOCATION_SERVICE);
		Criteria criteria = new Criteria();
		criteria.setAccuracy(Criteria.ACCURACY_COARSE);
		criteria.setPowerRequirement(Criteria.POWER_HIGH);
		String locationprovider = mLocationManager.getBestProvider(criteria, true);
		StringBuilder sb = new StringBuilder("geo info: \n");
		
		try {
			mLocation = mLocationManager.getLastKnownLocation(locationprovider);
			if (null != mLocation) {
				
				sb.append("Lat: ").append(mLocation.getLatitude()).append("Long: ")
						.append(mLocation.getLongitude());
				tv.setText(sb.toString());
			} else {
				tv.setText("No location information");
			}
		} catch (Exception e) {
			tv.setText(e.getMessage());
		}


		/*
		 * List<String> providers = mLocationManager.getProviders(true);
		 * StringBuilder mSB = new StringBuilder("Providers: \n");
		 * 
		 * for(int i = 0; i < providers.size(); i++) {
		 * mLocationManager.requestLocationUpdates(providers.get(i), 5000, 2.0f,
		 * new LocationListener() {
		 * 
		 * @Override public void onStatusChanged(String provider, int status,
		 * Bundle extras) { // TODO Auto-generated method stub
		 * 
		 * }
		 * 
		 * @Override public void onProviderEnabled(String provider) { // TODO
		 * Auto-generated method stub
		 * 
		 * }
		 * 
		 * @Override public void onProviderDisabled(String provider) { // TODO
		 * Auto-generated method stub
		 * 
		 * }
		 * 
		 * @Override public void onLocationChanged(Location location) { // TODO
		 * Auto-generated method stub
		 * 
		 * } }); mSB.append(providers.get(i)).append(": \n"); mLocation =
		 * mLocationManager.getLastKnownLocation(providers.get(i)); if(mLocation
		 * != null) { mSB.append(mLocation.getLatitude()).append(" , ");
		 * mSB.append(mLocation.getLongitude()).append(" \n"); } else {
		 * mSB.append("Location can not be found"); } }
		 * tv.setText(mSB.toString());
		 */
		/*
		 * List<Address> addresses;
		 * 
		 * try{ Geocoder mGC = new Geocoder(this, Locale.ENGLISH); addresses =
		 * mGC.getFromLocation(mLocation.getLatitude(),
		 * mLocation.getLongitude(), 1);
		 * 
		 * if(addresses != null) { Address currentAddr = addresses.get(0);
		 * StringBuilder mSB = new StringBuilder("Address: \n"); for(int i = 0;
		 * i < currentAddr.getMaxAddressLineIndex(); i++) {
		 * mSB.append(currentAddr.getAddressLine(i)).append("\n"); }
		 * tv.setText(mSB.toString()); } else { Toast.makeText(this,
		 * "Address is null", Toast.LENGTH_SHORT).show(); } }catch(IOException
		 * e) { tv.setText(e.getMessage()); }catch(NullPointerException e) {
		 * tv.setText(e.getMessage()); }
		 */
	}

	@Override
	public void onLocationChanged(Location location) {
		mLocation = location;
		showupdate();
	}

	@Override
	public void onProviderDisabled(String provider) {
		// TODO Auto-generated method stub

	}

	@Override
	public void onProviderEnabled(String provider) {
		// TODO Auto-generated method stub

	}

	@Override
	public void onStatusChanged(String provider, int status, Bundle extras) {
		// TODO Auto-generated method stub

	}

	public void showupdate() {
		tv.setText("Last location lat: " + mLocation.getLatitude() + "long: "
				+ mLocation.getLongitude());
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
