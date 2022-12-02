#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Team.h"



template <typename T>
int BinarySearch(vector <T> lastNames, string target, int lowVal, int highVal) {
    int itemPos;
    int midVal = (highVal + lowVal) / 2;
    int rangeSize = (highVal - lowVal) + 1;

    if (target == lastNames.at(midVal)) {
        itemPos = midVal;
    }
    else if (rangeSize == 1) {
        itemPos = -1;
    }
    else {
        if (target < lastNames.at(midVal)) {
            itemPos = BinarySearch(lastNames, target, lowVal, midVal);
        }
        else {
            itemPos = BinarySearch(lastNames, target, midVal + 1, highVal);
        }
    }
    return itemPos;
}

//int rBinarySearch() {}


//Declaring a selection sorting algorithm to sort a vector of players
template <typename T>
void selectionsort(vector <typename T> playerlist) {
    int i, j;
    int  small_index;
    for (i = 0; i < playerlist.size() - 1; ++i) {
        small_index = i;
        for (j = i + 1; j < playerlist.size() - 1; ++j)
            if (playerlist.at(j) < playerlist.at(small_index)) {
                small_index = i;
            }
        std::cout << "executing sort" << endl;
        swap(playerlist.at(i), playerlist.at(small_index));
    }
}

int displayMenu() {
    int choice = 0;
    std::cout << "===================================================== \n";
    std::cout << " \t\tMENU \t \n ";
    std::cout << "===================================================== \n";
    std::cout << " 1. Find player and return their stats\n";
    std::cout << " 2. Update a players points\n";
    std::cout << " 3. Display a team by country\n";
    std::cout << " 4. Update a teams points\n";
    std::cout << " 5. Compare a team with another existing team\n";
    std::cout << " 6. Copy a team\n";
    std::cout << " 7. Delete a team \n";
    cin >> choice;
    return choice;
}

/*reading the file into a vector
void Readingplayers(vector<TennisPlayer>& players) {
    int rank, points;
    string lastname, firstname, country, fileName;
    ifstream Infile;
    
    //std::cout << " Please type the name of the .txt file you would like to find." << endl; 
    //std::cin >> fileName;

    Infile.open("WomensSingles.txt");

    cout << "Reading file." << endl;

    if (!Infile.is_open()) {
        cout << "File does not exists" << endl;
        exit(1);
    }
    while (!Infile.eof()) {
        Infile >> rank >> lastname >> firstname >> country >> points;
        TennisPlayer aplayer(country, rank, lastname, firstname, points);

        players.push_back(aplayer);
    }
    Infile.close();
} */
// Apply selection sort function upon vector<TennisPlayer> playerList
int main(int argc, char* argv[]) {//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string inLastName, inFirstName, inCountry, countryCode, inBestName, line;
    int inRank, inPoints,choice, listSize = 0;

    ifstream inFile;
    inFile.open("WomensSingles.txt");
    if (inFile.is_open()) {
        while (getline(inFile, line)) { listSize++; } // checking to see how many lines are in the file, then using this int to intialize a vector of size n.
       //std::cout << "there are " << listSize << " Lines in this file " << endl;
    }
    else {
        std::cout << "InFile Failed" << endl;
        exit (1);
    }
    inFile.close();

    vector<TennisPlayer> playerlist(listSize); 


    inFile.open("WomensSingles.txt");
    if (inFile.is_open()) {

        while (!inFile.eof()) {// reading from .txt file and storing names into string vectors
            static int i = 0;
            inFile >> inRank >> inLastName >> inFirstName >> inCountry >> inPoints;
            playerlist.at(i).addTennisPlayer(inRank, inLastName, inFirstName, inCountry, inPoints);
            i++;
        }
        //for (int i = 0; i < playerlist.size() - 1; i++) {
        //    playerlist[i].display();
       // }

    }
    else { 
        std::cout << "InFile Failed" << endl;
        exit(1);
    }
    inFile.close();

    //TennisPlayer newPlayer(TennisPlayer & origPlayer);
    
    // Allow user to input a country code and print out all associated players
    // Allow user to prompt as many country codes and determine termination point

    selectionsort(playerlist);
    //std::cout << "sorted by country successfully! " << '\n' << endl;
   


    choice = displayMenu();
    while (1) {
        switch (choice) {
        case 1:
            //Find a player and return their stats
            break;
        case 2:
            //update a players points
            break;
        case 3:
            //display a team by country
            if (choice == 3) {
                std::cout << "Enter the country code you are looking for, press n to exit program" << endl;
                std::cin >> countryCode;
                Team aTeam(countryCode, playerlist);
                aTeam.print();
                choice = displayMenu();
                //somefunction { create vector teams, so we can access the vector of teams with the update function or compare}
            
             }
            break;
        case 4:
            //update a teams points
            if (choice == 4) {
                Team aTeam(countryCode, playerlist);
                aTeam.print();
                aTeam.teamUpdate();
                aTeam.print();
                choice = displayMenu();
            }
            break;
        case 5:
            //compare a team with another team
            break;
        case 6:
            //copy a team
            break;
        case 7:
            //delete a team
            break;
        }
    }

    return 0;
}