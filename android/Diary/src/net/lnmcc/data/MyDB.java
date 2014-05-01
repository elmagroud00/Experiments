package net.lnmcc.data;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteException;
import android.util.Log;

public class MyDB {

	private SQLiteDatabase db;
	private final Context context;
	private final MyDBHelper dbhelper;
	
	public MyDB(Context c) {
		context = c;
		dbhelper = new MyDBHelper(context, Contants.DATABASE_NAME, null, Contants.DATABASE_VERSION);
	}
	
	public void close() {
		db.close();
	}
	
	public void open() throws SQLiteException {
		try {
			db = dbhelper.getWritableDatabase();
		} catch(SQLiteException e) {
			Log.v("Open database exception caught", e.getMessage());
			db = dbhelper.getReadableDatabase();
		}
	}
	
	public long insertdiary(String title, String content) {
		try {
			ContentValues newTaskValue = new ContentValues();
			newTaskValue.put(Contants.TITLE_NAME, title);
			newTaskValue.put(Contants.CONTENT_NAME, content);
			newTaskValue.put(Contants.DATE_NAME, java.lang.System.currentTimeMillis());
			return db.insert(Contants.TABLE_NAME, null, newTaskValue);
		} catch(SQLiteException e) {
			Log.v("Insert into database exception caught", e.getMessage());
			return -1;
		}
	}
	
	public Cursor getdiaries() {
		Cursor c = db.query(Contants.TABLE_NAME, null, null, null, null, null, null);
		return c;
	}
}
