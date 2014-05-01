package com.example.mybrowser;

import java.util.ArrayList;
import java.util.HashMap;

import com.example.mybroswer.R;
import com.example.mybroswer.R.id;

import android.app.Activity;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.graphics.Color;
import android.os.Bundle;
import android.view.Gravity;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.AdapterView;
import android.widget.GridView;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.SimpleAdapter;

public class History extends Activity {
	private GridView gridView;
	private RelativeLayout bookMarkRL;
	private RelativeLayout historyRL;
	private ListView bookMarkLV;
	private ListView historyLV;
	private SQLiteDatabase db;
	private DBHelper dbHelper;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
				WindowManager.LayoutParams.FLAG_FULLSCREEN);
		setContentView(R.layout.history);

		bookMarkRL = (RelativeLayout) findViewById(R.id.BookMarkRelativeLayout);
		historyRL = (RelativeLayout) findViewById(R.id.HistoryRelativeLayout);
		bookMarkLV = (ListView) findViewById(R.id.BookMarkListView);
		historyLV = (ListView) findViewById(R.id.HistoryListView);
		historyLV.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				
			}
		});

		dbHelper = new DBHelper(this, DBHelper.DATABASE_NAME, null,
				DBHelper.DATABASE_VERSION);
		db = dbHelper.getWritableDatabase();
		createGridView();
	}

	private void createGridView() {
		gridView = (GridView) findViewById(R.id.GridView01);

		ArrayList<HashMap<String, String>> arrayList = new ArrayList<HashMap<String, String>>();
		HashMap<String, String> hashMap = new HashMap<String, String>();
		hashMap.put("item", "??????");
		arrayList.add(hashMap);
		hashMap = new HashMap<String, String>();
		hashMap.put("item", "??????");
		arrayList.add(hashMap);
		SimpleAdapter simpleAdapter = new SimpleAdapter(this, arrayList,
				R.layout.grid_item, new String[] { "item" },
				new int[] { R.id.TextView01 });
		gridView.setAdapter(simpleAdapter);

		gridView.setOnItemClickListener(new AdapterView.OnItemClickListener() {

			@Override
			public void onItemClick(AdapterView<?> parent, View view,
					int position, long id) {

				switch (position) {
				case 0:
					bookMarkRL.setVisibility(View.VISIBLE);
					historyRL.setVisibility(View.GONE);
					fetchBookMarkData();
					break;
				case 1:
					bookMarkRL.setVisibility(View.GONE);
					historyRL.setVisibility(View.VISIBLE);
					fetchHistoryData();
					break;
				default:
					break;
				}
			}
		});
	}

	private void fetchBookMarkData() {
		ArrayList<HashMap<String, String>> arrayList = new ArrayList<HashMap<String, String>>();
		HashMap<String, String> hashMap;
		String[] columns = { DBHelper.WEB_TITLE_COLUM, DBHelper.WEB_URL_COLUM };
		Cursor cursor = db.query(DBHelper.TABLE_BOOKMARK, columns, null, null,
				null, null, null);
		int titleIdx = cursor.getColumnIndexOrThrow(DBHelper.WEB_TITLE_COLUM);
		int urlIdx = cursor.getColumnIndexOrThrow(DBHelper.WEB_URL_COLUM);

		cursor.moveToFirst();
		while (cursor.moveToNext()) {
			hashMap = new HashMap<String, String>();
			String title = cursor.getString(titleIdx);
			String url = cursor.getString(urlIdx);
			hashMap.put("title", title);
			hashMap.put("url", url);
			arrayList.add(hashMap);
		}
		cursor.close();

		String[] from = new String[] { "title", "url" };
		int[] to = new int[] { R.id.list_title, R.id.list_url };
		SimpleAdapter adapter = new SimpleAdapter(this, arrayList,
				R.layout.list_item, from, to);
		bookMarkLV.setAdapter(adapter);
	}

	private void fetchHistoryData() {
		ArrayList<HashMap<String, String>> arrayList = new ArrayList<HashMap<String, String>>();
		HashMap<String, String> hashMap;

		String[] columns = { DBHelper.WEB_TITLE_COLUM, DBHelper.WEB_URL_COLUM };
		Cursor cursor = db.query(DBHelper.TABLE_HISTORY, columns, null, null,
				null, null, null);
		int titleIdx = cursor.getColumnIndexOrThrow(DBHelper.WEB_TITLE_COLUM);
		int urlIdx = cursor.getColumnIndexOrThrow(DBHelper.WEB_URL_COLUM);

		cursor.moveToFirst();
		while (cursor.moveToNext()) {
			hashMap = new HashMap<String, String>();
			String title = cursor.getString(titleIdx);
			String url = cursor.getString(urlIdx);
			hashMap.put("title", title);
			hashMap.put("url", url);
			arrayList.add(hashMap);
		}
		cursor.close();

		String[] from = new String[] { "title", "url" };
		int[] to = new int[] { R.id.list_title, R.id.list_url };
		SimpleAdapter adapter = new SimpleAdapter(this, arrayList,
				R.layout.list_item, from, to);
		historyLV.setAdapter(adapter);
	}

	@Override
	protected void onDestroy() {
		db.close();
		super.onDestroy();
	}
}
