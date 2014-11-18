package com.example.test8916;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity implements OnClickListener {

    Button btn;
    TextView tv;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btn = (Button) findViewById(R.id.btn);
        btn.setOnClickListener(this);
        tv = (TextView) findViewById(R.id.tv);

    }

    @Override
    public void onClick(View v) {
        if (v.getId() == R.id.btn) {
            WindowManager wm = (WindowManager) getSystemService(Context.WINDOW_SERVICE);
            DisplayMetrics outMetrics = new DisplayMetrics();
            wm.getDefaultDisplay().getRealMetrics(outMetrics);
            String info = "width = " + outMetrics.widthPixels + "pixels\n"
                    + "height = " + outMetrics.heightPixels + "pixels\n"
                    + "density = " + outMetrics.density + "\n"
                    + "densityDPI = " + outMetrics.densityDpi;
            tv.setText(info);
        }
    }

}
