#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "Global.h"

using namespace std;


class Team {
    public:
        //default constructor sets name to "NOT D1" and rating to -20
        Team();
        Team(string name);
        string getName();
        double getRating();
        double getSeasonRating();
        double getStatRating();
        double getTS();
        double getTOV();
        double getTSA();
        double getTOVA();
        double getORB();
        double getORBA();
        int getGP();
        int getWins();
        int getLosses();
        void setName(string name);
        void setRating(double rating);
        void setSeasonRating(double rating);
        void setStatRating(double rating);
        void setTS(double num);
        void setTOV(double num);
        void setORB(double num);
        void setTSA(double num);
        void setTOVA(double num);     
        void setORBA(double num);
        //increments GP as well as wins or losses accordingly
        //adds JUST THE RATING the team got for the game
        //updates seasonRating to take all games into account
        void addGame(double rating, bool win);
        void printGameRatings(ofstream& outs);
    private:
        vector<double> gameRatings;
        void setStatsToZero();
        //combines seasonRating and statRating according to weights
        double calculateRating();
        string teamName;
        double rating;
        //rating based purely off of scores and opponents
        double seasonRating;
        double statRating;      
        double TS;
        double TOV;
        double ORB;
        double TSA;
        double TOVA;
        double ORBA;
        int GP;
        int wins;
        int losses;
};

