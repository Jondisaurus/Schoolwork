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
    // Singleton class for storing and retrieving spelling results
    public class SpellingResultsService
    {
        private Queue<SpellingResult> results;  // Queue of results

        // Private constructor to enforce use of the static Instance property
        private SpellingResultsService()
        {
            results = new Queue<SpellingResult>();
        }

        // Holds the instance of this singleton
        static private SpellingResultsService instance;

        // Creates the instance of this singleton if instance is null,
        // and returns the instance of this object
        static public SpellingResultsService Instance
        {
            get
            {
                if (instance == null)
                    instance = new SpellingResultsService();
                return instance;
            }
        }

        // Returns the number of results stored
        public int Count
        {
            get
            {
                return results.Count;
            }
        }

        // Returns whether the queue has more results
        public bool HasMoreResults()
        {
            return results.Count > 0;
        }

        // Adds the result to the results queue
        public void AddResult(SpellingResult result)
        {
            if(result != null)
                results.Enqueue(result);
        }

        // Constructs a new result from an animal and user input string and adds it to the results queue
        public void AddResult(Animal animal, VerifiedLetterCollection verifiedInput)
        {
            if (animal != null && verifiedInput != null)
                results.Enqueue(new SpellingResult(animal, verifiedInput));
        }

        // Returns the next result on the results queue
        public SpellingResult NextResult()
        {
            return results.Dequeue();
        }

        // Empties the results list
        public void Clear()
        {
            results.Clear();
        }
    }
}
