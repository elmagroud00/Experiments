package net.lnmcc.data;

import android.content.ContentProvider;
import android.content.ContentValues;
import android.content.UriMatcher;
import android.database.Cursor;
import android.net.Uri;

public class DiaryContentProvider extends ContentProvider {

	private MyDB dba;
	private static final UriMatcher sUriMatcher ;
	// the code returned for URI match to components
	private static final int DIARIES = 1;
	public static final String AUTHORITY = "net.lnmcc.data";
	
	static {
		sUriMatcher = new UriMatcher(UriMatcher.NO_MATCH);
		sUriMatcher.addURI(AUTHORITY, Contants.TABLE_NAME, DIARIES);
	}
	
	@Override
	public int delete(Uri arg0, String arg1, String[] arg2) {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public String getType(Uri arg0) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public Uri insert(Uri arg0, ContentValues arg1) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public boolean onCreate() {
		dba = new MyDB(this.getContext());
		dba.open();
		return false;
	}

	@Override
	public Cursor query(Uri arg0, String[] arg1, String arg2, String[] arg3,
			String arg4) {
		Cursor c = null;
		switch(sUriMatcher.match(arg0)) {
		case DIARIES:
			c = dba.getdiaries();
			break;
		default:
			throw new IllegalArgumentException("Unkonown URI" + arg0);
		}
		c.setNotificationUri(getContext().getContentResolver(), arg0);
		return c;
	}

	@Override
	public int update(Uri arg0, ContentValues arg1, String arg2, String[] arg3) {
		// TODO Auto-generated method stub
		return 0;
	}

}
