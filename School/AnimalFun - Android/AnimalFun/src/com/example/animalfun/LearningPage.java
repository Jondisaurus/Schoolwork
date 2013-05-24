package com.example.animalfun;



import android.app.ActionBar;
import android.app.Activity;
import android.app.FragmentManager;
//import android.content.Intent;
import android.os.Bundle;

import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentStatePagerAdapter;
//import android.util.Log;
//import android.view.View;
//import android.widget.Button;
//import android.widget.TextView;
import android.support.v4.app.FragmentActivity;
import android.support.v4.view.PagerAdapter;
import android.support.v4.view.ViewPager;


public class LearningPage extends FragmentActivity {

	private ViewPager mPager; // Pager widget
	private ScreenSlidePagerAdapter mPagerAdapter;
	private int num_pages = 0; 
	Animals animals; 
	ScreenSlidePageFragment fragment; 
	
	public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
//        ActionBar actionBar = getActionBar();
//        actionBar.setTitle("LearningPage");
//        actionBar.hide();				//uncomment to hide action bar on top!!
        setContentView(R.layout.activity_learning_page);
//        setContentView(R.layout.learning_page_fragment);
        
        animals = new Animals(); 
        
        num_pages = animals.getSize();
        
        mPager = (ViewPager) findViewById(R.id.pager);
        mPagerAdapter = new ScreenSlidePagerAdapter(getSupportFragmentManager());
        mPager.setAdapter(mPagerAdapter);
        int numPages = mPagerAdapter.getCount();
        
        /*mPager.setOnPageChangeListener(new ViewPager.SimpleOnPageChangeListener() {
            @Override
            public void onPageSelected(int position) {
                // When changing pages, reset the action bar actions since they are dependent
                // on which page is currently active. An alternative approach is to have each
                // fragment expose actions itself (rather than the activity exposing actions),
                // but for simplicity, the activity provides the actions in this sample.
                //invalidateOptionsMenu();
            };
        });*/
        
	}
	
	private class ScreenSlidePagerAdapter extends FragmentStatePagerAdapter {
        public ScreenSlidePagerAdapter(android.support.v4.app.FragmentManager fragmentManager) {
            super(fragmentManager);
        }

        @Override
        public Fragment getItem(int position) {
            
        	Fragment thisFrag = ScreenSlidePageFragment.create(position);      	
        	return thisFrag; 
        }

        @Override
        public int getCount() {
            return num_pages;
        }
    }
        
        
}
