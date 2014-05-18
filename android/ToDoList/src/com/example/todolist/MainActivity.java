package com.example.todolist;

import java.util.ArrayList;

import android.os.Bundle;
import android.app.Activity;
import android.app.Fragment;
import android.app.FragmentManager;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ListView;

public class MainActivity extends Activity implements
		NewItemFragment.OnNewItemAddedListener {

	private ToDoItemAdapter aa;
	private ArrayList<ToDoItem> todoItems;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		FragmentManager fm = getFragmentManager();
		ToDoListFragment todoListFragment = (ToDoListFragment) fm
				.findFragmentById(R.id.ToDoListFragment);

		todoItems = new ArrayList<ToDoItem>();
		
		int resID = R.layout.todolist_item;
		aa = new ToDoItemAdapter(this,
				resID, todoItems);
		todoListFragment.setListAdapter(aa);
	}

	@Override
	public void onNewItemAdded(String newItem) {
		ToDoItem newToDoItem = new ToDoItem(newItem);
		todoItems.add(0, newToDoItem);
		aa.notifyDataSetChanged();
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
