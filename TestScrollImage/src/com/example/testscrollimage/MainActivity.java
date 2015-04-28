package com.example.testscrollimage;

import android.app.Activity;
import android.app.Activity;
import android.content.Context;
import android.graphics.Canvas;
import android.graphics.drawable.Drawable;
import android.graphics.drawable.ShapeDrawable;
import android.graphics.drawable.shapes.OvalShape;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.widget.ImageView;

public class MainActivity extends Activity implements SensorEventListener {
    private static final String TAG = "xxx";

    private SensorManager sensorManager;
    private Sensor accelerometer;
    private long lastUpdate;

    AnimatedView animatedView = null;
    Drawable mDrawable;
    public static int x;
    public static int y;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // setContentView(R.layout.activity_main);

        sensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);
        accelerometer = sensorManager
                .getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        lastUpdate = System.currentTimeMillis();

        animatedView = new AnimatedView(this);
        setContentView(animatedView);
    }

    @Override
    protected void onResume() {
        super.onResume();
        sensorManager.registerListener(this, accelerometer,
                SensorManager.SENSOR_DELAY_GAME);
    }

    @Override
    protected void onPause() {
        super.onPause();
        sensorManager.unregisterListener(this);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        return true;
    }

    @Override
    public void onAccuracyChanged(Sensor arg0, int arg1) {
        // TODO Auto-generated method stub

    }

    @Override
    public void onSensorChanged(SensorEvent event) {
        // TODO Auto-generated method stub
        if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {

            x -= (int) event.values[0];
            y += (int) event.values[1];

            Log.d(TAG, "event.values[0] = " + event.values[0]
                    + "   event.values[1] = " + event.values[1]);

        }
    }

    public class AnimatedView extends ImageView {

        static final int width = 500;
        static final int height = 500;

        public AnimatedView(Context context) {
            super(context);
            // TODO Auto-generated constructor stub

            mDrawable = (Drawable) context.getResources().getDrawable(
                    R.drawable.longbg);// new ShapeDrawable(new OvalShape());
            // mDrawable.getPaint().setColor(0xffffAC23);
            mDrawable.setBounds(x, y, x + width, y + height);

        }

        @Override
        protected void onDraw(Canvas canvas) {

            mDrawable.setBounds(x, y, x + width, y + height);
            mDrawable.draw(canvas);
            invalidate();
        }
    }

}

/*
 * private float mx, my;
 * @Override protected void onCreate(Bundle savedInstanceState) {
 * super.onCreate(savedInstanceState); setContentView(R.layout.activity_main);
 * final ImageView switcherView = (ImageView) this.findViewById(R.id.img);
 * switcherView.setOnTouchListener(new View.OnTouchListener() { public boolean
 * onTouch(View arg0, MotionEvent event) { float curX, curY; switch
 * (event.getAction()) { case MotionEvent.ACTION_DOWN: mx = event.getX(); my =
 * event.getY(); break; case MotionEvent.ACTION_MOVE: curX = event.getX(); curY
 * = event.getY(); switcherView.scrollBy((int) (mx - curX), (int) (my - curY));
 * mx = curX; my = curY; break; case MotionEvent.ACTION_UP: curX = event.getX();
 * curY = event.getY(); switcherView.scrollBy((int) (mx - curX), (int) (my -
 * curY)); break; } return true; } }); } }
 */
