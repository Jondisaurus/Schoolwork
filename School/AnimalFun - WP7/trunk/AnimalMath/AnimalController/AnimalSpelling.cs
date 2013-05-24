using System;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Navigation;
using System.Windows.Shapes;

using System.Collections.ObjectModel;
using System.Collections.Generic;
using System.Linq;

using System.Windows.Resources;
using Media = System.Windows.Media;

namespace AnimalMath
{
    public class VerifiedLetter
    {
        public char letter;
        public bool isCorrect;
    }

    public class VerifiedLetterCollection
    {
        public bool isCorrect;

        public Collection<VerifiedLetter> letters = new Collection<VerifiedLetter>();
    }

    // Controller class for Animal Spelling
    public class AnimalSpelling
    {
        private Animals animals;        // animals container
        private int[] animalIndexes;    // order of animal indexes to use
        private int currentIndex;       // index of current animal

        static private AnimalSpelling instance;         // instance of this singleton
        static private SpellingResultsService results;  // instance of the SpellingResultsService

        public String correctPrompt = "Good job!";
        public String incorrectPrompt = "Incorrect.";

        // Property to return the instance of this singleton
        static public AnimalSpelling Instance
        {
            get
            {
                if (instance == null)
                    instance = new AnimalSpelling();
                return instance;
            }
        }

        // Property to return the SpellingResultsService
        static public SpellingResultsService Results
        {
            get
            {
                return results;
            }
        }

        // Property to return animals.getAllUsed()
        public bool allAnimalsUsed
        {
            get
            {
                return animals.getAllUsed();
            }
        }

        // Private constructor to enforce use of the static Instance property.
        // Initializes fields and properties and sets the current index to the first
        // random animal.
        private AnimalSpelling()
        {
            results = SpellingResultsService.Instance;      // get the results service and clear any previous results
            Initialize();
        }

        // Initializes fields and properties, randomizes the animals list, and sets the
        // currentIndex to the first random animal index
        public void Initialize()
        {
            animals = new Animals();
            animalIndexes = new int[animals.getSize()];     // initialize list of indexes
            for (int i = 0; i < animals.getSize(); i++)
                animalIndexes[i] = i;
            RandomizeAnimals();                             // randomize index order
            currentIndex = 0;                               // index of current animal
            animals.setUsed(animalIndexes[currentIndex]);   // set the first animal as used
            results.Clear();                                // clear the previous results
        }

        // Method to randomize the animalIndex order
        private void RandomizeAnimals()
        {
            Random randomizer = new Random();

            for (int i = 0; i < animals.getSize(); i++)
            {
                int newIndex = randomizer.Next(animals.getSize());
                int buffer = animalIndexes[i];
                animalIndexes[i] = animalIndexes[newIndex];
                animalIndexes[newIndex] = buffer;
            }
        }

        // Returns the current animal
        public Animal GetCurrentAnimal()
        {
            if (currentIndex < 0 || currentIndex >= animals.getSize())
                return null;
            return animals.getAnimalIndex(animalIndexes[currentIndex]);
        }

        // Sets the next animal based on a random animal index. No animal in the animal set
        // is reapeted. Once the set of remaining animals is empty, sets the current animal
        // to null.
        public Animal NextAnimal(String input)
        {
            VerifiedLetterCollection verifiedInput = VerifyInput(input, GetCurrentAnimal().getAnimalName());
            // add the current input to results
            results.AddResult(GetCurrentAnimal(), verifiedInput);

            if (allAnimalsUsed)
                currentIndex = -1;

            if (currentIndex > -1 && currentIndex < animals.getSize())
                // set the current animal used
                animals.setUsed(animalIndexes[++currentIndex]);

            return GetCurrentAnimal();
        }

        // Creates a run based on the letter correctness, green for correct, red for incorrect
        public Run CreateRun(Char letter, Media.Color color)
        {
            Run letterRun = new Run();
            letterRun.Text = letter.ToString();
            letterRun.Text = letter.ToString();

            letterRun.Foreground = new SolidColorBrush(color);
            return letterRun;
        }

        public VerifiedLetterCollection VerifyInput(String userInput, String expectedInput)
        {
            VerifiedLetterCollection collection = new VerifiedLetterCollection();
            collection.isCorrect = true;

            for (int i = 0; i < userInput.Length; i++)
            {
                VerifiedLetter verifiedLetter = new VerifiedLetter();

                // Set the letter upper case if its first, otherwise lower case
                if (i == 0)
                    verifiedLetter.letter = Char.ToUpper(userInput[i]);
                else
                    verifiedLetter.letter = Char.ToLower(userInput[i]);

                // set isCorrect
                verifiedLetter.isCorrect = Char.ToLower(userInput[i]) == Char.ToLower(expectedInput[i]);
                if (!verifiedLetter.isCorrect)
                    collection.isCorrect = false;

                collection.letters.Add(verifiedLetter);
            }

            // Adds the number of missing characters as stars.
            for (int i = userInput.Length; i < expectedInput.Length; i++)
            {
                VerifiedLetter missingLetter = new VerifiedLetter();
                missingLetter.letter = '*';
                missingLetter.isCorrect = false;
                collection.letters.Add(missingLetter);
                collection.isCorrect = false;
            }
            return collection;
        }
    }
}
