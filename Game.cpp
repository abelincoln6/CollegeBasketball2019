#include "Game.h"
//#include "Team.h"

using namespace std;

Game::Game() {
    opponent = Team();
    MOV = 0;
    day = 0;
    isWon = false;
    calculateGameRating(isWon, MOV, home);
}

Game::Game(Team o, int MOVin, bool win) {
    opponent = o;
    MOV = MOVin;
    isWon = win;
    calculateGameRating(isWon, MOV, home);
}

Game::Game(Team o, int MOVin, bool win, bool homeGame) {
    opponent = o;
    MOV = MOVin;
    isWon = win;
    home = homeGame;
    calculateGameRating(isWon, MOV, home);
}

Game::Game(Team o, int MOVin, bool win, int dayin) {
    opponent = o;
    MOV = MOVin;
    isWon = win;
    day = dayin;
    calculateGameRating(isWon, MOV, home);
}

double Game::getRating() {
    return rating;
}

void Game::calculateGameRating(bool win, bool home, int MOV) {
    int oppGP = opponent.getGP();
    double oppRating = opponent.getRating();
    double ratingCoef = 0;
    if (oppRating >= 0) {
        if (oppRating > GOOD_TEAM_CUTOFF) {
            ratingCoef += GOOD_TEAM_BOOST;
        }
        ratingCoef = sqrt(oppRating);
    }
    else {
        ratingCoef = -sqrt(abs(oppRating));
    }
    //ratingCoef *= sqrt(oppGP);
    double MOVd = MOV;
    if (win) {
        rating = (ratingCoef * OPP_RATING_WEIGHT) + WIN_BOOST + sqrt(MOVd);
    }
    else {
        rating = (ratingCoef * OPP_RATING_WEIGHT) - WIN_BOOST - sqrt(MOVd);
    }
    if (home) {
        rating -= ROAD_BOOST;
    }
    else {
        rating += ROAD_BOOST;
    }
}

bool Game::isWin() {
    return isWon;
}

bool Game::isHome() {
    return home;
}

Team Game::getOpponent() {
    return opponent;
}

void Game::setOpponent(Team o) {
    opponent = o;
}

int Game::getMOV() {
    return MOV;
}

void Game::setMOV(int n) {
    MOV = n;
}

int Game::getDay() {
    return day;
}

void Game::setDay(int d) {
    day = d;
}