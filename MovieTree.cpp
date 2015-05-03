#include <iostream>
#include "MovieTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <algorithm>


using namespace std;

//constructor
MovieTree::MovieTree()
{
    root = NULL;
    opCount = 1;
    Assignment6Output = json_object_new_object();
}
//dstor
MovieTree::~MovieTree()
{
    DeleteAll(root);

    // Clean up json object
    json_object_put(Assignment6Output);
}
/*Function Prototype: void MovieTree::DeleteAll(MovieNode * node);
  Function Description: Deletes all nodes in tree
  Example:
  MovieTree *mt;
  mt->DeleteAll(root);
  Precondition: Tree is built and this function us only used upon exiting the program


*/


/* Used to delete all nodes in the tree */
void MovieTree::DeleteAll(MovieNode * node)
{
    // clean to the left
    if (node->leftChild != NULL)
        DeleteAll(node->leftChild);
    // clean to the right
    if (node->rightChild != NULL)
        DeleteAll(node->rightChild);
    // delete this node
    delete node;

    return;
}

void MovieTree::initJson()
{
    Assignment6Output = json_object_new_object();
}


/*Function Prototype: void MovieTree::printMovieInventory();
  Function Description: Helper for the printMovieInventory recursive function, calls other print function, and handles additions to json object
  Example:
  MovieTree *mt;
  mt->printMovieInventory();
  Precondition: Tree is built*/
void MovieTree::printMovieInventory()
{
    // Create the json object for this operation
    json_object * newJSON = json_object_new_object();
    json_object * travLog = json_object_new_array();

    printMovieInventory(root,travLog);

    // Update our json object
    string stringNumber;
    stringstream convert;
    convert << opCount;
    stringNumber = convert.str();
    json_object *jsonOperation = json_object_new_string("traverse");
    json_object_object_add(newJSON,"operation",jsonOperation);
    json_object_object_add(newJSON,"output",travLog);
    json_object_object_add(Assignment6Output,stringNumber.c_str(),newJSON);

    opCount++;

    return;
}


/*Function Prototype: void MovieTree::printMovieInventory(MovieNode * node, json_object * traverseLog);
  Function Description:  Prints the inventory(in order traversal)
  Example: printMovieInventory(root,travLog);
  Precondition: Tree is built and is called from the helper function void MovieTree::printMovieInventory();
  */
void MovieTree::printMovieInventory(MovieNode * node, json_object * traverseLog)
{

    // Left Node
    if(node->leftChild!=NULL)
        printMovieInventory(node->leftChild,traverseLog);

    // Value
    cout<<"Movie: "<<node->title<< endl;

    // Update the traversal log
    json_object *curTitle = json_object_new_string(node->title.c_str());
    json_object_array_add(traverseLog, curTitle);

    // Right Node
    if(node->rightChild!=NULL)
        printMovieInventory(node->rightChild,traverseLog);

    return;
}


/*Function Prototype: void MovieTree::addMovieNode(int ranking, std::string title, int releaseYear, int quantity,std::string director,std::string genre, std::string rating);
  Function Description:  adds new nodes to the BST using the BST rules. Also adds to the json object
  Example:
  MovieTree *mt;
  mt->addMovieNode(atoi(ranking.c_str()),title,atoi(releaseYear.c_str()),atoi(quantity.c_str()),director,genre,rating);
  Precondition: Valid text file and correct types during function call. the atoi is so the string becomes an int.
  */
void MovieTree::addMovieNode(int ranking, std::string title, int releaseYear, int quantity,std::string director,std::string genre, std::string rating)
{
    //cout << "entered!\n";
    // Create the json object for this operation
    json_object * newJSON = json_object_new_object();
    // Create a log for the traversal
    json_object * travLog = json_object_new_array();

    // Create the node we will be inserting
    MovieNode * newMovie = new MovieNode(ranking,title,releaseYear,quantity,director,genre,rating);
    MovieNode * x = root;
    MovieNode * y = NULL;

    // Do we have an empty tree?
    if (root == NULL)
        root = newMovie;

    // If the tree is not empty
    else
    {

        // Get to the end of the tree, where we need to add this node.
        while (x != NULL)
        {
            // Add the current node to the traversal log before moving to next.
            json_object *curTitle = json_object_new_string(x->title.c_str());
            json_object_array_add(travLog, curTitle);

            y = x;
            if(newMovie->title.compare(x->title) < 0)
                x = x->leftChild;
            else
                x = x->rightChild;

        }

        // set the parent of this node to be the previous node.
        newMovie->parent = y;

        // Determine which child to this previous node we are at.
        if (newMovie->title.compare(y->title) < 0)
            y->leftChild = newMovie;
        else
            y->rightChild = newMovie;
    }

    // Update our json object
    string stringNumber;
    stringstream convert;
    convert << opCount;
    stringNumber = convert.str();
    json_object *jsonOperation = json_object_new_string("add");
    json_object_object_add(newJSON,"operation",jsonOperation);
    json_object *jsonTitle = json_object_new_string(title.c_str());
    json_object_object_add(newJSON,"parameter",jsonTitle);
    json_object_object_add(newJSON,"output",travLog);
    json_object_object_add(Assignment6Output,stringNumber.c_str(),newJSON);
    opCount++;

    return;

}


