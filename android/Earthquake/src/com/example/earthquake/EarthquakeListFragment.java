package com.example.earthquake;

import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLConnection;
import java.util.ArrayList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;

import android.app.ListFragment;
import android.os.Bundle;
import android.os.Handler;
import android.widget.ArrayAdapter;

public class EarthquakeListFragment extends ListFragment {

	ArrayAdapter<Quake> aa;
	ArrayList<Quake> earthquakes = new ArrayList<Quake>();
	private static final String TAG = "EARTHQUAKE";
	private Handler handler = new Handler();

	@Override
	public void onActivityCreated(Bundle savedInstanceState) {
		super.onActivityCreated(savedInstanceState);

		int layoutID = android.R.layout.simple_list_item_1;
		aa = new ArrayAdapter<Quake>(getActivity(), layoutID, earthquakes);
		setListAdapter(aa);
	}

	public void refreshEarthquakes() {
		URL url;
		try {
			String quakeFeed = getString(R.string.quake_feed);
			url = new URL(quakeFeed);
			URLConnection	connection;
			connection = url.openConnection();
			HttpURLConnection httpConnection = (HttpURLConnection)connection;
			int responseCode = httpConnection.getResponseCode();
			if(responseCode == HttpURLConnection.HTTP_OK) {
				InputStream in = httpConnection.getInputStream();
				DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
				DocumentBuilder db = dbf.newDocumentBuilder();
				
				Document dom = db.parse(in);
				Element docEle = dom.getDocumentElement();
				earthquakes.clear();
				
				NodeList nl = docEle.getElementsByTagName("entry");
				if(nl != null && nl.getLength() > 0) {
					for(int i = 0; i < nl.getLength(); i++) {
						Element entry = (Element)nl.item(i);
						Element title = (Element)entry.getel
					}
				}
				
			}
		}
	}
}
