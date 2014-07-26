package net.lnmcc.testprocess1;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends Activity {

	Button btn;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		btn = (Button) findViewById(R.id.btn);
		btn.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				ComponentName cn = new ComponentName("net.lnmcc.testprocess2",
						"net.lnmcc.testprocess2.MainActivity");
				Intent intent = new Intent();
				intent.setComponent(cn);
				startActivity(intent);
			}
		});

	}
}
