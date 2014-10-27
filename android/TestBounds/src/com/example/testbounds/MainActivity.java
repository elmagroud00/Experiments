package com.example.testbounds;

import android.app.Activity;
import android.graphics.Rect;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View.OnFocusChangeListener;
import android.widget.Toast;

public class MainActivity extends Activity {

    Rect rect1 = new Rect();
    Rect rect2 = new Rect();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

    }

    @Override
    protected void onResume() {
        // TODO Auto-generated method stub
        super.onResume();
    }

    @Override
    public void onWindowFocusChanged(boolean hasFocus) {
        super.onWindowFocusChanged(hasFocus);

        if (rect1.equals(rect2)) {
            Toast.makeText(this, "equal", Toast.LENGTH_SHORT).show();
        } else {
            Toast.makeText(this, "Not equal", Toast.LENGTH_SHORT).show();
        }
    }
}
