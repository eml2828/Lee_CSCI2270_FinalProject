# Lee_CSCI2270_FinalProject

#Project Summary
  This program will put movie info into a BST and vectors. The program will allow for searching(i.e renting) of movies and the ability to see all the info of avaiable movies. It filters via director, rating(MPAA), and genre. It will also allow for a random movie to be picked in the situation that you don;t know what you want to watch. The program also writes to an output file using JSON. THe program takes in a text file with movie data. Each data field must be separated by a comma. Upon exit the program will write to an output file.
  
#How to Run
Use the provided Test.txt. Information should be formatted as follows:
ranking,title,year,quantity,director,genre,rating
Each line of the text file must be formatted as above. Then after compiling, all you do is simply run the program and follow the instructions. 

#Dependencies
The JSON library. Use the command in the terminal
sudo apt-get install libjson0 libjson0-dev
Then make sure to include the json library using 
#include <json/json.h>
Finally, make sure that the linker setting have json added to them.
Also make sure that the compiler is using the C++11 flags under build options in codeblocks or whatever the equivalent is in the coding environment you are using.

#System	Requirements
Currently this has only been tested on the CSCI VM (linux), so compatibility is not assured with any other platform. However as long as the compiler shows no problems, the program should work.

#Group Members
Edmond Lee(owner)

#Contributors
Professor Hoenigman( provided base code that this is based off of)

#Open Issues/Bugs
Need conditionals for certain cases. THe code needs to check if a movie has already been added to a vector. Also I would like someone to add an actor/actress field to the struct and add the accompanying changes to the code. These would be changes in adding the node and new functions to add to the JSON object and printing out said movies.



