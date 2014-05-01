package com.example.cameraapplication;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.PixelFormat;
import android.hardware.Camera;
import android.hardware.Camera.PictureCallback;
import android.hardware.Camera.ShutterCallback;
import android.os.Bundle;
import android.provider.MediaStore.Images;
import android.app.Activity;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.ViewGroup.LayoutParams;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.Toast;

public class CameraApplication extends Activity implements SurfaceHolder.Callback{

	private static final String TAG = "cookbook.hardware";
	private LayoutInflater mInflater = null;
	Camera mCamera;
	byte[] tempdata;
	boolean mPreviewRunning = false;
	private SurfaceHolder m_SurfaceHolder;
	private SurfaceView mSurfaceView;
	Button takepicture;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		getWindow().setFormat(PixelFormat.TRANSLUCENT);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
		setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
		
		setContentView(R.layout.activity_camera_application);
		
		mSurfaceView = (SurfaceView)findViewById(R.id.surface);
		m_SurfaceHolder = mSurfaceView.getHolder();
		m_SurfaceHolder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
		m_SurfaceHolder.addCallback(this);
		
		mInflater = LayoutInflater.from(this);
		View overView = mInflater.inflate(R.layout.cameraoverlay, null);
		this.addContentView(overView, new LayoutParams(LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT));
		
		takepicture = (Button)findViewById(R.id.button);
		takepicture.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				mCamera.takePicture(mShutterCallback, mPictureCallback, mjpeg);
			}
		});
	}

	ShutterCallback mShutterCallback = new ShutterCallback() {
		
		@Override
		public void onShutter() {
			
		}
	};
	
	PictureCallback mPictureCallback = new PictureCallback() {
		
		@Override
		public void onPictureTaken(byte[] data, Camera camera) {
			
		}
	};
	
	PictureCallback mjpeg = new PictureCallback() {
		
		@Override
		public void onPictureTaken(byte[] data, Camera camera) {
			if(data != null) {
				tempdata = data;
				done();
			}
		}
	};
	
	void done() {
		Bitmap bm = BitmapFactory.decodeByteArray(tempdata, 0, tempdata.length);
		String url = Images.Media.insertImage(getContentResolver(), bm, null, null);
		bm.recycle();
		Bundle bundle = new Bundle();
		if(url != null) {
			bundle.putString("url", url);
			Intent mIntent = new Intent();
			mIntent.putExtras(bundle);
			setResult(RESULT_OK, mIntent);
		} else {
			Toast.makeText(this, "Picture can not be saved", Toast.LENGTH_SHORT).show();
		}
		//finish();
	}
	
	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width,
			int height) {

		Log.e(TAG, "surfaceChanged");
		try {
			if(mPreviewRunning) {
				mCamera.stopPreview();
				mPreviewRunning = false;
			}
			Camera.Parameters p = mCamera.getParameters();
			p.setPreviewSize(width, height);
			
			mCamera.setParameters(p);
			mCamera.setPreviewDisplay(holder);
			mCamera.startPreview();
			mPreviewRunning = true;
		} catch(Exception e) {
			Log.d("", e.toString());
		}
	}
	
	@Override
	public void surfaceCreated(SurfaceHolder holder) {
		Log.e(TAG, "surfaceCreated");
		mCamera = Camera.open();
	}
	
	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		Log.e(TAG, "surfaceDestoryed");
		mCamera.stopPreview();
		mPreviewRunning = false;
		mCamera.release();
		mCamera = null;
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.camera_application, menu);
		return true;
	}

}











