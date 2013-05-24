using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Windows.Resources;
using Microsoft.Phone.Controls;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework;

namespace AnimalMath
{
    public partial class SpellingPage : PhoneApplicationPage
    {
        Animals animals = new Animals();
        int imageIndex = 0;

        public SpellingPage()
        {
            InitializeComponent();
            imageBox.Source = new BitmapImage(animals.getAnimalIndex(imageIndex).getAnimalImage());
        }

        // Changes the text color of a TextBlock to green
        void changeColorRight(TextBlock control)
        {
            control.Foreground = new SolidColorBrush(Colors.Green);
        }

        // Changes the text color of a TextBlock to red
        void changeColorWrong(TextBlock control)
        {
            control.Foreground = new SolidColorBrush(Colors.Red);
        }

        // Displays the results in the textBox. Calls compare()
        void displayResults(string input, string answer)
        {
            // lower-case versions for comparison
            string inputLower = input.ToLower();
            string answerLower = answer.ToLower();

            // if the input is correct, print the answer in green
            if (inputLower == answerLower)
            {
                changeColorRight(textBlock1);
                textBlock1.Text = answer;
            }
            // if the input is incorrect, print the answer with incorrect letters
            // colored red
            else
            {
                // if input is shorter than answer, compare all characters and print
                // the remaining answer in red
                if (input.Length < answer.Length)
                {
                    // compare the input length
                    for (int i = 0; i < input.Length; i++)
                    {
                        if (inputLower.ElementAt(i) == answerLower.ElementAt(i))
                            textBlock1.Inlines.Add(new Run() { Text = new String(answer.ElementAt(i), 1), Foreground = new SolidColorBrush(Colors.Green) });
                        else
                            textBlock1.Inlines.Add(new Run(){Text = new String(answer.ElementAt(i), 1), Foreground = new SolidColorBrush(Colors.Red)});
                    }

                    // print the rest of the answer in red
                    textBlock1.Inlines.Add(new Run() { Text = answer.Substring(input.Length), Foreground = new SolidColorBrush(Colors.Red) });
                }
                // if input is the same length or longer than answer, compare the length
                // of the answer
                else
                {
                    for (int i = 0; i < answer.Length; i++)
                    {
                        if (inputLower.ElementAt(i) == answerLower.ElementAt(i))
                            textBlock1.Inlines.Add(new Run() { Text = new String(answer.ElementAt(i), 1), Foreground = new SolidColorBrush(Colors.Green) });
                        else
                            textBlock1.Inlines.Add(new Run() { Text = new String(answer.ElementAt(i), 1), Foreground = new SolidColorBrush(Colors.Red) });
                    }
                }
            }
        }

        private void button1_Click(object sender, RoutedEventArgs e)
        {
//<<<<<<< .mine
            //This is just test code, making sure that AnimalStructure works
            imageBox.Source = new BitmapImage(animals.getAnimalIndex(imageIndex++).getAnimalImage());
            if (imageIndex == animals.getSize())
                imageIndex = 0;  
         

           /*
            * For each index in animals.getsize
            *   create new pivot page
            *   each pivot has an image of the animal 
            *   and makes the animal's sound when selected
            *   
            *   on select the pivot is not iterrupted but keeps 
            * 
            * 
            */
//=======
            // check the name of the button
            switch (button1.Content.ToString())
            {
                case "Check":
                    // if the button says Check, display the results and set the button to Next
                    // or Main Page if all animals have been cycled
                    string input = textBox1.Text;
                    string answer = animals.getAnimalIndex(imageIndex).getAnimalName();

                    displayResults(input, answer);

                    if (++imageIndex == animals.getSize())
                        button1.Content = "Main Page";
                    else
                        button1.Content = "Next";
                    break;
                case "Next":
                    // if the button says Next, reset all controls and go to next animal
                    textBox1.Text = "";
                    textBlock1.Text = "";
                    button1.Content = "Check";
                    button1.IsEnabled = false;
                    imageBox.Source = new BitmapImage(animals.getAnimalIndex(imageIndex).getAnimalImage());
                    break;
                case "Main Page":
                    // if the button says Main Page, navigate to the main page
                    this.NavigationService.Navigate(new Uri("/MainPage.xaml", UriKind.Relative));
                    break;
            }

            ////This is just test code, making sure that AnimalStructure works
            //imageBox.Source = new BitmapImage(animals.getAnimalIndex(imageIndex++).getAnimalImage());
            //if (imageIndex == animals.getSize())
            //    imageIndex = 0;
//>>>>>>> .r27
        }

        private void textBox1_TextChanged(object sender, TextChangedEventArgs e)
        {
            // if the textBox is not empty and there are not already
            // results in the textBlock, enable the grading button
            if (textBox1.Text != "" && textBlock1.Text == "")
            {
                button1.Content = "Check";
                button1.IsEnabled = true;
            }
        }
    }
}