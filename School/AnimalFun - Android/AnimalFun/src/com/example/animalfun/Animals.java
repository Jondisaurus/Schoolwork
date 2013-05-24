package com.example.animalfun;

import java.util.ArrayList;

public class Animals {
	private ArrayList<Animal> list = new ArrayList<Animal>();
    private boolean[] usedIndexArray;
    private int totalUsedIndexes;

    public Animals()
    {
        list = new ArrayList<Animal>();
        loadAnimals();

        usedIndexArray = new boolean[list.size()];

        for(int i = 0; i < list.size(); i++)
            usedIndexArray[i] = false;

        totalUsedIndexes = 0;    
    }

    public ArrayList<Animal> getAllAnimals()
    {
        return this.list;
    }

    public int getTotalUsed()
    {
        return this.totalUsedIndexes;
    }

    public boolean getAllUsed()
    {
        return this.totalUsedIndexes >= this.getSize();
    }

    public void resetAnimals()
    {
        for (int i = 0; i < list.size(); i++)
        {
            usedIndexArray[i] = false;
        }

        totalUsedIndexes = 0;
    }

    public void setUsed(int i)
    {
        if (i < this.usedIndexArray.length)
        {
            if (this.usedIndexArray[i] == false)
            {
                this.usedIndexArray[i] = true;
                totalUsedIndexes++;
            }
        }
    }

    public void setUnused(int i)
    {
        if (i < this.usedIndexArray.length)
        {
            if (this.usedIndexArray[i] == true)
            {
                this.usedIndexArray[i] = false;
                totalUsedIndexes--;
            }
        }
    }

    public boolean getUsed(int i)
    {
        if (i < this.usedIndexArray.length)
        {
            return this.usedIndexArray[i];
        }

        return false;
    }

    public Animal getAnimalName(String name)
    {

        for (int i = 0; i < list.size(); i++)
        {
            if (list.get(i).getAnimalName().toString().toLowerCase().equals(name))
            {
                return list.get(i);
            }
        }
        return null;
    }

    public int getSize()
    {
        return list.size();
    }

    public Animal getAnimalIndex(int i)
    {
        if (i < list.size() && i > -1)
            return list.get(i);
        return list.get(0);
    }

    public void loadAnimals()
    {
        Animal bear = new Animal("Bear");
        list.add(bear);

        Animal cat = new Animal("Cat");
        list.add(cat);

        Animal dog = new Animal("Dog");
        list.add(dog);

        Animal dolphin = new Animal("Dolphin");
        list.add(dolphin);

        Animal elephant = new Animal("Elephant");
        list.add(elephant);

        Animal lion = new Animal("Lion");
        list.add(lion);

        Animal shark = new Animal("Shark");
        list.add(shark);

        Animal snake = new Animal("Snake");
        list.add(snake);

        Animal starfish = new Animal("Starfish");
        list.add(starfish);

        Animal turtle = new Animal("Turtle");
        list.add(turtle);
    }
}
