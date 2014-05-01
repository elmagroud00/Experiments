package com.example.listactivityexample;

import android.net.Uri;
import android.os.Bundle;
import android.app.Activity;
import android.app.ListActivity;
import android.app.SearchManager;
import android.content.Intent;
import android.view.Menu;
import android.view.View;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;

public class MainActivity extends ListActivity {

	static final String[] ACTIVITY_CHOICES = new String[] {
		"Open Website Exaple",
		"Open Contacts",
		"Open Phone Dialer Example",
		"Search Google Example",
		"Start Voice Command"
	};
	final String searchTerms = "superman";
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		setListAdapter(new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, ACTIVITY_CHOICES));
		
		getListView().setChoiceMode(ListView.CHOICE_MODE_SINGLE);
		getListView().setTextFilterEnabled(true);
		getListView().setOnItemClickListener(new OnItemClickListener() {
			@Override
			public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
					long arg3) {
				switch(arg2) {
				case 0:
					startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse("htp://lnmcc.net")));
					break;
				case 1:
					startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse("content://contacts/people")));
					break;
				case 2:
					startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse("tel:10080")));
					break;
				case 3:
					Intent intent = new Intent(Intent.ACTION_WEB_SEARCH);
					intent.putExtra(SearchManager.QUERY, searchTerms);
					startActivity(intent);
					break;
				case 4:
					startActivity(new Intent(Intent.ACTION_VOICE_COMMAND));
					break;
				default:
					break;
				}
			}
		});
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
