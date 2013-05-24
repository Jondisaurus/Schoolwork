// ----------------------------------------------------------------------------
//    CSS342 Lab 1  - Fall 2011 - Dr. Carol Zander
//
// AUTHOR: Jonathan Difrancesco
// PURPOSE: To sort a list of name and grades using an insertion sort then neatly
//          displaying the data along with a histogram and average of the grade data.
//
// ASSUMPTIONS : 
//               --All data is formatted in the text file correctly
//               --The names do not exceed MAXLENGTH
//               --There are no more than 100 names in the file
//               --all grades are greater than 0 and listed as integers
//
//------------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int const MAXSIZE = 100;	    // maximum number of records in total
int const MAXLENGTH = 31;	    // maximum string length 
int const MAXGRADE = 100;           // highest possible grade
int const LOWGRADE = 0;             // lowest possible grade
int const HISTOGRAMSIZE = (MAXGRADE-LOWGRADE)/10 + 1;     // grouped in tens

struct StudentType  {		    // information of one student
	int grade;		    // the grade of the person
	char last[MAXLENGTH];	    // last name (MAXLENGTH-1 at most)
	char first[MAXLENGTH];	    // first name (MAXLENGTH-1 at most)
};

// Function Prototypes

bool sortInput(ifstream&, StudentType [], int&);
void swapStudent(StudentType&, StudentType&);
void displayList(StudentType [], int);
void setHistogram(StudentType [], int [], int);
void displayHistogram(int []);
int findAverage(StudentType[], int);

//------------------------------- main ----------------------------------------
int main()  {
   StudentType students[MAXSIZE];   // list of max of MAXSIZE number of students
   int size = 0;                    // total number of students
   int histogram[HISTOGRAMSIZE] = { 0 };    // grades grouped in tens
   int average = 0;                 // average exam score, truncated

   // creates file object and opens the data file
   ifstream infile("data1.txt");
   if (!infile)  { 
      cout << "File could not be opened." << endl; 
      return 1;  
   }

   // read and sort input by last then first name
   bool successfulRead = sortInput(infile, students, size);              

   // display list, histogram, and class average 
   if (successfulRead)  {
      displayList(students, size);
      setHistogram(students, histogram, size);
      displayHistogram(histogram);
      average = findAverage(students, size);
      cout << "Average grade: " << average << endl << endl;
   }
   system("pause");
   return 0;
};

// ----------------------------------------------------------------------------
// Functions go here.

//------------------------------------------------------------------------------//
// FUNCTION NAME: sortInput
// RETURN TYPE: bool
// PARAMETERS: referanced ifstream, StudentType array, referanced int
// PURPOSE: This function takes data from a file stream object, outputs the data
//          into an array of StudentType arrays, sorts the data by last/first name,
//          and outputs the sorted array and an int containing the number of names. 
bool sortInput(ifstream& infile, StudentType students[], int& size)
{
	 int i = 0;
	 StudentType tempsort;
	 
     //load data into students
     for(;;)
     {
		 
         infile >> students[i].last >> students[i].first >> students[i].grade;

		 if(infile.eof()) break;

		 size++;
		 i++; 

     }
   
	 //Insertion sort students array
	 for(int j = size - 1; j >= 0; j--)
	 {	 	
	     tempsort = students[j];

		 for(i = size - 1; i >= 0; i--)
		 { 
			 if(strcmp(tempsort.last, students[i].last) > 0)
			 {
				 swapStudent(students[i], tempsort);
			 }
			 else if(strcmp(tempsort.last, students[i].last) == 0 && strcmp(tempsort.first, students[i].first) > 0)
			 {
				 swapStudent(students[i], tempsort);
			 } 			 
		 } 
		 students[j] = tempsort;
	 }
	 return 1;
};

