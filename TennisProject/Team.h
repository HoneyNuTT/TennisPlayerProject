#pragma once

using namespace std;
#include "TennisPlayer.h"
#include <vector>
using namespace std;
class Team {
public:
    Team();
    Team(string countryCode, vector <TennisPlayer>&); // constructor with parameter string and vector of TennisPlayer
    ~Team(); // destructor
   Team(const Team& origobj); // copy constructor
    Team& operator =(const Team& origobj); //overloaded assignment operator
    void print() const; // print function will utilize display method declared in TennisPlayer.cpp
    void teamUpdate(); //Updates the teams points
    void addPoints(int inPoints);// adds points to team

    string getCountry() const;
    int getNumberOfPlayers() const;
    int getTeamPoints() const;

private:
    int numberOfPlayers, teamPoints;
    string country;
    TennisPlayer* players;
};