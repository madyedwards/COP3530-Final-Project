#include <iostream>
#include "HashTable.h"
#include <map>
#include <algorithm>
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
//void HashTable::PrintRecipe(string tag) {
//    cout << "recipes in " << tag <<":" << endl;
//
//    for (auto iter = recipeStorage[tag].begin(); iter != recipeStorage[tag].end(); ++iter) {
//
//        cout << "name: " << iter->name << endl;
//        cout << "duration: " << iter->minutes << " minutes" << endl;
//        cout << "number of steps: " << iter->n_steps << endl;
//        cout << "ingredients needed: " << iter->ingredients << endl;
//        cout << "steps: " << iter->steps << endl;
//
//    }
//}


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
        //we switched this to minutes bc of quicksort, want to find a way for them both to be names
        if (X[i].minutes <= Y[j].minutes) {
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
void HashTable::quickSort(vector<Recipe>& arr, int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot -1);
        quickSort(arr, pivot+1, high);
    }
}


int HashTable::partition(vector<Recipe>& vec, int low, int high) {
    int pivot = stoi(vec.at(low).minutes);
    int up = low, down = high;

    while(up < down) {
        for (int j = up; j < high; j++) {
            if (stoi(vec.at(up).minutes) > pivot)
                break;
            up++;
        }
        for (int j = high; j > low; j--) {
            if (stoi(vec.at(down).minutes) < pivot)
                break;
            down--;
        }
        if (up < down) {
            swap(vec[up], vec[down]);
        }
    }
    swap(vec[low], vec[down]);
    return down;
}


//void HashTable::CheckTag(std::string tag) {
//    for (auto iter = recipeStorage.begin(); iter != recipeStorage.end(); ++iter) {
//        if (recipeStorage.find(tag) == recipeStorage.end() ){
//
//            cout << "tag not found! please try again. " << endl;
//        }
//    }
//
//}

vector<HashTable::Recipe> HashTable::GetRecipes(string tag) {
    // Check if tag exists in recipeStorage
    if (recipeStorage.find(tag) == recipeStorage.end()) {
        return vector<Recipe>();
    }

    // Return vector of recipes associated with the given tag
    return recipeStorage[tag];
}


vector<HashTable::Recipe> HashTable::SearchByIngredient(const string& tag, const string& ingredient) {
    vector<HashTable::Recipe> temp;
    unordered_map<string, vector<Recipe> >::iterator it = recipeStorage.find(tag);
    if (it != recipeStorage.end()) {
        vector<Recipe>& recipes = it->second;
        for (Recipe& r : recipes) {
            if (r.ingredients.find(ingredient) != string::npos) {
                temp.push_back(r);
            }
        }
    }
    return temp;
}

vector<HashTable::Recipe> HashTable::SearchByMinutes(const string& tag, const int& minutes) {
    vector<HashTable::Recipe> temp;
    unordered_map<string, vector<Recipe> >::iterator it = recipeStorage.find(tag);
    if (it != recipeStorage.end()) {
        vector<Recipe>& recipes = it->second;
        for (Recipe& r : recipes) {
            if (stoi(r.minutes) <= minutes) {
                temp.push_back(r);
            }
        }
    }
    return temp;
}

vector<HashTable::Recipe> HashTable::SearchBySteps(const string& tag, const int& steps) {
    vector<HashTable::Recipe> temp;
    unordered_map<string, vector<Recipe> >::iterator it = recipeStorage.find(tag);
    if (it != recipeStorage.end()) {
        vector<Recipe>& recipes = it->second;
        for (Recipe& r : recipes) {
            if (stoi(r.n_steps) <= steps) {
                temp.push_back(r);
            }
        }
    }
    return temp;
}

void HashTable::PrintResult(vector<Recipe> &arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << "Recipe Name: " << arr[i].name << endl;
        cout << "Recipe Duration: " << arr[i].minutes << " minutes" << endl;
        cout << "Number of Steps: " << arr[i].n_steps << endl;
        cout << "Ingredients in Recipe: " << arr[i].ingredients << endl;
        cout << "Steps: " << arr[i].steps << endl;

        cout << " " << endl;

    }
}


