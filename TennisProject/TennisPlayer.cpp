#include "TennisPlayer.h"
#include <iostream>

// default constructor
using namespace std;
TennisPlayer::TennisPlayer() {
    rank = 0;
    points = 0;
    lastName = "no name";
    firstName = "no name";
    country = "no country";
}
// loaded constructor
TennisPlayer::TennisPlayer(string country, int rank, string lname, string fname, int points) {
    this->rank = rank;
    this->points = points;
    lastName = lname;
    firstName = fname;
    this->country = country;
}
/*TennisPlayer::TennisPlayer(const TennisPlayer& origPlayer) {
    //std::cout << "Copy Constructor Called" << endl;

    lastName = origPlayer.lastName;
    firstName = origPlayer.firstName;
    points = origPlayer.points;
    country = origPlayer.country;
    rank = origPlayer.rank;
    this->display();

}*/
void TennisPlayer::addTennisPlayer(int inRank, string inLastName, string inFirstName, string inCountry, int inPoints)
{
    rank = inRank, lastName = inLastName, firstName = inFirstName, country = inCountry, points = inPoints;
}
// display method used later to print a player associated with a Tennis Team
void TennisPlayer::display() const {
    cout << rank << ": " << firstName << "," << lastName << " " << points << " " << country << endl;
}
void TennisPlayer::playerUpdate(){
    int inPoints = 0;
    std::cout << " How many points would you like to add to this player? " << endl;
    cin >> inPoints;
    this->points = inPoints + this->getPoints();
    std::cout << " Players has been updated! " << endl;
    this->display();
}
string TennisPlayer::getLastName() const{ return lastName;
}
string TennisPlayer::getFirstName() const{return firstName;
}
// getter function declared
string TennisPlayer::getcountry() const {return this->country;
}

int TennisPlayer::getPoints() const{ return points;
}

void TennisPlayer::setPoints(int inPoints){ points = inPoints;
}

bool TennisPlayer::operator<(const TennisPlayer& lhs)
{
    return (this->country < lhs.getcountry());
}

