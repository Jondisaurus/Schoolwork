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
    public partial class MathPage : PhoneApplicationPage
    {
        public MathPage()
        {
            InitializeComponent();

            //TouchPanel.EnabledGestures = GestureType.Tap | GestureType.Flick;

            //AnimalGrid.ManipulationCompleted += new EventHandler<ManipulationCompletedEventArgs>(AnimalGrid_ManipulationCompleted);

            //PopulateButtons();                      //populate buttons
            //generateImagePlacement();               //place images
            refreshPage();
        }

        Animals animals = new Animals();
        static int MAX_NUMBER = 9;                  //maximum number for animals displayed
        static int MAX_CHOICES = 4;                 //max number for choices, should always be 4
        int csize;                                  //
        int nsize;                                  //used for array size in random # selection
        int num0 = 0;                               //used to hold random integer for button 0
        int num1 = 0;                               //used to hold random integer for button 1
        int num2 = 0;                               //used to hold random integer for button 2
        int num3 = 0;                               //used to hold random integer for button 3
        int correctAnswer;                          //stores the correct answer
        Random random = new Random();               //instantiate new Random object
        int[] num_array = new int[MAX_NUMBER];      //instantiate a new # array
        int[] choice_array = new int[MAX_CHOICES];  //instantiate a new # array for choices
        Boolean choseCorrect = false;               //check for if right answer has been chosen
        Uri animalPath;                             //uri for loading animal image
        BitmapImage chosenAnimal;                     //
        BitmapImage blankImage = new BitmapImage(); //used to load blank files

        //void AnimalGrid_ManipulationCompleted(object sender, ManipulationCompletedEventArgs e)
        //{
        //    while (TouchPanel.IsGestureAvailable)
        //    {
        //        GestureSample gesture = TouchPanel.ReadGesture();

        //        switch (gesture.GestureType)
        //        {
        //            case GestureType.Tap:
        //                //GestureText.Text = "Tap";
        //                //if (choseCorrect)                //if correct answer has been found
        //                //{
        //                //    //PopulateButtons();          //repopulate buttons
        //                //    //resetImages();
        //                //    //generateImagePlacement();
        //                //    //refreshPage();
        //                //}
        //                break;
        //            case GestureType.DoubleTap:
        //                //GestureText.Text = "Double Tap";
        //                break;
        //            case GestureType.Hold:
        //                //GestureText.Text = "Hold";
        //                break;
        //            case GestureType.Flick:
        //                //refreshPage();
        //                //GestureText.Text = "Flick";

        //                break;
        //            case GestureType.Pinch:
        //                //GestureText.Text = "Pinch";
        //                break;
        //        }
        //    }
        //}

        //function to get random numbers that are unique using the Durstenfeld algorithm
        //sometimes known as the (Fisher–Yates shuffle)
        int getRandomNum()
        {
            int sub = random.Next(nsize-1);         //set the subscript to a random # in range
            int numToReturn = num_array[sub];       //set number to return based on subscript
            if(csize > 0)
                choice_array[csize - 1] = numToReturn;
            if(csize >= 0)
                csize--;
            nsize--;                                //reduce array size
            num_array[sub] = num_array[nsize];      //set number in subscript to last number in array
            return numToReturn;                     //return number that was randomly chosen
        }

        //randomly pick a number from the 4 that were generated to be the answer
        int pickCorrectAnswer()
        {
            int pick = MAX_CHOICES;         //pick is the high limit of random numbers
            int cSub = random.Next(pick);   //cSub is a random number up to 'pick'
            return choice_array[cSub];      //return the random number as an int
        }

        void generateImagePlacement()
        {
            animalPath = animals.getAnimalIndex(random.Next(animals.getSize())).getAnimalImage();
            chosenAnimal = new BitmapImage(animalPath);
            
            for (int i = 0; i < MAX_NUMBER; i++)
            {
                num_array[i] = i + 1;               // initialise them to their indexes
            }
            //csize = MAX_CHOICES;                    //
            nsize = MAX_NUMBER;                     //used for array size in random # selection
            int position;                           //
            for (int k = 0; k < correctAnswer; k++)
            {
                //if ((position = getRandomNum()) != 0)
                //{
                position = getRandomNum();
                //position = 3;
                placeImage(position, chosenAnimal);
                //}
            }
        }

        void resetImages()
        {
            AnimalGrid_1_1.Source = blankImage;
            AnimalGrid_1_2.Source = blankImage;
            AnimalGrid_1_3.Source = blankImage;
            AnimalGrid_2_1.Source = blankImage;
            AnimalGrid_2_2.Source = blankImage;
            AnimalGrid_2_3.Source = blankImage;
            AnimalGrid_3_1.Source = blankImage;
            AnimalGrid_3_2.Source = blankImage;
            AnimalGrid_3_3.Source = blankImage;
        }

        void placeImage(int position, BitmapImage chosenAnimal)
        {
            switch (position)
            {
                case 1:
                    AnimalGrid_1_1.Source = chosenAnimal;
                    break;
                case 2:
                    AnimalGrid_1_2.Source = chosenAnimal;
                    break;
                case 3:
                    AnimalGrid_1_3.Source = chosenAnimal;
                    break;
                case 4:
                    AnimalGrid_2_1.Source = chosenAnimal;
                    break;
                case 5:
                    AnimalGrid_2_2.Source = chosenAnimal;
                    break;
                case 6:
                    AnimalGrid_2_3.Source = chosenAnimal;
                    break;
                case 7:
                    AnimalGrid_3_1.Source = chosenAnimal;
                    break;
                case 8:
                    AnimalGrid_3_2.Source = chosenAnimal;
                    break;
                case 9:
                    AnimalGrid_3_3.Source = chosenAnimal;
                    break;
            }
        }

        

        //used to call a getRandomNum() on each button
        void GenerateRandom()
        {
            for (int i = 0; i < MAX_NUMBER; i++){
                num_array[i] = i + 1;               // initialise them to their indexes
            }
            csize = MAX_CHOICES;                    //
            nsize = MAX_NUMBER;                     //used for array size in random # selection
            this.num0 = getRandomNum();             //retrieve unique random number to display
            this.num1 = getRandomNum();             //retrieve unique random number to display
            this.num2 = getRandomNum();             //retrieve unique random number to display
            this.num3 = getRandomNum();             //retrieve unique random number to display
            correctAnswer = pickCorrectAnswer();    //pick an answer out of the random generated ones

            //animalPath = animals.getAnimalIndex(random.Next(animals.getSize())).getAnimalImage();
            //testAnimal = new BitmapImage(animalPath);
        }

        //used to populate buttons with numbers.
        void PopulateButtons()
        {
            this.topBarText.Text = "How Many Animal's Are There?";      //set title to starting title
            choseCorrect = false;                                       //correct answer hasnt been found yet
            refreshButtonColors();                                      //refresh buttons
            GenerateRandom();                                           //generate new numbers
            this.Math_Answer_0.Content = this.num0.ToString("N0");      //Put number on Button 0
            this.Math_Answer_1.Content = this.num1.ToString("N0");      //Put number on Button 1
            this.Math_Answer_2.Content = this.num2.ToString("N0");      //Put number on Button 2
            this.Math_Answer_3.Content = this.num3.ToString("N0");      //Put number on Button 3

            //this.answer_PH.Text = this.correctAnswer.ToString("N0");
        }

        //this function runs when you navigate to this page
        //protected override void OnNavigatedTo(NavigationEventArgs e)
        //{
        //    base.OnNavigatedTo(e);
        //    PopulateButtons();      //populate buttons
        //}




        void refreshPage()
        {
            PopulateButtons();          //repopulate buttons
            resetImages();
            generateImagePlacement();
        }
        

        //return a true/false if depending on whether answer is correct or not
        Boolean isAnswerCorrect(int possibleAnswer)
        {
            if (possibleAnswer == correctAnswer)
                return true;
            else
                return false;
        }

        //put all the things in here that you want to do on a right answer
        void processRightAnswer(Button sender)
        {
            changeColorRight(sender);
            this.topBarText.Text = "Good Job! Click to try another!";
            choseCorrect = true;
            //this.Math_Answer_0.IsEnabled = false;
        }

        //put all the things in here that you want to do on a wrong answer
        void processWrongAnswer(Button sender)
        {
            changeColorWrong(sender);
        }

        //function that changes the background color of a button if its right
        void changeColorRight(Button sender)
        {
            sender.Background = new SolidColorBrush(Colors.Green);
        }

        //function that changes the background color of a button if its wrong
        void changeColorWrong(Button sender)
        {
            sender.Background = new SolidColorBrush(Colors.Red);
        }

        //change button colors back to the original ones
        void refreshButtonColors()
        {
            this.Math_Answer_0.Background = new SolidColorBrush(Colors.Transparent);
            //this.Math_Answer_0.Background = new SolidColorBrush(SystemColors.WindowColor);
            this.Math_Answer_1.Background = new SolidColorBrush(Colors.Transparent);
            this.Math_Answer_2.Background = new SolidColorBrush(Colors.Transparent);
            this.Math_Answer_3.Background = new SolidColorBrush(Colors.Transparent);
            //Foreground="{StaticResource PhoneForegroundBrush}"
        }

        //this function runs when you click on the named object
        void Math_Answer_0_Click(object sender, RoutedEventArgs e)
        {
            if (isAnswerCorrect(num0))
            {
                processRightAnswer(this.Math_Answer_0);
            }
            else
            {
                processWrongAnswer(this.Math_Answer_0);
            }
        }
        //this function runs when you click on the named object
        void Math_Answer_1_Click(object sender, RoutedEventArgs e)
        {
            if (isAnswerCorrect(num1))
            {
                processRightAnswer(this.Math_Answer_1);
            }
            else
            {
                processWrongAnswer(this.Math_Answer_1);
            }
        }
        //this function runs when you click on the named object
        void Math_Answer_2_Click(object sender, RoutedEventArgs e)
        {
            if (isAnswerCorrect(num2))
            {
                processRightAnswer(this.Math_Answer_2);
            }
            else
            {
                processWrongAnswer(this.Math_Answer_2);
            }
        }
        //this function runs when you click on the named object
        void Math_Answer_3_Click(object sender, RoutedEventArgs e)
        {
            if (isAnswerCorrect(num3))
            {
                processRightAnswer(this.Math_Answer_3);
            }
            else
            {
                processWrongAnswer(this.Math_Answer_3);
            }
        }

        private void OnFlick(object sender, FlickGestureEventArgs e)
        {
            //refreshPage();

            if (e.HorizontalVelocity < 0) // determine direction (Right > 0)
            {
                //Some Action
                refreshPage();
            }
            else
            {
                //Some Action
                refreshPage();
            }

        }

        //when clicking on screan
        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonDown(e);
            if (choseCorrect)                //if correct answer has been found
            {
                //PopulateButtons();          //repopulate buttons
                //resetImages();
                //generateImagePlacement();
                refreshPage();
            }
        }



        //imageBox.Source = new BitmapImage(animals.getAnimalIndex(imageIndex).getAnimalImage());



    }
}