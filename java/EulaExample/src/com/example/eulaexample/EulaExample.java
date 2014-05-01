package com.example.eulaexample;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.widget.Toast;

public class EulaExample extends Activity implements Eula.OnEulaAgreedTo {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_eula_example);
		Eula.show(this);
	}

	@Override
	public void onEulaAgreedTo() {
		Toast.makeText(this, "Think you !", Toast.LENGTH_SHORT).show();
	}
}
