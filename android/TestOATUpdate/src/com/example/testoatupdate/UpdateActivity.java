package com.example.testoatupdate;

import java.io.File;
import java.io.FileFilter;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.content.Context;
import android.content.DialogInterface;
import android.content.res.Configuration;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.provider.MediaStore.Files;
import android.text.GetChars;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ProgressBar;
import android.widget.TextView;

public class UpdateActivity extends Activity implements OnClickListener {

    private static final String TAG = "UpdateActivity";

    private static final String SYSTEM_IMAGES_PATH = Environment
            .getExternalStorageDirectory().getAbsolutePath() + "/PND";
    private static final String CACHE_FOLDER = "/cache/recovery";

    private static final int MSG_NO_SUCH_FILE = 0x01;
    private static final int MSG_UPDATE_ERROR = 0x03;
    private static final int MSG_UPDATE_OK = 0x04;
    private static final int MSG_BEGIN_UPDATE = 0x05;
    private static final int MSG_CREATE_CACHE_PATH_FAILED = 0x06;

    private static final String KEY_MSG_DATA = "msg_data";

    private Handler mHander;
    private ProgressBar mProgressBar;
    private TextView mUpdateStatusTV;
    private Button mSelectSystemImageBtn;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_update);

        Log.d(TAG, "SYSTEM_IMAGES_PATH = " + SYSTEM_IMAGES_PATH);

        mHander = new Handler() {
            @Override
            public void handleMessage(Message msg) {
                Bundle data;
                String updateFile;
                switch (msg.what) {
                case MSG_NO_SUCH_FILE:
                    data = msg.getData();
                    updateFile = data.getString(KEY_MSG_DATA);
                    mUpdateStatusTV.setText(updateFile + "No Such File");
                    mProgressBar.setVisibility(View.INVISIBLE);
                    break;
                case MSG_UPDATE_ERROR:
                    mUpdateStatusTV.setText("Update Error Occured");
                    mProgressBar.setVisibility(View.INVISIBLE);
                    break;
                case MSG_UPDATE_OK:
                    mUpdateStatusTV.setText("Update OK");
                    mProgressBar.setVisibility(View.INVISIBLE);
                    break;
                case MSG_CREATE_CACHE_PATH_FAILED:
                    mUpdateStatusTV.setVisibility(View.VISIBLE);
                    mUpdateStatusTV.setText("Create cache folder failed");
                    mProgressBar.setVisibility(View.INVISIBLE);
                    break;
                case MSG_BEGIN_UPDATE:
                    data = msg.getData();
                    updateFile = data.getString(KEY_MSG_DATA);
                    mUpdateStatusTV.setText("Updating: " + updateFile);
                    mProgressBar.setVisibility(View.VISIBLE);
                default:
                    super.handleMessage(msg);
                    break;
                }
            }
        };

        mProgressBar = (ProgressBar) findViewById(R.id.progressBar);
        mUpdateStatusTV = (TextView) findViewById(R.id.updateStatusTV);
        mSelectSystemImageBtn = (Button) findViewById(R.id.selectSystemImageBtn);
        mSelectSystemImageBtn.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        if (v.getId() == R.id.selectSystemImageBtn) {
            showListDialog();
        }
    }

    /* List all available System update images */
    private void showListDialog() {
        final String[] files = fetchAllUpdateImages();
        String title;

        if (null != files && files.length > 0)
            title = "Select One Image";
        else
            title = "No Available Image";

        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle(title);
        builder.setItems(files, new DialogInterface.OnClickListener() {

            @Override
            public void onClick(DialogInterface dialog, int which) {
                Log.d(TAG, "Selected Image: " + files[which]);
                String fileName = files[which];
                beginUpdate(fileName);
            }
        });
        builder.create().show();
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);
    }

    private boolean beginUpdate(String fileName) {
        boolean retVal = false;
        Bundle msgData = new Bundle();

        File cacheFolder = new File(CACHE_FOLDER);
        if (!cacheFolder.exists()) {
            Log.d(TAG, "Create Folder: " + CACHE_FOLDER);
            boolean ret = cacheFolder.mkdir();
            if (!ret) {
                mHander.sendEmptyMessage(MSG_CREATE_CACHE_PATH_FAILED);
                return retVal;
            }
        }

        File updateFile = new File(SYSTEM_IMAGES_PATH + "/" + fileName);
        if (!updateFile.isFile()) {
            // Bundle data = new Bundle();
            msgData.putString(KEY_MSG_DATA, fileName);
            Message msg = mHander.obtainMessage();
            msg.what = MSG_NO_SUCH_FILE;
            msg.setData(msgData);
            mHander.sendMessage(msg);
            return retVal;
        }

        msgData.putString(KEY_MSG_DATA, fileName);
        Message msg = mHander.obtainMessage();
        msg.what = MSG_BEGIN_UPDATE;
        msg.setData(msgData);
        mHander.sendMessage(msg);

        FileInputStream fis = null;
        FileOutputStream fos = null;
        try {
            fis = new FileInputStream(updateFile);
            fos = new FileOutputStream(CACHE_FOLDER + "/" + fileName);
            // fos = new FileOutputStream("/cache/recovery");
            // fos = openFileOutput(CACHE_NAME, Context.MODE_PRIVATE);
            byte[] buf = new byte[1024];
            int len = 0;
            while ((len = fis.read()) > 0) {
                Log.d(TAG, "write: " + len);
                fos.write(buf, 0, len);
            }
        } catch (Exception e) {
            e.printStackTrace();
            retVal = false;
        } finally {
            try {
                if (null != fis)
                    fis.close();

                if (null != fos)
                    fos.close();
            } catch (Exception e) {
                e.printStackTrace();
                retVal = false;
            }
        }

        if (!retVal)
            mHander.sendEmptyMessage(MSG_UPDATE_ERROR);
        else
            mHander.sendEmptyMessage(MSG_UPDATE_OK);

        return retVal;
    }

    private String[] fetchAllUpdateImages() {
        File dir = new File(SYSTEM_IMAGES_PATH);

        if (!dir.exists() || !dir.isDirectory() || !dir.canRead())
            return null;

        FileFilter filter = new FileFilter() {

            @Override
            public boolean accept(File file) {
                if (file.getName().endsWith(".zip")) {
                    return true;
                }
                return false;
            }
        };
        File[] files = dir.listFiles(filter);
        if (0 == files.length) {
            return null;
        }

        String[] allUpdateImages = new String[files.length];
        for (int i = 0; i < files.length; i++) {
            // FIXME
            Log.d(TAG, "Find image file: " + files[i].getName());
            allUpdateImages[i] = files[i].getName();
        }

        return allUpdateImages;
    }

}
