package com.example.audioexample;

import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;

import android.app.ListActivity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.ListView;

public class ListFiles extends ListActivity {

	private List<String> directroyEntries = new ArrayList<String>();

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		Intent i = getIntent();
		File directroy = new File(i.getStringExtra("directory"));
		
		if(directroy.isDirectory()) {
			File[] files = directroy.listFiles();
			
			Arrays.sort(files, new Comparator<File>() {
				@Override
				public int compare(File lhs, File rhs) {
					return -Long.valueOf(lhs.lastModified()).compareTo(rhs.lastModified());
				}
			});
			directroyEntries.clear();
			for(File file : files) {
				directroyEntries.add(file.getPath());
			}
			ArrayAdapter<String> directoryList = new ArrayAdapter<String>(this, R.layout.file_row, directroyEntries);
			setListAdapter(directoryList);
		}
	}
	
	@Override
	protected void onListItemClick(ListView l, View v, int position, long id) {
		File clickedFile = new File(directroyEntries.get(position));
		Intent i = getIntent();
		i.putExtra("clickedFile", clickedFile.toString());
		setResult(RESULT_OK, i);
		finish();
	}
}
