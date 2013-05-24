using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Media.Animation;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Microsoft.Xna.Framework.Input.Touch;
using Microsoft.Phone.Controls;

namespace AnimalMath
{
    public class AnimalMath
    {
        //Animals animals = new Animals();
        public static int MAX_NUMBER = 9;                           //maximum number for animals displayed
        public static int MAX_CHOICES = 4;                          //max number for choices, should always be 4
        public static int csize = 0;                                //used for array size in correct answer selection
        public static int nsize = 0;                                //used for array size in random # selection
        public static int correctAnswer;                            //stores the correct answer
        public static Random random = new Random();                 //instantiate new Random object
        public static int[] num_array = new int[MAX_NUMBER];        //instantiate a new # array
        public static int[] choice_array = new int[MAX_CHOICES];    //instantiate a new # array for choices
        public static BitmapImage blankImage = new BitmapImage();   //used to load blank files


        //function to get random numbers that are unique using the Durstenfeld algorithm
        //sometimes known as the (Fisher–Yates shuffle)
        public static int getRandomNum()
        {
            int sub = random.Next(nsize - 1);           //set the subscript to a random # in range
            int numToReturn = num_array[sub];           //set number to return based on subscript
            if (csize > 0)                              //if c size is greater than 0
                choice_array[csize - 1] = numToReturn;  //add number generated to array of choices
            if (csize >= 0)                             //if c size is greater or equal to 0
                csize--;                                //reduce csize by one
            nsize--;                                    //reduce array size
            num_array[sub] = num_array[nsize];          //set number in subscript to last number in array
            return numToReturn;                         //return number that was randomly chosen
        }

        //randomly pick a number from the 4 that were generated to be the answer
        public static int pickCorrectAnswer()
        {
            int pick = MAX_CHOICES;                     //pick is the high limit of random numbers
            int cSub = random.Next(pick);               //cSub is a random number up to 'pick'
            return choice_array[cSub];                  //return the random number as an int
        }

        //used to call a getRandomNum() on each button
        public static void GenerateRandomArrays()
        {
            for (int i = 0; i < MAX_NUMBER; i++)
            {
                num_array[i] = i + 1;               // initialise them to their indexes
            }
            csize = MAX_CHOICES;                    //
            nsize = MAX_NUMBER;                     //used for array size in random # selection
            correctAnswer = pickCorrectAnswer();    //pick an answer out of the random generated ones

        }

        //return a true/false if depending on whether answer is correct or not
        public static Boolean isAnswerCorrect(int possibleAnswer)
        {
            if (possibleAnswer == correctAnswer)
                return true;
            else
                return false;
        }
        
    }
}
