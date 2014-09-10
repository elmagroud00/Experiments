package net.lnmcc.testgetcontentimage;

import android.app.Activity;
import android.content.Intent;
import android.content.res.Configuration;
import android.graphics.Bitmap;
import android.graphics.Point;
import android.os.Bundle;
import android.view.Display;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.Toast;

public class MainActivity extends Activity implements OnClickListener {

    Button openImageBtn;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        openImageBtn = (Button) findViewById(R.id.BtnOpenImage);
        openImageBtn.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        final Intent intent = new Intent(Intent.ACTION_GET_CONTENT, null);
        intent.setType("image/*");
        intent.putExtra("crop", true);
        intent.putExtra("scale", true);
        intent.putExtra("scaleUpIfNeeded", false);
        intent.putExtra("layout_witdh", -1);
        intent.putExtra("layout_height", -1);
        intent.putExtra("outputFormat", Bitmap.CompressFormat.JPEG.toString());

        final Display display = getWindowManager().getDefaultDisplay();
        boolean isPortrait = getResources().getConfiguration().orientation == Configuration.ORIENTATION_PORTRAIT;
        
        Point screenDimension = new Point();
        display.getSize(screenDimension);
        Toast.makeText(this, "Default Display:X = " + screenDimension.x +
                " Y = " + screenDimension.y, Toast.LENGTH_SHORT).show();
        int width = screenDimension.x;
        int height = screenDimension.y;
        intent.putExtra("aspectX", width);
        intent.putExtra("aspectY", height);
        startActivity(intent);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        // TODO Auto-generated method stub
        super.onActivityResult(requestCode, resultCode, data);
    }
}

















































