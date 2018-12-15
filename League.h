#pragma once
#include "Team.h"
#include "Game.h"
#include "Global.h"
class League
{
    public:
        //constructor fill TeamList, giving all the teams stats
        //and calculating the stat rating for each team
        League();
        //reads scores from file, adds games to teams
        //games vector via team.addGame
        void readScores(ifstream& ins);
        //prints the teams and stats into readable table format in file
        void printTeams(ofstream& outs);
        void normalizeRatings();
    private:
        Team teamList[NUM_TEAMS];
        vector<Team> sortedTeamList;
        vector<double> sortedTeamRatings;
        //fills teamList and gives all teams their stats and
        //stat rating
        void createTeams();
        //following 4 are all used to extract team from Scores.txt
        Team getTeamFromStr(string str);
        int findNumDigits(string str);
        void cropLine(string& str);
        void removeSeed(string& team);
        
    
};


