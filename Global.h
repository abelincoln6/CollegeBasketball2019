#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

const int NUM_TEAMS = 353;
const double ROAD_BOOST = 0.4;
const double TS_WEIGHT = 0.4;
const double TOV_WEIGHT = 0.4;
const double ORB_WEIGHT = 0.2;
const double STAT_WEIGHT = 1.0;
const double GAME_WEIGHT = 2.0;
const double OPP_RATING_WEIGHT = 0.75;
const double GOOD_TEAM_CUTOFF = 1.0;
const double GOOD_TEAM_BOOST = 2;
const double MEAN_TSDiff = 0.01749575071;
const double MEAN_TOVDiff = 0.7773371105;
const double MEAN_ORBDiff = 1.49379845;
const double SDEV_TSDiff = 0.05947579348;
const double SDEV_TOVDiff = 3.200958085;
const double SDEV_ORBDiff = 5.774852827;
const double MEAN_GAME = -2.011817269;
const double SDEV_GAME = 0.8821230872;
const double NOT_D1_RATING = -20;
const double WIN_BOOST = 1;