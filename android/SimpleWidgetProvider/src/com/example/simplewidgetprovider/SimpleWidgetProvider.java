package com.example.simplewidgetprovider;

import android.os.Bundle;
import android.app.Activity;
import android.appwidget.AppWidgetManager;
import android.appwidget.AppWidgetProvider;
import android.content.Context;
import android.view.Menu;
import android.widget.RemoteViews;
import android.widget.RemoteViews.RemoteView;

public class SimpleWidgetProvider extends AppWidgetProvider {

	final static int APPWIDGET = 1001;

	@Override
	public void onUpdate(Context context, AppWidgetManager appWidgetManager,
			int[] appWidgetIds) {
		// TODO Auto-generated method stub
		super.onUpdate(context, appWidgetManager, appWidgetIds);
		final int N = appWidgetIds.length;
		for(int i = 0; i < N; i++) {
			int appWidgetId = appWidgetIds[i];
			String titlePrefix = "Time since the widget was started: ";
			updateAppWidget(context, appWidgetManager, appWidgetId, titlePrefix);
		}
	}

	static void updateAppWidget(Context context, AppWidgetManager appWidgetManaget, int appWidetId, String titlePrefix) {
		Long millis = System.currentTimeMillis();
		int seconds = (int)(millis / 1000);
		int minutes = seconds / 60;
	    seconds = seconds % 60;
		String text = titlePrefix;
		text += " " + minutes + " : " + String.format("%02d", seconds);
		
		RemoteViews views = new RemoteViews(context.getPackageName(), R.layout.widget_layout);
		views.setTextViewText(R.id.widget_example_text, text);
		appWidgetManaget.updateAppWidget(appWidetId, views);
	}
}
