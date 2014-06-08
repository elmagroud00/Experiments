package com.example.livewallpaper;

import android.os.Bundle;
import android.app.Activity;
import android.service.wallpaper.WallpaperService;
import android.view.Menu;

public class LiveWallpaper extends WallpaperService {
	@Override
	public Engine onCreateEngine() {
		return new LiveWallpaperEnginer();
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
