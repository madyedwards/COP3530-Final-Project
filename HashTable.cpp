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

HashTable::Recipe::Recipe() {

}

void HashTable::InsertRecipe(std::string tag, HashTable::Recipe currentRecipe) {
    recipeStorage[tag].push_back(currentRecipe);

}
void HashTable::PrintRecipe(string tag) {
    cout << "recipes in " << tag <<":" << endl;

    for (auto iter = recipeStorage[tag].begin(); iter != recipeStorage[tag].end(); ++iter) {

        cout << "name: " << iter->name << endl;
        cout << "duration: " << iter->minutes << " minutes" << endl;
        cout << "number of steps: " << iter->n_steps << endl;
        cout << "ingredients needed: " << iter->ingredients << endl;
        cout << "steps: " << iter->steps << endl;

    }
}
void HashTable::CheckTag(std::string tag) {
    for (auto iter = recipeStorage.begin(); iter != recipeStorage.end(); ++iter) {
        if (recipeStorage.find(tag) == recipeStorage.end() ){
            cout << "tag not found! please try again. " << endl;
        }
    }

}

// Merge function for Recipe vectors
void HashTable::merge(std::vector<Recipe>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<Recipe> X(n1), Y(n2);

    for (int i = 0; i < n1; i++)
        X[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        Y[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (X[i].name <= Y[j].name) {
            arr[k] = X[i];
            i++;
        } else {
            arr[k] = Y[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = X[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = Y[j];
        j++;
        k++;
    }
}

// Merge sort function for Recipe vectors
void HashTable::mergeSort(std::vector<Recipe>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}


