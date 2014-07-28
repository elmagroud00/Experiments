package net.lnmcc.reflectview;

import java.io.IOException;
import java.io.InputStream;

import android.animation.ObjectAnimator;
import android.animation.TimeInterpolator;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.animation.LinearInterpolator;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.Toast;

public class ReflectView extends LinearLayout {
    private ImageView mFirstImage;
    private ImageView mSecondImage;
    private LinearLayout mContainer;
    private Context mContext;
    private float mInitPos = 0f;
    private boolean mDraging = false;

    public ReflectView(Context context) {
        this(context, null);
        mContext = context;
    }

    public ReflectView(Context context, AttributeSet attrs) {
        super(context, attrs);

        mContext = context;

        LayoutInflater inflater = LayoutInflater.from(context);
        inflater.inflate(R.layout.reflect_view, this);

        mFirstImage = (ImageView) findViewById(R.id.firstImage);
        mSecondImage = (ImageView) findViewById(R.id.secondImage);
        mContainer = (LinearLayout) findViewById(R.id.container);

        InputStream is = null;
        try {
            is = mContext.getAssets().open("1.jpg");
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        Bitmap bmp = BitmapFactory.decodeStream(is);
        mFirstImage.setImageBitmap(bmp);
        mSecondImage.setImageBitmap(bmp);
    }

    @Override
    public boolean onInterceptTouchEvent(MotionEvent event) {
        final int action = event.getAction();

        switch (action) {
        case MotionEvent.ACTION_DOWN:
            mDraging = false;
            mInitPos = getY();
            break;

        case MotionEvent.ACTION_MOVE:
            mDraging = true;
            break;

        case MotionEvent.ACTION_UP:
        case MotionEvent.ACTION_CANCEL:
            mDraging = false;
            break;
        }
        return mDraging;
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        final int action = event.getAction();
        View view = getChildAtPosition(event);

        switch (action) {
        case MotionEvent.ACTION_DOWN:
            /*
             * View v = getChildAtPosition(event); float newPos =
             * v.getMeasuredHeight(); LinearInterpolator sLinearInterpolator =
             * new LinearInterpolator(); ObjectAnimator anim =
             * ObjectAnimator.ofFloat(v, "translationY", -newPos);
             * anim.setInterpolator(sLinearInterpolator);
             * anim.setDuration(3000); anim.start();
             */
            break;

        case MotionEvent.ACTION_MOVE:
            float delta = event.getY() - mInitPos;
            float size = view.getY();
            float maxDistance = 0.5f * size;
            
            if(Math.abs(delta) >= size) {
                delta = delta > 0 ? maxDistance : -maxDistance;
            } else {
                delta = maxDistance * (float)Math.sin((delta / size) * (Math.PI / 2));
            }
            
            view.setTranslationY(delta);
            break;

        case MotionEvent.ACTION_UP:
        case MotionEvent.ACTION_CANCEL:

        }

        return true;
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
