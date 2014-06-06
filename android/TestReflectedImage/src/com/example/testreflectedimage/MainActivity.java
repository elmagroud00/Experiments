
package com.example.testreflectedimage;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.LinearGradient;
import android.graphics.Bitmap.Config;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.PorterDuff.Mode;
import android.graphics.PorterDuffXfermode;
import android.graphics.Shader.TileMode;
import android.graphics.drawable.BitmapDrawable;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;

public class MainActivity extends Activity {

    Button btn;
    ImageView image;
    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        btn = (Button)findViewById(R.id.test);
        image = (ImageView)findViewById(R.id.image);
        
        btn.setOnClickListener(new View.OnClickListener() {
            
            @Override
            public void onClick(View v) {
                  Bitmap src = BitmapFactory.decodeResource(getResources(), R.drawable.mypic4);
                  Bitmap dst = createReflectedImage(src);
                  src.recycle();
                  BitmapDrawable bd = new BitmapDrawable(dst);
                  image.setBackground(bd);
            }
        });
    }

    private Bitmap createReflectedImage(Bitmap src) {
        final int reflectionGap = 2;
        int width = src.getWidth();
        int height = src.getHeight();
        Matrix matrix = new Matrix();
        matrix.preScale(1, -1);
        Bitmap reflectionBmp = Bitmap.createBitmap(src, 0, height / 2, width, height / 2, matrix,
                false);
        Bitmap bitmapWithReflection = Bitmap.createBitmap(width, (height + height / 2),
                Config.ARGB_8888);
        Canvas canvas = new Canvas(bitmapWithReflection);
        canvas.drawBitmap(src, 0, 0, null);
        Paint paint = new Paint();
        canvas.drawRect(0, height, width, height + reflectionGap, paint);
        canvas.drawBitmap(reflectionBmp, 0, height + reflectionGap, null);

        paint = new Paint();
        LinearGradient shader = new LinearGradient(0, height, 0,
                bitmapWithReflection.getHeight() + reflectionGap, 0x70ffffff, 0x00ffffff,
                TileMode.CLAMP);
        paint.setShader(shader);
        paint.setXfermode(new PorterDuffXfermode(Mode.DST_IN));
        canvas.drawRect(0, height, width, bitmapWithReflection.getHeight() + reflectionGap, paint);
        canvas.setBitmap(null);
        
        return bitmapWithReflection; 
        
    }
}












