package com.example.sijiewang.testfragmenttab;

import android.net.Uri;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentTabHost;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.VideoView;

import java.net.URI;

public class MainActivity extends FragmentActivity {

    private FragmentTabHost mTabHost;
    private VideoView mVideoView;

    private static final String TEST_URL = "rtsp://120.27.55.222:554/live/1188?sign=a93a973bff08b2711ad0d778f040ab8b&UserID=66&Atoken=033d72a87fd411e5ba3f00163e003613&DevUUID=8799b04369b745af9366840243f1d8ee&Time=1446298466";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        //setSupportActionBar(toolbar);

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });

        initViews();
    }

    private void initViews() {
        mVideoView = (VideoView) findViewById(R.id.videoview);
        //mVideoView.setVideoURI(Uri.parse(TEST_URL));
        //mVideoView.start();
    }

    @Override
    protected void onResume() {
        super.onResume();
        mVideoView.setVideoURI(Uri.parse(TEST_URL));
        mVideoView.requestFocus();
        mVideoView.start();
    }

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