/*Function Prototype: void MovieTree::findMovie(std::string title);
  Function Description: searches for movie based on title else returns error message
  Example:
  MovieTree *mt;
  mt->findMovie("Shawshank Redemption")
  Precondition: Tree must be built
  */
void MovieTree::findMovie(std::string title)
{
    // Create a traversal log
    json_object * travLog = json_object_new_array();
    // Find the movie
    MovieNode * foundMovie = searchMovieTree(root,title,travLog);
    if (foundMovie != NULL)
    {
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << foundMovie->ranking << endl;
        cout << "Title:" << foundMovie->title << endl;
        cout << "Year:" << foundMovie->year << endl;
        cout << "Quantity:" << foundMovie->quantity << endl;
    }
    else
        cout << "Movie not found." << endl;

    return;
}
/*Function Prototype: MovieNode* MovieTree::searchMovieTree(MovieNode * node, std::string title, json_object * traverseLog);
  Function Description: searches tree for the rent movie function
  Example:
  MovieTree *mt;
  mt->searchMovieTree(root, title, travLog)
  Precondition: Tree must be built
  */
MovieNode* MovieTree::searchMovieTree(MovieNode * node, std::string title, json_object * traverseLog)
{
    // Add the current node to the traverse log
    if (node != NULL)
    {
        json_object *curTitle = json_object_new_string(node->title.c_str());
        json_object_array_add(traverseLog, curTitle);
    }

    // If the node is NULL, we just return. Failed to find node.
    if (node == NULL)
        return NULL;
    // Return this node if it is the one we are searching for
    else if (node->title == title)
        return node;

    // Else return the correct recursive call.
    else
    {
        if(title.compare(node->title) < 0)
            return searchMovieTree(node->leftChild,title,traverseLog);

        else
            return searchMovieTree(node->rightChild,title,traverseLog);
    }
}
/*Function Prototype: void MovieTree::rentMovie(std::string title);
  Function Description: rents a movie by searching for the movie and checking the quantity. If the quantity is greater than 0 then it decreases by 1, else it returns an error statement.
  It also adds to the json object.
  Example:
  MovieTree *mt;
  mt->rentMovie(title)
  Precondition: Tree must be built
  */
void MovieTree::rentMovie(std::string title)
{
    // Create the json object for this operation
    json_object * newJSON = json_object_new_object();

    int stockOutput = 0;

    json_object * travLog = json_object_new_array();
    MovieNode * foundMovie = searchMovieTree(root,title,travLog);

    // If the movie exists.
    if (foundMovie != NULL)
    {
        // If it's in stock.
        if (foundMovie->quantity > 0)
        {
            cout << "Movie has been rented." << endl;
            foundMovie->quantity--;
            stockOutput = foundMovie->quantity;

            // Update our json object
            string stringNumber;
            string stockOutputString;
            stringstream convert;
            convert << opCount;
            stringNumber = convert.str();
            convert << stockOutputString;
            stockOutputString = convert.str();
            json_object *jsonOperation = json_object_new_string("rent");
            json_object_object_add(newJSON,"operation",jsonOperation);
            json_object *jsonTitle = json_object_new_string(title.c_str());
            json_object_object_add(newJSON,"parameter",jsonTitle);
            json_object *jsonOutput = json_object_new_string(stockOutputString.c_str());
            json_object_object_add(newJSON,"output",jsonOutput);
            json_object_object_add(Assignment6Output,stringNumber.c_str(),newJSON);

            opCount++;

            //change this to print information
            cout << "Movie Info:" << endl;
            cout << "===========" << endl;
            cout << "Ranking:" << foundMovie->ranking << endl;
            cout << "Title:" << foundMovie->title << endl;
            cout << "Year:" << foundMovie->year << endl;
            cout << "Quantity:" << foundMovie->quantity << endl;
            // If the stock is 0 delete the movie
            if (foundMovie->quantity == 0)
                deleteMovieNode(foundMovie->title);

        }
        // If it's not in stock.
        else
            cout << "Movie out of stock." << endl;

    }
    // If it doesn't exist.
    else
        cout << "Movie not found." << endl;

}
/*Function Prototype: void MovieTree::deleteMovieNode(std::string title);
  Function Description: delete a movie from the tree. Checks the cases of no children, on child, and two children and adjusts accordingly so that all the correct and necessary pointers are overwritten.
  It also adds to the json object.
  Example:
  MovieTree *mt;
  mt->deleteMovieNode(title);
  Precondition: Tree must be built
  */
