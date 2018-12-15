#pragma once
#include <string>
#include "Team.h"
using namespace std;

class Game
{
    public:
        //all constructors call calculateRating()
        Game();
        Game(Team o, int MOVin, bool win);
        Game(Team o, int MOVin, bool win, bool homeGame);
        Game(Team o, int MOVin, bool win, int dayin);
        double getRating();
        bool isWin();
        Team getOpponent();
        void setOpponent(Team o);
        bool isHome();
        int getMOV();
        void setMOV(int n);
        int getDay();
        void setDay(int d);

    private:
        //modifies rating according to algorithm
        void calculateGameRating(bool win, bool home, int MOV);
        double rating;
        bool isWon;
        bool home;
        Team opponent;
        int MOV;
        int day;
};

