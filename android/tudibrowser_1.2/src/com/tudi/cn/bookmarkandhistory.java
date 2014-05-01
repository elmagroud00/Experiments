package com.tudi.cn;

import java.security.PublicKey;
import java.util.ArrayList;
import java.util.HashMap;

import org.apache.http.client.entity.UrlEncodedFormEntity;

import android.R.integer;
import android.app.Activity;
import android.app.AlertDialog.Builder;
import android.content.ContentValues;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.DialogInterface.OnClickListener;
import android.content.DialogInterface.OnMultiChoiceClickListener;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.net.Uri;
import android.os.Bundle;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.view.animation.Animation;
import android.view.animation.TranslateAnimation;
import android.webkit.URLUtil;
import android.webkit.WebView;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.GridView;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.SimpleAdapter;
import android.widget.SimpleCursorAdapter;
import android.widget.Toast;
import android.widget.AdapterView.OnItemClickListener;

public class bookmarkandhistory extends Activity{

	private GridView  myGridView;
	
	//����2����ͼ�Ĳ���
	private  RelativeLayout myRelativeLayout01;
	private  RelativeLayout myRelativeLayout02;
	
	//���ݿ�
	private  MySQLiteHelper  mySQLiteHelper;
	private  SQLiteDatabase  db;
	
	//�б�1
	private  ListView        myListView01;
	private  Cursor          bookmarkcursor;
	
	
	//�б�2
	private  ListView        myListView02;
	private  Cursor          cursor;
	
	
	//��ť
	private  Button          btn01;
	private  Button          btn02;
	private  Button          btn03;
	private  Button          btn04;
	
	//�����ǩ�Ի����2���༭��
	private  EditText       et01;
	private  EditText       et02;
	//�����ǩ�༭���2���༭��
	private  EditText       et03;
	private  EditText       et04;
	public void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		
		//�ޱ������״̬��
		this.requestWindowFeature(Window.FEATURE_NO_TITLE);
		this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
	
		
		setContentView(R.layout.bookmarkandhistory);
	
		//�������ݿ��ʵ��
		mySQLiteHelper=new MySQLiteHelper(bookmarkandhistory.this, "mydb.db", null, 1);
		db=mySQLiteHelper.getReadableDatabase();
		
		
		
	//��������2����ͼ�Ĳ��ֵ�ʵ��
		myRelativeLayout01=(RelativeLayout) findViewById(R.id.Cent01);
		myRelativeLayout02=(RelativeLayout) findViewById(R.id.Cent02);
		
	//�����б��ʵ��
		myListView01=(ListView) findViewById(R.id.ListView01);
		myListView02=(ListView) findViewById(R.id.ListView02);
		
	
	//������ť��ʵ��
		//��Ӱ�ť
		btn01=(Button) findViewById(R.id.Button01);
		//���ذ�ť
		btn02=(Button) findViewById(R.id.Button02);
		//����ť
		btn03=(Button) findViewById(R.id.Button03);
		//���ذ�ť
		btn04=(Button) findViewById(R.id.Button04);
	
	
		
		
	//��ǩ�з��ذ�ť�ĵ���¼�	
		btn02.setOnClickListener(new Button.OnClickListener(){

			public void onClick(View arg0) {
				Intent intent=new Intent();
				intent.setClass(bookmarkandhistory.this, main.class);
				startActivity(intent);
				bookmarkandhistory.this.finish();//�ͷ��ڴ�
				db.close();//�ر����ݿ�
			}
			
		});
		
