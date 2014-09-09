package net.lnmcc.testmultilayout;

import net.lnmcc.testmultilayout.MainActivity.ViewHolder;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Camera;
import android.graphics.Canvas;
import android.graphics.Matrix;
import android.graphics.NinePatch;
import android.graphics.Paint;
import android.graphics.Rect;
import android.graphics.drawable.Drawable;
import android.util.AttributeSet;
import android.view.View;
import android.view.animation.Transformation;
import android.widget.FrameLayout;
import android.widget.ImageView;

public class ZFrameLayout extends FrameLayout {

    private Context mContext;
    private Camera mCamera;
    private int count = 0;

    public ZFrameLayout(Context context) {
        this(context, null);
    }

    public ZFrameLayout(Context context, AttributeSet attrs) {
        super(context, attrs);
        mContext = context;
        mCamera = new Camera();
        setChildrenDrawingOrderEnabled(true);
        setStaticTransformationsEnabled(true);
    }

    @Override
    public void addView(View child) {
        count++;
        super.addView(child);
    }
    
    @Override
    public void draw(Canvas canvas) {
        Paint paint = new Paint();
        paint.setARGB(100, 255, 0, 0);
        canvas.drawRect(0, 0, 1000, 1000, paint);
        if (count > 1) {
            Bitmap bmp_9path = BitmapFactory.decodeResource(getResources(),
                    R.drawable.ic_background);
            NinePatch np = new NinePatch(bmp_9path,
                    bmp_9path.getNinePatchChunk(), null);
            Rect rect = new Rect(0, 0, 2000, 50);
            np.draw(canvas, rect);
        }
        super.draw(canvas);
    }

    @Override
    public void removeView(View view) {
        count--;
        super.removeView(view);
    }

    @Override
    public void removeAllViews() {
        count = 0;
        super.removeAllViews();
    }

    @Override
    protected boolean getChildStaticTransformation(View child, Transformation t) {

        ViewHolder holder;
        Object tag = child.getTag();
        if (tag == null || !(tag instanceof ViewHolder))
            return false;

        holder = (ViewHolder) tag;

        t.clear();
        t.setTransformationType(Transformation.TYPE_MATRIX);

        float centerX = (float) getWidth() / 2;
        float centerY = (float) getHeight() / 2;
        final Matrix matrix = t.getMatrix();
        float x = 0, y = 0, z = 0, r = 0;

        if (holder.Id == 1) {
            x = 0;
            y = 0;
            z = 0;
            r = 0;
        }
        if (holder.Id == 2) {
            x = -10;
            y = 0;
            z = 0;
            r = -3;
        }
        if (holder.Id == 3) {
            x = -20;
            y = 0;
            z = 0;
            r = -5;
        }

        mCamera.save();
        // mCamera.translate(x, y, z);
        // mCamera.rotate(0, -3, 0);
        mCamera.getMatrix(matrix);
        matrix.preTranslate(-centerX, -centerY);
        matrix.postTranslate(centerX, centerY);

        float[] values = new float[9];
        matrix.getValues(values);
        mCamera.restore();

        Matrix mm = new Matrix();
        mm.setValues(values);
        // TODO
        child.invalidate();

        return true;

    }
}
