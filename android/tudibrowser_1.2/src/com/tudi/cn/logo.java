package com.tudi.cn;

import android.app.Activity;
import android.content.Intent;
import android.graphics.drawable.AnimationDrawable;
import android.os.Bundle;
import android.view.Window;
import android.view.WindowManager;
import android.widget.ImageView;

public class logo extends Activity implements Runnable{
    
	private ImageView  imageView;
	private AnimationDrawable animDrawable;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //�ޱ���
        this.requestWindowFeature(Window.FEATURE_NO_TITLE);
        //��״̬��
        this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        
        setContentView(R.layout.logo);
        
        imageView=(ImageView) findViewById(R.id.frameview);
        animDrawable=(AnimationDrawable) imageView.getBackground();
   
    //���ж��߳�
        new Thread(logo.this).start();
    
    }
    //���Activity�����Ƿ�������
    public void onWindowFocusChanged(boolean hasFocus){
    	super.onWindowFocusChanged(hasFocus);
    	animDrawable.start();
    }
	public void run() {
		
		try {
			Thread.sleep(2000L);
		
		    Intent intent=new Intent();
		    intent.setClass(logo.this, main.class);
		    startActivity(intent);
		    
		    logo.this.finish();
		
		} catch (InterruptedException e) {
			
			e.printStackTrace();
		}
		
	}
    //������������
	public  void onResume(){
		super.onResume();
	}
	
	public void onStart(){
		super.onStart();
	}
	
	public void onPause(){
		super.onPause();
	}
	
	public void onRestart(){
		super.onRestart();
	}
	
	public void onStop(){
		super.onRestart();
	}
	
	public void onDestroy(){
		super.onDestroy();
	}
	
	
	//
}