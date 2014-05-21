package com.example.testaction;

import android.os.Bundle;
import android.app.ActionBar;
import android.app.Fragment;
import android.app.FragmentTransaction;
import android.app.ActionBar.Tab;
import android.app.Activity;
import android.content.Intent;
import android.content.res.Resources;
import android.graphics.drawable.Drawable;
import android.view.Menu;
import android.view.MenuItem;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		// getWindow().requestFeature(Window.FEATURE_ACTION_BAR_OVERLAY);
		setContentView(R.layout.activity_main);

		ActionBar actionBar = getActionBar();
		actionBar.setDisplayShowHomeEnabled(true);
		actionBar.setHomeButtonEnabled(true);
		actionBar.setTitle("Main");
		actionBar.setNavigationMode(ActionBar.NAVIGATION_MODE_TABS);
		actionBar.setDisplayShowTitleEnabled(false);

		Tab tabOne = actionBar.newTab().setText("Tab1");
		TabListener<MyFragment> tabListen = new TabListener<MyFragment>(this,
				R.id.fragment_container, MyFragment.class);
		tabOne.setTabListener(tabListen);

		Tab tabTwo = actionBar.newTab().setText("Tab2");
		TabListener<MyFragment> tabListen2 = new TabListener<MyFragment>(this,
				R.id.fragment_container, MyFragment.class);
		tabTwo.setTabListener(tabListen2);

		actionBar.addTab(tabOne);
		actionBar.addTab(tabTwo);

		Resources r = getResources();
		// Drawable myDrawable = r.getDrawable(R.drawable.ic_launcher);
		// actionBar.setBackgroundDrawable(myDrawable);

		actionBar.show();
	}

	class TabListener<T extends Fragment> implements ActionBar.TabListener {

		private MyFragment fragment = null;
		private Activity activity = null;
		private Class<T> fragmentClass = null;
		private int fragmentContainer;

		public TabListener(Activity _activity, int _fragmentContainer,
				Class<T> _fragmentClass) {
			activity = _activity;
			fragmentContainer = _fragmentContainer;
			fragmentClass = _fragmentClass;
		}

		@Override
		public void onTabReselected(Tab tab, FragmentTransaction ft) {

		}

		@Override
		public void onTabSelected(Tab tab, FragmentTransaction ft) {
			if (fragment == null) {
				String fragmentName = fragmentClass.getName();
				fragment = (MyFragment) Fragment.instantiate(activity,
						fragmentName);
				// add会触发Fragment的onAttach();
				ft.add(fragmentContainer, fragment, null);
				// ft.replace(fragmentContainer, fragment);
				fragment.setFragmentText(tab.getText());
			} else {
				ft.attach(fragment);
			}
		}

		@Override
		public void onTabUnselected(Tab tab, FragmentTransaction ft) {
			if (fragment != null) {
				ft.detach(fragment);
			}
		}
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		switch (item.getItemId()) {
		case (android.R.id.home):
			Intent intent = new Intent(this, ActionBarActivity.class);
			intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
			startActivity(intent);
			return true;
		default:
			return super.onOptionsItemSelected(item);
		}
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
