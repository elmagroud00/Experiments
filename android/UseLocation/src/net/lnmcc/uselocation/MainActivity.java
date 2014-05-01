package net.lnmcc.uselocation;

import android.location.Location;
import android.location.LocationManager;
import android.os.Bundle;
import android.app.Activity;
import android.app.PendingIntent;
import android.view.Menu;
import android.widget.TextView;

public class MainActivity extends Activity {
	private static final String LOG_TAG = "UseLocation";
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		PendingIntent
		
		LocationManager lm = (LocationManager) getSystemService(LOCATION_SERVICE);
		Location loc = lm.getLastKnownLocation(LocationManager.GPS_PROVIDER);
		displayLocation(loc);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	private void displayLocation(Location loc) {
		if(loc == null) {
			((TextView)findViewById(R.id.main_tv_latitude)).setText("latitude N/A");
			((TextView)findViewById(R.id.main_tv_longitude)).setText("longtitude N/A");
			((TextView)findViewById(R.id.main_tv_altitude)).setText("altitude N/A");
			return;
		}
		((TextView)findViewById(R.id.main_tv_latitude)).setText("latitude" + loc.getLatitude());
		((TextView)findViewById(R.id.main_tv_longitude)).setText("longtitude" + loc.getLongitude());
		((TextView)findViewById(R.id.main_tv_altitude)).setText("altitude" + loc.getAltitude());
		((TextView)findViewById(R.id.main_tv_supprimental_info)).setText("Provider = "
				+ loc.getProvider() + "\n" + "Time = " + loc.getTime() + "\n"
				+ loc.getAccuracy() + "\n" + "Speed = " + loc.getSpeed() + "\n"
				+ "Bearing = "
				+ loc.getBearing() + "\n");

	}
}












