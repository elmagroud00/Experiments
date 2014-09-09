package net.lnmcc.reflectview;

import java.io.IOException;
import java.io.InputStream;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;

public class MainActivity extends Activity {
    ReflectView reflectView; 
    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        reflectView = (ReflectView)findViewById(R.id.reflectView);
        
        InputStream is = null;
        Bitmap bmp = null;
        
        try {
            is = getAssets().open("1.jpg");
            bmp = BitmapFactory.decodeStream(is);
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        
        if(bmp != null) {
            reflectView.setOrigPicure(bmp);
        }
        
        try {
            is = getAssets().open("1.jpg");
            bmp = BitmapFactory.decodeStream(is);
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        
        if(bmp != null) {
            reflectView.setReflectPicture(bmp);
        }

    }
    
    @Override
    protected void onStart() {
        // TODO Auto-generated method stub
        super.onStart();
    }
    
    @Override
    protected void onResume() {
        // TODO Auto-generated method stub
        super.onResume();
    }
}