void MovieTree::deleteMovieNode(std::string title)
{

    // Create the json object for this operation
    json_object * newJSON = json_object_new_object();

    json_object * travLog = json_object_new_array();
    MovieNode * foundMovie = searchMovieTree(root,title,travLog);

    // If the movie exists
    if (foundMovie != NULL)
    {
        // If it has no children
        if (foundMovie->leftChild == NULL && foundMovie->rightChild == NULL)
        {
            // If this node is the left child, set the parents left child to NULL
            if (foundMovie->parent->leftChild == foundMovie)
                foundMovie->parent->leftChild = NULL;
            // Else, this node is the right child, set that to NULL
            else
                foundMovie->parent->rightChild = NULL;
            // Delete the node
            delete foundMovie;

        }
        // If it only has a left child
        else if (foundMovie->rightChild == NULL)
        {
            if (foundMovie->parent->leftChild == foundMovie)
                foundMovie->parent->leftChild = foundMovie->leftChild;
            else
                 foundMovie->parent->rightChild = foundMovie->leftChild;

            delete foundMovie;

        }
        // If it only has a right child
        else if (foundMovie->leftChild == NULL)
        {
            if (foundMovie->parent->leftChild == foundMovie)
                foundMovie->parent->leftChild = foundMovie->rightChild;
            else
                 foundMovie->parent->rightChild = foundMovie->rightChild;

            delete foundMovie;
        }

        // Node has two children, we need the smallest node from the right child
        else
        {
            // Start on the right sub-tree
            MovieNode * replacementNode = foundMovie->rightChild;

            // search for the smallest left child
            while (replacementNode->leftChild != NULL)
            {
                replacementNode = replacementNode->leftChild;
            }

            // Swap in all the info from the replacement to this node we are "deleting"
            foundMovie->title = replacementNode->title;
            foundMovie->quantity = replacementNode->quantity;
            foundMovie->ranking = replacementNode->ranking;
            foundMovie->year = replacementNode->year;
            foundMovie->director = replacementNode->director;
            foundMovie->genre = replacementNode->genre;
            foundMovie->rating = replacementNode->rating;


            // If the replacement node has a right child, update the parent
            if (replacementNode->rightChild != NULL)
                replacementNode->rightChild->parent = replacementNode->parent;

            // If the replacement node is a left child
            if (replacementNode->parent->leftChild == replacementNode)
                replacementNode->parent->leftChild = replacementNode->rightChild;
            // If it is a right child
            else
                replacementNode->parent->rightChild = replacementNode->rightChild;

            // Delete the node
            delete replacementNode;
        }

        // Update our json object
        string stringNumber;
        stringstream convert;
        convert << opCount;
        stringNumber = convert.str();
        json_object *jsonOperation = json_object_new_string("delete");
        json_object_object_add(newJSON,"operation",jsonOperation);
        json_object *jsonTitle = json_object_new_string(title.c_str());
        json_object_object_add(newJSON,"parameter",jsonTitle);
        json_object_object_add(newJSON,"output",travLog);
        json_object_object_add(Assignment6Output,stringNumber.c_str(),newJSON);
        opCount++;

    }
    // If it doesn't exist
    else
        cout << "Movie not found." << endl;



}

/*Function Prototype: vint MovieTree::countMovieNodes();;
  Function Description: helper function to the function that counts the number of movie nodes in the tree.
  It also adds to the json object.
  Example:
  MovieTree *mt;
  mt->countMovieNodes();
  Precondition: Tree must be built
  */
