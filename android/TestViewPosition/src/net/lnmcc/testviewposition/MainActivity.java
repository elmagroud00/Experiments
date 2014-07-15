package net.lnmcc.testviewposition;

import android.app.Activity;
import android.graphics.Rect;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity {

	TextView testView;
	TextView infoView;
	TextView sizeInfo;

	Button localVisibleRectBtn;
	Button globalVisibleRectBtn;
	Button locationOnScreenBtn;
	Button locationInWindowBtn;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		testView = (TextView) findViewById(R.id.test);
		infoView = (TextView) findViewById(R.id.infomation);
		sizeInfo = (TextView)findViewById(R.id.sizeinfo);

		localVisibleRectBtn = (Button) findViewById(R.id.getLocalVisibleRect);
		localVisibleRectBtn.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				
				StringBuilder sb = new StringBuilder();
				sb.append("TestArea").append("\n");
				sb.append("Width: ").append(testView.getWidth()).append("\n");
				sb.append("Height: ").append(testView.getHeight()).append("\n");
				sizeInfo.setText(sb.toString());
			
				Rect rect = new Rect();
				testView.getLocalVisibleRect(rect);
				sb = new StringBuilder();
				sb.append("localVisibleRect").append("\n");
				sb.append("Top: ").append(rect.top).append("    ");
				sb.append("left: ").append(rect.left).append("\n");
				sb.append("right: ").append(rect.right).append("    ");
				sb.append("bottom: ").append(rect.bottom).append("    ");
				infoView.setText(sb.toString());
			}
		});

		globalVisibleRectBtn = (Button) findViewById(R.id.getGlobalVisibleRect);
		globalVisibleRectBtn.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				
				StringBuilder sb = new StringBuilder();
				sb.append("TestArea").append("\n");
				sb.append("Width: ").append(testView.getWidth()).append("\n");
				sb.append("Height: ").append(testView.getHeight()).append("\n");
				sizeInfo.setText(sb.toString());
				
				Rect rect = new Rect();
				testView.getGlobalVisibleRect(rect);
				sb = new StringBuilder();
				sb.append("globalVisibleRect").append("\n");
				sb.append("Top: ").append(rect.top).append("    ");
				sb.append("left: ").append(rect.left).append("\n");
				sb.append("right: ").append(rect.right).append("    ");
				sb.append("bottom: ").append(rect.bottom).append("    ");
				infoView.setText(sb.toString());
			}
		});

		locationOnScreenBtn = (Button) findViewById(R.id.getLocationOnScreen);
		locationOnScreenBtn.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				
				StringBuilder sb = new StringBuilder();
				sb.append("TestArea").append("\n");
				sb.append("Width: ").append(testView.getWidth()).append("\n");
				sb.append("Height: ").append(testView.getHeight()).append("\n");
				sizeInfo.setText(sb.toString());
				
				int[] location = new int[2];
				testView.getLocationOnScreen(location);
				sb = new StringBuilder();
				sb.append("locationOnScreen").append("\n");
				sb.append("X: ").append(location[0]).append("\n");
				sb.append("Y: ").append(location[1]).append("\n");
				infoView.setText(sb.toString());
			}
		});
		
		locationInWindowBtn = (Button)findViewById(R.id.getLocationInWindow);
		locationInWindowBtn.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				
				StringBuilder sb = new StringBuilder();
				sb.append("TestArea").append("\n");
				sb.append("Width: ").append(testView.getWidth()).append("\n");
				sb.append("Height: ").append(testView.getHeight()).append("\n");
				sizeInfo.setText(sb.toString());
				
				int[] location = new int[2];
				testView.getLocationInWindow(location);
				sb = new StringBuilder();
				sb.append("locationInWindow").append("\n");
				sb.append("X: ").append(location[0]).append("\n");
				sb.append("Y: ").append(location[1]).append("\n");
				infoView.setText(sb.toString());
			}
		});
	}
}
