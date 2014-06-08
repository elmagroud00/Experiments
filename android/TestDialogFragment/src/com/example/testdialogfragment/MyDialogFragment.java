package com.example.testdialogfragment;

import android.app.AlertDialog;
import android.app.Dialog;
import android.app.DialogFragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

public class MyDialogFragment extends DialogFragment {
	private static String CURRENT_TIME = "CURRENT_TIME";
	
	public static MyDialogFragment newInstance(String currentTime) {
		MyDialogFragment fragment = new MyDialogFragment();
		Bundle args = new Bundle();
		args.putString(CURRENT_TIME, currentTime);
		fragment.setArguments(args);
		return fragment;
	}
	
/*	@Override
	public Dialog onCreateDialog(Bundle savedInstanceState) {
		AlertDialog.Builder timeDialog = new AlertDialog.Builder(getActivity());
		timeDialog.setTitle("The Current Time is ...");
		timeDialog.setMessage(getArguments().getString(CURRENT_TIME));
		
		return timeDialog.create();
	}*/
	
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {
		View view = inflater.inflate(R.layout.dialog_view, container); 
		TextView text = (TextView)view.findViewById(R.id.dialog_text_view);
		text.setText(getArguments().getString(CURRENT_TIME));
		
		return view;
	}
}
