package com.tudi.cn;

import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;


import android.app.Activity;
import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.content.ContentValues;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.DialogInterface.OnClickListener;
import android.content.DialogInterface.OnMultiChoiceClickListener;
import android.database.sqlite.SQLiteDatabase;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.os.Bundle;
import android.provider.SyncStateContract.Helpers;
import android.view.GestureDetector;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.view.GestureDetector.OnGestureListener;
import android.view.View.OnTouchListener;
import android.view.animation.Animation;
import android.view.animation.TranslateAnimation;
import android.webkit.CacheManager;
import android.webkit.URLUtil;
import android.webkit.WebChromeClient;
import android.webkit.WebIconDatabase;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.AdapterView;
import android.widget.EditText;
import android.widget.GridView;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ProgressBar;
import android.widget.RelativeLayout;
import android.widget.SimpleAdapter;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.AdapterView.OnItemClickListener;

public class main extends Activity implements OnTouchListener,
		OnGestureListener {
    //�������������ܲ���
	private RelativeLayout  skinLayout;
	
	//��һ�����벼��
	private LinearLayout myenter01;
	private EditText enterurl01;
    //�ڶ������벼��
	private LinearLayout myenter02;
	private EditText enterurl02;
	private ImageView okImageView;
    //���Ʋ���
	private WebView myWebView;
	private GestureDetector gestureDetector;
	private Boolean flag = true;
	private RelativeLayout myRelativeLayout;
    //��ַ����
	private String strURL;
	private String strindex;
	private String strurlhttp = "";

	//���⡢��������ͼ��
	private TextView    mytitle;
	private ProgressBar myProgressBar;
	private ImageView   myicon;
	
	
	private WebSettings webSettings;
	
	//�ײ��˵�
	private GridView    myGridView;
	private SimpleAdapter adapter;
	
	//��ʷ�����ݿ�
	private MySQLiteHelper mySQLiteHelper;
	private SQLiteDatabase db;
	private String         dbString;
	
	//���öԻ����������ͼ
	private GridView      setGridView;
	
	//��ҳ����
	private EditText      zhuyenameEditText;
	private EditText      zhuyeurlEditText;
	private SharedPreferences zhuyesp;
	private SharedPreferences.Editor zhuyeEditor;
	private String        queryurlString;
	//JavaScript����
	private SharedPreferences jssp;
	private SharedPreferences.Editor jsEditor;
	//��������
	private SharedPreferences cachesp;
	private SharedPreferences.Editor  cacheEditor;
	//Ƥ������
	private SharedPreferences skinsp;
	private SharedPreferences.Editor  skinEditor;
	//��ֽ����
	private SharedPreferences bizhisp;
	private SharedPreferences.Editor  bizhiEditor;
	//ɾ������ı�־��
	private boolean           cleancachebln;
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		// ȥ����
		this.requestWindowFeature(Window.FEATURE_NO_TITLE);
		// ��״̬��
		this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
				WindowManager.LayoutParams.FLAG_FULLSCREEN);

		setContentView(R.layout.main);
         
		//������ʷ���ݿ��ʵ��
		mySQLiteHelper=new MySQLiteHelper(main.this, "mydb.db", null, 1);
	    
		//�������������ܵĲ���(Ƥ��)
		skinLayout=(RelativeLayout) findViewById(R.id.skin01);
		
		// ����������ʵ��
		myenter01 = (LinearLayout) findViewById(R.id.enter01);
		enterurl01 = (EditText) findViewById(R.id.enterurl01);

		myenter02 = (LinearLayout) findViewById(R.id.enter02);
		enterurl02 = (EditText) findViewById(R.id.enterurl02);
		okImageView = (ImageView) findViewById(R.id.ImageView01);

		//���⡢��������ͼ���ʵ��
		mytitle=(TextView) findViewById(R.id.title01);
		myProgressBar=(ProgressBar) findViewById(R.id.progress_horizontal01);
		myicon=(ImageView) findViewById(R.id.icon);
		//��ȡ����վ��ͼ�꣬����������վ���ݿ��ʵ��
		final WebIconDatabase mydb=WebIconDatabase.getInstance();
		mydb.open(getDir("icons", MODE_PRIVATE).getPath());
		
		//-----------------------------------
		//SharedPreferences��ʵ�����֣���ʼ
		//-----------------------------------
		
		//��ҳ����		
		zhuyesp=main.this.getSharedPreferences("zhuyeset", MODE_PRIVATE);
		zhuyeEditor=zhuyesp.edit();
		//JavaScript����
		jssp=main.this.getSharedPreferences("jsset", MODE_PRIVATE);
		jsEditor=jssp.edit();
		//��������
		cachesp=main.this.getSharedPreferences("cacheset", MODE_PRIVATE);
		cacheEditor=cachesp.edit();
		//Ƥ������
		skinsp=main.this.getSharedPreferences("skinset", MODE_PRIVATE);
		skinEditor=skinsp.edit();
		//��ֽ����
		bizhisp=main.this.getSharedPreferences("bizhiset", MODE_PRIVATE);
		bizhiEditor=bizhisp.edit();
		//------------------------------------
		//SharedPreferences��ʵ�����֣�����
		//------------------------------------
		//---------begin:��ѯ���ݣ�����Ƥ��-------------------------------
		int skinvalue=skinsp.getInt("skin", 0);
		switch(skinvalue){
		case 0:
			skinLayout.setBackgroundColor(Color.parseColor("#ffd7d7d7"));
			break;
		case 1:
			skinLayout.setBackgroundResource(R.drawable.skin_title_jingdian);
			break;
		case 2:
			skinLayout.setBackgroundResource(R.drawable.skin_title_chitang);
			break;
		case 3:
			skinLayout.setBackgroundResource(R.drawable.skin_title_jijingshouwang);
			break;
		case 4:
			skinLayout.setBackgroundResource(R.drawable.skin_title_kewangfeixiang);
			break;
		case 5:
			skinLayout.setBackgroundResource(R.drawable.skin_title_mengdong);
			break;
		case 6:
			skinLayout.setBackgroundResource(R.drawable.skin_title_xuanlan);
			break;
		case 7:
			skinLayout.setBackgroundResource(R.drawable.skin_title_hetang);
			break;
		case 8:
			skinLayout.setBackgroundResource(R.drawable.skin_title_zhanlantiankong);
			break;
		case 9:
			skinLayout.setBackgroundResource(R.drawable.skin_title_qingchasiyu);
			break;
		}
		
		
		//--------end:��ѯ���ݣ�����Ƥ��-----------------------------------------------------------
		// -----begin��ҳ����---------------------------------------------------------
		// ��ҳ��ͼ��ʵ��
		myWebView = (WebView) findViewById(R.id.WebView01);
		//��ҳ��ͼ�ı�ֽ����
		int bizhivalue=bizhisp.getInt("bizhi", 0);
		switch(bizhivalue){
		case 0:
			myWebView.setBackgroundColor(0);
			myWebView.setBackgroundResource(R.drawable.white);
			break;
		case 1:
			myWebView.setBackgroundColor(0);
			myWebView.setBackgroundResource(R.drawable.chuntian);
			break;
		case 2:
			myWebView.setBackgroundColor(0);
			myWebView.setBackgroundResource(R.drawable.xiatian);
			break;
		case 3:
			myWebView.setBackgroundColor(0);
			myWebView.setBackgroundResource(R.drawable.xianhuaduoduo);
			break;
		case 4:
			myWebView.setBackgroundColor(0);
			myWebView.setBackgroundResource(R.drawable.huayu);
			break;
		}
		
		myWebView.setOnTouchListener(main.this);
		gestureDetector = new GestureDetector(main.this);
		// ��ҳ�ĸ�����ͼ��ʵ��
		myRelativeLayout = (RelativeLayout) findViewById(R.id.skin01);

		// ������ҳ�ͻ���
		myWebView.setWebViewClient(new WebViewClient() {

		});
        //������ҳchrome�ͻ���
		myWebView.setWebChromeClient(new WebChromeClient(){
		    //���ñ���
			public void onReceivedTitle(WebView view,String title){
				super.onReceivedTitle(view, title);
				title=myWebView.getTitle();
				dbString=title;
				mytitle.setText(title);
			}
			//���ý�����
			public void onProgressChanged(WebView view,int progress){
				myProgressBar.setProgress(progress);
				if(progress==100){
					myProgressBar.setProgress(0);
				}
			}
			
			//����ͼ��
			public void onReceivedIcon(WebView view,Bitmap icon){
				super.onReceivedIcon(view, icon);
				icon=myWebView.getFavicon();
				myicon.setImageBitmap(icon);
			}
			
		
			
			
		});
		
		
		
		
		// ------end��ҳ����---------------------------------------------------------------------

		// �����ĵ���¼�
		enterurl01.setOnClickListener(new LinearLayout.OnClickListener() {

			public void onClick(View v) {
				myenter01.setVisibility(View.GONE);
				myenter02.setVisibility(View.VISIBLE);
			}

		});
		// ͼƬ��ť�ĵ���¼�
		okImageView.setOnClickListener(new ImageView.OnClickListener() {

			public void onClick(View v) {
				myenter02.setVisibility(View.GONE);
				myenter01.setVisibility(View.VISIBLE);
				// ȡ����ַ
				strURL = enterurl02.getText().toString();
				int length = strURL.length();
				if (length == 0) {
					Toast.makeText(main.this, "��������ַ��", Toast.LENGTH_SHORT)
							.show();
				} else {
					strindex = strURL.substring(0, 7);
					boolean bln = strindex.equalsIgnoreCase("http://");
					if (bln == true) {

						if (URLUtil.isNetworkUrl(strURL)) {// ������ַ�ĺϷ����ж�

							myWebView.loadUrl(strURL);
                            
							db=mySQLiteHelper.getReadableDatabase();
							//�����ݱ��浽��ʷ���ݿ���
							ContentValues cv=new ContentValues();							
							cv.put("title", dbString);
							cv.put("url", strURL);
							db.insert("history", null, cv);
						
							
						} else {
							Toast.makeText(main.this, "������Ϸ�����ַ��лл��",
									Toast.LENGTH_SHORT).show();
						}
					} else if (bln == false) {
						strURL = ("http://" + strURL);
						if (URLUtil.isNetworkUrl(strURL)) {
							myWebView.loadUrl(strURL);
							
							db=mySQLiteHelper.getReadableDatabase();
							//�����ݱ��浽��ʷ���ݿ���
							ContentValues cv=new ContentValues();						
							cv.put("title", dbString);
							cv.put("url", strURL);
							db.insert("history", null, cv);
						   //mydb.execSQL("insert into historytable(_id,title,url) values(1,dbString,strURL);"); 
						} else {
							Toast.makeText(main.this, "������Ϸ�����ַ��лл��",
									Toast.LENGTH_SHORT).show();
						}
					}

				}

				enterurl02.setText("");

			}

		});

		//------begin��ҳ�ĸ�������-------------------------------------
		webSettings=myWebView.getSettings();
		//JavaScript������
		boolean jsbln=jssp.getBoolean("jsbln", false);
		if(jsbln==true){
		webSettings.setJavaScriptEnabled(true);	
		}else if(jsbln==false){
		webSettings.setJavaScriptEnabled(false);
		//����
		int cachevalue=cachesp.getInt("cache", 1);
		if(cachevalue==0){
		webSettings.setAppCacheEnabled(true);	
		}else if(cachevalue==1){
		webSettings.setAppCacheEnabled(false);	
		}
		
		}
		
		
		
		//------end��ҳ�ĸ�������-------------------------------------------------------
		
	    
	    
	}

	// ---------begin���������������Ƽ����ķ���-------------------------------------------------------

	public boolean onTouch(View v, MotionEvent event) {
		gestureDetector.onTouchEvent(event);// ���������¼����������¼�
        
		//���󽹵�
		myWebView.requestFocus();

		
		
		return false;
	}

	public boolean onDown(MotionEvent e) {
		if (flag == true) {
			int height = myRelativeLayout.getHeight();
			Animation myTranslateAnimation = new TranslateAnimation(0, 0, 0,
					-height);
			myTranslateAnimation.setDuration(500);
			myRelativeLayout.setAnimation(myTranslateAnimation);
			myRelativeLayout.setVisibility(View.GONE);
			flag = false;
		}

		return true;
	}

	public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX,
			float velocityY) {
		float vx = Math.abs(velocityX);// ȡ�����ֵ
		float vy = Math.abs(velocityY);
		//----begin���ø�����ĵ������ջ�--------------------
		if (vy > vx) {
			if (velocityY > 0) {//���õ���
				if (flag == false) {

					int height = myRelativeLayout.getHeight();
					Animation myTranslateAnimation = new TranslateAnimation(0,
							0, -height, 0);
					myTranslateAnimation.setDuration(500);
					myRelativeLayout.setAnimation(myTranslateAnimation);
					myRelativeLayout.setVisibility(View.VISIBLE);

					flag = true;
				}

			} else if (velocityY < 0) {//�����ջ�

				if (flag == true) {
					int height = myRelativeLayout.getHeight();
					Animation myTranslateAnimation = new TranslateAnimation(0,
							0, 0, -height);
					myTranslateAnimation.setDuration(500);
					myRelativeLayout.setAnimation(myTranslateAnimation);
					myRelativeLayout.setVisibility(View.GONE);
					flag = false;
				}

			}

		}else
		//-----end���ø�����ĵ������ջ�---------------------------------	
		//-----begin�������һ�����ҳ-----------------------	
		if(vx>vy){
		if(velocityX>0){//ǰһҳ
		   if(myWebView.canGoBack()){
			  
			   myWebView.goBack(); 
			   
			   int width=myWebView.getWidth();
			   Animation myTranslateAnimation=new TranslateAnimation(0,width,0,0);
			   myTranslateAnimation.setDuration(400);
			   myWebView.setAnimation(myTranslateAnimation);
			   
			  
		   }
		}else if(velocityX<0){//��һҳ
			if(myWebView.canGoForward()){
			  
				myWebView.goForward();
				
				int width=myWebView.getWidth();
				Animation myTranslateAnimation=new TranslateAnimation(0,-width,0,0);
				myTranslateAnimation.setDuration(400);
				myWebView.setAnimation(myTranslateAnimation);
				
				
			}
		}
		}
		//-----end�������һ�����ҳ------------------------
		return false;
	}

	public void onLongPress(MotionEvent e) {
		// TODO Auto-generated method stub

	}

	public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX,
			float distanceY) {
		// TODO Auto-generated method stub
		return false;
	}

	public void onShowPress(MotionEvent e) {
		// TODO Auto-generated method stub

	}

	public boolean onSingleTapUp(MotionEvent e) {
		// TODO Auto-generated method stub
		return false;
	}
	// --------end���������������Ƽ����ķ���----------------------------------------------

	//__________________________________________________________________________________
	//-------------(begin)�����ĵ���¼�------------------------------------------------------
	//___________________________________________________________________________________
	
	public boolean onKeyDown(int keyCode,KeyEvent event){
		
		switch(keyCode){
		case KeyEvent.KEYCODE_MENU:
			//���뷽��
			if(myGridView==null){
			
			loadBottomMenu();
			
			}
			if(myGridView.getVisibility()==View.GONE){
				myGridView.setVisibility(View.VISIBLE);
			}else{
				myGridView.setVisibility(View.GONE);
			}
			break;
		
		//���ؼ����¼�
		case KeyEvent.KEYCODE_BACK:
			
			Builder exitBuilder=new Builder(main.this);
			exitBuilder.setIcon(R.drawable.siyecao30);
			exitBuilder.setTitle("�˳���ʾ");
			exitBuilder.setMultiChoiceItems(new String[]{"ɾ������"}, new boolean[]{false}, new OnMultiChoiceClickListener(){

				public void onClick(DialogInterface dialog, int which,
						boolean isChecked) {
				switch(which){
				case 0:
					if(isChecked==true){
					cleancachebln=true;	
					}
					break;
				}
					
				}

				});
			exitBuilder.setPositiveButton("ȷ��", new OnClickListener(){

				public void onClick(DialogInterface dialog, int which) {
					if(cleancachebln==true){
					File file=CacheManager.getCacheFileBaseDir();
					if(file!=null&&file.exists()&&file.isDirectory()){
					
						for(File item:file.listFiles()){
							item.delete();
						}
						file.delete();
					}
					main.this.deleteDatabase("webview.db");
					main.this.deleteDatabase("webviewCache.db");
					Toast.makeText(main.this,"����ɾ���ɹ���", Toast.LENGTH_LONG).show();
					}
					
					main.this.finish();
				}
				
			});
			exitBuilder.setNegativeButton("ȡ��", new OnClickListener(){

				public void onClick(DialogInterface dialog, int which) {
					
					
				}
				
			});
			exitBuilder.show();
			break;
		
		
		
		}
		
		return super.onKeyDown(keyCode, event);
	}
	
	//__________________________________________________________________________________
	//-------------(end)�����ĵ���¼�------------------------------------------------------
	//___________________________________________________________________________________
	
	//-------------begin����ײ��˵��ķ���---------------------------------------------------------------------
	public void loadBottomMenu(){
		myGridView=(GridView) findViewById(R.id.GridView01);
		//���ò˵���
		myGridView.setNumColumns(5);
		myGridView.setGravity(Gravity.CENTER);
		myGridView.setVerticalSpacing(10);
		myGridView.setHorizontalSpacing(10);
		
		ArrayList arrayList=new ArrayList();
		HashMap hashMap=new HashMap();
		hashMap.put("itemimage", R.drawable.fangda);
		arrayList.add(hashMap);
		
		hashMap=new HashMap();
		hashMap.put("itemimage", R.drawable.suoxiao);
		arrayList.add(hashMap);
		
		hashMap=new HashMap();
		hashMap.put("itemimage", R.drawable.home);
		arrayList.add(hashMap);
		
		hashMap=new HashMap();
		hashMap.put("itemimage", R.drawable.history);
		arrayList.add(hashMap);
		
		hashMap=new HashMap();
		hashMap.put("itemimage", R.drawable.set);
		arrayList.add(hashMap);
		
		adapter=new SimpleAdapter(this, arrayList, R.layout.bottommenu, new String[]{"itemimage"}, new int[]{R.id.item});
		
		myGridView.setAdapter(adapter);
		
		myGridView.setOnItemClickListener(new OnItemClickListener(){

			public void onItemClick(AdapterView<?> arg0, View arg1, int which,
					long arg3) {
			switch(which){
			    case 0:
				webSettings.setDefaultZoom(WebSettings.ZoomDensity.CLOSE);
				    break;
			    case 1:
			    webSettings.setDefaultZoom(WebSettings.ZoomDensity.FAR);	
			    	break;
			    case 2:
			    //��ѯ��ҳ�����е�ֵ
			    	 queryurlString=zhuyesp.getString("url", "http://www.baidu.cn");
			    	//�ж���ַ��ǰ׺�Ƿ����http://
			    	String strindex=queryurlString.substring(0,7);
			    	boolean bln=strindex.equalsIgnoreCase("http://");
			    	if(bln==true){
			    	
			    		if(URLUtil.isNetworkUrl(queryurlString)){
			    			myWebView.loadUrl(queryurlString);		
			    		}else{
			    			Toast.makeText(main.this, "��ַ���Ϸ���", Toast.LENGTH_LONG).show();
			    		}
			    	}else if(bln==false){
			    		queryurlString="http://"+queryurlString;
			    		if(URLUtil.isNetworkUrl(queryurlString)){
			    			myWebView.loadUrl(queryurlString);		
			    		}else{
			    			Toast.makeText(main.this, "��ַ���Ϸ���", Toast.LENGTH_LONG).show();
			    		}
			    	}
			    	
			    	
			    	break;
			    case 3:
			    	Intent intent=new Intent();
			    	intent.setClass(main.this, bookmarkandhistory.class);
			    	startActivity(intent);
			    	main.this.finish();			    	
			    	break;
			    case 4:
			    	//�����öԻ���
			    	setdialoge();
			    				    	
			    	break;
				
			}
				
			}
			
		});
	}
	
	
	//-------------end����ײ��˵��ķ���----------------------------------------------------------------------
	//-------------begin:���öԻ���-----------------------------------------------------------------------
	public void setdialoge(){
	
		//�������öԻ���
    	final AlertDialog setBuilder=new Builder(main.this).create();

    	//�������öԻ������ͼ
    	LayoutInflater inflater=LayoutInflater.from(main.this);
    	View view=inflater.inflate(R.layout.setview, null);
    	setGridView=(GridView) view.findViewById(R.id.GridView01);
    	
    	ArrayList  arrayList=new ArrayList();
    	
    	HashMap map=new HashMap();
    	map.put("imageitem", R.drawable.skin);
    	map.put("textitem", "Ƥ��");
    	arrayList.add(map);
    	
    	map=new HashMap();
    	map.put("imageitem", R.drawable.bizhi);
    	map.put("textitem", "��ֽ");
    	arrayList.add(map);
    	
    	map=new HashMap();
    	map.put("imageitem", R.drawable.zhuye);
    	map.put("textitem", "��ҳ");
    	arrayList.add(map);
    	
    	map=new HashMap();
    	map.put("imageitem", R.drawable.js);
    	map.put("textitem", "JavaScript");
    	arrayList.add(map);
    	
    	map=new HashMap();
    	map.put("imageitem", R.drawable.huancun);
    	map.put("textitem", "����");
    	arrayList.add(map);
    	
    	map=new HashMap();
    	map.put("imageitem", R.drawable.help);
    	map.put("textitem", "����");
    	arrayList.add(map);
    	
    	map=new HashMap();
    	map.put("imageitem", R.drawable.about);
    	map.put("textitem", "����");
    	arrayList.add(map);
    	
    	map=new HashMap();
    	map.put("imageitem", R.drawable.menu_return);
    	map.put("textitem", "����");
    	arrayList.add(map);
    	
    	SimpleAdapter setsa=new SimpleAdapter(main.this, arrayList, R.layout.setviewitem, new String[]{"imageitem","textitem"}, new int[]{R.id.ImageView01,R.id.TextView01});
    	setGridView.setAdapter(setsa);
    	
    	
    	//�����ͼ
    	setBuilder.setView(view);
    	
    	setBuilder.show();
    	//--------begin:������ͼ�ĵ���¼�------------------------------------------------------
    	setGridView.setOnItemClickListener(new OnItemClickListener(){

			public void onItemClick(AdapterView<?> arg0, View arg1, int which,
					long arg3) {
			switch(which){
			
			case 0:
				//Ƥ������
				Builder builder=new Builder(main.this);
				builder.setIcon(R.drawable.siyecao30);
				builder.setTitle("Ƥ������");
				builder.setSingleChoiceItems(new String[]{"Ĭ��Ƥ��","���»ö�","ˮī����","�ž�����","��������","�ȶ���ɫ","Ѥ��Ʈ��","������ɫ","տ�����","���˿��"}, -1, new OnClickListener(){

					public void onClick(DialogInterface dialog, int which) {
					switch(which){
					
					case 0:
						skinLayout.setBackgroundColor(Color.parseColor("#ffd7d7d7"));
						Toast.makeText(main.this, "Ĭ������", Toast.LENGTH_LONG).show();
						//�������õ�����
						skinEditor.putInt("skin", 0);
						skinEditor.commit();
						
						break;
					case 1:
						skinLayout.setBackgroundResource(R.drawable.skin_title_jingdian);
						Toast.makeText(main.this, "���»ö�", Toast.LENGTH_LONG).show();
						//�������õ�����
						skinEditor.putInt("skin", 1);
						skinEditor.commit();
						break;
						
					case 2:
						skinLayout.setBackgroundResource(R.drawable.skin_title_chitang);
						Toast.makeText(main.this, "ˮī����", Toast.LENGTH_LONG).show();
						//�������õ�����
						skinEditor.putInt("skin", 2);
						skinEditor.commit();
						
						break;
						
					case 3:
						skinLayout.setBackgroundResource(R.drawable.skin_title_jijingshouwang);
						Toast.makeText(main.this, "�ž�����", Toast.LENGTH_LONG).show();
						//�������õ�����
						skinEditor.putInt("skin", 3);
						skinEditor.commit();
						break;
						
					case 4:
						skinLayout.setBackgroundResource(R.drawable.skin_title_kewangfeixiang);
						Toast.makeText(main.this, "��������", Toast.LENGTH_LONG).show();
						//�������õ�����
						skinEditor.putInt("skin", 4);
						skinEditor.commit();
						break;
						
					case 5:
						skinLayout.setBackgroundResource(R.drawable.skin_title_mengdong);
						Toast.makeText(main.this, "�ȶ���ɫ", Toast.LENGTH_LONG).show();
						//�������õ�����
						skinEditor.putInt("skin", 5);
						skinEditor.commit();
						break;
						
					case 6:
						skinLayout.setBackgroundResource(R.drawable.skin_title_xuanlan);
						Toast.makeText(main.this, "Ѥ��Ʈ��", Toast.LENGTH_LONG).show();
						//�������õ�����
						skinEditor.putInt("skin", 6);
						skinEditor.commit();
						break;
						
					case 7:
						skinLayout.setBackgroundResource(R.drawable.skin_title_hetang);
						Toast.makeText(main.this, "������ɫ", Toast.LENGTH_LONG).show();
						//�������õ�����
						skinEditor.putInt("skin", 7);
						skinEditor.commit();
						break;
						
					case 8:
						skinLayout.setBackgroundResource(R.drawable.skin_title_zhanlantiankong);
						Toast.makeText(main.this, "տ�����", Toast.LENGTH_LONG).show();
						//�������õ�����
						skinEditor.putInt("skin", 8);
						skinEditor.commit();
						break;
						
					case 9:
						skinLayout.setBackgroundResource(R.drawable.skin_title_qingchasiyu);
						Toast.makeText(main.this, "���˿��", Toast.LENGTH_LONG).show();
						//�������õ�����
						skinEditor.putInt("skin", 9);
						skinEditor.commit();
						break;
					
					}
						
					}
					
				});
				builder.setPositiveButton("����", new OnClickListener(){

					public void onClick(DialogInterface dialog, int which) {
						
						
					}
					
				});
				builder.show();
				break;
			case 1:
				//��ֽ����
				Builder bizhiBuilder=new Builder(main.this);
				bizhiBuilder.setIcon(R.drawable.siyecao30);
				bizhiBuilder.setTitle("��ֽ����");
				bizhiBuilder.setSingleChoiceItems(new String[]{"Ĭ�ϱ�ֽ","��ɫ����","������Ӱ","�ʻ����","�ۻ���¶"}, -1, new OnClickListener(){

					public void onClick(DialogInterface dialog, int which) {
					switch(which){
					case 0:
						//Ĭ�ϱ�ֽ
						myWebView.setBackgroundColor(0);
						myWebView.setBackgroundResource(R.drawable.white);
						//������������
						bizhiEditor.putInt("bizhi", 0);
						bizhiEditor.commit();
						break;
					case 1:
						//��ɫ����
						myWebView.setBackgroundColor(0);
						myWebView.setBackgroundResource(R.drawable.chuntian);
						//������������
						bizhiEditor.putInt("bizhi", 1);
						bizhiEditor.commit();
						break;
						
					case 2:
						//������Ӱ
						myWebView.setBackgroundColor(0);
						myWebView.setBackgroundResource(R.drawable.xiatian);
						//������������
						bizhiEditor.putInt("bizhi", 2);
						bizhiEditor.commit();
						break;
					case 3:
						//�ʻ����
						myWebView.setBackgroundColor(0);
						myWebView.setBackgroundResource(R.drawable.xianhuaduoduo);
						//������������
						bizhiEditor.putInt("bizhi", 3);
						bizhiEditor.commit();
						break;
					case 4:
						//�ۻ���¶
						myWebView.setBackgroundColor(0);
						myWebView.setBackgroundResource(R.drawable.huayu);
						//������������
						bizhiEditor.putInt("bizhi", 4);
						bizhiEditor.commit();
						break;
					}
						
					}
					
				});
				bizhiBuilder.setPositiveButton("����", new OnClickListener(){

					public void onClick(DialogInterface dialog, int which) {
						
						
					}
					
				});
				bizhiBuilder.show();
				break;
				
			case 2:				
				//��ҳ����
				Builder zhuyeBuilder=new Builder(main.this);
				zhuyeBuilder.setIcon(R.drawable.siyecao30);
				zhuyeBuilder.setTitle("��ҳ����");
				LayoutInflater inflater=LayoutInflater.from(main.this);
				View view=inflater.inflate(R.layout.zhuyeset, null);
				
				zhuyenameEditText=(EditText) view.findViewById(R.id.EditText01);
				zhuyeurlEditText=(EditText) view.findViewById(R.id.EditText02);
				//��ѯ�����ֵ
				String queryzhuyename=zhuyesp.getString("name", "��վ����");
				String queryzhuyeurl=zhuyesp.getString("url","��ַ");
				//����ѯ��ֵ��ӵ��༭��
				zhuyenameEditText.setText(queryzhuyename);
				zhuyeurlEditText.setText(queryzhuyeurl);
				
				zhuyeBuilder.setView(view);
				zhuyeBuilder.setPositiveButton("ȷ��", new OnClickListener(){

					public void onClick(DialogInterface dialog, int which) {
					//ȡ�ñ༭���ֵ
					String zhuyename=zhuyenameEditText.getText().toString();
					String zhuyeurl=zhuyeurlEditText.getText().toString();
					//���༭���е�ֵ���б���
					zhuyeEditor.putString("name", zhuyename);
					zhuyeEditor.putString("url", zhuyeurl);
					zhuyeEditor.commit();
					}
					
				});
				zhuyeBuilder.setNegativeButton("ȡ��", new OnClickListener(){

					public void onClick(DialogInterface dialog, int which) {
						
						
					}
					
				});
				zhuyeBuilder.show();
				break;
				
			case 3:
				//JavaScript����
				Builder jsBuilder=new Builder(main.this);
				jsBuilder.setIcon(R.drawable.siyecao30);
				jsBuilder.setTitle("JavaScript����");
				jsBuilder.setSingleChoiceItems(new String[]{"��","�ر�"}, -1, new OnClickListener(){

					public void onClick(DialogInterface dialog, int which) {
					switch(which){
					
					case 0:
						WebSettings myWebSettings=myWebView.getSettings();
						myWebSettings.setJavaScriptEnabled(true);
						//��������
						jsEditor.putBoolean("jsbln", true);
						jsEditor.commit();
						break;
					case 1:
						WebSettings myWebSettings2=myWebView.getSettings();
						myWebSettings2.setJavaScriptEnabled(false);
						//��������
						jsEditor.putBoolean("jsbln", false);
						jsEditor.commit();
						
						break;
					
					}
						
					}
					
				});
				jsBuilder.setPositiveButton("����", new OnClickListener(){

					public void onClick(DialogInterface dialog, int which) {
						// TODO Auto-generated method stub
						
					}
					
				});
				jsBuilder.show();
				break;
				
			case 4:
				//��������
				Builder cacheBuilder=new Builder(main.this);
				cacheBuilder.setIcon(R.drawable.siyecao30);
				cacheBuilder.setTitle("��������");
				cacheBuilder.setSingleChoiceItems(new String[]{"�����","����ر�"}, -1, new OnClickListener(){

					public void onClick(DialogInterface dialog, int which) {
					switch(which){
					case 0:
					WebSettings myWebSettings=myWebView.getSettings();
					myWebSettings.setAppCacheEnabled(true);
					//�������õ�����
					cacheEditor.putInt("cache", 0);
					cacheEditor.commit();
					break;
					case 1:
					WebSettings myWebSettings2=myWebView.getSettings();
					myWebSettings2.setAppCacheEnabled(false);
					//�������õ�����
					cacheEditor.putInt("cache", 1);
					cacheEditor.commit();
					break;
					
					}	
					}});
				cacheBuilder.setPositiveButton("����", new OnClickListener(){

					public void onClick(DialogInterface dialog, int which) {
						
						
					}});
				cacheBuilder.show();
				break;
			
			case 5:
				Builder helpBuilder=new Builder(main.this);
				helpBuilder.setIcon(R.drawable.siyecao30);
				helpBuilder.setTitle("����");
				LayoutInflater inflater2=LayoutInflater.from(main.this);
				View view2=inflater2.inflate(R.layout.help, null);
				helpBuilder.setView(view2);
				helpBuilder.setPositiveButton("����", new OnClickListener(){

					public void onClick(DialogInterface dialog, int which) {
						
						
					}
					
				});
				helpBuilder.show();
				break;
				
			case 6:
				Builder aboutBuilder=new Builder(main.this);
				aboutBuilder.setIcon(R.drawable.siyecao30);
				aboutBuilder.setTitle("����");
				LayoutInflater inflater3=LayoutInflater.from(main.this);
				View view3=inflater3.inflate(R.layout.about, null);
				aboutBuilder.setView(view3);
				aboutBuilder.setPositiveButton("����", new OnClickListener(){

					public void onClick(DialogInterface dialog, int which) {
						
						
					}});
				aboutBuilder.show();
				break;
				
			case 7:
				 setBuilder.cancel();
				break;
			
			
			}
				
			}
    		
    	});
    	//-------end:������ͼ�ĵ���¼�---------------------------------------------------------
    	
	}
	
	
	//-------------end:���öԻ���-----------------------------------------------------------------------
//�����������������
	public void onStart(){
		super.onStart();
	}

    public void onResume(){
    	super.onResume();
    }
   public void  onPause(){
	   super.onPause();
   }
   public void  onRestart(){
	   super.onRestart();
   }
   public void onStop(){
	   super.onStop();
   }
   public void onDestroy(){
	   super.onDestroy();
   }
   
   
}
