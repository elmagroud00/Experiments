
package com.example.testsnapshot;

import android.app.Activity;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.PixelFormat;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.view.Display;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.Toast;

import java.io.DataInput;
import java.io.DataInputStream;
import java.io.EOFException;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;


public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
       
        Button btn = (Button)findViewById(R.id.snapshot);
        btn.setOnClickListener(new View.OnClickListener() {
            
            @Override
            public void onClick(View v) {
                SnapShot();
            }
        });
    }
    
    public static InputStream getInputStream() {
        FileInputStream buf = null;
        try {
            buf = new FileInputStream(new File("/dev/graphics/fb0"));
        } catch (FileNotFoundException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return buf;
    }
    
    public static void convertToRgba32(DataInput frameBuffer, int[] into) {
        try {
            for(int x = 0; x < into.length; x++) {
                try {
                    int rgb = frameBuffer.readShort() & 0xffff;
                    int red = rgb >> 11;
                    red = (red << 3) | (red >> 2);
                    int green = (rgb >> 5) & 63;
                    green = (green << 2) | (green >> 4);
                    int blue = rgb & 31;
                    blue = (blue << 3) | (blue >> 2);
                    into[x] = 0xff000000 | (red << 16) | (green << 8) | blue;
                } catch(EOFException ex) {
                    ex.printStackTrace();
                }
            }
        } catch(IOException e) {
            e.printStackTrace();
        }
    }
    
    private void SnapShot() {
        DisplayMetrics metrics = new DisplayMetrics();
        WindowManager wm = (WindowManager)getSystemService(Context.WINDOW_SERVICE);
        Display display = wm.getDefaultDisplay();
        display.getMetrics(metrics);
        int height = metrics.heightPixels;
        int width = metrics.widthPixels;
        int pixelformat = display.getPixelFormat();
        PixelFormat localPixelFormat1 = new PixelFormat();
        PixelFormat.getPixelFormatInfo(pixelformat, localPixelFormat1);
        int deepth = localPixelFormat1.bytesPerPixel;
        Toast.makeText(this, String.valueOf(height) + " x " + String.valueOf(width)
                + " x " + deepth + " " + pixelformat, Toast.LENGTH_LONG).show();
        byte[] piex = new byte[height * width * deepth];
        InputStream stream = getInputStream();
        DataInputStream dStream = new DataInputStream(stream);
        try {
            dStream.readFully(piex);
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        
    }
    
}
