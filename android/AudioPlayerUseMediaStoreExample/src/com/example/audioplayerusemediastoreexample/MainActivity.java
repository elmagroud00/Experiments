package com.example.audioplayerusemediastoreexample;

import java.io.File;

import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.R.anim;
import android.app.Activity;
import android.content.Intent;
import android.database.Cursor;
import android.util.Log;
import android.view.Menu;

public class MainActivity extends Activity {

	String[] colums = { MediaStore.Audio.Media.DATA,
			MediaStore.Audio.Media._ID, MediaStore.Audio.Media.TITLE,
			MediaStore.Audio.Media.DISPLAY_NAME,
			MediaStore.Audio.Media.MIME_TYPE, MediaStore.Audio.Media.ARTIST,
			MediaStore.Audio.Media.ALBUM, MediaStore.Audio.Media.IS_RINGTONE,
			MediaStore.Audio.Media.IS_MUSIC, MediaStore.Audio.Media.IS_ALARM,
			MediaStore.Audio.Media.IS_NOTIFICATION };

	Cursor cursor;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		//cursor = managedQuery(MediaStore.Audio.Media.EXTERNAL_CONTENT_URI, colums, null, null, null);
		cursor = getContentResolver().query(MediaStore.Audio.Media.EXTERNAL_CONTENT_URI, colums, null, null, null);
		int fileColumn = cursor.getColumnIndex(MediaStore.Audio.Media.DATA);
		int titleColumn = cursor.getColumnIndex(MediaStore.Audio.Media.TITLE);
		int displayColumn = cursor.getColumnIndex(MediaStore.Audio.Media.DISPLAY_NAME);
		int mimeTypeColumn = cursor.getColumnIndex(MediaStore.Audio.Media.MIME_TYPE);
		
		if(cursor.moveToFirst()) {
			String audioFilePath = cursor.getString(fileColumn);
			String mimeType = cursor.getString(mimeTypeColumn);
			Log.v("AUDIOFILEPATH:", audioFilePath);
			Log.v("AUDIOMEMITYPE", mimeType);
			
			Intent i = new Intent(android.content.Intent.ACTION_VIEW);
			File audioFile = new File(audioFilePath);
			i.setDataAndType(Uri.fromFile(audioFile), mimeType);
			startActivity(i);
		}
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
