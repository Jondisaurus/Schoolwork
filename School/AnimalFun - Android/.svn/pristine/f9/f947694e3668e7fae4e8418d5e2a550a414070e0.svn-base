package com.example.animalfun;
import java.util.Random;

public class AnimalMath {
	//Animals animals = new Animals();
    public int MAX_NUMBER = 9;                           //maximum number for animals displayed
    public int MAX_CHOICES = 4;                          //max number for choices, should always be 4
    public int csize = 0;                                //used for array size in correct answer selection
    public int nsize = 0;                                //used for array size in random # selection
    public int correctAnswer;                            //stores the correct answer
    public Random random = new Random();                 //instantiate new Random object
    public int[] num_array = new int[MAX_NUMBER];        //instantiate a new # array
    public int[] choice_array = new int[MAX_CHOICES];    //instantiate a new # array for choices
//    public static BitmapImage blankImage = new BitmapImage();   //used to load blank files

    //-------------------------------------------------------------------------
    //function to get random numbers that are unique using the Durstenfeld algorithm
    //sometimes known as the (Fisher–Yates shuffle)
    public int getRandomNum()
    {
    	int sub;
    	
//    	return random.nextInt(MAX_NUMBER);
    	if(nsize > 0)
    		sub = random.nextInt(nsize);        //set the subscript to a random # in range
    	else
    		sub = 0;
        int numToReturn = num_array[sub];           //set number to return based on subscript
        if (csize > 0)                              //if c size is greater than 0
            choice_array[csize - 1] = numToReturn;  //add number generated to array of choices
        if (csize >= 0)                             //if c size is greater or equal to 0
            csize--;                                //reduce csize by one
        nsize--;                                    //reduce array size
        num_array[sub] = num_array[nsize];          //set number in subscript to last number in array
        return numToReturn;                         //return number that was randomly chosen
    }
    
    //-------------------------------------------------------------------------
    //randomly pick a number from the 4 that were generated to be the answer
    public int pickCorrectAnswer()
    {
        int pick = MAX_CHOICES;                     //pick is the high limit of random numbers
        int cSub = random.nextInt(pick - 1 );       //cSub is a random number up to 'pick'
        return choice_array[cSub];                  //return the random number as an int
    }

    //-------------------------------------------------------------------------
    //used to call a getRandomNum() on each button
    public void GenerateRandomArrays()
    {
        for (int i = 0; i < MAX_NUMBER; i++)
        {
            num_array[i] = i + 1;               // initialise them to their indexes
        }
        csize = MAX_CHOICES;                    //
        nsize = MAX_NUMBER;                     //used for array size in random # selection
        correctAnswer = pickCorrectAnswer();    //pick an answer out of the random generated ones

    }

    //-------------------------------------------------------------------------
    //return a true/false if depending on whether answer is correct or not
    public Boolean isAnswerCorrect(int possibleAnswer)
    {
        if (possibleAnswer == correctAnswer)
            return true;
        else
            return false;
    }
}
