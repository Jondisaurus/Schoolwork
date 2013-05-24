package com.example.animalfun;

import android.content.Context;

import com.example.animalfun.AnimalSpelling.*;

public class SpellingResult {

	private Animal animal;
	private VerifiedLetterCollection verifiedInput;
	public boolean isCorrect;

	// Constructor takes the animal, the input string, and whether or not the
	// result is correct
	public SpellingResult(Animal animal, VerifiedLetterCollection verifiedInput) {
		this.animal = animal;
		this.verifiedInput = verifiedInput;
		this.isCorrect = verifiedInput.isCorrect;
	}

	// Returns the animal image
	public int getImage(Context context)
	{
		return animal.getAnimalImage(context);
	}
	
	public int getThumbnail(Context context)
	{
		return animal.getAnimalThumbnail(context);
	}

	// Returns the input string
	public VerifiedLetterCollection getInput() {
		return verifiedInput;
	}

	// Returns the animal name
	public String getName() {
		return animal.getAnimalName();
	}

	// Returns the color-coded verified input
	public VerifiedLetterCollection getVerifiedName() {
		return verifiedInput;
	}
}
