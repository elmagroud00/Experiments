package com.example.backgroundaudiobind;

import android.app.Service;
import android.content.Intent;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnCompletionListener;
import android.os.Binder;
import android.os.IBinder;

public class BackgrondAudioService extends Service implements
		OnCompletionListener {

	MediaPlayer mediaPlayer;
	private final IBinder basBinder = new BackgroundAudioServiceBinder();

	public class BackgroundAudioServiceBinder extends Binder {

		BackgrondAudioService getService() {
			return BackgrondAudioService.this;
		}
	}

	@Override
	public IBinder onBind(Intent intent) {
		return basBinder;
	}
	
	public void haveFun() {
		if(mediaPlayer.isPlaying()) {
			mediaPlayer.seekTo(mediaPlayer.getCurrentPosition() - 5000);
		}
	}

}
