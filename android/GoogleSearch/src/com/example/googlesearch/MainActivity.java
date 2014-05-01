package com.example.googlesearch;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.security.NoSuchAlgorithmException;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.os.Bundle;
import android.provider.SearchRecentSuggestions;
import android.app.Activity;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends Activity {

	TextView tv1;
	EditText ed1;
	Button bt1;
	static String url = "https://www.googleapis.com/customsearch/v1?";
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		tv1 = (TextView)findViewById(R.id.display);
		ed1 = (EditText)findViewById(R.id.editText);
		bt1 = (Button)findViewById(R.id.submit);
		
		bt1.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				if(ed1.getText().toString() != null) {
					try {
						ProcessResponse(SearchRequest(ed1.getText().toString()));
					}catch(Exception e) {
						Log.v("Exception google search", "Exception: " + e.getMessage());
					}
				}
				ed1.setText("");
			}
		});
	}

	public String SearchRequest(String searchString)
					throws MalformedURLException, IOException {
		
		String newFeed = url + searchString;
		StringBuilder response = new StringBuilder();
		Log.v("gsearch", "gsearch url:" + newFeed);
		URL url = new URL(newFeed);
		HttpURLConnection httpconn = (HttpURLConnection)url.openConnection();
		if(httpconn.getResponseCode() == HttpURLConnection.HTTP_OK) {
			BufferedReader input = new BufferedReader(new InputStreamReader(httpconn.getInputStream()), 8129);
			String strLine = null;
			while((strLine = input.readLine()) != null) {
				response.append(strLine);
			}
			input.close();
		}
		return response.toString();
	}
	
	public void ProcessResponse(String resp) 
					throws IllegalStateException, IOException, JSONException, NoSuchAlgorithmException {
		StringBuilder sb = new StringBuilder();
		Log.v("gsearch", "gsearch result: " + resp);
		JSONObject mResponseObject = new JSONObject(resp);
		JSONObject responObject = mResponseObject.getJSONObject("responseData");
		JSONArray array = responObject.getJSONArray("results");
		Log.v("gsearch", "number of results: " + array.length());
		for(int i = 0; i < array.length(); i++) {
			Log.v("result", i+ "]" + array.get(i).toString());
			String title = array.getJSONObject(i).getString("title");
			String urllink = array.getJSONObject(i).getString("visibleUrl");
			sb.append(title);
			sb.append("\n");
			sb.append(urllink);
			sb.append("\n");
		}
		tv1.setText(sb.toString());
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
}





















