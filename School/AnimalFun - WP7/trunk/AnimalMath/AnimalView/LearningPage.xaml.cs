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
        }

        private void AnimalLearningPivot_Tap_1(object sender, System.Windows.Input.GestureEventArgs e)
        {
            SoundLoader soundLoader = new SoundLoader();
            int selectedItem = AnimalLearningPivot.SelectedIndex;

            Animals animals = new Animals();
            Animal animal = animals.getAnimalIndex(selectedItem);
            soundLoader.playSoundFromURI(animal.getAnimalSound());
        }
    }
}