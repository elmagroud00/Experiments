package com.example.sijiewang.testscaleanimation;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;
import android.view.animation.BounceInterpolator;
import android.widget.OverScroller;
import android.widget.TextView;

/**
 * Created by sijiewang on 6/23/15.
 */
public class JerryTextView extends TextView {
    private OverScroller mScroller;

    private float lastX;
    private float lastY;

    private float startX;
    private float startY;

    public JerryTextView(Context context, AttributeSet attrs) {
        super(context, attrs);
        mScroller = new OverScroller(context, new BounceInterpolator());
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN:
                lastX = event.getRawX();
                lastY = event.getRawY();
                break;
            case MotionEvent.ACTION_MOVE:
                float disX = event.getRawX() - lastX;
                float disY = event.getRawY() - lastY;

                offsetLeftAndRight((int) disX);
                offsetTopAndBottom((int) disY);

                lastX = event.getRawX();
                lastY = event.getRawY();
                break;
            case MotionEvent.ACTION_UP:
                mScroller.startScroll((int) getX(), (int) getY(), -(int) (getX() - startX), -
                        (int) (getY() - startY));
                invalidate();
                break;
            default:
                break;
        }
        //return super.onTouchEvent(event);
        return true;
    }

    @Override
    public void computeScroll() {
        if (mScroller.computeScrollOffset()) {
            setX(mScroller.getCurrX());
            setY(mScroller.getCurrY());
            invalidate();
        }
    }

    @Override
    protected void onSizeChanged(int w, int h, int oldw, int oldh) {
        Log.d("wangsijie", "onSizeChanged: " + "w:h:oldw:oldh" + " = " + w + "  " + h + "  " +
                oldw + "  " + oldh);

        super.onSizeChanged(w, h, oldw, oldh);
        startX = getX();
        startY = getY();
    }

    public void spingBack() {

    }
}
