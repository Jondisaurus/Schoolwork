package com.example.animalfun;

import android.app.Activity;
import android.content.SharedPreferences;
import android.content.res.Resources;
import android.os.Bundle;
import android.view.Gravity;
import android.widget.*;
import android.text.*;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Paint;

import com.example.animalfun.AnimalSpelling.*;

public class SpellingResultsPage extends Activity {

	private static AnimalSpelling animalSpelling;
	private static SpellingResultsService results;

	private final int imageSize = 75; // default size of images
	private final int textFontSize = 20; // default font size for textblocks
												// borders
	// private FontFamily textFont = new FontFamily("Comic Sans MS"); // default
	// font for textblocks (can't be made const)

	TableLayout resultsTable;
	private SharedPreferences prefs;
	private int theme1;

	// Constructor
	public SpellingResultsPage() {
		animalSpelling = AnimalSpelling.Instance();
		results = animalSpelling.Results();
	}

	// Inserts a TableRow with headings and calls BuildStackPanel() for each
	// result
	public void DisplayResults() {
		int numCorrect = results.NumCorrect();
		int total = results.Count();

		TableLayout.LayoutParams tableRowLayout = new TableLayout.LayoutParams(
				TableLayout.LayoutParams.MATCH_PARENT,
				TableLayout.LayoutParams.WRAP_CONTENT);

		// add column headings
		resultsTable.addView(BuildColumnHeadings(), tableRowLayout);

		// add all results
		while (results.HasMoreResults()) {
			TableRow row = BuildTableRow(results.NextResult());
			resultsTable.addView(row, tableRowLayout);
		}

		resultsTable.addView(BuildNumCorrect(numCorrect, total), tableRowLayout);
	}
	
	// Builds the column headings row
	private TableRow BuildColumnHeadings()
	{
		TableRow row = new TableRow(this);
		row.setLayoutParams(new TableRow.LayoutParams(
				TableRow.LayoutParams.MATCH_PARENT,
				TableRow.LayoutParams.WRAP_CONTENT));
		
		TextView view1 = new TextView(this);
		view1.setLayoutParams(new TableRow.LayoutParams(
		          TableLayout.LayoutParams.MATCH_PARENT,
		          TableLayout.LayoutParams.WRAP_CONTENT, 0.2f
		      ));
		
		TextView view2 = new TextView(this);
		view2.setLayoutParams(new TableRow.LayoutParams(
		          TableLayout.LayoutParams.MATCH_PARENT,
		          TableLayout.LayoutParams.WRAP_CONTENT, 0.4f
		      ));
		view2.setTextSize(textFontSize);
		view2.setText(R.string.results_answer);
		view2.setPaintFlags(view2.getPaintFlags() | Paint.UNDERLINE_TEXT_FLAG);
		
		TextView view3 = new TextView(this);
		view3.setLayoutParams(new TableRow.LayoutParams(
		          TableLayout.LayoutParams.MATCH_PARENT,
		          TableLayout.LayoutParams.WRAP_CONTENT, 0.4f
		      ));
		view3.setTextSize(textFontSize);
		view3.setText(R.string.results_actual);
		view3.setPaintFlags(view3.getPaintFlags() | Paint.UNDERLINE_TEXT_FLAG);
		
		row.addView(view1);
		row.addView(view2);
		row.addView(view3);
		
		return row;
	}

	// Builds a result row
	private TableRow BuildTableRow(SpellingResult result) {
		VerifiedLetterCollection collection = result.getInput();

		// build row
		TableRow row = new TableRow(this);
		row.setLayoutParams(new TableRow.LayoutParams(
				TableRow.LayoutParams.MATCH_PARENT,
				TableRow.LayoutParams.WRAP_CONTENT));

		// add image
		int resId = result.getThumbnail(getBaseContext());
		ImageView image = buildImageView(resId);
		row.addView(image);

		// add input text
		TextView answer = buildTextView(collection);
		row.addView(answer);

		TextView actual;
		if (collection.isCorrect)
			actual = buildTextView(collection);
		else {
			// add actual
			actual = buildTextView(result.getName());
		}
		row.addView(actual);

		return row;
	}

	// builds an image view from a resource ID
	public ImageView buildImageView(int resId) {
		ImageView image = new ImageView(this);
		image.setImageResource(resId);
		image.setLayoutParams(new TableRow.LayoutParams(
		          TableLayout.LayoutParams.MATCH_PARENT,
		          TableLayout.LayoutParams.WRAP_CONTENT, 0.2f
		      ));
		return image;
	}

	// builds a colored TextView from a verifiedLetterCollection
	public TextView buildTextView(VerifiedLetterCollection input) {
		TextView textView = new TextView(this);
		SpannableStringBuilder verifiedText = animalSpelling.buildVerifiedString(input);
		textView.setLayoutParams(new TableRow.LayoutParams(
		          TableLayout.LayoutParams.MATCH_PARENT,
		          TableLayout.LayoutParams.WRAP_CONTENT, 0.4f
		      ));
		textView.setTextSize(textFontSize);
		textView.setText(verifiedText);
		
		return textView;
	}
	
	// builds a TextView from a string
	public TextView buildTextView(String input)
	{
		TextView textView = new TextView(this);
		textView.setLayoutParams(new TableRow.LayoutParams(
		          TableLayout.LayoutParams.MATCH_PARENT,
		          TableLayout.LayoutParams.WRAP_CONTENT, 0.4f
		      ));

		textView.setTextSize(textFontSize);
		textView.setText(input);	
		
		return textView;
	}
	
	// Builds text to display the number of correct results
    private TextView BuildNumCorrect(int numCorrect, int total)
    {
        TextView view = new TextView(this);
        view.setGravity(Gravity.CENTER);
        view.setTextSize(textFontSize);

        String correctText = numCorrect + "/" + total + " Correct";
        if (numCorrect < total)
            view.setText(correctText);
        else{
        	correctText += "!";
            view.setText(animalSpelling.buildColoredString(correctText, AnimalSpelling.Colors.GREEN));
        }
        
        return view;
    }

	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		this.prefs = getSharedPreferences("settings", 0);
        theme1 = this.prefs.getInt("Theme", 0);
        Utils.setThemeToActivity(this, theme1);

		setContentView(R.layout.activity_spelling_results_page);

		resultsTable = (TableLayout) findViewById(R.id.resultsTable);

		DisplayResults();
	}
}
