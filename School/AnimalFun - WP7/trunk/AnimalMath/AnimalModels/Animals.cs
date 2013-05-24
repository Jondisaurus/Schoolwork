﻿using System;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Shapes;
using System.Collections.Generic;
using System.Linq;

namespace AnimalMath
{
    public class Animals
    {
        private List<Animal> list = new List<Animal>();
        private bool[] usedIndexArray;
        private int totalUsedIndexes;

        public Animals()
        {
            list = new List<Animal>();
            loadAnimals();

            usedIndexArray = new bool[list.Count];

            for(int i = 0; i < list.Count; i++)
                usedIndexArray[i] = false;

            totalUsedIndexes = 0;    
        }

        public List<Animal> getAllAnimals()
        {
            return this.list;
        }

        public int getTotalUsed()
        {
            return this.totalUsedIndexes;
        }

        public bool getAllUsed()
        {
            return this.totalUsedIndexes >= this.getSize();
        }

        public void resetAnimals()
        {
            for (int i = 0; i < list.Count; i++)
            {
                usedIndexArray[i] = false;
            }

            totalUsedIndexes = 0;
        }

        public void setUsed(int i)
        {
            if (i < this.usedIndexArray.Length)
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
            if (i < this.usedIndexArray.Length)
            {
                if (this.usedIndexArray[i] == true)
                {
                    this.usedIndexArray[i] = false;
                    totalUsedIndexes--;
                }
            }
        }

        public bool getUsed(int i)
        {
            if (i < this.usedIndexArray.Length)
            {
                return this.usedIndexArray[i];
            }

            return false;
        }

        public Animal getAnimalName(String name)
        {

            for (int i = 0; i < list.Count; i++)
            {
                if (list.ElementAt(i).getAnimalName().ToString().ToLower().Equals(name))
                {
                    return list.ElementAt(i);
                }
            }
            return null;
        }

        public int getSize()
        {
            return list.Count;
        }

        public Animal getAnimalIndex(int i)
        {
            if (i < list.Count && i > -1)
                return list.ElementAt(i);
            return list.ElementAt(0);
        }

        public void loadAnimals()
        {
            Animal bear = new Animal("Bear");
            list.Add(bear);

            Animal cat = new Animal("Cat");
            list.Add(cat);

            Animal dog = new Animal("Dog");
            list.Add(dog);

            Animal dolphin = new Animal("Dolphin");
            list.Add(dolphin);

            Animal elephant = new Animal("Elephant");
            list.Add(elephant);

            Animal lion = new Animal("Lion");
            list.Add(lion);

            Animal shark = new Animal("Shark");
            list.Add(shark);

            Animal snake = new Animal("Snake");
            list.Add(snake);

            Animal starfish = new Animal("Starfish");
            list.Add(starfish);

            Animal turtle = new Animal("Turtle");
            list.Add(turtle);
        }
    }
}
