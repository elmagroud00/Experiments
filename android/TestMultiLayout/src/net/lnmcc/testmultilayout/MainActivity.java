package net.lnmcc.testmultilayout;

import java.io.IOException;

import android.app.Activity;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.util.EventLogTags.Description;
import android.view.GestureDetector;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewGroup.LayoutParams;
import android.widget.FrameLayout;
import android.widget.ImageView;

public class MainActivity extends Activity {

    private static final int LARGE_MOVE = 60;

    FrameLayout firstContatiner;
    GestureDetector gestureDetector;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        firstContatiner = (FrameLayout) findViewById(R.id.first_LL);

        gestureDetector = new GestureDetector(this,
                new GestureDetector.OnGestureListener() {

                    @Override
                    public boolean onSingleTapUp(MotionEvent e) {
                        // TODO Auto-generated method stub
                        return false;
                    }

                    @Override
                    public void onShowPress(MotionEvent e) {
                        // TODO Auto-generated method stub

                    }

                    @Override
                    public boolean onScroll(MotionEvent e1, MotionEvent e2,
                            float distanceX, float distanceY) {
                        // TODO Auto-generated method stub
                        return false;
                    }

                    @Override
                    public void onLongPress(MotionEvent e) {
                        // TODO Auto-generated method stub

                    }

                    @Override
                    public boolean onFling(MotionEvent e1, MotionEvent e2,
                            float velocityX, float velocityY) {
                        if (e1.getY() - e2.getY() > LARGE_MOVE) {
                            return true;
                        } else if (e2.getY() - e1.getY() > LARGE_MOVE) {
                            return true;
                        } else if (e1.getX() - e2.getX() > LARGE_MOVE) {
                            return true;
                        } else if (e2.getX() - e1.getX() > LARGE_MOVE) {
                            return true;
                        }

                        return false;
                    }

                    @Override
                    public boolean onDown(MotionEvent e) {
                        // TODO Auto-generated method stub
                        return false;
                    }
                });
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        return false;
    }

    @Override
    protected void onStart() {
        // TODO Auto-generated method stub
        super.onStart();
    }

    @Override
    protected void onResume() {
        getView();
        super.onResume();
    }

    View.OnTouchListener touchListener = new View.OnTouchListener() {
        float y1, y2;

        @Override
        public boolean onTouch(View v, MotionEvent event) {
            int action = event.getAction();

            switch (action) {
            case MotionEvent.ACTION_DOWN:
                y1 = event.getY();
                break;
            case MotionEvent.ACTION_MOVE:
                y2 = event.getY();
                if (y1 - y2 > 200) {
                    firstContatiner.removeView(v);
                    firstContatiner.postInvalidate();
                }
                break;
            case MotionEvent.ACTION_CANCEL:
            case MotionEvent.ACTION_UP:
                break;
            }

            return true;
        }
    };

    class ViewHolder {
        int Id;
    }
    
    void getView() {
        ViewHolder holder;
        View view = LayoutInflater.from(this).inflate(R.layout.item, null);

        ImageView image = (ImageView) view.findViewById(R.id.image);
        try {
            image.setImageBitmap(BitmapFactory.decodeStream(getAssets().open(
                    "1.jpg")));
        } catch (IOException e) {
            e.printStackTrace();
        }
        holder = new ViewHolder();
        holder.Id = 1;
        view.setTag(holder);
        view.setOnTouchListener(touchListener);
        firstContatiner.addView(view);

        View view2 = LayoutInflater.from(this).inflate(R.layout.item, null);
        ImageView image2 = (ImageView) view2.findViewById(R.id.image);
        try {
            image2.setImageBitmap(BitmapFactory.decodeStream(getAssets().open(
                    "2.jpg")));
        } catch (IOException e) {
            e.printStackTrace();
        }
        holder = new ViewHolder();
        holder.Id = 2;
        view2.setTag(holder);
        view2.setOnTouchListener(touchListener);
        firstContatiner.addView(view2);

        View view3 = LayoutInflater.from(this).inflate(R.layout.item, null);
        ImageView image3 = (ImageView) view3.findViewById(R.id.image);
        try {
            image3.setImageBitmap(BitmapFactory.decodeStream(getAssets().open(
                    "3.jpg")));
        } catch (IOException e) {
            e.printStackTrace();
        }
        holder = new ViewHolder();
        holder.Id = 3;
        view3.setTag(holder);
        view3.setOnTouchListener(touchListener);
        firstContatiner.addView(view3);

    }
}
