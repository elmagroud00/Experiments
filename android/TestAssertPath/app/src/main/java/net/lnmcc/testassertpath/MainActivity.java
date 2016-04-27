package net.lnmcc.testassertpath;

import android.content.res.AssetManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

import java.io.InputStream;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Thread thread = new Thread(new Runnable() {
            @Override
            public void run() {
                AssetManager assetManager = getAssets();
                try {
                    InputStream ims = assetManager.open("1.jpg");
                    while(ims.available() > 0) {
                        System.out.println(ims.read());
                    }
                } catch (Exception e) {
                    Log.d("wangsijie", e.toString());
                }
            }
        });

        thread.start();
    }
}
