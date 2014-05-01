package com.example.mybrowser;

import java.util.ArrayList;
import java.util.HashMap;

import com.example.mybroswer.R;

import android.R.integer;
import android.app.Activity;
import android.content.ContentValues;
import android.content.Intent;
import android.database.sqlite.SQLiteDatabase;
import android.gesture.GestureOverlayView.OnGestureListener;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.view.GestureDetector;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MotionEvent;
import android.view.View;
import android.view.Window;
import android.view.View.OnTouchListener;
import android.view.WindowManager;
import android.view.animation.Animation;
import android.view.animation.TranslateAnimation;
import android.webkit.URLUtil;
import android.webkit.WebChromeClient;
import android.webkit.WebIconDatabase;
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

public class Browser extends Activity implements View.OnTouchListener,
		android.view.GestureDetector.OnGestureListener {

	private RelativeLayout relativeLayout01;

	private LinearLayout enter01;
	private EditText enterurl01;
	private ProgressBar progressBar;
	private LinearLayout enter02;
	private EditText enterurl02;
	private ImageView okImageView;
	private GestureDetector gestureDetector;
	private WebView webView01;
	boolean flag;
	private TextView titleTV;
	private ImageView iconIV;
	private WebIconDatabase webIcondb;

	private SQLiteDatabase db;;
	private DBHelper dbHelper;
	private GridView menuGV;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
				WindowManager.LayoutParams.FLAG_FULLSCREEN);
		setContentView(R.layout.browser);

		dbHelper = new DBHelper(this, DBHelper.DATABASE_NAME, null,
				DBHelper.DATABASE_VERSION);
		db = dbHelper.getWritableDatabase();

		menuGV = (GridView) findViewById(R.id.MenuGridView);
		loadMenuGrid();

		relativeLayout01 = (RelativeLayout) findViewById(R.id.skin01);
		titleTV = (TextView) findViewById(R.id.title01);
		iconIV = (ImageView) findViewById(R.id.icon);
		enterurl01 = (EditText) findViewById(R.id.enterurl01);
		webIcondb = WebIconDatabase.getInstance();
		webIcondb.open(getDir("icons", MODE_PRIVATE).getPath());
		progressBar = (ProgressBar) findViewById(R.id.progress_horizontal01);
 
		webView01 = (WebView) findViewById(R.id.WebView01);
		webView01.setOnTouchListener(this);
		webView01.setWebViewClient(new WebViewClient() {

		});
		webView01.setWebChromeClient(new WebChromeClient() {
			@Override
			public void onReceivedTitle(WebView view, String title) {
				super.onReceivedTitle(view, title);
				titleTV.setText(title);
			}

			@Override
			public void onReceivedIcon(WebView view, Bitmap icon) {
				super.onReceivedIcon(view, icon);
				iconIV.setImageBitmap(icon);
			}

			@Override
			public void onProgressChanged(WebView view, int newProgress) {
				progressBar.setProgress(newProgress);
				enterurl01.setText(webView01.getUrl());
				if (newProgress == 100) {
					progressBar.setProgress(0);
					addToHistory(webView01.getTitle(), webView01.getUrl());
				}
			}

			@Override
			public void onReceivedTouchIconUrl(WebView view, String url,
					boolean precomposed) {
				super.onReceivedTouchIconUrl(view, url, precomposed);
			}
		});

		enter01 = (LinearLayout) findViewById(R.id.enter01);
		enterurl01 = (EditText) findViewById(R.id.enterurl01);
		enterurl01.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				enter01.setVisibility(View.GONE);
				enter02.setVisibility(View.VISIBLE);
			}
		});

		enter02 = (LinearLayout) findViewById(R.id.enter02);
		enterurl02 = (EditText) findViewById(R.id.enterurl02);

		okImageView = (ImageView) findViewById(R.id.ImageView01);
		okImageView.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				enter02.setVisibility(View.GONE);
				enter01.setVisibility(View.VISIBLE);

				String strUrl = enterurl02.getText().toString();
				int length = strUrl.length();
				if (length == 0) {
					Toast.makeText(Browser.this, "Please input URL",
							Toast.LENGTH_LONG).show();
				} else {
					String strindex = strUrl.substring(0, 7);
					boolean bln = strindex.equalsIgnoreCase("http://");
					if (bln == true) {
						if (URLUtil.isNetworkUrl(strUrl)) {
							webView01.loadUrl(strUrl);
						} else {
							Toast.makeText(Browser.this,
									"Please input correct URL",
									Toast.LENGTH_LONG).show();
						}
					} else {
						strUrl = "http://" + strUrl;
						if (URLUtil.isNetworkUrl(strUrl)) {
							webView01.loadUrl(strUrl);
						} else {
							Toast.makeText(Browser.this,
									"Please input correct URL",
									Toast.LENGTH_LONG).show();
						}
					}
				}
				enterurl02.setText("");
			}
		});

		gestureDetector = new GestureDetector(this, this);
		flag = true;
	}

	private void addToHistory(String title, String url) {
		ContentValues values = new ContentValues();
		values.put(DBHelper.WEB_TITLE_COLUM, title);
		values.put(DBHelper.WEB_URL_COLUM, url);
		db.insert(DBHelper.TABLE_HISTORY, null, values);
	}

	private void loadMenuGrid() {
		ArrayList<HashMap<String, Integer>> arrayList = new ArrayList<HashMap<String, Integer>>();
		HashMap<String, Integer> hashMap = new HashMap<String, Integer>();
		hashMap.put("image", R.drawable.history);
		arrayList.add(hashMap);
		hashMap = new HashMap<String, Integer>();
		hashMap.put("image", R.drawable.favorite);
		arrayList.add(hashMap);

		String[] from = new String[] { "image" };
		int[] to = new int[] { R.id.menuitem };
		SimpleAdapter adapter = new SimpleAdapter(this, arrayList,
				R.layout.menu, from, to);
		menuGV.setAdapter(adapter);

		menuGV.setOnItemClickListener(new AdapterView.OnItemClickListener() {
			@Override
			public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
					long arg3) {
				switch (arg2) {
				case 0:// history
					Intent intent = new Intent();
					intent.setClass(Browser.this, History.class);
					startActivity(intent);
					break;
				case 1:// favorite
					break;
				default:
					break;
				}
			}

		});
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		db.close();
	}

	@Override
	public boolean onTouchEvent(MotionEvent event) {
		return false;
	}

	@Override
	public boolean onDown(MotionEvent e) {
		if (flag == true) {
			int height = relativeLayout01.getHeight();
			Animation myTranslateAnimation = new TranslateAnimation(0, 0, 0,
					-height);
			myTranslateAnimation.setDuration(500);
			relativeLayout01.setAnimation(myTranslateAnimation);
			relativeLayout01.setVisibility(View.GONE);
			flag = false;
		}
		return false;
	}

	@Override
	public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX,
			float velocityY) {

		float vx = Math.abs(velocityX);
		float vy = Math.abs(velocityY);
		// ??????????????????
		if (vy > vx) {
			if (velocityY > 0) {
				if (flag == false) {
					int height = relativeLayout01.getHeight();
					Animation myTranslateAnimation = new TranslateAnimation(0,
							0, -height, 0);
					myTranslateAnimation.setDuration(500);
					relativeLayout01.setAnimation(myTranslateAnimation);
					relativeLayout01.setVisibility(View.VISIBLE);
					flag = true;
				}
			} else if (velocityY < 0) {
				if (flag == true) {
					int height = relativeLayout01.getHeight();
					Animation myTranslateAnimation = new TranslateAnimation(0,
							0, 0, -height);
					myTranslateAnimation.setDuration(500);
					relativeLayout01.setAnimation(myTranslateAnimation);
					relativeLayout01.setVisibility(View.VISIBLE);
					flag = false;
				}
			}
		}
		// ?????????????????????????????????
		if (vx > vy) {
			if (velocityX > 0) {
				if (webView01.canGoBack()) {
					webView01.goBack();
					int width = webView01.getWidth();
					Animation translateAnimation = new TranslateAnimation(0,
							width, 0, 0);
					translateAnimation.setDuration(300);
					webView01.setAnimation(translateAnimation);
				}
			} else if (velocityX < 0) {
				if (webView01.canGoForward()) {
					webView01.goForward();
					int width = webView01.getWidth();
					Animation translateAnimation = new TranslateAnimation(0,
							-width, 0, 0);
					translateAnimation.setDuration(300);
					webView01.setAnimation(translateAnimation);
				}
			}
		}

		return false;
	}

	@Override
	public boolean onTouch(View v, MotionEvent event) {
		gestureDetector.onTouchEvent(event);
		return false;
	}

	@Override
	public void onLongPress(MotionEvent e) {
	}

	@Override
	public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX,
			float distanceY) {
		return false;
	}

	@Override
	public void onShowPress(MotionEvent e) {
	}

	@Override
	public boolean onSingleTapUp(MotionEvent e) {
		return false;
	}

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		switch (keyCode) {
		case KeyEvent.KEYCODE_MENU:
			if (menuGV.isShown()) {
				menuGV.setVisibility(View.GONE);
			} else {
				menuGV.setVisibility(View.VISIBLE);
			}
			break;
		default:
			break;
		}

		return super.onKeyDown(keyCode, event);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {

		return true;
	}
}