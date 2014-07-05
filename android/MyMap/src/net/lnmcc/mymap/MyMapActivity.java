package net.lnmcc.mymap;

import android.R;
import android.os.Bundle;

import com.google.android.maps.MapActivity;
import com.google.android.maps.MapController;
import com.google.android.maps.MapView;

public class MyMapActivity extends MapActivity {
	private MapView mapView;
	private MapController mapController;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		setContentView(R.layou);
		mapView = (MapView) findViewById(R.id.map_view);
	}

	@Override
	protected boolean isRouteDisplayed() {
		return true;
	}

}