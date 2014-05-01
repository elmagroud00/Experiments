package net.lnmcc.diary;

import com.example.diary.R;

import net.lnmcc.data.MyDB;
import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;


public class Diary extends Activity {

	EditText titleET, contentET;
	Button submitBT;
	MyDB dba;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.diary);
		dba = new MyDB(this);
		dba.open();
		titleET = (EditText)findViewById(R.id.diarydescriptionText);
		contentET = (EditText)findViewById(R.id.diarycontentText);
		submitBT = (Button)findViewById(R.id.submitButton);
		submitBT.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				try {
					saveItToDB();
				} catch(Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	public void saveItToDB() {
		dba.insertdiary(titleET.getText().toString(), contentET.getText().toString());
		dba.close();
		titleET.setText("");
		contentET.setText("");
		Intent i = new Intent(Diary.this, DisplayDiaries.class);
		startActivity(i);
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
