#include <iostream>
#include "Team.h"

using namespace std;

Team::Team()
{
}

// declaring constructor with parameter string and vector of TennisPlayers
Team::Team(string countryCode, vector <TennisPlayer>& playerlist) {
    country = countryCode;
    int count = 0;
    int startIndex = -1;
    for (int i = 0; i < playerlist.size(); i++) {
        if (playerlist.at(i).getcountry() == countryCode) {
            count++;
            if (startIndex == -1) {
                startIndex = i;
            }
        }
    }

    players = new TennisPlayer[count];
    int j = 0;
    for (int i = startIndex; i < startIndex + count; i++) {
        players[j] = playerlist.at(i);
        j++;
    }
    cout << "There are " << count << " players in this country" << endl;
    this->numberOfPlayers = count;
}
// destructor
Team :: ~Team() {
    delete[]players;
}
// copy constructor
Team::Team(const Team& origTeam) {
    cout << "Copy Constructor called" << endl;
    teamPoints = origTeam.teamPoints;
    country = origTeam.country;
    numberOfPlayers = origTeam.numberOfPlayers;

    players = new TennisPlayer[origTeam.numberOfPlayers];
    for (int j = 0; j < origTeam.numberOfPlayers; ++j) {
        players[j] = (origTeam.players[j]);
    }
}
//overloaded assigment operator
Team& Team:: operator=(const Team& teamCopy) {
    cout << "Overloaded Assignment Operator called" << endl;
    if (this != &teamCopy) {
        country = teamCopy.country;
        numberOfPlayers = teamCopy.numberOfPlayers;
        delete[] players;

        players = new TennisPlayer[teamCopy.numberOfPlayers];
        players = (teamCopy.players);
    }
    return *this;
}
// declaring print function; utilizes display method from TennisPlayer.cpp
void Team::print() const {
    cout << endl;
    for (int j = 0; j < numberOfPlayers; ++j) {
        players[j].display();

    }
}

void Team::teamUpdate() {
    int teamPoints = 0;
    for (int i = 0; i < numberOfPlayers; i++){
        teamPoints += players[i].getPoints();
    }
    std::cout << '\n' << "Total Team points are: " << teamPoints << endl;

}

void Team::addPoints(){
    int pointsToAdd = 0;
    int updatedTeamPoints = 0;
    int inPoints = 0;

    std::cout << "How many points would you like to add? " << endl;
    cin >> pointsToAdd;
    for (int i = 0; i < numberOfPlayers; i++) { // setting each indiv players points to a pointsToAdd + their current points
        inPoints = (players[i].getPoints() + pointsToAdd);
        players[i].setPoints(inPoints);
    }
    for (int i = 0; i < numberOfPlayers; i++) {// updating their teams total points by again getting the summation of each players points 
        updatedTeamPoints = updatedTeamPoints + players[i].getPoints();
    }
    std::cout << '\n' << "Total Team points are: " << updatedTeamPoints << '\n' << endl;
}

string Team::getCountry() const
{
    return country;
}

int Team::getNumberOfPlayers() const
{
    return numberOfPlayers;
}

int Team::getTeamPoints() const
{
    return teamPoints;
}


