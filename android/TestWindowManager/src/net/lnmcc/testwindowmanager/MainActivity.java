package net.lnmcc.testwindowmanager;

import android.app.Activity;
import android.content.Context;
import android.graphics.PixelFormat;
import android.os.Bundle;
import android.view.WindowManager;
import android.view.WindowManager.LayoutParams;
import android.widget.TextView;

public class MainActivity extends Activity {

    WindowManager mWm;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        mWm = (WindowManager)getSystemService(Context.WINDOW_SERVICE);
        
    }
    
    @Override
    protected void onStart() {
        super.onStart();
        TextView tv = new TextView(this);
        tv.setText("Hello");
        LayoutParams lp = new LayoutParams();
        lp.type = LayoutParams.TYPE_APPLICATION;
        lp.flags |= LayoutParams.FLAG_NOT_FOCUSABLE
                | LayoutParams.FLAG_NOT_TOUCHABLE;
        lp.format = PixelFormat.RGBA_8888;
        lp.width = LayoutParams.WRAP_CONTENT;
        lp.height = LayoutParams.WRAP_CONTENT;
        mWm.addView(tv, lp);
    }
   
}
