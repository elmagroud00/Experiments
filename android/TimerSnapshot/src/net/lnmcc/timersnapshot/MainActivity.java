package net.lnmcc.timersnapshot;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.OutputStream;

import android.hardware.Camera;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.provider.MediaStore;
import android.app.Activity;
import android.content.ContentValues;
import android.content.res.Configuration;
import android.view.Menu;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity implements OnClickListener,
		SurfaceHolder.Callback, Camera.PictureCallback {

	SurfaceView cameraView;
	SurfaceHolder surfaceHolder;
	Camera camera;
	Button startButton;
	TextView countdownTextView;
	Handler timerUpdateHandler;
	boolean timerRunning = false;
	int currentTime = 0;
	private static final int TIME_BETWEEN = 60; 
	
	private Runnable timerUpdateTask = new Runnable() {

		@Override
		public void run() {
			if (currentTime < TIME_BETWEEN) {
				currentTime++;
			} else {
				camera.takePicture(null, null, MainActivity.this);
				currentTime = 0;
			}
			timerUpdateHandler.postDelayed(timerUpdateTask, 1000);
			countdownTextView.setText("" + currentTime);
		}
	};

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		cameraView = (SurfaceView) findViewById(R.id.CameraView);
		surfaceHolder = cameraView.getHolder();
		surfaceHolder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
		surfaceHolder.addCallback(this);

		countdownTextView = (TextView) findViewById(R.id.CountDownTextView);
		startButton = (Button) findViewById(R.id.StartStopButton);
		startButton.setOnClickListener(this);

		timerUpdateHandler = new Handler();
	}

	@Override
	public void onClick(View v) {

		if (!timerRunning) {
			startButton.setText("stop");
			timerRunning = true;
			timerUpdateHandler.post(timerUpdateTask);
		} else {
			startButton.setText("start");
			timerRunning = false;
			timerUpdateHandler.removeCallbacks(timerUpdateTask);
		}
	}

	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width,
			int height) {

		camera.startPreview();
	}

	@Override
	public void surfaceCreated(SurfaceHolder holder) {
		camera = Camera.open();
		try {
			camera.setPreviewDisplay(surfaceHolder);
			Camera.Parameters parameters = camera.getParameters();
			if (this.getResources().getConfiguration().orientation != Configuration.ORIENTATION_LANDSCAPE) {
				parameters.set("orientation", "portrait");
				camera.setDisplayOrientation(90);
				parameters.setRotation(90);
			}
			camera.setParameters(parameters);
		} catch (IOException e) {
			camera.release();
		}
	}

	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		camera.stopPreview();
		camera.release();
	}
	
	@Override
	public void onPictureTaken(byte[] data, Camera camera) {
		Uri imageFileUri = getContentResolver().insert(MediaStore.Images.Media.EXTERNAL_CONTENT_URI, new ContentValues());
		try {
			OutputStream imageFileOS = getContentResolver().openOutputStream(imageFileUri);
			imageFileOS.write(data);
			imageFileOS.flush();
			imageFileOS.close();
			Toast.makeText(this, "Saved JPEG", Toast.LENGTH_SHORT).show();
		} catch (FileNotFoundException e) {
			Toast.makeText(this, e.getMessage(), Toast.LENGTH_SHORT).show();
		} catch (IOException e) {
			Toast.makeText(this, e.getMessage(), Toast.LENGTH_SHORT).show();
		}
		camera.startPreview();
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
