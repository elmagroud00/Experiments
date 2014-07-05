package com.example.bestprovider;

import java.util.List;

import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.app.Activity;
import android.content.Context;
import android.view.Menu;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
	}
	LocationManager locationManager = getSystemService(Context.LOCATION_SERVICE);

	private void unregisterAllListeners() {
		locationManager.removeUpdates(bestProviderListener);
		locationManager.removeUpdates(bestAvailableProviderListener);
	}
	
	private void registerListener() {
		unregisterAllListeners();
		String bestProvider = locationManager.getBestProvider(criteria, false);
		String bestAvailableProvider = locationManager.getBestProvider(criteria, true);
		
		if(bestProvider == null) {
			Log.d(TAG, "No Location Provider exist on device");
		} else if(bestProvider.equals(bestAvailableProvider)) {
			locationManager.requestLocationUpdates(bestAvailableProvider, minTime, minDistance, bestAvailableProviderListener);
		} else {
			locationManager.requestLocationUpdate(bestProviderm minUpdateTime, minUpdateDistance, bestProviderListener);
		}
		
		if(bestAvailableProvider != null) {
			locationManager.requestLocationUpdates(bestAvailableProvider, minTime, minDistance, bestAvailableProviderListener);
		} else {
			List<String> allProviders = locationManager.getAllProviders();
			for(String provider : allProviders)
				locationManager.requestLocationUpdates(provider, minTime, minDistance, bestProviderListener);
			Log.d(TAG, "No Location Providers currently available.");
		}
	}
	
	private LocationListener bestProviderListener = new LocationListener() {

		@Override
		public void onProviderEnabled(String provider) {
			registerListener();
		}
	};
	
	private LocationListener bestAvailableProviderListener = new LocationListener() {
			
		@Override
		public void onProviderEnabled(String provider) {
			registerListener();
		}
		
	};
	
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
