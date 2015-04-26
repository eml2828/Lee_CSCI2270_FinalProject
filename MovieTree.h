#ifndef MOVIETREE_H
#define MOVIETREE_H

#include <json/json.h>
#include <vector>

struct MovieNode{
    int ranking;
    std::string title;
    std::string director;
    std::string genre;
    std::string rating;
    int year;
    int quantity;
    MovieNode *parent;
    MovieNode *leftChild;
    MovieNode *rightChild;

    MovieNode(){};

    MovieNode(int in_ranking, std::string in_title, int in_year, int in_quantity,std::string in_director,std::string in_genre, std::string in_rating)
    {
        ranking = in_ranking;
        title = in_title;
        year = in_year;
        director = in_director;
        genre = in_genre;
        rating = in_rating;
        quantity = in_quantity;
        leftChild = NULL;
        rightChild = NULL;
    }

};

class MovieTree
{
        int opCount;

    public:
        MovieTree();
        virtual ~MovieTree();
        void printMovieInventory();
        int countMovieNodes();
        void deleteMovieNode(std::string title);
        void addMovieNode(int ranking, std::string title, int releaseYear, int quantity,std::string director,std::string genre, std::string rating);
        void findMovie(std::string title);
        void rentMovie(std::string title);
        void initJson();
        //use this to return the json object from the class when you are ready to write it to a file
        json_object* getJsonObject();
        void printAllInfo();
        void printByGenre();
        void printByRating();
        void printByDirector();
        void vectorPrintGenre(std::string genre);
        void vectorPrintRating(std::string rating);
        void vectorPrintDirector(std::string director);
        void randomMovie();
        void randomMoviePrint();



    protected:

    private:
        void DeleteAll(MovieNode * node); //use this for the post-order traversal deletion of the tree
        void printMovieInventory(MovieNode * node, json_object * traverseLog);
        void printAllInfo(MovieNode * node, json_object * traverseLog);
        void printByGenre(MovieNode * node, json_object * traverseLog);
        void printByRating(MovieNode * node, json_object * traverseLog);
        void printByDirector(MovieNode * node, json_object * traverseLog);
        void randomMovie(MovieNode * node, json_object * traverseLog);
        int countMovieNodes(MovieNode *node);
        MovieNode* searchMovieTree(MovieNode * node, std::string title, json_object * traverseLog);
        MovieNode *root;
        // Count of how many operations we have done.
        //including the json_object in the class makes it global within the class, much easier to work with
        json_object * Assignment6Output;
        std::vector<MovieNode*> genrePrint;
        std::vector<MovieNode*> ratingPrint;
        std::vector<MovieNode*>DirectorPrint;
        std::vector<MovieNode*>random;




};

#endif // MOVIETREE_H
