package com.example.testlayout;

import android.app.Activity;
import android.graphics.Color;
import android.graphics.Rect;
import android.os.Bundle;
import android.util.Log;
import android.view.Gravity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup.LayoutParams;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.Toast;

public class MainActivity extends Activity {
    private static final String TAG = "TestLayout";

    LinearLayout linear;
    FrameLayout frame;
    Button btn1;
    Button btn2;

    ImageView img1;
    ImageView img2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // setContentView(R.layout.activity_main);

        frame = new FrameLayout(this);
        FrameLayout.LayoutParams lp_f = new FrameLayout.LayoutParams(
                LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT);

        linear = new LinearLayout(this);
        linear.setOrientation(LinearLayout.HORIZONTAL);
        linear.setPadding(0, 0, 0, 0);

        LinearLayout.LayoutParams lp1 = new LinearLayout.LayoutParams(0,
                LayoutParams.MATCH_PARENT, 1);

        LinearLayout.LayoutParams lp2 = new LinearLayout.LayoutParams(0,
                LayoutParams.MATCH_PARENT, 1);

        btn1 = new Button(this);
        btn1.setBackgroundColor(Color.parseColor("red"));
        btn1.setText("Button1");

        btn2 = new Button(this);
        btn2.setBackgroundColor(Color.parseColor("blue"));
        btn2.setText("Button2");

        img1 = new ImageView(this);
        img1.setBackgroundColor(Color.parseColor("blue"));
        img1.setOnTouchListener(new View.OnTouchListener() {

            @Override
            public boolean onTouch(View v, MotionEvent event) {
                Log.d(TAG, "img1.onTouch");
                // img2.dispatchTouchEvent(event);

                int location[] = new int[2];
                img1.getLocationOnScreen(location);
                Log.d(TAG, "loaction: = " + " x = " + location[0] + "  y = "
                        + location[1]);

                int touchRawX = (int) event.getRawX();
                int touchRawY = (int) event.getRawY();

                int touchX = (int) event.getX();
                int touchY = (int) event.getY();

                Log.d(TAG, "Raw touch: = " + " x = " + touchRawX + "  y = "
                        + touchRawY);
                Log.d(TAG, "touch: = " + " x = " + touchX + "  y = " + touchY);

                Rect rect = new Rect(location[0], location[1], location[0]
                        + img1.getWidth(), location[1] + img1.getHeight() / 2);

                if (rect.contains(touchRawX, touchRawY)) {
                    Toast.makeText(MainActivity.this, "Touch Top Half",
                            Toast.LENGTH_SHORT).show();
                } else {
                    Toast.makeText(MainActivity.this, "Touch Buttom Half",
                            Toast.LENGTH_SHORT).show();
                }

                return false;
            }
        });

        img2 = new ImageView(this);
        img2.setBackgroundColor(Color.parseColor("red"));
        img2.setOnTouchListener(new View.OnTouchListener() {

            @Override
            public boolean onTouch(View v, MotionEvent event) {
                Log.d(TAG, "img2.onTouch");
                return false;
            }
        });

        linear.addView(img1, lp1);
        linear.addView(img2, lp2);
        // frame.addView(btn1, lp1);

        setContentView(linear);
    }
}
