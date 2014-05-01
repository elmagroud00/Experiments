package com.example.datastorage;

import android.os.Bundle;
import android.preference.PreferenceManager;
import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.view.Menu;
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
		setContentView(R.layout.activity_data_storage);
		myprefs = PreferenceManager.getDefaultSharedPreferences(this);
		final String username = myprefs.getString("username", null);
		final String password = myprefs.getString("password", null);
		if(username != null && password != null) {
			setContentView(R.layout.main);
			userET = (EditText)findViewById(R.id.userText);
			passwordET = (EditText)findViewById(R.id.passwordText);
			loginBT = (Button)findViewById(R.id.loginButton);
			loginBT.setOnClickListener(new View.OnClickListener() {
				
				@Override
				public void onClick(View arg0) {
					try {
						if(username.equals(userET.getText().toString())
								&& password.equals(passwordET.getText().toString())) {
							Toast.makeText(DataStorage.this, "login passed!", Toast.LENGTH_SHORT).show();
							Intent i = new Intent(DataStorage.this, MyPreferences.class);
							startActivity(i);
						} else {
							Toast.makeText(DataStorage.this, "login failed!", Toast.LENGTH_SHORT).show();
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

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.data_storage, menu);
		return true;
	}

}
