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
using System.Windows.Navigation;

namespace TransTraveler
{
    public partial class Signs : PhoneApplicationPage
    {
        private string country;

        public Signs()
        {
            InitializeComponent();

            lbSigns.DataContext = App.SignsVM;

            this.Loaded += new RoutedEventHandler(Signs_Loaded);
        }

        void Signs_Loaded(object sender, RoutedEventArgs e)
        {
            if (!App.SignsVM.IsDataLoaded)
            {
                App.SignsVM.LoadData();
            }
        }


        protected override void OnNavigatedTo(NavigationEventArgs args)
        {
            IDictionary<string, string> parameters = this.NavigationContext.QueryString;
            
            if (parameters.ContainsKey("Country"))
            {
                country = parameters["Country"];
            }

            signsPageTitle.Text = country + " Signs";
            App.SignsVM.ClearData();
            App.SignsVM.LoadData();

            base.OnNavigatedTo(args);
        }


        private void appBarCancelButton_Click(object sender, EventArgs e)
        {
            // Return to the main page.
            if (NavigationService.CanGoBack)
            {
                NavigationService.GoBack();
            }
        }
    }
}