//------------------------------------------------------------------------------//
// FUNCTION NAME: swapStudent
// RETURN TYPE: void
// PARAMETERS: 2 StudentType arrays
// PURPOSE: This function swaps the values between the two inputted arrays. 
void swapStudent(StudentType& swap1, StudentType& swap2)
{
	StudentType swapHolder;

	//Copy swap2 to placeholder
	strcpy(swapHolder.first, swap2.first);
	strcpy(swapHolder.last, swap2.last);
	swapHolder.grade = swap2.grade;

	//copy swap1 to swap2
	strcpy(swap2.first, swap1.first);
	strcpy(swap2.last, swap1.last);
	swap2.grade = swap1.grade;

	//copy placeholder to swap 1
	strcpy(swap1.first, swapHolder.first);
	strcpy(swap1.last, swapHolder.last);
	swap1.grade = swapHolder.grade;
}

//------------------------------------------------------------------------------//
// FUNCTION NAME: displayList
// RETURN TYPE: void
// PARAMETERS: StudentType array, int
// PURPOSE: This formats and displays the info stored in the StudentType array
void displayList(StudentType students[], int size)
{
	cout << "List of names Sorted: " << endl;

	for(int i = 0; i < size; i++)
	{
		cout << setw(4) << left << students[i].grade << setw(8) << left 
			 << students[i].last << setw(10) << left << students[i].first << endl; 
	}

	cout << endl; 
}

//------------------------------------------------------------------------------//
// FUNCTION NAME: setHistogram
// RETURN TYPE: void
// PARAMETERS: StudentType array, int array, int
// PURPOSE: This builds a histogram from the Data in the StudentType array and 
//          places it in the int array. 
void setHistogram(StudentType students[], int histogram[], int size)
{
	//adds one number per range of grades into the histogram array
	for(int i = 0; i < size; i++)
	{
		if(students[i].grade < 10)
		{
			histogram[0]++;
		}

		else if(students[i].grade < 20)
		{
			histogram[1]++;
		}

		else if(students[i].grade < 30)
		{
			histogram[2]++;
		}

		else if(students[i].grade < 40)
		{
			histogram[3]++;
		}

		else if(students[i].grade < 50)
		{
			histogram[4]++;
		}

		else if(students[i].grade < 60)
		{
			histogram[5]++;
		}

		else if(students[i].grade < 70)
		{
			histogram[6]++;
		}

		else if(students[i].grade < 80)
		{
			histogram[7]++;
		}

		else if(students[i].grade < 90)
		{
			histogram[8]++;
		}

		else if(students[i].grade < 100)
		{
			histogram[9]++;
		}

		else if(students[i].grade >= 100)
		{
			histogram[10]++;
		}
	}
}

//------------------------------------------------------------------------------//
// FUNCTION NAME: displayHistogram
// RETURN TYPE: void
// PARAMETERS: int array
// PURPOSE: This formats and outputs the information passed in the int array
void displayHistogram(int histogram[])
{
	int disp = 0,
		temp = 0;

	cout << "Histogram of Grades:" << endl;

	for(int i = 0; i <= 10 ; i++)
	{
		temp = histogram[i];
		cout << setw(3) << right << disp << "-->" << setw(4); 
		
		//this makes sure the second set of grade numbers doesnt go over 100
		if(disp < 100)	
		{
           cout << disp + 9 << ": ";
		}
		else
		{
		   cout << 100 << ": ";
		}
			
		//this outputs '*' characters for each number stored in the int array	
		while(temp != 0)
		{
			cout << right << '*';
			temp--;
		}
		cout << endl;
		disp += 10; 	
	}
}

//------------------------------------------------------------------------------//
// FUNCTION NAME: findAverage
// RETURN TYPE: int
// PARAMETERS: StudentType array, int
// PURPOSE: This takes data from the StudentType array and returns an average 
//          grade taken from the StudentType.grade member
int findAverage(StudentType students[], int size)
{
	float average = 0;

	//add all the grade members together
	for(int i = 0; i < size; i++)
	{
		if(students[i].grade >= 0)
		{
			average += students[i].grade;
		}
	}

    //.5 is added to the average to properly round the number to the nearest int. 
	return ((average / size) + 0.5);
}
