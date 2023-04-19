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
    fstream file("temp.csv", ios::in);

    // storage units to use to read in information
    vector<string> row;
    string line, word;

    if(file.is_open()) {
        //while (getline(file, line)) {
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

    // need to make main at end of the project cleaner; for now, to test, just insert the name of a tag here to print out

    //example user input:
    cout << "please input a tag from the following list! " << endl;
    //then when user inputs something, call CheckTag to ensure it exists in the map
    // if it does, proceed by printing
    // if not, print "please try again!" and then loop back to the start
    // after correct tag is inputted, display the menu
    // then provide list of actions for the user to take afterwards
    //1. Add another tag
    //2. Search by ingredient
    //3. Search by minutes
    //4. Search by number of steps
    //5. Display Results

    //testing print here; not needed after project is done
    //h.PrintRecipe("60-minutes-or-less");
    //h.PrintRecipe("side-dishes,");
    //h.PrintRecipe("vegetarian,");

    // there will probably be a large amount of diff tags (100+); its impossible for the user to know all of them,
    // so we can either provide a list of all possible tags (we can limit it to show like 20 at a time)

}
