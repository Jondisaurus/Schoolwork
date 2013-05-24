//This class contains the backend for the MathPage
package com.example.animalfun;
import android.app.ActionBar;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.SharedPreferences;
import android.content.res.ColorStateList;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TableLayout;
import android.widget.ImageView;
import android.widget.TextView;

public class MathPage extends Activity {
	
	ImageView[] imageViews;		//array of image views
	Button[] buttons;			//array of buttons
	Animals animals = new Animals();
	Bitmap blank;
	Bitmap chosenAnimal;
	AnimalMath math = new AnimalMath();
	TextView topText;
	Drawable originalBackground;
	int defColor;
	
	private SharedPreferences prefs;
	private int theme1;
	
//	int counter = 1;
	
//	Animal testAn = new Animal("Bear");
	
	//create an integer array that stores a "pointer"
	//to the drawable object that will be displayed
	//"pointer" because i am not sure what they are called
	//but in the R.java, each drawable is assigned an int
//	Integer[] mImageIds = {
//			R.drawable.bear, 
//			R.drawable.cat,
//			R.drawable.dog,
//			R.drawable.dolphin,
//			R.drawable.elephant,
//			R.drawable.lion,
//			R.drawable.shark,
//			R.drawable.snake,
//			R.drawable.starfish,
//			R.drawable.turtle
//	};
	
	//create an integer array that stores a "pointer"
	//to the imageview object that will be displayed
	//"pointer" because i am not sure what they are called
	//but in the R.java, each imageview is assigned an int
	Integer[] imageViewIds = {
		R.id.math_imageView1,
		R.id.math_imageView2,
		R.id.math_imageView3,
		R.id.math_imageView4,
		R.id.math_imageView5,
		R.id.math_imageView6,
		R.id.math_imageView7,
		R.id.math_imageView8,
		R.id.math_imageView9
	};
	
	Integer[] buttonIds = {
			R.id.math_button1,
			R.id.math_button2,
			R.id.math_button3,
			R.id.math_button4
	};

	//imageNum is an int that is used to pick which drawable
	//to display
	int imageNum = 0;
	
	//onCreate is ran when the page is first loaded, all the things you want
	//to happen on load go in this function
	public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
//        ActionBar actionBar = getActionBar();	//create and load action bar object
//        actionBar.setTitle("MathPage");			//set title on the action bar
//        actionBar.hide();						//uncomment to hide action bar on top!!
       
//      this.theme1 = this.prefs.getInt("Theme", 0);
        this.prefs = getSharedPreferences("settings", 0);
        theme1 = this.prefs.getInt("Theme", 0);
        Utils.setThemeToActivity(this, theme1);
//      
//        int myTheme = Utils.theme;
//        String mystring = Integer.toString(myTheme);
//        
//        //alert for testing purposes only
//        new AlertDialog.Builder(this)
//        	.setTitle("Value of Utils.theme")
//        	.setMessage(mystring)
//        	.setNeutralButton("Close", null).show(); 
        
        
//        switch(theme1) {
//        case 0:
//        	setTheme(R.style.LightTheme);
//        	break;
//        case 1:
//        	setTheme(R.style.DarkTheme);
//        	break;
//        }
        
//        Utils.setThemeToActivity(this, theme1);
//        setTheme(R.style.DarkTheme);
        
        setContentView(R.layout.activity_math_page);	//load specified xml page
//        Animal animalClass = new Animal(this);
        topText = (TextView) findViewById(R.id.math_topText);
        ColorStateList csl = topText.getTextColors();
        defColor = csl.getDefaultColor();
        
        //call to set up the array of imageviews
        setImageViews();
        setButtonArray();
        
        
        //set the images initially
//    	setImages();
        refreshPage();
    	
    	setButtonArray();

        //create tablelayout object, used to capture tap events
        TableLayout table = (TableLayout) findViewById(R.id.TableLayout01);
  
        //set a click listener to catch taps/clicks on the table and do
        //whatever you want within the onClick function
        table.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
//				imageNum = (imageNum + 1) % animals.getSize();	//change int to next int
//				setImages();							//set images again
				refreshPage();
			}
		});


