package com.example.browserview;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.net.Uri;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnKeyListener;
import android.widget.Button;
import android.widget.EditText;
import android.webkit.WebView;

public class MainActivity extends Activity {
    private WebView webView;
    private EditText urlText;
    private Button goButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        urlText = (EditText)findViewById(R.id.url_field);
        goButton = (Button)findViewById(R.id.go_button);

        goButton.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View view) {
                openBrowser();
            }
        });

        urlText.setOnKeyListener(new OnKeyListener() {
            @Override
            public boolean onKey(View view, int i, KeyEvent keyEvent) {
                if(i == KeyEvent.KEYCODE_ENTER) {
                    openBrowser();
                    return true;
                }
                return false;
            }
        });

        webView = (WebView)findViewById(R.id.web_view);

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    private void openBrowser() {
        webView.getSettings().setJavaScriptEnabled(true);
        webView.loadUrl(urlText.getText().toString());
    }
}
