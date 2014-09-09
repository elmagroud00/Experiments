package net.lnmcc.testintent;

import android.app.Activity;
import android.content.ActivityNotFoundException;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.location.SettingInjectorService;
import android.net.Uri;
import android.os.Bundle;
import android.os.UserHandle;
import android.provider.Settings;
import android.util.Log;
import android.view.View;
import android.widget.Button;

public class MainActivity extends Activity {

    Button setting;
    Button browser;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        setting = (Button) findViewById(R.id.btn_setting);

        setting.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                Intent intent = new Intent();
                intent.setAction(Intent.ACTION_VIEW);

                // intent.setClassName("com.android.settings",
                // "com.android.settings.ManageApplications");
                // ComponentName cm = new ComponentName("com.android.settings",
                // "com.android.settings.wifi.WifiSettings");
                // ComponentName cm = new ComponentName("com.android.settings",
                // "com.android.settings.Settings$WifiSettingsActivity");
                // intent.setComponent(cm);
                intent.setClassName("com.android.settings",
                        "com.android.settings.Settings.$WifiSettingsActivity");
                intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                startActivity(intent);
            }
        });

        browser = (Button) findViewById(R.id.btn_browser);

        browser.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                Intent intent = new Intent();
                intent.setAction(Intent.ACTION_VIEW);
                intent.setClassName("com.android.browser",
                        "com.android.browser.BrowserActivity");
                intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                startActivity(intent);
            }
        });
    }
}
