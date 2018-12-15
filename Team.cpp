#include "Team.h"

Team::Team() {
    teamName = "NOT D1";
    setStatsToZero();
    rating = NOT_D1_RATING;
}

Team::Team(string name) {
    teamName = name;
    setStatsToZero();
}

void Team::setStatsToZero() {
    statRating = 0;
    seasonRating = 0;
    rating = 0;
    TS = 0;
    TOV = 0;
    TSA = 0;
    TOVA = 0;
    ORB = 0;
    ORBA = 0;
    GP = 0;
    wins = 0;
    losses = 0;
}

double Team::calculateRating() {
    double rar = statRating * STAT_WEIGHT +
        seasonRating * GAME_WEIGHT;
    return rar;
}

void Team::addGame(double rat, bool win) {
    GP++;
    if (win) {
        wins++;
    }
    else {
        losses++;
    }

    gameRatings.push_back(rat);
    //change gameRating to new average of all game ratings
    double total = 0;
    for (int i = 0; i < gameRatings.size(); i++) {
        total += gameRatings[i];
    }
    seasonRating = total / GP;
    rating = calculateRating();
}

string Team::getName() {
    return teamName;
}

double Team::getRating() {
    return rating;
}

double Team::getSeasonRating() {
    return seasonRating;
}

double Team::getStatRating() {
    return statRating;
}

void Team::printGameRatings(ofstream& outs) {
    for (int i = 0; i < gameRatings.size(); i++) {
        outs << gameRatings[i] << "\t\t";
    }
}

void Team::setName(string name) {
    teamName = name;
}

void Team::setRating(double rateIn) {
    rating = rateIn;
}

void Team::setSeasonRating(double rat) {
    seasonRating = rat;
}

void Team::setStatRating(double rat) {
    statRating = rat;
}

double Team::getTS() {
    return TS;
}

void Team::setTS(double num) {
    TS = num;
}

double Team::getTOV() {
    return TOV;
}

void Team::setTOV(double num) {
    TOV = num;
}

double Team::getORB() {
    return ORB;
}

void Team::setORB(double num) {
    ORB = num;
}

double Team::getTSA() {
    return TSA;
}

void Team::setTSA(double num) {
    TSA = num;
}

double Team::getTOVA() {
    return TOVA;
}

void Team::setTOVA(double num) {
    TOVA = num;
}

double Team::getORBA() {
    return ORBA;
}

void Team::setORBA(double num) {
    ORBA = num;
}

int Team::getGP() {
    return GP;
}

int Team::getWins() {
    return wins;
}

int Team::getLosses() {
    return losses;
}