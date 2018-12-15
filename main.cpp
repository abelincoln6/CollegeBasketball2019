#include "Team.h"
#include "Game.h"
#include "Global.h"
#include "League.h"

using namespace std;

int main() {

    League league;

    ifstream scoresIn;
    scoresIn.open("Scores.txt");
    league.readScores(scoresIn);
    scoresIn.close();

    league.normalizeRatings();

    ofstream outs;
    outs.open("Table.txt");
    league.printTeams(outs);
    outs.close();

    return 0;
}

