using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Navigation;
using System.Windows.Resources;
using System.Windows.Threading;
using Microsoft.Phone.Controls;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Media;


namespace AnimalMath
{
    public class SoundLoader
    {
        // Holds the instance of this singleton
        static private SoundLoader instance;

        // Creates the instance of this singleton if instance is null,
        // and returns the instance of this object
        static public SoundLoader Instance
        {
            get
            {
                if (instance == null)
                    instance = new SoundLoader();
                return instance;
            }
        }
   
        public void playSoundFromURI(Uri soundFilePath)
        {
            SoundEffect Sound = null;
            try
            {
                StreamResourceInfo SoundFileInfo = App.GetResourceStream(soundFilePath);
                Sound = SoundEffect.FromStream(SoundFileInfo.Stream);

                Sound.Play();
            }
            catch (NullReferenceException)
            {}
        }

        // Resets the instance
        public void Reset()
        {
            instance = new SoundLoader();
        }
    }
}
