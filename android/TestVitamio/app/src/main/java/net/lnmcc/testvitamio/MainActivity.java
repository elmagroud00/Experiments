package net.lnmcc.testvitamio;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import io.vov.vitamio.LibsChecker;
import io.vov.vitamio.MediaPlayer;
import io.vov.vitamio.widget.MediaController;
import io.vov.vitamio.widget.VideoView;

public class MainActivity extends AppCompatActivity {

    private final String HLS_PATH = "http://devimages.apple.com/iphone/samples/bipbop/bipbopall.m3u8";
    private final String RTSP_PATH = "rtsp://wowzaec2demo.streamlock.net/vod/mp4:BigBuckBunny_115k.mov";
    private final String RTMP_PATH = "";

    private VideoView mVideoView;
    private Button mPlay;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        if (!LibsChecker.checkVitamioLibs(this)) {
            return;
        }

        mVideoView = (VideoView) findViewById(R.id.videoview);
        mPlay = (Button) findViewById(R.id.play);
        mPlay.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mVideoView.start();
            }
        });
    }

    @Override
    protected void onResume() {
        super.onResume();
        mVideoView.setVideoPath(RTSP_PATH);
        mVideoView.setMediaController(new MediaController(this));
        mVideoView.requestFocus();

        mVideoView.setOnPreparedListener(new MediaPlayer.OnPreparedListener() {

            @Override
            public void onPrepared(MediaPlayer mp) {
                mp.setPlaybackSpeed(1.0f);
            }
        });
    }
}
