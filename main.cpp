#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>
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
    fstream file("new.csv", ios::in);

    // storage units to use to read in information
    vector<string> row;
    string line, word;

    if(file.is_open()) {
        //while (getline(file, line)) {
        for (int i = 0; i < 2; i++) { //num of rows to read
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

            // current problem with this; splits it based off newline, there is going to be a , at the end of each tag
            // see if possible for ariella to alter the .csv and remove the commas
            // if not will have to create substrings to fix
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
    // need to make main at end of the project cleaner; for now, to test, just insert the name of a tag here to print out
    // remember that currently, commas will be at the end of the tag name
    h.PrintRecipe("60-minutes-or-less,");
    h.PrintRecipe("side-dishes,");

}