	//��ʷ��¼�з��ذ�ť�ĵ���¼�
		btn04.setOnClickListener(new Button.OnClickListener(){

			public void onClick(View v) {
				Intent intent=new Intent();
				intent.setClass(bookmarkandhistory.this, main.class);
				startActivity(intent);
				bookmarkandhistory.this.finish();//�ͷ��ڴ�
			//�ر����ݿ�
				db.close();
			
			}});
		//����GridView
	loadGridView();
	}
	
	public void loadGridView(){
	myGridView=(GridView) findViewById(R.id.GridView01);
	myGridView.setNumColumns(2);
	myGridView.setGravity(Gravity.CENTER);
	myGridView.setVerticalSpacing(10);
	myGridView.setHorizontalSpacing(10);
	
	ArrayList arrayList=new ArrayList();
	
	HashMap hashMap=new HashMap();
	hashMap.put("itemword", "��ǩ");
	arrayList.add(hashMap);
	
	hashMap=new HashMap();
	hashMap.put("itemword", "��ʷ");
	arrayList.add(hashMap);
	
	SimpleAdapter simpleAdapter=new SimpleAdapter(bookmarkandhistory.this, arrayList, R.layout.gridviewitem, new String[]{"itemword"}, new int[]{R.id.TextView01});
	myGridView.setAdapter(simpleAdapter);
	//----------begin:myGridView�ĵ���¼�----------------------------------------------------------
	myGridView.setOnItemClickListener(new OnItemClickListener(){

		public void onItemClick(AdapterView<?> arg0, View arg1, int which,
				long arg3) {
		switch(which){
		case 0:
			if(myRelativeLayout01.getVisibility()==View.GONE){
			//�Ƚ���һ�����ݵĲ�ѯ
			bookmarkcursor=db.query("bookmarktable", new String[]{"_id","title","url"}, null, null, null, null, null);	
			SimpleCursorAdapter sca=new SimpleCursorAdapter(bookmarkandhistory.this, R.layout.listview01item, bookmarkcursor, new String[]{"title","url"}, new int[]{R.id.TextView01,R.id.TextView02});	
			myListView01.setAdapter(sca);	
				//����һ������
			int width=myRelativeLayout02.getWidth();
				
			Animation myTranslateAnimation=new TranslateAnimation(0,-width,0,0);
			myTranslateAnimation.setDuration(1000);
			myRelativeLayout02.setAnimation(myTranslateAnimation);
			
			myRelativeLayout01.setVisibility(View.VISIBLE);
			myRelativeLayout02.setVisibility(View.GONE);
			//----begin:myListView01�б���ͼ�ĵ���¼�-------------------------------------------------
			myListView01.setOnItemClickListener(new OnItemClickListener(){

				public void onItemClick(AdapterView<?> arg0, View arg1,
						int arg2, long arg3) {
					//�����Ի���
					Builder builder=new Builder(bookmarkandhistory.this);
					builder.setIcon(R.drawable.siyecao30);
					builder.setTitle("��ǩ����");
					builder.setSingleChoiceItems(new String[]{"��","�༭","ɾ��"}, -1, new OnClickListener(){

						public void onClick(DialogInterface dialog, int which) {
							if(which==0){
							//����վ
							int urlindex=bookmarkcursor.getColumnIndex("url");
							String markurl=bookmarkcursor.getString(urlindex);
							//����һ����ַǰ�Ƿ������http��//
							String strindex=markurl.substring(0,7);
							 boolean bln=strindex.equalsIgnoreCase("http://");
							if(bln==false){
							markurl="http://"+markurl;	
							}
							 if(URLUtil.isNetworkUrl(markurl)){
								Uri url=Uri.parse(markurl);
								Intent intent=new Intent(Intent.ACTION_VIEW,url);
								startActivity(intent);
								
							    }else{Toast.makeText(bookmarkandhistory.this, "��ַ����", Toast.LENGTH_LONG).show();}
							
							}else if(which==1){
							//�༭
								Builder editBuilder=new Builder(bookmarkandhistory.this);
								editBuilder.setIcon(R.drawable.siyecao30);
								editBuilder.setTitle("��ǩ�༭");
								LayoutInflater inflater=LayoutInflater.from(bookmarkandhistory.this);
								View view=inflater.inflate(R.layout.bookmarkedit,null);
								et03=(EditText) view.findViewById(R.id.EditText03);
								et04=(EditText) view.findViewById(R.id.EditText04);
								editBuilder.setView(view);
								editBuilder.setPositiveButton("ȷ��", new OnClickListener(){

									public void onClick(DialogInterface dialog,
											int which) {
									int idindex=bookmarkcursor.getColumnIndex("_id");
									int myid=bookmarkcursor.getInt(idindex);	
									String mytitle=et03.getText().toString();
									String myurl=et04.getText().toString();
									
									ContentValues cv=new ContentValues();
									cv.put("title", mytitle);
									cv.put("url", myurl);
									db.update("bookmarktable", cv, "_id"+"="+myid, null);
									//�ٽ���һ�����ݿ�Ĳ�ѯ
									
									bookmarkcursor=db.query("bookmarktable", new String[]{"_id","title","url"}, null, null, null, null, null);	
									SimpleCursorAdapter sca=new SimpleCursorAdapter(bookmarkandhistory.this, R.layout.listview01item, bookmarkcursor, new String[]{"title","url"}, new int[]{R.id.TextView01,R.id.TextView02});	
									myListView01.setAdapter(sca);	
									}});
								editBuilder.setNegativeButton("ȡ��", new OnClickListener(){

									public void onClick(DialogInterface dialog,
											int which) {
										
										
										
									}
									
								});
								
								editBuilder.show();
								
								
								
								//
							}else if(which==2){
							//ɾ��
								Builder deleteBuilder=new Builder(bookmarkandhistory.this);
								deleteBuilder.setIcon(R.drawable.siyecao30);
								deleteBuilder.setTitle("��ǩɾ��");	
								deleteBuilder.setMultiChoiceItems(new String[]{"ɾ����ǩ"}, new boolean[]{false}, new OnMultiChoiceClickListener(){

									public void onClick(DialogInterface dialog,
											int which, boolean isChecked) {
									if(which==0){
									if(isChecked==true){
									
										int idindex=bookmarkcursor.getColumnIndex("_id");
										int myid=bookmarkcursor.getInt(idindex);
										db.delete("bookmarktable", "_id"+"="+myid, null);
										//�ٽ���һ�����ݿ�Ĳ�ѯ
										bookmarkcursor=db.query("bookmarktable", new String[]{"_id","title","url"}, null, null, null, null, null);	
										SimpleCursorAdapter sca=new SimpleCursorAdapter(bookmarkandhistory.this, R.layout.listview01item, bookmarkcursor, new String[]{"title","url"}, new int[]{R.id.TextView01,R.id.TextView02});	
										myListView01.setAdapter(sca);
										
									}
									}
										
									}
									
								});
								deleteBuilder.setPositiveButton("����", new OnClickListener(){

									public void onClick(DialogInterface dialog,
											int which) {
										
										
									}
									
								});
								
								deleteBuilder.show();
							}
							
						}});
					
					builder.show();
				}
				
			});
			
			//----end:myListView01�б���ͼ�ĵ���¼�--------------------------------------------------
			}
			break;
		case 1:
			if(myRelativeLayout02.getVisibility()==View.GONE){
			
			//�Ƚ������ݵĲ�ѯ	
			cursor=db.query("history", new String[]{"_id","title","url"}, null, null, null, null, null);	
			SimpleCursorAdapter sca=new SimpleCursorAdapter(bookmarkandhistory.this, R.layout.listview02item, cursor, new String[]{"url"}, new int[]{R.id.TextView01});	
			myListView02.setAdapter(sca);	
				
			//����һ������
				int width=myRelativeLayout01.getWidth();
				
				Animation myTranslateAnimation=new TranslateAnimation(0,width,0,0);
				myTranslateAnimation.setDuration(1000);
				myRelativeLayout01.setAnimation(myTranslateAnimation);
				
			myRelativeLayout02.setVisibility(View.VISIBLE);	
			myRelativeLayout01.setVisibility(View.GONE);
			
			//myListView02�б���ͼ�ĵ���¼�
			myListView02.setOnItemClickListener(new OnItemClickListener(){

				public void onItemClick(AdapterView<?> arg0, View arg1,
						int which, long arg3) {
				
					
				Builder builder=new Builder(bookmarkandhistory.this);
				builder.setIcon(R.drawable.siyecao30);
				builder.setTitle("��ʷ��¼");
				builder.setSingleChoiceItems(new String[]{"��","ɾ��"}, -1, new OnClickListener(){

					public void onClick(DialogInterface dialog, int which) {
					if(which==0){
					
					int   urlindex=cursor.getColumnIndex("url");
					String myurl=cursor.getString(urlindex);
					
					//���д���ҳ�Ĳ���
					if(URLUtil.isNetworkUrl(myurl)){
					
						Uri url=Uri.parse(myurl);
						Intent intent=new Intent(Intent.ACTION_VIEW,url);
						startActivity(intent);
					}else{Toast.makeText(bookmarkandhistory.this, "��ַ����", Toast.LENGTH_LONG).show();}
					
					}else if(which==1){
					//ɾ����ַ�Ĳ���
					int idindex=cursor.getColumnIndex("_id");	
					int myid=cursor.getInt(idindex);	
					
					db.delete("history", "_id"+"="+myid, null);
					//�ٴν������ݵĲ�ѯ
					cursor=db.query("history", new String[]{"_id","title","url"}, null, null, null, null, null);	
					SimpleCursorAdapter sca=new SimpleCursorAdapter(bookmarkandhistory.this, R.layout.listview02item, cursor, new String[]{"url"}, new int[]{R.id.TextView01});	
					myListView02.setAdapter(sca);	
					}
						
					}});
				builder.show();
				
				}
				
			});
			
			}
			break;
		
		
		}
			
		}
		
	});
	//---------end:myGridView�ĵ���¼�-----------------------------------------------------------
	//��ǩ����Ӱ�ť�ĵ���¼�
	btn01.setOnClickListener(new Button.OnClickListener(){

		public void onClick(View v) {
			Builder myBuilder=new Builder(bookmarkandhistory.this);
			myBuilder.setIcon(R.drawable.siyecao30);
			myBuilder.setTitle("�����ǩ");
			//������ͼ
			LayoutInflater inflater=LayoutInflater.from(bookmarkandhistory.this);
			View           view=inflater.inflate(R.layout.bookmarkadd, null);
			//������ͼ��ʵ��
			et01=(EditText) view.findViewById(R.id.Title01);
			et02=(EditText) view.findViewById(R.id.Url01);
			myBuilder.setView(view);
			//ȷ����ť
			myBuilder.setPositiveButton("ȷ��", new OnClickListener(){

				public void onClick(DialogInterface dialog, int which) {
				String mytitle=et01.getText().toString();	
				String myurl=et02.getText().toString();
				ContentValues cv=new ContentValues();
				cv.put("title", mytitle);
				cv.put("url", myurl);
				db.insert("bookmarktable", null, cv);
				
				//��ѯһ�����ݿ�
				//�Ƚ���һ�����ݵĲ�ѯ
				bookmarkcursor=db.query("bookmarktable", new String[]{"_id","title","url"}, null, null, null, null, null);	
				SimpleCursorAdapter sca=new SimpleCursorAdapter(bookmarkandhistory.this, R.layout.listview01item, bookmarkcursor, new String[]{"title","url"}, new int[]{R.id.TextView01,R.id.TextView02});	
				myListView01.setAdapter(sca);	
				
				}
				
			});
			//ȡ����ť
			myBuilder.setNegativeButton("ȡ��", new OnClickListener(){

				public void onClick(DialogInterface dialog, int which) {
					
					
				}
				
			});
			myBuilder.show();
		}
		
	});
	
	
	
	//����ť�ĵ���¼�	
	btn03.setOnClickListener(new Button.OnClickListener(){

		public void onClick(View v) {
			
			Builder myBuilder=new Builder(bookmarkandhistory.this);
			myBuilder.setIcon(R.drawable.siyecao30);
			myBuilder.setTitle("��ʷ��¼����");
			myBuilder.setMessage("�Ƿ�ȫ��ɾ����");
			myBuilder.setPositiveButton("ȷ��", new OnClickListener(){

				public void onClick(DialogInterface dialog, int which) {
					cursor=db.query("history", new String[]{"_id","title","url"}, null, null, null, null, null);
					while(cursor.moveToNext()){
					
						int idindex=cursor.getColumnIndex("_id");
						int myid=cursor.getInt(idindex);
						db.delete("history", "_id"+"="+myid, null);
					}	
					//��ʾ��
					Toast.makeText(bookmarkandhistory.this, "��ʷ��¼��ȫ��ɾ����", Toast.LENGTH_LONG).show();
					//���²�ѯһ��
					cursor=db.query("history", new String[]{"_id","title","url"}, null, null, null, null, null);
					SimpleCursorAdapter sca=new SimpleCursorAdapter(bookmarkandhistory.this, R.layout.listview02item, cursor, new String[]{"url"}, new int[]{R.id.TextView01});	
					myListView02.setAdapter(sca);
				}
				
			});
			myBuilder.setNegativeButton("ȡ��", new OnClickListener(){

				public void onClick(DialogInterface dialog, int which) {
					
					
				}
				
			});
			myBuilder.show();
		}
		
	});
	//
	}
	
	//���ð����ĵ���¼�
	public boolean onKeyDown(int keyCode,KeyEvent event){
		
		switch(keyCode){
		case  KeyEvent.KEYCODE_BACK:
			Intent intent=new Intent();
			intent.setClass(bookmarkandhistory.this, main.class);
			startActivity(intent);
			bookmarkandhistory.this.finish();
			db.close();
		}
		
		return     super.onKeyDown(keyCode, event);
	}
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
