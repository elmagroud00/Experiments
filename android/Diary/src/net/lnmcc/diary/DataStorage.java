package net.lnmcc.diary;

import com.example.diary.R;

import net.lnmcc.data.MyDB;
import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class DataStorage extends Activity {
	
	SharedPreferences myprefs;
	EditText userET, passwordET;
	Button loginBT;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		myprefs = PreferenceManager.getDefaultSharedPreferences(this);
		final String username = myprefs.getString("username", null);
		final String password = myprefs.getString("password", null);
		if(username != null && password != null) {
			setContentView(R.layout.login);
			userET = (EditText)findViewById(R.id.userText);
			passwordET = (EditText)findViewById(R.id.passwordText);
			loginBT = (Button)findViewById(R.id.loginButton);
			loginBT.setOnClickListener(new View.OnClickListener() {
				
				@Override
				public void onClick(View arg0) {
					try {
						if(username.equals(userET.getText().toString()) &&
								password.equals(passwordET.getText().toString())) {
							
							Toast.makeText(DataStorage.this, "login passed!", Toast.LENGTH_SHORT).show();
							Intent i = new Intent(DataStorage.this, Diary.class);
							startActivity(i);
						}
					} catch(Exception e) {
						e.printStackTrace();
					}
				}
			});
		} else {
			Intent i = new Intent(this, MyPreferences.class);
			startActivity(i);
		}
	}
	
}
