﻿using System;
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
    public partial class LearningPage : PhoneApplicationPage
    {
        public LearningPage()
        {

            Animals animals = new Animals();

            InitializeComponent();

            for (int i = 0; i < animals.getSize(); i++)
            {
                PivotItem pivotItem = new PivotItem();
                Image image = new Image();

                image.Source = new BitmapImage(animals.getAnimalIndex(i).getAnimalImage());
                pivotItem.Header = animals.getAnimalIndex(i).getAnimalName();
                pivotItem.Content = image;

       

                AnimalLearningPivot.Items.Add(pivotItem);
            }

            //on animal selection take them to a seperate scene with animal name, animal facts, and animal sounds. 
            //need to research animal facts and add them to xml files
            

            //create image view with each animal in it
            //add event when animal is clicked update thread
            //
        }
        
        private void AnimalLearningPivot_Tap(object sender, GestureEventArgs e)
        {/*
            PivotItem pivotItem = (PivotItem)AnimalLearningPivot.SelectedItem;

            Animals animals = new Animals();

            Animal animal = animals.getAnimalName((String)pivotItem.Header);

            String animalName = animal.getAnimalName();

            SoundEffect animalSound = 
       */ } 
    }
}