package net.lnmcc.sqlitetest;

import net.lnmcc.sqlitetest.BooksDB.DataColumns;
import android.app.Activity;
import android.content.ContentValues;
import android.database.Cursor;
import android.os.Bundle;
import android.widget.Toast;

public class MainActivity extends Activity{
	private BooksDB mBooksDB;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		mBooksDB = new BooksDB(this);
		
		ContentValues values = new ContentValues();
		values.put(DataColumns.TITLE, "C#2008 Programmers Reference");
		values.put(DataColumns.ISBN, "000112233");
		
		long id = mBooksDB.insert(values);
		mBooksDB.delete(id, null, null);
		
		values = new ContentValues();
		values.put(DataColumns.TITLE, "android hacks");
		values.put(DataColumns.ISBN, "22332323");
		
		id = mBooksDB.insert(values);
		
		values = new ContentValues();
		values.put(DataColumns.TITLE, "droid hacks");
		values.put(DataColumns.ISBN, "999999");
		mBooksDB.update(id, values, null, null);
		
		Cursor c = mBooksDB.query(null, null, null, "title desc");
		if(c.moveToFirst()) {
			do {
				Toast.makeText(this,
						c.getString(c.getColumnIndex(DataColumns._ID))
						+ ", "
						+ c.getString(c.
								getColumnIndex(DataColumns.TITLE))
						+ ", "
						+ c.getString(c
								.getColumnIndex(DataColumns.ISBN)),
						Toast.LENGTH_LONG).show();
			} while(c.moveToNext());
		}
	}
}










