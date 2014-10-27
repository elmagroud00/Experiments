package com.example.testwmaddview;

import android.app.Activity;
import android.content.Context;
import android.graphics.PixelFormat;
import android.os.Bundle;
import android.util.Log;
import android.view.Gravity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.SurfaceView;
import android.view.View;
import android.view.WindowManager;
import android.view.WindowManager.LayoutParams;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {
    private static String TAG = "TestWMAddView";
    
    WindowManager wm;
    Button btn;
    TextView tv;
    SurfaceView sv;
    LayoutParams lp_tv;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        wm = (WindowManager) getSystemService(Context.WINDOW_SERVICE);

        btn = new Button(this);
        btn.setText("Remove");
        btn.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                if (tv.isAttachedToWindow()) {
                    Log.d(TAG, "remove");
                    wm.removeView(tv);
                    btn.setText("Add");
                } else if (!tv.isAttachedToWindow()) {
                    Log.d(TAG, "add");
                    wm.addView(tv, lp_tv);
                    btn.setText("Remove");
                }
            }
        });

        tv = new TextView(this);
        tv.setText("I am a TextView");
        lp_tv = new LayoutParams();
        lp_tv.type = LayoutParams.TYPE_APPLICATION;
        lp_tv.flags = LayoutParams.FLAG_NOT_FOCUSABLE;
        lp_tv.width = 400;
        lp_tv.height = 100;
        lp_tv.gravity = Gravity.BOTTOM;

        wm.addView(tv, lp_tv);

        LayoutParams lp_btn = new LayoutParams();
        lp_btn = new LayoutParams();
        //lp_btn.type = LayoutParams.TYPE_SYSTEM_ALERT;
        lp_btn.flags = LayoutParams.FLAG_NOT_FOCUSABLE;
        lp_btn.width = 400;
        lp_btn.height = 100;
        lp_btn.gravity = Gravity.TOP | Gravity.LEFT;
        wm.addView(btn, lp_btn);

    }

    @Override
    protected void onResume() {
        super.onResume();

    }
}
