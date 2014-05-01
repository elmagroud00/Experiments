package net.lnmcc.backgroundaudio;

import android.app.Service;
import android.content.Intent;
import android.media.MediaPlayer;
import android.os.IBinder;

public class BackgroundAudioService extends Service {

	MediaPlayer mediaPlayer;
	
	@Override
	public IBinder onBind(Intent intent) {
		return null;
	}

	@Override
	public void onCreate() {
		super.onCreate();
		
		mediaPlayer = MediaPlayer.create(this, R.raw.deep);
		mediaPlayer.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {
			
			@Override
			public void onCompletion(MediaPlayer mp) {
				stopSelf();
			}
		});
	}
	
	@Override
	public int onStartCommand(Intent intent, int flags, int startId) {
		
		if(!mediaPlayer.isPlaying()) {
			mediaPlayer.start();
		}
		return START_STICKY;
	}
	
	@Override
	public void onDestroy() {
		super.onDestroy();
		if(mediaPlayer.isPlaying()) {
			mediaPlayer.stop();
		}
		mediaPlayer.release();
	}
}
