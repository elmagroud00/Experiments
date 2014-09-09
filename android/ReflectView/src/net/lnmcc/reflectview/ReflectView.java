package net.lnmcc.reflectview;

import android.animation.Animator;
import android.animation.AnimatorListenerAdapter;
import android.animation.ObjectAnimator;
import android.animation.ValueAnimator;
import android.content.Context;
import android.graphics.Bitmap;
import android.util.AttributeSet;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.Toast;

public class ReflectView extends LinearLayout {
    private final String TAG = "ReflectView";
    private ImageView mFirstImage;
    private ImageView mSecondImage;
    private LinearLayout mContainer;

    private Context mContext;
    private float mInitPos = 0f;
    private boolean mDraging = false;
    private View mCurrentView = null;

    private Bitmap origBmp = null;
    private Bitmap reflectBmp = null;

    public ReflectView(Context context) {
        this(context, null);
        mContext = context;
    }

    public ReflectView(Context context, AttributeSet attrs) {
        super(context, attrs);

        mContext = context;

        LayoutInflater inflater = LayoutInflater.from(context);
        inflater.inflate(R.layout.reflect_view, this);

    }

    @Override
    protected void onFinishInflate() {
        super.onFinishInflate();

        mContainer = (LinearLayout) findViewById(R.id.container);
        mFirstImage = (ImageView) findViewById(R.id.firstImage);
        mSecondImage = (ImageView) findViewById(R.id.secondImage);

        mFirstImage.setOnTouchListener(new View.OnTouchListener() {

            @Override
            public boolean onTouch(View v, MotionEvent event) {
                return true;
            }
        });

        mSecondImage.setOnTouchListener(new View.OnTouchListener() {

            @Override
            public boolean onTouch(View v, MotionEvent event) {
                return true;
            }
        });
    }

    public void setOrigPicure(Bitmap bmp) {
        origBmp = bmp;
        mFirstImage.setImageBitmap(origBmp);
    }

    public void setReflectPicture(Bitmap bmp) {
        reflectBmp = bmp;
        mSecondImage.setImageBitmap(reflectBmp);
    }

    @Override
    public boolean onInterceptTouchEvent(MotionEvent event) {
        final int action = event.getAction();

        switch (action) {
        case MotionEvent.ACTION_DOWN:
            mCurrentView = getChildAtPosition(event);
            mDraging = false;
            mInitPos = event.getY();
            break;

        case MotionEvent.ACTION_MOVE:
            float pos = event.getY();
            float delta = pos - mInitPos;
            if (Math.abs(delta) > 20) {
                mDraging = true;
                mInitPos = event.getY() - mCurrentView.getTranslationY();
            }
            break;

        case MotionEvent.ACTION_UP:
        case MotionEvent.ACTION_CANCEL:
            mDraging = false;
            mCurrentView = null;
            break;
        }
        return mDraging;
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        if (!mDraging) {
            return false;
        }

        if (!mCurrentView.equals(mFirstImage)) {
            return true;
        }

        final int action = event.getAction();
        switch (action) {
        case MotionEvent.ACTION_DOWN:
            Log.e(TAG, "onTouchEvent ACTION_DOWN");

            break;

        case MotionEvent.ACTION_MOVE:
            float delta = event.getY() - mInitPos;

            if (delta > 0) {
                if (delta > Math.abs(mFirstImage.getTranslationY())) {
                    delta = Math.abs(mFirstImage.getTranslationY());
                }
            }

            if (mFirstImage.getTranslationY() > 0) {
                mFirstImage.setTranslationY(0f);
            } else {
                mFirstImage.setTranslationY(delta);
                mSecondImage.setTranslationY(-delta);
            }
            updateAlphaFromOffset(mFirstImage);
            updateAlphaFromOffset(mSecondImage);

            break;

        case MotionEvent.ACTION_UP:
        case MotionEvent.ACTION_CANCEL:
            boolean needDismiss = Math.abs(mFirstImage.getTranslationY()) > mFirstImage
                    .getMeasuredHeight() * 0.4;

            if (needDismiss) {

            } else {
                snapView(mFirstImage);
                snapView(mSecondImage);
            }

            break;

        }

        return true;
    }

    private void snapView(View view) {
        final View animView = view;
        ObjectAnimator anim = ObjectAnimator.ofFloat(animView, "translationY",
                0);
        anim.setDuration(150);
        anim.addUpdateListener(new ValueAnimator.AnimatorUpdateListener() {

            @Override
            public void onAnimationUpdate(ValueAnimator animation) {
            }
        });
        anim.addListener(new AnimatorListenerAdapter() {
            public void onAnimationEnd(Animator animator) {
                updateAlphaFromOffset(animView);
            }
        });

        anim.start();
    }

    private float getAlphaForOffset(View view) {
        float result = 1.0f;
        float viewHeight = view.getMeasuredHeight();
        float pos = Math.abs(view.getTranslationY());

        result = 1.0f - (pos / viewHeight) * 2f;

        return Math.max(0.1f, result);
    }

    private void updateAlphaFromOffset(View view) {
        float alpha = getAlphaForOffset(view);
        if (alpha != 0f && alpha != 1f) {
            view.setLayerType(View.LAYER_TYPE_HARDWARE, null);
        } else {
            view.setLayerType(View.LAYER_TYPE_NONE, null);
        }
        view.setAlpha(alpha);
    }

    public View getChildAtPosition(MotionEvent ev) {
        final float x = ev.getX();
        final float y = ev.getY();

        if (x >= mFirstImage.getLeft() && x < mFirstImage.getRight()
                && y > mFirstImage.getTop() && y < mFirstImage.getBottom()) {

            Toast.makeText(mContext, "FirstImage is touched",
                    Toast.LENGTH_SHORT).show();

            return mFirstImage;
        }

        if (x >= mSecondImage.getLeft() && x < mSecondImage.getRight()
                && y > mSecondImage.getTop() && y < mSecondImage.getBottom()) {

            Toast.makeText(mContext, "SecondImage is touched",
                    Toast.LENGTH_SHORT).show();

            return mSecondImage;
        }

        return null;
    }
}