int MovieTree::countMovieNodes()
{
    // Create the json object for this operation
    json_object * newJSON = json_object_new_object();

    // Determine the count
    int count = countMovieNodes(root);

    // Update our json object
    string stringNumber;
    string stringCount;
    stringstream convert;
    convert << opCount;
    stringNumber = convert.str();
    convert << stringCount;
    stringCount = convert.str();
    json_object *jsonOperation = json_object_new_string("count");
    json_object_object_add(newJSON,"operation",jsonOperation);
    json_object *jsonOutput = json_object_new_string(stringCount.c_str());
    json_object_object_add(newJSON,"output",jsonOutput);
    json_object_object_add(Assignment6Output,stringNumber.c_str(),newJSON);
    opCount++;

    return count;
}

/*Function Prototype: int MovieTree::countMovieNodes(MovieNode *node);;
  Function Description: function that counts the number of movie nodes in the tree.
  It also adds to the json object.
  Example:
  MovieTree *mt;
  mt->countMovieNodes(root);
  Precondition: Tree must be built
  */
int MovieTree::countMovieNodes(MovieNode *node)
{
    if (node == NULL)
        return 0;
    return countMovieNodes(node->leftChild) + countMovieNodes(node->rightChild) + 1;
}

//gets json onject for printing
json_object* MovieTree::getJsonObject()
{
    return Assignment6Output;
}
/*Function Prototype: ivoid MovieTree::printAllInfo(MovieNode * node, json_object * traverseLog);
  Function Description: function prints all info about each movie in the tree
  It also adds to the json object.
  Example:
  MovieTree *mt;
  mt->printAllInfo(root, travlog)
  Precondition: Tree must be built
  */
void MovieTree::printAllInfo(MovieNode * node, json_object * traverseLog){
     if(node->leftChild!=NULL)
        printAllInfo(node->leftChild,traverseLog);

    // Value
    cout<<"Movie: "<<node->title<< endl;
    cout<<"Title: "<<node->year<<endl;
    cout<<"Director: "<<node->director<<endl;
    cout<<"Genre: "<<node->genre<<endl;
    cout<<"Rating: "<<node->rating<<endl;
    cout<<"Quantity: "<<node->quantity<<endl;
    // Update the traversal log
    json_object *curTitle = json_object_new_string(node->title.c_str());
    json_object_array_add(traverseLog, curTitle);

    // Right Node
    if(node->rightChild!=NULL)
        printAllInfo(node->rightChild,traverseLog);

    return;
}
/*Function Prototype: ivoid MovieTree::printAllInfo();
  Function Description: helper function that prints all info about each movie in the tree
  It also adds to the json object.
  Example:
  MovieTree *mt;
  mt->printAllInfo()
  Precondition: Tree must be built
  */
void MovieTree::printAllInfo()
{
    // Create the json object for this operation
    json_object * newJSON = json_object_new_object();
    json_object * travLog = json_object_new_array();

    printAllInfo(root,travLog);

    // Update our json object
    string stringNumber;
    stringstream convert;
    convert << opCount;
    stringNumber = convert.str();
    json_object *jsonOperation = json_object_new_string("traverse all info");
    json_object_object_add(newJSON,"operation",jsonOperation);
    json_object_object_add(newJSON,"output",travLog);
    json_object_object_add(Assignment6Output,stringNumber.c_str(),newJSON);

    opCount++;

    return;
}
/*Function Prototype: void MovieTree::printByGenre();
  Function Description: helper function that adds to the json object and calls for the function that adds the movies to a
  vector.
  Example: .
  MovieTree *mt;
  mt->printByGenre()
  Precondition: Tree must be built
  */
void MovieTree::printByGenre(){
    json_object * newJSON = json_object_new_object();
    json_object * travLog = json_object_new_array();

    printByGenre(root,travLog);

    // Update our json object
    string stringNumber;
    stringstream convert;
    convert << opCount;
    stringNumber = convert.str();
    json_object *jsonOperation = json_object_new_string("traverse genre");
    json_object_object_add(newJSON,"operation",jsonOperation);
    json_object_object_add(newJSON,"output",travLog);
    json_object_object_add(Assignment6Output,stringNumber.c_str(),newJSON);

    opCount++;

    return;
}
/*Function Prototype: void MovieTree::printByGenre()(MovieNode * node, json_object * traverseLog);
  Function Description: function that adds to a vector for printing
  It also adds to the json object.
  Example:
  printByGenre(root, travlog);
  Precondition: Tree must be built
  */
