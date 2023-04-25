#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>
#include <chrono>
#include "HashTable.h"
using namespace std;

int main() {
    //read in csv file per line
    // structure: number (not explicit or needed), name, minutes, tags, n_steps, steps, ingredients
    // ex. 1 - taco - 20 min - mexican, under 60 minutes, affordable, easy - 4 steps - 1. , 2.. 3., - tomato, tortilla
    // technically this is an unordered map, not a hashtable; changed it after making the file
    HashTable h;

    // Open an existing file
    fstream file("FINAL_DATA.csv", ios::in);

    // storage units to use to read in information
    vector<string> row;
    string line, word;

    if(file.is_open()) {
        for (int i = 0; i < 200000; i++) { //num of rows to read
            getline(file, line); //grab row

            row.clear();
            stringstream str(line);

            //define all elements to create a recipe object
            string name, n_steps, minutes, tags, steps, ingredients;

            //read data from csv file!
            getline(str, word, '"'); //skip comma
            getline(str,word,'"'); // get name
            name = word;
            //cout << "name: " << name << endl;

            getline(str,word,'"'); //skip over the comma
            getline(str,word,'"'); //get number of steps
            minutes = word;

            getline(str,word,'"'); //skip over the comma
            getline(str,word,'"'); //get tags
            tags = word;

            //breaks the separate tags up by newline
            stringstream ss(tags);
            istream_iterator<string> begin(ss);
            istream_iterator<string> end;
            vector<string> totalTags(begin, end); //storage container for all tags

            getline(str,word,'"'); //skip over the comma
            getline(str,word,'"'); //get minutes
            n_steps = word;

            getline(str,word,'"'); //skip comma
            getline(str,word,'"'); //get steps
            steps = word;

            getline(str,word,'"'); //skip comma
            getline(str,word,'"'); // get ingredients
            ingredients = word;

            //now create associated recipe obj
            HashTable::Recipe currentRecipe = HashTable::Recipe(name, n_steps, minutes, steps, ingredients);

            //then insert based on totalTags vector
            for (int j = 0; j < totalTags.size(); j++) {
                h.InsertRecipe(totalTags[j],currentRecipe);
            }
        }
    }
    
    string tag;

    cout << "Please input a tag from the following list: " << endl;
    cout << "60-minutes-or-less, side-dishes, mexican, easy, fall, holiday-event,vegetarian, winter, 30-minutes-or-less, breakfast, main-dish," << endl;
    cout << "kid-friendly, 15-minutes-or-less, desserts, no-cook, indian, asian, north-american, vegan, healthy, seafood, chicken, meat, salads" << endl;

    cin >> tag;
    h.GetRecipes(tag);


    int choice;

    string ingredients;
    int minutes;
    int steps;

    vector<HashTable::Recipe> temp; //functions will push back to this temp


    // Display the menu options
    cout << "Please select one of the following to continue:" << endl;
    cout << "1. Search by ingredient" << endl;
    cout << "2. Search by minutes" << endl;
    cout << "3. Search by number of steps" << endl;

    // Get user input for their choice
    cin >> choice;


    switch (choice) {
        case 1:
            // Search by ingredient
            cout << "Which ingredient would you like your recipes to include?" << endl;
            cin >> ingredients;

            // get the recipes associated with the initial tag that include the specified ingredient
            temp = h.SearchByIngredient(tag, ingredients);

            break;

        case 2:
            // Search by minutes
            cout << "What is the maximum number of minutes the recipes should take?" << endl;
            cin >> minutes;

            temp.clear(); // clear the temporary vector
            temp = h.SearchByMinutes(tag, minutes);


            break;

        case 3:
            // Search by number of steps
            cout << "What is the maximum number of steps the recipes should have?" << endl;
            cin >> steps;

            temp.clear(); // clear the temporary vector
            temp = h.SearchBySteps(tag, steps);

            break;
        }

        // Display result
        vector<HashTable::Recipe> testMerge = temp;
        vector<HashTable::Recipe> testQuick = temp;
// FIRST ALGORITHM HERE
        auto start = chrono::high_resolution_clock::now();

        // call mergeSort
        for (auto& recipe : testMerge) {
            h.mergeSort(testMerge, 0, testMerge.size() - 1);
        }


        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;
        double timeMerge = elapsed_seconds.count();

//SECOND ALGORITHM HERE
        auto start2 = chrono::high_resolution_clock::now();

        // call mergeSort
        for (auto& recipe : testQuick) {
            h.quickSort(testQuick, 0, testQuick.size()-1);
        }

        auto end2 = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed_seconds2 = end2 - start2;
        double timeQuick = elapsed_seconds2.count();

        //COMPARISON HERE
        if (timeMerge < timeQuick) {
            h.PrintResult(testMerge);
            cout << "MERGE" << endl;
        }
        else {
            h.PrintResult(testQuick);
            cout << "QUICK" << endl;
        }

        cout << "timeMerge: " << timeMerge << endl;
        cout << "timeQuick: " << timeQuick << endl;

    }
