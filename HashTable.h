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

        Recipe(string name, string n_steps, string minutes, string steps, string ingredients);

    };
    unordered_map<string, vector<Recipe>> recipeStorage;

    void InsertRecipe(string tag, Recipe currentRecipe);
    void PrintResult(vector<Recipe> &arr);
    void merge(vector<Recipe>& arr, int left, int mid, int right);
    void mergeSort (vector<Recipe>& arr, int left, int right);
    vector<HashTable::Recipe> SearchByIngredient(const string& tag, const string& ingredient);
    vector<HashTable::Recipe> SearchByMinutes(const string& tag, const int& minutes);
    vector<HashTable::Recipe> SearchBySteps(const string& tag, const int& steps);
    vector<HashTable::Recipe> GetRecipes(string tag);
    void quickSort(vector<Recipe>& arr, int low, int high);
    int partition(vector<Recipe>& arr, int low, int high);
    void PrintRecipe(string tag);
};
