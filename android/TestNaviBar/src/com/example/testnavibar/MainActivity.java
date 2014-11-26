package com.example.testnavibar;

import android.app.Activity;
import android.content.Context;
import android.graphics.Point;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.view.Display;
import android.view.Menu;
import android.view.MenuItem;
import android.view.WindowManager;
import android.widget.Toast;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    @Override
    public void onWindowFocusChanged(boolean hasFocus) {
        super.onWindowFocusChanged(hasFocus);
        if (isNavigationBottom()) {
            Toast.makeText(this, "NavigationBar is at bottom", Toast.LENGTH_LONG)
                    .show();
        }
    }

    public boolean isNavigationBottom() {
        WindowManager wm;
        Display display;
        DisplayMetrics realSize;
        DisplayMetrics windowSize;

        realSize = new DisplayMetrics();
        windowSize = new DisplayMetrics();
        wm = (WindowManager) getSystemService(Context.WINDOW_SERVICE);
        display = wm.getDefaultDisplay();

        display.getRealMetrics(realSize);
        display.getMetrics(windowSize);

        if (windowSize.heightPixels != realSize.heightPixels)
            return true;
        else
            return false;
    }
}