void MovieTree::printByGenre(MovieNode * node, json_object * traverseLog){
    if(node->leftChild!=NULL){
        printByGenre(node->leftChild,traverseLog);
    }

    genrePrint.push_back(node);

    // Update the traversal log
    json_object *curTitle = json_object_new_string(node->title.c_str());
    json_object_array_add(traverseLog, curTitle);

    // Right Node
    if(node->rightChild!=NULL){
        printByGenre(node->rightChild,traverseLog);
    }
    return;
}
/*Function Prototype: void MovieTree::vectorPrintGenre(std::string in_genre);
  Function Description: function that prints out movies of given genre
  Example:
  MovieTree *mt;
  mt->vectorPrintGenre;
  Precondition: Tree must be built
  */
void MovieTree::vectorPrintGenre(std::string in_genre){

    for(unsigned int i = 0; i<genrePrint.size();i++){
        if(genrePrint[i]->genre == in_genre){
            cout<<genrePrint[i]->title<<endl;
            return;//if match is found function returns before print statement
        }
    }
    cout<<"No movies in list with type "<<in_genre<<" genre"<<endl;//if no match is found function returns to menu after print statement
    genrePrint.clear();
    return;
}
/*Function Prototype: void MovieTree::printByRating();
  Function Description: helper function that adds to the json object and calls for the function that adds the movies to a
  vector.
  Example: .
  MovieTree *mt;
  mt->printByRating()
  Precondition: Tree must be built
  */
void MovieTree::printByRating(){
    json_object * newJSON = json_object_new_object();
    json_object * travLog = json_object_new_array();

    printByRating(root,travLog);

    // Update our json object
    string stringNumber;
    stringstream convert;
    convert << opCount;
    stringNumber = convert.str();
    json_object *jsonOperation = json_object_new_string("traverse rating");
    json_object_object_add(newJSON,"operation",jsonOperation);
    json_object_object_add(newJSON,"output",travLog);
    json_object_object_add(Assignment6Output,stringNumber.c_str(),newJSON);

    opCount++;

    return;
}
/*Function Prototype: void MovieTree::printByrating(MovieNode * node, json_object * traverseLog);
  Function Description: helper function that adds to the json object and calls for the function that adds the movies to a
  vector.
  Example: .
  printByRating(root,travlog);
  Precondition: Tree must be built
  */
void MovieTree::printByRating(MovieNode * node, json_object * traverseLog){

    if(node->leftChild!=NULL){
        printByRating(node->leftChild,traverseLog);
    }

    ratingPrint.push_back(node);

    // Update the traversal log
    json_object *curTitle = json_object_new_string(node->title.c_str());
    json_object_array_add(traverseLog, curTitle);

    // Right Node
    if(node->rightChild!=NULL){
        printByRating(node->rightChild,traverseLog);
    }
    return;
}
/*Function Prototype: void MovieTree::vectorPrintRating(std::string in_genre);
  Function Description: function that prints out movies of given MPAA rating.
  Example:
  MovieTree *mt;
  mt->vectorPrintRating(rating);
  Precondition: Tree must be built
  */
void MovieTree::vectorPrintRating(std::string in_rating){

    for(unsigned int i = 0; i<ratingPrint.size();i++)
    {
        if(ratingPrint[i]->rating == in_rating)
        {
            cout<<"Title: "<<ratingPrint[i]->title<<endl;
            cout<<"Year: "<<ratingPrint[i]->year<<endl;
            cout<<"Director: "<<ratingPrint[i]->director<<endl;
            cout<<"Genre: "<<ratingPrint[i]->genre<<endl;
            cout<<"Rating: "<<ratingPrint[i]->rating<<endl; 
            return;//function returns if match is found, before print statement
		}
   }
   cout<<"No movies in list with rating "<<in_rating<<endl;//if no match is found function returns to menu after this print statement
   ratingPrint.clear();
   return;
}
/*Function Prototype: void MovieTree::printBydirector();
  Function Description: helper function that adds to the json object and calls for the function that adds the movies to a
  vector.
  Example: .
  MovieTree *mt;
  mt->printByDirector()
  Precondition: Tree must be built
  */
