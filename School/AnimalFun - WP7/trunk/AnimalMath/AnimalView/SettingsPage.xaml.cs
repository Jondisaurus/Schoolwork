using System;
using System.IO.IsolatedStorage;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using System.Windows.Media.Imaging;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using System.Windows.Media.Imaging;

namespace AnimalMath.AnimalView
{
    public partial class SettingsPage : PhoneApplicationPage
    {
        IsolatedStorageSettings settings;

        /*
         * TODO ====
         * ---------
         * 
         * XXX Put in keys for "Currently selected background"
         * Save/load from isolated storage file
         * Put in objects in each page 
         *      load fro isolated storage
         *      set background image src to current background in storage
         * Create grid and add backgrounds
         * generate very simple color back grounds
         * check fonts of all pages and update to comic sans
         * reticulate splines
         * 
         * On button click
         *    change isolated storeage setting to currently button image source
         *    
         * On each page
         *    load isolated storage
         *    change background to isolated storage item. 
         *    
         */


        //Storage keys for settings lookup
        const string BackgroundKeyName = "BackgroundSetting";

        

        //Default settings
        const System.Windows.Media.ImageSource BackgroundSettingDefault = null;
        const int DifficultySettingDefault = 0;

        public SettingsPage()
        {
            InitializeComponent();

            settings = IsolatedStorageSettings.ApplicationSettings;
        }

        public bool AddOrUpdateValue(string Key, Object value)
        {
            bool valueChanged = false;

            // If the key exists
            if (settings.Contains(Key))
            {
                // If the value has changed
                if (settings[Key] != value)
                {
                    // Store the new value
                    settings[Key] = value;
                    valueChanged = true;
                }
            }
            // Otherwise create the key.
            else
            {
                settings.Add(Key, value);
                valueChanged = true;
            }
            return valueChanged;
        }

        private void  setBackground()
        {
            if(settings.Contains("BackGroundSetting"))
            {
                Background.Source = BackgroundSetting;
            }
        }

        // Handle a tap on the button for Settings
        void Button_Settings_Click(object sender, RoutedEventArgs e)
        {
           
        }


        /// Get the current value of the setting, or if it is not found, set the 
        /// setting to the default setting.
        public T GetValueOrDefault<T>(string Key, T defaultValue)
        {
            T value;

            // If the key exists, retrieve the value.
            if (settings.Contains(Key))
            {
                value = (T)settings[Key];
            }
            // Otherwise, use the default value.
            else
            {
                value = defaultValue;
            }
            return value;
        }

        //Save settings
        public void Save()
        {
            settings.Save();
        }

        /// <summary>
        /// Property to get and set a ListBox Setting Key.
        /// </summary>
        public System.Windows.Media.ImageSource BackgroundSetting
        {
            get
            {
                return GetValueOrDefault<System.Windows.Media.ImageSource>
                    (BackgroundKeyName, BackgroundSettingDefault);
            }
            set
            {
                if (AddOrUpdateValue(BackgroundKeyName, value))
                {
                    Save();
                }
            }
        }

        private void Blue_Click(object sender, RoutedEventArgs e)
        {
            BackgroundSetting = blueImg.Source;
            setBackground();
        }
    }
}