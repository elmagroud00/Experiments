package net.lnmcc.testandroidtrace;

import android.os.Trace;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {

    Button mBtn;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Trace.beginSection("Test Button");
        mBtn = (Button) findViewById(R.id.btn);
        Trace.endSection();

    }
}
