using System;
using System.Collections.Generic;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Shapes;
using System.Xml.Linq;
using System.Linq;

namespace TransTraveler
{
    public static class ContinentsParser
    {
        public static List<string> GetContinents()
        {
            XElement myElement = XElement.Load(@"Datastore\Xml\Continents.xml");
            List<string> listOfContinents = new List<string>();

            foreach (XElement continent in myElement.Elements("continent"))
            {
                listOfContinents.Add(continent.Element("name").Value);
            }

            listOfContinents.Sort();

            return listOfContinents;
        }

        public static List<string> GetCountries(string continentName)
        {
            XElement myElement = XElement.Load(@"Datastore\Xml\Continents.xml");
            List<string> listOfCountries = new List<string>();


            IEnumerable<XElement> tmpElements = from p in myElement.Elements("continent")
                                                where p.Element("name").Value == continentName
                                                select p;

            XElement countries = tmpElements.First<XElement>().Element("countries");


            foreach (XElement country in countries.Elements("country"))
            {
                listOfCountries.Add(country.Value);
            }

            listOfCountries.Sort();

            return listOfCountries;
        }
    }
}
