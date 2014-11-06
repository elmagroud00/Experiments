package com.example.testoatupdate;

import java.io.File;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class MainActivity extends Activity implements OnClickListener {

    private static final String TAG = "MainActivity";

    Button mUpdateBtn;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mUpdateBtn = (Button) findViewById(R.id.updateBtn);
        mUpdateBtn.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        Intent updateIntent = new Intent(this, UpdateActivity.class);
        startActivity(updateIntent);
    }

}
