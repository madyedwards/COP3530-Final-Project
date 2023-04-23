#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class HashTable {
public:
    struct Recipe {
        Recipe();

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
    void PrintResult(vector<Recipe> &arr);
    //print all recipes within a certain tag; if we do a website, we can print it per every 20 values, like how
    //a page in a website works
    void PrintRecipe(string tag);
    //check if tag exists in the map
    void CheckTag(string tag);
    void merge(vector<Recipe>& arr, int left, int mid, int right);
    void mergeSort (vector<Recipe>& arr, int left, int right);
    vector<HashTable::Recipe> SearchByIngredient(const string& tag, const string& ingredient);
    vector<HashTable::Recipe> SearchByMinutes(const string& tag, const int& minutes);
    vector<HashTable::Recipe> SearchBySteps(const string& tag, const int& steps);
    vector<HashTable::Recipe> GetRecipes(string tag);
    void quickSort(vector<Recipe>& arr, int low, int high);
    int partition(vector<Recipe>& arr, int low, int high);


};
