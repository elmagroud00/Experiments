package com.example.shutter;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

import android.os.Bundle;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.hardware.Camera;
import android.hardware.Camera.PictureCallback;
import android.hardware.Camera.ShutterCallback;
import android.view.Menu;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.Window;
import android.view.WindowManager;

public class MainActivity extends Activity {

	@SuppressLint("SdCardPath")
	private static final File OUTPUT_FILE = new File("/sdcard/usecamera.jpg");
	private Camera mCamera = null;
	
	ShutterCallback mShutter = new ShutterCallback() {
		
		@Override
		public void onShutter() {
			
		}
	};
	
	PictureCallback mRaw = new PictureCallback() {
		
		@Override
		public void onPictureTaken(byte[] data, Camera camera) {
			
		}
	};
	
	PictureCallback mJpeg = new PictureCallback() {
		
		@Override
		public void onPictureTaken(byte[] data, Camera camera) {
			
			FileOutputStream out = null;
			try {
				out = new FileOutputStream(OUTPUT_FILE);
				out.write(data);
				out.flush();
				out.close();
			} catch(FileNotFoundException e) {
				e.printStackTrace();
			} catch(IOException e) {
				e.printrm StackTrace();
			}
		}
	};
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);

		setContentView(new CameraPreview(this));
		mCamera = Camera.open();
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	@Override
	public boolean onTouchEvent(MotionEvent event) {
	
		if(event.getAction() == MotionEvent.ACTION_DOWN) {
			mCamera.takePicture(mShutter, mRaw, mJpeg);
			mCamera.startPreview();
			return true;
		}
		
		return super.onTouchEvent(event);
	}
	
	private class CameraPreview extends SurfaceView implements SurfaceHolder.Callback {
		
		SurfaceHolder mHolder;
			
		public CameraPreview(Context context) {
			super(context);
			mHolder = getHolder();
			mHolder.addCallback(this);
			mHolder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
		}				 				
		
		@Override
		public void surfaceChanged(SurfaceHolder holder, int format, int width,
				int height) {
			
			Camera.Parameters parameters = mCamera.getParameters();
			parameters.setPreviewSize(width, height);
			mCamera.setParameters(parameters);
			mCamera.startPreview();
		}
		
		@Override
		public void surfaceCreated(SurfaceHolder holder) {
			if(mCamera != null) return;

			try {
				mCamera.setPreviewDisplay(mHolder);
			} catch(IOException e) {
				mCamera.release();
				mCamera = null;
			}
		}
		
		@Override
		public void surfaceDestroyed(SurfaceHolder holder) {
			mCamera.stopPreview();
			mCamera.release();
			mCamera = null;
		}
	}
}


