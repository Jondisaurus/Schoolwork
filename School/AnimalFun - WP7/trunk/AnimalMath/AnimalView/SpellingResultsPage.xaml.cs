using System;
using System.Collections.ObjectModel;
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
using Microsoft.Phone.Controls;
using Media = System.Windows.Media;

namespace AnimalMath
{
    public partial class SpellingResultsPage : PhoneApplicationPage
    {
        private const int imageSize = 70;           // default size of images
        private const int imageBorderWidth = 80;    // default width of image borders
        private const int textFontSize = 36;        // default font size for textblocks
        private const int textBorderWidth = 188;    // default width of textblock borders
        private FontFamily font = new FontFamily("Comic Sans MS");  // default font for textblocks (can't be made const)

        // Constructor
        public SpellingResultsPage()
        {
            InitializeComponent();
        }

        // Inserts a stackpanel with headings and calls BuildStackPanel() for each result
        public void DisplayResults()
        {
            // add column headings
            BuildColumnHeadings();

            // add all results
            while (AnimalSpelling.Results.HasMoreResults())
                spellingResultsList.Items.Add(BuildStackPanel(AnimalSpelling.Results.NextResult()));
        }

        // Builds the column headings
        private void BuildColumnHeadings()
        {

            // Empty border for correct spacing
            Border imageSizeBorder = new Border();
            imageSizeBorder.Width = imageBorderWidth;

            // Input heading border
            Border inputHeadingBorder = new Border();
            inputHeadingBorder.Width = textBorderWidth;

            // "Answer" heading
            TextBlock inputHeadingBlock = new TextBlock();
            inputHeadingBlock.FontSize = textFontSize;
            inputHeadingBlock.FontFamily = font;
            inputHeadingBlock.TextDecorations = TextDecorations.Underline;
            inputHeadingBlock.Text = "Answer";
            inputHeadingBorder.Child = inputHeadingBlock;

            // Result heading border
            Border resultHeadingBorder = new Border();
            resultHeadingBorder.Width = textBorderWidth;

            // "Actual" heading
            TextBlock resultHeadingBlock = new TextBlock();
            resultHeadingBlock.FontSize = textFontSize;
            resultHeadingBlock.FontFamily = font;
            resultHeadingBlock.TextDecorations = TextDecorations.Underline;
            resultHeadingBlock.Text = "Actual";
            resultHeadingBorder.Child = resultHeadingBlock;

            // add the borders
            columnHeadingsPanel.Children.Add(imageSizeBorder);
            columnHeadingsPanel.Children.Add(inputHeadingBorder);
            columnHeadingsPanel.Children.Add(resultHeadingBorder);
        }

        // Builds a stackpanel from a SpellingResult
        private StackPanel BuildStackPanel(SpellingResult result)
        {
            StackPanel sp = new StackPanel();
            sp.Orientation = System.Windows.Controls.Orientation.Horizontal;

            sp.Children.Add(BuildImage(result.getImage()));
            sp.Children.Add(BuildFormattedBlock(result.getVerifiedName()));
            if (result.isCorrect)
                sp.Children.Add(BuildFormattedBlock(AnimalSpelling.Instance.VerifyInput("Correct!", "Correct!")));
            else
                sp.Children.Add(BuildUnformattedBlock(result.getName()));

            return sp;
        }

        // Builds an image from a source
        private Border BuildImage(Uri source)
        {
            // Build the image
            Image image = new Image();
            image.Height = image.Width = imageSize;
            image.Source = new BitmapImage(source);

            // Build the border
            Border imageBorder = new Border();
            imageBorder.Width = imageBorderWidth;
            imageBorder.Child = image;

            return imageBorder;
        }

        // Builds a formatted textBlock from formatted text
        private Border BuildFormattedBlock(VerifiedLetterCollection text)
        {
            // Build the textBlock
            TextBlock formattedTextBlock = new TextBlock();
            formattedTextBlock.FontSize = textFontSize;
            formattedTextBlock.FontFamily = font;
            foreach (VerifiedLetter letter in text.letters)
            {
                Media.Color color;
                if (letter.isCorrect)
                    color = Colors.Green;
                else
                    color = Colors.Red;

                formattedTextBlock.Inlines.Add(AnimalSpelling.Instance.CreateRun(letter.letter, color));
            }

            // Build the border
            Border formattedTextBorder = new Border();
            formattedTextBorder.Width = textBorderWidth;
            formattedTextBorder.Child = formattedTextBlock;

            return formattedTextBorder;
        }

        // Builds an unformatted textBlock from a string
        private Border BuildUnformattedBlock(String text)
        {
            // Build the textblock
            TextBlock unformattedTextBlock = new TextBlock();
            unformattedTextBlock.FontSize = textFontSize;
            unformattedTextBlock.FontFamily = font;
            unformattedTextBlock.Text = text;

            // Build the border
            Border unformattedTextBorder = new Border();
            unformattedTextBorder.Width = textBorderWidth;
            unformattedTextBorder.Child = unformattedTextBlock;

            return unformattedTextBorder;
        }

        // Display results on page load
        private void PhoneApplicationPage_Loaded(object sender, RoutedEventArgs e)
        {
            DisplayResults();
        }

        // Workaround to disable listBox selection
        private void spellingResultsList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (spellingResultsList.SelectedIndex != -1)
                spellingResultsList.SelectedIndex = -1;
        }

        // Remove the SpellingPage from the BackStack
        protected override void OnNavigatedTo(System.Windows.Navigation.NavigationEventArgs e)
        {
            if (e.NavigationMode != System.Windows.Navigation.NavigationMode.Back)
                NavigationService.RemoveBackEntry();

            base.OnNavigatedTo(e);
        }
    }
}