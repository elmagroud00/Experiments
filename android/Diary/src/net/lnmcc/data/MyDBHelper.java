package net.lnmcc.data;

import android.content.Context;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.database.sqlite.SQLiteDatabase.CursorFactory;
import android.util.Log;
import android.widget.Toast;

public class MyDBHelper extends SQLiteOpenHelper { 
	
	private final Context mcontext;
	
	private static final String CREATE_TABLE = "create table " +
												Contants.TABLE_NAME + " ( " +
												Contants.KEY_ID + " integer primary key autoincrement, " +
												Contants.TITLE_NAME + " text not null, " +
												Contants.CONTENT_NAME + " text not null, " +
												Contants.DATE_NAME + " long );";
	
	public MyDBHelper(Context context, String name, CursorFactory factory, int version) {
		super(context, name, factory, version);
		mcontext = context;
	}
												
	@Override
	public void onCreate(SQLiteDatabase db) {
		Log.v("MyDBHelper OnCreate", "Creating all the tables");
		try {
			db.execSQL(CREATE_TABLE);
		} catch(SQLException e) {
			Log.v("Create table exception", e.getMessage());
			Toast.makeText(mcontext, e.getMessage(), Toast.LENGTH_SHORT).show();
		}
	}
	
	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
		Log.w("TaskDBAdapter", "Upgrading from version " + oldVersion + " to " + newVersion + " , which will destroy all old data");
		db.execSQL("drop table if exist " + Contants.TABLE_NAME);
		onCreate(db);
	}
}
