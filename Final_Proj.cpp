#include <iostream>
#include "MovieTree.h"
//#include "MovieTree.cpp"
#include <fstream>  //allows istream/ostream
#include <string>
#include <json/json.h>
#include <stdlib.h>
#include <vector>

using namespace std;

struct Movie{
    string ranking;
    string title;
    string quantity;
    string releaseYear;
    Movie(){};

    Movie(string in_ranking, string in_title, string in_year, string in_quantity)
    {
        ranking = in_ranking;
        title = in_title;
        releaseYear = in_year;
        quantity = in_quantity;
    }
};

void displayMenu();
int getFileSize(char * fileName);
void readFileIntoTree(MovieTree * mt, char * fileName);

int main()
{
    int input;
    // Determine the size of the text file.
    //int fileSize = getFileSize(argv[1]);
    //cout << "about to create object\n";
    // Create a new communication network
    MovieTree *mt = new MovieTree();

    // Read each line and add it to tree
    readFileIntoTree(mt, "Test.txt");

    // Flag used for exiting menu
    bool quit = false;

    // Used for input
    string title;
    string genre;
    string rating;
    string director;
    while(quit != true)
    {
        displayMenu();
        cin >> input;

        //clear out cin
        cin.clear();
        cin.ignore(10000,'\n');

        switch (input)
        {
            // Find a movie
            /*
            case 1:
                cout << "Enter title:" << endl;
                getline(cin,title);
                mt->findMovie(title);
                break;
            */
            // Rent a movie
            case 1:
                cout << "Enter title:" << endl;
                getline(cin,title);
                mt->rentMovie(title);
                break;
            // Print the inventory
            case 2:
                mt->printMovieInventory();
                break;

            // Delete Node
            case 3:
                cout << "Enter title: " << endl;
                getline(cin,title);
                mt->deleteMovieNode(title);
                break;
            // Count Tree
            case 4:
                cout << "Tree contains: " << mt->countMovieNodes() << " nodes." << endl;
                break;
            case 5:
                mt->printAllInfo();
                break;
            case 6:
                cout << "Enter genre: "<<endl;
                getline(cin,genre);
                mt->printByGenre();
                mt->vectorPrintGenre(genre);
                break;
            case 7:
                cout<<"Enter Rating: "<<endl;
                getline(cin,rating);
                mt->printByRating();
                mt->vectorPrintRating(rating);
                break;
            case 8:
                cout<<"Enter Director: "<<endl;
                getline(cin,director);
                mt->printByDirector();
                mt->vectorPrintDirector(director);
                break;
            case 9:
                mt->randomMovie();
                mt->randomMoviePrint();
                break;
            case 10:
                cout << "Goodbye!" << endl;
                quit = true;
                break;
            // invalid input
            default:
                cout << "Invalid Input" << endl;
                cin.clear();
                cin.ignore(10000,'\n');
                break;
        }
    }

    // Write our JSON object to a file
    ofstream myfile;
    myfile.open("Sample_Output.txt");
    myfile << json_object_to_json_string_ext(mt->getJsonObject(), JSON_C_TO_STRING_PRETTY);
    myfile.close();


    // Free memory and return
    delete mt;

    return 0;
}

/*displays a menu with options to enqueue and dequeue a message and transmit the entire message and quit*/
void displayMenu()
{
    cout << "======Main Menu=====" << endl;
    //cout << "1. Find a movie" << endl;
    cout << "1. Rent a movie" << endl;
    cout << "2. Print the inventory" << endl;
    cout << "3. Delete a movie" << endl;
    cout << "4. Count the movies" << endl;
    cout << "5. Print All Info" << endl;
    cout << "6. Print by Genre" << endl;
    cout << "7. Print by Rating" << endl;
    cout << "8. Print by Director" << endl;
    cout << "9. Random Movie" << endl;
    cout << "10. Quit" << endl;
    return;
}

/*grabs the number of words in a file */
int getFileSize(char * fileName)
{
    ifstream in_stream;
    in_stream.open(fileName);
    int count = 0;
    string word;

    while (!in_stream.eof())
    {
        getline(in_stream,word);
        count++;
    }

    in_stream.close();

    return count;
}

/* reads file into tree */
void readFileIntoTree(MovieTree * mt, char * fileName)
{
    ifstream in_stream;
    cout << fileName << endl;
    in_stream.open(fileName);
    if (!in_stream)
    {
        cout << "Could not open file\n";
        return;
    }
    string ranking;
    string title;
    string releaseYear;
    string quantity;
    string director;
    string genre;
    string rating;

    while (!in_stream.eof())
    {
        title ="";
        getline(in_stream, ranking, ',');
        getline(in_stream, title, ',');
        getline(in_stream, releaseYear, ',');
        getline(in_stream, quantity,','); // "\n" is the default delimiter
        getline(in_stream, director,',');
        getline(in_stream, genre,',');
        getline(in_stream, rating);
        if (title != "")
        {
            //cout << "Adding: " << title << endl;
            mt->addMovieNode(atoi(ranking.c_str()),title,atoi(releaseYear.c_str()),atoi(quantity.c_str()),director,genre,rating);
        }
    }
}

