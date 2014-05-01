package com.example.twittercookbook;

import twitter4j.ResponseList;
import twitter4j.Status;
import twitter4j.Twitter;
import android.app.ListActivity;
import android.content.Context;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class UpdateAndList extends ListActivity {

	EditText userET;
	Button updateBT;
	Twitter twitter;
	ResponseList<Status> userTimeline;
	UserTimeLineAdapter myAdapter;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_twitter_cook_book);
		userET = (EditText)findViewById(R.id.userStatus);
		updateBT = (Button)findViewById(R.id.updateButton);
		twitter = TwitterCookBook.twitter;
		setup stup = new setup();
		stup.execute();
		
		updateBT.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				try {
					twitter.updateStatus(userET.getText().toString());
					loadstatus ldstatus = new loadstatus();
					ldstatus.execute();
					userET.setText("");
				} catch(Exception e) {
					e.printStackTrace();
				}
			}
		});
	}
	
	private class UserTimeLineAdapter extends BaseAdapter {
		private LayoutInflater mInflater;

		public UserTimeLineAdapter(Context context) {
			mInflater = LayoutInflater.from(context);
		}

		@Override
		public int getCount() {
			return userTimeline.size();
		}

		@Override
		public Status getItem(int position) {
			return userTimeline.get(position);
		}

		@Override
		public long getItemId(int position) {
			return position;
		}

		@Override
		public View getView(int position, View convertView, ViewGroup parent) {
			final ViewHolder holder;
			View v = convertView;
			if ((v == null) || (v.getTag() == null)) {
				v = mInflater.inflate(R.layout.user_timeline_row, null);
				holder = new ViewHolder();
				holder.mName = (TextView) v.findViewById(R.id.name);
				holder.mStatus = (TextView) v.findViewById(R.id.msg);
				v.setTag(holder);
			} else {
				holder = (ViewHolder) v.getTag();
			}
			holder.status = getItem(position);
			holder.mName.setText(holder.status.getUser().getName());
			holder.mStatus.setText(holder.status.getText());
			v.setTag(holder);
			return v;
		}

		public class ViewHolder {
			Status status;
			TextView mName;
			TextView mStatus;
		}
	}

	private class setup extends AsyncTask<String, Integer, String> {
		@Override
		protected String doInBackground(String... params) {
			try {
				userTimeline = twitter.getHomeTimeline();
				return " ";
			} catch(Exception e) {
				Log.v("Exception Twitter query", "Exception: " + e.getMessage());
				return " ";
			}
		}
		
		@Override
		protected void onPostExecute(String result) {
			try {
				myAdapter = new UserTimeLineAdapter(UpdateAndList.this);
				UpdateAndList.this.setListAdapter(myAdapter);
			} catch(Exception e) {
				Log.v("Exception Twitter query", "Exception: " + e.getMessage());
			}
		}
	}
	
	private class loadstatus extends AsyncTask<String, Integer, String> {
		@Override
		protected String doInBackground(String... params) {
			try {
				userTimeline = twitter.getHomeTimeline();
				return " "; 
			} catch(Exception e) {
				Log.v("Exception Twitter query", "Exception: " + e.getMessage());
				return " ";
			}
		}
		
		@Override
		protected void onPostExecute(String result) {
			try {
				myAdapter.notifyDataSetChanged();
			}catch(Exception e) {
				Log.v("Exception twitter query", "Exception: " + e.getMessage());
			}
		}
	}
	
}























