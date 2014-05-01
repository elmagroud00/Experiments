package com.example.envents;

import static android.provider.BaseColumns._ID;
import static com.example.envents.Constants.TABLE_NAME;
import static com.example.envents.Constants.TIME;
import static com.example.envents.Constants.TITLE;

import android.app.ListActivity;
import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.content.ContentValues;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.widget.SimpleCursorAdapter;
import android.widget.TextView;

public class MainActivity extends ListActivity {
    private EventsData events;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        events = new EventsData(this);
        try {
            addEvent("Hello, Android!");
            Cursor cursor = getEvents();
            showEvents(cursor);
        } finally {
             events.close();
        }
    }

    private void addEvent(String string) {
        SQLiteDatabase db = events.getWritableDatabase();
        ContentValues values = new ContentValues();
        values.put(TIME, System.currentTimeMillis());
        values.put(TITLE, string);
        db.insertOrThrow(TABLE_NAME, null, values);
    }

    private static String[] FROM = {_ID, TIME, TITLE};
    private static String ORDER_BY = TIME + " DESC";
    private Cursor getEvents() {
        SQLiteDatabase db = events.getReadableDatabase();
        Cursor cursor = db.query(TABLE_NAME, FROM, null, null, null, null, ORDER_BY);
        startManagingCursor(cursor);
        return cursor;
    }

    private static int[] TO = {R.id.rowid, R.id.time, R.id.title};
    private void showEvents(Cursor cursor) {
        SimpleCursorAdapter adapter = new SimpleCursorAdapter(this, R.layout.item, cursor, FROM, TO);
        setListAdapter(adapter);
        /*StringBuilder builder = new StringBuilder("Saved events:\n");

        while(cursor.moveToNext()) {
            long id = cursor.getLong(0);
            long time = cursor.getLong(1);
            String title = cursor.getString(2);
            builder.append(id).append(": ");
            builder.append(time).append(": ");
            builder.append(title).append("\n");
        }
        TextView text = (TextView) findViewById(R.id.text);
        text.setText(builder);
        */
    }
}
