package com.example.animalfun;
import java.io.IOException;
import java.nio.CharBuffer;

import android.app.ActionBar;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
//import android.content.Intent;
import android.media.MediaPlayer;
import android.os.Bundle;
//import android.util.Log;
//import android.view.View;
//import android.widget.Button;
//import android.widget.TextView;
import android.view.GestureDetector;
import android.view.View;
import android.view.GestureDetector.OnGestureListener;
import android.view.MotionEvent;
import android.view.View.OnClickListener;
import android.view.inputmethod.InputMethodManager;
import android.widget.*;
import android.widget.TextView.*;
import android.text.*;
import android.text.style.*;
import com.example.animalfun.AnimalSpelling.*;

public class SpellingPage extends Activity 
{
	AnimalSpelling animalSpelling;

	TextView promptTextView;
	TextView continueTextView;
	
	ImageView image;
	TextView analyzedNameTextBlock;
	EditText userInputTextBox;
	
	private SharedPreferences prefs;
	private int theme1;

	GestureDetector gestureDetector;
	
	public SpellingPage()
	{
		animalSpelling = AnimalSpelling.Instance();
		animalSpelling.Initialize();
	}
	
	private void DisplayCurrentAnimal()
	{
		 Animal currentAnimal = animalSpelling.GetCurrentAnimal();
         image.setImageResource(currentAnimal.getAnimalImage(getBaseContext()));
         
         InputFilter lengthFilter = new InputFilter.LengthFilter(currentAnimal.getAnimalName().length());
         userInputTextBox.setFilters( new InputFilter[] { lengthFilter }); 
         userInputTextBox.setText("");
         
         promptTextView.setText("");
         continueTextView.setText(getString(R.string.initial_continue));         
         
         SetAnalyzedNameTextBox("");
         
         currentAnimal.playAnimalSound(this);
	}
	
    // Shows the given input length, coloring each letter green (correct) or red (incorrect).
    private void SetAnalyzedNameTextBox(String input)
    {
        Animal currentAnimal = animalSpelling.GetCurrentAnimal();

        analyzedNameTextBlock.setText("");
        if (currentAnimal == null)
        {
            return;
        }

        VerifiedLetterCollection collection = animalSpelling.VerifyInput(input, currentAnimal.getAnimalName());
        
        analyzedNameTextBlock.setText(animalSpelling.buildVerifiedString(collection));

        if (input.length() == currentAnimal.getAnimalName().length())
        {        	
            UpdatePrompt(collection.isCorrect);
            InputMethodManager imm = (InputMethodManager)getSystemService(Context.INPUT_METHOD_SERVICE);
            imm.hideSoftInputFromWindow(userInputTextBox.getWindowToken(), 0);
        }
    }	
	
    private void UpdatePrompt(Boolean isCorrect)
    {
    	if (isCorrect)
    	{
    		promptTextView.setText(animalSpelling.buildColoredString(getString(R.string.correct_prompt), AnimalSpelling.Colors.GREEN));
    		continueTextView.setText(R.string.correct_continue);
    	}
    	else
    	{
    		promptTextView.setText(animalSpelling.buildColoredString(getString(R.string.incorrect_prompt), AnimalSpelling.Colors.RED));
    		continueTextView.setText(R.string.incorrect_continue);    	
    	}
    }
    
	public void onCreate(Bundle savedInstanceState) 
	{
        super.onCreate(savedInstanceState);
        
        this.prefs = getSharedPreferences("settings", 0);
        theme1 = this.prefs.getInt("Theme", 0);
        Utils.setThemeToActivity(this, theme1);
                        
        setContentView(R.layout.activity_spelling_page);

    	promptTextView = (TextView) findViewById(R.id.promptTextView);
    	continueTextView = (TextView) findViewById(R.id.continueTextView);
        
        image = (ImageView)findViewById(R.id.imageBox);
        analyzedNameTextBlock = (TextView) findViewById(R.id.analyzedNameTextView);
        userInputTextBox = (EditText)findViewById(R.id.userInputTextBox);
        
        TextWatcher textWatcher = new TextWatcher() 
        {
			
			@Override
			public void onTextChanged(CharSequence arg0, int arg1, int arg2, int arg3) 
			{		
			}
			
			@Override
			public void beforeTextChanged(CharSequence arg0, int arg1, int arg2, int arg3) {
			}
			
			@Override
			public void afterTextChanged(Editable text) 
			{
				SetAnalyzedNameTextBox(text.toString());
			}
		};
        userInputTextBox.addTextChangedListener(textWatcher);
        
        OnGestureListener gestureListener = new OnGestureListener() 
        {
			
			@Override
			public boolean onSingleTapUp(MotionEvent e) 
			{
				Animal currentAnimal = animalSpelling.GetCurrentAnimal();
				currentAnimal.playAnimalSound(getBaseContext());
				return true;
			}
			
			@Override
			public void onShowPress(MotionEvent e) 
			{
			}
			
			@Override
			public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX, float distanceY) 
			{
				return false;
			}
			
			@Override
			public void onLongPress(MotionEvent e) 
			{				
			}
			
			@Override
			public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX,	float velocityY) 
			{
					if (animalSpelling.NextAnimal(userInputTextBox.getText().toString()) == null)
					{
						Intent learningScreenIntent = new Intent(SpellingPage.this, SpellingResultsPage.class);
						
						//load screen
						startActivity(learningScreenIntent);				
					}
					else
					{
						DisplayCurrentAnimal();
					}
				return false;
			}
			
			@Override
			public boolean onDown(MotionEvent e) 
			{ 
				return true;
			}
		};
        
        gestureDetector = new GestureDetector(this, gestureListener);
                
        DisplayCurrentAnimal();
	}
			
	public boolean onTouchEvent(MotionEvent event) 
	{
		gestureDetector.onTouchEvent(event);
	    return true; 
	}	
}