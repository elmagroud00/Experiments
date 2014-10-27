package com.example.testres;

import java.io.InputStream;
import java.lang.reflect.Field;

import android.app.Activity;
import android.content.Context;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Point;
import android.graphics.Rect;
import android.graphics.BitmapFactory.Options;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.view.Display;
import android.view.Menu;
import android.view.MenuItem;
import android.view.WindowManager;
import android.widget.ImageView;
import android.widget.Toast;

public class MainActivity extends Activity {

    ImageView image;
    int width;
    int height;
    int statusBarHeight;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        WindowManager wm = (WindowManager) getSystemService(Context.WINDOW_SERVICE);
        Display display = wm.getDefaultDisplay();
        Point point = new Point();
        display.getRealSize(point);

        DisplayMetrics dm = getResources().getDisplayMetrics();
        width = point.x;// dm.widthPixels;
        height = point.y;// dm.heightPixels;

        Class c;
        try {
            c = Class.forName("com.android.internal.R$dimen");
            Object obj = c.newInstance();
            Field field = c.getField("status_bar_height");
            int dim = Integer.parseInt(field.get(obj).toString());

            Field field2 = c.getField("navigation_bar_height");
            int dim2 = Integer.parseInt(field2.get(obj).toString());

            statusBarHeight = getResources().getDimensionPixelSize(dim)
                    + getResources().getDimensionPixelSize(dim2);
        } catch (Exception e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        Toast.makeText(
                this,
                "height = " + height + " width = " + width
                        + " statusbarHeight = " + statusBarHeight,
                Toast.LENGTH_LONG).show();

        image = (ImageView) findViewById(R.id.image);

        /*
         * String path = "com/example/testres/k.jpg"; InputStream is =
         * getClassLoader().getResourceAsStream(path); Drawable background =
         * Drawable.createFromStream(is, null);
         */
        int realWidth = width > height ? height : width;
        int realHeight = width > height ? width : height;

        BitmapFactory.Options option = new BitmapFactory.Options();
        option.inJustDecodeBounds = true;

        Bitmap bitmap = BitmapFactory.decodeResource(getResources(),
                R.drawable.k, option);

        if (option.outHeight > realHeight || option.outWidth > realWidth) {
            option.inSampleSize = 10;
        }

        option.inJustDecodeBounds = false;

         Bitmap scaledBg = BitmapFactory.decodeResource(getResources(),
                 R.drawable.k, option);
        // Bitmap scaledBg = Bitmap.createScaledBitmap(bitmap, realWidth,
        // realHeight, option);
        Drawable background = new BitmapDrawable(scaledBg);
        // bitmap.recycle();

        image.setBackground(background);
    }
}
