package com.example.shownotification;

import java.io.NotActiveException;

import android.net.Uri;
import android.os.Bundle;
import android.app.Activity;
import android.app.Application;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.view.Menu;
import android.view.View;
import android.widget.Button;

public class ShowNotification extends Activity {
	
	private NotificationManager mNManager;
	private static final int NOTIFY_ID = 1100;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_show_notification);
		
		String ns = Context.NOTIFICATION_SERVICE;
		mNManager = (NotificationManager)getSystemService(ns);
		final Notification msg =  new Notification(R.drawable.ic_launcher, "New event of importance", System.currentTimeMillis());
		Button start = (Button)findViewById(R.id.start);
		Button cancel = (Button)findViewById(R.id.cancel);
		
		start.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				Context context = getApplicationContext();
				CharSequence contentTitle = "ShowNotigication Example";
				CharSequence contentText = "Broswe Android Cookbook site";
				Intent msgIntent = new Intent(Intent.ACTION_VIEW, Uri.parse("http://lnmcc.net"));
				PendingIntent intent = PendingIntent.getActivity(ShowNotification.this, 0, msgIntent, Intent.FLAG_ACTIVITY_NEW_TASK);
				msg.defaults |= Notification.DEFAULT_SOUND;
				msg.defaults |= Notification.FLAG_AUTO_CANCEL;
				
				msg.setLatestEventInfo(context, contentTitle, contentText, intent);
				mNManager.notify(NOTIFY_ID, msg);
			}
		});
		
		cancel.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				mNManager.cancel(NOTIFY_ID);
			}
		});
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.show_notification, menu);
		return true;
	}

}

