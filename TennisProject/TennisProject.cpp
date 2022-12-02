#include <iostream>
#include <windows.h>
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

int rBinarySearch(vector <TennisPlayer> playerList, string inFirstName, string inLastName){
    static int high = playerList.size(), low = 0, mid = (high + low) / 2;
    
    if (playerList[mid].getLastName() == inLastName) {
        return mid;
    }
    else {
        if (playerList[mid].getLastName() > inLastName) {
            high = mid - 1;
            mid = (high + low) / 2;
        }
        else if (playerList[mid].getLastName() < inLastName) {
            low = mid + 1;
            mid = (high + low) / 2;
        }
    }

    return rBinarySearch(playerList, inFirstName, inLastName);
}


//Declaring a selection sorting algorithm to sort a vector of players
void selectionsort(vector<TennisPlayer>& teamList) {
    int i, j;
    int  small_index;

    for (i = 0; i < teamList.size() - 1; ++i) {
        small_index = i;
        for (j = i + 1; j < teamList.size() - 1; ++j) {
            if (teamList.at(j) < teamList.at(small_index)) {
                small_index = j;
            }
        }
        swap(teamList.at(i), teamList.at(small_index));
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

//reading the file into a vector
void readingPlayers(vector<TennisPlayer>& players, string fileName) {
    int rank, points;
    string lastname, firstname, country;
    ifstream Infile;

    Infile.open(fileName);

    cout << "Reading file " << fileName << '\n' << endl;

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
} 
// Apply selection sort function upon vector<TennisPlayer> playerList
int main(int argc, char* argv[]) {//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string inLastName, inFirstName, inCountry, countryCode, inBestName, line, fileName = argv[1];
    int inRank, inPoints,choice, foundPlayer = NULL, listSize = 0;
/*
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
  */

    // Allow user to input a country code and print out all associated players
    // Allow user to prompt as many country codes and determine termination point

    vector <TennisPlayer> playerList; //List to be sorted by Last Name
    vector <TennisPlayer> teamList; // List to be sorted by Country
    readingPlayers(playerList, fileName);
    readingPlayers(teamList, fileName);
    selectionsort(teamList);
    

    choice = displayMenu();
    while (1) {
        switch (choice) {
        case 1:
            if (choice == 1) {
                //Find a player and return their stats
                for (int i = 0; i < playerList.size() - 1; i++) {
                    playerList[i].display();
                }
                std::cout << '\n' << "Please enter the First and Last name of the person you would like to find. " << endl;
                std::cin >> inFirstName;
                std::cin >> inLastName;
                foundPlayer = rBinarySearch(playerList, inFirstName, inLastName);
                playerList[foundPlayer].display();
                std::cout << '\n' << endl;
                Sleep(2000);
                choice = displayMenu();
            }
            break;
        case 2:
            //update a players points
            if (choice == 2) {
                if (foundPlayer != NULL) {
                    playerList[foundPlayer].playerUpdate();
                    Sleep(2000);
                    choice = displayMenu();
                }
                else {
                    std::cout << "Please choose a player to edit by choosing option 1 in the Main Menu " << endl;
                    Sleep(2000);
                    choice = displayMenu();
                }
            }
            break;
        case 3:
            //display a team by country
            if (choice == 3) {
                std::cout << "Enter the country code you are looking for, press n to exit program" << endl;
                std::cin >> countryCode;
                Team aTeam(countryCode, teamList);
                aTeam.print();
                Sleep(2000);
                choice = displayMenu();
                //somefunction { create vector teams, so we can access the vector of teams with the update function or compare}
            
             }
            break;
        case 4:
            //update a teams points
            if (choice == 4) {
                Team aTeam(countryCode, teamList);
                aTeam.print();
                aTeam.teamUpdate();
                aTeam.print();
                Sleep(2000);
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