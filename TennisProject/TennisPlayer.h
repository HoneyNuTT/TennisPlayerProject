#pragma once
#include <string>

using namespace std;

class TennisPlayer {
public:
    TennisPlayer();
    TennisPlayer(string, int, string, string, int);
    TennisPlayer(const TennisPlayer&  origPlayer); // copy constructor for TennisPlayer
    void addTennisPlayer(int, string, string, string, int);
    void display() const;
    string getcountry()const;
    int getPoints()const;
    void setPoints(int inPoints);

    bool operator < (const TennisPlayer& lhs) {
        return (this->country < lhs.getcountry());
    }

private:
    string lastName;
    string firstName;
    string country;
    int rank, points;
};