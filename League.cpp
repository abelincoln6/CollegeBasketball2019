#include "League.h"

League::League()
{
    createTeams();
}

void League::readScores(ifstream& scores) {
    string str1;
    string str2;
    string team1;
    string team2;
    int score1;
    int score1Digits;
    int score2;
    int score2Digits;
    string winTeam;
    string loseTeam;
    while (scores.good()) {
        //flag becomes true when one team gets found so when the second one does it can break
        //only purpose is to save time for compiler
        bool flag = false;
        //get two lines at once because two teams in game
        getline(scores, str1);
        getline(scores, str2);
        //remove final and whitespace from scores
        cropLine(str1);
        cropLine(str2);

        score1Digits = findNumDigits(str1);
        score2Digits = findNumDigits(str2);
        string t1 = str1.substr(0, str1.size() - score1Digits - 1);
        string t2 = str2.substr(0, str2.size() - score2Digits - 1);
        removeSeed(t1);
        removeSeed(t2);
        score1 = stoi(str1.substr(str1.size() - score1Digits));
        score2 = stoi(str2.substr(str2.size() - score2Digits));

        int MOV = abs(score1 - score2);
        bool team1win = score1 > score2;
        
        Team team1 = getTeamFromStr(t1);
        Team team2 = getTeamFromStr(t2);

        for (int i = 0; i < NUM_TEAMS; i++) {
            string name = teamList[i].getName();
            //add game for team 1 with team 2 as opponent
            //team 2 is home team
            if (name == t1) {
                Game g(team2, MOV, team1win, false);
                teamList[i].addGame(g.getRating(), team1win);
                if (flag) {
                    break;
                }
                flag = true;
            }
            //vice versa from above
            else if (name == t2) {
                Game g(team1, MOV, !team1win, true);
                teamList[i].addGame(g.getRating(), !team1win);
                if (flag) {
                    break;
                }
                flag = true;
            }
        }
    }
}

void League::createTeams() {
    ifstream ins;
    ifstream TSReader, TOVReader, TSAReader, TOVAReader, ORBReader, ORBAReader;
    string fileName;
    ins.open("Teams.txt");
    TSReader.open("TS.txt");
    TOVReader.open("TOV.txt");
    TSAReader.open("TSA.txt");
    TOVAReader.open("TOVA.txt");
    ORBReader.open("ORB.txt");
    ORBAReader.open("ORBA.txt");
    //statReader.open("FT.txt");
    string teamName;
    double TS, TOV, TSA, TOVA, ORB, ORBA;
    int i = 0;
    while (getline(ins, teamName) && TSReader >> TS && TOVReader >> TOV && 
        TSAReader >> TSA && TOVAReader >> TOVA && ORBReader >> ORB && ORBAReader >> ORBA) {
        teamList[i].setName(teamName);
        teamList[i].setTS(TS);
        teamList[i].setTOV(TOV);
        teamList[i].setTSA(TSA);
        teamList[i].setTOVA(TOVA);
        teamList[i].setORB(ORB);
        teamList[i].setORBA(ORBA);
        double TSDiff = (TS - TSA) - MEAN_TSDiff;
        double TOVDiff = (TOVA - TOV) - MEAN_TOVDiff;
        double ORBDiff = (ORB - ORBA) - MEAN_ORBDiff;
        TSDiff /= SDEV_TSDiff;
        TOVDiff /= SDEV_TOVDiff;
        ORBDiff /= SDEV_ORBDiff;
        double rat = (TSDiff * TS_WEIGHT) + (TOVDiff * TOV_WEIGHT) + (ORBDiff * ORB_WEIGHT);
        teamList[i].setStatRating(rat);
        teamList[i].setRating(rat);
        i++;
    }

    ins.close();
    TSReader.close();
    TOVReader.close();
    TSAReader.close();
    TOVAReader.close();
}

void League::printTeams(ofstream& outs) {
    ofstream outs2;
    outs2.open("Output.txt");
    for (int i = 0; i < NUM_TEAMS; i++) {
        sortedTeamRatings.push_back(teamList[i].getRating());
    }
    sort(sortedTeamRatings.begin(), sortedTeamRatings.end());

    for (int i = 0; i < NUM_TEAMS; i++) {
        for (int j = 0; j < NUM_TEAMS; j++) {
            
            if (abs(teamList[j].getRating() - sortedTeamRatings[i]) <= 0.0001) {
                sortedTeamList.push_back(teamList[j]);
                break;
            }
        }
    }
    //outs << "Team\t\t\t\t\t\t\t" << "RATING\t" << "GP\t\t" << "Wins\t" << "Losses\t" << 
        //"TS%\t\t" << "TOV\t\t" << "STAT\t" << "GAME\t" << endl;
    for (int i = NUM_TEAMS - 1; i >= 0; i--) {
        Team t = sortedTeamList[i];

        outs << t.getName();
        //for alignment
        int len = t.getName().size();
        for (int i = 0; i < 7 - len / 4; i++) {
            outs << "\t";
        }
        outs << "\t" << round(t.getRating() * 1000) / 1000 + 0.0001 << "\t\t"
            << t.getWins() << "\t\t" << t.getLosses() <<
            "\t" << t.getStatRating() << "\t\t" << t.getSeasonRating() << endl;
        //outs << "\t\t";
        //t.printGameRatings(outs);
        //outs << endl;
        
        outs2 << t.getSeasonRating() << endl;
    }
    
    outs2.close();
}

void League::normalizeRatings() {
    for (int i = 0; i < NUM_TEAMS; i++) {
        double newRating = ((teamList[i].getSeasonRating() - MEAN_GAME) / SDEV_GAME);
        teamList[i].setSeasonRating(newRating);
    }
}

Team League::getTeamFromStr(string str) {
    for (int i = 0; i < NUM_TEAMS; i++) {
        if (teamList[i].getName() == str) {
            return teamList[i];
        }
    }
    return Team();
}

int League::findNumDigits(string str) {
    int i = str.size() - 1;
    int count = 0;
    while (isdigit(str.at(i))) {
        i--;
        count++;
    }
    return count;
}

void League::removeSeed(string& team) {
    for (int i = 0; i < team.size(); i++) {
        if (team.at(i) == '(') {
            //check for number, some teams have () in their name such as
            //St. Johns (NY)
            if (isdigit(team.at(i + 1))) {
                int pos = team.find_last_of('(');
                //-1 is for the space always right before seed
                team = team.substr(0, pos - 1);
            }
        }
    }
}

void League::cropLine(string& str) {
    if (str.substr(str.size() - 5) == "Final") {
        str = str.substr(0, str.size() - 5);
    }
    else if (str.substr(str.size() - 2) == "OT") {
        str = str.substr(0, str.size() - 2);
    }
    //take 2 spaces off if number isn't at 2nd to last position
    if (!isdigit(str.at(str.size() - 2))) {
        str = str.substr(0, str.size() - 2);
    }
    //take 1 off otherwise
    else {
        str = str.substr(0, str.size() - 1);
    }
}