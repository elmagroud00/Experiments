package com.example.sijiewang.testviewpager;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.view.ViewPager;
import java.util.ArrayList;

public class MainActivity extends FragmentActivity {
    private ViewPager mAlarmCreateViewPager;
    private Fragment mFragmentOne;
    private Fragment mFragmentTwo;
    private ArrayList<Fragment> mFragmentList;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mFragmentList = new ArrayList<Fragment>(2);
        mFragmentOne = new mFragmentOne();
        mFragmentList.add(mFragmentOne);
        mFragmentTwo = new mFragmentTwo();
        mFragmentList.add(mFragmentTwo);

        mAlarmCreateViewPager = (ViewPager) findViewById(R.id.viewpager);
        mAlarmCreateViewPager.setAdapter(new PagerAdapterDemo(getSupportFragmentManager()));
    }

    class PagerAdapterDemo extends FragmentPagerAdapter {

        public PagerAdapterDemo(FragmentManager fm) {
            super(fm);
        }

        @Override
        public Fragment getItem(int arg0) {
            return mFragmentList.get(arg0);
        }

        @Override
        public int getCount() {
            return mFragmentList.size();
        }

    }
}
