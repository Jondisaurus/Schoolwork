using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Shapes;
using Microsoft.Phone.Controls;

namespace TransTraveler
{
    public partial class MainPage : PhoneApplicationPage
    {
        private string _currentCountry;

        // Constructor
        public MainPage()
        {
            InitializeComponent();

            // Set the data context of the listbox control to the sample data
            lbContinents.DataContext = App.ContinentVM;
            lbCountries.DataContext = App.CountryVM;
            lbCountryMenu.DataContext = App.MenuVM;

            _currentCountry = string.Empty;

            this.Loaded += new RoutedEventHandler(MainPage_Loaded);
        }

        // Load data for the ViewModel Items
        private void MainPage_Loaded(object sender, RoutedEventArgs e)
        {
            if (!App.ContinentVM.IsDataLoaded)
            {
                App.ContinentVM.LoadData();
            }
        }      

        private void lbContinents_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            //Clear down stream PanoramaItems
            App.MenuVM.ClearData();
            piCountryMenu.Header = string.Empty;

            App.CountryVM.ClearData();

            _currentCountry = string.Empty;


            string continent = ((ItemViewModel)e.AddedItems[0]).LineOne;
            App.CountryVM.LoadData(continent);

            pMain.DefaultItem = pMain.Items[1];
        }

        private void lbCountries_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (App.CountryVM.IsDataLoaded)
            {
                App.MenuVM.ClearData();

                string country = ((ItemViewModel)e.AddedItems[0]).LineOne;

                piCountryMenu.Header = country;

                App.MenuVM.LoadData(country);

                _currentCountry = country;

                pMain.DefaultItem = pMain.Items[2];
            }
        }

        private void bCountryMen_Click(object sender, RoutedEventArgs e)
        {
            if (App.MenuVM.IsDataLoaded)
            {
                Button b = (Button)e.OriginalSource;
                StackPanel sp = (StackPanel)b.Content;
                string buttonText = ((TextBlock)sp.Children[0]).Text;

                switch (buttonText)
                {
                    case "Signs":
                        {
                            NavigationService.Navigate(new Uri("/DataPages/Signs.xaml?Country=" + _currentCountry, UriKind.Relative));
                            piCountryMenu.UpdateLayout();
                            break;
                        }
                    case "Currency": 
                        {
                            NavigationService.Navigate(new Uri("/DataPages/Currency.xaml?Country=" + _currentCountry, UriKind.Relative));
                            piCountryMenu.UpdateLayout();
                            break;
                        }
                    default:
                        {
                            break;
                        }
                }
            }
        }
    }
}