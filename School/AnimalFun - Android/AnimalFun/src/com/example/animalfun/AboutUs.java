package com.example.animalfun;

import android.app.ActionBar;
import android.app.Activity;
import android.os.Bundle;

public class AboutUs extends Activity{

	public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
//        ActionBar actionBar = getActionBar();
//        actionBar.setTitle("About Us");
//        actionBar.hide();				//uncomment to hide action bar on top!!
        
        setContentView(R.layout.about_us);
	}
}
