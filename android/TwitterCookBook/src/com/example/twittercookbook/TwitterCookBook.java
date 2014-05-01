package com.example.twittercookbook;

import twitter4j.Twitter;
import twitter4j.TwitterFactory;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class TwitterCookBook extends Activity {

	SharedPreferences myprefs;
	EditText userET, passwordET;
	Button loginBT;
	static Twitter twitter;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		myprefs = PreferenceManager.getDefaultSharedPreferences(this);
		final String username = myprefs.getString("username", null);
		final String password = myprefs.getString("password", null);
		setContentView(R.layout.login);
		userET = (EditText) findViewById(R.id.userText);
		passwordET = (EditText) findViewById(R.id.passwordText);
		loginBT = (Button) findViewById(R.id.loginButton);
		userET.setText(username);
		passwordET.setText(password);
		loginBT.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View arg0) {
				try {
					//AccessToken at = new AccessToken(userET.getText()
					//		.toString(), passwordET.getText().toString());
					twitter = new TwitterFactory().getInstance(userET.getText().toString(), passwordET.getText().toString());
					twitter.getFollowersIDs(-1);
					Intent i = new Intent(TwitterCookBook.this, UpdateAndList.class);
					startActivity(i);
					Editor ed = myprefs.edit();
					ed.putString("username", userET.getText().toString());
					ed.putString("password", passwordET.getText().toString());
					ed.commit();
					finish();
					
				} catch (Exception e) {
					e.printStackTrace();
					Toast.makeText(TwitterCookBook.this, "login failed!", Toast.LENGTH_SHORT).show();
				}
			}
		});

	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.twitter_cook_book, menu);
		return true;
	}

}