//        int test2 = this.getResources().getIdentifier(animalName.toLowerCase(), "drawable", this.getPackageName());
//        buttons[0].setText(testAn.getAnimalImage(this));
//        buttons[2].setText(mImageIds[0]);
	}
	
	//-------------------------------------------------------------------------
	//getCount returns the length of the array that contains the drawables
	public int getAnimalCount() {
//    	return mImageIds.length;
		return animals.getSize();
    }
	
	//-------------------------------------------------------------------------
	public int getGridCount() {
		return imageViewIds.length;
	}
	
	public void setButtonArray() {
		buttons = new Button[4];
		for(int i = 0; i < 4; i++) {
			buttons[i] = (Button) findViewById(buttonIds[i]);
		}
		originalBackground = buttons[0].getBackground();
	}
	
	//-------------------------------------------------------------------------
	//set up the imageViews array with all of the imageview ids
	public void setImageViews() {
		imageViews = new ImageView[getGridCount()];
		for(int i = 0; i < getGridCount(); i++)	{
			imageViews[i] = (ImageView) findViewById(imageViewIds[i]);
		}
		
	}
	
	//-------------------------------------------------------------------------
	public void refreshPage() {
//		topText.setText("Count the ");
		resetButtons();				//reset buttons to be blank
		populateButtons();          //repopulate buttons
        resetImages();              //reset images to be blank
        setImages();
//        generateImagePlacement();   //generate and place images into grid
	}
	
	//-------------------------------------------------------------------------
	public void resetImages() {
		for(int i=0; i < getGridCount(); i++) {
			imageViews[i].setImageBitmap(blank);
		}
	}
	
	//-------------------------------------------------------------------------
	public void resetButtons() {
		for(int i=0; i < 4; i++) {
			
		}
	}
	
	//-------------------------------------------------------------------------
	void populateButtons() {
		
		math.GenerateRandomArrays();
		for(int i = 0; i < 4; i++) {
//			buttons[i].setBackground(originalBackground);
//			buttons[i].setClickable(true);
			buttons[i].setEnabled(true);
			buttons[i].setTextColor(Color.BLACK);
			buttons[i].setText(Integer.toString(math.getRandomNum()));
		}
	}
	
	//-------------------------------------------------------------------------
	//used to set the resource for each imageview object using the
	//array of drawables/ints
	public void setImages() {
		
		imageNum = (imageNum + 1) % animals.getSize();	//change int to next int
		String name = animals.getAnimalIndex(imageNum).getAnimalNamePlural();
		topText.setTextColor(defColor);
		topText.setText("Count the " + name);
		math.GenerateRandomArrays();
//		topText.setText(Integer.toString(math.correctAnswer));

		int position;
//		animals.getAnimalIndex(imageNum).getAnimalImage(this)
		chosenAnimal = BitmapFactory.decodeResource(this.getResources(), 
				animals.getAnimalIndex(imageNum).getAnimalImage(this) );
		for(int i = 0; i < math.correctAnswer; i++)	{
			position = math.getRandomNum()-1;		//get spot on grid
			imageViews[position].setImageBitmap(chosenAnimal);	//place animal

		}

	}
	
	//called whenever one of the buttons on the math page is pressed
	//the switch gets the id of the button that got pressed and checks
	//the answer that is on that button
	//-------------------------------------------------------------------------
	public void processClick(View v) {
//		originalBackground = v.getBackground();
//		counter--;
		switch(v.getId()) {
		case R.id.math_button1:
			checkAnswer(0);			//check answer for button 1
			break;
		case R.id.math_button2:
			checkAnswer(1);			//check answer for button 2
			break;
		case R.id.math_button3:
			checkAnswer(2);			//check answer for button 3
			break;
		case R.id.math_button4:
			checkAnswer(3);			//check answer for button 4
			break;
		}
	}
	
	//used to take the number that is on the button and convert it from a 
	//string to an int, then check if it matches with the correct answer
	//-------------------------------------------------------------------------
	public void checkAnswer(int buttonNum) {
		String ans = buttons[buttonNum].getText().toString();	//get string
		int possibleAnswer = Integer.valueOf(ans);				//string to int
		if(math.isAnswerCorrect(possibleAnswer))				//check answer
			processRightAnswer(buttonNum);			//if right, process
		else
			processWrongAnswer(buttonNum);			//if wrong, process
	}
	
	//put whatever you want to happen when the right answer is chosen
	//in this function
	//-------------------------------------------------------------------------
	public void processRightAnswer(int buttonNum) {
		topText.setText("Excellent");
		topText.setTextColor(0xFF556B2F);
		buttons[buttonNum].setTextColor(0xFF556B2F);
//		buttons[buttonNum].setEnabled(false);
//		buttons[buttonNum].setBackgroundColor(Color.GREEN);	//background to green
		for(int i = 0; i < 4; i++){
//			if(buttonNum != i)
			buttons[i].setEnabled(false);		//disable all buttons
		}
	}
	
	//put whatever you want to happen when the wrong answer is chosen in this
	//funcion
	//-------------------------------------------------------------------------
	public void processWrongAnswer(int buttonNum) {
		topText.setText("TRY AGAIN");
		topText.setTextColor(Color.RED);
		buttons[buttonNum].setTextColor(Color.RED);
//		buttons[buttonNum].setEnabled(false);
//		buttons[buttonNum].setBackgroundColor(Color.RED);
	}
}







