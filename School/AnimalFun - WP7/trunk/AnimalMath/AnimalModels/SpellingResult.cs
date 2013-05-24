using System;
using System.Collections.ObjectModel;
using System.Collections.Generic;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Shapes;

namespace AnimalMath
{
    // Class to hold a single spelling result
    public class SpellingResult
    {
        private Animal animal;
        private VerifiedLetterCollection verifiedInput;
        public bool isCorrect;

        // Constructor takes the animal, the input string, and whether or not the result is correct
        public SpellingResult(Animal animal, VerifiedLetterCollection verifiedInput)
        {
            this.animal = animal;
            this.verifiedInput = verifiedInput;
            this.isCorrect = verifiedInput.isCorrect;
        }

        // Returns the animal image Uri
        public Uri getImage()
        {
            return animal.getAnimalImage();
        }

        // Returns the input string
        public VerifiedLetterCollection getInput()
        {
            return verifiedInput;
        }

        // Returns the animal name
        public String getName()
        {
            return animal.getAnimalName();
        }

        // Returns the color-coded verified input
        public VerifiedLetterCollection getVerifiedName()
        {
            return verifiedInput;
        }
    }
}
