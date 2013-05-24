package com.example.animalfun;

//import com.example.animalfun.R.id;

import android.os.Bundle;
//import android.app.ActionBar;
//import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ImageButton;

public class MainPage extends Activity {

	private SharedPreferences prefs;
	private int theme1;

	//    @SuppressLint("NewApi")
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		//        ActionBar actionBar = getActionBar();	//load action bar
		//        actionBar.hide();						//hide action bar

		this.prefs = getSharedPreferences("settings", 0);
		theme1 = this.prefs.getInt("Theme", 0);
		Utils.setThemeToActivity(this, theme1);
		//        
		//        if(Utils.changed) {
		//        	this.recreate();
		//        }

		setContentView(R.layout.activity_main_page);

		ImageButton btnLearningPage = (ImageButton) findViewById(R.id.btn_learning);
		ImageButton btnSpellingPage = (ImageButton) findViewById(R.id.btn_spelling);
		ImageButton btnMathPage = (ImageButton) findViewById(R.id.btn_math);

		AndroidTools.PlaySound(this, R.raw.animalfun);

		btnLearningPage.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				//Starting a new Intent for Learning Page
				//                  Intent learningScreenIntent = new Intent(getApplicationContext(), LearningPage.class);
				AndroidTools.PlaySound(getBaseContext(), R.raw.animallearning);
				AndroidTools.wait(1500);
				Intent learningScreenIntent = new Intent(MainPage.this, LearningPage.class);

				//load screen
				MainPage.this.startActivity(learningScreenIntent);
			}
		});

		btnSpellingPage.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				//Starting a new Intent for Learning Page
				//                  Intent learningScreenIntent = new Intent(getApplicationContext(), LearningPage.class);
				AndroidTools.PlaySound(getBaseContext(), R.raw.animalspelling);
				AndroidTools.wait(1500);
				Intent learningScreenIntent = new Intent(MainPage.this, SpellingPage.class);

				//load screen
				MainPage.this.startActivity(learningScreenIntent);
			}
		});

		btnMathPage.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				//Starting a new Intent for Learning Page
				//                  Intent learningScreenIntent = new Intent(getApplicationContext(), LearningPage.class);
				AndroidTools.PlaySound(getBaseContext(), R.raw.animalmath);
				AndroidTools.wait(1200);
				Intent learningScreenIntent = new Intent(MainPage.this, MathPage.class);

				//load screen
				MainPage.this.startActivity(learningScreenIntent);
			}
		});
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		super.onCreateOptionsMenu(menu);                //added just now
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_main_page, menu);

		return true;
	}

	/* Handles item selections */
	public boolean onOptionsItemSelected(MenuItem item) {
		switch (item.getItemId()) {
		case R.id.menu_settings:
			//whatever you do when settings is selected
			openSettings();
			return true;
		case R.id.menu_aboutpage:
			openAboutUs();
			return true;
		}
		return false;
	}

	public void openAboutUs() {
		Intent aboutUsIntent = new Intent(MainPage.this, AboutUs.class);

		//load screen about us
		MainPage.this.startActivity(aboutUsIntent);
	}

	public void openSettings() {
		Intent settingsIntent = new Intent(MainPage.this, Settings.class);

		//load screen settings
		MainPage.this.startActivity(settingsIntent);
	}


}
