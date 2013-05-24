package com.example.animalfun;

import android.support.v4.app.Fragment;
import android.content.Context;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

public class ScreenSlidePageFragment extends Fragment{
	/**
     * The argument key for the page number this fragment represents.
     */
    public static final String ARG_PAGE = "page";
    public Animals animals; 
    public Animal animal; 
    private String animalName; 
//    private int AnimalSoundID; 
    
    private SoundLoader snd; 

    /**
     * The fragment's page number, which is set to the argument value for {@link #ARG_PAGE}.
     */
    private int mPageNumber;

    /**
     * Factory method for this fragment class. Constructs a new fragment for the given page number.
     */
    public static ScreenSlidePageFragment create(int pageNumber) {
        ScreenSlidePageFragment fragment = new ScreenSlidePageFragment();
        Bundle args = new Bundle();
        args.putInt(ARG_PAGE, pageNumber);
        fragment.setArguments(args);
        return fragment;
    }

    public ScreenSlidePageFragment() {

    	snd = new SoundLoader(this.getActivity());
    	
    	animals = new Animals(); 
    	animal = animals.getAnimalIndex(mPageNumber);
    	animalName = animal.getAnimalName();
    	
    	
    }
    
    //This is put in to help avoid a problem involving static/non-static members. 
    //...I didn't know what to call a double contructor a doubastuctor... I dunno....
    /*
    public void playSound(){ 
    	
    	AnimalSoundID = animal.getAnimalSoundID(this.getActivity());
        AnimalSoundID = snd.load(AnimalSoundID);
        
      	snd.play(AnimalSoundID);
        
    }
    */
 
    
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mPageNumber = getArguments().getInt(ARG_PAGE);
    }
    // This is where you set the view for each frame. Its a gaaaas
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
            Bundle savedInstanceState) {
        // Inflate the layout containing a title and body text.
        ViewGroup rootView = (ViewGroup) inflater
                .inflate(R.layout.learning_page_fragment, container, false);

        // Set the title view to show the page number.
        ((TextView) rootView.findViewById(android.R.id.text1)).setText((animals.getAnimalIndex(mPageNumber)).getAnimalName());

        //NOTE: I used some of this code from the Math Page. If you read this, thanks
        ((ImageView)rootView.findViewById(R.id.learning_imageView1)).setImageBitmap(
    		     BitmapFactory.decodeResource(this.getResources(), 
    					animals.getAnimalIndex(mPageNumber).getAnimalImage((this.getActivity())) )
        );
       
       final Context cntx = this.getActivity(); 

       LinearLayout ll= (LinearLayout) rootView.findViewById(R.id.fragmentLayout);
       ll.setOnClickListener(new View.OnClickListener() {
           public void onClick(View v) {
        	   animals.getAnimalIndex(mPageNumber).playAnimalSound(cntx);
           }
       });
      
       return rootView;
    }
    /**
     * Returns the page number represented by this fragment object.
     */
    public int getPageNumber() {
        return mPageNumber;
    }

}
