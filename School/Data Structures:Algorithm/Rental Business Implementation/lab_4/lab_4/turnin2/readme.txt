 1. Describe the state of your program, exactly what works and what does not work. 
	-The majority of my program functions, with some of the output still needing to be formatted that will be done in time.
	-There is also an issue with memory leaks that I was unable to resolve. 
	-As far as what does work, it processes all the commands, it creates and edits all the lists, with more time
	-I would of liked to have had less or no switch statements and relied completly on inheritence but was unable to 
	get that aspect of the program finished.


 2. Describe your hash table(s): what they are used for and file found in. (Include any hash factories.) 
	-My hash table was used to store customer data and allowed for fast customer lookup. I built my hash table as an 
	 openchaining hash that used a multiplicated factor to find the key. The reason I went with a list is it seemed
	 to use less operations that would happen if I had to lookup using linar or quadratic hashing. 

 3. Describe anything you are particularly proud of ... 
	-I am particularly proud of the limited amount of inheritence my program has. This was a difficult subject for me to learn
	 and the amount I have in there is good that I was able to grab it. 

 4. Describe which file and which function you read the movie data, high level function call, 
      i.e., how/where it gets into your movie collections. 
	Mediastore - > initialize generates the movie data and
	MediaBase(derivitive) - > buildList parses the data and builds the list

 5. Describe which file and which function you read the command data, high level function call, 
      i.e., how/where you perform the commands/transactions.
	Manager - > run reads the commands and delegates their output.  