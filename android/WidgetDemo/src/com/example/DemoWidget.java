package com.example;

import android.appwidget.AppWidgetManager;
import android.appwidget.AppWidgetProvider;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.RemoteViews;

public class DemoWidget extends AppWidgetProvider {

	private static final String tag = "DemoWidget";

	@Override
	public void onDeleted(Context context, int[] appWidgetIds) {
		super.onDeleted(context, appWidgetIds);
		Log.e(tag, "onDelete");
	}

	@Override
	public void onDisabled(Context context) {
		super.onDisabled(context);
		Log.e(tag, "onDisable");
	}

	@Override
	public void onEnabled(Context context) {
		super.onEnabled(context);
		Log.e(tag, "onEnable");
	}

	@Override
	public void onReceive(Context context, Intent intent) {
		super.onReceive(context, intent);
		Log.e(tag, "onReceive");
	}

	@Override
	public void onUpdate(Context context, AppWidgetManager appWidgetManager,
			int[] appWidgetIds) {
		super.onUpdate(context, appWidgetManager, appWidgetIds);

		for (int widgetId : appWidgetIds) {
			update(context, appWidgetManager, widgetId);
		}
		Log.e(tag, "onUpdate");

	}

	public static void update(Context context,
			AppWidgetManager appWidgetManager, int widgetId) {
		
		String title = context.getSharedPreferences(WidgetConfig.PREFS_NAME, 0)
				.getString(WidgetConfig.PREF_TITLE_KEY + widgetId, "");
		RemoteViews views = new RemoteViews(context.getPackageName(),
				R.layout.widget);
		views.setTextViewText(R.id.textView2, title);
		Log.e(tag, "textView: " + title);
		appWidgetManager.updateAppWidget(widgetId, views);
	}

	@Override
	public void onAppWidgetOptionsChanged(Context context,
			AppWidgetManager appWidgetManager, int appWidgetId,
			Bundle newOptions) {
		super.onAppWidgetOptionsChanged(context, appWidgetManager, appWidgetId,
				newOptions);
		Log.e(tag, "onAppWidgetOptionsChanged");
	}
}
