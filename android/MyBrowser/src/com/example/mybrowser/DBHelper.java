package com.example.mybrowser;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteDatabase.CursorFactory;
import android.database.sqlite.SQLiteOpenHelper;

public class DBHelper extends SQLiteOpenHelper {
	public static final String DATABASE_NAME = "BrowserDB.db";
	public static final String TABLE_BOOKMARK = "BookMarkTable";
	public static final String TABLE_HISTORY = "HistoryTable";
	public static final int DATABASE_VERSION = 1;

	public static final String KEY_ID = "_id";
	public static final String WEB_URL_COLUM = "webUrl";
	public static final String WEB_TITLE_COLUM = "webTitle";

	private static final String BOOKMARK_TABLE_CREATE = "create table "
			+ TABLE_BOOKMARK + " (" + KEY_ID
			+ " integer primary key autoincrement, " + WEB_TITLE_COLUM
			+ " text, " + WEB_URL_COLUM + " text not null " + " );";

	private static final String HISTORY_TABLE_CREATE = "create table "
			+ TABLE_HISTORY + " (" + KEY_ID
			+ " integer primary key autoincrement, " + WEB_TITLE_COLUM
			+ " text, " + WEB_URL_COLUM + " text not null " + " );";

	public DBHelper(Context context, String name, CursorFactory factory,
			int version) {
		super(context, name, factory, version);
	}

	@Override
	public void onCreate(SQLiteDatabase db) {
		db.execSQL(BOOKMARK_TABLE_CREATE);
		db.execSQL(HISTORY_TABLE_CREATE);
	}

	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {

	}
}
