#include <iostream>
#include "HashTable.h"
#include <map>
using namespace std;

HashTable::Recipe::Recipe(std::string name, string n_steps, string minutes, std::string steps, std::string ingredients) {
    this->name = name;
    this->n_steps = n_steps;
    this->minutes = minutes;
    this->steps = steps;
    this->ingredients = ingredients;

}

void HashTable::InsertRecipe(std::string tag, HashTable::Recipe currentRecipe) {
    recipeStorage[tag].push_back(currentRecipe);

}
void HashTable::PrintRecipe(string tag) {
    cout << "recipes in " << tag <<":" << endl;

    for (auto iter = recipeStorage[tag].begin(); iter != recipeStorage[tag].end(); ++iter) {

        cout << "name: " << iter->name << endl;
        cout << "duration: " << iter->minutes << endl;
        cout << "number of steps: " << iter->n_steps << endl;
        cout << "ingredients needed: " << iter->ingredients << endl;
        cout << "steps: " << iter->steps << endl;

    }
}
