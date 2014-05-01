package net.lnmcc.diary;

import java.util.ArrayList;
import java.util.Date;

import com.example.diary.R;

import net.lnmcc.data.Contants;
import net.lnmcc.data.MyDB;


import android.app.Activity;
import android.app.ListActivity;
import android.content.Context;
import android.database.Cursor;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

public class DisplayDiaries extends ListActivity {

	MyDB dba;
	DiaryAdapter myAdapter;

	private class MyDiary {

		public String title;
		public String content;
		public String recorddate;

		public MyDiary(String t, String c, String r) {
			title = t;
			content = c;
			recorddate = r;
		}
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		dba = new MyDB(this);
		dba.open();
		super.onCreate(savedInstanceState);
		setContentView(R.layout.diaries);
		myAdapter = new DiaryAdapter(this);
		this.setListAdapter(myAdapter);
	}
	
	private class DiaryAdapter extends BaseAdapter {
		private LayoutInflater mInflater;
		private ArrayList<MyDiary> diaries;

		public DiaryAdapter(Context context) {
			mInflater = LayoutInflater.from(context);
			diaries = new ArrayList<MyDiary>();
			getdata();
		}

		public void getdata() {
			Cursor c = dba.getdiaries();
			startManagingCursor(c);
			if (c.moveToNext()) {
				do {
					String title = c.getString(c
							.getColumnIndex(Contants.TITLE_NAME));
					String content = c.getString(c
							.getColumnIndex(Contants.CONTENT_NAME));
					long datel = c
							.getLong(c.getColumnIndex(Contants.DATE_NAME));
					Date date = new Date(datel);
					java.text.DateFormat dateFormat = java.text.DateFormat
							.getDateInstance();
					String datedata = dateFormat.format(date.getTime());
					MyDiary temp = new MyDiary(title, content, datedata);
					diaries.add(temp);
				} while (c.moveToNext());
			}
		}

		@Override
		public int getCount() {
			return diaries.size();
		}
		
		@Override
		public MyDiary getItem(int position) {
			return diaries.get(position);
		}
		
		@Override
		public long getItemId(int position) {
			return position;
		}
		
		public class ViewHolder {
			MyDiary mdiary;
			TextView mTitle;
			TextView mDate;
		}
		
		@Override
		public View getView(int position, View convertView, ViewGroup parent) {
			final ViewHolder holder;
			View v = convertView;
			if((v == null) || (v.getTag() == null)) {
				v = mInflater.inflate(R.layout.diaryrow, null);
				holder = new ViewHolder();
				holder.mTitle = (TextView)v.findViewById(R.id.name);
				holder.mDate = (TextView)v.findViewById(R.id.datetext);
				v.setTag(holder);
			} else {
				holder = (ViewHolder)convertView.getTag();
			}
			
			holder.mdiary = getItem(position);
			holder.mTitle.setText(holder.mdiary.title);
			holder.mDate.setText(holder.mdiary.recorddate);
			
			v.setTag(holder);
			return v;
		}
	}
}





















