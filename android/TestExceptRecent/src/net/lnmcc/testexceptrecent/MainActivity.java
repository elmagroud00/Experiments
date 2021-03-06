package net.lnmcc.testexceptrecent;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;

public class MainActivity extends Activity {

    Button btn;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btn = (Button) findViewById(R.id.btn);
        btn.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                Intent intent = new Intent();
                ComponentName cm = new ComponentName(
                        "net.lnmcc.testexceptrecent",
                        "net.lnmcc.testexceptrecent.OtherActivity");
                intent.setComponent(cm);
                startActivity(intent);
            }
        });
    }
}
