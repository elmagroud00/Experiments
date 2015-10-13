package com.example.sijiewang.floatingsurfaceview;

import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.MotionEvent;
import android.view.Surface;
import android.view.SurfaceView;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.RelativeLayout;

public class MainActivity extends AppCompatActivity {

    private static String TAG = "MainActivity";
    private static int SUR_WIDTH = 500;
    private static int SUR_HEIGHT = 500;
    private SurfaceView surface;
    private int x = 500;
    private int y = 300;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });

        surface = (SurfaceView)findViewById(R.id.sur);
        surface.setOnTouchListener(touch);
        RelativeLayout.LayoutParams params = new RelativeLayout.LayoutParams(SUR_WIDTH, SUR_HEIGHT);
        params.leftMargin = x;
        params.topMargin = y;
        surface.setLayoutParams(params);
    }

    private View.OnTouchListener touch = new View.OnTouchListener() {
        int[] tmp = new int[] {0, 0};
        RelativeLayout.LayoutParams params = new RelativeLayout.LayoutParams(SUR_WIDTH, SUR_HEIGHT);

        @Override
        public boolean onTouch(View view, MotionEvent motionEvent) {
            int eventaction = motionEvent.getAction();
            int x = (int) motionEvent.getRawX();
            int y = (int) motionEvent.getRawY();

            switch (eventaction) {
                case MotionEvent.ACTION_DOWN:
                    tmp[0] = x - view.getLeft();
                    tmp[1] = y - view.getTop();
                    break;
                case MotionEvent.ACTION_MOVE:
                    params.leftMargin = x - tmp[0];
                    params.topMargin = y - tmp[1];
                    view.setLayoutParams(params);
                    break;
                case MotionEvent.ACTION_UP:
                    break;
            }

            return true;
        }
    };

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
