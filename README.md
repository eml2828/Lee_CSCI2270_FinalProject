# Lee_CSCI2270_FinalProject

#Project Summary
  This program will put movie info into a BST and vectors. The program will allow for searching(i.e renting) of movies and the ability to see all the info of avaiable movies. It filters via director, rating(MPAA), and genre. It will also allow for a random movie to be picked in the situation that you don;t know what you want to watch. The program also writes to an output file using JSON. THe program takes in a text file with movie data. Each data field must be separated by a comma. Upon exit the program will write to an output file.
  
#How to Run
All directions will be given assuming the user is using Codeblocks and a Debian based OS (i.e Debian,Ubuntu, and Mint). For ease of following these instructions please use the CSCI VM and Codeblocks.
First create a project in Codeblocks and add the source files to the project. Make sure all dependencies listed below are resolved and then click the compile button. I have ommitted the command line arguments for sake of simplicity for both the user and I as we are working on it.Then use the provided Test.txt as the input. Information on each line should be formatted as follows:
ranking,title,year,quantity,director,genre,rating
Check that the text files follows the given format. Then after compiling, all you do is simply run the program and follow the menu and instructions. The program takes in no command line arguments.

#Dependencies
The JSON library must first be installed. Use the command in the terminal
sudo apt-get install libjson0 libjson0-dev
Once JSON is installed, make sure that the linker setting in Codeblocks has json added. To do this right click on your project and click build option. Then from there click linker settings. On the linker setting page click add and enter json. Also make sure that the compiler is using the C++11 flags under build options in codeblocks. For other coding environments please do the equivalent in them.

#System	Requirements
Currently this has only been tested on the CSCI VM (linux), so compatibility is not assured with any other platform. However as long as the compiler shows no problems, the program should work.

#Group Members
Edmond Lee(owner)

#Contributors
Professor Hoenigman( provided base code that this is based off of)

#Open Issues/Bugs
Need conditionals for certain cases. The code needs to check if an input is valid in the case of menu options 6-9. Also I would like someone to add an actor/actress, number of awards, metacritic score or whatever information you can think of that would be pertinent pertinent in picking a movie to rent.If you do add another data field then please also add the accompanying functions to cout and add to the json object. Also any speedups to the code are also welcome.



