using System;
using System.ComponentModel;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Collections.ObjectModel;
using System.Xml.Linq;


namespace TransTraveler
{
    public class SignsViewModel : INotifyPropertyChanged
    {
        public SignsViewModel()
        {
            this.Items = new ObservableCollection<ItemViewModel>();
        }

        /// <summary>
        /// A collection for ItemViewModel objects.
        /// </summary>
        public ObservableCollection<ItemViewModel> Items { get; private set; }

        private string _sampleProperty = "Sample Runtime Property Value";
        /// <summary>
        /// Sample ViewModel property; this property is used in the view to display its value using a Binding
        /// </summary>
        /// <returns></returns>
        public string SampleProperty
        {
            get
            {
                return _sampleProperty;
            }
            set
            {
                if (value != _sampleProperty)
                {
                    _sampleProperty = value;
                    NotifyPropertyChanged("SampleProperty");
                }
            }
        }

        public bool IsDataLoaded
        {
            get;
            private set;
        }

        /// <summary>
        /// Creates and adds a few ItemViewModel objects into the Items collection.
        /// </summary>
        public void LoadData()
        {
            this.Items.Add(new ItemViewModel() { LineOne = "Maximum Speed", LineTwo = @"..\Datastore\Japan\Maximum_Speed.jpg" });
            this.Items.Add(new ItemViewModel() { LineOne = "No Crossing Center Line to Overtake", LineTwo = @"..\Datastore\Japan\No Crossing Center Line to Overtake.jpg" });
            this.Items.Add(new ItemViewModel() { LineOne = "No Motor Vehicles", LineTwo = @"..\Datastore\Japan\No Motor Vehicles.jpg" });
            this.Items.Add(new ItemViewModel() { LineOne = "No Stopping", LineTwo = @"..\Datastore\Japan\No Stopping.jpg" });

            this.IsDataLoaded = true;
        }

        public void ClearData()
        {
            IsDataLoaded = false;
            this.Items.Clear();
        }

        public event PropertyChangedEventHandler PropertyChanged;
        private void NotifyPropertyChanged(String propertyName)
        {
            PropertyChangedEventHandler handler = PropertyChanged;
            if (null != handler)
            {
                handler(this, new PropertyChangedEventArgs(propertyName));
            }
        }
    }
}