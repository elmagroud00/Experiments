package com.tudi.cn;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.database.sqlite.SQLiteDatabase.CursorFactory;

public class MySQLiteHelper extends SQLiteOpenHelper{

	public MySQLiteHelper(Context context, String name, CursorFactory factory,
			int version) {
		super(context, name, factory, version);
		
	}

	@Override
	public void onCreate(SQLiteDatabase db) {
		//������ǩ�����ݿ��
		db.execSQL("create table bookmarktable(_id integer primary key autoincrement,title text,url text)");
		//������ʷ�����ݿ��
		db.execSQL("create table history( _id integer primary key autoincrement,title text,url text);");	
		
	}

	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
		
	}

}
