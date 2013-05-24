using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;

namespace AnimalMath
{
    public partial class MathPage2 : PhoneApplicationPage
    {
        Random random = new Random();
        Button[] myButton;

        //randomly generates correct answer
        int correctAnswer; 

        //determines which button will display the correct answer
        int correctButton; 

        public MathPage2()
        {
            InitializeComponent();

            //initialize array of myButton that is linked to the 4 answer buttons
            //then disable all of them
            myButton = new[] {answer1, answer2, answer3, answer4};
            disableAllAnswerButtons();
            
        }

        void Instruction_Click(object sender, RoutedEventArgs e)
        {
            //enable all answer buttons
            enableAllAnswerButtons();

            //generate correct answer
            correctAnswer = random.Next(1, 11);

            //display the correct answer on screen
            this.CenterNumber.Text = correctAnswer.ToString();

            //determine which button will display the correct answer
            correctButton = random.Next(1, 5);

            //populate correct & wrong answers 
            populateAnswers();

            //disable the instruction button
            instructionButton.Content = " ";
            instructionButton.IsEnabled = false ;
        }


        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            determineCorrectAnswers(0);
        }
        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            determineCorrectAnswers(1);
        }
        private void Button_Click_3(object sender, RoutedEventArgs e)
        {
            determineCorrectAnswers(2);
        }
        private void Button_Click_4(object sender, RoutedEventArgs e)
        {
            determineCorrectAnswers(3);
        }


        //populate correct & incorrect answers on 4 buttons
        void populateAnswers(){
            for (int i = 0; i < myButton.Length; i++)
            {
                if (correctButton == i + 1)
                    myButton[i].Content = correctAnswer.ToString();
                else{
                    
                    int incorrectAns = generateWrongAnswer();
                    while (isAlreadyPopulated(incorrectAns))
                        incorrectAns = generateWrongAnswer();
                    myButton[i].Content = incorrectAns.ToString();
                }
            }
        }

        //generate wrong answer
        int generateWrongAnswer()
        {
            int incorrectAns = random.Next(1,11) + 99 % 11;
            while (incorrectAns == correctAnswer)
                incorrectAns = random.Next(1, 11) + 99 % 11;

            return incorrectAns;
        }

        //determine if the pressed button has the correct answer
        void determineCorrectAnswers(int n)
        {
            if (myButton[n].Content.ToString() == correctAnswer.ToString())
                populateCorrectAnswer();
            else
                populateWrongAnswer();
        }

        //alert the player if the answer was correct
        void populateCorrectAnswer()
        {
            instructionButton.Content = "YAY!";
            disableAllAnswerButtons();

            //I might implement delay sequence here
            //when i learn how to do it

            instructionButton.Content = "Continue";
            instructionButton.IsEnabled = true;
        }


        //alert the player if the answer was incorrect
        void populateWrongAnswer()
        {
            //or we could play a sound
            instructionButton.Content = "OH NO!";
        }

        //disable all Answer buttons
        void disableAllAnswerButtons()
        {
            for (int i = 0; i < myButton.Length; i++)
            {
                myButton[i].Content = " ";
                myButton[i].IsEnabled = false;
            }
            
        }

        //enable all answer buttons
        void enableAllAnswerButtons()
        {
            for (int i = 0; i < myButton.Length; i++)
                myButton[i].IsEnabled = true;
        }

        //checks if the correct/incorrect answer is already populated on 
        //1 of the 4 buttons. If true then the above populateAnswers() function 
        //will keep generating a wrong answer
        bool isAlreadyPopulated(int n)
        {
            for (int i = 0; i < 4; i++)
            {
                if (myButton[i].Content.ToString() == " ")
                    return false;
                if (Convert.ToInt32(myButton[i].Content.ToString()) == n)
                    return true;
            }
            return false;
        }
    }
}