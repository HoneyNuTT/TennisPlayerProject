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
template <typename T> 
int rBinarySearch(vector <T> playerList, string inFirstName, string inLastName){
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
template <typename T>
void selectionsort(vector<T>& teamList) {
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
    std::cout << " 5. Test Overloaded Assignment Operator\n";
    std::cout << " 6. Test Copy Constructor\n";
    std::cout << " 7. Exit Program \n";
    cin >> choice;
    return choice;
}

//reading the file into a vector
void readingPlayers(vector<TennisPlayer>& players, string fileName) {
    int rank, points;
    string lastname, firstname, country;
    ifstream inFile;

    inFile.open(fileName);

    cout << "Reading file " << fileName << '\n' << endl;

    if (!inFile.is_open()) {
        cout << "File does not exists" << endl;
        exit(1);
    }
    while (!inFile.eof()) {
        inFile >> rank >> lastname >> firstname >> country >> points;
        TennisPlayer aplayer(country, rank, lastname, firstname, points);

        players.push_back(aplayer);
    }
    inFile.close();
} 
// Apply selection sort function upon vector<TennisPlayer> playerList
int main(int argc, char* argv[]) {//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string inLastName, inFirstName, inCountry, countryCode = "NULL", inBestName, line, fileName = argv[1];
    int inRank, inPoints,choice, foundPlayer = NULL, listSize = 0;

    // Allow user to input a country code and print out all associated players
    // Allow user to prompt as many country codes and determine termination point

    vector <TennisPlayer> playerList; //List to be sorted by Last Name
    vector <TennisPlayer> teamList; // List to be sorted by Country
    vector <Team> listOfTeams;
    readingPlayers(playerList, fileName);
    readingPlayers(teamList, fileName);
    selectionsort(teamList);
    

    choice = displayMenu();
    while (1) {
        switch (choice) {
        case 1:
            {
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
            {
                    std::cout << '\n' << "Please enter the First and Last name of the person you would like to find. " << endl;
                    std::cin >> inFirstName;
                    std::cin >> inLastName;
                    foundPlayer = rBinarySearch(playerList, inFirstName, inLastName);
                    playerList[foundPlayer].display();
                    playerList[foundPlayer].playerUpdate();
                    Sleep(2000);
                    choice = displayMenu();
            }
            break;
        case 3:
            //display a team by country + add team to a list for later use.
            if (choice == 3) {
                std::cout << "Enter the country code you are looking for " << endl;
                std::cin >> countryCode;
                Team aTeam(countryCode, teamList);
                aTeam.print();
                Sleep(2000);
                choice = displayMenu();
        }
            break;
        case 4:
            //update a teams points
            {
                if (countryCode != "NULL") {
                    Team aTeam(countryCode, teamList);
                    aTeam.print();
                    aTeam.teamUpdate();
                    std::cout << "How many points would you like to add? " << endl;
                    cin >> inPoints;
                    aTeam.addPoints(inPoints);
                    aTeam.print();
                    Sleep(2000);
                    choice = displayMenu();
                }
                else {
                    std::cout << " Please choose a Team to edit by choosing option 3 in the Main Menu " << endl;
                    Sleep(2000);
                    choice = displayMenu();
                }
            }
            break;
        case 5:
            //Testing Overloaded Operator
            {
                string inFirstCountry;
                std::cout << " Enter the first country for comparison " << endl;
                std::cin >> inFirstCountry;
                Team firstTeam(inFirstCountry, teamList);
                Team secondTeam;
                secondTeam = firstTeam;
                std::cout << " We are adding 200 points to Team: Copy " << endl;
                secondTeam.addPoints(200);
                std::cout << "Team:Copy " << secondTeam.getCountry() << endl;               
                secondTeam.print(); 
                secondTeam.teamUpdate();
                std::cout << "\n\n";
                std::cout << "Team:Original " << secondTeam.getCountry() << endl;
                firstTeam.print();
                firstTeam.teamUpdate();

                Sleep(2000);
                choice = displayMenu();

            }
            break;
        case 6:
            //copy a team copy an existing time, and update their points without touching the old version
            {
                std::cout << "Enter the Country of the Team for which you would like to copy " << endl;
                std::cin >> countryCode;
                Team aTeam(countryCode, teamList);
                Team bTeam(aTeam);
                std::cout << " We are adding 300 points to Team: Copy " << endl;
                bTeam.addPoints(300);
                bTeam.teamUpdate();
                bTeam.print();

                aTeam.print();
                aTeam.teamUpdate();

                Sleep(2000);
                choice = displayMenu();
            }
            break;
        case 7:
            {
                //Exits Program
                exit(1);
            }
        }
    }

    return 0;
}