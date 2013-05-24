package com.example.animalfun;
//
//import android.os.Bundle;
//import android.preference.PreferenceActivity;
//
//public class Settings extends PreferenceActivity {
//	@SuppressWarnings("deprecation")
//	@Override
//    public void onCreate(Bundle savedInstanceState) {
//        super.onCreate(savedInstanceState);
//        addPreferencesFromResource(R.xml.settings);
//    }
//}

//import android.app.Activity;
//import android.content.SharedPreferences;
//import android.os.Bundle;
//import android.preference.PreferenceActivity;
//import android.preference.PreferenceManager;
//import android.widget.TextView;
//
//public class Settings extends PreferenceActivity {
//
//	@SuppressWarnings("deprecation")
//	@Override
//	protected void onCreate(Bundle savedInstanceState) {
//
//		super.onCreate(savedInstanceState);
//		addPreferencesFromResource(R.xml.settings);
//		setContentView(R.layout.show_settings);
//
//		SharedPreferences sharedPrefs = PreferenceManager.getDefaultSharedPreferences(this);
//
//		StringBuilder builder = new StringBuilder();
//
//		builder.append("\n" + sharedPrefs.getBoolean("perform_updates", false));
//		builder.append("\n" + sharedPrefs.getString("updates_interval", "-1"));
//		builder.append("\n" + sharedPrefs.getString("welcome_message", "NULL"));
//
//		TextView settingsTextView = (TextView) findViewById(R.id.settings_text_view);
//		settingsTextView.setText(builder.toString());
//
//	}
//
//}

//import com.example.animalFun.R;

//import java.util.prefs.Preferences;

import android.app.AlertDialog;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.ListPreference;
import android.preference.Preference;
import android.preference.PreferenceActivity;
 
public class Settings extends PreferenceActivity {
	
	private SharedPreferences prefs;
	private SharedPreferences.Editor editor;
	private ListPreference theme;
	private int theme1;
	
    @SuppressWarnings("deprecation")
	@Override
    protected void onCreate(Bundle savedInstanceState) {
    	
    	this.prefs = getSharedPreferences("settings", 0);
    	this.editor = this.prefs.edit();
        this.theme1 = this.prefs.getInt("Theme", 0);
        
        switch(this.theme1) {
        case 0:
        	setTheme(R.style.LightTheme);
        	break;
        case 1:
        	setTheme(R.style.DarkTheme);
        	break;
        }
        
        
        super.onCreate(savedInstanceState);
        addPreferencesFromResource(R.xml.preferences);
        
        this.theme = ((ListPreference)findPreference("Theme"));
        this.theme.setSummary(getResources()
        		.getStringArray(R.array.themes)[this.prefs.getInt("Theme", 0)]);
        
        this.theme.setOnPreferenceChangeListener(new Preference.OnPreferenceChangeListener()
        {
          public boolean onPreferenceChange(Preference myPref, Object param)
          {
        	  Utils.theme = (Utils.theme + 1) % 2;
        	  Utils.changed = true;
//        	  Utils.theme = prefs.getInt("Theme", 1);
//        	  Utils.theme = 1;
//        	  showMessage();
//        	  Utils.theme = prefs.getInt("Theme", 1);
        	  editor.putInt("Theme", Integer.parseInt(param.toString()));
        	  editor.putInt("Theme", Utils.theme ); 
        	  editor.commit();
        	  theme.setSummary(getResources().getStringArray(R.array.themes)[Integer.parseInt(param.toString())]);
//            startActivity(new Intent( Settings.this, Settings.class));
        	  return true;
          }
          
        });
        
        
        

    }
    
    public void showMessage() {
    	
    	int myTheme = Utils.theme;
        String mystring = Integer.toString(myTheme);
        
    	//alert for testing purposes only
        new AlertDialog.Builder(this)
        	.setTitle("Value of Utils.theme")
        	.setMessage(mystring)
        	.setNeutralButton("Close", null).show(); 
    }
    
//  @Override
//	public void onBackPressed() {
//		// TODO Auto-generated method stub
//		super.onBackPressed();
////		startActivity(new Intent( Settings.this, MainPage.class));
////		Settings.this.finish();
//	}
  
  
  
  
}







