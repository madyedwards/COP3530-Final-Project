#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
using namespace std;

class HashTable {
public:
    struct Recipe {
        string name;
        string n_steps;
        string minutes;
        string steps;
        string ingredients;
        //counter for "relevancy" that is incremented via number of tags associated

        Recipe(string name, string n_steps, string minutes, string steps, string ingredients);

    };
    //map has key of strings for tags, and stores recipes within it that has steps, ingredients, etc.
    //right now its not a hashtable; can implement a hash function to make it that
    unordered_map<string, vector<Recipe>> recipeStorage;

    void InsertRecipe(string tag, Recipe currentRecipe);
    //int HashFunction(string tag);
    //print all recipes without filtering a map; uhhh super extreme, prob wont do this
    void PrintAll();
    //print all recipes within a certain tag; if we do a website, we can print it per every 20 values, like how
    //a page in a website works
    void PrintRecipe(string tag);

    // two sorting algos here to organize/print the recipes in the vectors of the tags associated
    // void sortingAlgo1
    // void sortingAlgo2

};