void MovieTree::printByDirector(){
    json_object * newJSON = json_object_new_object();
    json_object * travLog = json_object_new_array();

    printByDirector(root,travLog);

    // Update our json object
    string stringNumber;
    stringstream convert;
    convert << opCount;
    stringNumber = convert.str();
    json_object *jsonOperation = json_object_new_string("traverse director");
    json_object_object_add(newJSON,"operation",jsonOperation);
    json_object_object_add(newJSON,"output",travLog);
    json_object_object_add(Assignment6Output,stringNumber.c_str(),newJSON);

    opCount++;

    return;
}
/*Function Prototype: void MovieTree::printBydirector(MovieNode * node, json_object * traverseLog);
  Function Description: helper function that adds to the json object and calls for the function that adds the movies to a
  vector.
  Example: .
  printByDirector(root,travlog)
  Precondition: Tree must be built
  */
void MovieTree::printByDirector(MovieNode * node, json_object * traverseLog){

    if(node->leftChild!=NULL){
        printByDirector(node->leftChild,traverseLog);
    }

    DirectorPrint.push_back(node);

    // Update the traversal log
    json_object *curTitle = json_object_new_string(node->title.c_str());
    json_object_array_add(traverseLog, curTitle);

    // Right Node
    if(node->rightChild!=NULL){
        printByDirector(node->rightChild,traverseLog);
    }
    return;
}
/*Function Prototype: void MovieTree::vectorPrintDirector(std::string in_Director);
  Function Description: function that prints out movies of given director
  Example:
  MovieTree *mt;
  mt->vectorPrintDirector(director);
  Precondition: Tree must be built
  */
void MovieTree::vectorPrintDirector(std::string in_Director){

    for(unsigned int i = 0; i<DirectorPrint.size();i++){
        if(DirectorPrint[i]->director == in_Director){
            cout<<"Title: "<<DirectorPrint[i]->title<<endl;
            cout<<"Year: "<<DirectorPrint[i]->year<<endl;
            cout<<"Director: "<<DirectorPrint[i]->director<<endl;
            cout<<"Genre: "<<DirectorPrint[i]->genre<<endl;
            cout<<"Rating: "<<DirectorPrint[i]->rating<<endl;
            return;//if director found function returns

        }
    }
	cout<<"Director not found"<<endl;//if director not found function returns after printing this
	return;
}
/*Function Prototype: void MovieTree::randomMovie();
  Function Description: helper function that adds to the json object and calls for the function that adds the movies to a
  vector.
  Example: .
  MovieTree *mt;
  mt->randomMovie()
  Precondition: Tree must be built
  */
void MovieTree::randomMovie(){
    json_object * newJSON = json_object_new_object();
    json_object * travLog = json_object_new_array();

    randomMovie(root,travLog);

    // Update our json object
    string stringNumber;
    stringstream convert;
    convert << opCount;
    stringNumber = convert.str();
    json_object *jsonOperation = json_object_new_string("traverse");
    json_object_object_add(newJSON,"operation",jsonOperation);
    json_object_object_add(newJSON,"output",travLog);
    json_object_object_add(Assignment6Output,stringNumber.c_str(),newJSON);

    opCount++;

    return;
}
/*Function Prototype: MovieTree::randomMovie(MovieNode * node, json_object * traverseLog);
  Function Description: function that adds to the json object and calls for the function that adds the movies to a
  vector.
  Example: .
  randomMovie(root,travlog)
  Precondition: Tree must be built
  */
void MovieTree::randomMovie(MovieNode * node, json_object * traverseLog){

    if(node->leftChild!=NULL){
        randomMovie(node->leftChild,traverseLog);
    }

    random.push_back(node);

    // Update the traversal log
    json_object *curTitle = json_object_new_string(node->title.c_str());
    json_object_array_add(traverseLog, curTitle);

    // Right Node
    if(node->rightChild!=NULL){
        randomMovie(node->rightChild,traverseLog);
    }
    return;
}
/*Function Prototype: MovieTree::randomMoviePrint();
  Function Description: function that prints out the random movie by generating a random integer and % it by the vector size.
  This will assure that the int will always be in the bounds of the vector.
  Example:
  MovieTree *mt
  mt->randomMoviePrint()
  Precondition: Tree must be built
  */
void MovieTree::randomMoviePrint(){
    int i = rand() % random.size();
    cout<<"Title: "<<random[i]->title<<endl;
    cout<<"Year: "<<random[i]->year<<endl;
    cout<<"Director: "<<random[i]->director<<endl;
    cout<<"Genre: "<<random[i]->genre<<endl;
    cout<<"Rating: "<<random[i]->rating<<endl;
    random.clear();
}
