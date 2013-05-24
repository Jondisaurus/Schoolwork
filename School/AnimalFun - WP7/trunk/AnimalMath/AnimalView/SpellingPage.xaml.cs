using System;
using System.Collections.ObjectModel;
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
using Microsoft.Xna.Framework.Input.Touch;
using Media = System.Windows.Media;
namespace AnimalMath
{
    // This class is responsible for the spelling module
    public partial class SpellingPage : PhoneApplicationPage
    {
        AnimalSpelling animalSpelling;

        // Constructor
        public SpellingPage()
        {
            InitializeComponent();

            // save the instance of animalSpelling and initialize it
            animalSpelling = AnimalSpelling.Instance;
            animalSpelling.Initialize();
        }

        // Initializes properties and displays the first animal on load.
        private void PhoneApplicationPage_Loaded(object sender, RoutedEventArgs e)
        {
            DisplayCurrentAnimal();
        }

        // Moves the view to the next random animal.
        private void nextButton_Click(object sender, RoutedEventArgs e)
        {
            // navigate to SpellingResultsPage.xaml if no animals are left
            if (animalSpelling.NextAnimal(userInputTextBox.Text) == null)
                NavigationService.Navigate(new Uri("/AnimalMath;component/AnimalView/SpellingResultsPage.xaml", UriKind.Relative));
            else
                DisplayCurrentAnimal();
        }

        // Displays the current animal, if there is no animal left 
        // shows the results page
        private void DisplayCurrentAnimal()
        {
            Animal currentAnimal = animalSpelling.GetCurrentAnimal();

            imageBox.Source = new BitmapImage(currentAnimal.getAnimalImage());
            userInputTextBox.MaxLength = currentAnimal.getAnimalName().Length;
            userInputTextBox.Text = String.Empty;
            analyzedNameTextBlock.Text = String.Empty;
            SetAnalyzedNameTextBox("");

            UpdatePrompt();
        }

        // Shows the given input length, coloring each letter green (correct) or red (incorrect).
        private void SetAnalyzedNameTextBox(String input)
        {
            Animal currentAnimal = animalSpelling.GetCurrentAnimal();

            analyzedNameTextBlock.Inlines.Clear();
            if (currentAnimal == null)
                return;

            UpdatePrompt();

            VerifiedLetterCollection collection = animalSpelling.VerifyInput(input, currentAnimal.getAnimalName());
            foreach (VerifiedLetter letter in collection.letters)
            {
                Media.Color color;
                if (letter.isCorrect)
                    color = Colors.Green;
                else
                    color = Colors.Red;

                analyzedNameTextBlock.Inlines.Add(animalSpelling.CreateRun(letter.letter, color));
            }
        }

        // Displays colored user input when the text is changed.
        private void userInputTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            SetAnalyzedNameTextBox(((TextBox)sender).Text);

            if (userInputTextBox.Text.Length == animalSpelling.GetCurrentAnimal().getAnimalName().Length)
                Focus();
        }

        private void UpdatePrompt()
        {
            // Clear the prompt
            userPrompt.Text = String.Empty;

            // Update the prompt if the input is correct
            if (String.Compare(userInputTextBox.Text.ToLower(), animalSpelling.GetCurrentAnimal().getAnimalName().ToLower()) == 0)
            {
                foreach (Char letter in animalSpelling.correctPrompt)
                    userPrompt.Inlines.Add(animalSpelling.CreateRun(letter, Colors.Green));
                foreach (Char letter in "\nSwipe to continue.")
                    userPrompt.Inlines.Add(animalSpelling.CreateRun(letter, Colors.White));
            }
            // Update the prompt if the input is incorrect
            else if(userInputTextBox.Text.Length == animalSpelling.GetCurrentAnimal().getAnimalName().Length)
            {
                foreach (Char letter in animalSpelling.incorrectPrompt)
                    userPrompt.Inlines.Add(animalSpelling.CreateRun(letter, Colors.Red));
                foreach (Char letter in "\nTry again or swipe to continue.")
                    userPrompt.Inlines.Add(animalSpelling.CreateRun(letter, Colors.White));
            }
            else
                userPrompt.Text = "Spell this animal or swipe to skip.";
        }

        // Go back another page if navigated from SpellingResultsPage
        protected override void OnNavigatedTo(System.Windows.Navigation.NavigationEventArgs e)
        {
            if (e.NavigationMode == System.Windows.Navigation.NavigationMode.Back)
                NavigationService.GoBack();

            base.OnNavigatedTo(e);
        }

        private void OnFlick(object sender, FlickGestureEventArgs e)
        {
            // navigate to SpellingResultsPage.xaml if no animals are left
            if (animalSpelling.NextAnimal(userInputTextBox.Text) == null)
                NavigationService.Navigate(new Uri("/AnimalMath;component/AnimalView/SpellingResultsPage.xaml", UriKind.Relative));
            else
                DisplayCurrentAnimal();
        }
    }
}