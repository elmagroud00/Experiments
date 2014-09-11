package net.lnmcc.testgetcontentimage;

import java.io.File;
import java.io.IOException;

import android.app.Activity;
import android.content.Intent;
import android.content.res.Configuration;
import android.graphics.Bitmap;
import android.graphics.Point;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.provider.MediaStore;
import android.util.Log;
import android.view.Display;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.Toast;

public class MainActivity extends Activity implements OnClickListener {

    private static final String TAG = "TestGetContentImage";
    private static final int REQUEST_CODE = 1;

    Button openImageBtn;
    Uri tempPhotoUri;

    private Uri getTempUri() {
        Uri tempPhotoUri = Uri.fromFile(getTempFile());
        return tempPhotoUri;
    }

    private File getTempFile() {
        if (isSDCARDMounted()) {
            File f = new File(Environment.getExternalStorageDirectory(),
                    "temp.jpg");
            try {
                f.createNewFile();
            } catch (IOException e) {
                Log.d(TAG, "Create temp file " + e.toString());
            }
            return f;
        }
        return null;
    }

    private boolean isSDCARDMounted() {
        String status = Environment.getExternalStorageState();
        if (status.equals(Environment.MEDIA_MOUNTED))
            return true;
        else
            return false;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        openImageBtn = (Button) findViewById(R.id.BtnOpenImage);
        openImageBtn.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {

        final Display display = getWindowManager().getDefaultDisplay();
        boolean isPortrait = getResources().getConfiguration().orientation == Configuration.ORIENTATION_PORTRAIT;

        Point screenDimension = new Point();
        display.getSize(screenDimension);
        Toast.makeText(
                this,
                "Default Display:X = " + screenDimension.x + " Y = "
                        + screenDimension.y, Toast.LENGTH_SHORT).show();

        final Intent intent = new Intent(Intent.ACTION_GET_CONTENT, null);
        intent.setType("image/*");
        intent.putExtra("crop", "true");
        intent.putExtra("return-data", false);
        intent.putExtra(MediaStore.EXTRA_OUTPUT, getTempUri());
        intent.putExtra("outputFormat", Bitmap.CompressFormat.JPEG.toString());

        int width = screenDimension.x;
        int height = screenDimension.y;
        intent.putExtra("outputX", width);
        intent.putExtra("outputY", height);

        startActivityForResult(intent, REQUEST_CODE);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        Log.d(TAG, "onActivityResult: resultCode: " + resultCode + " data: "
                + data.toString());
        Log.d(TAG, "data.getData: " + data.getData().toString());
        super.onActivityResult(requestCode, resultCode, data);
    }
}
