package net.lnmcc.sqlitetest;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.database.sqlite.SQLiteQueryBuilder;
import android.provider.BaseColumns;
import android.text.TextUtils;
import android.util.Log;

public class BooksDB {
	
	public interface DataColumns extends BaseColumns {
		public static final String DISPLAY_NAME = "_display_name";
		public static final String TITLE = "title";
		public static final String _ID = "_id";
		public static final String ISBN = "isbn";
	}
	
	private SQLiteDatabase booksDB;
	private static final String DATABASE_TABLE = "titles";
	
	private static class DatabaseHelper extends SQLiteOpenHelper {
		private static final String DATABASE_NAME = "Books";
		private static final int DATABASE_VERSION = 2;
		private static final String DATABASE_CREATE = "create table " 
				+ DATABASE_TABLE + " ("
				+ DataColumns._ID + "  integer primary key autoincrement, "
				+ DataColumns._COUNT + "  integer, "
				+ DataColumns.DISPLAY_NAME + "  text,"
				+ DataColumns.ISBN + " text not null, "
				+ DataColumns.TITLE + " text not null "
				+ " ); ";
		
		DatabaseHelper(Context context) {
			super(context, DATABASE_NAME, null, DATABASE_VERSION);
		}
		
		@Override
		public void onCreate(SQLiteDatabase db) {
			db.execSQL(DATABASE_CREATE);
		}
		
		@Override
		public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
			Log.w("Content provider database",
					"Upgrading database from version" + oldVersion + "to "
					+ newVersion + ",which will destroy all old data");
			db.execSQL("DROP TABLE IF EXIST titles");
			onCreate(db);
		}
	}
	
	public int delete(long id, String selection, String[] selectionArgs) {
		int count = 0;
		count = booksDB.delete(DATABASE_TABLE, DataColumns._ID 
				+ " = "
				+ id 
				+ ( !TextUtils.isEmpty(selection) ? " AND (" + selection + ')' : ""), 
				selectionArgs);
		return count;
	}
	
	public long insert(ContentValues values) {
		long rowID = booksDB.insert(DATABASE_TABLE, "", values);
		if(rowID > 0) {
			return rowID;
		}
		throw new SQLException("Failed to insert row");
	}
	
 	public BooksDB(Context context) {
 		DatabaseHelper dbHelper = new DatabaseHelper(context);
 		booksDB = dbHelper.getWritableDatabase();
	}
 	
 	public Cursor query(String[] projection, String selection, String[] selectionArgs, String sortOrder) {
 		SQLiteQueryBuilder sqlBuilder = new SQLiteQueryBuilder();
 		sqlBuilder.setTables(DATABASE_TABLE);
 		
 		if(sortOrder == null || sortOrder == "")
 			sortOrder = DataColumns.TITLE;
 		
 		Cursor c = sqlBuilder.query(booksDB, projection, selection, selectionArgs, null, null, sortOrder);
 		
 		return c;
 	}
 	
 	public int update(long id, ContentValues values, String selection, String[] selectionArgs) {
 	
 		int count = 0;
 		
 		count = booksDB.update(DATABASE_TABLE, values, DataColumns._ID 
 				+ "=" 
 				+ id
 				+ (!TextUtils.isEmpty(selection) ? " AND (" + selection + ')' : ""), selectionArgs);
 		
 		return count;
 	}
}












