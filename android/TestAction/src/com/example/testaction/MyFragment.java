package com.example.testaction;

import android.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

public class MyFragment extends Fragment {

	private CharSequence fragmentTextString = "";
	private TextView fragmentText;
	
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {
		
		View v = inflater.inflate(R.layout.my_fragment, container, false);
		fragmentText = (TextView)v.findViewById(R.id.tv);		
		fragmentText.setText(fragmentTextString);

		return v;
	}

	public void setFragmentText(CharSequence _text) {
		fragmentTextString = _text;
		if(fragmentText != null) {
			fragmentText.setText(fragmentTextString);
		}
	}
}
