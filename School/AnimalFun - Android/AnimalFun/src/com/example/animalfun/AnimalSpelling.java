package com.example.animalfun;

import java.util.*;

import android.graphics.Color;
import android.text.Spannable;
import android.text.SpannableStringBuilder;
import android.text.style.ForegroundColorSpan;

public class AnimalSpelling {

	public enum Colors {
		RED, GREEN;
	}

	public class VerifiedLetter {
		public char letter;
		public boolean isCorrect;
	}

	public class VerifiedLetterCollection {
		public boolean isCorrect;

		public Collection<VerifiedLetter> letters;

		public VerifiedLetterCollection() {
			letters = (Collection<VerifiedLetter>) new ArrayList<VerifiedLetter>();
		}
	}

	private Animals animals; // animals container
	private int[] animalIndexes; // order of animal indexes to use
	private int currentIndex; // index of current animal

	static private AnimalSpelling instance; // instance of this singleton
	static private SpellingResultsService results; // instance of the SpellingResultsService

	private int red = 0xffff0000;
	private int green = 0xFF298A08;

	// static public AnimalSpelling Instance;

	public static AnimalSpelling Instance() {
		if (instance == null)
			instance = new AnimalSpelling();
		return instance;
	}

	// Property to return the SpellingResultsService
	static public SpellingResultsService Results;

	public SpellingResultsService Results() {
		return results;
	}

	// Property to return animals.getAllUsed()
	public boolean allAnimalsUsed() {
		return animals.getAllUsed();
	}

	// Private constructor to enforce use of the static Instance property.
	// Initializes fields and properties and sets the current index to the first
	// random animal.
	private AnimalSpelling() {
		results = SpellingResultsService.Instance(); // get the results service
														// and clear any
														// previous results
		Initialize();
	}

	// Initializes fields and properties, randomizes the animals list, and sets
	// the
	// currentIndex to the first random animal index
	public void Initialize() {
		animals = new Animals();
		animalIndexes = new int[animals.getSize()]; // initialize list of
													// indexes
		for (int i = 0; i < animals.getSize(); i++)
			animalIndexes[i] = i;
		RandomizeAnimals(); // randomize index order
		currentIndex = 0; // index of current animal
		animals.setUsed(animalIndexes[currentIndex]); // set the first animal as
														// used
		results.Clear(); // clear the previous results
	}

	// Method to randomize the animalIndex order
	private void RandomizeAnimals() {
		Random randomizer = new Random();

		for (int i = 0; i < animals.getSize(); i++) {
			int newIndex = randomizer.nextInt(animals.getSize());
			int buffer = animalIndexes[i];
			animalIndexes[i] = animalIndexes[newIndex];
			animalIndexes[newIndex] = buffer;
		}
	}

	// Returns the current animal
	public Animal GetCurrentAnimal() {
		if (currentIndex < 0 || currentIndex >= animals.getSize())
			return null;
		return animals.getAnimalIndex(animalIndexes[currentIndex]);
	}

	// Sets the next animal based on a random animal index. No animal in the
	// animal set
	// is repeated. Once the set of remaining animals is empty, sets the current
	// animal
	// to null.
	public Animal NextAnimal(String input) {
		VerifiedLetterCollection verifiedInput = VerifyInput(input,
				GetCurrentAnimal().getAnimalName());
		// add the current input to results
		results.AddResult(GetCurrentAnimal(), verifiedInput);

		if (allAnimalsUsed())
			currentIndex = -1;

		if (currentIndex > -1 && currentIndex < animals.getSize())
			// set the current animal used
			animals.setUsed(animalIndexes[++currentIndex]);

		return GetCurrentAnimal();
	}

	// Creates a run based on the letter correctness, green for correct, red for
	// incorrect
	public String CreateRun(char letter, String color) {
		String letterRun = new String("<font color=\"" + color + "\"> "
				+ letter);
		return letterRun;
	}

	public VerifiedLetterCollection VerifyInput(String userInput,
			String expectedInput) {
		VerifiedLetterCollection collection = new VerifiedLetterCollection();
		collection.isCorrect = true;

		for (int i = 0; i < userInput.length(); i++) {
			VerifiedLetter verifiedLetter = new VerifiedLetter();

			// Set the letter upper case if its first, otherwise lower case
			if (i == 0)
				verifiedLetter.letter = Character.toUpperCase(userInput
						.charAt(i));
			else
				verifiedLetter.letter = Character.toLowerCase(userInput
						.charAt(i));

			// set isCorrect
			verifiedLetter.isCorrect = Character.toLowerCase(userInput
					.charAt(i)) == Character.toLowerCase(expectedInput
					.charAt(i));
			if (!verifiedLetter.isCorrect)
				collection.isCorrect = false;

			collection.letters.add(verifiedLetter);
		}

		// Adds the number of missing characters as stars.
		for (int i = userInput.length(); i < expectedInput.length(); i++) {
			VerifiedLetter missingLetter = new VerifiedLetter();
			missingLetter.letter = '*';
			missingLetter.isCorrect = false;
			collection.letters.add(missingLetter);
			collection.isCorrect = false;
		}
		return collection;
	}

	public SpannableStringBuilder buildVerifiedString(
			VerifiedLetterCollection collection) {
		SpannableStringBuilder verifiedText = new SpannableStringBuilder();

		for (VerifiedLetter letter : collection.letters) {
			verifiedText.append(letter.letter);
		}

		int index = 0;
		for (VerifiedLetter letter : collection.letters) {
			ForegroundColorSpan color;

			if (letter.isCorrect)
				color = new ForegroundColorSpan(green);
			else
				color = new ForegroundColorSpan(red);

			verifiedText.setSpan(color, index, index + 1,
					Spannable.SPAN_EXCLUSIVE_EXCLUSIVE);
			index++;
		}

		return verifiedText;
	}

	public SpannableStringBuilder buildColoredString(String input, Colors color) {
		SpannableStringBuilder coloredText = new SpannableStringBuilder(input);

		ForegroundColorSpan spanColor;
		switch (color) {
		case RED:
			spanColor = new ForegroundColorSpan(red);
			break;
		case GREEN:
			spanColor = new ForegroundColorSpan(green);
			break;
		default:
			return coloredText;
		}
		coloredText.setSpan(spanColor, 0, input.length(),
				Spannable.SPAN_EXCLUSIVE_EXCLUSIVE);

		return coloredText;
	}
}
