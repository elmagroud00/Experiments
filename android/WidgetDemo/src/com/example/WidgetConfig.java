package com.example;

import android.app.Activity;
import android.appwidget.AppWidgetManager;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class WidgetConfig extends Activity {

	private static final String tag = "WidgetConfig";
	public static final String PREFS_NAME = "WidgetDemo";
	public static final String PREF_TITLE_KEY = "title_";
	private static final String Tag = "WidgetConfig";

	private EditText etInput;
	private Button btnOK;
	private int mAppWidgetId = AppWidgetManager.INVALID_APPWIDGET_ID;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setResult(RESULT_CANCELED);
		setContentView(R.layout.config);
		etInput = (EditText) findViewById(R.id.editText);
		btnOK = (Button) findViewById(R.id.button);

		Intent intent = getIntent();
		Bundle extras = intent.getExtras();
		if (extras != null) {
			mAppWidgetId = extras.getInt(AppWidgetManager.EXTRA_APPWIDGET_ID,
					AppWidgetManager.INVALID_APPWIDGET_ID);
		}
		Log.e(tag, "mAppWidgetId: " + mAppWidgetId);
		if (mAppWidgetId == AppWidgetManager.INVALID_APPWIDGET_ID) {
			Log.e(Tag, "no appwidgetId");
			finish();
		}
		etInput.setText(loadTitlePref(mAppWidgetId));
		btnOK.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				String title = etInput.getText().toString();
				saveTitlePref(mAppWidgetId, title);
				Intent resultValue = new Intent();
				resultValue.putExtra(AppWidgetManager.EXTRA_APPWIDGET_ID,
						mAppWidgetId);
				setResult(RESULT_OK, resultValue);

				Context context = WidgetConfig.this;
				AppWidgetManager appWidgetManager = AppWidgetManager
						.getInstance(context);
				DemoWidget.update(context, appWidgetManager, mAppWidgetId);
				finish();
			}
		});
	}

	private void saveTitlePref(int appWidgetId, String text) {
		SharedPreferences.Editor prefs = getSharedPreferences(PREFS_NAME, 0)
				.edit();
		prefs.putString(PREF_TITLE_KEY + appWidgetId, text);
		prefs.commit();
	}

	private String loadTitlePref(int appWidgetId) {
		SharedPreferences prefs = getSharedPreferences(PREFS_NAME, 0);
		String prefix = prefs.getString(PREF_TITLE_KEY + appWidgetId, null);
		if (prefix != null) {
			return prefix;
		} else {
			return "Default Text";
		}
	}
}
