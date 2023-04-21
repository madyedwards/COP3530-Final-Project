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

    // sfml, pages in main?

    // Open an existing file
    fstream file("fixed.csv", ios::in);

    // storage units to use to read in information
    vector<string> row;
    string line, word;

    if(file.is_open()) {
        //while (getline(file, line)) {
        cout <<"here";
        for (int i = 0; i < 20; i++) { //num of rows to read
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

    //testing print here; not needed after project is done
    h.PrintRecipe("60-minutes-or-less");
    //h.PrintRecipe("side-dishes,");
    //h.PrintRecipe("vegetarian,");

    // need to make main at end of the project cleaner; for now, to test, just insert the name of a tag here to print out

    //example user input:
    string tag;

    cout << "Please input a tag from the following list: 60-minutes-or-less, side-dishes, mexican, easy, fall, holiday-event,vegetarian, winter, 30-minutes-or-less, "
            "breakfast, main-dish, kid-friendly, 15-minutes-or-less, desserts, no-cook, indian, asian, north-american,"
            "vegan, healthy, seafood, chicken, meat, salads" << endl;

    cin >> tag;

    //then when user inputs something, call CheckTag to ensure it exists in the map
    // if it does, proceed by printing
    // if not, print "please try again!" and then loop back to the start

    int choice;
    bool continue_looping = true;

    string ingredients;
    int minutes;
    int steps;

    vector<HashTable::Recipe> temp; //functions will push back to this temp


    while (continue_looping) {
        // Display the menu options
        cout << "Please select one of the following to continue:" << endl;
        cout << "1. Add another tag" << endl;
        cout << "2. Search by ingredient" << endl;
        cout << "3. Search by minutes" << endl;
        cout << "4. Search by number of steps" << endl;
        cout << "5. Display Results" << endl;

        // Get user input for their choice
        cin >> choice;


        switch (choice) {
            case 1:
                // Add another tag
                cout << "Please input another tag:" << endl;
                cin >> tag;
                // to do: implement this option
                break;
            case 2:
                // Search by ingredient
                cout << "Which ingredient would you like your recipes to include?" << endl;
                cin >> ingredients;
                // to do: implement this option
                break;
            case 3:
                // Search by minutes
                cout << "What is the maximum amount of minutes you want the recipes included to follow?" << endl;
                cin >> minutes;
                // to do: implement this option
                break;
            case 4:
                // Search by number of steps
                cout << "What is the maximum amount of steps you want the recipes included to follow?" << endl;
                cin >> steps;
                // to do: implement this option
                break;
            case 5:
                // Display results
                // Sort the recipes in recipeStorage based on name
                // to do: implement this option
                vector<HashTable::Recipe> test2 = temp;
                auto start = chrono::high_resolution_clock::now();

                // Sort the recipes in recipeStorage based on name
                for (auto& recipe : temp) {
                    h.mergeSort(temp, 0, temp.size() - 1);
                }

                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double> elapsed_seconds = end - start;
                double time = elapsed_seconds.count();

                // same thing for quick sort on test2
                //if statement comparing the time for each sorting algorithm
                //call print function on whichever is faster on the vector

                break;
            default:
                // Invalid choice
                cout << "Invalid choice. Please select a valid option." << endl;
        }
        char continue_choice;
        cout << "Do you want to continue? (y/n)" << endl;
        cin >> continue_choice;

        if (continue_choice != 'y') {
            continue_looping = false;
        }
    }

}

